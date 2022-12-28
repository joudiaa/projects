/*
 * File: SamplerQuilt.js
 * ---------------------
 * This program uses the object-oriented graphics model to draw
 * a Sampler Quilt to the screen. :)
 */

"use strict";

/* Constants */
const PATCH_DIMENSION = 75;
const NUM_ROWS = 7;
const NUM_COLUMNS = 7;
const BORDER_COLOR = "Black";
const BULLSEYE_BOLD_COLOR = "Red";
const BULLSEYE_MILD_COLOR = "White";
const LOG_COLOR = "Tan";
const LOVE_FRAME_COLOR = "Pink";
const LOVE_MAT_COLOR = "White";

/* Derived Constants */
const WINDOW_WIDTH = NUM_COLUMNS * PATCH_DIMENSION;
const WINDOW_HEIGHT = NUM_ROWS * PATCH_DIMENSION;

/*
 * Function: DrawSamplerQuilt
 * --------------------------
 * Draws a sampler quilt as outlined in the assignment handout.
 */

function DrawSamplerQuilt() {
   let gw = GWindow(WINDOW_WIDTH, WINDOW_HEIGHT);
   drawQuilt(gw);
}

/*
 * Function: drawQuilt
 * --------------------------
 * Inserts all of the sampler quilt into the supplied graphics window.
 */
function drawQuilt(gw) {
   for (let row = 0; row < NUM_ROWS; row++) {
      for (let col = 0; col < NUM_COLUMNS; col++) {
         let patch = createPlaceholderPatch();
         gw.add(patch, col * PATCH_DIMENSION, row * PATCH_DIMENSION);

         let bull = bullseye();
         let fr = frame();
         let rose = flower();
         let love = loveLead();

         let pat = [ bull, fr, rose, love];
         let i = pat.length;
         let x = col * PATCH_DIMENSION;
         let y = row * PATCH_DIMENSION;

         if (((col + row )% 4 == 2)){
            gw.add(rose, (col) * PATCH_DIMENSION, (row) * PATCH_DIMENSION);
         }
         if ((col + row) % 4 == 0){
            gw.add(bull, x, y);
         }
         if (((col + row) % 4 == 3)){
            gw.add(love, (col * PATCH_DIMENSION) + (PATCH_DIMENSION/2), ((row) * PATCH_DIMENSION + (PATCH_DIMENSION/2)));

         }
         if ((col + row)% 4 == 1) {
            gw.add(fr, x + (PATCH_DIMENSION/2), (y) + (PATCH_DIMENSION/2));

         }

      }

      
   }
}

/**
 * Function: createPlaceholderPatch
 * --------------------------------
 * This function is only here to draw a simple rectangle of the correct
 * size to occupy the space where a more elaborate patch belongs.  You will
 * want to remove it after you've implemented everything.
 */
function createPlaceholderPatch() {   
   return GRect(PATCH_DIMENSION,PATCH_DIMENSION);
}

function bullseye(){
   let MAX_OVALS = 8;
   let r = (PATCH_DIMENSION/2); //initial radius
   let x = 0; //initial x
   let y = 0; // initial y


   let circ = GCompound();
   let i = 1;
   let d = PATCH_DIMENSION;
  
   for (i = 1; i < MAX_OVALS; i++){
      x += (r/8);
      y += (r/8);
      d -= r/4;
      let oval = GOval(x, y ,d, d);
      oval.setFilled(true);

      // change color
      if (i % 2 == 0){
         oval.setFillColor(BULLSEYE_MILD_COLOR);
      }
      else{
         oval.setFillColor(BULLSEYE_BOLD_COLOR);
      }

      circ.add(oval);
   }

   return circ;

}

function flower(){
   let coo = (PATCH_DIMENSION/2)/8;
   let diameter = 2*(PATCH_DIMENSION/5);
   let flo = GCompound();
   let flower1 = GOval(coo, coo, diameter, diameter);
   let flower2 = GOval(coo + (PATCH_DIMENSION/2), coo, diameter, diameter);
   let flower3 = GOval(coo, - (coo - (PATCH_DIMENSION/2)) + 8 , diameter, diameter);
   let flower4 = GOval(coo + (PATCH_DIMENSION/2), - (coo - (PATCH_DIMENSION/2)) + 8, diameter, diameter);
   let flower5 = GOval(coo + (PATCH_DIMENSION/2)/2, coo + (PATCH_DIMENSION/2)/2 , diameter, diameter);

   flower1.setFilled(true);
   flower2.setFilled(true);
   flower3.setFilled(true);
   flower4.setFilled(true);
   flower5.setFilled(true);
   flower1.setFillColor(randomColor());
   flower2.setFillColor(randomColor());
   flower3.setFillColor(randomColor());
   flower4.setFillColor(randomColor());
   flower5.setFillColor(randomColor());

   flo.add(flower1);
   flo.add(flower2);
   flo.add(flower3);
   flo.add(flower4);
   flo.add(flower5);

   return flo;

}

