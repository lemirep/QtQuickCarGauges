import QtQuick 2.2

Canvas
{
    id : gauge_canvas
    contextType: "2d"
    antialiasing: true;

    property real currentValue : 0;
    property real minValue : 0
    property real maxValue : 0;

    property real tmpMaxValue : minValue

    property real lowValues : 0;
    property real highValues : 0;
    property int subDivs : 0
    property font textFont : {family : "Helvetica";}
    property color textColor : "white";

    property color outerCirclingColor : "#0099FF";
    property color innerCirclingColor : "white";
    property color lowValuesColor : "#0066FF";
    property color highValuesColor : "#cc0000";

    property alias updateInterval : update_timer.interval


    QtObject
    {
        id : d
        property var values : new Array();
        property real range : maxValue - minValue;
    }

    onPaint:
    {
        console.log("Drawing");
        drawCadran();
        drawGraph();
        drawGraduations();
    }

    Timer
    {
        id : update_timer
        repeat: true
        running : true
        interval : 500
        onTriggered:
        {
            d.values.push(currentValue);
            while (d.values.length > width - 22)
                d.values.shift();
            requestPaint();
        }
    }

    function drawCadran()
    {
        context.reset();
        context.beginPath();

        context.strokeStyle = outerCirclingColor;
        context.lineWidth = 1;
        context.strokeRect(10, 10, width - 20, height - 20);
    }

    function drawGraph()
    {
        // Calculate currentGraph MaxValue
        for (var i = 0; i < d.values.length; i++)
            if (d.values[i] > tmpMaxValue)
                tmpMaxValue = d.values[i];

        console.log("currentValue " + currentValue)

        context.lineWidth = 1;
        context.strokeStyle = outerCirclingColor;

        for (i = 0; i < d.values.length; i++)
        {
            context.beginPath();
            var heightPos = (height - 24) * (1 - ((d.values[i] - minValue) / d.range));
            console.log(heightPos);
            context.moveTo(i + 12, heightPos);
            context.lineTo(i + 12, heightPos - 1);
            context.stroke();
        }

        context.beginPath();
        context.strokeStyle = "red";
        i = d.values.length - 1;
        heightPos = (height - 24) * (1 - ((d.values[i] - minValue) / d.range));
        context.moveTo(i + 12, heightPos);
        context.lineTo(i + 12, heightPos - 1);
        context.stroke();

    }

    function drawGraduations()
    {
        if (subDivs === 0)
            return ;
        text_model.clear();
        var inStep = height / subDivs;
        var inGrad = d.range / subDivs;
        for (var i = 0; i <= subDivs; i++)
        {
            context.beginPath()
            context.moveTo(10, i * inStep);
            context.lineTo(width, i * inStep);
            context.stroke();
            text_model.append({"text" : maxValue - (i * inGrad),
                                  "x" : 10,
                                  "y" : i * inStep});
        }
    }

    Repeater
    {
        anchors.fill: parent
        model :  ListModel {id : text_model}
        delegate : Component {
            Text
            {
                color : textColor
                font : textFont
                x : model.x
                y : model.y
                text : model.text
                style : Text.Sunken
                styleColor: outerCirclingColor
            }
        }
    }
}
