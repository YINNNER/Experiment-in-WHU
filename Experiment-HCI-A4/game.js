/**
 * @constructor
 * @param {props} An object containing properties for the actor
 */
function Game(canvas) {
  //Setup our fields
  this.context = canvas.getContext("2d");
  this.dragFocus = null;
  this.width = canvas.width;
  this.height = canvas.height;
  this.grabPointX = 0;
  this.grabPointY = 0;
  this.actors = [];

	this.canvas = canvas;
	this.background = null;

  var self = this;
  // Listen for events here and dispatch them
	canvas.addEventListener("mousedown", function(event) {
		event = _.clone(event);
		event.type = "mousedown";
		self.dispatchToAll(event);
	});
	canvas.addEventListener("mouseup", function(event) {
		event = _.clone(event);
		event.type = "dragend";
		self.dispatchToAll(event);
	});
	canvas.addEventListener("mousemove", function(event) {
		event = _.clone(event);
		event.type = "dragmove";
		self.dispatchToAll(event);
	});
}


/**
 * Adds a new actor to the game. Each actor must be an independent object 
 * (new * object). Make sure to properly clone actors if adding multiple 
 * of the same type.
 * @param {Actor} actor to add to the game.
 */
Game.prototype.addActor = function(actor) {
  this.actors.push(actor);
  actor.parent = this;
};

/**
 * Find and return the list of actors whose bounds overlap the given
 * rectangular area.  The actors (if any) in the list should be in reverse
 * drawing order. That is, the actors drawn later should appear earlier in the
 * list.
 * @param {Integer} left position of the rectangle 
 * @param {Integer} top position of the rectangle
 * @param {Integer} width of the rectangle
 * @param {Integer} height of the rectangle
 * @return {Array} A list of actors in reverse drawning order that are under 
 */
Game.prototype.actorsUnder = function(left, top, width, height) {
	var actorList	= [];
	var rect1 = {
			left: left,
			top: top,
			right: left+width,
			bottom: top+height
	};
  for (var i=this.actors.length-1; i >= 0 ; i--){
		  var rect2 = {
				  left: this.actors[i].x,
				  top: this.actors[i].y,
				  right: this.actors[i].x + this.actors[i].width,
				  bottom: this.actors[i].y + this.actors[i].height
		  };
		  if (!(rect1.left>=rect2.right||rect1.top>=rect2.bottom||
						  rect2.left>=rect1.right||rect2.top>=rect1.bottom)) actorList.push(this.actors[i]);
  }
  return actorList;
};

/**
 * Dispatch the given event to one actor under the given x,y position. When
 * multiple actors are under the position we offer it to them in reverse
 * drawing order. As soon as a actor takes the event (returns true from its
 * deliverEvent() method) we stop offering it to others so that only one actor
 * gets the event.
 * @param {Event} Javascript event object (from an event handler)
 * @return {boolean} True if the event was consumed, false if it was not
 */
Game.prototype.pointDispatch = function(event) {
	var actorList = this.actorsUnder(event.x,event.y,1,1);
	for (var i = 0; i < actorList.length; i++){
		if (actorList[i].deliverEvent(event)) return true;
	}
	return false;
};

/**
 * Dispatch the given event to one actor whose bounds overlap the given
 * rectangle. When multiple actors are overlapped we offer it to them in
 * reverse drawing order. As soon as a actor takes the event (returns true from
 * its deliverEvent() method) we stop offering it to others so that only one
 * actor gets the event.
 * @param {Object} Javascript object with the following properties
 *  - top: top coordinate of the bounding box
 *  - left: left coordinate of the bounding box
 *  - width: Width of the bounding box
 *  - height: height of the bounding box
 * @param {Event} Javascript event object (from an event handler)
 * @return {boolean} True if the event was consumed, false if it was not
 */
Game.prototype.areaDispatch = function(area, event) {
	var actorList = this.actorsUnder(area.left, area.top, area.width, area.height);
	for (var i = 0; i < actorList.length; i++){
		if (actorList[i].deliverEvent(event)) return true;
	}
	return false;
};

/**
 ￼* Dispatch the given event directly to the given actor
 * @param {Event} Javascript event object (from an event handler)
 * @param {Actor} Actor to dispatch the event to
 * @return {boolean} True if the event was consumed, false if it was not
 */
Game.prototype.directDispatch = function(event, actor) {
	return actor.deliverEvent(event);
};

/**
 * Dispatch the given event to all actors in reverse drawing order. This
 * dispatch does not stop after the first actor accepts the event, but instead
 * always continues through the list of all actors
 * @param {Event} Javascript event object (from an event handler)
 * @return {boolean} True if the event was consumed by any of the actors
 */
Game.prototype.dispatchToAll = function(event) {
	var isConsumed = false;
	for (var i = 0; i < this.actors.length; i++){
		if (this.actors[i].deliverEvent(event)) isConsumed = true;
	}
	return isConsumed;
};

