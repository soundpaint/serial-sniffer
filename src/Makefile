# serial-sniffer -- a serial port sniffer and logger
#
# Copyright (C) 2021 Jürgen Reuter
#
# This program is free software: you can redistribute it and/or
# modify it under the terms of the GNU General Public License as
# published by the Free Software Foundation, either version 3 of the
# License, or (at your option) any later version.
#
# This program is distributed in the hope that it will be useful, but
# WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
# General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see
# <https://www.gnu.org/licenses/>.
#
# For updates and more info or contacting the author, visit:
# <https://github.com/soundpaint/serial-sniffer>
#
# Author's web site: www.juergen-reuter.de

ROOT=..

include ../defs.mk
include qt5.mk

SH=sh -c
CPP=c++
MY_CXX_OPTS=-std=c++17 -Wall -pedantic -g -O0 $(LOCAL_CXX_OPTS)
MY_LD_OPTS=$(LOCAL_LD_OPTS)

LOCAL_CXX_OPTS=-fPIC
LOCAL_LD_OPTS=-fPIC $(MY_MOC_FILES)
MY_BIN_FILES=$(BUILD_BIN)/serial-sniffer

MY_QT5_OBJ_FILES = \
  about-dialog.o app-control.o config-panel.o \
  control-console-logger-panel.o control-file-logger-panel.o \
  control-panel.o control-serial-ports-panel.o \
  file-menu.o help-menu.o license-dialog.o \
  log-config-panel.o log-panel.o log-panel-list.o log-panel-list-updater.o \
  main-window.o menu-bar.o qt-actions.o serial-config-panel.o \
  serial-config-data-bits-panel.o serial-config-parity-bit-panel.o \
  serial-config-stop-bits-panel.o serial-sniffer.o

MY_MOC_FILES=$(patsubst %.o,$(BUILD)/obj/%.moc.o,$(MY_QT5_OBJ_FILES))

MY_OBJ_FILES = \
  $(patsubst %.o,$(BUILD_OBJ)/%.o, \
  abstract-config-reader.o config.o config-reader.o config-writer.o \
  file-logger.o key-bindings.o line-in.o line-out.o log.o line.o \
  serial-event.o serial-event-default-filter.o serial-event-filter.o \
  serial-event-pass-all-filter.o streamer-thread.o time-utils.o uart.o \
  xml-node-list.o xml-parser-error-handler.o \
  $(MY_QT5_OBJ_FILES))

LIB_OBJ_FILES=
MY_INCLUDE_DIRS=-I$(QT5_INCLUDE_DIR) -I$(BUILD_SRC) -I.
MY_LIB_DIRS =

MY_LIBS = \
  -lpthread -lusb -lX11 -lxerces-c -lQt5Core -lQt5Widgets -lQt5Gui -lm \
  -lboost_system -lboost_filesystem

CONFIG_XML=$(BUILD_BIN)/config.xml
CONFIG_XSD=$(BUILD_BIN)/config.xsd
STYLE_QSS=$(BUILD_BIN)/style.qss

all: $(CONFIG_XML) $(CONFIG_XSD) $(STYLE_QSS) $(MY_BIN_FILES)

$(BUILD_SRC):
	mkdir -p $@

$(BUILD_OBJ):
	mkdir -p $@

$(BUILD_BIN):
	mkdir -p $@

$(CONFIG_XML): $(SRC)/config.xml
	cp -pf $< $@

$(CONFIG_XSD): $(SRC)/config.xsd
	cp -pf $< $@

$(STYLE_QSS): $(SRC)/style.qss
	cp -pf $< $@

$(BUILD_SRC)/%.moc.cc: %.hh | $(BUILD_SRC)
	$(MOC) -I. -o $@ $<

$(BUILD_OBJ)/about-dialog.o: $(BUILD_SRC)/ABOUT.h

$(BUILD_OBJ)/license-dialog.o: $(BUILD_SRC)/COPYING.h

include common.mk

.SECONDARY: #keep intermediate files

.SUFFIXES:

#  Local Variables:
#    coding:utf-8
#    mode:Makefile
#  End:
