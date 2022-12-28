/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

enum {
    kPhaser        = 0,
    kFlanger,
    kChorus
};
enum {
    kModeSine   =0,
    kModeTri
};


#include <JuceHeader.h>

#define kPi                         3.1415926
#define kDelayLength                 48000
#define kSmoothingTime      0.05


typedef struct {
    double  dly[kDelayLength];         // delay storage
    int     wp;                         // write pointer
    void Init(){
        int ind;
        for (ind=0; ind<kDelayLength; ind++)
            dly[ind]=0.0;
        wp=0;
    }
    void Write(double inData){
        wp--;
        // When wrapping write pointer, copy most recent four samples to the end of the line
        // to facilitate reading four consecutive samples for Lagrange interpolation without
        // having to check each of the four taps for wrapping.
        if(wp<0){
            wp += kDelayLength-4;
            dly[kDelayLength-4]=dly[0];
            dly[kDelayLength-3]=dly[1];
            dly[kDelayLength-2]=dly[2];
            dly[kDelayLength-1]=dly[3];
        }
        dly[wp]=inData;
    }
    double Read(double delay){
        // Limit delay based on max allocated storage in buffer
        if(delay>((double)kDelayLength)-5.0)
            delay=((double)kDelayLength)-5.0;
        // Calculate read pointer location, wrapping if necessary
        double rp=((double) wp) + delay-1.0;
        if(rp>((double)kDelayLength-4.0))
            rp -= ((double) kDelayLength-4.0);
        
        double delaysamp=floor(rp);
        int readpoint=((int) delaysamp);
        double frac=1.0 + rp-delaysamp;
        double b0,b1,b2,b3;
        
        // Lab2_Task
        // Calculate Lagrange coefficients here. Note that the quantity frac should contain the
        // Lagrange fraction, with 1.0 < frac < 2.0. Also note that in the function ProcessDelayLoop
        // which calls this function, Read is called before Write, so the write pointer has not yet
        // been decremented when Read is called. This could lead to an apparent "off by one" error in
        // the amount of delay applied.
        
        // Pass-through code, sets delay to integer number of samples
        b0 = (-1/6)*(frac-1)*(frac-2)*(frac-3);
        b1 = (1/2)*(frac-0)*(frac-2)*(frac-3);
        b2 = (-1/2)*(frac-0)*(frac-1)*(frac-3);
        b3 = (1/6)*(frac-0)*(frac-1)*(frac-2);
        double outsamp = b0*dly[readpoint]+b1*dly[readpoint+1]+b2*dly[readpoint+2]+b3*dly[readpoint+3];
        return outsamp;
    }
} DelayLine;


