#ifndef OPENCARDASHBOARD_SENSORS_SENSORMANAGERS_H
#define OPENCARDASHBOARD_SENSORS_SENSORMANAGERS_H

#include <QObject>
#include <QHash>

namespace OpenCarDashboard
{

namespace Sensors
{

class BaseSensor;

class SensorManagers : public QObject
{
    Q_OBJECT
public :
    static SensorManagers* sensorManagers();
    void addSensor(const QString &sensorName, BaseSensor *sensor);
    void removeSensor(const QString &sensor);

private:
    SensorManagers();
    static SensorManagers *m_instance;
    QHash<QString, BaseSensor *> m_sensors;
};

} // Sensors

} // OpenCarDashboard

#endif // OPENCARDASHBOARD_SENSORS_SENSORMANAGERS_H
