/* Doodle Drawing Library
 *
 * Drawable and Primitive are base classes and have been implemented for you.
 * Do not modify them! 
 *
 * Stubs have been added to indicate where you need to complete the
 * implementation.
 * Please email me if you find any errors!
 */

/*
 * Root container for all drawable elements.
 */
function Doodle (context) {
    this.context = context;
    this.children = [];
}

Doodle.prototype.draw = function() {
 	// Your draw code here
    for (var i = 0; i < this.children.length; i++) {
        this.children[i].draw(this.context);
    }
};

/* Base class for all drawable objects.
 * Do not modify this class!
 */
function Drawable (attrs) {
    var dflt = { 
        left: 0,
        top: 0,
        visible: true,
        theta: 0,
        scale: 1
    };
    attrs = mergeWithDefault(attrs, dflt);
    this.left = attrs.left;
    this.top = attrs.top;
    this.visible = attrs.visible;
    this.theta = attrs.theta*Math.PI/180;
    this.scale = attrs.scale;
}

/*
 * Summary: returns the calculated width of this object
 */
Drawable.prototype.getWidth = function(context) {
  console.log("ERROR: Calling unimplemented draw method on drawable object.");
  return 0;
};

/*
 * Summary: returns the calculated height of this object
 */
Drawable.prototype.getHeight = function(context) {
  console.log("ERROR: Calling unimplemented draw method on drawable object.");
  return 0;
};

/*
 * Summary: Uses the passed in context object (passed in by a doodle object)
 * to draw itself.
 */
Drawable.prototype.draw = function(context) {
    console.log("ERROR: Calling unimplemented draw method on drawable object.");
};


/* Base class for objects that cannot contain child objects.
 * Do not modify this class!
 */
function Primitive(attrs) {
    var dflt = {
        lineWidth: 1,
        color: "black"
    };
    attrs = mergeWithDefault(attrs, dflt);
    Drawable.call(this, attrs);
    this.lineWidth = attrs.lineWidth;
    this.color = attrs.color;
}
Primitive.inheritsFrom(Drawable);

function Text(attrs) {
    var dflt = {
        content: "",
        fill: "black", //color
        font: "Helvetica", //font family
        size: 12, //Size in pt
        bold: false //bold boolean
    };
    attrs = mergeWithDefault(attrs, dflt);
    Drawable.call(this, attrs);

    //Rest of constructor code here
    this.content = attrs.content;
    this.fill = attrs.fill;
    this.font = attrs.font;
    this.size = attrs.size;
    this.bold = attrs.bold;
}
Text.inheritsFrom(Drawable);

//Text methods here
/**
 * Draw the text using the values defined in attrs.
 * @param context
 */
Text.prototype.draw = function (context) {
    if (this.bold) context.font = "bold " + this.getHeight(context) + "px " + this.font;
    else context.font = this.getHeight(context) + "px " + this.font;
    context.fillStyle = this.fill;
    context.scale(this.scale, this.scale);
    context.theta = this.theta;
    context.fillText(this.content, this.left, this.top);
};

/**
 * Return the width of the text
 * @param context
 * @return the width of the text
 */
Text.prototype.getWidth = function () {
    var text = MeasureText(this.content, this.bold, this.font, this.size);
    return text[0];
};

/**
 * Return the height of the text
 * @param context
 * @return the height of the text
 */
Text.prototype.getHeight = function () {
    var text = MeasureText(this.content, this.bold, this.font, this.size);
    return text[1];
};

function DoodleImage(attrs) {
    var dflt = {
        width: -1,
        height: -1,
        src: ""
    };
    attrs = mergeWithDefault(attrs, dflt);
    Drawable.call(this, attrs);
 
    //Rest of constructor code here
    this.width = attrs.width;
    this.height = attrs.height;
    this.src = attrs.src;

}
DoodleImage.inheritsFrom(Drawable);

//DoodleImage methods here

/**
 *  Draw the image using the specified source,
 *  with the specified width and height
 * @param context
 */
DoodleImage.prototype.draw = function (context) {
    var image = new Image();
    var width;
    var height;
    image.src = this.src;
    var x = this.left;
    var y = this.top;
    context.scale(this.scale, this.scale);
    context.theta = this.theta;
    var dooleImage = this;
    if(image.complete){
        width = dooleImage.getWidth(image);
        height = dooleImage.getHeight(image);
        context.drawImage(image, x, y, width, height);
    }else{
        image.onload=function () {
            width = dooleImage.getWidth(image);
            height = dooleImage.getHeight(image);
            context.drawImage(image, x, y, width, height);
        };
    }
};

/**
 * Return the width of the image
 * @param image
 * @return the width of the image
 */
DoodleImage.prototype.getWidth = function (image) {
    var width;
    if (this.width == -1){
        width = image.width;
        return width;
    }else {
        return this.width;
    }
};

/**
 * Return the height of the image
 * @param image
 * @return the height of the image
 */
DoodleImage.prototype.getHeight = function (image) {
    var height;
    if (this.height == -1){
        height = image.height;
        return height;
    }else {
        return this.height;
    }
};

