SinOsc n => ADSR a => dac;
Noise o => LPF lpf => dac;
SqrOsc s => dac;


for (20 => int u; u < 60; u++)
{
    Math.random2(10000,20000) => int f;
    f => s.freq;
    0.1 => s.gain;
    100::ms => now;
}


for (38 => int i; i >30; i--)
{
    <<< i >>>;
    i => Std.mtof => n.freq;
    0 => s.gain;
    a.keyOn();
    100::ms => now;
    
    a.keyOff();
    
    a.releaseTime() => now;
    
    300::ms => now;
}

for (38 => int i; i >30; i--)
{
    <<< i >>>;
    i => Std.mtof => n.freq;
    
    a.keyOn();
    100::ms => now;
    
    a.keyOff();
    
    a.releaseTime() => now;
    
    300::ms => now;
}

0.5 => o.gain;