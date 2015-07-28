## TinyXml
INCLUDEPATH += "../TinyXML/include"
DEPENDPATH += "../TinyXML/include"

QT += widgets
QT += multimedia

TARGET = Synthez

SOURCES +=  main.cpp                            \
            ../TinyXML/lib/tinystr.cpp          \
            ../TinyXML/lib/tinyxml.cpp          \
            ../TinyXML/lib/tinyxmlerror.cpp     \
            ../TinyXML/lib/tinyxmlparser.cpp    \
            MainWindow.cpp                      \
            Loader.cpp \
    Music.cpp \
    Track.cpp

HEADERS  += \
    MainWindow.h \
    Loader.h \
    Music.h \
    Track.h
