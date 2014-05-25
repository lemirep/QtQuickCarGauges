#include "ValueSensor.h"

namespace OpenCarDashboard
{

namespace Sensors
{

ValueSensor::ValueSensor(QObject *parent) : BaseSensor(parent),
    m_value(0),
    m_tmpValue(0),
    m_refreshes(0),
    m_minValue(0),
    m_maxValue(0),
    m_refreshRate(0)
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
        if (m_refreshRate)
        {
            m_refreshes++;
            m_tmpValue += value;
        }
        else
        {
            m_value = value;
            emit valueChanged();
        }
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

int ValueSensor::refreshRate() const
{
    return m_refreshRate;
}

void ValueSensor::setRefreshRate(int refreshRate)
{
    if (m_refreshRate != refreshRate)
    {
        m_refreshRate = refreshRate;
        if (m_refreshTimeout.remainingTime() < m_refreshRate)
            this->refreshTimeoutElapsed();
        if (m_refreshRate)
        {
            if (!m_refreshTimeout.isActive())
                QObject::connect(&m_refreshTimeout, SIGNAL(timeout()), this, SLOT(refreshTimeoutElapsed()));
            m_refreshTimeout.start(m_refreshRate);
        }
        else
        {
            QObject::disconnect(&m_refreshTimeout, SIGNAL(timeout()), this, SLOT(refreshTimeoutElapsed()));
            m_refreshTimeout.stop();
        }
        emit refreshRateChanged();
    }
}

void ValueSensor::refreshTimeoutElapsed()
{
    if (!m_refreshes)
        return ;
    m_value = m_tmpValue / m_refreshes;
    m_refreshes = 0;
    m_tmpValue = 0;
    emit valueChanged();
}

} // Sensors

} // OpenCarDashboard
