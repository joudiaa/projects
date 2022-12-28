/*
 * File: Hailstone.js
 * ------------------
 * This program displays the Hailstone sequence for a number.
 */
"use strict";

let n = 29;

function TestHailstone() {
	let seq = n + " "


   while(n != 1)
   {
      console.log(n);
       if(n % 2 == 0)
       {
         n = n / 2;
         console.log("this is even, so I half it: " + n)
       }    
      else{    
         n = ((n * 3) + 1);
         console.log ("this is odd so I add 3n+1: " + n)

      }
      // console.log(n);
   }

   return seq + n;

}

/*
 * Function: hailstone
 * -------------------
 * Accepts the supplied number and prints the sequence of numbers that lead the original
 * number down to 1 (along with information about how the intermediate numbers were computed).
 */
// function hailstone(n) {
// 	console.log(n + "this is even, so I half it" ? "this is odd, so I add 3n+1") ;
//    evaluateExpressions();

// }
