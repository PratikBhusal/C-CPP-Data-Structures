# -----------------------------------------------------------------------------
# CMake project wrapper Makefile ----------------------------------------------
# -----------------------------------------------------------------------------

# SHELL := /bin/bash
SHELL := $(ComSpec)
BIN_DIR := output

# RM    := rm -rf
# MKDIR := mkdir -p
MAKE := make -C build/ --no-print-directory

MKDIR := mkdir

.PHONY: all
all: debug release

.PHONY: run
run:
	@$(MAKE) run

.PHONY: gdb
gdb: debug
	@$(MAKE) gdb

.PHONY: debug
debug: build/Makefile
	@$(MAKE) debug

.PHONY: release
release: build/Makefile
	@$(MAKE) release

build/Makefile: CMakeLists.txt
	mkdir build && cd build && cmake ..
test:
	@echo $(OS)
	@echo $(SHELL)
	@echo $(COMSPEC)
	@echo $(ComSpec)
