#include "BaseActuator.h"
#include "ActuatorsManager.h"

namespace OpenCarDashboard
{

namespace Actuators
{

BaseActuator::BaseActuator(QObject *parent)
    : QObject(parent)
    , m_active(false)
    , m_type(ActuatorType::Unknown)
{
}

bool BaseActuator::active() const
{
    return m_active;
}

void BaseActuator::setActive(bool active)
{
    if (active != m_active)
    {
        m_active = active;
        ActuatorsManager::actuatorsManager()->updateActuator(this);
        emit activeChanged();
    }
}

ActuatorType::ActuatorTypeEnum BaseActuator::type() const
{
    return m_type;
}

void BaseActuator::setType(ActuatorType::ActuatorTypeEnum type)
{
    if (type != m_type)
    {
        ActuatorsManager::actuatorsManager()->removeActuator(this);
        m_type = type;
        ActuatorsManager::actuatorsManager()->addActuator(this);
        emit typeChanged();
    }
}

} // Actuators

} // OpenCarDashboard
