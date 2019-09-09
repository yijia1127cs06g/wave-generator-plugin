/*
  ==============================================================================

    SynthVoice.cpp
    Created: 31 Jul 2019 12:42:28am
    Author:  lika

  ==============================================================================
*/

#include "SynthVoice.h"



bool SineWaveVoice::canPlaySound (SynthesiserSound *sound)
{
    return dynamic_cast<SineWaveSound*>(sound) != nullptr;
}

void SineWaveVoice::startNote (int midiNoteNumber, float velocity, SynthesiserSound *sound, int currentPitchWheelPosition)
{
    
    
    
    //std::cout << std::setw(3) << std::setiosflags(std::ios::left) << getNote(midiNoteNumber) << ": ";
    //std::cout << std::setw(8) << std::setiosflags(std::ios::right) <<std::fixed<<std::setprecision(3) << frequency << " Hz" <<std::endl;

    
    // Sine Wave: x(t) = A*sin(2*pi*f*t + phi) = A*sin(w*t + phi)
    // A: amplitude
    // f: ordinary frequency
    // phi: delay or advance
    
    level = velocity;
    angle = 0.0;
    tailOff = 0.0;
    frequency = MidiMessage::getMidiNoteInHertz(midiNoteNumber);
    auto cyclesPerSample = frequency / getSampleRate();            // cyclesPerSample is f
    angleDelta = cyclesPerSample *  MathConstants<double>::twoPi; // angleDelta is w
    
}

void SineWaveVoice::stopNote (float velocity, bool allowTailOff)
{
    if (allowTailOff)
    {
        // start a tail-off by setting this flag. The render callback will pick up on
        // this and do a fade out, calling clearCurrentNote() when it's finished.
        
        if (tailOff == 0.0) // we only need to begin a tail-off if it's not already doing so - the
            tailOff = 1.0;  // stopNote method could be called more than once.
    }
    else
    {
        // we're being told to stop playing immediately, so reset everything..
        clearCurrentNote();
        angleDelta = 0.0;
    }
}

void SineWaveVoice::pitchWheelMoved (int newPitchWheelValue)
{
    
}
void SineWaveVoice::controllerMoved (int controllerNumber, int newControllerValue)
{
    
}
void SineWaveVoice::renderNextBlock (AudioBuffer< float > &outputBuffer, int startSample, int numSamples)
{
    if (angleDelta != 0)
    {
        if (tailOff > 0.0)
        {
            while (--numSamples >= 0)
            {
                double currentSample = getCurrentSample() * level * tailOff;
                
                for (auto i = outputBuffer.getNumChannels(); --i >= 0;)
                {
                    outputBuffer.addSample (i, startSample, currentSample);
                }
                ++startSample;
                
                tailOff *= 0.99;
                if (tailOff <= 0.005)
                {
                    clearCurrentNote();
                    angleDelta = 0.0;
                    break;
                }
            }
            
        }
        else
        {
            while (--numSamples >= 0)
            {
                double currentSample= getCurrentSample()*level;
                
                for (auto i = outputBuffer.getNumChannels(); --i >= 0;)
                {
                    outputBuffer.addSample (i, startSample, currentSample);
                }
                ++startSample;
            }
        }
    }
}

double SineWaveVoice::getCurrentSample()
{
    switch (theWave) {
        case 0:
            return sineWave();
            break;
        case 1:
            return sawtoothWave();
            break;
        case 2:
            return squareWave();
            break;
        case 3:
            return triangleWave();
            break;
        default:
            return 0;
            break;
    }
}

double SineWaveVoice::sineWave()
{
    double output = std::sin(angle);
    
    angle += angleDelta;
    
    if (angle > 2*MathConstants<double>::pi)
        angle -= 2*MathConstants<double>::pi;
    
    return output;
}

double SineWaveVoice::squareWave()
{
    double output;
    if (angle < MathConstants<double>::pi)
        output = 1;
    else
        output = -1;
    
    angle += angleDelta;
    
    if (angle > MathConstants<double>::pi*2)
        angle -= MathConstants<double>::pi*2;
    
    return output;
}

double SineWaveVoice::triangleWave()
{
    double output;
    if (angle < MathConstants<double>::pi)
        output = -1 + (2/MathConstants<double>::pi)*angle;
    else
        output = 3 - (2/MathConstants<double>::pi)*angle;
    
    angle += angleDelta;
    
    if (angle>(MathConstants<double>::twoPi))
        angle -= MathConstants<double>::twoPi;
    
    return output;
}

double SineWaveVoice::sawtoothWave()
{
    double output;
    output = 1 - (1/MathConstants<double>::pi * angle);
    
    angle += angleDelta;
    
    if (angle > MathConstants<double>::twoPi)
        angle -= MathConstants<double>::twoPi;
    
    return output;
}



String SineWaveVoice::getNote (int midiNoteNumber)
{
    String note;
    switch(midiNoteNumber%12){
        case 0:
            note = "C";
            break;
        case 1:
            return "C#";
            break;
        case 2:
            return "D";
            break;
        case 3:
            return "Eb";
            break;
        case 4:
            return "E";
            break;
        case 5:
            return "F";
            break;
        case 6:
            return "F#";
            break;
        case 7:
            return "G";
            break;
        case 8:
            return "G#";
            break;
        case 9:
            return "A";
            break;
        case 10:
            return "Bb";
            break;
        case 11:
            return "B";
            break;
    }
    return note;
}

void SineWaveVoice::getWaveType (float *selection)
{
    theWave = *selection;
}