typedef struct {
    double  b[3];         // Continuous-time numerator
    double  a[3];         // Continuous-time denominator
    double  targetCofs[5];      // Discrete-time target coefficients
    double  cofs[5];            // Discrete-time smoothed coefficients
    double  smoothingFactor;
    double  samplingRate;
    double z1,z2;
    void Init(){
        z1=0.0;z2=0.0;
        b[0]=1.0;b[1]=0.0;b[2]=0.0;
        a[0]=1.0;a[1]=0.0;a[2]=0.0;
        targetCofs[0]=1.0;targetCofs[1]=0.0;targetCofs[2]=0.0;targetCofs[3]=0.0;targetCofs[4]=0.0;
        SlamCoefs();
        smoothingFactor=1.0-exp(-1.0/(samplingRate*kSmoothingTime));
    }
    void SetAllpassFreq(double afreq)
    {
        // Lab2_Task
        // Set allpass pole/zero locations here. Note that the input argument is
        // the desired frequency in Hz. Beware the dreaded "two pi" error!
        double afreq_rad = 2.0*kPi*afreq;
        
        
        // Pass-through code
        b[0]=1.0; b[1]=-2.0*afreq_rad; b[2]=pow(afreq_rad,2);
        a[0]=1.0; a[1]=2.0*afreq_rad;  a[2]=pow(afreq_rad,2);
    }
    void Bilinear(double warpfreq)
    {
        double sTerm,Td,scalar;
        double b0,b1,b2,a0,a1,a2;
        double bz0,bz1,bz2,az0,az1,az2;
        
        if(warpfreq==0.0)
            Td=1.0/samplingRate;
        else
            Td=2.0/(2.0*kPi*warpfreq)*tan(2.0*kPi*warpfreq/(2.0*samplingRate));
        
        b2=b[0]; b1=b[1]; b0=b[2];
        a2=a[0]; a1=a[1]; a0=a[2];
        sTerm=2.0/Td;
        bz0=b0+b1*sTerm+b2*sTerm*sTerm;
        bz1=2.0*b0-2.0*b2*sTerm*sTerm;
        bz2=b0-b1*sTerm+b2*sTerm*sTerm;
        az0=a0+a1*sTerm+a2*sTerm*sTerm;
        az1=2.0*a0-2.0*a2*sTerm*sTerm;
        az2=a0-a1*sTerm+a2*sTerm*sTerm;
        scalar=1.0/az0;
        targetCofs[0]=bz0*scalar; targetCofs[1]=bz1*scalar; targetCofs[2]=bz2*scalar; targetCofs[3]=az1*scalar; targetCofs[4]=az2*scalar;
    }
    void SetSR(double fs){
        samplingRate=fs;
    }
    double Process(double input){
        double temp;
        temp=z1+cofs[0]*input;
        z1=z2+cofs[1]*input-cofs[3]*temp;
        z2=cofs[2]*input-cofs[4]*temp;
        return temp;
    }
    double Getb0(){
        return cofs[0];
    }
    double GetState(){
        return z1;
    }
    void SlamCoefs(){
        cofs[0]=targetCofs[0];
        cofs[1]=targetCofs[1];
        cofs[2]=targetCofs[2];
        cofs[3]=targetCofs[3];
        cofs[4]=targetCofs[4];
    }
    void SmoothCoefs(){
        cofs[0] += (targetCofs[0]-cofs[0])*smoothingFactor;
        cofs[1] += (targetCofs[1]-cofs[1])*smoothingFactor;
        cofs[2] += (targetCofs[2]-cofs[2])*smoothingFactor;
        cofs[3] += (targetCofs[3]-cofs[3])*smoothingFactor;
        cofs[4] += (targetCofs[4]-cofs[4])*smoothingFactor;
    }
} Allpass;



typedef struct {
    double phase;
    double freq;
    double samplingRate;
    int mode;
    void Init(){
        phase=0.0;
        freq=1.0;
        mode=0;
    }
    void SetSR(double thesr){
        samplingRate=thesr;
    }
    void SetFreq(double thefreq){
        freq=thefreq;
    }
    void SetMode(double themode){
        mode=themode;
    }
    double GetVal(){
        double output;
        if (mode==kModeSine)  //sine mode
            output=0.5-0.5*cos(phase);
        else{
            if(phase>kPi)
                output=1.0-(phase-kPi)/kPi;
            else
                output=phase/kPi;
        }
                
        phase += freq*2.0*kPi/samplingRate;
        if(phase>2.0*kPi)
            phase -= 2.0*kPi;
        return output;
    }
} LFOosc;


//==============================================================================
/**
*/
class MUS424Lab2ModDelayAudioProcessor  : public juce::AudioProcessor
{
public:
    //==============================================================================
    MUS424Lab2ModDelayAudioProcessor();
    ~MUS424Lab2ModDelayAudioProcessor() override;

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    //==============================================================================
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

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
    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

    
    void SetPlugFunction(int theFunction);
    void SetLFOType(int lfotype);
    void SetLFORate(double thelforate);
    void SetMinFreq(double theminfreq);
    void SetMaxFreq(double themaxfreq);
    void SetModAmount(double themodamount);
    void SetMinMaxDelay();
    void SetFWDGain(double ffgain);
    void SetFBKGain(double fbgain);
    double ProcessDelayLoop(double inputsamp);
    
    juce::AudioParameterInt*   functionParam;
    juce::AudioParameterInt*   lfoTypeParam;
    juce::AudioParameterFloat*  minFreqParam;
    juce::AudioParameterFloat*  maxFreqParam;
    juce::AudioParameterFloat*  modAmountParam;
    juce::AudioParameterFloat*  lfoRateParam;
    juce::AudioParameterFloat*  fwdGainParam;
    juce::AudioParameterFloat*  fbkGainParam;

private:
    //Param values
    int     plugFunction;
    int     lfoFunction;
    double  minFreq;
    double  maxFreq;
    double  minDelay,maxDelay;
    double  modAmount;
    double  lfoRate;
    double  fwdGain;
    double  fbkGain;
    double  delayedAPsig;
    
    DelayLine   dly1;
    LFOosc      lfo1;
    Allpass     ap0,ap1,ap2,ap3;
    
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MUS424Lab2ModDelayAudioProcessor)
};
