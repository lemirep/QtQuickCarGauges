#ifndef OPENCARDASHBOARD_COM_COMINTERFACE_H
#define OPENCARDASHBOARD_COM_COMINTERFACE_H

#include <QString>
#include "SensorEnums.h"
#include "ActuatorEnums.h"

namespace OpenCarDashboard
{

namespace Sensors
{
    class SensorsManager;
}

namespace Actuators
{
    class ActuatorsManager;
}

namespace Com
{

class ComInterface
{
public:
    virtual QString communicationInterface() const = 0;

    virtual void setSensorsManager(Sensors::SensorsManager *manager) = 0;
    virtual void enableSensor(Sensors::SensorType::SensorTypeEnum sensorType) = 0;
    virtual void disableSensor(Sensors::SensorType::SensorTypeEnum sensorType) = 0;

    virtual void setActuatorManager(Actuators::ActuatorsManager *manager) = 0;
    virtual void enableActuator(Actuators::ActuatorType::ActuatorTypeEnum actuatorType) = 0;
    virtual void disableActuator(Actuators::ActuatorType::ActuatorTypeEnum actuatorType) = 0;
};

} // Com

} // OpenCarDashboard

#endif // OPENCARDASHBOARD_COM_COMINTERFACE_H
