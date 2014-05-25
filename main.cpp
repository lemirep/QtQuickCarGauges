#include <ViewManagement.h>
#include <QGuiApplication>
#include <QScopedPointer>
#include <QMatrix4x4>
#include <QDebug>
#include <QtSerialPort>
#include <QSerialPortInfo>
#include "SerialManager.h"
#include "SensorsManager.h"

int main(int ac, char **av)
{
    QScopedPointer<QGuiApplication> app(new QGuiApplication(ac, av));
    ViewManagement *view = ViewManagement::getInstance();
    OpenCarDashboard::Com::SerialManager *manager = new OpenCarDashboard::Com::SerialManager(app.data());
    OpenCarDashboard::Sensors::SensorsManager::sensorsManager()->setComInterface(manager);

    manager->addSerialDevice(QStringLiteral("/dev/ttymxc3"), 460800);

    view->setSource(QUrl("qrc:/qml/main.qml"));
    view->show();

    return app->exec();
}
