#include "RoundedGauge.h"
#include <QPainterPath>
#include <QPainter>

namespace OpenCarDashboard
{

namespace Gauges
{

RoundedGauge::RoundedGauge(QQuickItem *parent) : QQuickPaintedItem(parent),
    m_sensor(Q_NULLPTR),
    m_subDivisions(2),
    m_lowValuesColor(QColor(0, 0, 255)),
    m_highValuesColor(QColor(255, 0, 0))
{
}


void RoundedGauge::paint(QPainter *painter)
{
    QPointF center(x() + width() * 0.5, height() * 0.5);
    QPainterPath outerBezel;
//    outerBezel.moveTo(center);
//    qDebug() << Q_FUNC_INFO << x() << y() << width() << height();
//    outerBezel.arcTo(QRectF(QPointF(x(), y()), QSizeF(width(), height())), 30, 300);
//    outerBezel.closeSubpath();

//    outerBezel.moveTo(50.0, 50.0);
    outerBezel.arcTo(20.0, 30.0, 60.0, 40.0, 30, 300.0);
//    outerBezel.closeSubpath();

    painter->setRenderHint(QPainter::Antialiasing);
    painter->setBrush(Qt::SolidPattern);
    painter->setPen(QColor(255, 255, 255));
    painter->drawPath(outerBezel);
}

Sensors::ValueSensor *RoundedGauge::sensor() const
{
    return m_sensor;
}

void RoundedGauge::setSensor(Sensors::ValueSensor *sensor)
{
    if (m_sensor != sensor)
    {
        m_sensor = sensor;
        emit sensorChanged();
    }
}

int RoundedGauge::subDivisions() const
{
    return m_subDivisions;
}

void RoundedGauge::setSubDivisions(int subDivisions)
{
    if (m_subDivisions != subDivisions)
    {
        m_subDivisions = subDivisions;
        emit subDivisionsChanged();
    }
}

QColor RoundedGauge::highValuesColor() const
{
    return m_highValuesColor;
}

void RoundedGauge::setHighValuesColor(const QColor &color)
{
    if (m_highValuesColor != color)
    {
        m_highValuesColor = color;
        emit highValuesColorChanged();
    }
}

QColor RoundedGauge::lowValuesColor() const
{
    return m_lowValuesColor;
}

void RoundedGauge::setLowValuesColor(const QColor &color)
{
    if (m_lowValuesColor != color)
    {
        m_lowValuesColor = color;
        emit lowValuesColorChanged();
    }
}

} // Gauges

} // OpenCarDashboard
