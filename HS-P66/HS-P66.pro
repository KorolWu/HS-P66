QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Form/axischeck.cpp \
    Form/axisfrom.cpp \
    Form/axisinfoui.cpp \
    Form/ioform.cpp \
    Form/iomonitor.cpp \
    Form/pushbutton.cpp \
    Form/visionfrom.cpp \
    Units/c_systemlogmng.cpp \
    main.cpp \
    mainwindow.cpp \
    motioncontrol.cpp \
    sharedata.cpp

HEADERS += \
    DataStruct.h \
    Form/axischeck.h \
    Form/axisfrom.h \
    Form/axisinfoui.h \
    Form/ioform.h \
    Form/iomonitor.h \
    Form/pushbutton.h \
    Form/visionfrom.h \
    Units/c_systemlogmng.h \
    Units/myIniconfig.h \
    mainwindow.h \
    motioncontrol.h \
    sharedata.h

FORMS += \
    mainwindow.ui
#INCLUDEPATH += $$PWD/ADLINK
#LIBS += -L$$PWD/ADLINK/ -lAPS168x64
LIBS += -L$$PWD/ -lAPS168x64
# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target


win32:CONFIG(release, debug|release): LIBS += -LC:/openCv/opencv/build/x64/vc14/lib/ -lopencv_world452
else:win32:CONFIG(debug, debug|release): LIBS += -LC:/openCv/opencv/build/x64/vc14/lib/ -lopencv_world452d
else:unix: LIBS += -LC:/openCv/opencv/build/x64/vc14/lib/ -lopencv_world452

INCLUDEPATH += C:/openCv/opencv/build/include
DEPENDPATH += C:/openCv/opencv/build/include
RESOURCES += \
    resource.qrc
