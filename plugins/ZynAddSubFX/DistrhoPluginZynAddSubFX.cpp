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

START_NAMESPACE_DISTRHO

// -----------------------------------------------------------------------

DistrhoPluginZynAddSubFX::DistrhoPluginZynAddSubFX()
    : Plugin(paramCount, 0, 0) // 0 programs, 0 states
{
    // reset
    d_deactivate();
}

DistrhoPluginZynAddSubFX::~DistrhoPluginZynAddSubFX()
{
}

// -----------------------------------------------------------------------
// Init

void DistrhoPluginZynAddSubFX::d_initParameter(uint32_t /*index*/, Parameter& /*parameter*/)
{
}

// -----------------------------------------------------------------------
// Internal data

float DistrhoPluginZynAddSubFX::d_getParameterValue(uint32_t /*index*/) const
{
    return 0.0f;
}

void DistrhoPluginZynAddSubFX::d_setParameterValue(uint32_t /*index*/, float /*value*/)
{
}

// -----------------------------------------------------------------------
// Process

void DistrhoPluginZynAddSubFX::d_activate()
{
}

void DistrhoPluginZynAddSubFX::d_deactivate()
{
}

void DistrhoPluginZynAddSubFX::d_run(const float**, float** outputs, uint32_t frames, const MidiEvent* /*midiEvents*/, uint32_t /*midiEventCount*/)
{
    std::memset(outputs[0], 0, sizeof(float)*frames);
    std::memset(outputs[1], 0, sizeof(float)*frames);
}

// -----------------------------------------------------------------------

Plugin* createPlugin()
{
    return new DistrhoPluginZynAddSubFX();
}

// -----------------------------------------------------------------------

END_NAMESPACE_DISTRHO
