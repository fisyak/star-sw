*
* $Id: qtrace99.inc,v 1.2 2018/06/28 16:02:52 fisyak Exp $
*
* $Log: qtrace99.inc,v $
* Revision 1.2  2018/06/28 16:02:52  fisyak
* Merge with geant3
*
* Revision 1.1.1.1  2002/06/16 15:18:50  hristov
* Separate distribution  of Geant3
*
* Revision 1.1.1.1  1999/05/18 15:55:27  fca
* AliRoot sources
*
* Revision 1.1.1.1  1996/03/06 10:46:54  mclareni
* Zebra
*
*
#ifndef CERNLIB_ZEBRA_QTRACE99_INC
#define CERNLIB_ZEBRA_QTRACE99_INC
*
*
* qtrace99.inc
*
#if !defined(CERNLIB_QTRHOLL)||defined(CERNLIB_A6M)
  999 NQTRAC = NQTRAC - 1
#else
  999 NQTRAC = NQTRAC - 2
#endif

#endif