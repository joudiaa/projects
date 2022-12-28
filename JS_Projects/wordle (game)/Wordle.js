/*
 * File: Wordle.js
 * -----------------
 * This program implements the Wordle game.
 */
"use strict";

/* Constants */
// If you turn this to true, the game will use colors that are R/G colorblind friendly.
const COLORBLIND_MODE = false;

const GWINDOW_WIDTH = 400;  /** The width of the GWindow */

const NUM_LETTERS = 5;  /** The number of letters in each guess */
const NUM_GUESSES = 6;  /** The number of guesses the player has to win */

const GUESS_MARGIN = 8; /** The space around each guess square */
const SECTION_SEP = 32; /** The space between the grid, alert, and keyboard */

const BACKGROUND_DEFAULT_COLOR = "#121213";
const BACKGROUND_CORRECT_COLOR = COLORBLIND_MODE ? "#E37E43" : "#618C55";  /** Used in keyboard and guess squares */
const BACKGROUND_FOUND_COLOR = COLORBLIND_MODE ? "#94C1F6" : "#B1A04C";  /** Used in keyboard and guess squares */
const BACKGROUND_WRONG_COLOR = "#3A3A3C";  /** Used in keyboard and guess squares */
const KEYBOARD_DEFAULT_COLOR = "#818384";
const BORDER_COLOR = "#3A3A3C";  /** Color of the border around guess squares */
const TEXT_DEFAULT_COLOR = "#FFFFFF";
const TEXT_ALERT_COLOR = "#B05050";
const TEXT_WIN_COLOR = COLORBLIND_MODE ? "#94C1F6" : "#618C55";
const TEXT_LOSS_COLOR = "#B05050";

const GUESS_FONT = "700 36px HelveticaNeue";
const ALERT_FONT = "700 20px HelveticaNeue";

/* Computed Constants */

// The size of each guess square (computed to fill the entire GWINDOW_WIDTH)
const GUESS_SQUARE_SIZE =
  (GWINDOW_WIDTH - GUESS_MARGIN * 2 * NUM_LETTERS) / NUM_LETTERS;

// Height of the guess section in total
const GUESS_SECTION_HEIGHT =
  GUESS_SQUARE_SIZE * NUM_GUESSES + GUESS_MARGIN * NUM_GUESSES * 2;

// X and Y position where alerts should be centered
const ALERT_X = GWINDOW_WIDTH / 2;
const ALERT_Y = GUESS_SECTION_HEIGHT + SECTION_SEP;

// X and Y position to place the keyboard
const KEYBOARD_X = 0;
const KEYBOARD_Y = ALERT_Y + SECTION_SEP;

// GWINDOW_HEIGHT calculated to fit everything perfectly.
const GWINDOW_HEIGHT = KEYBOARD_Y + GKeyboard.getHeight(GWINDOW_WIDTH);

const arr_alerts = ["Hello World", "You Won!", "That guess isn't a word"];

/**
 * Accepts a KeyboardEvent and returns
 * the letter that was pressed, or null
 * if a letter wasn't pressed.
 * 
 * The letter returned will be lowercase
 */
function getKeystrokeLetter(e) {
  if (e.altKey || e.ctrlKey || e.metaKey) return null;
  const key = e.key.toLowerCase();

  if (!/^[a-z]$/.exec(key)) return null;

  return key;
}

/**
 * Accepts a KeyboardEvent and returns true
 * if that KeyboardEvent was the user pressing
 * enter (or return), and false otherwise.
 */
function isEnterKeystroke(e) {
  return (
    !e.altKey &&
    !e.ctrlKey &&
    !e.metaKey &&
    (e.code === "Enter" || e.code === "Return")
  );
}

/**
 * Accepts a KeyboardEvent and returns true
 * if that KeyboardEvent was the user pressing
 * backspace (or delete), and false otherwise.
 */
function isBackspaceKeystroke(e) {
  return (
    !e.altKey &&
    !e.ctrlKey &&
    !e.metaKey &&
    (e.code === "Backspace" || e.code === "Delete")
  );
}

/**
 * Accepts a string, and returns if it is a valid English word.
 */
function isEnglishWord(str) {
  str = str.toLowerCase();
  return _DICTIONARY.has(str);
}

/**
 * Returns a random common word from the English lexicon,
 * that is NUM_LETTERS long. All lowercase.
 * 
 * Throws an error if no such word exists.
 */
