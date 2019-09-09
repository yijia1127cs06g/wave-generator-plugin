/*
  ==============================================================================

    myConponent.h
    Created: 21 Aug 2019 2:35:05am
    Author:  lika

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"

//==============================================================================
/*
*/
class myConponent    : public Component
{
public:
    myConponent(SinWaveAudioProcessor&);
    ~myConponent();

    void paint (Graphics&) override;
    void resized() override;
    
    //void comboBoxChanged (ComboBox*) override;

private:
    ComboBox menu;
    ScopedPointer <AudioProcessorValueTreeState::ComboBoxAttachment> waveSelection;
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    SinWaveAudioProcessor& processor;
    
    
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (myConponent)
};
