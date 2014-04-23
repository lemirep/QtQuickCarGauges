#include "SensorManagers.h"
#include "BaseSensor.h"

namespace OpenCarDashboard
{

namespace Sensors
{

SensorManagers *SensorManagers::m_instance = Q_NULLPTR;

SensorManagers::SensorManagers() : QObject()
{
}

SensorManagers *SensorManagers::sensorManagers()
{
    if (SensorManagers::m_instance == Q_NULLPTR)
        SensorManagers::m_instance = new SensorManagers();
    return SensorManagers::m_instance;
}

void SensorManagers::addSensor(const QString &sensorName, BaseSensor *sensor)
{
    m_sensors[sensorName] = sensor;
}

void SensorManagers::removeSensor(const QString &sensor)
{
    m_sensors.remove(sensor);
}

} // Sensors

} // OpenCarDashboard

