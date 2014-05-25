#ifndef OPENCARDASHBOARD_SENSORS_SENSORENUMS_H
#define OPENCARDASHBOARD_SENSORS_SENSORENUMS_H

#include <QObject>

namespace OpenCarDashboard
{

namespace Sensors
{

class SensorType : public QObject
{
    Q_OBJECT
    Q_ENUMS(SensorTypeEnum)

public:
    SensorType(QObject *parent = 0) : QObject(parent)
    {}

    enum SensorTypeEnum
    {
        Unknown = 0,
        RPM,
        Speed,
        WaterTemperature,
        WaterPressure,
        WaterLevel,
        OilTemperature,
        OilPressure,
        OilLevel,
        FuelPressure,
        FuelLevel,
        MeanEffectivePressure,
        OutsideTemperature,
        LowBandOxygen,
        WideBandOxygen
    };
};

} // Sensors

} // OpenCarDashboard

#endif // OPENCARDASHBOARD_SENSORS_SENSORENUMS_H
