######################################################################
# Automatically generated by qmake (1.07a) Fri Sep 7 09:16:46 2007
######################################################################

TEMPLATE = app
QT += xml opengl 

QMAKE_LFLAGS_RPATH=

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

win32 {
  LIBS += $(ROOTSYS)/lib/QGLViewer.lib
  INCLUDEPATH += .  $(ROOTSYS)/qtgl/qglviewer
}
unix | macx {
 LIBS +=  -lQGLViewer
 !macx { 
     LIBS += -lGLU 
  }
}
# Input
HEADERS += animation.h histogram.h
SOURCES +=  histogram.cxx animation.cxx main.cxx