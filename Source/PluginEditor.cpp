/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
SinWaveAudioProcessorEditor::SinWaveAudioProcessorEditor (SinWaveAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p), myGui(p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (400, 200);
    addAndMakeVisible(&myGui);
}

SinWaveAudioProcessorEditor::~SinWaveAudioProcessorEditor()
{
}

//==============================================================================
void SinWaveAudioProcessorEditor::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll(Colours::black);
}

void SinWaveAudioProcessorEditor::resized()
{
    Rectangle<int> area = getLocalBounds();
    const int componentWidth = 200;
    const int componentHeight = 200;

    
    myGui.setBounds(area.removeFromLeft(componentWidth).removeFromTop(componentHeight));
}
