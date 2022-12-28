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

//[Headers] You can add your own extra header files here...
//[/Headers]

#include "Controls.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
Controls::Controls ()
{
    //[Constructor_pre] You can add your own custom stuff here..
    //[/Constructor_pre]

    function__comboBox.reset (new juce::ComboBox ("functionComboBox"));
    addAndMakeVisible (function__comboBox.get());
    function__comboBox->setEditableText (false);
    function__comboBox->setJustificationType (juce::Justification::centredLeft);
    function__comboBox->setTextWhenNothingSelected (juce::String());
    function__comboBox->setTextWhenNoChoicesAvailable (TRANS("(no choices)"));
    function__comboBox->addItem (TRANS("Phaser"), 1);
    function__comboBox->addItem (TRANS("Flanger"), 2);
    function__comboBox->addItem (TRANS("Chorus"), 3);
    function__comboBox->addListener (this);

    function__comboBox->setBounds (40, 32, 144, 24);

    min_freq__slider.reset (new juce::Slider ("minFreqSlider"));
    addAndMakeVisible (min_freq__slider.get());
    min_freq__slider->setRange (20, 2000, 0);
    min_freq__slider->setSliderStyle (juce::Slider::LinearHorizontal);
    min_freq__slider->setTextBoxStyle (juce::Slider::TextBoxLeft, false, 80, 20);
    min_freq__slider->addListener (this);

    min_freq__slider->setBounds (64, 104, 256, 24);

    max_freq__slider.reset (new juce::Slider ("maxFreqSlider"));
    addAndMakeVisible (max_freq__slider.get());
    max_freq__slider->setRange (20, 2000, 0);
    max_freq__slider->setSliderStyle (juce::Slider::LinearHorizontal);
    max_freq__slider->setTextBoxStyle (juce::Slider::TextBoxLeft, false, 80, 20);
    max_freq__slider->addListener (this);

    max_freq__slider->setBounds (64, 136, 256, 24);

    modAmount__slider.reset (new juce::Slider ("modAmountSlider"));
    addAndMakeVisible (modAmount__slider.get());
    modAmount__slider->setRange (0, 3, 0);
    modAmount__slider->setSliderStyle (juce::Slider::LinearHorizontal);
    modAmount__slider->setTextBoxStyle (juce::Slider::TextBoxLeft, false, 80, 20);
    modAmount__slider->addListener (this);

    modAmount__slider->setBounds (64, 200, 256, 24);

    lfoType__comboBox.reset (new juce::ComboBox ("LFOTypeComboBox"));
    addAndMakeVisible (lfoType__comboBox.get());
    lfoType__comboBox->setEditableText (false);
    lfoType__comboBox->setJustificationType (juce::Justification::centredLeft);
    lfoType__comboBox->setTextWhenNothingSelected (juce::String());
    lfoType__comboBox->setTextWhenNoChoicesAvailable (TRANS("(no choices)"));
    lfoType__comboBox->addItem (TRANS("Sin"), 1);
    lfoType__comboBox->addItem (TRANS("Tri"), 2);
    lfoType__comboBox->addListener (this);

    lfoType__comboBox->setBounds (64, 264, 136, 24);

    lfoRate__slider.reset (new juce::Slider ("lfoRateSlider"));
    addAndMakeVisible (lfoRate__slider.get());
    lfoRate__slider->setRange (0, 10, 0);
    lfoRate__slider->setSliderStyle (juce::Slider::LinearHorizontal);
    lfoRate__slider->setTextBoxStyle (juce::Slider::TextBoxLeft, false, 80, 20);
    lfoRate__slider->addListener (this);

    lfoRate__slider->setBounds (64, 296, 256, 24);

    forwardGain__slider.reset (new juce::Slider ("forwardGainSlider"));
    addAndMakeVisible (forwardGain__slider.get());
    forwardGain__slider->setRange (0, 1, 0);
    forwardGain__slider->setSliderStyle (juce::Slider::LinearHorizontal);
    forwardGain__slider->setTextBoxStyle (juce::Slider::TextBoxLeft, false, 80, 20);
    forwardGain__slider->addListener (this);

    forwardGain__slider->setBounds (64, 360, 256, 24);

    feedbackGain__slider.reset (new juce::Slider ("feedbackGainSlider"));
    addAndMakeVisible (feedbackGain__slider.get());
    feedbackGain__slider->setRange (-1, 1, 0);
    feedbackGain__slider->setSliderStyle (juce::Slider::LinearHorizontal);
    feedbackGain__slider->setTextBoxStyle (juce::Slider::TextBoxLeft, false, 80, 20);
    feedbackGain__slider->addListener (this);

    feedbackGain__slider->setBounds (64, 392, 256, 24);


    //[UserPreSize]
    //[/UserPreSize]

    setSize (348, 436);


    //[Constructor] You can add your own custom stuff here..
    function__comboBox->setSelectedId(1);
    lfoType__comboBox->setSelectedId(1);
    //[/Constructor]
}

