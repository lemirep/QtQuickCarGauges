#include <ViewManagement.h>
#include <QCoreApplication>
#include <QScopedPointer>
#include <QMatrix4x4>
#include <QDebug>
#include <QtSerialPort>
#include <QSerialPortInfo>
#include "SerialManager.h"
#include "SensorManagers.h"

int main(int ac, char **av)
{
    QScopedPointer<QCoreApplication> app(new QCoreApplication(ac, av));
    ViewManagement *view = ViewManagement::getInstance();

    OpenCarDashboard::Com::SerialManager *manager = new OpenCarDashboard::Com::SerialManager(app.data());

//    view->setSource(QUrl("qrc:/qml/main.qml"));
    view->show();
    manager->setSensorsManager(OpenCarDashboard::Sensors::SensorManagers::sensorManagers());
    manager->addSerialDevice(QStringLiteral("/dev/ttymxc3"), 460800);

    return app->exec();
}
