QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

RC_ICONS = icon.ico

SOURCES += \
    src/extra/addflat.cpp \
    src/extra/queue.cpp \
    src/extra/searchflat.cpp \
    src/extra/mainwindow.cpp \
    src/main.cpp \


HEADERS += \
    src/headers/addflat.h \
    src/headers/mainwindow.h \
    src/headers/queue.h \
    src/headers/searchflat.h

FORMS += \
    src/ui/addflat.ui \
    src/ui/mainwindow.ui \
    src/ui/searchflat.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    src/resource/res.qrc