Controls::~Controls()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    function__comboBox = nullptr;
    min_freq__slider = nullptr;
    max_freq__slider = nullptr;
    modAmount__slider = nullptr;
    lfoType__comboBox = nullptr;
    lfoRate__slider = nullptr;
    forwardGain__slider = nullptr;
    feedbackGain__slider = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void Controls::paint (juce::Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (juce::Colour (0xff323e44));

    {
        float x = 12.0f, y = 4.0f, width = 324.0f, height = 60.0f;
        juce::Colour fillColour = juce::Colour (0xff202038);
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.fillRoundedRectangle (x, y, width, height, 10.000f);
    }

    {
        int x = 100, y = 4, width = 124, height = 32;
        juce::String text (TRANS("Function"));
        juce::Colour fillColour = juce::Colour (0xffa3d7e4);
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font (15.00f, juce::Font::plain).withTypefaceStyle ("Regular"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centred, true);
    }

    {
        float x = 12.0f, y = 68.0f, width = 324.0f, height = 100.0f;
        juce::Colour fillColour = juce::Colour (0xff202038);
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.fillRoundedRectangle (x, y, width, height, 10.000f);
    }

    {
        int x = 92, y = 68, width = 148, height = 32;
        juce::String text (TRANS("Phaser / Flanger Freq"));
        juce::Colour fillColour = juce::Colour (0xffa3d7e4);
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font (15.00f, juce::Font::plain).withTypefaceStyle ("Regular"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centred, true);
    }

    {
        int x = 20, y = 100, width = 36, height = 32;
        juce::String text (TRANS("Min"));
        juce::Colour fillColour = juce::Colour (0xffa3d7e4);
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font (15.00f, juce::Font::plain).withTypefaceStyle ("Regular"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centred, true);
    }

    {
        int x = 20, y = 132, width = 36, height = 32;
        juce::String text (TRANS("Max"));
        juce::Colour fillColour = juce::Colour (0xffa3d7e4);
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font (15.00f, juce::Font::plain).withTypefaceStyle ("Regular"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centred, true);
    }

    {
        float x = 12.0f, y = 172.0f, width = 324.0f, height = 60.0f;
        juce::Colour fillColour = juce::Colour (0xff202038);
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.fillRoundedRectangle (x, y, width, height, 10.000f);
    }

    {
        int x = 100, y = 172, width = 148, height = 28;
        juce::String text (TRANS("Chorus Detune"));
        juce::Colour fillColour = juce::Colour (0xffa3d7e4);
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font (15.00f, juce::Font::plain).withTypefaceStyle ("Regular"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centred, true);
    }

    {
        int x = 20, y = 196, width = 36, height = 32;
        juce::String text (TRANS("Mod"));
        juce::Colour fillColour = juce::Colour (0xffa3d7e4);
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font (15.00f, juce::Font::plain).withTypefaceStyle ("Regular"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centred, true);
    }

    {
        float x = 12.0f, y = 236.0f, width = 324.0f, height = 92.0f;
        juce::Colour fillColour = juce::Colour (0xff202038);
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.fillRoundedRectangle (x, y, width, height, 10.000f);
    }

    {
        int x = 92, y = 236, width = 148, height = 32;
        juce::String text (TRANS("LFO"));
        juce::Colour fillColour = juce::Colour (0xffa3d7e4);
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font (15.00f, juce::Font::plain).withTypefaceStyle ("Regular"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centred, true);
    }

    {
        int x = 20, y = 260, width = 36, height = 32;
        juce::String text (TRANS("Fun"));
        juce::Colour fillColour = juce::Colour (0xffa3d7e4);
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font (15.00f, juce::Font::plain).withTypefaceStyle ("Regular"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centred, true);
    }

    {
        int x = 20, y = 292, width = 36, height = 32;
        juce::String text (TRANS("Rate"));
        juce::Colour fillColour = juce::Colour (0xffa3d7e4);
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font (15.00f, juce::Font::plain).withTypefaceStyle ("Regular"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centred, true);
    }

    {
        float x = 12.0f, y = 332.0f, width = 324.0f, height = 100.0f;
        juce::Colour fillColour = juce::Colour (0xff202038);
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.fillRoundedRectangle (x, y, width, height, 10.000f);
    }

    {
        int x = 92, y = 332, width = 148, height = 32;
        juce::String text (TRANS("MIX"));
        juce::Colour fillColour = juce::Colour (0xffa3d7e4);
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font (15.00f, juce::Font::plain).withTypefaceStyle ("Regular"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centred, true);
    }

    {
        int x = 20, y = 356, width = 36, height = 32;
        juce::String text (TRANS("Fwd"));
        juce::Colour fillColour = juce::Colour (0xffa3d7e4);
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font (15.00f, juce::Font::plain).withTypefaceStyle ("Regular"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centred, true);
    }

    {
        int x = 20, y = 388, width = 36, height = 32;
        juce::String text (TRANS("Back"));
        juce::Colour fillColour = juce::Colour (0xffa3d7e4);
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font (15.00f, juce::Font::plain).withTypefaceStyle ("Regular"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centred, true);
    }

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void Controls::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void Controls::comboBoxChanged (juce::ComboBox* comboBoxThatHasChanged)
{
    //[UsercomboBoxChanged_Pre]
    //[/UsercomboBoxChanged_Pre]

    if (comboBoxThatHasChanged == function__comboBox.get())
    {
        //[UserComboBoxCode_function__comboBox] -- add your combo box handling code here..
        switch(function__comboBox.get()->getSelectedId())
        {
            case 1:
            default:
                pProcessor->SetPlugFunction(kPhaser);
                *pProcessor->functionParam = 0;
                break;
            case 2:
                pProcessor->SetPlugFunction(kFlanger);
                *pProcessor->functionParam = 1;
                break;
            case 3:
                pProcessor->SetPlugFunction(kChorus);
                *pProcessor->functionParam = 2;
                break;
        }
        //[/UserComboBoxCode_function__comboBox]
    }
    else if (comboBoxThatHasChanged == lfoType__comboBox.get())
    {
        //[UserComboBoxCode_lfoType__comboBox] -- add your combo box handling code here..
        switch(lfoType__comboBox.get()->getSelectedId())
        {
            case 1:
            default:
                pProcessor->SetLFOType(kModeSine);
                *pProcessor->lfoTypeParam = 0;
                break;
            case 2:
                pProcessor->SetLFOType(kModeTri);
                *pProcessor->lfoTypeParam = 1;
                break;
        }
        //[/UserComboBoxCode_lfoType__comboBox]
    }

    //[UsercomboBoxChanged_Post]
    //[/UsercomboBoxChanged_Post]
}

void Controls::sliderValueChanged (juce::Slider* sliderThatWasMoved)
{
    //[UsersliderValueChanged_Pre]
    //[/UsersliderValueChanged_Pre]

    if (sliderThatWasMoved == min_freq__slider.get())
    {
        //[UserSliderCode_min_freq__slider] -- add your slider handling code here..
        float fval = min_freq__slider.get()->getValue();
        *pProcessor->minFreqParam = fval;
        pProcessor->SetMinFreq(fval);
        //[/UserSliderCode_min_freq__slider]
    }
    else if (sliderThatWasMoved == max_freq__slider.get())
    {
        //[UserSliderCode_max_freq__slider] -- add your slider handling code here..
        float fval = max_freq__slider.get()->getValue();
        *pProcessor->maxFreqParam = fval;
        pProcessor->SetMaxFreq(fval);
        //[/UserSliderCode_max_freq__slider]
    }
    else if (sliderThatWasMoved == modAmount__slider.get())
    {
        //[UserSliderCode_modAmount__slider] -- add your slider handling code here..
        float fval = modAmount__slider.get()->getValue();
        *pProcessor->modAmountParam = fval;
        pProcessor->SetModAmount(fval);
        //[/UserSliderCode_modAmount__slider]
    }
    else if (sliderThatWasMoved == lfoRate__slider.get())
    {
        //[UserSliderCode_lfoRate__slider] -- add your slider handling code here..
        float fval = lfoRate__slider.get()->getValue();
        *pProcessor->lfoRateParam = fval;
        pProcessor->SetLFORate(fval);
        //[/UserSliderCode_lfoRate__slider]
    }
    else if (sliderThatWasMoved == forwardGain__slider.get())
    {
        //[UserSliderCode_forwardGain__slider] -- add your slider handling code here..
        float fval = forwardGain__slider.get()->getValue();
        *pProcessor->fwdGainParam = fval;
        pProcessor->SetFWDGain(fval);
        //[/UserSliderCode_forwardGain__slider]
    }
    else if (sliderThatWasMoved == feedbackGain__slider.get())
    {
        //[UserSliderCode_feedbackGain__slider] -- add your slider handling code here..
        float fval = feedbackGain__slider.get()->getValue();
        *pProcessor->fbkGainParam = fval;
        pProcessor->SetFBKGain(fval);
        //[/UserSliderCode_feedbackGain__slider]
    }

    //[UsersliderValueChanged_Post]
    //[/UsersliderValueChanged_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
void Controls::init(MUS424Lab2ModDelayAudioProcessor *p)
{
    pProcessor = p;

}

void Controls::displayMinFreq(float val1)
{
    min_freq__slider.get()->setValue(val1);
}
void Controls::displayMaxFreq(float val1)
{
    max_freq__slider.get()->setValue(val1);
}
void Controls::displayModAmount(float val1)
{
    modAmount__slider.get()->setValue(val1);
}
void Controls::displaylfoRate(float val1)
{
    lfoRate__slider.get()->setValue(val1);
}
void Controls::displayForwardGain(float val1)
{
    forwardGain__slider.get()->setValue(val1);
}
void Controls::displayFeedbackGain(float val1)
{
    feedbackGain__slider.get()->setValue(val1);
}
void Controls::displayPlugFunction(int val1)
{
    //function__comboBox.get()->setSelectedId(val1);
}


//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Projucer information section --

    This is where the Projucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="Controls" componentName=""
                 parentClasses="public juce::Component" constructorParams="" variableInitialisers=""
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330"
                 fixedSize="0" initialWidth="348" initialHeight="436">
  <BACKGROUND backgroundColour="ff323e44">
    <ROUNDRECT pos="12 4 324 60" cornerSize="10.0" fill="solid: ff202038" hasStroke="0"/>
    <TEXT pos="100 4 124 32" fill="solid: ffa3d7e4" hasStroke="0" text="Function"
          fontname="Default font" fontsize="15.0" kerning="0.0" bold="0"
          italic="0" justification="36"/>
    <ROUNDRECT pos="12 68 324 100" cornerSize="10.0" fill="solid: ff202038"
               hasStroke="0"/>
    <TEXT pos="92 68 148 32" fill="solid: ffa3d7e4" hasStroke="0" text="Phaser / Flanger Freq"
          fontname="Default font" fontsize="15.0" kerning="0.0" bold="0"
          italic="0" justification="36"/>
    <TEXT pos="20 100 36 32" fill="solid: ffa3d7e4" hasStroke="0" text="Min"
          fontname="Default font" fontsize="15.0" kerning="0.0" bold="0"
          italic="0" justification="36"/>
    <TEXT pos="20 132 36 32" fill="solid: ffa3d7e4" hasStroke="0" text="Max"
          fontname="Default font" fontsize="15.0" kerning="0.0" bold="0"
          italic="0" justification="36"/>
    <ROUNDRECT pos="12 172 324 60" cornerSize="10.0" fill="solid: ff202038"
               hasStroke="0"/>
    <TEXT pos="100 172 148 28" fill="solid: ffa3d7e4" hasStroke="0" text="Chorus Detune"
          fontname="Default font" fontsize="15.0" kerning="0.0" bold="0"
          italic="0" justification="36"/>
    <TEXT pos="20 196 36 32" fill="solid: ffa3d7e4" hasStroke="0" text="Mod"
          fontname="Default font" fontsize="15.0" kerning="0.0" bold="0"
          italic="0" justification="36"/>
    <ROUNDRECT pos="12 236 324 92" cornerSize="10.0" fill="solid: ff202038"
               hasStroke="0"/>
    <TEXT pos="92 236 148 32" fill="solid: ffa3d7e4" hasStroke="0" text="LFO"
          fontname="Default font" fontsize="15.0" kerning="0.0" bold="0"
          italic="0" justification="36"/>
    <TEXT pos="20 260 36 32" fill="solid: ffa3d7e4" hasStroke="0" text="Fun"
          fontname="Default font" fontsize="15.0" kerning="0.0" bold="0"
          italic="0" justification="36"/>
    <TEXT pos="20 292 36 32" fill="solid: ffa3d7e4" hasStroke="0" text="Rate"
          fontname="Default font" fontsize="15.0" kerning="0.0" bold="0"
          italic="0" justification="36"/>
    <ROUNDRECT pos="12 332 324 100" cornerSize="10.0" fill="solid: ff202038"
               hasStroke="0"/>
    <TEXT pos="92 332 148 32" fill="solid: ffa3d7e4" hasStroke="0" text="MIX"
          fontname="Default font" fontsize="15.0" kerning="0.0" bold="0"
          italic="0" justification="36"/>
    <TEXT pos="20 356 36 32" fill="solid: ffa3d7e4" hasStroke="0" text="Fwd"
          fontname="Default font" fontsize="15.0" kerning="0.0" bold="0"
          italic="0" justification="36"/>
    <TEXT pos="20 388 36 32" fill="solid: ffa3d7e4" hasStroke="0" text="Back"
          fontname="Default font" fontsize="15.0" kerning="0.0" bold="0"
          italic="0" justification="36"/>
  </BACKGROUND>
  <COMBOBOX name="functionComboBox" id="54bd538d001d4ce1" memberName="function__comboBox"
            virtualName="" explicitFocusOrder="0" pos="40 32 144 24" editable="0"
            layout="33" items="Phaser&#10;Flanger&#10;Chorus" textWhenNonSelected=""
            textWhenNoItems="(no choices)"/>
  <SLIDER name="minFreqSlider" id="350e08138d37c6d5" memberName="min_freq__slider"
          virtualName="" explicitFocusOrder="0" pos="64 104 256 24" min="20.0"
          max="2000.0" int="0.0" style="LinearHorizontal" textBoxPos="TextBoxLeft"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1.0"
          needsCallback="1"/>
  <SLIDER name="maxFreqSlider" id="406d30445fa32756" memberName="max_freq__slider"
          virtualName="" explicitFocusOrder="0" pos="64 136 256 24" min="20.0"
          max="2000.0" int="0.0" style="LinearHorizontal" textBoxPos="TextBoxLeft"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1.0"
          needsCallback="1"/>
  <SLIDER name="modAmountSlider" id="6e8b05116ef1bc7f" memberName="modAmount__slider"
          virtualName="" explicitFocusOrder="0" pos="64 200 256 24" min="0.0"
          max="3.0" int="0.0" style="LinearHorizontal" textBoxPos="TextBoxLeft"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1.0"
          needsCallback="1"/>
  <COMBOBOX name="LFOTypeComboBox" id="42854635fd95e30d" memberName="lfoType__comboBox"
            virtualName="" explicitFocusOrder="0" pos="64 264 136 24" editable="0"
            layout="33" items="Sin&#10;Tri" textWhenNonSelected="" textWhenNoItems="(no choices)"/>
  <SLIDER name="lfoRateSlider" id="f2cc0905242b0ef6" memberName="lfoRate__slider"
          virtualName="" explicitFocusOrder="0" pos="64 296 256 24" min="0.0"
          max="10.0" int="0.0" style="LinearHorizontal" textBoxPos="TextBoxLeft"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1.0"
          needsCallback="1"/>
  <SLIDER name="forwardGainSlider" id="926063d2788f6e73" memberName="forwardGain__slider"
          virtualName="" explicitFocusOrder="0" pos="64 360 256 24" min="0.0"
          max="1.0" int="0.0" style="LinearHorizontal" textBoxPos="TextBoxLeft"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1.0"
          needsCallback="1"/>
  <SLIDER name="feedbackGainSlider" id="37c0d80b4bf140cb" memberName="feedbackGain__slider"
          virtualName="" explicitFocusOrder="0" pos="64 392 256 24" min="-1.0"
          max="1.0" int="0.0" style="LinearHorizontal" textBoxPos="TextBoxLeft"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1.0"
          needsCallback="1"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]

