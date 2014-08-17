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

#ifndef DISTRHO_PLUGIN_ZYNADDSUBFX_HPP_INCLUDED
#define DISTRHO_PLUGIN_ZYNADDSUBFX_HPP_INCLUDED

#include "DistrhoPlugin.hpp"

#include "../common/Misc/Master.h"

class MasterUI;

START_NAMESPACE_DISTRHO

class DistrhoUIZynAddSubFX;

// -----------------------------------------------------------------------

class DistrhoPluginZynAddSubFX : public Plugin
{
public:
    enum Parameters
    {
        paramCount = 0
    };

    DistrhoPluginZynAddSubFX();
    ~DistrhoPluginZynAddSubFX() override;

protected:
    // -------------------------------------------------------------------
    // Information

    const char* d_getLabel() const noexcept override
    {
        return "ZynAddSubFX";
    }

    const char* d_getMaker() const noexcept override
    {
        return "Nasca Octavian Paul, Mark McCurry, falkTX";
    }

    const char* d_getLicense() const noexcept override
    {
        return "GPL v2+";
    }

    uint32_t d_getVersion() const noexcept override
    {
        return 0x1000;
    }

    int64_t d_getUniqueId() const noexcept override
    {
        return d_cconst('Z', 'A', 'S', 'F');
    }

    // -------------------------------------------------------------------
    // Init

    void d_initParameter(uint32_t index, Parameter& parameter) override;
    void d_initStateKey(uint32_t index, d_string& stateKey) override;

    // -------------------------------------------------------------------
    // Internal data

    float d_getParameterValue(uint32_t index) const override;
    void  d_setParameterValue(uint32_t index, float value) override;
    void  d_setState(const char* key, const char* value) override;

    // -------------------------------------------------------------------
    // Process

    void d_run(const float**, float** outputs, uint32_t frames, const MidiEvent* midiEvents, uint32_t midiEventCount) override;

    // -------------------------------------------------------------------
    // Callbacks

    void d_bufferSizeChanged(uint32_t newBufferSize) override;
    void d_sampleRateChanged(double newSampleRate) override;

    // -------------------------------------------------------------------

private:
    Master* fMaster;
    //MasterUI* fMasterUI;
    uint    fSampleRate;

    DistrhoUIZynAddSubFX* fUI;

    void _initMaster();
    void _deleteMaster();

    friend class DistrhoUIZynAddSubFX;

    DISTRHO_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(DistrhoPluginZynAddSubFX)
};

// -----------------------------------------------------------------------

END_NAMESPACE_DISTRHO

#endif  // DISTRHO_PLUGIN_ZYNADDSUBFX_HPP_INCLUDED
