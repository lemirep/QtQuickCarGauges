#ifndef OPENCARDASHBOARD_SENSORS_SENSORMANAGERS_H
#define OPENCARDASHBOARD_SENSORS_SENSORMANAGERS_H

#include <QObject>
#include <QJsonObject>
#include <QHash>
#include "SensorEnums.h"

#ifdef Q_OS_UNIX
class QSocketNotifier;
#endif

namespace OpenCarDashboard
{

namespace Com
{
class ComInterface;
}

namespace Sensors
{

class BaseSensor;

class SensorsManager : public QObject
{
    Q_OBJECT
public :
    static SensorsManager* sensorsManager();

    void addSensor(BaseSensor *sensor);
    void removeSensor(BaseSensor *sensor);
    void updateSensors(SensorType::SensorTypeEnum sensorType, const QVariant &value);

    void setComInterface(Com::ComInterface *comInterface);
    Com::ComInterface *comInterface() const;

private:
    SensorsManager(QObject *parent = 0);

    static SensorsManager *m_instance;
    Com::ComInterface *m_comInterface;
    QMultiHash<SensorType::SensorTypeEnum, BaseSensor *> m_sensors;

#ifdef Q_OS_UNIX
public:
    static void hupSignalHandler(int unused);
    static void termSignalHandler(int unused);
    static int setup_unix_signal_handlers();

private:
    static int sighupFd[2];
    static int sigtermFd[2];

    QSocketNotifier *snHup;
    QSocketNotifier *snTerm;

private slots:
    void sigHupTriggered();
    void sigTermTriggered();
#endif
};

} // Sensors

} // OpenCarDashboard

#endif // OPENCARDASHBOARD_SENSORS_SENSORMANAGERS_H
