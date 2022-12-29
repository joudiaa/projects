/*
  ==============================================================================
    
    MUSIC 320C - ASSIGNMENT 1 STARTER CODE
    PLUGINPROCESSOR.H
    SPRING 2022

    COPYRIGHT (C) 2022 CENTER FOR COMPUTER RESEARCH IN MUSIC AND ACOUSTICS

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
// Import our Visualizer code
#include "Visualizer.h"

// Macros for FFT size and order. Try changing these!
#define FFT_ORDER 11
#define FFT_SIZE (1 << (FFT_ORDER))

//==============================================================================
/**
*/
class HW1StarterCodeAudioProcessor  :  public foleys::MagicProcessor,
                                    private juce::AudioProcessorValueTreeState::Listener  // Listener for parameters
{
public:
    //==============================================================================
    HW1StarterCodeAudioProcessor();
    ~HW1StarterCodeAudioProcessor() override;

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    //==============================================================================
// PGM takes this over:
//    juce::AudioProcessorEditor* createEditor() override;
//    bool hasEditor() const override;

    //==============================================================================
    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;

    //==============================================================================
    // Inherited from juce::AudioProcessorValueTreeState::Listener
    void parameterChanged(const juce::String &parameterID, float newValue) override;

private:
    //==============================================================================
    // Parameter listener setup
    juce::AudioProcessorValueTreeState treeState;
    juce::AudioProcessorValueTreeState::ParameterLayout createParameterLayout();

    // ADD YOUR PARAMETER POINTERS HERE
    float leak, fs;
    float dbgain;

    // PGM SETUP
    Visualizer* fftPlot = nullptr;       // We connect our FFT plot to this
    // PGM Tree state. Needs to be called after createParameterLayour
    //foleys::MagicProcessorState magicState {*this};   

    // FFT SETUP
    // Do your FFT setup here...
    // Here's some free buffers
    juce::dsp::FFT forwardFFT;
    juce::dsp::WindowingFunction<float> window;
    float fftBuffer[FFT_SIZE];
    float newFFTData[FFT_SIZE*2];
    float oldFFTData[FFT_SIZE/2];
    int fftIndex = 0;
    float fftData[FFT_SIZE/2];
    float frequencies[FFT_SIZE/2];

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (HW1StarterCodeAudioProcessor)
};
