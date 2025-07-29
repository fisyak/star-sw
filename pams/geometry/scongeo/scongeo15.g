*
* Support structures after removinf SVT 
* SCON has revisited accoudingly  drawings from https://drupal.star.bnl.gov/STAR/system/files/SVT%20CONE%20DRAWINGS%20BINDER%5B49%5D.pdf
* 07/01/2025
*
*
*******************************************************************************
*
*
*******************************************************************************
Module  SCONGEO15 is Support structures from SVTT moved into CAVE:

   Author  Yuri Fisyak
   Created 01 July 2025

*------------------------------------------------------------------------------
*  Division lines:                                                            *
*                 *********** separates major divisions                       *
*                 ----------- separates sub-divisions                         *
*                 - - - - - - separates sub-sub divisions                     *
+cde,AGECOM,GCONST,GCUNIT.
*
      Content          SCOM,SCON,SNMX,
                       SROD,SRON,SROI,SROH,
                       SBSP ,SAKM, SPOK, SASH, SDSK, SPOA, SPOB
      structure SVTG { Version,  
                       RsizeMin,  RsizeMax,
                       SupportVer,   ConeVer,
                       ifMany}
*
      structure SSUP { Version,  
		       NomexThk1,      NomexThk2,
		       Cone1z,      Cone1dZ,      Cone2dZ,      Cone3dZ,      Cone4z,
		       rO1,      rO3,      rO4,
		       RodLen,    RodDist,
                       RodID,     RodOD,     RodIDx,    RodODx,
                       carbonShell, carbonDens, nomexDens}
*
      structure SSUB { Version,  KMountId,  KMountOd,  KMntThk
                     ,AlScrThk, zG10Start, G10Thk1, G10Thk2, G10Thk3, G10RI, G10RO,
                       rbolz, dZBolt
	}
*
      Real           conez(7), coneRi(7), coneRO(7)
      Real           conezx(7), coneRix(7), coneROx(7)
      Real           phi, xbuf, xbuf1, xbuf2, yy
      Integer        i, j
***************************
   Fill SVTG ! Basic SVT dimensions 
      Version   = 4          ! geometry version
      RsizeMin  = 4.100      ! STV innermost radius
      RsizeMax  = 46.107     ! STV outermost radius
      SupportVer= 1          ! versioning of the shield
      ConeVer=    1          ! versioning of the support cone
      ifMany    = 0          ! whether we use the geant MANY option
*
   Fill SSUP ! Support structures
      Version   = 1          ! geometry version
      NomexThk1 =0.5 	     !	 support cone NOMEX thickness at begin   
      NomexThk2 =0.35 	     !	 support cone NOMEX thickness at end   
      Cone1z   =111.448/2    !	start of cylinder part of cone   
      Cone1dZ  =3.9          !	cylinder part for beam support wheel, start of conic part   
      Cone2dZ  =174.6-81.7   !	end of conic part   
      Cone3dZ  =174.6        !	end of cylinder part   
      Cone4z   =461.409/2    !	end of ring attached to TPC  
      rO1      =22.0         !	Outer radius at beam support wheel 	
      rO3      =38.9 	     !	Outer radius of cylinder part of cone 
      rO4      =38.9 	     !	Outer radius of cylinder part of cone  
      RodLen    = 111.4      ! Length of support rods
      RodDist   = 20.1       !  distance from center to IP
      RodID     = 3.64       ! ID of Carbon support rods 
      RodOD     = 4.50       ! OD of Carbon support rods 
      RodIDx    = 8.72       ! ID of Carbon support rods 
      RodODx    = 9.58       ! OD of Carbon support rods 

      carbonShell = 0.04     ! 0.4mm carbon fiber shell "  />
      carbonDens = 1.78      ! 1.78 g/cm^3 is a typical carbon composite density "  />
      nomexDens = 0.048      ! Ballpark figure "  />
*------------------------------------------------------------
*------------------------------------------------------------
   Fill SSUB ! beampipe support
      Version   = 1          ! geometry version
*
      KMountId  = 31.34      ! id of beampipe support kinematic mount
      KMountOd  = 38.96      ! od of beampipe support kinematic mount
      KMntThk   = 0.64       ! thickness of support kinematic mount
      AlScrThk  = 0.15       ! Alulimium screen BoB Soja 
      zG10Start = 54.2       ! start of G10 beam holder
      G10Thk1   = 2.40       ! Full thinkness of G10 support
      G10Thk2   = 1.6        ! thikness 
      G10Thk3   = 0.6        ! thikness 
      G10RI     = 4.1        ! radius 
      G10RO     = 6.4        ! radius 
      rbolz     = 0.3        ! bolt 	
      dZBolt    = 0.7        ! bolt    
   EndFill

