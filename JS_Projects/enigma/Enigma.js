/*
 * File: Enigma.js
 * ---------------
 * This program implements a graphical simulation of the Enigma machine.
 */

"use strict";

/* Main program */

// message,wirepairs, configurations, spindle1Offset,spindle2Offset, spindle3Offset, rotatePoint1, rotatePoint2

function Enigma() {
	let enigmaImage = GImage("EnigmaTopView.png");
	enigmaImage.addEventListener("load", function() {
		let gw = GWindow(enigmaImage.getWidth(), enigmaImage.getHeight());
		gw.add(enigmaImage);
		runEnigmaSimulation(gw);
   });
}

// You are responsible for filling in the rest of the code.  Your
// implementation of runEnigmaSimulation should perform the
// following operations:
//
// 1. Create an object that encapsulates the state of the Enigma machine.
// 2. Create and add graphical objects that sit on top of the image.
// 3. Add listeners that forward mouse events to those objects.

function runEnigmaSimulation(gw) {
   // Fill this in, along with helper functions that decompose the work
   let enigma = {lamps_arr:[], rotors_arr:[], offset:[]};
   let KEY_LETTERS = ["A","B","C","D","E","F","G","H","I","J","K","L","M","N","O","P","Q","R","S","T","U","V","W","X","Y","Z"];

   let mousedownAction = function(e) {
	let obj = gw.getElementAt(e.getX(), e.getY());
	if (obj !== null && obj.mousedownAction !== undefined) {
	obj.mousedownAction(enigma);
	}
   };

   let mouseupAction = function(e){
	let obj = gw.getElementAt(e.getX(), e.getY());
	if (obj !== null && obj.mouseupAction !== undefined){
		obj.mouseupAction(enigma);
	}
   };

   let clickAction = function(e){
	let obj = gw.getElementAt(e.getX(), e.getY());
	if (obj !== null && obj.clickAction !== undefined){
		obj.clickAction(enigma);
	}
   };

   // keyboard function
   function keys_fun(){
	for (let i = 0; i < 26; i++){
		let key = GCompound(-KEY_RADIUS,-KEY_RADIUS);
		let d = KEY_RADIUS*2;
		let coo = KEY_LOCATIONS[i];
		let x = coo.x;
		let y = coo.y;
		let big_circle = GOval(x, y, d, d);
		let small_circle = GOval(x + KEY_BORDER, y + KEY_BORDER, d - KEY_BORDER*2, d - KEY_BORDER*2);
		let letter = GLabel(KEY_LETTERS[i], x + KEY_BORDER*8, y + KEY_BORDER*8);
	
		letter.setFont(KEY_FONT);
		letter.setColor(KEY_UP_COLOR);
		letter.setTextAlign("center");
		letter.setBaseline("middle");
		big_circle.setFilled(true);
		big_circle.setColor(KEY_BORDER_COLOR);
		big_circle.setFillColor(KEY_BORDER_COLOR);
		small_circle.setFilled(true);
		small_circle.setColor(KEY_BGCOLOR);
		small_circle.setFillColor(KEY_BGCOLOR);
	
		key.add(big_circle);
		key.add(small_circle);
		key.add(letter);
		gw.add(key);
	
	
		key.mousedownAction = function(enigma) {
			//do stuff when mouse clicks down

			letter.setColor(KEY_DOWN_COLOR);
			let lamp_letter = KEY_LETTERS[i];

			for (let j = 2; j > -1; j--){
				lamp_letter = applyPermutation(lamp_letter, ROTOR_PERMUTATIONS[j], enigma.rotors_arr[j].offset);
			}

			//let advance = advanceRotor(enigma.rotors_arr[2]);
			if (advanceRotor(enigma.rotors_arr[2])){ // fast rotor
				if (advanceRotor(enigma.rotors_arr[1])){ // medium rotor
					advanceRotor(enigma.rotors_arr[0]); // slow rotor
				}
			}

			enigma.on = lamp_letter;

			let lamp_index = KEY_LETTERS.indexOf(lamp_letter);
			enigma.lamps_arr[lamp_index].setColor(LAMP_ON_COLOR);
		};
	
		key.mouseupAction = function(enigma){
			// stop doing stuff when mouse goes up
			letter.setColor(KEY_UP_COLOR);
			let lamp_letter = enigma.on;
			let lamp_index = KEY_LETTERS.indexOf(lamp_letter);
			enigma.lamps_arr[lamp_index].setColor(LAMP_OFF_COLOR);

		};
	
	   }
   }

   // lamps function
   function lamps_fun(){
	for (let i = 0; i < 26; i++){
		let lamp = GCompound(-LAMP_RADIUS, -LAMP_RADIUS);
		let d = LAMP_RADIUS*2;
		let coo = LAMP_LOCATIONS[i];
		let x = coo.x;
		let y = coo.y;
		let circ = GOval(x, y, d, d);
		let letter_lamp = GLabel(KEY_LETTERS[i], x + KEY_BORDER*8, y + KEY_BORDER*8);
	
		letter_lamp.setFont(LAMP_FONT);
		letter_lamp.setTextAlign("center");
		letter_lamp.setBaseline("middle");
		circ.setFilled(true);
		circ.setColor(LAMP_BORDER_COLOR);
		circ.setFillColor(LAMP_BGCOLOR);
	
		lamp.add(circ);
		lamp.add(letter_lamp);
		lamp.letter_lamp = letter_lamp;
		lamp.letter_lamp.setColor(LAMP_OFF_COLOR);
		gw.add(lamp);
		enigma.lamps_arr.push(letter_lamp);

	   }
   }

   //rotors function
   function rotors_fun(){
	for (let i = 0; i < 3; i++){
		let rotor = GCompound(-ROTOR_WIDTH/2, -ROTOR_HEIGHT/2);
		let coo = ROTOR_LOCATIONS[i];
		let x = coo.x;
		let y = coo.y;
		let rot_rect = GRect(x, y, ROTOR_WIDTH , ROTOR_HEIGHT);
		let letter_rot = GLabel(KEY_LETTERS[0], x + ROTOR_WIDTH/2, y + ROTOR_HEIGHT/2);
	
		letter_rot.setFont(ROTOR_FONT);
		letter_rot.setColor(ROTOR_COLOR);
		letter_rot.setTextAlign("center");
		letter_rot.setBaseline("middle");
		rot_rect.setFilled(true);
		rot_rect.setColor(ROTOR_BGCOLOR);
		rot_rect.setFillColor(ROTOR_BGCOLOR);
	
		rotor.add(rot_rect);
		rotor.add(letter_rot);
		invertKey(enigma.rotors_arr, i);

		gw.add(rotor);

		rotor.permutation = ROTOR_PERMUTATIONS[i];
		enigma.rotors_arr.push(rotor);	
		rotor.offset = 0;
		rotor.label = letter_rot;

		rotor.clickAction = function(enigma){
			advanceRotor(rotor);
		}
	   }
   	}

	// function to advance the rotors
	function advanceRotor(rotor){
		rotor.offset += 1;
		rotor.offset = rotor.offset % 26;
		rotor.label.setLabel(KEY_LETTERS[rotor.offset]);
		if (rotor.offset === 0){
			return true;
		}
	}

	// function to apply the permutations
	function applyPermutation(letter, permutation, offset_value) {
		// Compute the index of the letter after shifting it by the offset, wrapping around if necessary.

		// computer index of alphabet character
		let current_key = KEY_LETTERS.indexOf(letter);

		// shift index by the offset
		current_key += offset_value;
		current_key = current_key % 26;
		console.log("current key " + current_key);

		// look up character at that index in the permutation string
		permutation = ROTOR_PERMUTATIONS[2][current_key];
		
		let final_key_index = KEY_LETTERS.indexOf(permutation);

		final_key_index -= offset_value;
		final_key_index = (final_key_index + 26) % 26;
		console.log("final key index " + final_key_index);
		let result_key = KEY_LETTERS[final_key_index];

		// Return the index of the resulting character after subtracting the offset, wrapping if necessary.
		console.log("result key letter " + result_key);
		return result_key;
	}

	function invertKey(curr_encryption_str, index){
		// get the original pre-encryption string of letters
		curr_encryption_str = ROTOR_PERMUTATIONS[index]; // get a rotor permutation string
		let post_inv_str = ""; // empty string to fill with inverted permutation letters

		// get letter at that index
		for (let i = 0; i < 26; i++){
			let post_letter = KEY_LETTERS[i]; // character from alphabet string at a certain index from 26 letters
			let letter_index = curr_encryption_str.indexOf(post_letter); // get that character's index in the permutation string
			let pre_letter = KEY_LETTERS[letter_index]; // find its encryption letter
			post_inv_str += pre_letter; // add it to our empty string	
		}

		console.log(post_inv_str);
		return post_inv_str; // return that string

	}

   gw.addEventListener("mousedown", mousedownAction);
   gw.addEventListener("mouseup", mouseupAction);
   gw.addEventListener("click", clickAction);


   return keys_fun(), lamps_fun(), rotors_fun();
}
