<<< "Joudi A. - Assignment 2" >>>;
// sound chain
SinOsc s => dac.left;
TriOsc t => dac.right;
SqrOsc q => dac;
SawOsc w => Pan2 p => dac;
SinOsc d => dac;

// initialize variable i
40 => int i;

// while loop
while( i < 100 )
{
    // set volume for all
    .1 => q.gain;
    1 => s.gain;
    1 => t.gain;
    0 => w.gain;
    0 => d.gain;
    // set frequency
    i => q.freq;
    i => s.freq;
    i => t.freq;
    // print i
    <<< i >>>;
    // advance time
    100::ms => now;
    // updated in loop
    i++;
}

// updating gain
.1 => q.gain;
1 => s.gain;
1 => t.gain;
0 => w.gain;
0 => d.gain;

// initializing z variable
1 => float z;

// while loop
while( z <= .3 )
{
    // setting pan
    Math.sin(now/3::second*10*pi) => p.pan;
    // advance time
    100::ms => now;
}

// for loop
for( 400 => int i; i > 390; i--)
{
    // printing i
    <<< i >>>;
    // updating frequency
    i => s.freq;
    i => t.freq;
    i => q.freq;
    // advance time
    100::ms => now;
}

// update w frequency
124 => q.freq;

// updating gain for all
.1 => q.gain;
1 => s.gain;
1 => t.gain;
0 => w.gain;
0 => d.gain;

// array declaration
[64, 71, 69, 75, 83, 81, 55, 64, 47, 77, 70, 88, 66, 63, 58, 47] @=> int G[];
[76, 59, 45, 63, 71, 57, 31, 76, 59, 65, 58, 76, 42, 51, 46, 59] @=> int B[];

// G.cap() is maximum number of elements in G[]
<<< G.cap() >>>;

// B.cap() is maximum number of elements in B[]
<<< B.cap() >>>;

// initializing e and a variables
0 => int e;
0 => int a;

// loop
for( 0 => e, 0 => a; e <= G.cap(), a <= B.cap() ; e++, a++ )
{
    // printing index e and its value
    <<< e, G[e] >>>;
    // MIDI to frequency
    Std.mtof(G[e]) => s.freq;
    // printing index a and its value
    <<< a, B[a] >>>;
    // MIDI to frequency
    Std.mtof(B[a]) => t.freq;
    // advance time
    1::second => now;
}

