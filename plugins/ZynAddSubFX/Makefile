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
	DistrhoPluginZynAddSubFX.cpp.o

OBJS_UI  = \
	DistrhoArtworkZynAddSubFX.cpp.o \
	DistrhoUIZynAddSubFX.cpp.o

# --------------------------------------------------------------
# Do some magic

include ../Makefile.mk

# --------------------------------------------------------------
# Enable all possible plugin types

ifeq ($(LINUX),true)

# only build jack for now, testing
all: jack
# all: jack dssi lv2_sep vst

else
all: dssi lv2_sep vst
endif

# --------------------------------------------------------------
