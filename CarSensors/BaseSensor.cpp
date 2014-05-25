#include "BaseSensor.h"
#include "SensorsManager.h"

namespace OpenCarDashboard
{

namespace Sensors
{

BaseSensor::BaseSensor(QObject *parent) : QObject(parent),
    m_type(SensorType::Unknown)
{
}

QString BaseSensor::sensor() const
{
    return m_sensor;
}

void BaseSensor::setSensor(const QString &sensor)
{
    if (sensor != m_sensor)
    {
        m_sensor = sensor;
        emit sensorChanged();
    }
}

SensorType::SensorTypeEnum BaseSensor::type() const
{
    return m_type;
}

void BaseSensor::setType(SensorType::SensorTypeEnum type)
{
    if (m_type != type)
    {
        Sensors::SensorsManager::sensorsManager()->removeSensor(this);
        m_type = type;
        Sensors::SensorsManager::sensorsManager()->addSensor(this);
        emit typeChanged();
    }
}

} // Sensors

} // OpenCarDashboard
