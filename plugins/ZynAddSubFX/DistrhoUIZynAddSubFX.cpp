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

#include "DistrhoUIZynAddSubFX.hpp"

#include "../common/UI/common.H"
#include "../common/UI/MasterUI.h"

#include <FL/Fl_Dial.H>
#include <FL/Fl_Shared_Image.H>
#include <FL/Fl_Tiled_Image.H>
#include <FL/Fl_Theme.H>

using DISTRHO_NAMESPACE::d_string;

static Fl_Tiled_Image* gModuleBackdrop = nullptr;
static d_string gPixmapPath;
extern d_string gUiPixmapPath;

void set_module_parameters(Fl_Widget* o)
{
    DISTRHO_SAFE_ASSERT_RETURN(gModuleBackdrop != nullptr,);

    o->box(FL_DOWN_FRAME);
    o->align(o->align() | FL_ALIGN_IMAGE_BACKDROP);
    o->color(FL_BLACK);
    o->labeltype(FL_SHADOW_LABEL);
    o->image(gModuleBackdrop);
}

START_NAMESPACE_DISTRHO

// -----------------------------------------------------------------------

DistrhoUIZynAddSubFX::DistrhoUIZynAddSubFX()
    : UI(),
      fMasterUI(nullptr),
      fUiMutex(),
      fUiClosed(-1)
{
    DistrhoPluginZynAddSubFX* const plugin((DistrhoPluginZynAddSubFX*)d_getPluginInstancePointer());
    DISTRHO_SAFE_ASSERT_RETURN(plugin != nullptr,);

    initMaster(plugin->fMaster);
    plugin->fUI = this;
}

DistrhoUIZynAddSubFX::~DistrhoUIZynAddSubFX()
{
    if (DistrhoPluginZynAddSubFX* const plugin = (DistrhoPluginZynAddSubFX*)d_getPluginInstancePointer())
        plugin->fUI = nullptr;

    deleteMaster();
}

void DistrhoUIZynAddSubFX::initMaster(Master* const master)
{
    const MutexLocker ml(fUiMutex);

    DISTRHO_SAFE_ASSERT_RETURN(master != nullptr,);
    DISTRHO_SAFE_ASSERT_RETURN(fMasterUI == nullptr,);

    fMasterUI = new MasterUI(master, &fUiClosed);
    this->add(fMasterUI->masterwindow);
    fMasterUI->masterwindow->show();
}

void DistrhoUIZynAddSubFX::deleteMaster()
{
    const MutexLocker ml(fUiMutex);

    DISTRHO_SAFE_ASSERT_RETURN(fMasterUI != nullptr,);

    fMasterUI->masterwindow->hide();
    this->remove(fMasterUI->masterwindow);
    delete fMasterUI;
    fMasterUI = nullptr;
}

// -----------------------------------------------------------------------
// DSP Callbacks

void DistrhoUIZynAddSubFX::d_parameterChanged(uint32_t, float)
{
}

void DistrhoUIZynAddSubFX::d_stateChanged(const char* key, const char*)
{
    if (std::strcmp(key, "state") != 0)
        return;

    const MutexLocker sl(fUiMutex);

    if (fMasterUI != nullptr)
        fMasterUI->refresh_master_ui();
}

// -----------------------------------------------------------------------

UI* createUI()
{
    static bool initiated = false;

    if (! initiated)
    {
        initiated = true;

        // TODO: find pixmap path
        gPixmapPath = "/usr/share/zynaddsubfx/pixmaps/";
        gUiPixmapPath = gPixmapPath;

        Fl_Dial::default_style(Fl_Dial::PIXMAP_DIAL);

        if (Fl_Shared_Image* const img = Fl_Shared_Image::get(gPixmapPath + "knob.png"))
            Fl_Dial::default_image(img);

        if (Fl_Shared_Image* const img = Fl_Shared_Image::get(gPixmapPath + "window_backdrop.png"))
            Fl::scheme_bg(new Fl_Tiled_Image(img));

        if (Fl_Shared_Image* const img = Fl_Shared_Image::get(gPixmapPath + "module_backdrop.png"))
            gModuleBackdrop = new Fl_Tiled_Image(img);

        Fl::background(50, 50, 50);
        Fl::background2(70, 70, 70);
        Fl::foreground(255, 255, 255);

        //Fl_Theme::set("Cairo");
    }

    return new DistrhoUIZynAddSubFX();
}

// -----------------------------------------------------------------------

END_NAMESPACE_DISTRHO
