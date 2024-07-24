QT       += core gui svg

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

QMAKE_CXXFLAGS += -Wa,-mbig-obj # added this line for the error
                                # { error: [Makefile.Debug:1878: debug/qcustomplot.o] Error 1 }
CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

INCLUDEPATH += \
    include/ \
    "D:/Softwares_Installed/QT_Creator/eigen-3.4.0"

VPATH += src/

SOURCES += \
    main.cpp \
    src/bode_plot.cpp \
    src/qcustomplot.cpp

HEADERS += \
    include/bode_plot.h \
    include/qcustomplot.h

FORMS += \
    bode_plot.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
