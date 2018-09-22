// Provides the state machine descriptions and creates a new game

//First, load in all of our images
var loadCounter = 0;
var totalImg = 0;

var sky = new Image();
totalImg++;
sky.onload = function() {
	loadCounter++;
};
sky.src = 'sky.jpg';

var star = new Image();
totalImg++;
star.onload = function() {
  loadCounter++;
};
star.src = 'star.png';

var explosion = new Image();
totalImg++;
explosion.onload = function() {
	loadCounter++;
};
explosion.src = 'explosion.png';

var bear = new Image();
totalImg++;
bear.onload = function() {
  loadCounter++;
};
bear.src = 'bear.png';

var stone = new Image();
totalImg++;
stone.onload = function() {
	loadCounter++;
};
stone.src = 'stone.png';

// function for randomly generating position
// Returns a random integer between min (included) and max (included)
// Using Math.round() will give you a non-uniform distribution!
function getRandomIntInclusive(min, max) {
  min = Math.ceil(min);
  max = Math.floor(max);
  return Math.floor(Math.random() * (max - min + 1)) + min;
}

// Score multiplier, so you get bonuses for multiple hits
var multiplier = 1;

//Create our actors and their FSMs
var player = new Actor({
  height: 110,
  width: 110,
  x: 345,
  y: 390,
  img: bear
});
player.setFSM('focused', {
	'focused': {
		"dragmove": {
			actions: [
								{ func: function (event, params, actor) {
										var mousePoint = new Actor({
											height: 1,
											width: 1,
											x: event.offsetX,
											y: event.offsetY});
										actor.parent.newAnimation(actor,mousePoint,"hit","boom",150);
										actor.parent.damageActor(actor);
									}
								}],
			endState: "focused"
		},
		"animstart": {
			actions: [],
			endState: "focused"
		},
		"animmove": {
			actions: [{ func: Actions.followEventPosition }],
			endState: "focused"
		},
		"animend": {
			actions: [{ func: Actions.followEventPosition }],
			endState: "focused"
		}
	}
});

targetFSM = {
	'ready': {
		'message': {
			predicate: function(event, actor){
				return event.message == "boom" },
			actions: [{ func: Actions.changeImg,
				params: { img: explosion }},
				{ func: function(event, params, actor){
						var score_ele = document.getElementById("score");
						var score = parseInt(score_ele.innerHTML) + (100 * multiplier);
						score_ele.innerHTML = "" + score;}
				},
				{ func: function(event, params, actor){
						multiplier += 1;
						setTimeout(function(){
							multiplier -= 1;
						}, 1000);
						setTimeout(function(){
							actor.parent.directDispatch({type: 'tick'}, actor);
						}, 300);
					}}],
			endState: 'exploded'
		}
	},
	'exploded': {
		'tick': {
			actions: [{ func: Actions.changeImg,
				params: { img: star }},
				{ func: function(event, params, actor){
						var coords =  { targetAbsoluteX: getRandomIntInclusive(0,750),
							targetAbsoluteY: getRandomIntInclusive(0,350) };
						Actions.moveTo(event, coords, actor);
					}
				}],
			endState: 'ready'
		}
	}
};
var target =[];
for (var i=0; i<15; i++){
	target[i] = new Actor({
		height: 30,
		width: 30,
		x: getRandomIntInclusive(0,750),
		y: getRandomIntInclusive(0,350),
		img: star
	});

	target[i].setFSM('ready', targetFSM);
}

stoneFSM = {
	'ready': {
		'message': {
			predicate: function(event, actor){
				return event.message == "boom" },
			actions: [{ func: Actions.changeImg,
				params: { img: explosion }},
				{ func: function(event, params, actor){
						var score_ele = document.getElementById("score");
						var score = parseInt(score_ele.innerHTML) - (1000 * multiplier);
						score_ele.innerHTML = "" + score;}
				},
				{ func: function(event, params, actor){
						multiplier += 1;
						setTimeout(function(){
							multiplier -= 1;
						}, 1000);
						setTimeout(function(){
							actor.parent.directDispatch({type: 'tick'}, actor);
						}, 300);
					}}],
			endState: 'exploded'
		}
	},
	'exploded': {
		'tick': {
			actions: [{ func: Actions.changeImg,
				params: { img: stone }},
				{ func: function(event, params, actor){
						var coords =  { targetAbsoluteX: getRandomIntInclusive(0,750),
							targetAbsoluteY: getRandomIntInclusive(0,350) };
						Actions.moveTo(event, coords, actor);
					}
				}],
			endState: 'ready'
		}
	}
};
var stones =[];
for (var i=0; i<5; i++){
	stones[i] = new Actor({
		height: 50,
		width: 50,
		x: getRandomIntInclusive(0,750),
		y: getRandomIntInclusive(0,350),
		img: stone
	});

	stones[i].setFSM('ready', stoneFSM);
}


// counting time
var c = 30;
var timeID;
function timedCount()
{
	if (c == 0) {
		var score = document.getElementById('score').innerHTML;
		alert("Time's out, You got " + score + "!");
		location.reload();
	}
	document.getElementById('time').innerHTML = "" + c;
	c = c-1;
	timeID = setTimeout("timedCount()",1000);
}

function stopCount()
{
	clearTimeout(timeID);
}

//When the DOM has loaded, actually setup our game
window.onload = function() { 
  var game = new Game(document.getElementById("game"));

  // preview
	game.background = sky;
	game.onDraw();
	game.context.fillStyle = 'white';
	game.context.font = 'bold 20pt Arial';
	var x = game.width / 2 - 240;
	var y = game.height / 2;
	game.context.fillText('Press the play button to begin the game!', x, y);

  document.getElementById("play").addEventListener("click", function(event) {
	  //add actors
  	for (var i=0; i<15; i++){
		  game.addActor(target[i]);
	  }
	  for (var i=0; i<5; i++){
		  game.addActor(stones[i]);
	  }
	  game.addActor(player);

	  //dispatch event
    event = _.clone(event);
    event.type = "buttonpress";
    game.dispatchToAll(event);

	  //Wait for all of the imaages to load in before we start the game
	  var runGame = function() {
		  if (loadCounter >= totalImg){
			  stopCount();
			  game.run();
			  timedCount();
		  }
		  else
			  setTimeout(function() { runGame() }, 200);
	  };
	  runGame();
  });

};



