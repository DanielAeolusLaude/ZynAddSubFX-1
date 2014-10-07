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

#include "extra/d_string.hpp"

#define NTK_GUI
#define CARLA_VERSION_STRING
#define PLUGINVERSION
#define SOURCE_DIR "/usr/share/zynaddsubfx/examples"
#undef override

using DISTRHO_NAMESPACE::d_string;

d_string gUiPixmapPath;

// zynaddsubfx ui includes
#include "common/UI/NioUI.cpp"
#include "common/UI/WidgetPDial.cpp"
#include "common/UI/ADnoteUI.cpp"
#include "common/UI/BankUI.cpp"
#include "common/UI/ConfigUI.cpp"
#include "common/UI/EffUI.cpp"
#include "common/UI/EnvelopeUI.cpp"
#include "common/UI/FilterUI.cpp"
#include "common/UI/LFOUI.cpp"
#include "common/UI/MasterUI.cpp"
#include "common/UI/MicrotonalUI.cpp"
#include "common/UI/OscilGenUI.cpp"
#include "common/UI/PADnoteUI.cpp"
#include "common/UI/PartUI.cpp"
#include "common/UI/PresetsUI.cpp"
#include "common/UI/ResonanceUI.cpp"
#include "common/UI/SUBnoteUI.cpp"
#include "common/UI/VirKeyboard.cpp"
