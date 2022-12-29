/*
  ==============================================================================
    
    MUSIC 320C - ASSIGNMENT 1 STARTER CODE
    VISUALIZER.H
    SPRING 2022

    COPYRIGHT (C) 2022 CENTER FOR COMPUTER RESEARCH IN MUSIC AND ACOUSTICS

  ==============================================================================
*/
#pragma once

#include <JuceHeader.h>

  // MagicVisualizer is a custom class that can be used to plot x vs data
  class Visualizer : public foleys::MagicPlotSource
  {
  public:
    //==============================================================================
    // Constructor requires pointer to data and data array size
    Visualizer(float * data, int dataSize);
    ~Visualizer() {}; // Does nothing                                                           
    //==============================================================================
    void pushSamples (const juce::AudioBuffer<float>& buffer) override {};  // Does nothing
    void update();
    //==============================================================================
    void createPlotPaths (juce::Path& path, juce::Path& filledPath, juce::Rectangle<float> bounds, foleys::MagicPlotComponent& component) override;
    void prepareToPlay (double sampleRate, int samplesPerBlockExpected) override {};  // Does nothing
    //==============================================================================
    // Extra function to set x-axis data
    void setX(float * newX);
  private:
    //==============================================================================
    // Private members point to data arrays and provide data array size
    float * data;
    float * x = nullptr;
    int dataSize;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Visualizer)
  };
