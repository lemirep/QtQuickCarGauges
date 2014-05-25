#ifndef OPENCARDASHBOARD_ACTUATORS_ACTUATORENUMS_H
#define OPENCARDASHBOARD_ACTUATORS_ACTUATORENUMS_H

#include <QObject>

namespace OpenCarDashboard
{

namespace Actuators
{

class ActuatorType : public QObject
{
    Q_OBJECT
    Q_ENUMS(ActuatorTypeEnum)
public:
    ActuatorType(QObject *parent = 0) : QObject(parent)
    {}

    // To be completed as necessary to handle air conditionning, heater ...

    enum ActuatorTypeEnum
    {
        Unknown = 0,
        LeftTurnSignal,
        RightTurnSignal,
        Brake,
        HeadLights,
        Reverse,
        CourtesyLight
    };
};

} // Actuators

} // OpenCarDashboard

#endif // OPENCARDASHBOARD_ACTUATORS_ACTUATORENUMS_H
