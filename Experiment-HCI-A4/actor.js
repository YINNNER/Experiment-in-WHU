/**
 * @constructor
 * @param {props} An object containing properties for the actor
 */
function Actor(props) {
	this.parent = null; //Set in the game.addActor method
	this.height = props.height;
	this.width = props.width;
	this.x = props.x;
	this.y = props.y;
	this.img = props.img;
}

/**
 * Sets the FSM for the particular actor.
 * @param {Object} FSM object as detailed in the instructions
 */
Actor.prototype.setFSM = function (startState, fsm) {
	this.states = fsm;
	this.currentState = fsm[startState];
};

/**
 * Receives an event from dispatch and transitions the FSM appropriately
 * @param {Event} The event object received, which includes certain information
 *  depending on the event type
 * @return {boolean} True if the event was consumed by the actor, false if it
 *  was not consumed
 */
Actor.prototype.deliverEvent = function (event) {
	var state = this.currentState;
	for (theEvent in state) {
		if (theEvent == event.type) {
			if ((state[theEvent].predicate == undefined) ||
				(state[theEvent].predicate(event, this))) {
				this.makeTransition(event, state[theEvent]);
				return true;
			}
		}
	}
	return false;
};

/**
 * Transitions the FMS for a particular transition and event
 * @param {Event} event object received, which includes certain information
 *  depending on the event type
 */
Actor.prototype.makeTransition = function (event, transition) {
	var actions = transition.actions;
	for (action in actions) {
		var params = actions[action].params;
		actions[action].func(event, params, this);
	}
	this.currentState = this.states[transition.endState];
};

/**
 * Draws the actor on the canvas based on its parameters
 * @param {Context} The HTML5 canvas context object to be drawn on.
 */
Actor.prototype.draw = function (context) {
	if (this.img) {
		context.drawImage(this.img, this.x, this.y, this.width, this.height);
	}
};
