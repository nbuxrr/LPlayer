# ----------------------------------------------------
# This file is generated by the Qt Visual Studio Add-in.
# ------------------------------------------------------

TEMPLATE = app
TARGET = LPlayer
DESTDIR = ./bin
QT += core network widgets gui qml quick
CONFIG += release
DEFINES += _WINDOWS QT_QUICK_LIB QT_WIDGETS_LIB QT_QML_LIB QT_NETWORK_LIB
INCLUDEPATH += . \
    ./release \
    $(QTDIR)/mkspecs/win32-msvc2015 \
    ./thirdpart/vlc_sdk/include
LIBS += -L"./thirdpart/vlc_sdk/lib" \
    -L"../../../../../../../utils/postgresql/pgsql/lib" \
    -L"../../../../../../../utils/my_sql/my_sql/lib" \
    -lshell32 \
    -llibvlc \
    -llibvlccore
DEPENDPATH += .
MOC_DIR += ./GeneratedFiles/release
OBJECTS_DIR += release
UI_DIR += ./GeneratedFiles
RCC_DIR += ./GeneratedFiles
include(LPlayer.pri)