function Line(attrs) {
    var dflt = {
        startX: 0,
        startY: 0,
        endX: 0,
        endY: 0
    };
    attrs = mergeWithDefault(attrs, dflt);
    Primitive.call(this, attrs);

    //Rest of constructor code here
    this.startX = attrs.startX;
    this.startY = attrs.startY;
    this.endX = attrs.endX;
    this.endY = attrs.endY;
}
Line.inheritsFrom(Primitive);

//Line methods here
/**
 * Draw the line.
 * @param context
 */
Line.prototype.draw = function (context) {
    context.beginPath();
    context.moveTo(this.startX,this.startY);
    context.lineTo(this.endX,this.endY);
    context.strokeStyle = this.color;
    context.lineWidth = this.lineWidth;
    context.scale(this.scale, this.scale);
    context.theta = this.theta;
    context.stroke();
};

/**
 * Return the width of the line's bounding box
 * @param context
 */
Line.prototype.getWidth = function () {
    return Math.abs(this.startX-this.endX);
};

/**
 * Return the height of the line's bounding box
 * @param context
 */
Line.prototype.getHeight = function () {
    return Math.abs(this.startY-this.endY);
};

function Rectangle(attrs) {
    var dflt = {
        x: 0,
        y: 0,
        width: 0,
        height: 0
    };
    attrs = mergeWithDefault(attrs, dflt);
    Primitive.call(this, attrs);
    //Rest of constructor code here
    this.x = attrs.x;
    this.y = attrs.y;
    this.width = attrs.width;
    this.height = attrs.height;
}
Rectangle.inheritsFrom(Primitive);

//Rectangle Methods here
/**
 *  Draw the rectangle as specified by x, y, width, and height.
 *  just the outline, not filled in.
 * @param context
 */
Rectangle.prototype.draw = function (context) {
    context.beginPath();
    context.strokeStyle = this.color;
    context.lineWidth = this.lineWidth;
    context.scale(this.scale, this.scale);
    context.theta = this.theta;
    context.strokeRect(this.left, this.top, this.getWidth(), this.getHeight());
};

/**
 * return the width of the rectangle
 */
Rectangle.prototype.getWidth = function () {
    return this.width;
};

/**
 * return the height of the rectangle
 */
Rectangle.prototype.getHeight = function () {
    return this.height;
};

function Container(attrs) {
    var dflt = {
        width: 100,
        height: 100,
        fill: false,
        borderColor: "black",
        borderWidth: 0
    };
    attrs = mergeWithDefault(attrs, dflt);
    Drawable.call(this, attrs);    
    //Rest of constructor code here
    this.children = [];
    this.width = attrs.width;
    this.height = attrs.height;
    this.fill = attrs.fill;
    this.borderColor = attrs.borderColor;
    this.borderWidth = attrs.borderWidth;
}
Container.inheritsFrom(Drawable);

//Rest of container methods here
/**
 *  Draws itself and its children.
 *  If a child is not visible (visible property set to false), does not draw it.
 *  Scales, translates, and rotates children according to each child's scale, (left, top), and theta values.
 * @param context
 */
Container.prototype.draw = function (context,parent) {
    //draw the container
    context.beginPath();

    context.fillStyle = this.fill;
    context.strokeStyle = this.borderColor;
    context.lineWidth = this.borderWidth;
    context.textBaseline = "top";
    context.scale(this.scale, this.scale);
    context.theta = this.theta;
    context.rect(this.left, this.top, this.getWidth(), this.getHeight());
    if (this.fill != false) context.fill();
    if (this.borderWidth > 0 ) context.stroke();


    context.save();

    context.clip();

    context.translate(this.left, this.top);

    this.layout();

    //draw the children
    for (var i = 0; i < this.children.length; i++) {
        this.children[i].draw(context);
    }

    context.restore();

};

/**
 * Performs layout on the children objects before it draws them
 * simple layout
 */
Container.prototype.layout = function () {};

Container.prototype.getWidth = function () {
    return this.width;
};

Container.prototype.getHeight = function () {
    return this.height;
};

function Pile(attrs) {
  Container.call(this, attrs);
}
Pile.inheritsFrom(Container);

//Rest of pile methods here
/**
 * Places all of its children at its own top-left corner.
 * @param context
 */
Pile.prototype.layout = function () {};

function Row(attrs) {
  Container.call(this, attrs);
}
Row.inheritsFrom(Container);

//Rest of row methods here
Row.prototype.layout = function () {
    for (var i=0; i < this.children.length; i++){
        if (i == 0) this.children[i].left = 0;
        else this.children[i].left = this.children[i-1].left + this.children[i-1].getWidth();
        this.children[i].top = this.height/2 - this.children[i].getHeight()/2;
    }
};

function Column(attrs) {
  Container.call(this, attrs);
}
Column.inheritsFrom(Container);

//Rest of column methods here
Column.prototype.layout = function () {
    for (var i=0; i < this.children.length; i++){
        if (i == 0) this.children[i].top = 0;
        else this.children[i].top = this.children[i-1].top + this.children[i-1].getHeight();
        this.children[i].left = this.width/2 - this.children[i].getWidth()/2;
    }
};

