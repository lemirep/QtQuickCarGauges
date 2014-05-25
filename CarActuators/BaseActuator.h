#ifndef OPENCARDASHBOARD_ACTUATORS_BASEACTUATOR_H
#define OPENCARDASHBOARD_ACTUATORS_BASEACTUATOR_H

#include <QObject>
#include "ActuatorEnums.h"

namespace OpenCarDashboard
{

namespace Actuators
{

class BaseActuator : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool active READ active WRITE setActive NOTIFY activeChanged)
    Q_PROPERTY(ActuatorType::ActuatorTypeEnum type READ type WRITE setType NOTIFY typeChanged)

public:
    BaseActuator(QObject *parent = 0);

    bool active() const;
    void setActive(bool active);

    ActuatorType::ActuatorTypeEnum type() const;
    void setType(ActuatorType::ActuatorTypeEnum type);

private:
    bool m_active;
    ActuatorType::ActuatorTypeEnum m_type;

signals:
    void activeChanged();
    void typeChanged();
};

} // Actuators

} // OpenCarDashboard

#endif // OPENCARDASHBOARD_ACTUATORS_BASEACTUATOR_H
