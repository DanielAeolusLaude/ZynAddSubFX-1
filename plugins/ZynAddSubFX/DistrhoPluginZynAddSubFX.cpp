/*
 * DISTRHO ZynAddSubFX
 * Copyright (C) 2014 Filipe Coelho <falktx@falktx.com>
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
 * For a full copy of the GNU General Public License see the LICENSE file.
 */

#include "DistrhoPluginZynAddSubFX.hpp"
#include "DistrhoUIZynAddSubFX.hpp"

//#include "../common/DSP/FFTwrapper.h"
//#include "../common/Misc/Part.h"
#include "../common/Misc/Util.h"

#include <ctime>

START_NAMESPACE_DISTRHO

// -----------------------------------------------------------------------
// Manage global zyn data using a reference counter

class ZynAddSubFxInstanceCount
{
public:
    ZynAddSubFxInstanceCount()
        : fCount(0) {}

    ~ZynAddSubFxInstanceCount()
    {
        DISTRHO_SAFE_ASSERT(fCount == 0);
    }

    void addOne(const double sampleRate, const uint32_t bufferSize)
    {
        if (fCount++ == 0)
        {
            DISTRHO_SAFE_ASSERT(synth == nullptr);
            DISTRHO_SAFE_ASSERT(denormalkillbuf == nullptr);

            reinit(sampleRate, bufferSize);
        }
    }

    void removeOne()
    {
        if (--fCount == 0)
        {
            Master::deleteInstance();

            if (denormalkillbuf != nullptr)
            {
                delete[] denormalkillbuf;
                denormalkillbuf = nullptr;
            }

            if (synth != nullptr)
            {
                delete synth;
                synth = nullptr;
            }
        }
    }

    void reinit(const double sampleRate, const uint32_t bufferSize)
    {
        Master::deleteInstance();

        if (denormalkillbuf != nullptr)
        {
            delete[] denormalkillbuf;
            denormalkillbuf = nullptr;
        }

        if (synth != nullptr)
        {
            delete synth;
            synth = nullptr;
        }

        synth = new SYNTH_T();
        synth->buffersize = bufferSize;
        synth->samplerate = sampleRate;

        if (synth->buffersize > 32)
            synth->buffersize = 32;

        synth->alias();

        config.init();
        config.cfg.SoundBufferSize   = synth->buffersize;
        config.cfg.SampleRate        = synth->samplerate;
        config.cfg.GzipCompression   = 0;
        config.cfg.UserInterfaceMode = 1;

        sprng((std::time(nullptr)));

        denormalkillbuf = new float[synth->buffersize];
        for (int i=0; i < synth->buffersize; ++i)
            denormalkillbuf[i] = (RND - 0.5f) * 1e-16f;

        Master::getInstance();
    }

    void maybeReinit(const double sampleRate, const uint32_t bufferSize)
    {
        if (synth->buffersize == int(bufferSize) && synth->samplerate == uint(sampleRate))
            return;

        reinit(sampleRate, bufferSize);
    }

private:
    int fCount;

    DISTRHO_PREVENT_HEAP_ALLOCATION
    DISTRHO_DECLARE_NON_COPY_CLASS(ZynAddSubFxInstanceCount)
};

static ZynAddSubFxInstanceCount sInstanceCount;

// -----------------------------------------------------------------------

DistrhoPluginZynAddSubFX::DistrhoPluginZynAddSubFX()
    : Plugin(paramCount, 0, 1), // 0 programs, 1 states
      fMaster(nullptr),
      fSampleRate(d_getSampleRate()),
      fUI(nullptr)
{
    sInstanceCount.addOne(d_getSampleRate(), d_getBufferSize());
    _initMaster();
}

DistrhoPluginZynAddSubFX::~DistrhoPluginZynAddSubFX()
{
    _deleteMaster();
    sInstanceCount.removeOne();
}

// -----------------------------------------------------------------------
// Parameters (nothing yet)

void  DistrhoPluginZynAddSubFX::d_initParameter(uint32_t, Parameter&) {}
void  DistrhoPluginZynAddSubFX::d_setParameterValue(uint32_t, float)  {}
float DistrhoPluginZynAddSubFX::d_getParameterValue(uint32_t) const   { return 0.0f; }

// -----------------------------------------------------------------------
// State

