/*
  ==============================================================================

    SynthSound.h
    Created: 31 Jul 2019 12:42:11am
    Author:  lika

  ==============================================================================
*/

#pragma once
#include "../JuceLibraryCode/JuceHeader.h"


class SineWaveSound: public SynthesiserSound
{
public:
    bool appliesToNote (int /*midiNoteNumber*/);
    bool appliesToChannel (int /*midiChannel*/);
};
