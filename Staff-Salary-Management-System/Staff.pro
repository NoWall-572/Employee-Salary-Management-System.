QT        += core gui
QTPLUGIN  += qcncodecs

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

greaterThan(QT_MAJOR_VERSION, 5): QT += core5compat


CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    findstaff.cpp \
    infotable.cpp \
    main.cpp \
    mainwindow.cpp \
    readonlydelegate.cpp \
    salary.cpp \
    signupdialog.cpp \
    staff.cpp

HEADERS += \
    E:/当我很想认真学一门课/计算机程序设计/暑期学校/kernelfiles/readonlydelegate.h \
    findstaff.h \
    infotable.h \
    mainwindow.h \
    readonlydelegate.h \
    salary.h \
    signupdialog.h \
    staff.h

FORMS += \
    findstaff.ui \
    mainwindow.ui \
    signupdialog.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    E:/当我很想认真学一门课/计算机程序设计/暑期学校/kernelfiles.zip \
    E:/当我很想认真学一门课/计算机程序设计/暑期学校/kernelfiles.zip
