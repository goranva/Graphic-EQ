//
//  GraphLayout.cpp
//  grapher
//
//  Created by Jesus Turrubiates on 2020-08-22.
//

#include "GraphLayout.hpp"
#include <complex>

void BackgroundAndAxis::paint (Graphics& g)
{
    // graph background
    g.fillAll(juce::Colours::black);
    // gridLines colour
    g.setColour(juce::Colour(0x111d41).withAlpha(0.99f));
    
    // paint Frequency Lines
    paintFreqLines(g);
    
    // gradient Frequency lines
    g.setGradientFill(juce::ColourGradient(juce::Colours::transparentBlack, getWidth() / 2, getHeight() / 2, juce::Colours::black, getWidth() / 2, getHeight(), false));
    g.fillAll();
    
    // paint Decibels Lines
    g.setColour(juce::Colour(0x111d41).withAlpha(0.99f));
    paintDecibelLines(g);
    
    // outline
    g.setColour(juce::Colours::grey.withAlpha(0.5f));
    g.drawRect(0, 0, getWidth(), getHeight(), 1.0);
}


void BackgroundAndAxis::paintFreqLines(Graphics& g)
{
    juce::Array<juce::Line<float>> lines;
    // numLines is 11 so 10000 is the last frequency Line to draw
    auto numLines = 11;
    double lineThickness = 0.99f;

    // conditionals looks ugly
    for (int i = 10; i < numLines * 1000; i = i < 100 ? i+10 : i < 1000 ? i+100 : i + 1000)
    {
        juce::Line<float> line(juce::Point<float> (getX(i),0), juce::Point<float> (getX(i), getHeight()));
        lines.add(line);
        g.drawLine (line, lineThickness);
    }
}

void BackgroundAndAxis::paintDecibelLines(Graphics& g)
{
    juce::Array<juce::Line<float>> lines;
    double lineThickness = 0.99f;

    // increment condition is to have -6, 3, 0, 3 ,6
    for (int i = -18; i < 36; i = (i + 6 > -6) && (i + 3 <= 6) ? i + 3 : i + 6)
    {
        juce::Line<float> line(juce::Point<float> (0, getY(i)), juce::Point<float> (getWidth(), getY(i)));
        lines.add(line);
        g.drawLine (line, lineThickness);
    }
}

int BackgroundAndAxis::getX(int x)
{
    return ((getWidth() - 0)*(log10(x) - log10(10)))/(log10(20000) - log10(10)) + 0;
}

int BackgroundAndAxis::getY(int y)
{
    // if it's zero should be in the middle
    if (y == 0) return getHeight()/2;
    
    // myabe change to jmap
    if (y < 0)
        return ((getHeight() - getHeight()/2)*(abs(y) - 0))/(dBLimit - 0) + getHeight()/2;
    else
        return ((getHeight()/2 - 0)*(abs(y) - dBLimit))/(0 - dBLimit) + 0;
}

//============================================================================================
void DecibelsLabels::paint (Graphics& g)
{
    // TODO: check reduced here, need to match with recuced in plugineditor
    auto r = getLocalBounds().reduced(reducedSize);
    g.fillAll(juce::Colours::transparentBlack);
    g.setColour (juce::Colours::white.withAlpha(0.5f));
    g.setFont (juce::Font ("Times New Roman", 10.0f, juce::Font::plain));
    
    int fontWidth = 20;
    int fontHeight = 12;
    
    g.drawText("24", 0, getYAtDecibel(24) - reducedSize, fontWidth, fontHeight, juce::Justification::centred);
    g.drawText("18", 0, getYAtDecibel(18) - reducedSize, fontWidth, fontHeight, juce::Justification::centred);
    g.drawText("12", 0, getYAtDecibel(12) - reducedSize, fontWidth, fontHeight, juce::Justification::centred);
    g.drawText("6", 0, getYAtDecibel(6) - reducedSize, fontWidth, fontHeight, juce::Justification::centred);
    g.drawText("3", 0, getYAtDecibel(3) - reducedSize, fontWidth, fontHeight, juce::Justification::centred);
    g.drawText ("0", 0, r.getHeight()/2, fontWidth, fontHeight, juce::Justification::centred);
    g.drawText("-3", 0, getYAtDecibel(-3) - reducedSize, fontWidth, fontHeight, juce::Justification::centred);
    g.drawText("-6", 0, getYAtDecibel(-6) - reducedSize, fontWidth, fontHeight, juce::Justification::centred);
    g.drawText("-12", 0, getYAtDecibel(-12) - reducedSize, fontWidth, fontHeight, juce::Justification::centred);
    g.drawText("-18", 0, getYAtDecibel(-18) - reducedSize, fontWidth, fontHeight, juce::Justification::centred);
    g.drawText("-24", 0, getYAtDecibel(-24) - reducedSize, fontWidth, fontHeight, juce::Justification::centred);
#if DEBUG
    g.setColour(juce::Colours::red.withAlpha(0.5f));
//    g.drawRect(getLocalBounds());
#endif
}