*
*------------------------------  SHALL WE BEGIN? -------------------------------------------
      USE SVTG
      USE SSUP version=SVTG_ConeVer
      conez(1)  = SSUP_Cone1z              ! start of cone
      coneRo(1) = SSUP_rO1
      coneRi(1) = coneRo(1) - SSUP_NomexThk1 - 2*SSUP_carbonShell
      conez(2)  = conez(1)  + SSUP_Cone1dz  ! cylinder part of cone with nomex 0.5 cm
      coneRo(2) = coneRo(1)
      coneRi(2) = coneRi(1)
      conez(3)  = conez(2)                 ! start of cone with nomex 0.35 cm
      coneRo(3) = coneRo(2)
      coneRi(3) = coneRo(1) - SSUP_NomexThk2 - 2*SSUP_carbonShell
      conez(4)  = conez(1)  + SSUP_Cone2dz  
      coneRo(4) = SSUP_ro3 
      coneRi(4) = coneRo(4) - SSUP_NomexThk2 - 2*SSUP_carbonShell
      conez(5)  = conez(1)  + SSUP_Cone3dz  
      coneRo(5) = coneRo(4)
      coneRi(5) = coneRi(4)
      conez(6)  = conez(1) - 0.1 ! expand mother volume

      conezx(1)  = SSUP_Cone1z              ! start of code
      coneRox(1) = SSUP_rO1  - SSUP_carbonShell
      coneRix(1) = coneRox(1) - SSUP_NomexThk1
      conezx(2)  = conezx(1)  + SSUP_Cone1dz  ! cylinder part of cone with nomex 0.5 cm
      coneRox(2) = coneRox(1)
      coneRix(2) = coneRix(1)
      conezx(3)  = conezx(2)                 ! start of cone with nomex 0.35 cm
      coneRox(3) = coneRox(2)
      coneRix(3) = coneRox(1) - SSUP_NomexThk2 
      conezx(4)  = conezx(1)  + SSUP_Cone2dz  ! end of cone and star of cylinder 
      coneRox(4) = SSUP_ro3  - SSUP_carbonShell
      coneRix(4) = coneRox(4) - SSUP_NomexThk2
      conezx(5)  = conezx(1)  + SSUP_Cone3dz  ! end of cylinder
      coneRox(5) = coneRox(4)
      coneRix(5) = coneRix(4)

      Create and Position SCOM in Cave konly='MANY'
* The beampipe support
      Create   SBSP  "Beam Support"
      Position SBSP   z= 0             konly='MANY'
      Position SBSP   z= 0 ThetaZ=180  konly='MANY'
*******************************************************************************
Block SCOM is supporting cone mother volume
      Material   Air
      attribute SCOM    seen=0 colo=1
*      SHAPE     PCON    Phi1=0  Dphi=360  Nz=14,
* zi={ -conez(5),-conez(4),-conez(3),-conez(2),    -conez(2),    -conez(6),    -conez(6),     conez(6),     conez(6),     conez(2), conez(2), conez(3), conez(4), conez(5)},
*Rmn={ coneRi(5),coneRi(4),coneRi(3),coneRi(2),svtg_RSizeMin,svtg_RSizeMin,coneRi(1)-4.0,coneRi(1)-4.0,svtg_RSizeMin,svtg_RSizeMin,coneRi(2),coneRi(3),coneRi(4),coneRi(5)},
*Rmx={ coneRo(5),coneRo(4),coneRo(3),coneRo(2),    coneRo(2),    coneRo(1),coneRo(1)+0.6,coneRo(1)+0.6,    coneRo(1),    coneRo(2),coneRo(2),coneRo(3),coneRo(4),coneRo(5)}
         CALL AGSRESET                        
         AG_PHI1 = 0                          
         AG_DPHI = 360                        
         AG_NZ = 14              
 AG_ZI( 1) = -conez(5); AG_RMN( 1)  = coneRi(5);     AG_RMX( 1) =  coneRo(5);     
 AG_ZI( 2) = -conez(4);	AG_RMN( 2)  = coneRi(4);     AG_RMX( 2) =  coneRo(4);     
 AG_ZI( 3) = -conez(3);	AG_RMN( 3)  = coneRi(3);     AG_RMX( 3) =  coneRo(3);     
 AG_ZI( 4) = -conez(2); AG_RMN( 4)  = coneRi(2);     AG_RMX( 4) =  coneRo(2);     
 AG_ZI( 5) = -conez(2);	AG_RMN( 5)  = coneRi(2);     AG_RMX( 5) =  coneRo(2);     
 AG_ZI( 6) = -conez(6);	AG_RMN( 6)  = coneRi(2);     AG_RMX( 6) =  coneRo(1);     
 AG_ZI( 7) = -conez(6);	AG_RMN( 7)  = coneRi(1)-4.0; AG_RMX( 7) =  coneRo(1)+0.6; 
 AG_ZI( 8) =  conez(6);	AG_RMN( 8)  = coneRi(1)-4.0; AG_RMX( 8) =  coneRo(1)+0.6; 
 AG_ZI( 9) =  conez(6);	AG_RMN( 9)  = coneRi(2);     AG_RMX( 9) =  coneRo(1);     
 AG_ZI(10) =  conez(2);	AG_RMN(10) =  coneRi(2);     AG_RMX(10) =  coneRo(2);     
 AG_ZI(11) =  conez(2);	AG_RMN(11) =  coneRi(2);     AG_RMX(11) =  coneRo(2);     
 AG_ZI(12) =  conez(3);	AG_RMN(12) =  coneRi(3);     AG_RMX(12) =  coneRo(3);     
 AG_ZI(13) =  conez(4);	AG_RMN(13) =  coneRi(4);     AG_RMX(13) =  coneRo(4);     
 AG_ZI(14) =  conez(5);	AG_RMN(14) =  coneRi(5);     AG_RMX(14) =  coneRo(5);     
         AG_TITLE = 'PCON'                    
         AG_EXNAME = 'SHAPE'                  
         AG_PARLIST = 'PHI1_DPHI_NZ_ZI_RMX_RMN'
         CALL AXSHAPE                         
      Create and Position SCON 
      Create and Position SCON ThetaZ=180