/**
 * Attempt to dispatch the given event to all actors in reverse drawing order
 * stopping as soon as some actor takes the event (returns true from its
 * deliverEvent() method).
 * @param {Event} Javascript event object (from an event handler)
 * @return {boolean} True if the event was consumed by one of the actors, false
 *  if it was not
 */
Game.prototype.dispatchTryAll = function(event) {
	for (var i = 0; i < this.actors.length; i++){
		if (this.actors[i].deliverEvent(event)) return true;
	}
	return false;
};

/**
 * Dispatch the given event to the current drag focus object (if any). If there
 * is no current drag focus or the current drag focus object rejects the event
 * (returns false from its deliverEvent() method), this method returns false.
 * All events which contain an x,y position will have their x,y position
 * adjusted by (-grabPointX, -grabPointY) prior to being delivered.  In this
 * way the position indicated in the event will reflect where the top-left
 * corner of the dragged actor should be placed, rather than where the cursor
 * was (which will normally be inside the actor; specifically at a distance of
 * (grabPointX, grabPointY) from the top-left of the object).
 * @param {Event} Javascript event object (from an event handler)
 * @return {boolean} True if the event was consumed, false if it was not
 */
Game.prototype.dispatchDragFocus = function(event) {
	return (this.dragFocus!=null && this.dragFocus.deliverEvent(event));
};

/**
 * This method is responsible for drawing all of the actors
 */
Game.prototype.onDraw = function() {
	// clear all of the canvas before redraw
	this.context.clearRect(0, 0, this.canvas.width, this.canvas.height);

	// draw background
	if (this.background != null){
		this.context.drawImage(this.background, 0, 0, this.width, this.height);
	}

	//draw actors
  for (var i = 0; i < this.actors.length; i++){
		  this.actors[i].draw(this.context);
  }
};

/**
 * Provided methods below this line
 */

/**
 * Switch the current drag focus to the given actor.  The offset values
 * given indicate where inside the given actor the cursor was when the
 * drag was started.  This offset will be applied (negatively) to all 
 * drag events later delivered.  This will allow each of those events to 
 * reflect where the top-left corner of the dragged actor should be 
 * placed, rather than where the cursor currently is.
 * 
 * @param {Actor} actor that is to be the new drag focus.
 * @param {Integer} x distance from the left of the actor that the cursor
 *              was when the drag was started.
 * @param {Integer} y distance from the top of the actor that the cursor
 *              was when the drag was started.
 */
Game.prototype.requestDragFocus = function(actor, x, y) {
  this.dragFocus = actor;
  this.grabPointX = x;
  this.grabPointY = y;
};

/**
 * Clear the current drag focus.
 */
Game.prototype.releaseDragFocus = function() {
  this.dragFocus = null; 
};

/**
 * Creates a new animation to run
 * @param {Actor} movingActor - actor that will be moving
 * @param {Actor} targetActer - target the movingActor will be going to
 * @param {String} endMessage that will be send to targetActor after the
 *  animation completes
 * @param {String} passoverMessage that will be sent to any interactors the
 * movingActor animates over
 * @param {Integer} duration in ms for the animation
 */
Game.prototype.newAnimation = function(movingActor, targetActor, endMessage, passoverMessage, duration) {
  var self = this;
  var start = Date.now();
  var target_x = targetActor.x + (targetActor.width / 2) - (movingActor.width / 2);
  var target_y = targetActor.y + (targetActor.height / 2) - (movingActor.height / 2);
  var x_inc = (target_x - movingActor.x) / duration;
  var y_inc = (target_y - movingActor.y) / duration;
  var x_init = movingActor.x;
  var y_init = movingActor.y;
  self.directDispatch({type: "animstart"}, movingActor);
  var animation = function (timestamp) {
    var curTime = Date.now() - start_time;
    var x = x_init + curTime * x_inc;
    var y = y_init + curTime * y_inc;
    self.directDispatch({type: "animmove", offsetX: x, offsetY: y}, movingActor);
    if (passoverMessage) {
      self.areaDispatch({
        top: y,
        left: x, 
        width: movingActor.width,
        height: movingActor.height
      }, {type: "message", message: passoverMessage});
    }
    if (curTime < duration) {
      window.setTimeout(animation,1);
    } else {
      self.directDispatch({type: "animend", offsetX: x, offsetY: y}, movingActor);
      self.sendMessage(targetActor, endMessage);
    }
  };
  var start_time = Date.now();
  window.setTimeout(animation, 1);
};

/**
 * Starts the game!
 */
Game.prototype.run = function() {
  //Send the init message to all of our actors
  this.dispatchToAll({type: "message", message: "$INIT$"});
  this.onDraw(); 
};

/**
 * Reports damage on a particular actors. Uses a fairly dumb redraw strategy,
 * however a smarter one could be implimented for bells and whistles
 * @param {Actor} an actor that has been damaged through state change
 */
Game.prototype.damageActor = function(actor) {
  this.onDraw(); 
};

/**
 * Sends a message to a particular actor
 * @param {Actor} actor to send the message to
 * @param {String} Message to send
 */ 
Game.prototype.sendMessage = function(actor, message) {
  this.directDispatch({type: "message", message: message}, actor)
};
