/*
 * File: Breakout.js
 * -----------------
 * This program implements the Breakout game.
 */
"use strict";

/* Constants */
const GWINDOW_WIDTH = 360;           /* Width of the graphics window      */
const GWINDOW_HEIGHT = 600;          /* Height of the graphics window     */
const N_ROWS = 10;                   /* Number of brick rows              */
const N_COLS = 10;                   /* Number of brick columns           */
const BRICK_ASPECT_RATIO = 4 / 1;    /* Width to height ratio of a brick  */
const BRICK_TO_BALL_RATIO = 3 / 2;   /* Ratio of brick width to ball size */
const BRICK_TO_PADDLE_RATIO = 2 / 3; /* Ratio of brick to paddle width    */
const BRICK_SEP = 2;                 /* Separation between bricks         */
const TOP_FRACTION = 0.1;            /* Fraction of window above bricks   */
const BOTTOM_FRACTION = 0.05;        /* Fraction of window below paddle   */
const N_BALLS = 3;                   /* Number of balls in a game         */
const TIME_STEP = 10;                /* Time step in milliseconds         */
const INITIAL_Y_VELOCITY = 3.0;      /* Starting y velocity downward      */
const MIN_X_VELOCITY = 1.0;          /* Minimum random x velocity         */
const MAX_X_VELOCITY = 3.0;          /* Maximum random x velocity         */

/* Derived constants */
const BRICK_WIDTH = (GWINDOW_WIDTH - (N_COLS + 1) * BRICK_SEP) / N_COLS;
const BRICK_HEIGHT = BRICK_WIDTH / BRICK_ASPECT_RATIO;
const PADDLE_WIDTH = BRICK_WIDTH / BRICK_TO_PADDLE_RATIO;
const PADDLE_HEIGHT = BRICK_HEIGHT / BRICK_TO_PADDLE_RATIO;
const PADDLE_Y = (1 - BOTTOM_FRACTION) * GWINDOW_HEIGHT - PADDLE_HEIGHT;
const BALL_SIZE = BRICK_WIDTH / BRICK_TO_BALL_RATIO;

/* Main program */

