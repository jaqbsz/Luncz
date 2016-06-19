QT += core
QT += network
QT -= gui

CONFIG += c++11

TARGET = Luncz
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

DEFINES += __TESTS

SOURCES += \
    src/SQLiteCpp/Backup.cpp \
    src/SQLiteCpp/Column.cpp \
    src/SQLiteCpp/Database.cpp \
    src/SQLiteCpp/Statement.cpp \
    src/SQLiteCpp/Transaction.cpp \
    src/main.cpp \
    src/OrderList.cpp \
    src/UserList.cpp \
    src/SQLite/sqlite3.c \
    src/Server.cpp \
    src/LThread.cpp \
    src/Worker.cpp \
    src/Lrpc.cpp \
    src/LRpcMethod.cpp \
    src/LRpcResult.cpp

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
    debug.h \
    src/Server.h \
    src/LThread.h \
    src/Worker.h \
    src/Lrpc.h \
    src/LRpcMethod.h \
    src/LRpcResult.h
