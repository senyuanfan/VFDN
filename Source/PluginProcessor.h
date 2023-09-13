/*
  ==============================================================================

    This file was originally emitted for a "basic audio plugin" by Projucer.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

// Set this to 0 or 1:
// 0 - Use parameterChanged() in the usual way
// 1 - Refresh parameters once per audio block via raw pointers (like Faust does)
#define USE_RAW_POINTERS 0

// Set this to 0 or 1:
// 0 - do manual parameter layout as in Assignment 1
// 1 - create parameter layout automatically using ./FaustParameters.h
#define USE_FAUST_PARAMETERS_H 0

#include "VFDN.h" // Created in this directory by typing 'make' which uses ./Makefile

#if USE_FAUST_PARAMETERS_H == 1
#include "FaustParameters.h" // Includes a replacement for MapUI based on APIUI from ./FaustInterface.h
#define FAUST_PARAMETERS FaustParameters
#else
#define FAUST_PARAMETERS
#endif

// NOTE: Every Faust DSP module is a derived class of the class dsp, which is defined GLOBALLY in RingMod.h
// (because our architecture file faustMinimal.h includes /usr/local/include/faust/dsp/dsp.h).
// Sometimes the C++ compiler can confuse this with the juce::dsp:: namespace
// (which is defined when you are using the juce_dsp module).
// To resolve this ambiguity, you can say "::dsp" instead of "dsp" to direct the compiler
// to the global scope.
// The really right thing would be for the Faust distribution to define all its symbols inside
// a new "faust" namespace, so we would say "faust::dsp" in this case.
// However, this turns out to be a lot of work, so it's not done.
// Feel free to volunteer and be a hero!

//==============================================================================
/**
*/
class FaustAndJuceAudioProcessor  : public foleys::MagicProcessor
#if USE_RAW_POINTERS == 0
                                  , private juce::AudioProcessorValueTreeState::Listener
#endif
{
public:
    //==============================================================================
    FaustAndJuceAudioProcessor();
    ~FaustAndJuceAudioProcessor() override;

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    //==============================================================================
#if 0 // Let FaustAndJuce handle this:
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;
#endif
    //==============================================================================
    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;

    //==============================================================================
#if 0 // To override PGM and handle this ourselves:
    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;
#endif
#if USE_RAW_POINTERS == 0
    void parameterChanged (const juce::String& parameterPath, float newValue) override;
#endif

    //==============================================================================
    void runUnitTests(); // Call this to run unit tests (which halt on failure)

private:
    //==============================================================================

    VFDN vfdn;
#if USE_FAUST_PARAMETERS_H == 1
    FaustInterface vfdnUI;
#else
    MapUI vfdnUI;
#endif
    

    float* modFreqFaustP = nullptr;
    float* modWidthFaustP = nullptr;
    float* gainFaustP = nullptr;
    float* wetFaustP = nullptr;

#if USE_RAW_POINTERS == 1
    std::atomic<float>* modFreqGuiP = nullptr;
    std::atomic<float>* modWidthGuiP  = nullptr;
    std::atomic<float>* gainGuiP = nullptr;
    std::atomic<float>* wetGuiP = nullptr;
#endif

    // NOTE: ringModUI is "built" in createParameterLayout(), so
    // both it and ringMod must be already declared above:
    juce::AudioProcessorValueTreeState::ParameterLayout createParameterLayout();

    juce::AudioProcessorValueTreeState treeState;

    // New member variables go here

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FaustAndJuceAudioProcessor)
};
