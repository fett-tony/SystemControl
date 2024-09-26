TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

############################################################################
##       Meine einstellung immer ohne shadow build in QT creator!!!        #
############################################################################
PROGRAMMNAME = ServiceControl
TARGET = bin/$$PROGRAMMNAME
VERSION = v1.0.4
QMAKE_TARGET_PRODUCT = "$${PROGRAMMNAME}"
QMAKE_TARGET_COMPANY = "HOMELAND"
QMAKE_TARGET_COPYRIGHT = "Copyright (c) by Aktony"
DEFINES += APP_VERSION=\"\\\"$${VERSION}\\\"\" \
           APP_PRODUCT=\"\\\"$${QMAKE_TARGET_PRODUCT}\\\"\" \
           APP_COMPANY=\"\\\"$${QMAKE_TARGET_COMPANY}\\\"\" \
           APP_COPYRIGHT=\"\\\"$${QMAKE_TARGET_COPYRIGHT}\\\"\"
#unix:!macx:QMAKE_DEL_FILE = rm -f
#unix:!macx:QMAKE_DEL_DIR  = rm -rf
#unix:!macx:OUT_PWD = "$$PWD/Build_$$VERSION"
DESTDIR  = "$$PWD/Build_$$VERSION/debug/$$PROGRAMMNAME"
############################################################################
#__________________release and debug_______________________________________#
############################################################################
CONFIG(debug, debug|release) {
    DEFINES += DEBUG_MODE
    DESTDIR = "$$PWD/Build_$$VERSION/debug/$$PROGRAMMNAME"
    QMAKE_MAKEFILE = Makefile.debug
    MAKEFILE = Makefile.debug
} else:CONFIG(release, debug|release) {
    DEFINES += RELEASE_MODE
    DESTDIR = "$$PWD/Build_$$VERSION/release/$$PROGRAMMNAME"
    QMAKE_MAKEFILE = Makefile.release
    MAKEFILE = Makefile.release
} else:CONFIG(force_debug_info) {
    DEFINES += PROFILE_MODE
    DESTDIR = "$$PWD/Build_$$VERSION/profile/$$PROGRAMMNAME"
    QMAKE_MAKEFILE = Makefile.profile
    MAKEFILE = Makefile.profile
} else {
    DEFINES += DEBUG_MODE
    DESTDIR = "$$PWD/Build_$$VERSION/debug/$$PROGRAMMNAME"
    QMAKE_MAKEFILE = Makefile.debug
    MAKEFILE = Makefile.debug
}

RCC_DIR = "$$PWD/Build_$$VERSION/RCCFiles"
UI_DIR = "$$PWD/Build_$$VERSION/UICFiles"
MOC_DIR = "$$PWD/Build_$$VERSION/MOCFiles"
OBJECTS_DIR = "$$PWD/Build_$$VERSION/ObjFiles"

message($$_PRO_FILE_ " - Profile!")
message($$_PRO_FILE_PWD_ " - Profile dir!")
message($$DESTDIR " - Destdir Name!")
message($$MAKEFILE " - Makefile Name!")
message($$OUT_PWD " - out_pwd dir!")
message($$QMAKE_MAKEFILE " - Qmakefile Name!")
############################################################################
#__________________Copy files to build directory___________________________#
############################################################################
#copydata0.commands = $(DEL_DIR)     $$DESTDIR/config
#copydata1.commands = $(COPY_FILE)   $$PWD/lib/libLogWriter.a     $$DESTDIR/lib/libLogWriter.a
#copydata2.commands = $(COPY_FILE)   $$PWD/lib/libUserGroupList.a $$DESTDIR/lib/libUserGroupList.a
#first.depends = $(first) copydata0 copydata1 copydata2
#export(first.depends)
#export(copydata0.commands)
#export(copydata1.commands)
#export(copydata2.commands)
#QMAKE_EXTRA_TARGETS += first copydata0  copydata1 copydata2
unix:!macx: LIBS += -lncurses++w -Wall -lncursesw -lmenuw -lmenu -lformw -lpanelw -pthread -lreadline -Wreturn-type -lstdc++fs -lsystemd
#-lpam -lpam_misc -lxcb
#unix:!macx:LIBS_PRIVATE += $$DESTDIR/lib/libUserGroupList.a
#unix:!macx:LIBS_PRIVATE += $$DESTDIR/lib/libLogWriter.a
#unix:!macx: LIBS += -L$$DESTDIR/lib/ -lLogWriter -lUserGroupList
#$$DESTDIR/lib/libconfigator.a $$DESTDIR/lib/libdragonfail.a $$DESTDIR/lib/libtermbox.a $$DESTDIR/lib/libtestoasterror.a
#unix:!macx: LIBS += -L$$DESTDIR/lib/ -largoat -lconfigator -ldragonfail -ltermbox -ltestoasterror
###########################################################################
#                           Ende !!!                                      #
###########################################################################

SOURCES += \
#        MenuClass.cpp \
#		WinClass.cpp \
        MenuWinClass.cpp \
        ServiceClass.cpp \
        Start.cpp \
		TaskClass.cpp


HEADERS += \
    Info.h \
#	WinClass.h \
#    MenuClass.h \
    MenuWinClass.h \
    ServiceClass.h \
	TaskClass.h

DISTFILES += \
	zeug.txt

