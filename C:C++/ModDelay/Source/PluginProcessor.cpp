/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
MUS424Lab2ModDelayAudioProcessor::MUS424Lab2ModDelayAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       )
#endif
{
    addParameter(functionParam       = new juce::AudioParameterInt  ("function", "Function", 0, 2, 1));
    addParameter(lfoTypeParam       = new juce::AudioParameterInt  ("lfotype", "LFOType", 0, 1, 1));

    addParameter(minFreqParam         = new juce::AudioParameterFloat ("min freq", "Min Freq", 20.0f, 2.0e3f, 100.0f));
    addParameter(maxFreqParam         = new juce::AudioParameterFloat ("max freq", "Max Freq", 20.0f, 2.0e3f, 1000.0f));
    addParameter(modAmountParam         = new juce::AudioParameterFloat ("mod amount", "Mod Amount", 0.0f, 3.0f, 1.0f));
    addParameter(lfoRateParam         = new juce::AudioParameterFloat ("lfo rate", "LFO Rate", 0.0f, 10.0f, 0.5f));
    addParameter(fwdGainParam         = new juce::AudioParameterFloat ("fwd gain", "FWD Gain", 0.0f, 1.0f, 0.5f));
    addParameter(fbkGainParam         = new juce::AudioParameterFloat ("fbk gain", "FBK Gain", -1.0f, 1.0f, 0.5f));

    
    minFreq  = minFreqParam->get();
    maxFreq  = maxFreqParam->get();
    modAmount = modAmountParam->get();
    lfoRate  = lfoRateParam->get();
    fwdGain  = fwdGainParam->get();
    fbkGain  = fbkGainParam->get();

}

MUS424Lab2ModDelayAudioProcessor::~MUS424Lab2ModDelayAudioProcessor()
{
}

//==============================================================================
const juce::String MUS424Lab2ModDelayAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool MUS424Lab2ModDelayAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool MUS424Lab2ModDelayAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool MUS424Lab2ModDelayAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double MUS424Lab2ModDelayAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int MUS424Lab2ModDelayAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int MUS424Lab2ModDelayAudioProcessor::getCurrentProgram()
{
    return 0;
}

void MUS424Lab2ModDelayAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String MUS424Lab2ModDelayAudioProcessor::getProgramName (int index)
{
    return {};
}

void MUS424Lab2ModDelayAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void MUS424Lab2ModDelayAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
    double fs = getSampleRate();
    lfo1.SetSR(fs);
    dly1.Init();
    lfo1.Init();
    ap0.SetSR(fs);ap1.SetSR(fs);ap2.SetSR(fs);ap3.SetSR(fs);
    ap0.Init(); ap1.Init(); ap2.Init(); ap3.Init();
    delayedAPsig=0.0;
}

void MUS424Lab2ModDelayAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool MUS424Lab2ModDelayAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void MUS424Lab2ModDelayAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // This is here to avoid people getting screaming feedback
    // when they first compile a plugin, but obviously you don't need to keep
    // this code if your algorithm always overwrites all the output channels.
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    auto mainInputOutput = getBusBuffer (buffer, true, 0);
    auto numchans = mainInputOutput.getNumChannels();
    float inp0,inp1;
    for (auto j = 0; j < buffer.getNumSamples(); ++j)
    {
        inp0 = mainInputOutput.getReadPointer (0) [j];
        if(numchans>1)
            inp0= 0.5*(inp0 + mainInputOutput.getReadPointer (1) [j]);
        
        inp0=ProcessDelayLoop(inp0);
        
        //       if(numchans>1){
        //           inp1=wahFilter.ProcessR(inp1);
        //       }
        
        *mainInputOutput.getWritePointer (0, j) = inp0;
        if(numchans>1)
            *mainInputOutput.getWritePointer (1, j) = inp0;
    }
    // This is the place where you'd normally do the guts of your plugin's
    // audio processing...
    // Make sure to reset the state if your inner loop is processing
    // the samples and the outer loop is handling the channels.
    // Alternatively, you can process the samples with the channels
    // interleaved by keeping the same state.
    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        auto* channelData = buffer.getWritePointer (channel);

        // ..do something to the data...
    }
}