function getRandomWord() {
  const nLetterWords = [..._COMMON_WORDS].filter(
    (word) => word.length === NUM_LETTERS && isEnglishWord(word)
  );

  if (nLetterWords.length === 0) {
    throw new Error(
      `The list of common words does not have any words that are ${NUM_LETTERS} long!`
    );
  }

  return nLetterWords[randomInteger(0, nLetterWords.length - 1)];
}

const keyColor = [KEYBOARD_DEFAULT_COLOR, BACKGROUND_CORRECT_COLOR, BACKGROUND_FOUND_COLOR, BACKGROUND_WRONG_COLOR];
function win(){
  gameactive = true;
  return;
}

/** Main Function */
function Wordle() {
  let gw = GWindow(GWINDOW_WIDTH, GWINDOW_HEIGHT);
  let y = GUESS_MARGIN;
  let key_word = getRandomWord();
  let on_keyboard = GKeyboard(KEYBOARD_X, KEYBOARD_Y, GWINDOW_WIDTH, TEXT_DEFAULT_COLOR, keyColor[0]);
  let square_color = [BACKGROUND_DEFAULT_COLOR, BACKGROUND_CORRECT_COLOR, BACKGROUND_FOUND_COLOR, BACKGROUND_WRONG_COLOR];
  let guess_word = "";
  let user_input = ["", "", "", "", "", "", ""];
  let currentRow = 0;
  console.log("key word " + key_word);
  
  key_word = key_word.toUpperCase();

  let alert_label = GLabel(arr_alerts[0], ALERT_X, ALERT_Y);
  alert_label.setTextAlign("center");
  alert_label.setBaseline("middle");
  alert_label.setFont(ALERT_FONT);
  alert_label.setColor(TEXT_DEFAULT_COLOR);
  gw.add(alert_label);
  let guess = GCompound();
  let old_colors = [BACKGROUND_DEFAULT_COLOR, BACKGROUND_DEFAULT_COLOR, BACKGROUND_DEFAULT_COLOR,BACKGROUND_DEFAULT_COLOR, BACKGROUND_DEFAULT_COLOR];

  function ROW(temp_y, guess_word){
    let x = GUESS_MARGIN;
    //array of colors that are blank
    for (let i = 0; i < NUM_LETTERS; i++){
      let square = GRect(x, temp_y, GUESS_SQUARE_SIZE,  GUESS_SQUARE_SIZE);
      square.setFilled(true);
      square.setFillColor(old_colors[0]);
      square.setColor(BORDER_COLOR);
      console.log("here "+ guess_word);

      let letter = guess_word[i];

      if (letter === undefined){
        letter = "";
      }

      let label = GLabel(letter, x + (GUESS_SQUARE_SIZE/2), temp_y + (GUESS_SQUARE_SIZE/2));

      label.setColor(TEXT_DEFAULT_COLOR);
      label.setFont(GUESS_FONT);
      label.setTextAlign("center");
      label.setBaseline("middle");

      if (letter === "" || letter === " "){
        square.setFillColor(old_colors[0]);
        // console.log("black");
      }
      else if (key_word[i] === letter){
        square.setFillColor(old_colors[1]);
        // console.log("green");
      } 
      else if (key_word.includes(letter)){
        square.setFillColor(old_colors[2]);
        // console.log("yellow");
      } 
      else{
        square.setFillColor(old_colors[3]);
        // console.log("grey");
      }
      x += (GUESS_SQUARE_SIZE + (2*GUESS_MARGIN));
      
      guess.add(square);
      guess.add(label);
    }

    // gw.add(guess);
    
    return guess;
  }

  function square_update(guess_word){
    // let square_color = [BACKGROUND_DEFAULT_COLOR, BACKGROUND_CORRECT_COLOR, BACKGROUND_FOUND_COLOR, BACKGROUND_WRONG_COLOR];
    old_colors[1] = BACKGROUND_CORRECT_COLOR;
    old_colors[2] = BACKGROUND_FOUND_COLOR;
    old_colors[3] = BACKGROUND_WRONG_COLOR;
  
  }

  function square_back(guess_word){
    old_colors[1] = BACKGROUND_DEFAULT_COLOR;
    old_colors[2] = BACKGROUND_DEFAULT_COLOR;
    old_colors[3] = BACKGROUND_DEFAULT_COLOR;
  }

 

  function cb1(){
    let len = guess_word.length;
    let add = (GUESS_SQUARE_SIZE + (2*GUESS_MARGIN));
    if (len < NUM_LETTERS){
      letter = letter.toUpperCase();
      guess_word += letter;
      user_input[currentRow] = guess_word;
      let new_y = GUESS_MARGIN + (currentRow*add);
      let newWord = ROW(new_y, guess_word);
      gw.add(newWord);

    }
    else if (len > NUM_LETTERS){
      null;
    }

  }

  function guessGrid(user_input){
    let curr_y = GUESS_MARGIN;
    let add = (GUESS_SQUARE_SIZE + (2*GUESS_MARGIN));
    for(let i = 0; i < NUM_GUESSES; i++){
      let newRow = ROW(curr_y, user_input[i]);
      curr_y += add;
      //console.log(curr_y);
      gw.add(newRow);
    }
  }

  //have default colors for the guess as a global variable
  //click enter -> selectColors function for previous guess 
  //color previous guess in those new colors by going through it again 


  function cb2(){
    // function for enter key click
    let len = guess_word.length;
    square_update(user_input[currentRow - 1]);
    guessGrid(user_input);
    square_back(user_input[currentRow]);
    alerts(guess_word);
    if (currentRow < (NUM_GUESSES - 1)){
      if (len < NUM_LETTERS || !isEnglishWord(guess_word)){
        return; 
      }
      else{
        user_input[currentRow] = guess_word;
        currentRow += 1;
        guess_word = "";

      }
    }

  }
  function cb3(){
    // function for backspace key click
    if (currentRow < NUM_GUESSES - 1 || !isEnglishWord(guess_word)){
      console.log("guessword back" + guess_word);
      let len = guess_word.length;
      console.log("user input top" + user_input);
      guess_word = guess_word.substring(0,len -1);
      console.log("user input before" + user_input);
      user_input[currentRow] = guess_word;
      let newGrid = guessGrid(user_input);
      console.log("user input after" + user_input);

      return newGrid;

    }

  }

  function alerts(guess_word){
    //calling the function that updates the keyboard keys colors
    colorKey(guess_word);

    if (guess_word === key_word){
      alert_label.setLabel(arr_alerts[1]);
      alert_label.setColor(TEXT_WIN_COLOR);
      console.log("you win" + alert_label);
      win(true);

    }
    else if (!isEnglishWord(guess_word) && guess_word !== ""){
      alert_label.setLabel(arr_alerts[2]);
      alert_label.setColor(TEXT_LOSS_COLOR);
      console.log("wrong!" + alert_label);
    }
    else {
      alert_label.setColor(TEXT_DEFAULT_COLOR);
      console.log("hello world" + alert_label);
    }
  }
  function pressRealkey(e){
    let letter = getKeystrokeLetter(e);

    if (letter !== null){
      cb1(letter);
    }
    else{
      if (isEnterKeystroke(e)){
        cb2();
      }
      if(isBackspaceKeystroke(e)){
        cb3();
      }
    }
  }

  // function for the keyboard
  function keyboard(){
    gw.add(on_keyboard);
    // on_keyboard.addEventListener("keyclick", cb1);
    // on_keyboard.addEventListener("enter", cb2);
    // on_keyboard.addEventListener("backspace", cb3);

  }

  // function for the keyboard color update
  function colorKey(guess_word){
    for (let j = 0; j < NUM_GUESSES; j++){
      if (guess_word === ""){
        return;
      }
      for (let i =0; i < NUM_LETTERS; i++){
        let letter = guess_word[i];
        if (key_word.includes(letter)){
          on_keyboard.setKeyColor(letter, keyColor[2]); // yellow
          if (key_word[i]=== letter){
            on_keyboard.setKeyColor(letter, keyColor[1]); //green
          }
        }
        else if (key_word[i] === letter){
          // corret: green
          on_keyboard.setKeyColor(letter, keyColor[1]); //green
          
        }
        else {
          //not correct but update (i don't think this is necessary but sure i'll add it)
          on_keyboard.setKeyColor(letter, keyColor[3]); // black
          if (key_word.includes(letter)){
            on_keyboard.setKeyColor(letter, keyColor[2]); // yellow
            if (key_word=== letter){
              on_keyboard.setKeyColor(letter, keyColor[1]); //green
            }
          }
        }
      }
    }

  }



  function draw(){
    gw.clear();
    gw.add(alert_label);
  
    return guessGrid(user_input), keyboard(), colorKey(guess_word);

  }
 
  
  gw.addEventListener("keydown", pressRealkey);

  return draw();



}
