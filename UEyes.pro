QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = WikiEyes
TEMPLATE = app

DESTDIR = ../bin

SOURCES += main.cpp\
        UEyes.cpp \
    UEye.cpp \
    UEyeWidget.cpp \
    UAboutProgram.cpp \
    USettings.cpp

HEADERS  += UEyes.h \
    USupport.h \
    UEye.h \
    UEyeWidget.h \
    USimpleButton.h \
    UAboutProgram.h \
    USettings.h \
    UInfoEyes.h

RC_FILE = app.rc

OTHER_FILES += \
    app.rc

RESOURCES += \
    resource.qrc

FORMS += \
    UAboutProgram.ui \
    USettings.ui
