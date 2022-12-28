//--------------------------------------------------------------------
// name: shepard-3-array.ck (class + array version)
// desc: continuous shepard-risset tone generator; 
//       descending but can easily made to ascend
//       generated for ARTFUL DESIGN | http://artful.design/
//
// author: Ge Wang (http://ccrma.stanford.edu/~ge/)
//   date: spring 2016; modified spring 2021
//--------------------------------------------------------------------

// Shepard generator class
class Shepard extends Chugraph
{
    // pitch offset
    0 => float OFFSET;
    // mean for normal intensity curve
    72+OFFSET => float MU;
    // standard deviation for normal intensity curve
    48 => float SD;
    // normalize to 1.0 at x==MU
    1 / gauss(MU, MU, SD) => float SCALE;
    // increment per unit time (use negative for descending)
    .002 => float INC;
    // unit time (change interval)
    1::ms => dur T;
    
    // starting pitches (in MIDI note numbers, octaves apart)
    [ 20.0, 100, 240, 300, 340, 400, 440, 500, 1000 ] @=> float BASE[];
    // actual pitches (including offset)
    [ 50.0, 100, 240, 300, 340, 400, 440, 500, 1000 ] @=> float pitches[];
    // number of tones
    pitches.size() => int N;
    // bank of tones
    TriOsc tones[N];
    // overall gain
    Gain sum => outlet; 20.0/N => sum.gain;
    // connect to dac
    for( int i; i < N; i++ ) { tones[i] => sum; }
    // offset
    offset( OFFSET );
    
    // set pitch offset
    fun float offset( float v )
    {
        v => OFFSET;
        // offset
        for( int i; i < N; i++) { BASE[i] + OFFSET => pitches[i]; }
    }
    
    // meant to be sporked!
    fun void run()
    {
        // infinite time loop
        while( true )
        {
            for( int i; i < N; i++ )
            {
                // set frequency from pitch
                pitches[i] => Std.mtof => tones[i].freq;
                // compute loundess for each tone
                gauss( pitches[i], MU, SD ) * SCALE => float intensity;
                // map intensity to amplitude
                Math.pow(intensity*96 => Math.dbtorms, 3) => tones[i].gain;
                // increment pitch
                INC +=> pitches[i];
                // wrap (for positive INC)
                if( pitches[i] > 120+OFFSET ) 108 -=> pitches[i];
                // wrap (for negative INC)
                else if( pitches[i] < 12+OFFSET ) 108 +=> pitches[i];
            }
            
            // advance time
            T => now;
        }
    }
    
    // normal function for loudness curve
    // NOTE: chuck-1.3.5.3 and later: can use Math.gauss() instead
    fun float gauss( float x, float mu, float sd )
    {
        return (1 / (sd*Math.sqrt(2*pi))) * Math.exp( -(x-mu)*(x-mu)
        / (2*sd*sd) );
    }
}

// sum
Gain sum => dac;
// array of three Shepard generators
Shepard tones[3];
// normalize
1.0 / tones.size() => sum.gain;

// set pitch offset
0 => tones[0].offset;
2 => tones[1].offset;
5 => tones[2].offset;

// initialize each Shepard generator
for( int i; i < tones.size(); i++ )
{
    tones[i] => sum;
    -.004 => tones[i].INC;
    spork ~ tones[i].run();
}

// main "wait" loop
while( true ) 1::second => now;