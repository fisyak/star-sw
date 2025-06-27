#ifndef STAR_St_g2t_Chair
#define STAR_St_g2t_Chair
#include <assert.h>
#include "TChair.h"
///////////////////////////////////////////////////////////////////////////////////
// This basic chair provides the custom methods for all hits
///////////////////////////////////////////////////////////////////////////////////

#include "tables/St_g2t_hits_Table.h"     /* Done */
#include "tables/St_g2t_ctf_hit_Table.h"  /* Done g2t_ctf_hit.idl	*/
#include "tables/St_g2t_emc_hit_Table.h"  /* Done g2t_emc_hit.idl	*/
#include "tables/St_g2t_etr_hit_Table.h"  /* done g2t_etr_hit.idl	*/
#include "tables/St_g2t_fgt_hit_Table.h"  /* Done g2t_fgt_hit.idl	*/
#include "tables/St_g2t_fst_hit_Table.h"  /* done g2t_fst_hit.idl	*/
#include "tables/St_g2t_ftp_hit_Table.h"  /* Done g2t_ftp_hit.idl	*/
#include "tables/St_g2t_fts_hit_Table.h"  /* done g2t_fts_hit.idl	*/
#include "tables/St_g2t_gem_hit_Table.h"  /* Done g2t_gem_hit.idl	*/
#include "tables/St_g2t_hca_hit_Table.h"  /* done g2t_hca_hit.idl	*/
#include "tables/St_g2t_hpd_hit_Table.h"  /* done g2t_hpd_hit.idl	*/
#include "tables/St_g2t_igt_hit_Table.h"  /* done g2t_igt_hit.idl	*/
#include "tables/St_g2t_ist_hit_Table.h"  /* Done g2t_ist_hit.idl	*/
#include "tables/St_g2t_mtd_hit_Table.h"  /* done g2t_mtd_hit.idl	*/
#include "tables/St_g2t_mwc_hit_Table.h"  /* Done g2t_mwc_hit.idl	*/
#include "tables/St_g2t_pix_hit_Table.h"  /* Done g2t_pix_hit.idl	*/
#include "tables/St_g2t_pmd_hit_Table.h"  /* Done g2t_pmd_hit.idl	*/
#include "tables/St_g2t_rch_hit_Table.h"  /* Done g2t_rch_hit.idl	*/
#include "tables/St_g2t_ssd_hit_Table.h"  /* Done g2t_ssd_hit.idl	*/
#include "tables/St_g2t_svt_hit_Table.h"  /* Done g2t_svt_hit.idl	*/
#include "tables/St_g2t_tpc_hit_Table.h"  /* Done g2t_tpc_hit.idl	*/
#include "tables/St_g2t_vpd_hit_Table.h"  /* Done g2t_vpd_hit.idl       */
#include "tables/St_g2t_track_Table.h"
#include "StarHitVector.h"
#define __HitChair__(det) \
  class St_g2t_ ## det ## _hitC : public St_g2t_Chair	{	\
  public:								\
    St_g2t_ ## det ## _hitC(TTable *table=0): St_g2t_Chair(table) {}	\
    virtual ~St_g2t_ ## det ## _hitC() {}				\
    virtual void    Fill(GHit_t &vect);					\
    ClassDefChair(St_g2t_ ## det ## _hit,g2t_ ## det ## _hit_st)		\
      ClassDef(St_g2t_ ## det ## _hitC,1)				\
      };
class St_g2t_Chair : public TChair {
 public:
  St_g2t_Chair(TTable *table): TChair(table) {}
  virtual ~St_g2t_Chair(){}
  virtual void    SetTable   (TTable *table) {fTable = table;}
  virtual Int_t   DetectorId (Int_t /* i */)                const  {return -1;};
  virtual Int_t   Sector     (Int_t /* i */)		    const  {return -1;};
  virtual Int_t   PadRow     (Int_t /* i */)                const  {return -1;};
  virtual Int_t   TrackId    (Int_t /* i */)                const  {return -1;};
  virtual Int_t   HitPosition(Int_t /* i */)     	    const  {return -1;};
  virtual Float_t GetX       (Int_t /* i */)                const  {return -999999;};
  virtual Float_t GetY       (Int_t /* i */)                const  {return -999999;};
  virtual Float_t GetZ       (Int_t /* i */)                const  {return -999999;};
  virtual void    SetX       (Float_t /* x */,Int_t /* i */)       {assert(0);};
  virtual void    SetY       (Float_t /* y */,Int_t /* i */)       {assert(0);};
  virtual void    SetZ       (Float_t /* z */,Int_t /* i */)       {assert(0);};
  virtual Float_t GetXError  (Int_t /* i */)                const  {return -999999;};
  virtual Float_t GetYError  (Int_t /* i */)       	    const  {return -999999;};
  virtual Float_t GetZError  (Int_t /* i */)                const  {return -999999;};
  virtual void    Fill(GHit_t &/* vect */) {}
  static  void    SetDebug(Int_t m=0) {fDebug = m;}
  static  Int_t   Debug() {return fDebug;}
 protected:
  static  Int_t           fDebug;
  ClassDef(St_g2t_Chair,1)
};
class St_g2t_hitsC : public St_g2t_Chair	{    
 public: 
  St_g2t_hitsC(TTable *table=0): St_g2t_Chair(table) {}
  virtual ~St_g2t_hitsC() {}
  virtual void    Fill(GHit_t &vect); 
  ClassDefChair(St_g2t_hits,g2t_hits_st)
  ClassDef(St_g2t_hitsC,1)
};
__HitChair__(ctf)
__HitChair__(emc)
__HitChair__(etr)
__HitChair__(fgt)
__HitChair__(fst)
__HitChair__(ftp)
__HitChair__(fts)
__HitChair__(gem)
__HitChair__(hca)
__HitChair__(hpd)
__HitChair__(igt)
__HitChair__(ist)
__HitChair__(mtd)
__HitChair__(mwc)
__HitChair__(pix)
__HitChair__(pmd)
__HitChair__(rch)
__HitChair__(ssd)
__HitChair__(svt)
__HitChair__(tpc)
__HitChair__(vpd)
#undef __HitChair__
#endif