double DecibelsLabels::getYAtDecibel(double decibel)
{
    if (decibel > 0)
    {
        return ((getHeight()/2 - 0)*(decibel - dBLimit))/(0 - dBLimit) + 0;
    }
    else
    {
        return ((getHeight() - getHeight()/2)*(-decibel - 0))/(dBLimit - 0) + getHeight()/2;
    }
    return 0;
}
//============================================================================================

void FrequencyLabels::paint (Graphics& g)
{
    // TODO: check reduced here, need to match with recuced in plugineditor, not good
    g.fillAll(juce::Colours::transparentBlack);
    g.setColour (juce::Colours::white.withAlpha(0.5f));
    g.setFont (juce::Font ("Times New Roman", 10.0f, juce::Font::plain));
    
    int fontWidth = 20;
    int fontHeight = 12;
    
    g.drawText("20", getXAtFrequency(20) - reducedSize, 0, fontWidth, fontHeight, juce::Justification::centred);
    g.drawText("50", getXAtFrequency(50) - reducedSize, 0, fontWidth, fontHeight, juce::Justification::centred);
    g.drawText("100", getXAtFrequency(100) - reducedSize, 0, fontWidth, fontHeight, juce::Justification::centred);
    g.drawText("200", getXAtFrequency(200) - reducedSize, 0, fontWidth, fontHeight, juce::Justification::centred);
    g.drawText("500", getXAtFrequency(500) - reducedSize, 0, fontWidth, fontHeight, juce::Justification::centred);
    g.drawText("1K", getXAtFrequency(1000) - reducedSize, 0, fontWidth, fontHeight, juce::Justification::centred);
    g.drawText("2K", getXAtFrequency(2000) - reducedSize, 0, fontWidth, fontHeight, juce::Justification::centred);
    g.drawText("5K", getXAtFrequency(5000) - reducedSize, 0, fontWidth, fontHeight, juce::Justification::centred);
    g.drawText("10K", getXAtFrequency(10000) - reducedSize, 0, fontWidth, fontHeight, juce::Justification::centred);
    g.drawText("20K", getXAtFrequency(18000) - reducedSize, 0, fontWidth, fontHeight, juce::Justification::left);
#if DEBUG
    g.setColour(juce::Colours::red.withAlpha(0.5f));
//    g.drawRect(getLocalBounds());
#endif
}

double FrequencyLabels::getXAtFrequency(double frequency)
{
    return ((getWidth() - 0)*(log10(frequency) - log10(10)))/(log10(20000) - log10(10)) + 0;
}

//============================================================================================
Knobs::Knobs() :
peakFilter(juce::dsp::IIR::Coefficients<float>::makePeakFilter(44100, 440, 1.0, 1.0))
{
    peakFilter.reset();
    // this is just for VISUALIZATION. The actual sample rate for the filters need to be taken
    // from PluginProcessor
    sampleRate = 48000;
}

void Knobs::resized()
{
    // resize to the width of the container
    frequencyMap.resize(getWidth() + 1);
    decibelMap.resize(frequencyMap.size());

    // maps frequency range [10, 20000] to 0-width of the container
    for (auto i = 0; i < frequencyMap.size(); i++)
        frequencyMap[i] = std::pow(10.f, juce::jmap(float(i), 0.f, (float)getWidth(), (float)log10(10), (float)log10(20000)));
}

