/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
GrapherAudioProcessorEditor::GrapherAudioProcessorEditor (GrapherAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
//    setResizable(true, true);
//    setResizeLimits(200, 120, 800, 300);
    setSize(700, 300);
    graphComponent.sampleRate = processor.getSampleRate();
    addAndMakeVisible(graphComponent);
}

GrapherAudioProcessorEditor::~GrapherAudioProcessorEditor()
{
}

void prepareToPlay (double sampleRate, int samplesPerBlock)
{
    
}

//==============================================================================
void GrapherAudioProcessorEditor::paint (Graphics& g)
{
    g.setGradientFill(juce::ColourGradient(juce::Colours::black.withAlpha(0.8f), getWidth() / 2, getHeight() / 4, juce::Colour(0x0d1121).withAlpha(0.9f), getWidth() / 2, 2* getHeight() / 3, false));
    g.fillAll();
}

void GrapherAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
    auto r = getLocalBounds();
    graphComponent.setBounds(r.reduced(5));
}