void DistrhoPluginZynAddSubFX::d_initState(uint32_t index, d_string& stateKey, d_string& defaultStateValue)
{
    if (index != 0)
        return;

    stateKey = "state";
    defaultStateValue = "";
}

void DistrhoPluginZynAddSubFX::d_setState(const char* key, const char* value)
{
    if (std::strcmp(key, "state") != 0)
        return;

    //fThread.stopLoadProgramLater();
    fMaster->putalldata(const_cast<char*>(value), 0);
    fMaster->applyparameters(true);
}

#if 0 // to get state
{
    config.save();

    char* data = nullptr;
    fMaster->getalldata(&data);
    return data;
}
#endif

// -----------------------------------------------------------------------
// Process

void DistrhoPluginZynAddSubFX::d_run(const float**, float** outputs, uint32_t frames, const MidiEvent* midiEvents, uint32_t midiEventCount)
{
    if (pthread_mutex_trylock(&fMaster->mutex) != 0)
    {
        std::memset(outputs[0], 0, frames);
        std::memset(outputs[1], 0, frames);
        return;
    }

    for (uint32_t i=0; i < midiEventCount; ++i)
    {
        const MidiEvent& midiEvent(midiEvents[i]);
        const uint8_t* const midiData(midiEvent.data);

        const uint8_t status  = (midiData[0] >= 0x80 && midiData[0] < 0xF0) ? midiData[0] & 0xF0 : midiData[0];
        const char    channel = (midiData[0] >= 0x80 && midiData[0] < 0xF0) ? midiData[0] & 0x0F : 0;

        if (status == 0x80)
        {
            const char note = midiData[1];

            fMaster->noteOff(channel, note);
        }
        else if (status == 0x90)
        {
            const char note = midiData[1];
            const char velo = midiData[2];

            fMaster->noteOn(channel, note, velo);
        }
        else if (status == 0xA0)
        {
            const char note     = midiData[1];
            const char pressure = midiData[2];

            fMaster->polyphonicAftertouch(channel, note, pressure);
        }
        else if (status == 0xB0)
        {
            const int control = midiData[1];
            const int value   = midiData[2];

            fMaster->setController(channel, control, value);
        }
        else if (status == 0xE0)
        {
            const uint8_t lsb = midiData[1];
            const uint8_t msb = midiData[2];
            const int   value = ((msb << 7) | lsb) - 8192;

            fMaster->setController(channel, C_pitchwheel, value);
        }
    }

    fMaster->GetAudioOutSamples(frames, fSampleRate, outputs[0], outputs[1]);

    pthread_mutex_unlock(&fMaster->mutex);
}

void DistrhoPluginZynAddSubFX::d_bufferSizeChanged(uint32_t newBufferSize)
{
    config.save();
    char* data = nullptr;
    fMaster->getalldata(&data);

    if (fUI != nullptr)
        fUI->deleteMaster();

    _deleteMaster();
    sInstanceCount.maybeReinit(d_getSampleRate(), newBufferSize);
    _initMaster();

    fMaster->putalldata(data, 0);
    fMaster->applyparameters(true);
    std::free(data);

    if (fUI != nullptr)
        fUI->initMaster(fMaster);
}

void DistrhoPluginZynAddSubFX::d_sampleRateChanged(double newSampleRate)
{
    config.save();
    char* data = nullptr;
    fMaster->getalldata(&data);

    if (fUI != nullptr)
        fUI->deleteMaster();

    fSampleRate = newSampleRate;

    _deleteMaster();
    sInstanceCount.maybeReinit(newSampleRate, d_getBufferSize());
    _initMaster();

    fMaster->putalldata(data, 0);
    fMaster->applyparameters(true);
    std::free(data);

    if (fUI != nullptr)
        fUI->initMaster(fMaster);
}

void DistrhoPluginZynAddSubFX::_initMaster()
{
    fMaster = new Master();

    for (int i = 0; i < NUM_MIDI_PARTS; ++i)
        fMaster->partonoff(i, 1);
}

void DistrhoPluginZynAddSubFX::_deleteMaster()
{
    //ensure that everything has stopped
    pthread_mutex_lock(&fMaster->mutex);
    pthread_mutex_unlock(&fMaster->mutex);

    delete fMaster;
    fMaster = nullptr;
}

// -----------------------------------------------------------------------

Plugin* createPlugin()
{
    return new DistrhoPluginZynAddSubFX();
}

// -----------------------------------------------------------------------

END_NAMESPACE_DISTRHO
