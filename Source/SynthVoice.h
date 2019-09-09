/*
  ==============================================================================

    SynthVoice.h
    Created: 31 Jul 2019 12:42:28am
    Author:  lika

  ==============================================================================
*/

#pragma once
#include "../JuceLibraryCode/JuceHeader.h"
#include "SynthSound.h"

class SineWaveVoice: public SynthesiserVoice
{
public:
    bool canPlaySound (SynthesiserSound *sound);
    void startNote (int midiNoteNumber, float velocity, SynthesiserSound *sound, int currentPitchWheelPosition);
    void stopNote (float velocity, bool allowTailOff);
    void pitchWheelMoved (int newPitchWheelValue);
    void controllerMoved (int controllerNumber, int newControllerValue);
    void renderNextBlock (AudioBuffer< float > &outputBuffer, int startSample, int numSamples);
    
    String getNote(int midiNoteNumber);
    double getSawtoothValue();
    double triangleWave();
    double sawtoothWave();
    double squareWave();
    double sineWave();
    
    void getWaveType (float *selection);
    double getCurrentSample();


    
private:
    double level;
    double frequency;
    double tailOff;
    // ====
    double output;
    double sampleRate;
    double angle;
    double angleDelta;
    int theWave;
};
