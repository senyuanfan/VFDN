#pragma once

/*
  FaustParameters.h
  Julius Smith <jos@ccrma.stanford.edu>
  2020-11-22
  License: MIT

  Static helper functions for Faust parameters:

  getParameterGroup(faustInterface, groupID) 
    Returns parameter info for a Faust class, as needed by JUCE.
    Returns a juce::AudioProcessorParameterGroup.
    Needed by PluginProcessor::createParameterLayout().

  setAllFaustParametersFromTreeState(faustInterface, groupID, treeState)
    JUCE to Faust parameter passing:
    Forwards JUCE parameters (in treeState) to corresponding Faust parameters.
    (Each parameter has an instance in both JUCE and the Faust DSP.)

  addParameterListeners(treeState, processor, faustInterface, groupID)
    Tells the APVTS treeState to add the processor as a listener to
    all parameters found in faustInterface, prepending the prefix
    groupID to the parameter name.

  getFaustParamName(parameterPath)
    strips away PGM path prefix, e.g., "Synth1:LFO1:Freq" -> "Freq"

  getFaustFloatP(parameterPath, faustUI)
    Returns a raw FAUSTFLOAT* pointer to the parameter named in
    parameterPath in Faust UI faustUI.
*/

#include <string.h>

#include "FaustInterface.h"

class FaustParameters {

public:

  static juce::ParameterID makeID(juce::String groupID, juce::String name, int parameterVersionHint) {
    return juce::ParameterID{ groupID + ":" + name, parameterVersionHint };
  }

  static juce::String makeStringID(juce::String groupID, juce::String name) {
    return groupID + ":" + name;
  }

  static juce::String makeName(juce::String groupID, juce::String name) {
    return groupID + ":" + name; // Include the group in the name because audio plugin parameter lists are generally flat
  }

  static juce::String makeNameFromID(juce::String name) {
    return name.fromLastOccurrenceOf(juce::String(":"),
                                     /* includeSubStringInResult */ false,
                                     /* ignoreCase */ false);
  }

  static std::unique_ptr<juce::AudioProcessorParameterGroup>
    getParameterGroup(FaustInterface& builtInterface, juce::String groupID) {

    auto parameterGroup = std::make_unique<juce::AudioProcessorParameterGroup>(groupID, groupID, "|");

    DBG(groupID << " Faust Parameters:");

    int nParams = builtInterface.getParamsCount();
    for (int i=0; i<nParams; i++) {
      std::string name = builtInterface.getParamLabel(i);
      // initialized in init(sampleRate) which happens in prepareToPlay():
      // float pVal = builtInterface.getParamValue(i);
      float pMin = builtInterface.getParamMin(i);
      float pMax = builtInterface.getParamMax(i);
      float pStep = builtInterface.getParamStep(i);
      float pInit = builtInterface.getParamInit(i); // init() sets Value to this
      DBG("\t" << name << ":\tdefault = " << pInit
          << ", range = (" << pMin << ", " << pMax << ") to accuracy "
          << pStep);
      //#define SUPPRESS_GATE_GAIN_FREQ_FAUST_PARAMETERS
#ifdef  SUPPRESS_GATE_GAIN_FREQ_FAUST_PARAMETERS
      if (name == "gate" || name == "gain" || name == "freq") {
        DBG("\t\t\t\thandled internally by noteOn (not in GUI)");
        continue;
      }
#endif
      FaustInterface::ItemType pType = builtInterface.getParamItemType(i);
      switch (pType) {
      case FaustInterface::kVSlider:
      case FaustInterface::kHSlider:
      case FaustInterface::kNumEntry: {
        if (pStep == 1.0f) { // pStep == 1.0f => use int:
          auto juceParam = std::make_unique <juce::AudioParameterInt>
            (makeID(groupID,name,1),makeName(groupID,name), pMin,pMax,pInit);
          parameterGroup->addChild (std::move(juceParam));
        } else { // pStep != 1.0f => use float:
          auto juceParam = std::make_unique <juce::AudioParameterFloat>
            (makeID(groupID,name,1),makeName(groupID,name),
             juce::NormalisableRange<float>(pMin, pMax, pStep), pInit);
          parameterGroup->addChild (std::move(juceParam));
        }
        break;
      }
      case FaustInterface::kCheckButton:
      case FaustInterface::kButton: {
        auto juceParam = std::make_unique <juce::AudioParameterBool>
          (makeID(groupID,name,1), makeName(groupID,name), pInit);
        parameterGroup->addChild (std::move(juceParam));
        break;
      }
      case FaustInterface::kHBargraph:
      case FaustInterface::kVBargraph: {
        auto juceParam = std::make_unique <juce::AudioParameterFloat>
          (makeID(groupID,name,1), makeName(groupID,name), pMin,pMax,pInit);
        parameterGroup->addChild (std::move(juceParam));
        break;
      }
      default: {
        std::cout << "*** FaustParameters: getParameterGroup: Unknown Faust parameter type " << pType << std::endl;
        break;
      }
      }
    }

    return parameterGroup;
  }

