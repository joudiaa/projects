/*
  ==============================================================================
    
    MUSIC 320C - ASSIGNMENT 1 STARTER CODE
    PLUGINPROCESSOR.CPP
    SPRING 2022

    COPYRIGHT (C) 2022 CENTER FOR COMPUTER RESEARCH IN MUSIC AND ACOUSTICS

  ==============================================================================
*/

#include "PluginProcessor.h"

//==============================================================================
// Create some static parameter IDs here
static juce::Identifier fftID {"fftPlot"};
static juce::String smoothTime {"smoothTime"};
static juce:: String dBOffset {" dB Offset"};

//==============================================================================

juce::AudioProcessorValueTreeState::ParameterLayout HW1StarterCodeAudioProcessor::createParameterLayout()
{
    juce::AudioProcessorValueTreeState::ParameterLayout layout;
    layout.add(std::make_unique<juce::AudioParameterFloat>(smoothTime, "Smooth Time", juce::NormalisableRange<float>(0, 500, 1), 0));
    layout.add(std::make_unique<juce::AudioParameterInt>(dBOffset, "dB Offset", 0, 60, 0));
               
    // Add your parameters here to your layout...
    return layout;
}

//==============================================================================
HW1StarterCodeAudioProcessor::HW1StarterCodeAudioProcessor()
  : // One or two initializations:
#ifndef JucePlugin_PreferredChannelConfigurations
  MagicProcessor (BusesProperties()
#if ! JucePlugin_IsMidiEffect
#if ! JucePlugin_IsSynth
                  .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
#endif
                  .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
#endif
                  ),
#endif
treeState(*this, nullptr, JucePlugin_Name, createParameterLayout()),
forwardFFT(FFT_ORDER),
window(FFT_SIZE, juce::dsp::WindowingFunction<float>::hann)
{ // Constructor body:
  // Attach your parameters to your listeners here...

  // Hooking up our FFT plot
  // Constructor needs pointer to data and data size
  fftPlot = magicState.createAndAddObject<Visualizer>(fftID, &fftData[0], FFT_SIZE/2);
  treeState.addParameterListener(smoothTime, this);
  treeState.addParameterListener(dBOffset, this);
    
  magicState.setGuiValueTree(BinaryData::Layout_xml, BinaryData::Layout_xmlSize);

}

HW1StarterCodeAudioProcessor::~HW1StarterCodeAudioProcessor()
{
}

//==============================================================================
const juce::String HW1StarterCodeAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool HW1StarterCodeAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool HW1StarterCodeAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool HW1StarterCodeAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double HW1StarterCodeAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int HW1StarterCodeAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int HW1StarterCodeAudioProcessor::getCurrentProgram()
{
    return 0;
}

void HW1StarterCodeAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String HW1StarterCodeAudioProcessor::getProgramName (int index)
{
    return {};
}

void HW1StarterCodeAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void HW1StarterCodeAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
    
    //oldFFTData.clear();
    
    // INITIALIZE frequency lines here
    for (int i = 0; i < FFT_SIZE/2; ++i)
        frequencies[i] = i*(fs/FFT_SIZE);
    
    fs = sampleRate;
    
    
    // Hook up frequencies to our x-axis data
    fftPlot->setX(&frequencies[0]);

    // Give our magicState the required sampling rate and samples per block
    magicState.prepareToPlay(sampleRate, samplesPerBlock);
}

void HW1StarterCodeAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool HW1StarterCodeAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
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

void HW1StarterCodeAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
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

    // This is the place where you'd normally do the guts of your plugin's
    // audio processing...
    // Make sure to reset the state if your inner loop is processing
    // the samples and the outer loop is handling the channels.
    // Alternatively, you can process the samples with the channels
    // interleaved by keeping the same state.
    
    
    // STARTER CODE TO GIVE YOU A PLOT
    // REPLACE THIS CODE
    
    // Sample plot is a gained up 2 Hz sin wave
    //for (int i = 0; i < FFT_SIZE/2; ++i)
        //fftData[i] = std::pow(10, 3)*std::sin(24.8* i/FFT_SIZE);
    
    // if we have data
    if (totalNumInputChannels > 0)
    {
        auto * channelData = buffer.getReadPointer(0);
        for (int samp = 0; samp < buffer.getNumSamples(); ++samp)
        {
            // add samples to a buffer
            fftBuffer[fftIndex] = channelData[samp];
            fftIndex++;
            
            // if buffer is full compute the fft
            if (fftIndex == FFT_SIZE)
            {
                // reset our index
                fftIndex = 0;
                juce::zeromem (newFFTData, sizeof (newFFTData));
                std::memcpy(newFFTData, fftBuffer, sizeof (fftBuffer));
                forwardFFT.performFrequencyOnlyForwardTransform(newFFTData);
                
                // copy FFTdata to plot data
                
                for (int i = 0; i < FFT_SIZE/2; i++)
                {
                    oldFFTData[i] = leak*oldFFTData[i] + (1.0 - leak)*newFFTData[i];
                    fftData[i] = dbgain*oldFFTData[i];
                }
            }
            
        }
    }
    
    fftPlot->update();
}

//==============================================================================
// Handle parameter updates here
void HW1StarterCodeAudioProcessor::parameterChanged(const juce::String &parameterID, float newValue)
{
    if (parameterID == smoothTime)
    {
        leak = newValue < __FLT_EPSILON__ ? 0.0 : std::exp(-(FFT_SIZE) / (newValue *0.001 * fs));
    }
    
    if (parameterID == dBOffset)
    {
        dbgain = std::pow(10, newValue/20.0);
    }
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new HW1StarterCodeAudioProcessor();
}