void Knobs::paint (Graphics& g)
{
    // this code is just an example. The knobs doesn't have movement here
    // you should implement a function to move the nobs
    // use jmap instead
    g.setColour (Colours::lightgreen);
    g.fillEllipse(getXAtFrequency(30) - reducedSize,((getHeight()/2 - 0)*(0 - dBLimit))/(0 - dBLimit) - reducedSize, 10, 10);
    
    g.setColour (Colours::lightblue);
    g.fillEllipse(getXAtFrequency(200) - reducedSize, ((getHeight()/2 - 0)*(0 - dBLimit))/(0 - dBLimit) - reducedSize, 10, 10);
    
    g.setColour (Colours::lightpink);
    g.fillEllipse(getXAtFrequency(1000) - reducedSize, ((getHeight()/2 - 0)*(12 - dBLimit))/(0 - dBLimit) - reducedSize, 10, 10);
    
    g.setColour (Colours::lightyellow);
    g.fillEllipse(getXAtFrequency(7000) - reducedSize, ((getHeight()/2 - 0)*(0 - dBLimit))/(0 - dBLimit) - reducedSize, 10, 10);
    
    paintFreqResponse(g);
}

void Knobs::paintFreqResponse(Graphics& g)
{
    // TODO: this is where you want to send your parameters from PluginProcessor
    // make a new function to listen for changes and remove this function from paint
    computeCoefficients(1000, 1.0, 12.0);
    
    juce::Path path;
    path.startNewSubPath(0, juce::jmap((float)decibelMap[0], (float)-dBLimit, (float)dBLimit, (float)getHeight(), 0.f));
    
    for (auto i = 1; i < decibelMap.size(); i++)
        path.lineTo(juce::jmap((float)std::log10(frequencyMap[i]), (float)log10(10), (float)log10(20000),
                               0.f, (float)getWidth()),
                               ((getHeight()/2 - 0)*(decibelMap[i] - dBLimit))/(0 - dBLimit) + 0);

    g.strokePath(path, juce::PathStrokeType(1.0f, juce::PathStrokeType::JointStyle::curved, juce::PathStrokeType::EndCapStyle::butt));
    
    g.setColour(juce::Colours::lightpink.withAlpha(0.3f));
    g.fillPath(path);
}

double Knobs::getXAtFrequency(double frequency)
{
    return ((getWidth() - 0)*(log10(frequency) - log10(10)))/(log10(20000) - log10(10)) + 0;
}

void Knobs::computeCoefficients(int freq, double Q, double gain)
{
    juce::dsp::IIR::Coefficients<float>::Ptr  coeffs = juce::dsp::IIR::Coefficients<float>::makePeakFilter (sampleRate, freq, Q, juce::Decibels::decibelsToGain(gain));
    
    coeffs->getMagnitudeForFrequencyArray(frequencyMap.data(), decibelMap.data(), frequencyMap.size(), sampleRate);
    
    for (auto i = 0; i < decibelMap.size(); i++)
        decibelMap[i] = juce::Decibels::gainToDecibels(decibelMap[i]);
}

//============================================================================================

double GraphComponent::getXAtFrequency(double frequency)
{
    auto r = backgroundAxis.getLocalBounds();
    return ((r.getWidth() - 0)*(log10(frequency) - log10(10)))/(log10(20000) - log10(10)) + 0;
}

void GraphComponent::paint (Graphics& g)
{
}

void GraphComponent::resized()
{
    auto r = getLocalBounds();
    backgroundAxis.setBounds(r.removeFromLeft(getWidth() - 60).removeFromTop(getHeight() - 60));
    decibelLabels.setBounds(getWidth()-60, 0, 20, getHeight()-60);
    frequencyLabels.setBounds(0, getHeight()-60, getWidth()-60, 12);
    
    auto rAxis = backgroundAxis.getLocalBounds();
    knobs.setBounds(rAxis);
}
