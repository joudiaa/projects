/*
 * File: SternBrocotSequences.js
 * -----------------------------
 * Exports a function that generates Stern-Brocot sequences for
 * arbitrary real numbers between 0 and 1.
 */

"use strict";

function TestSternBrocotSequences() {
   console.log("sbs(0.5) -> " + sbs(0.5));
   console.log("sbs(0.125) -> " + sbs(0.125));
   console.log("sbs(0.65) -> " + sbs(0.65));
   console.log("sbs(Math.E - 2) -> " + sbs(Math.E - 2));
   console.log("sbs(Math.PI - 3) -> " + sbs(Math.PI - 3));
   console.log("sbs(Math.PI - 3, 100) -> " + sbs(Math.PI - 3, 100));
   console.log("");
   console.log("Now use the console to test the function for arbitrary positive numbers.");
   evaluateExpressions();
}

/*
 * Function: sbs
 * -------------
 * Accepts the provided number and an optional max length and returns
 * the Stern-Brocot sequence best representing it.  We assume the supplied
 * number is between 0 and 1, and that max, if supplied, is a reasonably small
 * (in the hundreds).
 */
function helper(l, r){
   return [l[0] + r[0], l[1] + r[1]];
}

function val(c) {
   return c[0] / c[1];
}

function charNotInString(s, c) {
   return s.indexOf(c) == -1;
}

function updateStr(s, c) {
   if (s == "") return c;
   
   // index of start of last block
   let i = s.lastIndexOf(" ");
   if (i == -1) {
      i = 0;
   }
   let lastBox = s.substr(i).trim();
   if (charNotInString(lastBox, c)){
      s += (" " + c); 
   }
   else{
      let n = lastBox.length;
      let num = 1;
      if (n > 1) {
         // extract number
         num = parseInt(lastBox.substr(1));
      }
      num += 1;
      s = (s.substr(0, i)) + " " + (c + num);
   }

   return s;
}


const DEFAULT_MAX_LENGTH = 500;

function sbs(num, max) {
   // second argument is missing? use 500 as a default
   if (max === undefined) max = DEFAULT_MAX_LENGTH;

   // inits
   let s = "";
   let l = [0, 1];
   let r = [1, 1];
   let c = helper(l , r);
   let i = 0;

   // loop
   while (i < max) {
      // update pointers
      c = helper(l, r);
      let tmp = val(c);

      // main algo
      if (num == tmp) {
         break;
      }
      if(num < tmp){
         // right
         r = c;
         s = updateStr(s, "L");
      }
      if (num > tmp){
         // left
         l = c;
         s = updateStr(s, "R");
      }
      i += 1;
   }
   
   return s;
}
