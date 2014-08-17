/*
 * Carla Native Plugins
 * Copyright (C) 2012-2014 Filipe Coelho <falktx@falktx.com>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * For a full copy of the GNU General Public License see the doc/GPL.txt file.
 */

#include "src/DistrhoDefines.h"

// zynaddsubfx includes
#include "common/DSP/AnalogFilter.cpp"
#include "common/DSP/FFTwrapper.cpp"
#include "common/DSP/Filter.cpp"
#include "common/DSP/FormantFilter.cpp"
#include "common/DSP/SVFilter.cpp"
#include "common/DSP/Unison.cpp"
#include "common/Effects/Alienwah.cpp"
#include "common/Effects/Chorus.cpp"
#include "common/Effects/Distorsion.cpp"
#include "common/Effects/DynamicFilter.cpp"
#include "common/Effects/Echo.cpp"
#include "common/Effects/Effect.cpp"
#include "common/Effects/EffectLFO.cpp"
#include "common/Effects/EffectMgr.cpp"
#include "common/Effects/EQ.cpp"
#include "common/Effects/Phaser.cpp"
#include "common/Effects/Reverb.cpp"
#include "common/Misc/Bank.cpp"
#include "common/Misc/Config.cpp"
#include "common/Misc/Dump.cpp"
#include "common/Misc/Master.cpp"
#include "common/Misc/Microtonal.cpp"
#include "common/Misc/Part.cpp"
#include "common/Misc/Recorder.cpp"
//#include "common/Misc/Stereo.cpp"
#include "common/Misc/Util.cpp"
#include "common/Misc/WavFile.cpp"
#include "common/Misc/WaveShapeSmps.cpp"
#include "common/Misc/XMLwrapper.cpp"
#include "common/Params/ADnoteParameters.cpp"
#include "common/Params/Controller.cpp"
#include "common/Params/EnvelopeParams.cpp"
#include "common/Params/FilterParams.cpp"
#include "common/Params/LFOParams.cpp"
#include "common/Params/PADnoteParameters.cpp"
#include "common/Params/Presets.cpp"
#include "common/Params/PresetsArray.cpp"
#include "common/Params/PresetsStore.cpp"
#include "common/Params/SUBnoteParameters.cpp"
#include "common/Synth/ADnote.cpp"
#include "common/Synth/Envelope.cpp"
#include "common/Synth/LFO.cpp"
#include "common/Synth/OscilGen.cpp"
#include "common/Synth/PADnote.cpp"
#include "common/Synth/Resonance.cpp"
#include "common/Synth/SUBnote.cpp"
#include "common/Synth/SynthNote.cpp"

// Dummy variables and functions for linking purposes
const char* instance_name = nullptr;
SYNTH_T* synth = nullptr;
class WavFile;
namespace Nio {
   bool start(void){return 1;}
   void stop(void){}
   bool setSource(std::string){return true;}
   bool setSink(std::string){return true;}
   std::set<std::string> getSources(void){return std::set<std::string>();}
   std::set<std::string> getSinks(void){return std::set<std::string>();}
   std::string getSource(void){return "";}
   std::string getSink(void){return "";}
   void waveNew(WavFile*){}
   void waveStart(void){}
   void waveStop(void){}
   void waveEnd(void){}
}
