#ifndef OPENCARDASHBOARD_SENSORS_VALUESENSOR_H
#define OPENCARDASHBOARD_SENSORS_VALUESENSOR_H

#include "BaseSensor.h"

namespace OpenCarDashboard
{

namespace Sensors
{

class ValueSensor : public BaseSensor
{
    Q_OBJECT
    Q_PROPERTY(float value READ value WRITE setValue NOTIFY valueChanged)
    Q_PROPERTY(float minValue READ minValue WRITE setMinValue NOTIFY minValueChanged)
    Q_PROPERTY(float maxValue READ maxValue WRITE setMaxValue NOTIFY maxValueChanged)
    Q_PROPERTY(float lowValueThreshold READ lowValueThreshold WRITE setLowValueThreshold NOTIFY lowValueThresholdChanged)
    Q_PROPERTY(float maxValueThreshold READ maxValueThreshold WRITE setMaxValueThreshold NOTIFY maxValueThresholdChanged)
public:
    ValueSensor();

    float value() const;
    void setValue(float value);

    float minValue() const;
    void setMinValue(float minValue);

    float maxValue() const;
    void setMaxValue(float maxValue);

    float lowValueThreshold() const;
    void setLowValueThreshold(float lowValueThreshold);

    float maxValueThreshold() const;
    void setMaxValueThreshold(float maxValueThreshold);

private:
    float m_value;
    float m_minValue;
    float m_maxValue;
    float m_lowValueThreshold;
    float m_maxValueThreshold;
signals:
    void valueChanged();
    void minValueChanged();
    void maxValueChanged();
    void lowValueThresholdChanged();
    void maxValueThresholdChanged();
};

} // Sensors

} // OpenCarDashboard

#endif // OPENCARDASHBOARD_SENSORS_VALUESENSOR_H
