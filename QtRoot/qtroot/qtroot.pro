######################################################################
# Automatically generated by qmake (1.07a) Mon Jun 20 18:27:55 2005
######################################################################


TEMPLATE = lib

CONFIG += thread dll
CONFIG += create_prl

QMAKE_LFLAGS_RPATH=

macx: QMAKE_LFLAGS_SONAME = -Wl,-install_name,@rpath/

TARGET = QtRoot

QTROOTSYSPATHINSTALL = $(QTROOTSYSDIR)

QT_VERSION=$$[QT_VERSION]
contains( QT_VERSION, "^4.*" ) {
    QTROOTSYSPATHINSTALL = $$(QTROOTSYSDIR)
}

isEmpty(DESTDIR) {
  DESTDIR=..
}
isEmpty(QTROOTSYSPATHINSTALL) {
  QTROOTSYSPATHINSTALL = $$DESTDIR
}

QTROOTSYSDIR=$$DESTDIR

GQTDIRI   = ../qt/inc

QTROOTDIRS   = src
QTROOTDIRI   = inc

DEPENDPATH += $$QTROOTDIRI $$QTROOTDIRS
INCLUDEPATH +=  $$QTROOTDIRI $$GQTDIRI

unix {
  LIBS += -L..
}
# Input
HEADERS += $$QTROOTDIRI/TQtRootGuiFactory.h  \
           $$QTROOTDIRI/TQtContextMenuImp.h  \
           $$QTROOTDIRI/TQtObjectDialog.h

SOURCES += $$QTROOTDIRS/TQtRootGuiFactory.cxx \
           $$QTROOTDIRS/TQtObjectDialog.cxx   \
           $$QTROOTDIRS/TQtContextMenuImp.cxx

           
CREATE_ROOT_DICT_FOR_CLASSES  = $$QTROOTDIRI/TQtRootGuiFactory.h $$QTROOTDIRI/LinkDef.h

!exists ($$GQTDIRI/rootcintrule.pri){
     message "The rootcintrule.pri was not found"
}
exists ($$GQTDIRI/rootcintrule.pri){
    include ($$GQTDIRI/rootcintrule.pri)
}

mac {
    !exists ($$GQTDIRI/rootlibs.pri){
        message "The rootlibs.pri was not found"
    }
    exists ($$GQTDIRI/rootlibs.pri){
       include ($$GQTDIRI/rootlibs.pri)
    }
#    LIBS -= -lGQt
}

headerfiles.path   = $$QTROOTSYSPATHINSTALL/include
headerfiles.files  = $$QTROOTDIRI/*.*
headerfiles.files -= $$QTROOTDIRI/LinkDef.h

QTROOTSYSDIRLIB = $$(QTROOTSYSDIR_LIB)
isEmpty( QTROOTSYSDIRLIB  ) {
    QTROOTSYSDIRLIB=lib
} 
target.path = $$QTROOTSYSPATHINSTALL/$$QTROOTSYSDIRLIB


INSTALLS += headerfiles target


DISTFILES += LICENSE.QPL Module.mk

unix {
#  -- working directory 
  
  ROOTCINT_DIR = .rootcint
  UI_DIR = .ui
  MOC_DIR = .moc
  OBJECTS_DIR = .obj

}
#The following line was inserted by qt3to4
#QT += webkit network 
QT += network 
# qt3support 