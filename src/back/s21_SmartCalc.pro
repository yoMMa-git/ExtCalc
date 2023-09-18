QT       += core gui printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0




# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

FORMS += \
    ../front/calc/mainwindow.ui \
    ../front/credit/creditcalc.ui \
    ../front/deposit/depositcalc.ui \
    ../front/graphics/drawgraphics.ui

HEADERS += \
    calc/mainwindow.h \
    credit/creditcalc.h \
    deposit/depositcalc.h \
    graphics/drawgraphics.h \
    polish/polish.h \
    polish/stack.h \
    polish/tokenize.h \
    qcustomplot.h

SOURCES += \
    calc/mainwindow.cpp \
    credit/creditcalc.cpp \
    deposit/depositcalc.cpp \
    graphics/drawgraphics.cpp \
    main.cpp \
    polish/polish.c \
    polish/stack.c \
    polish/tokenize.c \
    qcustomplot.cpp

