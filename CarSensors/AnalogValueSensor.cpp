#include "AnalogValueSensor.h"
#include <QJsonValue>

namespace OpenCarDashboard
{

namespace Sensors
{

AnalogValueSensor::AnalogValueSensor() : ValueSensor(),
    m_analogBitsPrecision(10),
    m_maxBitsValue((1 << 10))
{
}

int AnalogValueSensor::analogBitsPrecision() const
{
    return m_analogBitsPrecision;
}

void AnalogValueSensor::setAnalogBitsPrecision(int analogBitsPrecision)
{
    if (m_analogBitsPrecision != analogBitsPrecision)
    {
        m_analogBitsPrecision = analogBitsPrecision;
        m_maxBitsValue = (1 << m_analogBitsPrecision);
        emit analogBitsPrecisionChanged();
    }
}

} // Sensors

} // OpenCarDashboard
