QT += core gui qml sql
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QtQmlSqlExample
TEMPLATE = app

# HEADERS += my_database.h
SOURCES += main.cpp
RESOURCES = main.qml.qrc
