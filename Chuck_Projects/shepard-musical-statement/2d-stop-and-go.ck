//--------------------------------------------------------------------
// name: shepard-2-class.ck (class-based version)
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
    -.002 => float INC;
    // unit time (change interval)
    1::ms => dur T;
    
    // starting pitches (in MIDI note numbers, octaves apart)
    [ 12.0, 24, 36, 48, 60, 72, 84, 96, 108 ] @=> float BASE[];
    // actual pitches (including offset)
    [ 12.0, 24, 36, 48, 60, 72, 84, 96, 108 ] @=> float pitches[];
    // number of tones
    pitches.size() => int N;
    // bank of tones
    TriOsc tones[N];
    // overall gain
    Gain sum => outlet; 10.0/N => sum.gain;
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

// instantiate three Shepard generators
Shepard a => Gain sum => dac;
Shepard b => sum;
Shepard c => sum;
// normalize
1.0/3 => sum.gain;

// relative pitch offset
0 => a.offset;
3 => b.offset;
7 => c.offset;

// set direction and speed
.004 => a.INC;
.004 => b.INC;
.004 => c.INC;

// spork independent control functions, one for each Shepard generator
spork ~ a.run();
spork ~ b.run();
spork ~ c.run();

// main "wait" loop
while( true ) 1::second => now;