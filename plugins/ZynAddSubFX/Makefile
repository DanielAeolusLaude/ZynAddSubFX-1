#!/usr/bin/make -f
# Makefile for DISTRHO Plugins #
# ---------------------------- #
# Created by falkTX
#

# --------------------------------------------------------------
# Project name, used for binaries

NAME = ZynAddSubFX

# --------------------------------------------------------------
# Files to build

OBJS_DSP = \
	DistrhoPluginZynAddSubFX.cpp.o \
	../zynaddsubfx-src.cpp.o

OBJS_UI  = \
	DistrhoUIZynAddSubFX.cpp.o \
	../zynaddsubfx-ui.cpp.o

# --------------------------------------------------------------
# Do some magic

include ../Makefile.mk

# --------------------------------------------------------------
# Enable all possible plugin types

ifeq ($(LINUX),true)
all: jack lv2 vst
else
all: dssi lv2 vst
endif

# --------------------------------------------------------------

ZYN_UI_FILES_CPP = \
	../common/UI/ADnoteUI.cpp \
	../common/UI/BankUI.cpp \
	../common/UI/ConfigUI.cpp \
	../common/UI/EffUI.cpp \
	../common/UI/EnvelopeUI.cpp \
	../common/UI/FilterUI.cpp \
	../common/UI/LFOUI.cpp \
	../common/UI/MasterUI.cpp \
	../common/UI/MicrotonalUI.cpp \
	../common/UI/OscilGenUI.cpp \
	../common/UI/PADnoteUI.cpp \
	../common/UI/PartUI.cpp \
	../common/UI/PresetsUI.cpp \
	../common/UI/ResonanceUI.cpp \
	../common/UI/SUBnoteUI.cpp \
	../common/UI/VirKeyboard.cpp

ZYN_UI_FILES_H = \
	../common/UI/ADnoteUI.h \
	../common/UI/BankUI.h \
	../common/UI/ConfigUI.h \
	../common/UI/EffUI.h \
	../common/UI/EnvelopeUI.h \
	../common/UI/FilterUI.h \
	../common/UI/LFOUI.h \
	../common/UI/MasterUI.h \
	../common/UI/MicrotonalUI.h \
	../common/UI/OscilGenUI.h \
	../common/UI/PADnoteUI.h \
	../common/UI/PartUI.h \
	../common/UI/PresetsUI.h \
	../common/UI/ResonanceUI.h \
	../common/UI/SUBnoteUI.h \
	../common/UI/VirKeyboard.h

# --------------------------------------------------------------

DistrhoPluginZynAddSubFX.cpp.o: DistrhoPluginZynAddSubFX.cpp
	$(CXX) $< $(BUILD_CXX_FLAGS) $(shell pkg-config --cflags fftw3 mxml zlib) -c -o $@

DistrhoUIZynAddSubFX.cpp.o: DistrhoUIZynAddSubFX.cpp $(ZYN_UI_FILES_H)
	$(CXX) $< $(BUILD_CXX_FLAGS) $(shell pkg-config --cflags ntk_images ntk) -c -o $@

../zynaddsubfx-src.cpp.o: ../zynaddsubfx-src.cpp $(ZYN_UI_FILES_H)
	$(CXX) $< $(BUILD_CXX_FLAGS) $(shell pkg-config --cflags fftw3 mxml zlib) -c -o $@

../zynaddsubfx-ui.cpp.o: ../zynaddsubfx-ui.cpp $(ZYN_UI_FILES_H) $(ZYN_UI_FILES_CPP)
	$(CXX) $< $(BUILD_CXX_FLAGS) $(shell pkg-config --cflags ntk_images ntk) -c -o $@

../common/UI/%.cpp: ../common/UI/%.fl
	ntk-fluid -c -o ../common/UI/$*.cpp -h ../common/UI/$*.h $<

../common/UI/%.h: ../common/UI/%.fl
	ntk-fluid -c -o ../common/UI/$*.cpp -h ../common/UI/$*.h $<

# --------------------------------------------------------------
