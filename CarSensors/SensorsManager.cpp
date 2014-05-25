#include "SensorsManager.h"
#include "BaseSensor.h"
#include "ValueSensor.h"
#include "BooleanSensor.h"
#include "AnalogValueSensor.h"
#include "SensorEnums.h"
#include "RoundedGauge.h"
#include "ComInterface.h"

#include <QJsonValue>

#ifdef Q_OS_LINUX
#include <QSocketNotifier>
#include <csignal>
#include <sys/socket.h>
#endif

namespace OpenCarDashboard
{

namespace Sensors
{

SensorsManager *SensorsManager::m_instance = Q_NULLPTR;
int SensorsManager::sighupFd[2];
int SensorsManager::sigtermFd[2];


SensorsManager::SensorsManager(QObject *parent)
    : QObject(parent)
    , m_comInterface(Q_NULLPTR)
{
    qmlRegisterType<SensorType>("OpenCarDashboard", 1, 0, "SensorType");
    qmlRegisterType<ValueSensor>("OpenCarDashboard", 1, 0, "ValueSensor");
    qmlRegisterType<AnalogValueSensor>("OpenCarDashboard", 1, 0, "AnalogValueSensor");
    qmlRegisterType<BooleanSensor>("OpenCarDashboard", 1, 0, "BooleanSensor");
    qmlRegisterType<Gauges::RoundedGauge>("OpenCarDashboard", 1, 0, "RoundedGauge");

#ifdef Q_OS_LINUX
    SensorsManager::setup_unix_signal_handlers();

    if (::socketpair(AF_UNIX, SOCK_STREAM, 0, sighupFd))
        qFatal("Couldn't create HUP socketpair");

    if (::socketpair(AF_UNIX, SOCK_STREAM, 0, sigtermFd))
        qFatal("Couldn't create TERM socketpair");
    snHup = new QSocketNotifier(sighupFd[1], QSocketNotifier::Read, this);
    QObject::connect(snHup, SIGNAL(activated(int)), this, SLOT(sigHupTriggered()));
    snTerm = new QSocketNotifier(sigtermFd[1], QSocketNotifier::Read, this);
    QObject::connect(snTerm, SIGNAL(activated(int)), this, SLOT(sigTermTriggered()));
#endif
}

#ifdef Q_OS_LINUX

void SensorsManager::hupSignalHandler(int unused)
{
    char a = 1;
    ::write(sighupFd[0], &a, sizeof(a));
}

void SensorsManager::termSignalHandler(int unused)
{
    char a = 1;
    ::write(sigtermFd[0], &a, sizeof(a));
}

int SensorsManager::setup_unix_signal_handlers()
{
    struct sigaction hup, term;

    hup.sa_handler = SensorsManager::hupSignalHandler;
    sigemptyset(&hup.sa_mask);
    hup.sa_flags = 0;
    hup.sa_flags |= SA_RESTART;

    if (sigaction(SIGINT, &hup, 0) > 0)
        return 1;

    term.sa_handler = SensorsManager::termSignalHandler;
    sigemptyset(&term.sa_mask);
    term.sa_flags |= SA_RESTART;

    if (sigaction(SIGTERM, &term, 0) > 0)
        return 2;

    return 0;
}

void SensorsManager::sigHupTriggered()
{
    snHup->setEnabled(false);
    char tmp;
    ::read(sighupFd[1], &tmp, sizeof(tmp));
    qDebug() << Q_FUNC_INFO;
    QCoreApplication::quit();
    snHup->setEnabled(true);
}

void SensorsManager::sigTermTriggered()
{
    snTerm->setEnabled(false);
    char tmp;
    ::read(sigtermFd[1], &tmp, sizeof(tmp));
    qDebug() << Q_FUNC_INFO;
    snTerm->setEnabled(true);
}

#endif

SensorsManager *SensorsManager::sensorsManager()
{
    if (SensorsManager::m_instance == Q_NULLPTR)
        SensorsManager::m_instance = new SensorsManager();
    return SensorsManager::m_instance;
}

void SensorsManager::addSensor(BaseSensor *sensor)
{
    if (!m_sensors.contains(sensor->type()))
        m_comInterface->enableSensor(sensor->type());
    if (!m_sensors.contains(sensor->type(), sensor))
        m_sensors.insertMulti(sensor->type(), sensor);
}

void SensorsManager::removeSensor(BaseSensor *sensor)
{
    m_sensors.remove(sensor->type(), sensor);
    if (!m_sensors.contains(sensor->type()))
        m_comInterface->disableSensor(sensor->type());
}

void SensorsManager::updateSensors(SensorType::SensorTypeEnum sensorType, const QVariant &value)
{
    // In the longterm, SensorManagers, ComInterface will be a standalone application
    // GUI will be separate applications communicating with this application through a JSON interface
    qDebug() << Q_FUNC_INFO << sensorType << value;
}

void SensorsManager::setComInterface(Com::ComInterface *comInterface)
{
    m_comInterface = comInterface;
    m_comInterface->setSensorsManager(this);
}

Com::ComInterface *SensorsManager::comInterface() const
{
    return m_comInterface;
}

} // Sensors

} // OpenCarDashboard

