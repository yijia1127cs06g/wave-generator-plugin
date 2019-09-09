/*
  ==============================================================================

    myConponent.cpp
    Created: 21 Aug 2019 2:35:05am
    Author:  lika

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "myConponent.h"

//==============================================================================
myConponent::myConponent(SinWaveAudioProcessor& p):
processor(p)
{
    setSize(200, 200);
    
    menu.addItem("Sine", 1);
    menu.addItem("Saw", 2);
    menu.addItem("Square", 3);
    menu.addItem("Triangle", 4);
    menu.setJustificationType(Justification::centred);
    addAndMakeVisible(&menu);
    // menu.addListener(this);
    
    waveSelection = new AudioProcessorValueTreeState::ComboBoxAttachment (processor.tree, "wavetype", menu);
}

myConponent::~myConponent()
{
}

void myConponent::paint (Graphics& g)
{

}

void myConponent::resized()
{
    Rectangle<int> area = getLocalBounds().reduced(40);
    menu.setBounds(area.removeFromTop(20));
}
/*
void myConponent::comboBoxChanged (ComboBox* box)
{
    
}
*/
