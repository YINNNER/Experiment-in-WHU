window.onload = function () {
    var canvas = document.getElementById("myCanvas");

    var context = canvas.getContext("2d");

    var root = new Doodle(context);

    var circleContainer = new Container({
        width: 860,
        height: 860,
        left: 20,
        top: 20,
        borderColor: "purple",
        borderWidth: 0
    });

    var halfCircle1 = new Circle({
        width: 800,
        height: 800,
        left: 30,
        top: 30,
        borderColor: "#C64C54",
        borderWidth: 40,
        layoutRadius: 400
    });

    var halfCircle2 = new Circle({
        width: 700,
        height: 700,
        left: 80,
        top: 80,
        borderColor: "#FABF50",
        borderWidth: 40,
        layoutRadius: 350
    });

    var halfCircle3 = new Circle({
        width: 600,
        height: 600,
        left: 130,
        top: 130,
        borderColor: "#3fabcb",
        borderWidth: 40,
        layoutRadius: 300
    });

    var halfCircle4 = new Circle({
        width: 500,
        height: 500,
        left: 180,
        top: 180,
        borderColor: "#994D7E",
        borderWidth: 40,
        layoutRadius: 250
    });

    var halfCircle5 = new Circle({
        width: 400,
        height: 400,
        left: 230,
        top: 230,
        borderColor: "#F79781",
        borderWidth: 40,
        layoutRadius: 200
    });
    circleContainer.children = [
        halfCircle1,
        halfCircle2,
        halfCircle4,
        halfCircle3,
        halfCircle5
    ];

    var oval = new OvalClip({
        width: 300,
        height: 250,
        left: 300,
        top: 295,
        borderWidth: 0
    });

    var image = new DoodleImage({
        width: 375,
        height: 250,
        src: "cat.jpg",
        top: 0,
        left: -70
    });

     oval.children.push(image);

    var letterContainer = new Row({
        width: 750,
        height: 200,
        left: 75,
        top: 580,
        borderColor: "purple",
        borderWidth: 0
    });
    var letterYContainer = new Container({
        width: 150,
        height: 200,
        borderColor: "purple",
        borderWidth: 0
    });
    var letterIContainer = new Container({
        width: 150,
        height: 200,
        borderColor: "purple",
        borderWidth: 0
    });
    var letterNContainer = new Container({
        width: 150,
        height: 200,
        borderColor: "purple",
        borderWidth: 0
    });
    var letterEContainer = new Container({
        width: 150,
        height: 200,
        borderColor: "purple",
        borderWidth: 0
    });
    var letterRContainer = new Container({
        width: 150,
        height: 200,
        borderColor: "purple",
        borderWidth: 0
    });

    letterContainer.children = [
        letterYContainer,
        letterIContainer,
        letterNContainer,
        letterEContainer,
        letterRContainer
    ];

    var text1 = new Text({
        height: 40,
        top:20,
        left: 20,
        font: "Helvetica",
        size: 16,
        fill: "#C64C54",
        content: "Hello, everyone!"
    });
    var text2 = new Text({
        height: 40,
        top:20,
        left: 700,
        font: "Helvetica",
        size: 16,
        fill: "#3fabcb",
        content: "I'm yiner!"
    });

    var containerCut = new Container({
        width: 860,
        height: 430,
        left: 20,
        top: 450,
        fill: "white",
        borderWidth: 0
    });

    containerCut.children = [text1,text2];

    var letterY1 = new Line({
        startX: 0,
        startY: 0,
        endX: 75,
        endY: 100,
        color: "#C64C54",
        lineWidth: 20
    });
    var letterY2 = new Line({
        startX: 150,
        startY: 0,
        endX: 75,
        endY: 100,
        color: "#C64C54",
        lineWidth: 20
    });
    var letterY3 = new Line({
        startX: 75,
        startY: 100,
        endX: 75,
        endY: 200,
        color: "#C64C54",
        lineWidth: 20
    });
    letterYContainer.children = [letterY1,letterY2,letterY3];

    var letterI1 = new Line({
        startX: 20,
        startY: 0,
        endX: 130,
        endY: 0,
        color: "#FABF50",
        lineWidth: 20
    });
    var letterI2 = new Line({
        startX: 75,
        startY: 0,
        endX: 75,
        endY: 200,
        color: "#FABF50",
        lineWidth: 20
    });
    var letterI3 = new Line({
        startX: 20,
        startY: 200,
        endX: 130,
        endY: 200,
        color: "#FABF50",
        lineWidth: 20
    });
    letterIContainer.children = [letterI1,letterI2,letterI3];

    var letterN1 = new Line({
        startX: 0,
        startY: 0,
        endX: 0,
        endY: 200,
        color: "#3fabcb",
        lineWidth: 20
    });
    var letterN2 = new Line({
        startX: 0,
        startY: 0,
        endX: 150,
        endY: 200,
        color: "#3fabcb",
        lineWidth: 20
    });
    var letterN3 = new Line({
        startX: 150,
        startY: 0,
        endX: 150,
        endY: 200,
        color: "#3fabcb",
        lineWidth: 20
    });
    letterNContainer.children = [letterN1,letterN2,letterN3];


    var letterE1 = new Line({
        startX: 30,
        startY: 0,
        endX: 130,
        endY: 0,
        color: "#994D7E",
        lineWidth: 20
    });
    var letterE2 = new Line({
        startX: 30,
        startY: 100,
        endX: 120,
        endY: 100,
        color: "#994D7E",
        lineWidth: 20
    });
    var letterE3 = new Line({
        startX: 30,
        startY: 200,
        endX: 130,
        endY: 200,
        color: "#994D7E",
        lineWidth: 20
    });
    var letterE4 = new Line({
        startX: 30,
        startY: 0,
        endX: 30,
        endY: 200,
        color: "#994D7E",
        lineWidth: 20
    });
    letterEContainer.children = [letterE1,letterE2,letterE3,letterE4];

    var letterR1 = new Line({
        startX: 20,
        startY: 0,
        endX: 20,
        endY: 200,
        color: "#F79781",
        lineWidth: 20
    });
    var letterR2 = new Line({
        startX: 20,
        startY: 100,
        endX: 120,
        endY: 200,
        color: "#F79781",
        lineWidth: 20
    });
    var letterR3 = new Line({
        startX: 20,
        startY: 0,
        endX: 120,
        endY: 0,
        color: "#F79781",
        lineWidth: 20
    });
    var letterR4 = new Line({
        startX: 120,
        startY: 0,
        endX: 120,
        endY: 100,
        color: "#F79781",
        lineWidth: 20
    });
    var letterR5 = new Line({
        startX: 20,
        startY: 90,
        endX: 120,
        endY: 90,
        color: "#F79781",
        lineWidth: 20
    });
    letterRContainer.children = [letterR1,letterR2,letterR3,letterR4,letterR5];


    root.children = [circleContainer,containerCut,letterContainer,oval];
    root.draw();

};