QT       += core gui
QT       += multimedia
QT       += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    makenotification.cpp \
    notification.cpp \
    notificationmanager.cpp \
    settingswindow.cpp \
    timermanager.cpp

HEADERS += \
    mainwindow.h \
    makenotification.h \
    notification.h \
    notificationmanager.h \
    settingswindow.h \
    timermanager.h

FORMS += \
    mainwindow.ui \
    makenotification.ui \
    settingswindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc
