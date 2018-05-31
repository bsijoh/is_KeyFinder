#*************************************************************************
#
# Copyright 2011-2013 Ibrahim Sha'ath
#
# This file is part of KeyFinder.
#
# KeyFinder is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# KeyFinder is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with KeyFinder.  If not, see <http://www.gnu.org/licenses/>.
#
#*************************************************************************

# CURRENT DEPENDENCIES:
# qt               5.4.1
# libkeyfinder     2.2.1
#  \-> fftw        3.3.4
# libav            0.7.7
# taglib           1.10

QT += \
  core \
  gui \
  widgets \
  concurrent \
  network \
  xmlpatterns \
  xml

TEMPLATE = app
DEPENDPATH += .

CONFIG += c++11
CONFIG += static

include(./source/source.pri)
include(./forms/forms.pri)

CONFIG(test) {
  TARGET = KeyFinderTests
  include(./test/test.pri)
  SOURCES += $$PWD/test/main.cpp
  CONFIG += console
  CONFIG -= app_bundle
  LIBS += -lgtest
} else {
  TARGET = KeyFinder
  SOURCES += $$PWD/source/main.cpp
  include(./resources/resources.pri)
  UI_DIR = ui
}

OTHER_FILES += README

QMAKE_CXXFLAGS += -D__STDC_CONSTANT_MACROS # for libav

LIBS += -L/usr/local/lib
LIBS += -lkeyfinder
LIBS += -lfftw3
LIBS += -lavformat
LIBS += -lavcodec
LIBS += -lavutil
LIBS += -ltag
LIBS += -lz


target.path = $$[QT_INSTALL_PREFIX]/bin
INSTALLS += target

TRANSLATIONS = \
  $$PWD/translations/is_keyfinder_en_GB.ts \
  $$PWD/translations/is_keyfinder_bg.ts \
  $$PWD/translations/is_keyfinder_da.ts \
  $$PWD/translations/is_keyfinder_de.ts \
  $$PWD/translations/is_keyfinder_el.ts \
  $$PWD/translations/is_keyfinder_en_US.ts \
  $$PWD/translations/is_keyfinder_es.ts \
  $$PWD/translations/is_keyfinder_fr.ts \
  $$PWD/translations/is_keyfinder_he.ts \
  $$PWD/translations/is_keyfinder_hr.ts \
  $$PWD/translations/is_keyfinder_it.ts \
  $$PWD/translations/is_keyfinder_nl.ts \
  $$PWD/translations/is_keyfinder_pl.ts \
  $$PWD/translations/is_keyfinder_pt_BR.ts \
  $$PWD/translations/is_keyfinder_pt_PT.ts \
  $$PWD/translations/is_keyfinder_ru.ts \
  $$PWD/translations/is_keyfinder_ru_RU.ts \
  $$PWD/translations/is_keyfinder_sv.ts \
  $$PWD/translations/is_keyfinder_tr.ts \
  $$PWD/translations/is_keyfinder_vi.ts \
  $$PWD/translations/is_keyfinder_zh_CN.ts
