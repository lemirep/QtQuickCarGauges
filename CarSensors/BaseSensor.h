#ifndef OPENCARDASHBOARD_SENSORS_BASESENSOR_H
#define OPENCARDASHBOARD_SENSORS_BASESENSOR_H

#include <QObject>
#include <QQuickItem>

namespace OpenCarDashboard
{

namespace Sensors
{

class BaseSensor : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString sensor READ sensor WRITE setSensor NOTIFY sensorChanged)
public:
    BaseSensor();

    QString sensor() const;
    void setSensor(const QString &sensor);

private:
    QString m_sensor;

signals:
    void    valueChanged();
    void    sensorChanged();
};

} // Sensors

} // OpenCarDashboard

#endif // OPENCARDASHBOARD_SENSORS_BASESENSOR_H
