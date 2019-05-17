CHIP ?= gap8

all:
	cat pmsis.dxy.in | sed s/@CHIP_CONFIG@/$(CHIP)/ > pmsis.dxy
	doxygen pmsis.dxy