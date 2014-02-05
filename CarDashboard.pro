PROJECT = CarDashboard

SOURCES += main.cpp

INCLUDEPATH += $$PWD

include(./QtQuickViewManager/View.pri)

RESOURCES += qml_resources.qrc

OTHER_FILES += \
    qml/main.qml \
    qml/RoundGauge.qml \
    qml/GraphGauge.qml \
    qml/needle.png
