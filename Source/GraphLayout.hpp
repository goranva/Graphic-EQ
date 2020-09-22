//
//  GraphLayout.hpp
//  grapher 
//
//  Created by Jesus Turrubiates on 2020-08-22.
//

#ifndef GraphLayout_hpp
#define GraphLayout_hpp

#include <stdio.h>

#include <JuceHeader.h>
#include <array>

// axis
class BackgroundAndAxis : public juce::Component
{
public:
    BackgroundAndAxis(){}
    ~BackgroundAndAxis(){}
    void paint (Graphics& g) override;
    
    int dBLimit = 0;
    
private:
    void paintFreqLines (Graphics& g);
    void paintDecibelLines (Graphics& g);
    
    int getX(int x);
    int getY(int y);
};

// labels

class DecibelsLabels : public juce::Component
{
public:
    DecibelsLabels(){}
    ~DecibelsLabels(){}
    void paint (Graphics& g) override;
    
    int reducedSize = 0;
    
    int dBLimit = 0;
private:
    double getYAtDecibel(double);
};

class FrequencyLabels : public juce::Component
{
public:
    FrequencyLabels(){}
    ~FrequencyLabels(){}
    void paint (Graphics& g) override;
    
    int reducedSize = 0;
private:
    double getXAtFrequency(double);
};

// knobs
class Knobs : public juce::Component
{
public:
    Knobs();
    ~Knobs(){}
    void paint (Graphics& g) override;
    
    void prepare(const dsp::ProcessSpec &spec);
    
    void resized() override;
    
    void computeCoefficients(int freq, double Q, double gain);
    
    // this is just for visualization, the actual filters need to obtain
    // the sampleRate from PluginProcessor
    int sampleRate;
    
    int reducedSize = 0;
    
    int dBLimit = 0;
    
private:
    double getXAtFrequency(double);
    void paintFreqResponse(Graphics& g);
    
    juce::dsp::IIR::Coefficients<float>::Ptr coeffs {nullptr};
    
    std::array<double, 5> coefficients {0.0, 0.0, 0.0, 0.0, 0.0};
    juce::dsp::IIR::Filter <float> peakFilter;
    
    std::vector<double> frequencyMap;
    std::vector<double> decibelMap;
};

// Graph UI
class GraphComponent : public juce::Component
{
public:
    GraphComponent()
    {
        addAndMakeVisible(backgroundAxis);
        addAndMakeVisible(decibelLabels);
        addAndMakeVisible(frequencyLabels);
        addAndMakeVisible(knobs);
        
        decibelLabels.reducedSize = reducedSize;
        frequencyLabels.reducedSize = reducedSize;
        knobs.reducedSize = reducedSize;
        
        backgroundAxis.dBLimit = dBLimit;
        decibelLabels.dBLimit = dBLimit;
        knobs.dBLimit = dBLimit;
    }
    ~GraphComponent(){}
    void paint (Graphics& g) override;
    void resized() override;
    
    int sampleRate = 0;
    
    int reducedSize = 5;
    
    int dBLimit = 25;
private:
    double getXAtFrequency(double);
    
    BackgroundAndAxis backgroundAxis;
    DecibelsLabels decibelLabels;
    FrequencyLabels frequencyLabels;
    Knobs knobs;
};


#endif /* GraphLayout_hpp */
