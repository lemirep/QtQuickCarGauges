#ifndef OPENCARDASHBOARD_ACTUATORS_ACTUATORSMANAGER_H
#define OPENCARDASHBOARD_ACTUATORS_ACTUATORSMANAGER_H

#include <QObject>
#include <QHash>
#include "ActuatorEnums.h"

namespace OpenCarDashboard
{

namespace Com
{
class ComInterface;
}

namespace Actuators
{

class BaseActuator;

class ActuatorsManager : public QObject
{
    Q_OBJECT
public:
    static ActuatorsManager* actuatorsManager();

    void addActuator(BaseActuator *actuator);
    void removeActuator(BaseActuator *actuator);
    void updateActuator(BaseActuator *actuator);

    void setComInterface(Com::ComInterface *comInterface);
    Com::ComInterface *comInterface() const;

private:
    ActuatorsManager(QObject *parent = 0);

    static ActuatorsManager *m_instance;
    Com::ComInterface *m_comInterface;
    QHash<ActuatorType::ActuatorTypeEnum, BaseActuator *> m_actuators;
};

} // Actuators

} // OpenCarDashboard

#endif // OPENCARDASHBOARD_ACTUATORS_ACTUATORSMANAGER_H
