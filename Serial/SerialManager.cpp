#include "SerialManager.h"
#include <QDebug>
#include <QSerialPortInfo>
#include "SensorsManager.h"
#include <QJsonDocument>
#include <QJsonObject>

namespace OpenCarDashboard
{

namespace Com
{

SerialManager::SerialManager(QObject *parent)
    : QObject(parent)
    , m_sensorsManager(Q_NULLPTR)
    , m_actuatorsManager(Q_NULLPTR)
{
    QTimer *timer = new QTimer();
    QObject::connect(timer, SIGNAL(timeout()), this, SLOT(sendCommand()));
    timer->start(100);
}

SerialManager::~SerialManager()
{
    qDebug() << Q_FUNC_INFO;
    closeAllSerialDevices();
    qDeleteAll(m_serialPorts);
    m_serialPortCommandData.clear();
}

void SerialManager::addSerialDevice(const QString &name,
                                    quint32 baudrate,
                                    QSerialPort::DataBits dataBits,
                                    QSerialPort::Parity parity,
                                    QSerialPort::FlowControl flowControl,
                                    QSerialPort::StopBits stopBits)
{
    if (m_serialPorts.contains(name))
        this->closeSerialDevice(name);
    QSerialPort *serialPort = new QSerialPort(name);
    qDebug() << Q_FUNC_INFO << "Trying to open serial port";

    serialPort->open(QIODevice::ReadWrite);

    if (serialPort->isOpen())
    {
        qDebug() << Q_FUNC_INFO << "Open successfull";
        if (!serialPort->setBaudRate(baudrate))
            qDebug() << Q_FUNC_INFO << "Couldn't set baudrate";
        if (!serialPort->setDataBits(dataBits))
            qDebug() << Q_FUNC_INFO << "Couldn't set data bits";
        if (!serialPort->setParity(parity))
            qDebug() << Q_FUNC_INFO << "Couldn't set parity";
        if (!serialPort->setStopBits(stopBits))
            qDebug() << Q_FUNC_INFO << "Couldn't set stop";
        if (!serialPort->setFlowControl(flowControl))
            qDebug() << Q_FUNC_INFO << "Coudldn't set flow control";

        m_serialPorts[name] = serialPort;
        QObject::connect(serialPort, SIGNAL(aboutToClose()), this, SLOT(onSerialClosedDetected()));
        QObject::connect(serialPort, SIGNAL(readyRead()), this, SLOT(onReadyRead()));
        QObject::connect(serialPort, SIGNAL(error(QSerialPort::SerialPortError)), this, SLOT(onError(QSerialPort::SerialPortError)));
        this->parseCommands(serialPort);
    }
    else
    {
        qDebug() << Q_FUNC_INFO << "Couldn't open serial port";
        delete serialPort;
    }
}

void SerialManager::removeSerialDevice(const QString &name)
{
    QSerialPort *serial = Q_NULLPTR;
    if (m_serialPorts.contains(name))
    {   serial = m_serialPorts[name];
        m_serialPortCommandData.remove(serial);
        this->closeSerialDevice(name);
        m_serialPorts.remove(name);

    }
}

void SerialManager::closeAllSerialDevices()
{
    foreach (const QString &name, m_serialPorts.keys())
        this->closeSerialDevice(name);
}

void SerialManager::closeSerialDevice(const QString &name)
{
    qDebug() << Q_FUNC_INFO;
    if (m_serialPorts.contains(name)) {
        //        m_serialPorts[name]->write(QByteArray("{off}\n"));
        m_serialPorts[name]->waitForBytesWritten(750);
        m_serialPorts[name]->close();
    }
}

QString SerialManager::communicationInterface() const
{
    return QStringLiteral("Arduino Serial");
}

void SerialManager::setSensorsManager(Sensors::SensorsManager *manager)
{
    m_sensorsManager = manager;
}

void SerialManager::enableSensor(Sensors::SensorType::SensorTypeEnum sensorType)
{
    dataframe frame;

    frame.magicStart = MAGIC_START_HEADER;
    frame.magicEnd = MAGIC_END_HEADER;
    frame.data = sensorType;
    frame.id = ENABLE_SENSOR;
    frame.reply = 0;
    frame.crc = this->crc((char *)&frame.data, 4);
    m_serialPorts["/dev/ttymxc3"]->write((char *)&frame, sizeof(dataframe));
}

void SerialManager::disableSensor(Sensors::SensorType::SensorTypeEnum sensorType)
{
    dataframe frame;

    frame.magicStart = MAGIC_START_HEADER;
    frame.magicEnd = MAGIC_END_HEADER;
    frame.data = sensorType;
    frame.id = DISABLE_SENSOR;
    frame.reply = 0;
    frame.crc = this->crc((char *)&frame.data, 4);
    m_serialPorts["/dev/ttymxc3"]->write((char *)&frame, sizeof(dataframe));
}

void SerialManager::setActuatorManager(Actuators::ActuatorsManager *manager)
{
    m_actuatorsManager = manager;
}

void SerialManager::enableActuator(Actuators::ActuatorType::ActuatorTypeEnum actuatorType)
{
    dataframe frame;

    frame.magicStart = MAGIC_START_HEADER;
    frame.magicEnd = MAGIC_END_HEADER;
    frame.data = actuatorType;
    frame.id = ENABLE_ACTUATOR;
    frame.reply = 0;
    frame.crc = this->crc((char *)&frame.data, 4);
    m_serialPorts["/dev/ttymxc3"]->write((char *)&frame, sizeof(dataframe));
}

void SerialManager::disableActuator(Actuators::ActuatorType::ActuatorTypeEnum actuatorType)
{
    dataframe frame;

    frame.magicStart = MAGIC_START_HEADER;
    frame.magicEnd = MAGIC_END_HEADER;
    frame.data = actuatorType;
    frame.id = DISABLE_ACTUATOR;
    frame.reply = 0;
    frame.crc = this->crc((char *)&frame.data, 4);
    m_serialPorts["/dev/ttymxc3"]->write((char *)&frame, sizeof(dataframe));
}

unsigned char SerialManager::crc(char *message, u_int8_t length)
{
    unsigned char i, crc = 0;

    for (i = 0; i < length; i++)
        crc ^= message[i];
    return crc;
}

void SerialManager::parseCommands(QSerialPort *serial)
{
    QByteArray readData = m_serialPortTmpCommandData[serial] + serial->readAll();
    m_serialPortTmpCommandData[serial].clear();
    QList<dataframe*> commands;

    int pos = 0;
    int len = readData.length();
    int dataframeSize = (short)sizeof(dataframe);

    while (len >= dataframeSize)
    {
        dataframe *frame = (dataframe*)(readData.data() + pos);
        // Find beginning of frame by checking header
        while (frame->magicStart != MAGIC_START_HEADER && frame->magicEnd != MAGIC_END_HEADER && len > dataframeSize)
        {
            len--;
            frame = (dataframe*)(readData.data() + ++pos);
        }
        if (len < dataframeSize)
            m_serialPortTmpCommandData[serial] += readData.left(len);

        pos += dataframeSize;
        len -= dataframeSize;

        unsigned char computed = this->crc((char *)&frame->data, 4);
        if (computed == frame->crc)
            commands.append(frame);
    }
    if (len > 0)
        m_serialPortTmpCommandData[serial] += readData.right(len);
}

void SerialManager::onReadyRead()
{
    //    qDebug() << Q_FUNC_INFO;
    this->parseCommands(static_cast<QSerialPort*>(this->sender()));
}

void SerialManager::onSerialClosedDetected()
{
    QSerialPort *serial = static_cast<QSerialPort*>(this->sender());
    qDebug() << Q_FUNC_INFO << serial->portName() << " was closed";
}

void SerialManager::onError(QSerialPort::SerialPortError error)
{
    QSerialPort *serial = static_cast<QSerialPort*>(this->sender());
    qWarning() << Q_FUNC_INFO << serial->errorString() << error;
}

void SerialManager::sendCommand()
{
    static int j = 0;
    for (int i = 0; i < 3; i++)
    {
        dataframe frame;

        frame.magicStart = MAGIC_START_HEADER;
        frame.magicEnd = MAGIC_END_HEADER;
        frame.data = j++;
        frame.id = 1;
        frame.reply = 0;
        frame.crc = this->crc((char *)&frame.data, 4);
        qDebug() << "Wrote " << m_serialPorts["/dev/ttymxc3"]->write((char *)&frame, sizeof(dataframe)) << j - 1;
    }
}

} // Com

} // OpenCarDashboard