//==============================================================================
bool MUS424Lab2ModDelayAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* MUS424Lab2ModDelayAudioProcessor::createEditor()
{
    return new MUS424Lab2ModDelayAudioProcessorEditor (*this);
}

//==============================================================================
void MUS424Lab2ModDelayAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
    juce::MemoryOutputStream stream (destData, true);
    stream.writeInt(*functionParam);
    stream.writeInt(*lfoTypeParam);
    stream.writeFloat(*minFreqParam);
    stream.writeFloat(*maxFreqParam);
    stream.writeFloat(*modAmountParam);
    stream.writeFloat(*lfoRateParam);
    stream.writeFloat(*fwdGainParam);
    stream.writeFloat(*fbkGainParam);
}

void MUS424Lab2ModDelayAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
    juce::MemoryInputStream stream (data, static_cast<size_t> (sizeInBytes), false);
    
    float fval, cval;
    int ival;
    bool bval;

    ival = stream.readInt();
    cval = functionParam->convertTo0to1(ival);
    functionParam->setValueNotifyingHost(cval);

    ival = stream.readInt();
    cval = lfoTypeParam->convertTo0to1(ival);
    lfoTypeParam->setValueNotifyingHost(cval);

    fval = stream.readFloat();
    cval = minFreqParam->convertTo0to1(fval);
    minFreqParam->setValueNotifyingHost(cval);

    fval = stream.readFloat();
    cval = maxFreqParam->convertTo0to1(fval);
    maxFreqParam->setValueNotifyingHost(cval);
    
    fval = stream.readFloat();
    cval = modAmountParam->convertTo0to1(fval);
    modAmountParam->setValueNotifyingHost(cval);
    
    fval = stream.readFloat();
    cval = lfoRateParam->convertTo0to1(fval);
    lfoRateParam->setValueNotifyingHost(cval);

    fval = stream.readFloat();
    cval = fwdGainParam->convertTo0to1(fval);
    fwdGainParam->setValueNotifyingHost(cval);

    fval = stream.readFloat();
    cval = fbkGainParam->convertTo0to1(fval);
    fbkGainParam->setValueNotifyingHost(cval);

}

void MUS424Lab2ModDelayAudioProcessor::SetPlugFunction(int theFunction)
{
    plugFunction=theFunction;
    SetMinMaxDelay();
    delayedAPsig=0.0;
}
void MUS424Lab2ModDelayAudioProcessor::SetLFOType(int lfotype)
{
    lfo1.SetMode(lfotype);
}
void MUS424Lab2ModDelayAudioProcessor::SetLFORate(double thelforate)
{
    lfo1.SetFreq(thelforate);
    lfoRate=thelforate;
    SetMinMaxDelay();
}

void MUS424Lab2ModDelayAudioProcessor::SetMinFreq(double theminfreq)
{
    minFreq=theminfreq;
    SetMinMaxDelay();
}
void MUS424Lab2ModDelayAudioProcessor::SetMaxFreq(double themaxfreq)
{
    maxFreq=themaxfreq;
    SetMinMaxDelay();
}
void MUS424Lab2ModDelayAudioProcessor::SetModAmount(double themodamount)
{
    modAmount=themodamount;
    SetMinMaxDelay();
}


void MUS424Lab2ModDelayAudioProcessor::SetMinMaxDelay()
{
    double slope;
    double fs = getSampleRate();
    if(plugFunction<kChorus){
        minDelay=0.5/maxFreq*fs;
        maxDelay=0.5/minFreq*fs;
    }
    else{
        minDelay=0.02*fs;
        slope=pow(2.0,modAmount/12.0)-1.0;
        maxDelay=minDelay + slope*fs/(kPi*lfoRate);
        if(lfoRate<0.1)
            maxDelay=minDelay;
        if(maxDelay>kDelayLength-5)
            maxDelay=kDelayLength-5;
    }
}

