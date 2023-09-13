/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"

// ringModUI parameters:
//static juce::String freqPath { "RingMod:Freq" };
//static juce::String wetPath  { "RingMod:Wet"  };
//
//static juce::ParameterID freqID { freqPath, /* parameter version hint */ 1 };
//static juce::ParameterID wetID  { wetPath, /* parameter version hint */ 1 };

static juce::String modFreq { "VFDN:mod_freq" };
static juce::String modWidth { "VFDN:mod_width" };
static juce::String gain { "VFDN:gain" };
static juce::String wet { "VFDN:wet" };

static juce::ParameterID modFreqID { modFreq, 1 };
static juce::ParameterID modWidthID { modWidth, 1 };
static juce::ParameterID gainID { gain, 1 };
static juce::ParameterID wetID { wet, 1 };


#if USE_FAUST_PARAMETERS_H == 0
  /** strip away PGM path prefix, e.g., "Synth1:LFO1:Freq" -> "Freq" */
  static juce::String getFaustParamName(const juce::String &parameterPath)
  {
    juce::String paramName = parameterPath.fromLastOccurrenceOf(":", /* include : */ false, /* ignoreCase */ true);
    return paramName;
  }

  /** return address of Faust parameter with the given name path in the given UI */
  static FAUSTFLOAT* getFaustFloatP(const juce::String &parameterPath, MapUI& faustUI)
  {
    juce::String paramName = getFaustParamName(parameterPath);
    FAUSTFLOAT* paramAddress = faustUI.getParamZone(std::string(paramName.getCharPointer()));
    if (paramAddress == nullptr) {
      DBG("*** FaustAndJuceAudioProcessor::getFaustFloatP: Parameter " << parameterPath << " NOT FOUND");
      return nullptr;
    }
    jassert (paramAddress != nullptr);
    return paramAddress;
  }
#endif

juce::AudioProcessorValueTreeState::ParameterLayout FaustAndJuceAudioProcessor::createParameterLayout()
{
  juce::AudioProcessorValueTreeState::ParameterLayout layout;

    // Create your AudioProcessorParameters here

  // Build the RingMod user interface now.
  // When ./FaustParameters.h is used, we retrieve metadata such as
  // parameter names, min, max, and default value from the interface automatically
  // so it is all in one place.
    vfdn.buildUserInterface(&vfdnUI);
    
    modFreqFaustP = FAUST_PARAMETERS::getFaustFloatP(modFreq, vfdnUI);
    modWidthFaustP = FAUST_PARAMETERS::getFaustFloatP(modWidth, vfdnUI);
    gainFaustP = FAUST_PARAMETERS::getFaustFloatP(gain, vfdnUI);
    wetFaustP = FAUST_PARAMETERS::getFaustFloatP(wet, vfdnUI);
    
    jassert(modFreqFaustP);
    jassert(modWidthFaustP);
    jassert(gainFaustP);
    jassert(wetFaustP);

  // Add our plugin parameters to the layout:
#if USE_FAUST_PARAMETERS_H == 0
  // Use the method of Assignment 1 (FFT), now adding a module-name prefix "RingMod".
  // This is the standard JUCE pattern.
  // Usage last time: ../../../hw1-FFT/hw1-sol/HW1Analyzer/Source/PluginProcessor.cpp
    layout.add(std::make_unique< juce::AudioParameterFloat >(modFreq, "Modulation Frequency", juce::NormalisableRange< float >(0.0f, 10.0f, 0.1f), 5.0f));
    layout.add(std::make_unique< juce::AudioParameterFloat >(modWidth, "Modulation Width", juce::NormalisableRange< float >(0.0f, 0.5f, 0.01f), 0.02f));
    layout.add(std::make_unique< juce::AudioParameterFloat >(gain, "Gain (dB)", juce::NormalisableRange< float >(-70.0f, 20.0f, 0.1f), -40.0f));
    layout.add(std::make_unique< juce::AudioParameterFloat >(wet, "Mix", juce::NormalisableRange< float >(0.0f, 1.0f, 0.01f), 0.5f));
#else
  // Simplified method taking advantage of Faust parameter metadata to fully automate:
    layout.add(FAUST_PARAMETERS::getParameterGroup(vfdnUI,"VFDN")); // adds all Faust parameters found
#endif

  return layout;
}

