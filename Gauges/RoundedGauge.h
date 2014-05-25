#ifndef OPENCARDAHSBOARD_GAUGES_ROUNDEDGAUGE_H
#define OPENCARDASHBOARD_GAUGES_ROUNDEDGAUGE_H

#include <QQuickPaintedItem>

namespace OpenCarDashboard
{

namespace Sensors
{
class ValueSensor;
}

namespace Gauges
{

class RoundedGauge : public QQuickPaintedItem
{
    Q_OBJECT
    Q_PROPERTY(OpenCarDashboard::Sensors::ValueSensor *sensor READ sensor WRITE setSensor NOTIFY sensorChanged)
    Q_PROPERTY(int subDivisions READ subDivisions WRITE setSubDivisions NOTIFY subDivisionsChanged)
    Q_PROPERTY(QColor lowValuesColor READ lowValuesColor WRITE setLowValuesColor NOTIFY lowValuesColorChanged)
    Q_PROPERTY(QColor highValuesColor READ highValuesColor WRITE setHighValuesColor NOTIFY highValuesColorChanged)
public:
    RoundedGauge(QQuickItem *parent = 0);

    void paint(QPainter *painter);

    Sensors::ValueSensor *sensor() const;
    void setSensor(Sensors::ValueSensor *sensor);

    int subDivisions() const;
    void setSubDivisions(int subDivisions);

    QColor highValuesColor() const;
    void setHighValuesColor(const QColor &color);

    QColor lowValuesColor() const;
    void setLowValuesColor(const QColor &color);

protected:
    Sensors::ValueSensor *m_sensor;
    int m_subDivisions;
    QColor m_lowValuesColor;
    QColor m_highValuesColor;

signals:
    void sensorChanged();
    void subDivisionsChanged();
    void lowValuesColorChanged();
    void highValuesColorChanged();
};

} // Gauges

} // OpenCarDashboard

#endif // OPENGARDASHBOARD_GAUGES_ROUNDEDGAUGE_H
