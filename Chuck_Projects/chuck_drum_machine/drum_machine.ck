// sound chain
Gain master => dac;
SndBuf kick => master;
SndBuf hihat => master;
SndBuf snare => master;

.6 => master.gain;

// load soundfiles into sndbuf
me.dir() +"Dubstep_Kick.wav" => kick.read;
me.dir() + "/Dubstep_Closed_Hat1.wav" => hihat.read;
me.dir() + "/Dubstep_Snare.wav" => snare.read;

// set all playheads to end so no sound is made
kick.samples() => kick.pos;
hihat.samples() => hihat.pos;
snare.samples() => snare.pos;

// initialize counter variable
0 => int counter;

// infinite loop
while ( true )
{
    // beat goes from 0 to 7 (8 positions)
    counter % 8 => int beat;
    
    // kick drum on 0 and 4
    if ( (beat == 0) || (beat == 4) )
    {
         0 => kick.pos;
    }
    
    0.5 => kick.gain;
    
    //snare drum on 2 and 6
    if ( (beat == 2) || (beat == 6) )
    {
        0 => snare.pos;
        Math.random2f(.6, 1.4) => snare.rate;
    }
    
    // hihat
    0 => hihat.pos;
    Math.random2f(.2, 1.8) => hihat.rate; // hihate rate
    <<< "counter: ", counter, "beat: ", beat >>>;
    counter++; // counter + 1 => counter
    250::ms => now;    
}