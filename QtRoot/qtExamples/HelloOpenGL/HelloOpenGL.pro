######################################################################
# Automatically generated by qmake (1.07a) Fri Sep 7 09:16:46 2007
######################################################################

TEMPLATE = lib
QT += xml opengl

QMAKE_LFLAGS_RPATH=
# Get the "lib" prefix to match the Unix default
win32 : TARGET = libHelloOpenGL

# Input
HEADERS +=  Viewer.h
SOURCES +=  Viewer.cxx

CREATE_ROOT_DICT_FOR_CLASSES  = $$HEADERS LinkDef.h

HEADERS +=  TQtFunViewer.h
SOURCES +=  TQtFunViewer.cxx

incFile = $(QTROOTSYSDIR)/include/rootcint.pri
exists ($$incFile) {
  include ($$incFile)
} 
!exists ($$incFile) {
  incFile = $(ROOTSYS)/include/rootcint.pri
  exists ($$incFile) {
    include ($$incFile)
  } 
  !exists ($$incFile) {
    message (" ")
    message ("WARNING:  The $$inlcudeFile was not found !!!")
    message ("Please update your Qt layer version from http://root.bnl.gov ")
    message (" ")
    LIBS += $$system(root-config --glibs) -lGQt
    INCLUDEPATH += $(ROOTSYS)/include
  }
}

win32: LIBS += libMathCore.lib QGLViewer.lib 
unix : LIBS += -lQGLViewer
