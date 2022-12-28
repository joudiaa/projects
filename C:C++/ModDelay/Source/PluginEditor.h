/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "Controls.h"
//==============================================================================
/**
*/
class MUS424Lab2ModDelayAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    MUS424Lab2ModDelayAudioProcessorEditor (MUS424Lab2ModDelayAudioProcessor&);
    ~MUS424Lab2ModDelayAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void UpdateDisplay();
    void resized() override;

    class ModTimer : public juce::Timer
    {
    public:
        ModTimer (MUS424Lab2ModDelayAudioProcessorEditor &);
        virtual void    timerCallback();
        
    private:
        MUS424Lab2ModDelayAudioProcessorEditor&  editor;
    };

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    MUS424Lab2ModDelayAudioProcessor& audioProcessor;
    ModTimer  *updateTimer;
    Controls      *controlsWin;

    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MUS424Lab2ModDelayAudioProcessorEditor)
};
