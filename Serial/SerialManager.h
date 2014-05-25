#ifndef OPENCARDASHBOARD_COM_SERIALMANAGER_H
#define OPENCARDASBBOARD_COM_SERIALMANAGER_H

#include <QObject>
#include <QHash>
#include <QSerialPort>
#include <QTimer>
#include "ComInterface.h"

#define MAGIC_START_HEADER 0xFFF8
#define MAGIC_END_HEADER 0x8FFF

#define ENABLE_SENSOR 100
#define DISABLE_SENSOR 101
#define ENABLE_ACTUATOR 102
#define DISABLE_ACTUATOR 103
#define ACTIVATE_ACTUATOR 104
#define DEACTIVATE_ACTUATOR 105

#define CRC7_POLY 0x91;

namespace OpenCarDashboard
{

namespace Com
{

struct dataframe
{
    short unsigned int magicStart;
    short unsigned id;
    quint32 data;
    unsigned char crc;
    // Type of reply expected if any
    unsigned char reply;
    short unsigned magicEnd;
};

class SerialManager : public QObject, public ComInterface
{
    Q_OBJECT
public:
    SerialManager(QObject * parent = 0);
    ~SerialManager();

    void addSerialDevice(const QString &name,
                         quint32 baudrate = 115200,
                         QSerialPort::DataBits dataBits = QSerialPort::Data8,
                         QSerialPort::Parity parity = QSerialPort::NoParity,
                         QSerialPort::FlowControl flowControl = QSerialPort::NoFlowControl,
                         QSerialPort::StopBits stopBits = QSerialPort::OneStop);
    void removeSerialDevice(const QString &name);
    void closeAllSerialDevices();
    void closeSerialDevice(const QString &name);

    // ComInterface interface
    QString communicationInterface() const Q_DECL_OVERRIDE;
    void setSensorsManager(Sensors::SensorsManager *manager) Q_DECL_OVERRIDE;
    void enableSensor(Sensors::SensorType::SensorTypeEnum sensorType) Q_DECL_OVERRIDE;
    void disableSensor(Sensors::SensorType::SensorTypeEnum sensorType) Q_DECL_OVERRIDE;

    void setActuatorManager(Actuators::ActuatorsManager *manager) Q_DECL_OVERRIDE;
    void enableActuator(Actuators::ActuatorType::ActuatorTypeEnum actuatorType) Q_DECL_OVERRIDE;
    void disableActuator(Actuators::ActuatorType::ActuatorTypeEnum actuatorType) Q_DECL_OVERRIDE;

private:
    Sensors::SensorsManager *m_sensorsManager;
    Actuators::ActuatorsManager *m_actuatorsManager;
    QHash<QString, QSerialPort*> m_serialPorts;
    QHash<QSerialPort*, QList<dataframe> > m_serialPortCommandData;
    QHash<QSerialPort*, QByteArray> m_serialPortTmpCommandData;

    void parseCommands(QSerialPort *serial);
    unsigned char crc(char *message, u_int8_t length);


private slots:
    void onReadyRead();
    void onSerialClosedDetected();
    void onError(QSerialPort::SerialPortError error);
    void sendCommand();

};

} // Com

} // OpenCarDashboard

#endif // OPENCARDASHBOARD_COM_SERIALMANAGER_H
