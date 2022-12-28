// sound chain
TriOsc chord[3];
Gain master => dac;
for( 0 => int i; i < chord.cap(); i++ )
{
    chord[i] => master;
    1.0/chord.cap() => chord[i].gain;
    
}

// function
fun void playChord( int root, float length )
{

    Std.mtof(root) => chord[0].freq;
    
    // third (minor)
    Std.mtof(root+3) => chord[1].freq;
    
    // fifth
    Std.mtof(root+7) => chord[2].freq;
    
    length::ms => now;
}

// MAIN PROGRAM
1 => master.gain;

// for loop
for( 20 => int i; i < 50; i++)
{
    playChord(Math.random2(50,70), 100);
    
    50::ms => now;
}

