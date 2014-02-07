import QtQuick 2.2

Canvas
{
    id : gauge_canvas
    contextType: "2d"
    antialiasing: true;

    property real currentValue : 0;
    property real minValue : 0
    property real maxValue : 0;
    property real lowValues : 0;
    property real highValues : 0;
    property int subDivs : 0
    property font textFont : {family : "Helvetica";}

    property color outerCirclingColor : "#0099FF";
    property color innerCirclingColor : "white";
    property color lowValuesColor : "#0066FF";
    property color highValuesColor : "#cc0000";

    QtObject
    {
        id : d
    }

    onPaint:
    {
        context.beginPath();

        context.strokeStyle = outerCirclingColor;
        context.lineWidth = 5;
        context.strokeRect(10, 10, width - 20, height - 20);

        context.strokeStyle = innerCirclingColor;
        context.lineWidth = 2;
        context.strokeRect(16, 16, width - 32, height - 32);

        var fillGradiant = context.createLinearGradient(0,0, 0,height);
        fillGradiant.addColorStop(1, lowValuesColor);
        fillGradiant.addColorStop(0, highValuesColor);

        context.strokeStyle = fillGradiant;
//        context.fillRect(18,18, width - 36, height - 36);
        context.lineWidth = 1;
        context.moveTo(25, height - 18);
        context.lineTo(25, 18);
        context.stroke();

        context.moveTo(35, height - 18);
        context.lineTo(35, 50);
        context.stroke();
    }
}
