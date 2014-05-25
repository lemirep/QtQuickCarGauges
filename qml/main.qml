import QtQuick 2.1
import QtQuick.Window 2.1
import OpenCarDashboard 1.0

Window
{
    id : mainScreen
    width: Screen.width * 0.5
    height: Screen.height * 0.5


    Rectangle
    {
        id : main_cadran
        anchors.fill: parent
        color : "black"
        Component.onCompleted: forceActiveFocus();

        property real randVal : 0;

        FpsItem {}

        Keys.onSpacePressed:
        {
            randVal = Math.random();
        }

        RoundGauge
        {
            anchors
            {
                left : parent.left
                right : parent.horizontalCenter
                top : parent.top
                bottom : parent.verticalCenter
            }
            outerCirclingColor: "#cc6600"
            textFont.family : "Helvetica"
            textFont.bold : true
            textFont.italic : true
            digitalFont.family : "Helvetica"
            digitalFont.bold : true
            digitalFont.italic : true

            textFont.pointSize : 12

            unit: "km/h"
            unitFont.pointSize: 12
            unitFont.bold: true
            unitFont.italic: true
            unitFont.family: "Helvetica"
            fullCircle: true
            subDivs: 33
            minValue: oil_temp_sensor.minValue
            maxValue: oil_temp_sensor.maxValue
            lowValues: 30
            highValues: 220
            currentValue: oil_temp_sensor.value
            digitalFont.pointSize: 15
        }

        //        RoundGauge
        //        {
        //            anchors
        //            {
        //              right : parent.right
        //              left : parent.horizontalCenter
        //              top : parent.top
        //              bottom : parent.verticalCenter
        //            }
        //            outerCirclingColor: "#cc6600"
        //            textFont.family : "Helvetica"
        //            textFont.bold : true
        //            textFont.italic : true
        //            digitalFont.family : "Helvetica"
        //            digitalFont.bold : true
        //            digitalFont.italic : true

        //            textFont.pointSize : 12

        //            unit: "km/h"
        //            unitFont.pointSize: 12
        //            unitFont.bold: true
        //            unitFont.italic: true
        //            unitFont.family: "Helvetica"
        //            fullCircle: true
        //            subDivs: 33
        //            minValue: oil_temp_sensor.minValue
        //            maxValue: oil_temp_sensor.maxValue
        //            lowValues: 30
        //            highValues: 220
        //            currentValue: oil_temp_sensor.value
        //            digitalFont.pointSize: 15
        //        }

        //            RoundGauge
        //            {
        //                id : tacho_gauge
        //                anchors
        //                {
        //                    right : parent.right
        //                    left : parent.horizontalCenter
        //                    top : parent.top
        //                    bottom : parent.verticalCenter
        //                }
        //                outerCirclingColor: "#ff2200"
        //                textFont.pointSize : 35
        //                textFont.family : "Helvetica"
        //                textFont.bold : true
        //                textFont.italic : true
        //                unit: "RPM x1000"
        //                unitFont.pointSize: 12
        //                unitFont.bold: true
        //                unitFont.italic: true
        //                unitFont.family: "Helvetica"
        //                digitalFont.family : "Helvetica"
        //                digitalFont.bold : true
        //                digitalFont.italic : true
        //                digitalFont.pointSize: 20
        //                currentValue: parent.randVal * Math.random() * (maxValue - minValue) + minValue;
        //                subDivs: 6
        //                minValue: 0
        //                maxValue: 7
        //                lowValues: 1
        //                highValues: 5
        //            }

        //        Item
        //        {
        //            id : dashboard
        //            width : parent.width * 0.5
        //            property int gaugeWidth : width * 0.25;
        //            property int gaugeHeight : height * 0.5

        //            anchors
        //            {
        //                horizontalCenter : parent.horizontalCenter
        //                top : parent.verticalCenter
        //                bottom : parent.bottom
        //            }

        //            RoundGauge
        //            {
        //                id : water_temp
        //                anchors
        //                {
        //                    left : parent.left
        //                    top : parent.top
        //                }
        //                indicatorWidth: 5
        //                width : dashboard.gaugeWidth
        //                height : dashboard.gaugeHeight
        //                unit : "Water C"
        //                minValue: water_temp_sensor.minValue
        //                maxValue: water_temp_sensor.maxValue
        //                subDivs: 1
        //                lowValues: 10
        //                highValues: 50
        //                unitFont.pointSize: 10
        //                textFont.pointSize : 6
        //                digitalFont.pointSize: 10
        //                currentValue: water_temp_sensor.value

        //                AnalogValueSensor
        //                {
        //                    id : water_temp_sensor
        //                    sensor: "temp"
        //                    analogBitsPrecision: 12
        //                    onValueChanged: console.log("Value " + value);
        //                    minValue : -40
        //                    maxValue: 125
        //                    refreshRate: 1000
        //                }
        //            }
        //            RoundGauge
        //            {
        //                id : oil_temp
        //                anchors
        //                {
        //                    horizontalCenter : parent.horizontalCenter
        //                    top : parent.top
        //                }
        //                indicatorWidth: 5
        //                unit : "Oil C"
        //                width : dashboard.gaugeWidth
        //                height : dashboard.gaugeHeight
        //                minValue: oil_temp_sensor.minValue
        //                maxValue: oil_temp_sensor.maxValue
        //                subDivs: 1
        //                lowValues: 50
        //                highValues: 150
        //                textFont.pointSize : 6
        //                unitFont.pointSize: 10
        //                digitalFont.pointSize: 10
        //                currentValue: oil_temp_sensor.value

                        AnalogValueSensor {
                            id : oil_temp_sensor
                            sensor: "pot"
                            analogBitsPrecision: 12
                            onValueChanged: console.log("Value " + value);
                            refreshRate: 125
                            minValue : -20
                            maxValue: 250
                        }
        //            }

        //            RoundedGauge
        //            {
        //                sensor:
        //                anchors
        //                {
        //                    horizontalCenter : parent.horizontalCenter
        //                    top : parent.top
        //                }
        //                width : dashboard.gaugeWidth
        //                height : dashboard.gaugeHeight
        //            }

        //                RoundGauge
        //                {
        //                    id : fuel_level
        //                    width : dashboard.gaugeWidth
        //                    height : dashboard.gaugeHeight
        //                    anchors
        //                    {
        //                        right : parent.right
        //                        top : parent.top
        //                    }
        //                    indicatorWidth: 5
        //                    unit : "Fuel"
        //                    minValue: 0
        //                    maxValue: 60
        //                    lowValuesColor: "#cc0000"
        //                    subDivs: 3
        //                    lowValues: 10
        //                    highValues: maxValue
        //                    unitFont.pointSize: 10
        //                    textFont.pointSize : 6
        //                    digitalFont.pointSize: 10
        //                    currentValue: main_cadran.randVal * Math.random() * (maxValue - minValue) + minValue;
        //                }
        //            GraphGauge
        //            {
        //                id : graph_gauge
        //                width : dashboard.gaugeWidth
        //                height : dashboard.gaugeHeight
        //                minValue: 0
        //                maxValue: 60
        //                subDivs: 4
        //                anchors
        //                {
        //                    left : fuel_level.right
        //                    top : parent.top
        //                }
        ////                currentValue: main_cadran.randVal *  (maxValue - minValue) + minValue;
        //                currentValue: 30
        //            }

        //                RoundGauge
        //                {
        //                    id : oil_pressure
        //                    width : dashboard.gaugeWidth
        //                    height : dashboard.gaugeHeight
        //                    anchors
        //                    {
        //                        left : water_temp.horizontalCenter
        //                        bottom : parent.bottom
        //                    }
        //                    indicatorWidth: 5
        //                    unit : "Oil PSI"
        //                    minValue: 0
        //                    maxValue: 10
        //                    lowValuesColor: "#cc0000"
        //                    subDivs: 9
        //                    lowValues: 2
        //                    highValues: 8
        //                    unitFont.pointSize: 10
        //                    textFont.pointSize : 6
        //                    digitalFont.pointSize: 10
        //                    currentValue: main_cadran.randVal  * Math.random() *  (maxValue - minValue) + minValue;
        //                }
        //                RoundGauge
        //                {
        //                    id : fuel_pressure
        //                    width : dashboard.gaugeWidth
        //                    height : dashboard.gaugeHeight
        //                    anchors
        //                    {
        //                        right : fuel_level.horizontalCenter
        //                        bottom : parent.bottom
        //                    }
        //                    indicatorWidth: 5
        //                    unit : "Fuel PSI"
        //                    minValue: 0
        //                    maxValue: 10
        //                    lowValuesColor: "#cc0000"
        //                    subDivs: 9
        //                    lowValues: 2
        //                    highValues: 8
        //                    unitFont.pointSize: 10
        //                    textFont.pointSize : 6
        //                    digitalFont.pointSize: 10
        //                    currentValue: main_cadran.randVal * Math.random() *  (maxValue - minValue) + minValue;
        //                }
        //    }
    }
}
