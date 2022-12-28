// sound chain
Gain master => dac;
SndBuf pencil => master;
SndBuf panic => dac;
SndBuf zoom => master;
SndBuf gtr => master;
SndBuf type => master;
SndBuf tea => dac.left;
SndBuf book => dac.right;
SndBuf cafe => master;
SndBuf fay => master;

5 => panic.gain;
0.8 => master.gain;

// load soundfiles into sndbuf
me.dir() +"/pencil.wav" => pencil.read;
me.dir() + "/panic.wav" => panic.read;
me.dir() + "/zoom.wav" => zoom.read;
me.dir() + "/guitar.wav" => gtr.read;
me.dir() + "/typing_short.wav" => type.read;
me.dir() + "/tea.wav" => tea.read;
me.dir() + "/book_page_short.wav" => book.read;
me.dir() + "/cafe.wav" => cafe.read;
me.dir() + "/fayrouz_short.wav" => fay.read;

// set all playheads to end so no sound is made
pencil.samples() => pencil.pos;
panic.samples() => panic.pos;
zoom.samples() => zoom.pos;
gtr.samples() => gtr.pos;
type.samples() => type.pos;
tea.samples() => tea.pos;
book.samples() => book.pos;
cafe.samples() => cafe.pos;
fay.samples() => fay.pos;

// initialize counter variable
0 => int counter;

// infinite loop
for ( 0 => int i; i < 50; i++ )
{
    <<<i>>>;
    // beat goes from 0 to 7 (8 positions)
    counter % 8 => int beat;
    
    // pencil drum on 0 and 4
    if ( (beat == 0) || (beat == 4) )
    {
        0 => pencil.pos;
    }
    
    0.5 => pencil.gain;
    
    //zoom drum on 2 and 6
    if ( (beat == 2))
    {
        0 => book.pos;
        0.8 => book.rate;
       
    }
    if (( beat == 5))
    {
        0 => zoom.pos;
        Math.random2f(0.5,1.5) => zoom.rate;
    }
    if ((beat == 6))
    {
        0 => tea.pos;
        1 => tea.rate;
    }
    if (( beat == 1) || (beat == 3))
    {
        0 => gtr.pos;
        Math.random2f(.5, 1.8) => gtr.rate;
    }
    
    // typing
    0 => type.pos;
    2 => type.gain;
    Math.random2f(.4, 1.8) => type.rate; // type rate
    <<< "counter: ", counter, "beat: ", beat >>>;
    counter++; // counter + 1 => counter
    500::ms => now;    
}

for ( 0 => int i; i < 50; i++ )
{
    <<<i>>>;
    // beat goes from 0 to 7 (8 positions)
    counter % 8 => int beat;
    
    // pencil drum on 0 and 4
    if ( (beat == 0) || (beat == 4) )
    {
        0 => book.pos;
    }
    
    0.5 => book.gain;
    
    //beat 2
    if ( (beat == 2) || ( beat == 6))
    {
        0 => tea.pos;
        1 => tea.rate;
        
    }
    if (( beat == 4))
    {
        0 => gtr.pos;
        0.5 => gtr.rate;
    }
    if ((beat == 3))
    {
        0 => fay.pos;
        0.2 => fay.gain;
        Math.random2f(1.0, 2.0) => fay.rate;
    }
    
    <<< "counter: ", counter, "beat: ", beat >>>;
    counter++; // counter + 1 => counter
    500::ms => now; 
}

fun void foo( int a )
{
    for (1 => int a; a < 10; a++)
    {
        <<<a>>>;
        Math.random2f(.2,.8) => panic.gain;
        1 => panic.rate;
        //Math.random2f(.2,1.8) => panic.rate;
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