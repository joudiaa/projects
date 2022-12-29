/*
  ==============================================================================
    
    MUSIC 320C - ASSIGNMENT 1 STARTER CODE
    VISUALIZER.CPP
    SPRING 2022 

    COPYRIGHT (C) 2022 CENTER FOR COMPUTER RESEARCH IN MUSIC AND ACOUSTICS

  ==============================================================================
*/
#include "Visualizer.h"

  // Constructor requires pointer to data array and data array size
  Visualizer::Visualizer(float * data, int dataSize):
  data(data),
  dataSize(dataSize)
  {
  }

  // Set X write the 'x' pointer. It is up to the user to ensure
  // x matches dataSize
  void Visualizer::setX(float * newX)
  {
    x = newX;
  }

  // Update calls the parent resetLastDataFlag() method to update the plot
  void Visualizer::update()
  {
    resetLastDataFlag();
  }

  // createPlotPaths updates paths 
  void Visualizer::createPlotPaths(juce::Path &path, juce::Path &filledPath, juce::Rectangle<float> bounds,
                                   foleys::MagicPlotComponent &component)
  {
    // YOUR CODE GOES HERE
    // Modify the arguments as needed
    // scale factors are set based on the height/width of the rectangle divided by
    // the maximum value
    const auto yFactor = bounds.getHeight() / 60;
    const auto xFactor = static_cast<double> (bounds.getWidth()) / std::log10(dataSize-1);
    // clear the path and start a new subpath
    // if data is too small just draw from the bottom
    path.clear();
      path.startNewSubPath(bounds.getX(), float( data[0] > 0.001 ? bounds.getBottom() - yFactor*(20*std::log10(data[0])):bounds.getBottom()));
    // plot data
      for (int i = 1; i < dataSize; ++i)
      {
          float dBY = 20*std::log10(1.0e-7+data[i]);
          float Y = data[i] > 0.001 ? bounds.getBottom() - yFactor*dBY : bounds.getBottom();
          float X = bounds.getX() + std::log10(1.0e-7+i) * xFactor;
          path.lineTo( X, Y);
      }
      
      // Set the filledPath to path. This tells juce to draw this path
      // then we draw to each path
      filledPath = path;
      filledPath.lineTo(bounds.getBottomRight());
      filledPath.lineTo(bounds.getBottomLeft());
      filledPath.closeSubPath();
  }
