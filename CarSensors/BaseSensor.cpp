#include "BaseSensor.h"

namespace OpenCarDashboard
{

namespace Sensors
{

BaseSensor::BaseSensor() : QObject()
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

} // Sensors

} // OpenCarDashboard
