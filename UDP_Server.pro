QT       += core gui
QT += network
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    udp_file_recv.cpp \
    udt_src/api.cpp \
    udt_src/buffer.cpp \
    udt_src/cache.cpp \
    udt_src/ccc.cpp \
    udt_src/channel.cpp \
    udt_src/common.cpp \
    udt_src/core.cpp \
    udt_src/epoll.cpp \
    udt_src/list.cpp \
    udt_src/md5.cpp \
    udt_src/packet.cpp \
    udt_src/queue.cpp \
    udt_src/window.cpp \
    widget.cpp

HEADERS += \
    udp_file_recv.h \
    udt_src/api.h \
    udt_src/buffer.h \
    udt_src/cache.h \
    udt_src/ccc.h \
    udt_src/channel.h \
    udt_src/common.h \
    udt_src/core.h \
    udt_src/epoll.h \
    udt_src/list.h \
    udt_src/md5.h \
    udt_src/packet.h \
    udt_src/queue.h \
    udt_src/udt.h \
    udt_src/window.h \
    widget.h

FORMS += \
    widget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resource/resource.qrc

#图标
RC_ICONS =logo.ico

LIBS += -lwsock32
LIBS += -lws2_32
