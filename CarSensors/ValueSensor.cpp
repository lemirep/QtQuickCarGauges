#include "ValueSensor.h"

namespace OpenCarDashboard
{

namespace Sensors
{

ValueSensor::ValueSensor() : BaseSensor()
{
}

float ValueSensor::value() const
{
    return m_value;
}

void ValueSensor::setValue(float value)
{
    if (m_value != value)
    {
        m_value = value;
        emit valueChanged();
    }
}

float ValueSensor::minValue() const
{
    return m_minValue;
}

void ValueSensor::setMinValue(float minValue)
{
    if (minValue != m_minValue)
    {
        m_minValue = minValue;
        emit minValueChanged();
    }
}

float ValueSensor::maxValue() const
{
    return m_maxValue;
}

void ValueSensor::setMaxValue(float maxValue)
{
    if (maxValue != m_maxValue)
    {
        m_maxValue = maxValue;
        emit maxValueChanged();
    }
}

float ValueSensor::lowValueThreshold() const
{
    return m_lowValueThreshold;
}

void ValueSensor::setLowValueThreshold(float lowValueThreshold)
{
    if (lowValueThreshold != m_lowValueThreshold)
    {
        m_lowValueThreshold = lowValueThreshold;
        emit lowValueThresholdChanged();
    }
}

float ValueSensor::maxValueThreshold() const
{
    return m_maxValueThreshold;
}

void ValueSensor::setMaxValueThreshold(float maxValueThreshold)
{
    if (maxValueThreshold != m_maxValueThreshold)
    {
        m_maxValueThreshold = maxValueThreshold;
        emit maxValueThresholdChanged();
    }
}

} // Sensors

} // OpenCarDashboard
