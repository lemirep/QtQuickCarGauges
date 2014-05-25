#include "BooleanSensor.h"
#include <QJsonValue>

namespace OpenCarDashboard
{

namespace Sensors
{

BooleanSensor::BooleanSensor() : BaseSensor()
{
}

bool BooleanSensor::value() const
{
    return m_value;
}

void BooleanSensor::setValue(bool value)
{
    if (m_value != value)
    {
        m_value = value;
        emit valueChanged();
    }
}

} // Sensors

} // OpenCarDashboard
