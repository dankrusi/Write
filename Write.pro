# -------------------------------------------------
# Project created by QtCreator 2012-04-17T11:15:28
# -------------------------------------------------
QT += core gui network printsupport
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
TARGET = Write
TEMPLATE = app
SOURCES += main.cpp \
    MainWindow.cpp \
    FadedTextEdit.cpp \
    GradientWidget.cpp \
    FaderWidget.cpp
HEADERS += MainWindow.h \
    FadedTextEdit.h \
    FaderWidget.h \
    GradientWidget.h
FORMS += MainWindow.ui
RESOURCES += Resources.qrc
ICON = Write.icns