* 
* SVT support rods -- previously incorrectly described as Be,
* carbon compound in reality
      Create    SROD  "Support rod"
      Position  SROD  y = ssup_rodDist  
      Position  SROD  y =-ssup_rodDist  

EndBlock
*******************************************************************************
*
* ****************************************************************************
*
* ****************************************************************************
*
Block SCON is the Silicon tracker supporting cone mother volume
      Material   Carbon
      Material CarbonFiber dens=ssup_carbonDens	
      attribute SCON    seen=0 colo=1
      SHAPE     PCON    Phi1=0  Dphi=360  Nz=5,
 zi={ conez(6), conez(2), conez(3), conez(4), conez(5)},
Rmn={coneRi(1),coneRi(2),coneRi(3),coneRi(4),coneRi(5)},
Rmx={coneRo(1),coneRo(2),coneRo(3),coneRo(4),coneRo(5)}
*
      Create    SNMX  " graphite/epoxy support cone (lowest layer)"
      Position  SNMX
*
Endblock
*
*------------------------------------------------------------------------------
*
Block SNMX is the Nomex structure 
      Component C      A=12  Z=6  W=5
      Component H      A=1   Z=1  W=8
      Component O      A=16  Z=8  W=2
      Mixture   Nomex  Dens=ssup_nomexDens
      Attribute SNMX   Seen=1   Colo=6
      SHAPE     PCON   Phi1=0   Dphi=360   Nz=5,
 zi={ conez(6), conezx(2), conezx(3), conezx(4), conezx(5)},
rmn={coneRix(1),coneRix(2),coneRix(3),coneRix(4),coneRix(5)},
rmx={coneRox(1),coneRox(2),coneRox(3),coneRox(4),coneRox(5)}

EndBlock
*
*------------------------------------------------------------------------------
*
Block SROD is the SVT Carbon composite support rod

      Material  Carbon
      Material CarbonFiber dens=ssup_carbonDens
      Attribute SROD  Seen=1  Colo=1
      Shape     ELTU   p1=ssup_RodODx/2,
                       p2=ssup_RodOD/2, 
                       dz=conez(6)

      Create   SRON  "The support rod nomex core"
      Position SRON
endblock

*
* ****************************************************************************
*


BLOCK SRON Is the creamy nomex filling

      Component C      A=12  Z=6  W=5
      Component H      A=1   Z=1  W=8
      Component O      A=16  Z=8  W=2
      Mixture   Nomex  Dens=ssup_nomexDens
      Attribute SRON seen=1 colo=5

      Shape     ELTU p1=ssup_rododx/2-ssup_carbonShell,
                     p2=ssup_rodod /2-ssup_carbonShell
      Create   SROI "The support rod inner shell"
      Position SROI

ENDBLOCK

BLOCK SROI Is the inner carbon fiber shell

      Material CarbonFiber
      Attribute SROI seen=1 colo=1
      Shape ELTU p1=ssup_rodidx/2+ssup_carbonShell,
                 p2=ssup_rodid /2+ssup_carbonShell

      Create   SROH "The support rod hole"
      Position SROH

ENDBLOCK

