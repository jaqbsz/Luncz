QT += core
QT -= gui

CONFIG += c++11

TARGET = Luncz
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += \
    src/SQLiteCpp/Backup.cpp \
    src/SQLiteCpp/Column.cpp \
    src/SQLiteCpp/Database.cpp \
    src/SQLiteCpp/Statement.cpp \
    src/SQLiteCpp/Transaction.cpp \
    src/main.cpp \
    src/Order.cpp \
    src/OrderList.cpp \
    src/User.cpp \
    src/UserList.cpp \
    src/SQLite/sqlite3.c

HEADERS += \
    src/SQLite/sqlite3.h \
    src/SQLiteCpp/Assertion.h \
    src/SQLiteCpp/Backup.h \
    src/SQLiteCpp/Column.h \
    src/SQLiteCpp/Database.h \
    src/SQLiteCpp/Exception.h \
    src/SQLiteCpp/SQLiteCpp.h \
    src/SQLiteCpp/Statement.h \
    src/SQLiteCpp/Transaction.h \
    src/Order.h \
    src/OrderList.h \
    src/User.h \
    src/UserList.h \
    debug.h