function Circle(attrs) {
  Container.call(this, attrs);      
  var dflt = {
    layoutCenterX: this.width / 2,
    layoutCenterY: this.height / 2,
    layoutRadius: Math.min(this.width, this.height) / 2 - 30
  };
  attrs = mergeWithDefault(attrs, dflt);
  this.layoutCenterX = attrs.layoutCenterX;
  this.layoutCenterY = attrs.layoutCenterY;
  this.layoutRadius = attrs.layoutRadius;
}
Circle.inheritsFrom(Container);

//Rest of circle methods here
Circle.prototype.draw = function (context) {
    //draw the container
    context.beginPath();

    context.fillStyle = this.fill;
    context.strokeStyle = this.borderColor;
    context.lineWidth = this.borderWidth;
    context.textBaseline = "top";
    context.scale(this.scale, this.scale);
    context.theta = this.theta;
    var center = {
        x:0,
        y:0
    };
    center.x = this.left + this.layoutCenterX;
    center.y = this.top + this.layoutCenterY;
    context.arc(center.x, center.y, this.layoutRadius, 0, Math.PI * 2);
    if (this.fill != false) context.fill();
    if (this.borderWidth > 0 ) context.stroke();

    context.save();

    context.translate(this.left, this.top);

    this.layout();

    //draw the children
    for (var i = 0; i < this.children.length; i++) {
        this.children[i].draw(context);
    }

    context.restore();
};

Circle.prototype.layout = function (context) {
    // notice: sin(angle)  angle must be radian
    var angle = 2 * Math.PI / this.children.length;
    var center = {
        x:0,
        y:0
    };
    for (var i = 0; i < this.children.length; i++) {
        center.y = this.layoutCenterY - Math.sin(angle * i) * this.layoutRadius;
        center.x = this.layoutCenterX + Math.cos(angle * i) * this.layoutRadius;
        this.children[i].left = center.x - this.children[i].getWidth()/2;
        this.children[i].top = center.y - this.children[i].getHeight()/2;
    }
};

function OvalClip(attrs) {
  Container.call(this, attrs);
}
OvalClip.inheritsFrom(Container);

//Rest of ovalClip methods here
OvalClip.prototype.draw = function(context) {
    //draw the container

    //其方法是用arc方法绘制圆，结合scale进行
    //横轴或纵轴方向缩放（均匀压缩）
    //这种方法绘制的椭圆的边离长轴端越近越粗，长轴端点的线宽是正常值
    //边离短轴越近、椭圆越扁越细，甚至产生间断，这是scale导致的结果
    //这种缺点某些时候是优点，比如在表现环的立体效果（行星光环）时
    //对于参数a或b为0的情况，这种方法不适用
    context.save();
    context.fillStyle = this.fill;
    context.strokeStyle = this.borderColor;
    context.lineWidth = this.borderWidth;
    context.textBaseline = "top";
    context.theta = this.theta;

    var a = this.getWidth()/2;
    var b = this.getHeight()/2;
    var x = this.left + a;
    var y = this.top + b;
    //选择a、b中的较大者作为arc方法的半径参数
    var r = (a > b) ? a : b;
    var ratioX = a / r; //横轴缩放比率
    var ratioY = b / r; //纵轴缩放比率
    context.scale(ratioX, ratioY); //进行缩放（均匀压缩）
    context.beginPath();

    //从椭圆的左端点开始逆时针绘制
    context.moveTo((x + a) / ratioX, y / ratioY);
    context.arc(x / ratioX, y / ratioY, r, 0, 2 * Math.PI);
    context.closePath();
    if (this.fill != false) context.fill();
    if (this.borderWidth > 0 ) context.stroke();

    context.restore();

    context.clip();

    context.translate(this.left, this.top);

    this.layout();

    //draw the children
    for (var i = 0; i < this.children.length; i++) {
        this.children[i].draw(context);
    }

    context.restore();
};

OvalClip.prototype.layout = function (context) {};

/**
 * Measurement function to measure canvas fonts
 *
 * @return: Array with two values: the first [0] is the width and the seconds [1] is the height 
 *          of the font to be measured. 
 **/
function MeasureText(text, bold, font, size)
{
    // This global variable is used to cache repeated calls with the same arguments
    var str = text + ':' + bold + ':' + font + ':' + size;
    if (typeof(__measuretext_cache__) == 'object' && __measuretext_cache__[str]) {
        return __measuretext_cache__[str];
    }

    var div = document.createElement('DIV');
        div.innerHTML = text;
        div.style.position = 'absolute';
        div.style.top = '-100px';
        div.style.left = '-100px';
        div.style.fontFamily = font;
        div.style.fontWeight = bold ? 'bold' : 'normal';
        div.style.fontSize = size + 'pt';
    document.body.appendChild(div);
    
    var size = [div.offsetWidth, div.offsetHeight];

    document.body.removeChild(div);
    
    // Add the sizes to the cache as adding DOM elements is costly and can cause slow downs
    if (typeof(__measuretext_cache__) != 'object') {
        __measuretext_cache__ = [];
    }
    __measuretext_cache__[str] = size;
    
    return size;
}