#ifndef OPENCARDASHBOARD_SENSORS_ANALOGVALUESENSOR_H
#define OPENCARDASHBOARD_SENSORS_ANALOGVALUESENSOR_H

#include "ValueSensor.h"

namespace OpenCarDashboard
{

namespace Sensors
{

class AnalogValueSensor : public ValueSensor
{
    Q_OBJECT
    Q_PROPERTY(int analogBitsPrecision READ analogBitsPrecision WRITE setAnalogBitsPrecision NOTIFY analogBitsPrecisionChanged)
public:
    AnalogValueSensor();

    int analogBitsPrecision() const;
    void setAnalogBitsPrecision(int analogBitsPrecision);

private:
    int m_analogBitsPrecision;
    int m_maxBitsValue;

signals:
    void analogBitsPrecisionChanged();

};

} // Sensors

} // OpenCarDashboard

#endif // OPENCARDASHBOARD_SENSORS_ANALOGVALUESENSOR_H
