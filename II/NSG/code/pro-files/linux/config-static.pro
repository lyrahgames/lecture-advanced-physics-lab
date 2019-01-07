TARGET  = static

TEMPLATE = app
CONFIG += qt thread warn_on release 
QT = core gui

greaterThan(QT_MAJOR_VERSION, 4) {
    QT += widgets
}

DEFINES += 
QMAKE_CXXFLAGS  += -O2 -fPIC -restrict -fno-fnalias -fno-rtti -fno-exceptions -static -std=c++11
QMAKE_LFLAGS    +=

INCLUDEPATH += 

LIBS +=

HEADERS = \
	../../src/render-w.h \
	../../src/vec.h \
	../../src/grid.h \
	../../src/vec-field.h \
	../../src/scalar-field.h \
	../../src/nsg.h \
	../../src/utils.h

SOURCES = ../../src/main.cpp


unix:OBJECTS_DIR          = obj
unix:MOC_DIR              = moc

unix:QMAKE_POST_LINK=strip $(TARGET)
