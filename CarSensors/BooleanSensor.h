#ifndef OPENCARDASHBOARD_SENSORS_BOOLEANSENSOR_H
#define OPENCARDASHBOARD_SENSORS_BOOLEANSENSOR_H

#include "BaseSensor.h"

namespace OpenCarDashboard
{

namespace Sensors
{

class BooleanSensor : public BaseSensor
{
    Q_OBJECT
    Q_PROPERTY(bool value READ value WRITE setValue NOTIFY valueChanged)

public:
    BooleanSensor();

    bool value() const;
    void setValue(bool value);

private:
    bool m_value;
signals:
    void valueChanged();
};

} // Sensors

} // OpenCarDashboard

#endif // OPENCARDASHBOARD_SENSORS_BOOLEANSENSOR_H