function createFrame(w,h){
   let FRA = GCompound();
   let meh = (w + h)/2;
   let rect1 = GRect(-meh, -meh, w, h);
   let rect2 = GRect(meh -h, -meh, h, w);
   let rect3 = GRect(-meh, h - meh, h, w);
   let rect4 = GRect(h - meh,meh - h , w, h);

   rect1.setFilled(true);
   rect1.setFillColor(LOG_COLOR);
   rect2.setFilled(true);
   rect2.setFillColor(LOG_COLOR);
   rect3.setFilled(true);
   rect3.setFillColor(LOG_COLOR);
   rect4.setFilled(true);
   rect4.setFillColor(LOG_COLOR);

   FRA.add(rect1);
   FRA.add(rect2);
   FRA.add(rect3);
   FRA.add(rect4);

   return FRA;
}

function frame(){
   let big_frame = GCompound();
   let h = PATCH_DIMENSION/9;
   let w = PATCH_DIMENSION - h;
   //let j = PATCH_DIMENSION 
   let i = 0;

   for (i = 0; i < 4; i++){
      let f1 = createFrame(w,h);
      big_frame.add(f1);
      w -= (2 * h);
   }


   return big_frame;
}

function loveSect(w,h){


   return LoveFrame;
}


function loveLead(){
   let myFrame = GCompound();
   let h = PATCH_DIMENSION/9;
   let w = PATCH_DIMENSION - h;
   let wh = (w + h)/2;
   let wh2 = ((w-(2*h))+h)/2
   let name = ["http://web.stanford.edu/class/cs106ax/img/jonathan.png", "http://web.stanford.edu/class/cs106ax/img/sophie.png", "http://web.stanford.edu/class/cs106ax/img/stephan.png", "http://web.stanford.edu/class/cs106ax/img/avi.png", "http://web.stanford.edu/class/cs106ax/img/ryan.png"];
   let i = name.length;

   Array.prototype.random = function lead() {
      return name[Math.floor((Math.random()*i))];
    }

   let leader = name.random(i);

   // let leader = 'http://web.stanford.edu/class/cs106ax/img/jonathan.png';

   let image = GImage(leader, wh - (h*9), wh - (h*9));

   myFrame.add(image);

   let rect11 = GRect(-wh, -wh, w, h);
   let rect22 = GRect(wh -h, -wh, h, w);
   let rect33 = GRect(-wh, h - wh, h, w);
   let rect44 = GRect(h - wh,wh - h , w, h);

   rect11.setFilled(true);
   rect22.setFilled(true);
   rect33.setFilled(true);
   rect44.setFilled(true);
   rect11.setFillColor(LOVE_FRAME_COLOR);
   rect22.setFillColor(LOVE_FRAME_COLOR);
   rect33.setFillColor(LOVE_FRAME_COLOR);
   rect44.setFillColor(LOVE_FRAME_COLOR);

   myFrame.add(rect11);
   myFrame.add(rect22);
   myFrame.add(rect33);
   myFrame.add(rect44);

   let rect111 = GRect(-wh2, -wh2, (w - (2*h)), h);
   let rect222 = GRect((wh2 -h), -wh2, h, (w - (2*h)));
   let rect333 = GRect((-wh2), (h - wh2), h, (w - (2*h)));
   let rect444 = GRect((h - wh2), (wh2 - h ), (w - (2*h)), h);

   rect111.setFilled(true);
   rect222.setFilled(true);
   rect333.setFilled(true);
   rect444.setFilled(true);
   rect111.setFillColor(LOVE_MAT_COLOR);
   rect222.setFillColor(LOVE_MAT_COLOR);
   rect333.setFillColor(LOVE_MAT_COLOR);
   rect444.setFillColor(LOVE_MAT_COLOR);

   myFrame.add(rect111);
   myFrame.add(rect222);
   myFrame.add(rect333);
   myFrame.add(rect444);


   return myFrame;

}