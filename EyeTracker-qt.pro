QT       += core gui sql
QT       += sql
QT       += multimedia
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11


# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS
DEFINES += QT_MESSAGELOGCONTEXT
# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ControlWidget/navlistview.cpp \
    ControlWidget/sliderbar.cpp \
    SSCameraToolBox.cpp \
    SSToolBox.cpp \
    SSToolBoxItem.cpp \
    addpatientdialog.cpp \
    appinit.cpp \
    eyecalibratethread.cpp \
    eyetrackertoolbox.cpp \
    eyetrackontv.cpp \
    logindialog.cpp \
    main.cpp \
    maindlg.cpp \
    mainwindow.cpp \
    patientcongrol.cpp \
    qcalibratewidgetontv.cpp \
    qcalibration.cpp \
    qcalibrationwidget.cpp \
    qccdcontrol.cpp \
    qdisplayontv.cpp \
    qeyeconfigcontrol.cpp \
    qeyecontrol.cpp \
    qeyetrackingwidget.cpp \
    qeyetrackwidget.cpp \
    qeyevoiceprompt.cpp \
    qindockwidget.cpp \
    qmeasureanalywidget.cpp \
    qpatientlistwidget.cpp \
    qpatientwidget.cpp \
    qplayaudio.cpp \
    qshowpiclabel.cpp \
    qshowpicwidget.cpp \
    quiwidget.cpp \
    sqlitecontrol.cpp \
    userlogindialog.cpp

HEADERS += \
    ControlWidget/navlistview.h \
    ControlWidget/sliderbar.h \
    QEyeCommon.h \
    QEyeDefine.h \
    SSCameraToolBox.h \
    SSToolBox.h \
    SSToolBoxItem.h \
    addpatientdialog.h \
    appinit.h \
    eyecalibratethread.h \
    eyetrackertoolbox.h \
    eyetrackontv.h \
    head.h \
    logindialog.h \
    maindlg.h \
    mainwindow.h \
    patientcongrol.h \
    qcalibratewidgetontv.h \
    qcalibration.h \
    qcalibrationwidget.h \
    qccdcontrol.h \
    qdisplayontv.h \
    qeyeconfigcontrol.h \
    qeyecontrol.h \
    qeyetrackingwidget.h \
    qeyetrackwidget.h \
    qeyevoiceprompt.h \
    qindockwidget.h \
    qmeasureanalywidget.h \
    qpatientlistwidget.h \
    qpatientwidget.h \
    qplayaudio.h \
    qshowpiclabel.h \
    qshowpicwidget.h \
    quiwidget.h \
    sqlitecontrol.h \
    userlogindialog.h

FORMS += \
    addpatientdialog.ui \
    eyetrackontv.ui \
    logindialog.ui \
    maindlg.ui \
    mainwindow.ui \
    measureanaly.ui \
    qcalibratewidgetontv.ui \
    qcalibrationwidget.ui \
    qdisplayontv.ui \
    qeyetrackingwidget.ui \
    qeyetrackwidget.ui \
    qmeasureanalywidget.ui \
    qpatientlistwidget.ui \
    qpatientwidget.ui \
    userlogindialog.ui

TRANSLATIONS += \
    EyeTracker-qt_zh_CN.ts

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target



INCLUDEPATH += $$PWD/include
DEPENDPATH += $$PWD/include

win32: LIBS += -L$$PWD/OpenCV2.2/lib/ -lopencv_core220

INCLUDEPATH += $$PWD/OpenCV2.2/include
DEPENDPATH += $$PWD/OpenCV2.2/include

win32: LIBS += -L$$PWD/OpenCV2.2/lib/ -lopencv_highgui220

INCLUDEPATH += $$PWD/OpenCV2.2/include
DEPENDPATH += $$PWD/OpenCV2.2/include

win32: LIBS += -L$$PWD/OpenCV2.2/lib/ -lopencv_imgproc220

INCLUDEPATH += $$PWD/OpenCV2.2/include
DEPENDPATH += $$PWD/OpenCV2.2/include

win32: LIBS += -L$$PWD/lib/ -lQuickLink2

INCLUDEPATH += $$PWD/include
DEPENDPATH += $$PWD/include

RESOURCES += \
    Res.qrc
