#include <ViewManagement.h>
#include <QGuiApplication>
#include <QScopedPointer>

int main(int ac, char **av)
{
    QScopedPointer<QGuiApplication> app(new QGuiApplication(ac, av));
    ViewManagement *view = ViewManagement::getInstance();

    view->setSource(QUrl("qrc:/qml/main.qml"));
    view->show();

    return app->exec();
}
