QT       += core gui

TARGET = chess
TEMPLATE = app

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

SOURCES += \
main.cpp		    \
ChessViewWidget.cpp	    \
ChessBoard.cpp	    \
MainWindowWidget.cpp    \
    ChessCtrl.cpp	    \

HEADERS += \
ChessViewWidget.h	    \
ChessBoard.h	    \
MainWindowWidget.h  \
ChessCtrl.h	    \

FORMS += \
MainWindow.ui

RESOURCES += \
Pieces.qrc
