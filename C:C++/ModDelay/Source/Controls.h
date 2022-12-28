/*
  ==============================================================================

  This is an automatically generated GUI class created by the Projucer!

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Created with Projucer version: 6.0.7

  ------------------------------------------------------------------------------

  The Projucer is part of the JUCE library.
  Copyright (c) 2020 - Raw Material Software Limited.

  ==============================================================================
*/

#pragma once

//[Headers]     -- You can add your own extra header files here --
#include <JuceHeader.h>
#include "PluginProcessor.h"
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Projucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class Controls  : public juce::Component,
                  public juce::ComboBox::Listener,
                  public juce::Slider::Listener
{
public:
    //==============================================================================
    Controls ();
    ~Controls() override;

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    void init (MUS424Lab2ModDelayAudioProcessor *p);
    void displayMinFreq(float val1);
    void displayMaxFreq(float val1);
    void displayModAmount(float val1);
    void displaylfoRate(float val1);
    void displayForwardGain(float val1);
    void displayFeedbackGain(float val1);
    void displayPlugFunction(int val1);
    //[/UserMethods]

    void paint (juce::Graphics& g) override;
    void resized() override;
    void comboBoxChanged (juce::ComboBox* comboBoxThatHasChanged) override;
    void sliderValueChanged (juce::Slider* sliderThatWasMoved) override;



private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    MUS424Lab2ModDelayAudioProcessor *pProcessor;
    //[/UserVariables]

    //==============================================================================
    std::unique_ptr<juce::ComboBox> function__comboBox;
    std::unique_ptr<juce::Slider> min_freq__slider;
    std::unique_ptr<juce::Slider> max_freq__slider;
    std::unique_ptr<juce::Slider> modAmount__slider;
    std::unique_ptr<juce::ComboBox> lfoType__comboBox;
    std::unique_ptr<juce::Slider> lfoRate__slider;
    std::unique_ptr<juce::Slider> forwardGain__slider;
    std::unique_ptr<juce::Slider> feedbackGain__slider;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Controls)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

