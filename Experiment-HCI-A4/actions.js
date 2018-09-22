// General actions for the actor's statemachine's. To be implimented

var Actions = (function () {
	return {
		/**
		 * Causes the character to change its image to the parameterized bitmap. If
		 * the parameter is null, no image should be displayed.
		 * @param {Object} params
		 *   img: Image to change the actor
		 */
		changeImg: function (event, params, actor) {
			if (params && params.img) actor.img = params.img;
			else actor.img = null;
			//redraw actors
			actor.parent.damageActor(actor);
		},
		/**
		 * Moves the character to exact x,y coordinates (no bounds checking)
		 * @param {Object} params
		 *   targetAbsoluteX: the x coordinate for the character to move to
		 *   targetAbsoluteY: the y coordinate for the character to move to
		 */
		moveTo: function (event, params, actor) {
			actor.x = params.targetAbsoluteX;
			actor.y = params.targetAbsoluteY;
			//redraw actors
			actor.parent.damageActor(actor);
		},
		/**
		 * Moves the character by the increment specified by x and y, relative to
		 * its current position (no bounds checking)
		 * @param {Object} params
		 *   targetOffsetX: the x offset for the character to move
		 *   targetOffsetY: the y offset for the character to move
		 */
		moveInc: function (event, params, actor) {
			actor.x += params.targetOffsetX;
			actor.y += params.targetOffsetY;
			//redraw actors
			actor.parent.damageActor(actor);
		},
		/**
		 * Move the character to the x, y coordinates of the corresponding event
		 */
		followEventPosition: function (event, params, actor) {
			if (actor == actor.parent.dragFocus){
				actor.x = event.offsetX + actor.parent.grabPointX;
				actor.y = event.offsetY + actor.parent.grabPointY;
			}
			else {
				actor.x = event.offsetX;
				actor.y = event.offsetY;
			}
			//redraw actors
			actor.parent.damageActor(actor);
		},
		/**
		 *  Cause the character to begin the specified animation
		 *  @params {Object} params
		 *    movingActor: Actor obj that should animate
		 *    targetActor: Actor obj that should animate
		 *    endMessage - String that specifies the message to deliver when the
		 *     character reaches its destination
		 *    passOverMessage – String that specifies the message to deliver if the
		 *     character passes over another character
		 *    duration – integer that specifies the duration for the animation to take
		 */
		runAnim: function (event, params, actor) {
			actor.parent.newAnimation(params.movingActor, params.targetActor,
				params.endMessage, params.passOverMessage, params.duration);
		},
		/**
		 * Cause the character to be the focus of a drag event
		 */
		getDragFocus: function (event, params, actor) {
			var distanceX = actor.x - event.offsetX;
			var distanceY = actor.y - event.offsetY;
			actor.parent.requestDragFocus(actor, distanceX, distanceY);
		},
		/**
		 * Cause the character to release focus of the drag event
		 */
		dropDragFocus: function (event, params, actor) {
			actor.parent.releaseDragFocus();
		},
		/**
		 * Send the specified message to the specified target character
		 * @params {Object} params
		 *    message: Message to send
		 *    actor: Actor to send the message to
		 */
		sendMessage: function (event, params, actor) {
			actor.parent.sendMessage(params.actor, params.message);
		},
		/**
		 * Write a debug message to the debug log with the tag “ssui”
		 *  @params {Object} params
		 *    message: Message to log in the console
		 */
		debugMessage: function (event, params, actor) {
			console.log("ssui: %s", params.message);
		},

		/**
		 * New added function for part 2.
		 * Send the specified message to the actors under the moving actor's area
		 * @param {Object} params
		 *    message: Message to send
		 */
		sendMessageToAreaActors: function (event, params, actor){
			var actors = actor.parent.actorsUnder(actor.x,actor.y,actor.width,actor.height);
			for (var i=0; i<actors.length; i++){
				actor.parent.sendMessage(actors[i], params.message);
			}
		}
	};
})();
 
 
