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

#ifndef DISTRHO_PLUGIN_INFO_H_INCLUDED
#define DISTRHO_PLUGIN_INFO_H_INCLUDED

#define DISTRHO_PLUGIN_NAME "ZynAddSubFX"

#define DISTRHO_PLUGIN_HAS_UI        1
#define DISTRHO_PLUGIN_IS_SYNTH      1

#define DISTRHO_PLUGIN_NUM_INPUTS    0
#define DISTRHO_PLUGIN_NUM_OUTPUTS   2

#define DISTRHO_PLUGIN_WANT_DIRECT_ACCESS 1
#define DISTRHO_PLUGIN_WANT_LATENCY       0
#define DISTRHO_PLUGIN_WANT_PROGRAMS      0
#define DISTRHO_PLUGIN_WANT_STATE         1
#define DISTRHO_PLUGIN_WANT_TIMEPOS       0

#define DISTRHO_PLUGIN_URI "http://zynaddsubfx.sourceforge.net/"

#define DISTRHO_UI_USE_NTK 1

#endif // DISTRHO_PLUGIN_INFO_H_INCLUDED
