import QtQuick 2.1
import QtQuick.Window 2.1

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
            //            outerCirclingColor: "#cc6600"
            textFont.family : "Helvetica"
            textFont.bold : true
            textFont.italic : true
            digitalFont.family : "Helvetica"
            digitalFont.bold : true
            digitalFont.italic : true

            //            textFont.pointSize : 12

            unit: "km/h"
            unitFont.pointSize: 12
            unitFont.bold: true
            unitFont.italic: true
            unitFont.family: "Helvetica"
            fullCircle: true
            subDivs: 33
            minValue: 0
            maxValue: 340
            lowValues: 30
            highValues: 220
            currentValue: parent.randVal *  (maxValue - minValue) + minValue;
            digitalFont.pointSize: 15
        }
        RoundGauge
        {
            id : tacho_gauge
            anchors
            {
                right : parent.right
                left : parent.horizontalCenter
                top : parent.top
                bottom : parent.verticalCenter
            }
            outerCirclingColor: "#ff2200"
            textFont.pointSize : 35
            textFont.family : "Helvetica"
            textFont.bold : true
            textFont.italic : true
            unit: "RPM x1000"
            unitFont.pointSize: 12
            unitFont.bold: true
            unitFont.italic: true
            unitFont.family: "Helvetica"
            digitalFont.family : "Helvetica"
            digitalFont.bold : true
            digitalFont.italic : true
            digitalFont.pointSize: 20
            currentValue: parent.randVal * (maxValue - minValue) + minValue;
            subDivs: 6
            minValue: 0
            maxValue: 7
            lowValues: 1
            highValues: 5
        }

        Item
        {
            id : dashboard
            width : parent.width * 0.5
            property int gaugeWidth : width * 0.25;
            property int gaugeHeight : height * 0.5

            anchors
            {
                horizontalCenter : parent.horizontalCenter
                top : parent.verticalCenter
                bottom : parent.bottom
            }

            RoundGauge
            {
                id : water_temp
                anchors
                {
                    left : parent.left
                    top : parent.top
                }
                indicatorWidth: 5
                width : dashboard.gaugeWidth
                height : dashboard.gaugeHeight
                unit : "Water C"
                minValue: -20
                maxValue: 200
                subDivs: 1
                lowValues: 30
                highValues: 150
                unitFont.pointSize: 10
                textFont.pointSize : 6
                digitalFont.pointSize: 10
                currentValue: main_cadran.randVal *  (maxValue - minValue) + minValue;

            }
            RoundGauge
            {
                id : oil_temp
                anchors
                {
                    horizontalCenter : parent.horizontalCenter
                    top : parent.top
                }
                indicatorWidth: 5
                unit : "Oil C"
                width : dashboard.gaugeWidth
                height : dashboard.gaugeHeight
                minValue: 0
                maxValue: 250
                subDivs: 1
                lowValues: 50
                highValues: 150
                textFont.pointSize : 6
                unitFont.pointSize: 10
                digitalFont.pointSize: 10
                currentValue: main_cadran.randVal *  (maxValue - minValue) + minValue;
            }
            RoundGauge
            {
                id : fuel_level
                width : dashboard.gaugeWidth
                height : dashboard.gaugeHeight
                anchors
                {
                    right : parent.right
                    top : parent.top
                }
                indicatorWidth: 5
                unit : "Fuel"
                minValue: 0
                maxValue: 60
                lowValuesColor: "#cc0000"
                subDivs: 3
                lowValues: 10
                highValues: maxValue
                unitFont.pointSize: 10
                textFont.pointSize : 6
                digitalFont.pointSize: 10
                currentValue: main_cadran.randVal *  (maxValue - minValue) + minValue;
            }
            GraphGauge
            {
                id : graph_gauge
                width : dashboard.gaugeWidth
                height : dashboard.gaugeHeight
                minValue: 0
                maxValue: 60
                subDivs: 4
                anchors
                {
                    left : fuel_level.right
                    top : parent.top
                }
//                currentValue: main_cadran.randVal *  (maxValue - minValue) + minValue;
                currentValue: 30
            }

            RoundGauge
            {
                id : oil_pressure
                width : dashboard.gaugeWidth
                height : dashboard.gaugeHeight
                anchors
                {
                    left : water_temp.horizontalCenter
                    bottom : parent.bottom
                }
                indicatorWidth: 5
                unit : "Oil PSI"
                minValue: 0
                maxValue: 10
                lowValuesColor: "#cc0000"
                subDivs: 9
                lowValues: 2
                highValues: 8
                unitFont.pointSize: 10
                textFont.pointSize : 6
                digitalFont.pointSize: 10
                currentValue: main_cadran.randVal *  (maxValue - minValue) + minValue;
            }
            RoundGauge
            {
                id : fuel_pressure
                width : dashboard.gaugeWidth
                height : dashboard.gaugeHeight
                anchors
                {
                    right : fuel_level.horizontalCenter
                    bottom : parent.bottom
                }
                indicatorWidth: 5
                unit : "Fuel PSI"
                minValue: 0
                maxValue: 10
                lowValuesColor: "#cc0000"
                subDivs: 9
                lowValues: 2
                highValues: 8
                unitFont.pointSize: 10
                textFont.pointSize : 6
                digitalFont.pointSize: 10
                currentValue: main_cadran.randVal *  (maxValue - minValue) + minValue;
            }
        }
    }
}
