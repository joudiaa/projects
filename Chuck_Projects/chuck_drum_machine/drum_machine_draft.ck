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