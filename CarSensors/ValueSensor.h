#ifndef OPENCARDASHBOARD_SENSORS_VALUESENSOR_H
#define OPENCARDASHBOARD_SENSORS_VALUESENSOR_H

#include "BaseSensor.h"
#include <QTimer>

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
    Q_PROPERTY(int refreshRate READ refreshRate WRITE setRefreshRate NOTIFY refreshRateChanged)
public:
    ValueSensor(QObject *parent = 0);

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

    int refreshRate() const;
    void setRefreshRate(int refreshRate);

protected:
    float m_value;
    float m_tmpValue;
    float m_refreshes;
    float m_minValue;
    float m_maxValue;
    float m_lowValueThreshold;
    float m_maxValueThreshold;
    int m_refreshRate;
    QTimer m_refreshTimeout;

protected slots:
    void refreshTimeoutElapsed();

signals:
    void valueChanged();
    void minValueChanged();
    void maxValueChanged();
    void lowValueThresholdChanged();
    void maxValueThresholdChanged();
    void refreshRateChanged();
};

} // Sensors

} // OpenCarDashboard

#endif // OPENCARDASHBOARD_SENSORS_VALUESENSOR_H
