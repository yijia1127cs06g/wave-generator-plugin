/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/
#include "PluginProcessor.h"
#include "PluginEditor.h"


//==============================================================================
SinWaveAudioProcessor::SinWaveAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", AudioChannelSet::stereo(), true)
                     #endif
                       ),
tree(*this, nullptr,"PARAMETERS",
     {std::make_unique<AudioParameterFloat>("wavetype", "WaveType", NormalisableRange<float>(0.0f, 3.0f), 0.0f)})
#endif
{
    //using Parameter = AudioProcessorValueTreeState::Parameter;
    //NormalisableRange<float> waveTypeParam (0, 3);
    //tree.createAndAddParameter(std::make_unique<Parameter>("wavetype", "WaveType", "wave", waveTypeParam, 0, nullptr, nullptr));
    
    mySythn.clearVoices();
    for (int i=0; i<5; i++)
    {
        mySythn.addVoice(new SineWaveVoice());
    }
    
    mySythn.clearSounds();
    mySythn.addSound(new SineWaveSound());
    
}

SinWaveAudioProcessor::~SinWaveAudioProcessor()
{
}

//==============================================================================
const String SinWaveAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool SinWaveAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool SinWaveAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool SinWaveAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double SinWaveAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int SinWaveAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int SinWaveAudioProcessor::getCurrentProgram()
{
    return 0;
}

void SinWaveAudioProcessor::setCurrentProgram (int index)
{
}

const String SinWaveAudioProcessor::getProgramName (int index)
{
    return {};
}

void SinWaveAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void SinWaveAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    ignoreUnused(samplesPerBlock);
    lastSampleRate = sampleRate;
    mySythn.setCurrentPlaybackSampleRate(lastSampleRate);
}

void SinWaveAudioProcessor::releaseResources()
{
    
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool SinWaveAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void SinWaveAudioProcessor::processBlock (AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
    
    for (int i = 0; i<mySythn.getNumVoices(); i++)
    {
        if ((SineVoice = dynamic_cast<SineWaveVoice*>(mySythn.getVoice(i))))
        {
            SineVoice->getWaveType(tree.getRawParameterValue("wavetype"));
        }
    }
    
    buffer.clear();
    mySythn.renderNextBlock(buffer, midiMessages, 0, buffer.getNumSamples());
}

//==============================================================================
bool SinWaveAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* SinWaveAudioProcessor::createEditor()
{
    return new SinWaveAudioProcessorEditor (*this);
}

//==============================================================================
void SinWaveAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void SinWaveAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new SinWaveAudioProcessor();
}








