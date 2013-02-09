// ==================================================================================
// Copyright (c) 2012 HiFi-LoFi
//
// This is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.
// ==================================================================================

#ifndef _IRMANAGER_H
#define _IRMANAGER_H


#include "../JuceLibraryCode/JuceHeader.h"

#include "ChangeNotifier.h"
#include "Envelope.h"

#include <vector>


// Forward declarations;
class IRAgent;
class PluginAudioProcessor;


typedef std::vector<IRAgent*> IRAgentContainer;


class IRManager : public ChangeNotifier
{
public:
  IRManager(PluginAudioProcessor& processor, size_t inputChannels, size_t outputChannels);
  virtual ~IRManager();
  
  PluginAudioProcessor& getProcessor();
  const PluginAudioProcessor& getProcessor() const;
  
  void initialize(double sampleRate, size_t samplesToProcess);
  
  double getConvolverSampleRate() const;
  
  size_t getConvolverHeadBlockSize() const;
  size_t getConvolverTailBlockSize() const;
  
  IRAgent* getAgent(size_t inputChannel, size_t outputChannel) const;
  size_t getAgentCount() const;
  IRAgentContainer getAgents() const;
  void reset();
  
  void setStretch(double stretch);
  double getStretch() const;
  
  void setReverse(bool reverse);
  bool getReverse() const;
  
  void setEnvelope(const Envelope& envelope);
  Envelope getEnvelope() const; 
    
  size_t getMaxIRSampleCount() const;
  size_t getMaxFileSampleCount() const;
  double getMaxFileDuration() const;

  void setFileBeginSeconds(double fileBeginSeconds);
  double getFileBeginSeconds() const;
  
  void setPredelayMs(double predelayMs);
  double getPredelayMs() const;

  void updateConvolvers();
  
private:  
  PluginAudioProcessor& _processor;
  IRAgentContainer _agents;

  mutable juce::CriticalSection _mutex;
  double _stretch;
  bool _reverse;
  Envelope _envelope;
  double _convolverSampleRate;
  size_t _convolverHeadBlockSize;
  size_t _convolverTailBlockSize;
  double _fileBeginSeconds;
  double _predelayMs;
  juce::CriticalSection _irCalculationMutex;
  juce::ScopedPointer<juce::Thread> _irCalculation;
  
  // Prevent uncontrolled usage  
  IRManager(const IRManager&);
  IRManager& operator=(const IRManager&);
};

#endif // Header guard