//==============================================================================
FaustAndJuceAudioProcessor::FaustAndJuceAudioProcessor()
  : // One or two initializations:
#ifndef JucePlugin_PreferredChannelConfigurations
  foleys::MagicProcessor ( BusesProperties()
#if ! JucePlugin_IsMidiEffect
#if ! JucePlugin_IsSynth
                           .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
#endif
                           .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
#endif
                           ),
#endif
  treeState (*this, nullptr, ProjectInfo::projectName, createParameterLayout())
{
  // Constructor body begins:
  // Initialize Faust classes, parameters, etc.
  // Done in createParameterLayout: ringMod.buildUserInterface(&ringModUI);
  // magicState.setGuiValueTree(BinaryData::RingMod_xml, BinaryData::RingMod_xmlSize);
#if USE_RAW_POINTERS == 0
#if USE_FAUST_PARAMETERS_H == 0
  // Listen to the processor parameters which in turn listen to PGM
  // GUI elements via "parameter attachments":
    treeState.addParameterListener(modFreqID.getParamID(), this);
    treeState.addParameterListener(modWidthID.getParamID(), this);
    treeState.addParameterListener(gainID.getParamID(), this);
    treeState.addParameterListener(wetID.getParamID(), this);
    
#else
  FAUST_PARAMETERS::addParameterListeners(treeState,this,vfdnUI,"VFDN"); // one line for all parameters
#endif
#else // no listeners:
  modFreqGuiP = treeState.getRawParameterValue (modFreq);
  modWidthGuiP = treeState.getRawParameterValue (modWidth);
    gainGuiP = treeState.getRawParameterValue (gain);
    wetGuiP = treeState.getRawParameterValue (wet);
#endif

// Search for JUCE_UNIT_TEST in the JUCE distribution using your IDE to see how these are normally called
// (not every time in the constructor like this, but in a separate console app that can go in a GitHub Action etc.):
#if JUCE_UNIT_TESTS
  runUnitTests();
#endif
    
    // to load saved PGM layout
    magicState.setGuiValueTree(BinaryData::layout_xml, BinaryData::layout_xmlSize);
    
}

FaustAndJuceAudioProcessor::~FaustAndJuceAudioProcessor()
{
}

//==============================================================================
const juce::String FaustAndJuceAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool FaustAndJuceAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool FaustAndJuceAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool FaustAndJuceAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double FaustAndJuceAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int FaustAndJuceAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int FaustAndJuceAudioProcessor::getCurrentProgram()
{
    return 0;
}

void FaustAndJuceAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String FaustAndJuceAudioProcessor::getProgramName (int index)
{
    return {};
}

void FaustAndJuceAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void FaustAndJuceAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
  vfdn.init(sampleRate);
}

void FaustAndJuceAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool FaustAndJuceAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
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

#if 0
// Do MIDI and audio like this if minimized controller-to-sound latency is important:
// Untested pseudo-code:
  processBlock (... audioBuffer, ... midiMessages) {
    int currentTime = 0;
    for (auto mm : midiMessages ) {
    {
      juce::MidiMessage m = mm.getMessage();
      int nextEventTime = m.getTimeStampSamples(); // MIDI timestamp, 0 = start of buffer
      if (nextEventTime > currentTime) // compute audio to nextEventTime:
        faustModule.compute(nextEventTime - currentTime,
              faustBuffersAtCurrentTime()); // pointers into audioBuffer
      processMidiMessage(m); // JUCE parameters possibly set here
      currentTime = nextEventTime; // refresh Faust parameters from JUCE parameters:
      *faustParam1Address = *juceParamRawPointer1;
      *faustParam2Address = *juceParamRawPointer2;
      ...
    }
    int remainingSamples = audioBuffer.getNumSamples() - currentTime;
    faustModule.compute(remainingSamples, faustBuffersAtCurrentTime());
  }
#endif

void FaustAndJuceAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;

  int numSamples = buffer.getNumSamples();
  int numChannels = buffer.getNumChannels();
  int numChannelsFaust = vfdn.getNumOutputs();
  jassert(numChannelsFaust == vfdn.getNumInputs());
  jassert(numChannelsFaust == 1); // Otherwise make an array of instances, etc.

  // The JUCE MidiKeyboardComponent sends us MIDI events via PGM:
  // MIDI assignments to GUI elements using MIDI learn in PGM happen here as well,
  // but note that the assignments are not saved in either the layout or settings (TODO):
  magicState.processMidiBuffer (midiMessages, numSamples, /* injectKeyboardEvents */ true);

#if USE_RAW_POINTERS == 1 // Do it Faust style
  // Note: Here we update the parameters once per audio block, but in a high-performance
  // situation, we would update them after each group of MIDI messages at the same timestamp
    *modFreqFaustP = *modFreqGuiP;
    *modWidthFaustP = *modWdithGuiP;
    *gainFaustP = *gainGuiP;
    *wetFaustP = *wetGuiP;
#ifdef DEBUG
    // simple hack to print out parameters once per second:
    static int sampleCounter;
    sampleCounter += numSamples;
    if (sampleCounter > 44100) {
      sampleCounter = 0;
        DBG("\nParameter Freq = " << *modFreqFaustP);
        DBG("Parameter Width = " << *modWidthFaustP);
        DBG("Parameter Gain = " << *gainFaustP);
        DBG("Parameter Wet = " << *wetFaustP);
    }
#endif
#endif // else parameterChanged() already did any parameter changes

    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // This is here to avoid people getting screaming feedback
    // when they first compile a plugin, but obviously you don't need to keep
    // this code if your algorithm always overwrites all the output channels.
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    // This is the place where you'd normally do the guts of your plugin's
    // audio processing...
    // Make sure to reset the state if your inner loop is processing
    // the samples and the outer loop is handling the channels.
    // Alternatively, you can process the samples with the channels
    // interleaved by keeping the same state.
    // for (int channel = 0; channel < totalNumInputChannels; ++channel)
    // {
    //     auto* channelData = buffer.getWritePointer (channel);

    //     // ..do something to the data...
    // }

    float*const* writePointers = buffer.getArrayOfWritePointers();
    float* bufferPointersFaust[numChannelsFaust];
    for (int i=0; i<numChannelsFaust; i++)
      bufferPointersFaust[i] = writePointers[i];

    vfdn.compute(numSamples, bufferPointersFaust, bufferPointersFaust);
    
    if (numChannels > 1) {  // copy L ro R:
      buffer.copyFrom(1,0,buffer,0,0,numSamples);
    }
}

//==============================================================================
//bool FaustAndJuceAudioProcessor::hasEditor() const
//{
//    return true; // (change this to false if you choose to not supply an editor)
//}
//
//juce::AudioProcessorEditor* FaustAndJuceAudioProcessor::createEditor()
//{
//    return new FaustAndJuceAudioProcessorEditor (*this);
//}

//==============================================================================
#if 0 // Let FaustAndJuce handle this:

void FaustAndJuceAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void FaustAndJuceAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

#endif

#if USE_RAW_POINTERS == 0
void FaustAndJuceAudioProcessor::parameterChanged(const juce::String &parameterPath, float newValue)
{
  if (parameterPath == modFreq) {
    *modFreqFaustP = newValue;
  } else if (parameterPath == modWidth) {
    *modWidthFaustP = newValue;
  } else if (parameterPath == gain) {
      *gainFaustP = newValue;
  } else if (parameterPath == wet) {
      *wetFaustP = newValue;
  }
  DBG("Parameter " << parameterPath << " set to " << newValue);
}
#endif

void FaustAndJuceAudioProcessor::runUnitTests() {
  DBG ("-----------------------------------------------------------------");
  std::cout << "UnitTests.h: Out of the available UNIT-TEST categories:\n  ";
  for (auto c : juce::UnitTest::getAllCategories()) {
    std::cout << c << ", ";
  }
  DBG ("\nrunning the following unit tests:");

  juce::UnitTestRunner testRunner;
  // Can simply say this, but it's a lot: testRunner.runAllTests();
  auto tests = juce::UnitTest::getAllTests();
  for (auto t : tests) {
    auto cat = t->getCategory();
    auto test = t->getName();
    if (cat == "RingMods") { // see bottom of this file for test defs
      DBG("  " << cat << " / " << test);
      t->performTest(&testRunner);
    }
    // ... repeat for each category we want to see here ...
  }
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new FaustAndJuceAudioProcessor();
}