  static void setAllFaustParametersFromTreeState(FaustInterface& builtInterface,
                                                 juce::String groupID,
                                                 juce::AudioProcessorValueTreeState& treeState)
  {
    DBG(juce::String(" Setting all Faust Parameters for group ") << groupID);
    int nParams = builtInterface.getParamsCount();
    for (int i=0; i<nParams; i++) {
      const char* name = builtInterface.getParamLabel(i);
      juce::String pName = makeStringID(groupID, name);
#ifdef SUPPRESS_GATE_GAIN_FREQ_FAUST_PARAMETERS
      if (strcmp(name,"gate")==0 || strcmp(name,"gain")==0 || strcmp(name,"freq")==0) {
        DBG("FaustParameters.h: (gate,gain,freq) presumed handled internally by noteOn and omitted from GUI");
        continue;
      }
#endif
      std::atomic<float>* pValP = treeState.getRawParameterValue(pName); // JUCE param
      float pVal = 0.0f;
      if (pValP != nullptr) {
        pVal = *pValP;
      } else {
        DBG("*** FaustParameters.h: Parameter " << pName << " NOT FOUND in treeState");
      }
#if JOS_FAUST_PARAM_LOG == 1
      if (treeState.getParameter(pName) == (juce::RangedAudioParameter*)nullptr) { // JUCE param
        std::cerr << "*** FaustParameters.h: Cannot find parameter " << pName << " in treeState\n";
      } else {
        std::cout << "\t" << name << " <- " << pVal << "\n";
      }
#endif
      builtInterface.setParamValue (name, pVal); // forward to Faust param
    }
  }

  static void addParameterListeners(juce::AudioProcessorValueTreeState& treeState,
                                    juce::AudioProcessorValueTreeState::Listener* processor,
                                    FaustInterface& builtInterface,
                                    juce::String groupID)
  {
    DBG(juce::String(" Setting up all Faust Parameter Listeners for group ") << groupID);
    int nParams = builtInterface.getParamsCount();
    for (int i=0; i<nParams; i++) {
      const char* name = builtInterface.getParamLabel(i);
      juce::String pName = makeStringID(groupID, name);
#ifdef SUPPRESS_GATE_GAIN_FREQ_FAUST_PARAMETERS
      if (strcmp(name,"gate")==0 || strcmp(name,"gain")==0 || strcmp(name,"freq")==0) {
        continue;
      }
#endif
      treeState.addParameterListener(pName, processor);
    }
  }

  /** strip away PGM path prefix, e.g., "Synth1:LFO1:Freq" -> "Freq" */
  static juce::String getFaustParamName(const juce::String &parameterPath)
  {
    juce::String paramName = parameterPath.fromLastOccurrenceOf(":", /* include : */ false, /* ignoreCase */ true);
    return paramName;
  }

  /** return address of Faust parameter with the given name path in the given UI */
  static FAUSTFLOAT* getFaustFloatP(const juce::String &parameterPath, FaustInterface& faustUI)
  {
    juce::String paramName = getFaustParamName(parameterPath);
    // For MapUI, you can call getParamZone(const std::string& str) directly. Here assume APIUI style UI:
    int paramIndex = faustUI.getParamIndex(paramName.getCharPointer());
    if (paramIndex < 0) {
      DBG("*** FaustAndJuceAudioProcessor::getFaustFloatP: Parameter " << parameterPath << " NOT FOUND");
      return nullptr;
    }
    FAUSTFLOAT* paramAddress = faustUI.getParamZone(paramIndex);
    jassert (paramAddress != nullptr);
    return paramAddress;
  }

};