Block SROH is the hole in SROD

      Material  Air
      Attribute SROH  Seen=1  Colo=3
      Shape     ELTU   p1=ssup_RodIDx/2,
                       p2=ssup_RodID/2

endblock

*
*******************************************************************************
*
Block SBSP is the beampipe support mother volume
      Material Air
      Attribute SBSP Seen=0 Colo=1
      Shape PCON   Phi1=0   Dphi=360   Nz=6,
 zi={ SSUB_zG10Start,       conez(6),       conez(6),        conez(1),       conez(1),                    conez(2)},
Rmn={  svtg_RSizeMin,  svtg_RSizeMin,  svtg_RSizeMin,   svtg_RSizeMin,  svtg_RSizeMin,               svtg_RSizeMin},
Rmx={  coneRi(2)-4.0,  coneRi(2)-4.0,  coneRi(1)+0.1,   coneRi(1)+0.1,      coneRi(1),                   coneRi(1)}
      Create SAKM  " aluminum kinematic mount (just guess) "
      Position SAKM
      Create    SPOA  " spoke to support beam pipe assembly "
*     {"90XD",   90.0,   90.0,    0.0,    0.0,   90.0,    0.0}, // "90XD"  (x,y,z) = > ( z, x, y)
      YY = (SSUB_KMountId/2 + svtg_RSizeMin)/2/sqrt(2.)
      Position  SPOA x=YY  y=YY  z=conez(1)  ThetaX=90 Phix=135 ThetaY=0 PhiY=0 ThetaZ=90 Phiz=45
      Position  SPOA x=-YY y=YY  z=conez(1)  ThetaX=90 Phix=225 ThetaY=0 PhiY=0 ThetaZ=90 Phiz=135
      Position  SPOA x=-YY y=-YY z=conez(1)  ThetaX=90 Phix=315 ThetaY=0 PhiY=0 ThetaZ=90 Phiz=225
      Position  SPOA x=YY  y=-YY z=conez(1)  ThetaX=90 Phix=45  ThetaY=0 PhiY=0 ThetaZ=90 Phiz=315
      Create SASH   " Aliuminium screen "
      Position SASH
      Create SDSK    " G10 support Disk"
      Position SDSK  konly='MANY'
endblock
*
Block SAKM is the beampipe support aluminum kinematic mount*
      Material Aluminium
      Attribute SAKM Seen=1 Colo=2
      Shape PCON   Phi1=0   Dphi=360   Nz=4,
 zi={     conez(6),     conez(1),     conez(1),     conez(2)},
Rmn={SSUB_KMountId/2,SSUB_KMountId/2,SSUB_KMountId/2,SSUB_KMountId/2+SSUP_Cone1dZ},
Rmx={coneRi(1)+0.1,coneRi(1)+0.1,    coneRi(1),     coneRi(1)}
Endblock
*
*------------------------------------------------------------------------------
*
Block SPOA is beam spoke assembly
      Material Air
      Attribute SPOA Seen=1 Colo=2
      SHAPE box dx=1.6 dy=1.25 dz = (SSUB_KMountId/2 - svtg_RSizeMin)/2
      Create and Position SPOK y =  -0.4 
      Create and Position SPOB z = -(SSUB_KMountId/2 - svtg_RSizeMin)/2 + 0.8
EndBlock
Block SPOB is beam spoke assembly
      Material G10
      Attribute SPOB Seen=1 Colo=2
      SHAPE box dx=1.6 dy=1.25 dz = 0.8 
EndBlock
Block SPOK is beam line support spokes
      Material Aluminium
      Attribute SPOK Seen=1 Colo=2
      SHAPE TUBE rmin=0 rmax = 0.15 dz = (SSUB_KMountId/2 - svtg_RSizeMin)/2
EndBlock
*
*------------------------------------------------------------------------------
*
Block SASH is the beampipe support aluminum EM shield
      Material Aluminium
      Material AluminiumMesh dens=0.125 ! Bob Soja
      Attribute SASH Seen=1 Colo=2
      Shape PCON   Phi1=0   Dphi=360   Nz=2,
 zi={       conez(6),  conez(6)+SSUB_AlScrThk},
Rmn={  svtg_RSizeMin,           svtg_RSizeMin},
Rmx={SSUB_KMountId/2,         SSUB_KMountId/2}
Endblock
*
*------------------------------------------------------------------------------
*
Block SDSK is the beampipe support G10
      Material G10
      Attribute SDSK Seen=1 Colo=3
      Shape PCON   Phi1=0   Dphi=360   Nz=2,
 zi={conez(6)-SSUB_G10Thk3,   conez(6)},
Rmn={           SSUB_G10RI, SSUB_G10RI},
Rmx={           SSUB_G10RO, SSUB_G10RO}
Endblock
end
