/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
MUS424Lab2ModDelayAudioProcessorEditor::MUS424Lab2ModDelayAudioProcessorEditor (MUS424Lab2ModDelayAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    updateTimer = new ModTimer(*this);

    controlsWin = new Controls();
    controlsWin->init(&p);
    addAndMakeVisible (controlsWin);
    controlsWin->setBounds (0, 0, controlsWin->getWidth(), controlsWin->getHeight());

    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize(controlsWin->getWidth(), controlsWin->getHeight());
    // Start timer
    updateTimer->startTimer(20);
}

MUS424Lab2ModDelayAudioProcessorEditor::~MUS424Lab2ModDelayAudioProcessorEditor()
{
    delete updateTimer;
    delete controlsWin;
}

//==============================================================================
void MUS424Lab2ModDelayAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setColour (juce::Colours::white);
    g.setFont (15.0f);
    g.drawFittedText ("Hello World!", getLocalBounds(), juce::Justification::centred, 1);
}

void MUS424Lab2ModDelayAudioProcessorEditor::UpdateDisplay()
{
    controlsWin->displayMinFreq(audioProcessor.minFreqParam->get());
    controlsWin->displayMaxFreq(audioProcessor.maxFreqParam->get());
    controlsWin->displayModAmount(audioProcessor.modAmountParam->get());
    controlsWin->displaylfoRate(audioProcessor.lfoRateParam->get());
    controlsWin->displayForwardGain(audioProcessor.fwdGainParam->get());
    controlsWin->displayFeedbackGain(audioProcessor.fbkGainParam->get());
    controlsWin->displayPlugFunction(audioProcessor.functionParam->get());
}

void MUS424Lab2ModDelayAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
}

//==============================================================================
MUS424Lab2ModDelayAudioProcessorEditor::ModTimer::ModTimer(MUS424Lab2ModDelayAudioProcessorEditor &p)
: editor(p)
{
}

void    MUS424Lab2ModDelayAudioProcessorEditor::ModTimer::timerCallback()
{
    editor.UpdateDisplay();
    editor.repaint();
}
