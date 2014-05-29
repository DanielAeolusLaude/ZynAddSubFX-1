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

#ifndef DISTRHO_UI_ZYNADDSUBFX_HPP_INCLUDED
#define DISTRHO_UI_ZYNADDSUBFX_HPP_INCLUDED

#include "DistrhoUI.hpp"

#include "DistrhoArtworkZynAddSubFX.hpp"

START_NAMESPACE_DISTRHO

// -----------------------------------------------------------------------

class DistrhoUIZynAddSubFX : public UI
{
public:
    DistrhoUIZynAddSubFX();

protected:
    // -------------------------------------------------------------------
    // Information

    uint d_getWidth() const noexcept override
    {
        return DistrhoArtworkZynAddSubFX::backgroundWidth;
    }

    uint d_getHeight() const noexcept override
    {
        return DistrhoArtworkZynAddSubFX::backgroundHeight;
    }

    // -------------------------------------------------------------------
    // DSP Callbacks

    void d_parameterChanged(uint32_t index, float value) override;

    // -------------------------------------------------------------------
    // Widget Callbacks

    void onDisplay() override;

private:
    Image fImgBackground;

    DISTRHO_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(DistrhoUIZynAddSubFX)
};

// -----------------------------------------------------------------------

END_NAMESPACE_DISTRHO

#endif // DISTRHO_UI_ZYNADDSUBFX_HPP_INCLUDED