void MUS424Lab2ModDelayAudioProcessor::SetFWDGain(double ffgain)
{
    fwdGain=ffgain;
}
void MUS424Lab2ModDelayAudioProcessor::SetFBKGain(double fbgain)
{
    fbkGain=fbgain;
}


double MUS424Lab2ModDelayAudioProcessor::ProcessDelayLoop(double inputsamp)
{
    double readData = 0.0,inData; // These are the output and input of the allpass or delay line
    double lfoVal;   // lfoVal is used either for setting allpass frequency or anount of delay
    
    if(plugFunction==kPhaser){
        // Set allpass coefficients for the frequency determined by the LFO
        lfoVal=lfo1.GetVal()*(maxFreq-minFreq) + minFreq;
        ap0.SetAllpassFreq(lfoVal);ap1.SetAllpassFreq(lfoVal);
        ap2.SetAllpassFreq(lfoVal);ap3.SetAllpassFreq(lfoVal);
        ap0.Bilinear(lfoVal);ap1.Bilinear(lfoVal);ap2.Bilinear(lfoVal);ap3.Bilinear(lfoVal);
        ap0.SmoothCoefs();ap1.SmoothCoefs();ap2.SmoothCoefs();ap3.SmoothCoefs();


        // Lab2_Task
        // Implement Phaser here. The four filters within the phaser are declared as
        // ap0,ap1,ap2, and ap3. They can be run after the delay-free loop is resolved
        // and the value of u is discovered, by executing, e.g, u1=ap0.Process(u).
        // Since the flanger/chorus uses the same loop structure as the phaser, there are
        // declarations corresponding to the figure in the lab handout as follows:
        // ID on Figure         code declaration
        // x                ->  inputsamp
        // y                ->  outData
        // gB               ->  fbkGain
        // gF               ->  fwdGain
        // w                ->  readData
        // u                ->  inData
        // The values of each filter's b0 coefficient and current state are obtained in the
        // starter code below and are returned in  bT0,bT1,bT2,bT3 for the coefficients, and
        // ST0,ST1,ST2,ST3 for the four filter states. For each filter at any given time, you
        // can assume that the output of the nth filter would then be:
        // output = bTn*input + STn.
        // Note that the feedforward path is already implemented below for the flanger/chorus
        // and that code can be shared by the phaser, using the line
        // outData=readData+fwdGain+inData.
        double bT0,bT1,bT2,bT3,ST0,ST1,ST2,ST3;
        bT0=ap0.Getb0();bT1=ap1.Getb0();bT2=ap2.Getb0();bT3=ap3.Getb0();
        ST0=ap0.GetState();ST1=ap1.GetState();ST2=ap2.GetState();ST3=ap3.GetState();
        
        double bT, sT;
        //bT = bT0*bT1*bT2*bT3;
        bT=bT0*bT1*bT2*bT3;
        //sT = (bT3*bT2*bT1*bT0*ST0)+(bT3*bT2*ST1)+(bT3*ST2)+ST3;
        sT = ((bT1*bT2*bT3*ST0) + (bT2*bT3*ST1) + (bT3*ST2) + ST3);

        
        // Place your code here.
        //inData = inputsamp+(fbkGain*readData);
        //readData = bT*inData + sT;    // Dummy code: set allpass chain output to zero.
        inData = inputsamp + (fbkGain*readData);
        readData = bT*inData + sT;// Dummy code: set allpass chain output to zero.
//        double u0, u1, u2, u3;
//        u0 = ap0.Process(inData); u1 = ap1.Process(u0); u2 = ap1.Process(u1); u3 = ap1.Process(u2);
        double u0 = ap0.Process(inData);
        double u1 = ap1.Process(u0);
        double u2 = ap2.Process(u1);
        double u3 = ap3.Process(u2);
  }
    else{
        lfoVal=lfo1.GetVal()*(maxDelay-minDelay) + minDelay;
        readData=dly1.Read(lfoVal);
        inData=readData*fbkGain + inputsamp;
        dly1.Write(inData);
    }
    
    double outData=readData+fwdGain*inData;
    return outData;
}


//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new MUS424Lab2ModDelayAudioProcessor();
}
