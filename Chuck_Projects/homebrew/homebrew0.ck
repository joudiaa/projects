// sound chain
Gain master => dac;
SndBuf pencil => master;
SndBuf panic => dac;
SndBuf zoom => master;

5 => panic.gain;
0.8 => master.gain;

// load soundfiles into sndbuf
me.dir() +"/pencil.wav" => pencil.read;
me.dir() + "/panic.wav" => panic.read;
me.dir() + "/zoom.wav" => zoom.read;

// set all playheads to end so no sound is made
pencil.samples() => pencil.pos;
panic.samples() => panic.pos;
zoom.samples() => zoom.pos;

// initialize counter variable
0 => int counter;

// infinite loop
while ( true )
{
    // beat goes from 0 to 7 (8 positions)
    counter % 8 => int beat;
    
    // pencil drum on 0 and 4
    if ( (beat == 0) || (beat == 4) )
    {
        0 => pencil.pos;
    }
    
    0.5 => pencil.gain;
    
    //zoom drum on 2 and 6
    if ( (beat == 2) || (beat == 6) )
    {
        0 => zoom.pos;
        Math.random2f(.6, 1.4) => zoom.rate;
    }
    
    // breath
    0 => panic.pos;
    0.1 => panic.gain;
    Math.random2f(.2, 1.8) => panic.rate; // breath rate
    <<< "counter: ", counter, "beat: ", beat >>>;
    counter++; // counter + 1 => counter
    250::ms => now;    
}