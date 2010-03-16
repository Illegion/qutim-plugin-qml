HEADERS += src/libnotifylayer.h \
    src/notificationcore.h \
    src/popupwidget.h \
    src/popup.h \
    src/manager.h \
    src/backend.h \
    src/qtdwm/qtdwm.h \
    src/qmlsettingswidget.h \
    k8json/k8json.h \
    src/settingsmanager.h
SOURCES += src/libnotifylayer.cpp \
    src/notificationcore.cpp \
    src/popupwidget.cpp \
    src/popup.cpp \
    src/manager.cpp \
    src/backend.cpp \
    src/qtdwm/qtdwm.cpp \
    src/qmlsettingswidget.cpp \
    k8json/k8json.cpp \
    src/settingsmanager.cpp
CONFIG += qt \
    plugin
unix:INCLUDEPATH += /usr/include
windows:INCLUDEPATH += C:\\qutim-builds\\qutim\\include
QT += core \
    gui \
    declarative
TEMPLATE = lib
TARGET = qmlpopup
INSTALLS += target
unix:target.path += /usr/lib/qutim
FORMS += src/qmlsettingswidget.ui
RESOURCES += icons.qrc
