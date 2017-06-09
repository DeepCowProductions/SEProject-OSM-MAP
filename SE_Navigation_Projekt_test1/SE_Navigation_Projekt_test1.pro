TEMPLATE = app

QT += qml quick network quick positioning location

CONFIG += c++11

SOURCES += main.cpp \
    src/settings.cpp \
    src/userdata.cpp \
    src/place.cpp \
    src/road.cpp \
    src/placesmodel.cpp \
    src/roadsmodel.cpp \
    src/OsmTilesOffline/tilesdownloader.cpp \
    src/OsmTilesOffline/tilereply.cpp \
    src/OsmTilesOffline/tile.cpp \
    src/OsmTilesOffline/tileofflinemanager.cpp \
    src/locationpin.cpp \
    src/teteteettetet.cpp
    src/OsmTilesOffline/downloadthread.cpp

RESOURCES += qml.qrc \
    res.qrc \
    icons.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    src/settings.h \
    src/userdata.h \
    src/place.h \
    src/road.h \
    src/placesmodel.h \
    src/roadsmodel.h \
    src/OsmTilesOffline/tilesdownloader.h \
    src/OsmTilesOffline/tilereply.h \
    src/OsmTilesOffline/tile.h \
    src/OsmTilesOffline/tileofflinemanager.h \
    src/Singleton/networkaccesmanagersingleton.hpp \
    src/locationpin.h \
    src/teteteettetet.h
    src/OsmTilesOffline/downloadthread.h

DISTFILES += \
    dump
