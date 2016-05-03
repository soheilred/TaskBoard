#-------------------------------------------------
#
# Project created by QtCreator 2016-03-09T12:04:00
#
#-------------------------------------------------

QT       += core gui sql

CONFIG += c++11

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

RC_ICONS = appIcon.ico

TARGET = TaskBoard
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    taskcolumn.cpp \
    taskmodel.cpp \
    databasemanager.cpp \
    qlistviewdelegate.cpp \
    taskentry.cpp \
    edittaskdialog.cpp \
    colorcontainer.cpp \
    editprojectdialog.cpp \
    projectentry.cpp \
    timercontroller.cpp \
    timedisplay.cpp \
    QCustomPlot/qcustomplot.cpp \
    statisticswindow.cpp \
    projectanalyzer.cpp \
    burnupchartcreator.cpp \
    dailyworkchartcreator.cpp \
    taskrecordsdialog.cpp \
    estimationerrorchartcreator.cpp \
    histogram.cpp

HEADERS  += mainwindow.h \
    taskcolumn.h \
    taskmodel.h \
    databasemanager.h \
    qlistviewdelegate.h \
    taskentry.h \
    edittaskdialog.h \
    colorcontainer.h \
    editprojectdialog.h \
    projectentry.h \
    timercontroller.h \
    timedisplay.h \
    QCustomPlot/qcustomplot.h \
    statisticswindow.h \
    projectanalyzer.h \
    burnupchartcreator.h \
    dailyworkchartcreator.h \
    taskrecordsdialog.h \
    estimationerrorchartcreator.h \
    histogram.h

FORMS    += mainwindow.ui \
    taskcolumn.ui \
    edittaskdialog.ui \
    editprojectdialog.ui \
    statisticswindow.ui \
    taskrecordsdialog.ui

RESOURCES += \
    resources.qrc
