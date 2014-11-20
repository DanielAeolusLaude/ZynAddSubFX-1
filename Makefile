#!/usr/bin/make -f
# Makefile for DISTRHO Plugins #
# ---------------------------- #
# Created by falkTX
#

all: plugins gen

# --------------------------------------------------------------

plugins:
	$(MAKE) all -C plugins/ZynAddSubFX

gen: plugins dpf-ntk/utils/lv2_ttl_generator
	@$(CURDIR)/dpf-ntk/utils/generate-ttl.sh

dpf-ntk/utils/lv2_ttl_generator:
	$(MAKE) -C dpf-ntk/utils/lv2-ttl-generator

# --------------------------------------------------------------

clean:
	$(MAKE) clean -C dpf-ntk/utils/lv2-ttl-generator
	$(MAKE) clean -C plugins/ZynAddSubFX

# --------------------------------------------------------------

.PHONY: plugins
