/**
 * File: match-the-flag.js
 * -----------------------
 * Defines the controller for the MatchTheFlag application.
 */
"use strict";

const WIN_IMG = "images/win.png"
const RESTART = "images/restart.png"


function BootstrapMatchTheFlag() {

   // var location = window.location.pathname;
   // var directoryPath = location.substring(0, location.lastIndexOf("/")+1);
   let click = [];
   let done = [];

   let clickAction = function(e){
      // console.log("click");
      console.log(done);
      if (e.target.getAttribute("src") === COVER_IMAGE){
         if( click.length < 2){
            e.target.setAttribute("src", e.target.getAttribute("data-country-image"));
            click.push(e.target);
            // console.log(click);
            if (click.length === 2){
               setTimeout(compare, DELAY);   
               console.log(click);     
            }
         }
      }
      // restart game button
      if (e.target.getAttribute("src") === RESTART){
         console.log("restart");
         location.reload();
      }
   };
   let body = document.getElementById("board");
   function compare(){
      console.log("compare");
      if (click[0].getAttribute("data-country-image") === click[1].getAttribute("data-country-image")){
         click[0].setAttribute("src", MATCHED_IMAGE);
         click[1].setAttribute("src", MATCHED_IMAGE);
         done.push(click[0]);
         done.push(click[1]);
         console.log(done);
         if (done.length === 16){
            // when you win/game ends you get a "you win" statement and a restart button
            const winNode = document.createElement("img");
            const startNode = document.createElement("img");
            winNode.setAttribute("src", WIN_IMG);
            div.appendChild(winNode);
            startNode.setAttribute("src", RESTART);
            div.appendChild(startNode);
            console.log("done");
            startNode.addEventListener("click", clickAction);

         }
      }
      else {
         click[0].setAttribute("src", COVER_IMAGE);
         click[1].setAttribute("src", COVER_IMAGE);
      }
      click = [];
   }
      
   let div = document.getElementById("board")

   function flags(lst){
      // for loop to add a string to the directory then add it to the list
      let flags = []
      let len = lst.length
      let direct_start = "images/"
      let direct_end = ".png"
      for (let i = 0; i < len; i++){
         let comb = direct_start + lst[i] + direct_end
         flags.push(comb)
         flags.push(comb)
      }
      shuffle(flags)
      for (let j = 0; j < flags.length; j++){
         const imgNode = document.createElement("img");
         imgNode.setAttribute("data-country-image", flags[j]);
         imgNode.setAttribute("src", COVER_IMAGE);
         div.appendChild(imgNode);
         imgNode.addEventListener("click", clickAction);
      }
   }

   /*
    * Function: shuffle
    * -----------------
    * Generically shuffles the supplied array so
    * that any single permutation of the elements
    * is equally likely.
    */
   function shuffle(array) {
      for (let lh = 0; lh < array.length; lh++) {
         let rh = lh + Math.floor(Math.random() * (array.length - lh));
         let temp = array[rh];
         array[rh] = array[lh];
         array[lh] = temp;
      }    
      console.log(array)
   }
   return flags(COUNTRIES)
}

/* Execute the above function when the DOM tree is fully loaded. */
document.addEventListener("DOMContentLoaded", BootstrapMatchTheFlag);
