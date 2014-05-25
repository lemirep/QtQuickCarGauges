#ifndef OPENCARDASHBOARD_SENSORS_BASESENSOR_H
#define OPENCARDASHBOARD_SENSORS_BASESENSOR_H

#include <QObject>
#include "SensorEnums.h"

class QJsonValue;

namespace OpenCarDashboard
{

namespace Sensors
{

class BaseSensor : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString sensor READ sensor WRITE setSensor NOTIFY sensorChanged)
    Q_PROPERTY(SensorType::SensorTypeEnum type READ type WRITE setType NOTIFY typeChanged)
public:
    BaseSensor(QObject *parent = 0);

    QString sensor() const;
    void setSensor(const QString &sensor);

    SensorType::SensorTypeEnum type() const;
    void setType(SensorType::SensorTypeEnum type);

private:
    QString m_sensor;
    SensorType::SensorTypeEnum m_type;

signals:
    void    valueChanged();
    void    sensorChanged();
    void    typeChanged();
};

} // Sensors

} // OpenCarDashboard

#endif // OPENCARDASHBOARD_SENSORS_BASESENSOR_H

