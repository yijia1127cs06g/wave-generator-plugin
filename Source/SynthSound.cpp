/*
  ==============================================================================

    SynthSound.cpp
    Created: 31 Jul 2019 12:42:11am
    Author:  lika

  ==============================================================================
*/

#include "SynthSound.h"
bool SineWaveSound::appliesToNote (int midiNoteNumber)
{
    return true;
}

bool SineWaveSound::appliesToChannel (int midiChannel)
{
    return true;
}
