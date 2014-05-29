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

START_NAMESPACE_DISTRHO

// -----------------------------------------------------------------------

DistrhoUIZynAddSubFX::DistrhoUIZynAddSubFX()
    : UI()
{
    // background
    fImgBackground = Image(DistrhoArtworkZynAddSubFX::backgroundData, DistrhoArtworkZynAddSubFX::backgroundWidth, DistrhoArtworkZynAddSubFX::backgroundHeight, GL_BGR);
}

// -----------------------------------------------------------------------
// DSP Callbacks

void DistrhoUIZynAddSubFX::d_parameterChanged(uint32_t /*index*/, float /*value*/)
{
}

// -----------------------------------------------------------------------
// Widget Callbacks

void DistrhoUIZynAddSubFX::onDisplay()
{
    fImgBackground.draw();
}

// -----------------------------------------------------------------------

UI* createUI()
{
    return new DistrhoUIZynAddSubFX();
}

// -----------------------------------------------------------------------

END_NAMESPACE_DISTRHO
