SinOsc s => dac;
SqrOsc q => dac;

// initialize variable i
500 => int a;

// while loop
while( a > 100 )
{
    // set volume for all
    0 => s.gain;
    0.1 => q.gain;
    // set frequency
    a => q.freq;
    // print i
    <<< a >>>;
    // advance time
    0.01::second => now;
    // updated in loop
    a--;
}

// set s volume
1=> s.gain;
0 => q.gain;

// set s frequency
//200 => s.freq;
Math.random2(100,1000) => int f;
f => s.freq; 
// play for 2 seconds
5::second => now;