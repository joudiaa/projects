// sound chain
SndBuf hum => dac;

me.dir() + "/hum.wav" => hum.read;
hum.samples() => hum.pos;


// functions
fun void funOne()
{
    Math.random2f(1.0,2.0) => hum.rate;
    0 => hum.pos;
    2::second => now;
}

fun void funTwo()
{
    Math.random2f(.2,.8) => panic.gain;
    1 => panic.rate;
    0 => panic.pos;
    1000::ms => now;
        
    0 => cafe.pos;
    1 => cafe.rate;
    1000::ms => now;
}

// MAIN PROGRAM
for ( 0 => int i; i < 50; i++ )
{
    funOne(); 
    funTwo();

    
}


fun void foo( int a )
{
    for (1 => int a; a < 10; a++)
    {
        <<<a>>>;
        Math.random2f(.2,.8) => panic.gain;
        1 => panic.rate;
        0 => panic.pos;
        1000::ms => now;
        
        0 => cafe.pos;
        1 => cafe.rate;
        1000::ms => now;
        
    }
}

spork ~ foo(1);
500::ms => now;
spork ~ foo(2);

while(true)
    1::second => now;