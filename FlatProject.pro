QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

RC_ICONS = icon.ico

SOURCES += \
    addflat.cpp \
    main.cpp \
    mainwindow.cpp \
    queue.cpp \
    searchflat.cpp

HEADERS += \
    addflat.h \
    mainwindow.h \
    queue.h \
    searchflat.h

FORMS += \
    addflat.ui \
    mainwindow.ui \
    searchflat.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc
