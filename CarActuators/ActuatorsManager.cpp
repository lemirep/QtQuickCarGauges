#include "ActuatorsManager.h"
#include "BaseActuator.h"
#include "ComInterface.h"
#include <QDebug>

namespace OpenCarDashboard
{

namespace Actuators
{

ActuatorsManager *ActuatorsManager::m_instance = Q_NULLPTR;

ActuatorsManager::ActuatorsManager(QObject *parent)
    : QObject(parent)
    , m_comInterface(Q_NULLPTR)
{
}

ActuatorsManager *ActuatorsManager::actuatorsManager()
{
    if (ActuatorsManager::m_instance == Q_NULLPTR)
        ActuatorsManager::m_instance = new ActuatorsManager();
    return ActuatorsManager::m_instance;
}

void ActuatorsManager::addActuator(BaseActuator *actuator)
{
    if (!m_actuators.contains(actuator->type()))
    {
        m_actuators[actuator->type()] = actuator;
        m_comInterface->enableActuator(actuator->type());
    }
}

void ActuatorsManager::removeActuator(BaseActuator *actuator)
{
    if (m_actuators.contains(actuator->type()))
        m_comInterface->disableActuator(actuator->type());
    m_actuators.remove(actuator->type());
}

void ActuatorsManager::updateActuator(BaseActuator *actuator)
{
    qDebug() << Q_FUNC_INFO;
}

void ActuatorsManager::setComInterface(Com::ComInterface *comInterface)
{
    m_comInterface = comInterface;
    m_comInterface->setActuatorManager(this);
}

Com::ComInterface *ActuatorsManager::comInterface() const
{
    return m_comInterface;
}

} // Actuators

} // OpenCarDashboard