//==============================================================================
//                                  UNIT TESTS                                ||
//==============================================================================
// #if JUCE_UNIT_TESTS

// cf. /l/mfjj/modules/jos_juce/static/static_utilities.h:835
// cf. /l/mfjj/PGM/JUCE/modules/juce_core/unit_tests/juce_UnitTestCategories.h

      
//class FaustAndJuceAudioProcessorTests : public juce::UnitTest
//{
//public:
//  FaustAndJuceAudioProcessorTests() : juce::UnitTest ("FaustAndJuceAudioProcessor", "RingMods")
//  {}
//
//  //==============================================================================
//  void runTest() override
//  {
//    beginTest ("basic ring modulator test"); // write this to be _linked_ with this compilation
//    {
//      expect(1==1);
//      DBG("1 is in fact 1 for starters");
//#if USE_FAUST_PARAMETERS_H == 1
//      FaustInterface ringModUI;
//#else
//      MapUI ringModUI;
//#endif
//
//      RingMod ringMod;
//      ringMod.buildUserInterface(&ringModUI);
//
//// ringModUI must be "built" before caching its parameter pointers:
//      float* freqFaustP = FAUST_PARAMETERS::getFaustFloatP(freqPath, ringModUI);
//      float* wetFaustP = FAUST_PARAMETERS::getFaustFloatP(wetPath, ringModUI);
//
//      int numChannelsFaust = ringMod.getNumOutputs();
//      jassert(numChannelsFaust == ringMod.getNumInputs());
//      jassert(numChannelsFaust == 1); // Otherwise make an array of instances, etc.
//
//      jassert(ringModUI.getParamsCount() == 2);
//
//      float testFreqVal = 100.0f;
//      std::string freqParamName = std::string(FAUST_PARAMETERS::getFaustParamName(freqPath).getCharPointer());
//      ringModUI.setParamValue(freqParamName, testFreqVal);
//      jassert(testFreqVal == ringModUI.getParamValue(freqParamName));
//      jassert(testFreqVal == *freqFaustP);
//
//      float testWetVal = 0.01f;
//      std::string wetParamName = std::string(FAUST_PARAMETERS::getFaustParamName(wetPath).getCharPointer());
//      ringModUI.setParamValue(wetParamName, testWetVal);
//      jassert(testWetVal == ringModUI.getParamValue(wetParamName));
//      jassert(testWetVal == *wetFaustP);
//
//      testFreqVal = 200.0f;
//      ringModUI.setParamValue(freqParamName, testFreqVal);
//      jassert(testFreqVal == ringModUI.getParamValue(freqParamName));
//      jassert(testFreqVal == *freqFaustP);
//
//      testWetVal = 0.02f;
//      ringModUI.setParamValue(wetParamName, testWetVal);
//      jassert(testWetVal == ringModUI.getParamValue(wetParamName));
//      jassert(testWetVal == *wetFaustP);
//
//      float fs = 44100.0f;
//      ringMod.init(fs);
//
//      jassert(fs == ringMod.getSampleRate());
//
//      // ...
//    }
//    beginTest ("new FaustAndJuceAudioProcessor test");
//    {
//      expect(2==2);
//      DBG("2 is also 2, so things are looking good so far");
//      // Test something YOU wrote
//    }
//  }
//
//private:
//  //==============================================================================
//  /**
//   * Used to compare frequencies which should be audibly identical.
//   */
//  void expectEqualsWithinOneCent (double frequencyInHertzActual,
//                                  double frequencyInHertzExpected)
//  {
//    double ratio = frequencyInHertzActual / frequencyInHertzExpected;
//    double oneCent = 1.0005946;
//    expect (ratio < oneCent);
//    expect (ratio > 1.0 / oneCent);
//  }
//
//  /**
//   * Signal samples are floats between -1 and 1, so that absolute
//   * error can be used instead of relative error.
//   */
//  void expectEqualSignals (float f1, float f2, float tol=1.0e-7f)
//  {
//    double err = f1-f2;
//    expect(fabs(err) < tol);
//  }
//};
//
//static FaustAndJuceAudioProcessorTests FaustAndJuceAudioProcessorUnitTests;
//
//#endif // JUCE_UNIT_TESTS
//



