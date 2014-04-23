#ifndef OPENCARDASHBOARD_COM_COMINTERFACE_H
#define OPENCARDASHBOARD_COM_COMINTERFACE_H

#include <QString>

namespace OpenCarDashboard
{

namespace Sensors
{
    class SensorManagers;
}

namespace Com
{

class ComInterface
{
public:
    virtual QString communicationInterface() const = 0;
    virtual void setSensorsManager(Sensors::SensorManagers *manager) = 0;
};

} // Com

} // OpenCarDashboard

#endif // OPENCARDASHBOARD_COM_COMINTERFACE_H
