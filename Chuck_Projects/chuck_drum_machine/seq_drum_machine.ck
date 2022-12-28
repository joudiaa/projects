Hid hi;
HidMsg msg;

// which keyboard
0 => int device;
// get from command line
if( me.args() ) me.arg(0) => Std.atoi => device;

// open keyboard (get device number from command line)
if( !hi.openKeyboard( device ) ) me.exit();
<<< "keyboard '" + hi.name() + "' ready", "" >>>;


fun void keyboard_control()
{
    // infinite event loop
    while( true )
    {
        // wait on event
        hi => now;

        // get one or more messages
        while( hi.recv( msg ) )
        {
            // check for action type
            if( msg.isButtonDown() )
            {
                <<< "down:", msg.which, "(code)", msg.key, "(usb key)", msg.ascii, "(ascii)" >>>;
                recognize_key();
                recognize_key2();
                recognize_key3();

            }

            else
            {
                //<<< "up:", msg.which, "(code)", msg.key, "(usb key)", msg.ascii, "(ascii)" >>>;
            }
        }
    }
}

spork ~ keyboard_control();

float gain_param;

// STK ModalBar

// patch
//ModalBar bar => NRev r => dac;

// scale
//[0, 2, 4, 7, 8, 11] @=> int scale[];

// sound chain
Gain master => dac;
SndBuf kick => master;
SndBuf hihat => master;
SndBuf snare => master;
SndBuf openhat => NRev r => master;

.6 => master.gain;
0 => hihat.gain;
// infinite time loop
while( true )
{


    // load soundfiles into sndbuf
    me.dir() +"Dubstep_Kick.wav" => kick.read;
    me.dir() + "/Dubstep_Closed_Hat1.wav" => hihat.read;
    me.dir() + "/Dubstep_Snare.wav" => snare.read;
    me.dir() + "/Dubstep_Open_Hat.wav" => openhat.read;

    // set all playheads to end so no sound is made
    kick.samples() => kick.pos;
    hihat.samples() => hihat.pos;
    snare.samples() => snare.pos;
    openhat.samples() => openhat.pos;

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
        1 => hihat.rate; // hihate rate
        <<< "counter: ", counter, "beat: ", beat >>>;
        counter++; // counter + 1 => counter
        250::ms => now;
    
        // open hat
        if ((beat == 3) || (beat == 5))
        {
            0 => openhat.pos;
            1 => openhat.rate;
        }
        
    }
}

1::week => now;
float reverb_param;
float rate_param;

fun void recognize_key()
{
    if (msg.ascii == 65) // A
    {
        <<<"Increase hihat.gain by 0.05">>>;
        if (gain_param < 0.5)
        {
            0.5 +=> gain_param;
            <<<"current hihat.gain(): " + gain_param>>>;
        }
        gain_param => hihat.gain;
    }

    if (msg.ascii == 68)// D
    {
        <<<"Decrease hihat.gain by 0.05">>>;
        if (gain_param > 0)
        {
            0.5 -=> gain_param;
            <<<"current hihat.gain(): " + gain_param>>>;
        }
        gain_param => hihat.gain;
    }
}
fun void recognize_key2()
{

    if (msg.ascii == 81)
    {
        <<<"Increase r.mix by 0.05">>>;
        if (reverb_param < 0.5)
        {
            0.05 +=> reverb_param;
            <<<"current r.mix(): " + reverb_param>>>;
        }
        reverb_param => r.mix;
    }

    if (msg.ascii == 69)
    {
        <<<"Decrease r.mix by 0.05">>>;
        if (reverb_param > 0)
        {
            0.05 -=> reverb_param;
            <<<"current r.mix(): " + reverb_param>>>;
        }
        reverb_param => r.mix;
    }
}

fun void recognize_key3()
{
    if (msg.ascii == 87)
    {
        <<<"Increase kick.rate by 0.05">>>;
        if (rate_param < 0.5)
        {
            0.05 +=> rate_param;
            <<<"current kick.rate(): " + rate_param>>>;
        }
        rate_param => kick.rate;
    }

    if (msg.ascii == 83)
    {
        <<<"Decrease kick.rate by 0.05">>>;
        if (rate_param > 0)
        {
            0.05 -=> rate_param;
            <<<"current kick.rate(): " + rate_param>>>;
        }
        rate_param => kick.rate;
    }
}