function Breakout() {
  // You fill this in along with any helper and callback functions.
  let x = 2;
  let y = 40;
  let gw = GWindow(GWINDOW_WIDTH, GWINDOW_HEIGHT);
  let bricks = GCompound();
  let i = 0;
  let firstBrick = GRect (x, y, BRICK_WIDTH, BRICK_HEIGHT);
  let secondBrick = GRect (x, y + (BRICK_HEIGHT + BRICK_SEP), BRICK_WIDTH, BRICK_HEIGHT);
  let brick3 = GRect (x, y + ((BRICK_HEIGHT) + BRICK_SEP)*2, BRICK_WIDTH, BRICK_HEIGHT);
  let brick4 = GRect (x, y + ((BRICK_HEIGHT + BRICK_SEP))*3, BRICK_WIDTH, BRICK_HEIGHT);
  let brick5 = GRect (x, y + ((BRICK_HEIGHT + BRICK_SEP))*4, BRICK_WIDTH, BRICK_HEIGHT);
  let brick6 = GRect (x, y + ((BRICK_HEIGHT + BRICK_SEP))*5, BRICK_WIDTH, BRICK_HEIGHT);
  let brick7 = GRect (x, y + ((BRICK_HEIGHT + BRICK_SEP))*6, BRICK_WIDTH, BRICK_HEIGHT);
  let brick8 = GRect (x, y + ((BRICK_HEIGHT + BRICK_SEP))*7, BRICK_WIDTH, BRICK_HEIGHT);
  let brick9 = GRect (x, y + ((BRICK_HEIGHT + BRICK_SEP))*8, BRICK_WIDTH, BRICK_HEIGHT);
  let brick10 = GRect (x, y + ((BRICK_HEIGHT + BRICK_SEP))*9, BRICK_WIDTH, BRICK_HEIGHT);
  firstBrick.getColor(true);
  firstBrick.setColor("white");
  firstBrick.setFilled(true);
  firstBrick.setFillColor("Red");

  secondBrick.getColor(true);
  secondBrick.setColor("white");
  secondBrick.setFilled(true);
  secondBrick.setFillColor("Red");

  brick3.getColor(true);
  brick3.setColor("white");
  brick3.setFilled(true);
  brick3.setFillColor("Orange");

  brick4.getColor(true);
  brick4.setColor("white");
  brick4.setFilled(true);
  brick4.setFillColor("Orange");

  brick5.getColor(true);
  brick5.setColor("white");
  brick5.setFilled(true);
  brick5.setFillColor("Green");

  brick6.getColor(true);
  brick6.setColor("white");
  brick6.setFilled(true);
  brick6.setFillColor("Green");

  brick7.getColor(true);
  brick7.setColor("white");
  brick7.setFilled(true);
  brick7.setFillColor("Cyan");

  brick8.getColor(true);
  brick8.setColor("white");
  brick8.setFilled(true);
  brick8.setFillColor("Cyan");

  brick9.getColor(true);
  brick9.setColor("white");
  brick9.setFilled(true);
  brick9.setFillColor("Blue");

  brick10.getColor(true);
  brick10.setColor("white");
  brick10.setFilled(true);
  brick10.setFillColor("Blue");

  gw.add(firstBrick);
  gw.add(secondBrick);
  gw.add(brick3);
  gw.add(brick4);
  gw.add(brick5);
  gw.add(brick6);
  gw.add(brick7);
  gw.add(brick8);
  gw.add(brick9);
  gw.add(brick10);

  for (i = 0; i < N_ROWS; i++){
    x += (BRICK_WIDTH + BRICK_SEP);

    let br = GRect(x, y,BRICK_WIDTH, BRICK_HEIGHT);
    let br2 = GRect(x, (y + (BRICK_HEIGHT + BRICK_SEP)),BRICK_WIDTH, BRICK_HEIGHT);
    let br3 = GRect (x, y + ((BRICK_HEIGHT) + BRICK_SEP)*2, BRICK_WIDTH, BRICK_HEIGHT);
    let br4 = GRect (x, y + ((BRICK_HEIGHT + BRICK_SEP))*3, BRICK_WIDTH, BRICK_HEIGHT);
    let br5 = GRect (x, y + ((BRICK_HEIGHT + BRICK_SEP))*4, BRICK_WIDTH, BRICK_HEIGHT);
    let br6 = GRect (x, y + ((BRICK_HEIGHT + BRICK_SEP))*5, BRICK_WIDTH, BRICK_HEIGHT);
    let br7 = GRect (x, y + ((BRICK_HEIGHT + BRICK_SEP))*6, BRICK_WIDTH, BRICK_HEIGHT);
    let br8 = GRect (x, y + ((BRICK_HEIGHT + BRICK_SEP))*7, BRICK_WIDTH, BRICK_HEIGHT);
    let br9 = GRect (x, y + ((BRICK_HEIGHT + BRICK_SEP))*8, BRICK_WIDTH, BRICK_HEIGHT);
    let br10 = GRect (x, y + ((BRICK_HEIGHT + BRICK_SEP))*9, BRICK_WIDTH, BRICK_HEIGHT);

    br.getColor(true);
    br.setColor("white");
    br.setFilled(true);
    br.setFillColor("Red");

    br2.getColor(true);
    br2.setColor("white");
    br2.setFilled(true);
    br2.setFillColor("Red");

    br3.getColor(true);
    br3.setColor("white");
    br3.setFilled(true);
    br3.setFillColor("Orange");

    br4.getColor(true);
    br4.setColor("white");
    br4.setFilled(true);
    br4.setFillColor("Orange");

    br5.getColor(true);
    br5.setColor("white");
    br5.setFilled(true);
    br5.setFillColor("Green");

    br6.getColor(true);
    br6.setColor("white");
    br6.setFilled(true);
    br6.setFillColor("Green");

    br7.getColor(true);
    br7.setColor("white");
    br7.setFilled(true);
    br7.setFillColor("Cyan");

    br8.getColor(true);
    br8.setColor("white");
    br8.setFilled(true);
    br8.setFillColor("Cyan");

    br9.getColor(true);
    br9.setColor("white");
    br9.setFilled(true);
    br9.setFillColor("Blue");

    br10.getColor(true);
    br10.setColor("white");
    br10.setFilled(true);
    br10.setFillColor("Blue");

    gw.add(br);
    gw.add(br2);
    gw.add(br3);
    gw.add(br4);
    gw.add(br5);
    gw.add(br6);
    gw.add(br7);
    gw.add(br8);
    gw.add(br9);
    gw.add(br10);
 
  }

  // gw.add(bricks);

  let x_pad = (GWINDOW_WIDTH/2) - PADDLE_WIDTH;
  let y_pad = (TOP_FRACTION * GWINDOW_HEIGHT) * (9.5);
  let paddle = GRect(x_pad, y_pad, PADDLE_WIDTH, PADDLE_HEIGHT); // initial paddle position
  paddle.setFillColor(true);
  paddle.setFilled("Black");
  // gw.add(paddle);

  let mousemove = function(e) {
    if (e.getX() > 0 && e.getX() <= (GWINDOW_WIDTH - PADDLE_WIDTH)){
      paddle.setLocation(e.getX(), y_pad, PADDLE_WIDTH, PADDLE_HEIGHT);
      gw.add(paddle);
    }
  };

  let vx = randomReal(MIN_X_VELOCITY, MAX_X_VELOCITY);
  if (randomChance()) vx = -vx;
  let vy = INITIAL_Y_VELOCITY;
  let bx = (GWINDOW_WIDTH/2) - BALL_SIZE;
  let by = (GWINDOW_HEIGHT/2) - BALL_SIZE;

  let ball = GOval(bx, by, BALL_SIZE, BALL_SIZE);
  ball.setFillColor(true);
  ball.setFilled("Black");
  gw.add(ball);
  let stepCounter = 0;
  let N_STEPS = 100;

  function moveBall (){
    let xx = bx + vx;
    let yy = by + vy;
    if ( xx < 0 || xx > GWINDOW_WIDTH){
      vx = -vx;
    }
    if (yy < 0){
      vy = -vy;
    }
    bx += vx;
    by += vy;

    if (yy > GWINDOW_HEIGHT){
      window.location.reload();

    }

  }

  let clickAction = function(e){
    let step = function() {
      ball.setLocation(bx, by);
      CollideResponse();
      moveBall();
      stepCounter++;
   };
   if (stepCounter === N_STEPS) clearInterval(timer);
   let timer = setInterval(step, TIME_STEP);

   

  };


  function getCollidingObject(){
    let CollidingObject;
    CollidingObject = gw.getElementAt(bx, by);
    if (CollidingObject !== null){
      return CollidingObject;
    }

    CollidingObject = gw.getElementAt(bx + BALL_SIZE, by);
    if (CollidingObject !== null){
      return CollidingObject;
    }
    CollidingObject = gw.getElementAt(bx, by + BALL_SIZE);
    if (CollidingObject !== null){
      return CollidingObject;

    }
    CollidingObject = gw.getElementAt(bx + BALL_SIZE, by + BALL_SIZE);
    if (CollidingObject !== null){
      return CollidingObject;

    }
    else {
      return null;
    }
  }

  function CollideResponse(){
    let collider = getCollidingObject();
    if (collider === paddle){
      vx = -vx;
      vy = -vy;
    }
    else if (collider !== null){
      gw.remove(collider);
    }
  }

  gw.addEventListener("click", clickAction);

  gw.addEventListener("mousemove", mousemove);

  return mousemove, clickAction, getCollidingObject, CollideResponse;

}
