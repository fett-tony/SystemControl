TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

###########################################################################
#                                                                         #
#       Meine einstellung immer ohne shadow build in QT creator!!!        #
#                                Start                                    #
###########################################################################

CONFIG(debug, debug|release)  {
    DEFINES += DEBUG_MODE
    DESTDIR = "$$PWD/Build/debug"
    MAKEFILE = Makefile.debug }
else:CONFIG(release, debug|release) {
    DEFINES += RELEASE_MODE
    DESTDIR = "$$PWD/Build/release"
    MAKEFILE = Makefile.release }
else:CONFIG(force_debug_info) {
    DEFINES += PROFILE_MODE
    DESTDIR = "$$PWD/Build/profile"
    MAKEFILE = Makefile.profile }
else {
    DEFINES += PROFILE_MODE
    DESTDIR = "$$PWD/Build/profile"
    MAKEFILE = Makefile.profile }

RCC_DIR = "$$PWD/Build/RCCFiles"
UI_DIR = "$$PWD/Build/UICFiles"
MOC_DIR = "$$PWD/Build/MOCFiles"
OBJECTS_DIR = "$$PWD/Build/ObjFiles"

# Copy files to build directory
#copydata0.commands = $(COPY_DIR) $$PWD/config/config.txt $$DESTDIR
#copydata1.commands = $(COPY_DIR) $$PWD/config/SystemMan.db $$DESTDIR
#first.depends = $(first) copydata0 copydata1
#export(first.depends)
#export(copydata0.commands)
#export(copydata1.commands)
#QMAKE_EXTRA_TARGETS += first copydata0 copydata1

#QFile DbFile;
#QString DatabaseDataStoragePath = QStandardPaths::writableLocation(QStandardPaths::StandardLocation::AppDataLocation);
#DbFile.setFileName("assets:/MyDatabase.sqlite");
#DbFile.copy(DatabaseDataStoragePath + "/MyDatabase.sqlite")
#QFile::setPermissions(DatabaseDataStoragePath + "/MyDatabase.sqlite", QFile::WriteOwner | QFile::ReadOwner);

unix:!macx: LIBS += -Wall -lncursesw -lmenuw -lformw -lpanelw -pthread -lsystemd -lncurses++w -lmenu -ldbus-c++-1
###########################################################################
#                           Ende !!!                                      #
###########################################################################

SOURCES += \
        MenuClass.cpp \
        ServiceClass.cpp \
        Start.cpp \
        TaskClass.cpp \
        WinClass.cpp

HEADERS += \
    Info.h \
    MenuClass.h \
    ServiceClass.h \
    TaskClass.h \
    WinClass.h
