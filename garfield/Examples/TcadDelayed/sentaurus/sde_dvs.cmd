# Define process constants

# One metal layer (Al) with equivalent total thickness (125nm)
(define MTh 0.125)

(define NTh @N_Thickness@)
(define PTh @P_Thickness@)

(define NDoping @N_Doping@)
(define PDoping @P_Doping@)

(define CDoping @Contact_Dose@)

(define CD @Contact_Depth@)

(define TotalW @Diode_Size@)

## Interface Properties
# High N-Doping
(define IDoping 1e22)
# 3nm Interface region on each side
(define InterfaceW2 0.003)

## Define dependant constants
(define TotalW2 (* 0.5 TotalW))


(sdegeo:set-auto-region-naming OFF)

# New structure replaces old
(sdegeo:set-default-boolean "ABA")


## Define the substrate regions
(sdegeo:create-rectangle
  (position 0 (- TotalW2) 0) (position NTh TotalW2 0)
  "Silicon" "g.n_substrate"
)
(sdedr:define-refeval-window "ref.n_substrate" "Rectangle"
  (position 0 (- TotalW2) 0) (position NTh TotalW2 0)
)


(sdegeo:create-rectangle
  (position 0 TotalW2 0) (position (- PTh) (- TotalW2) 0)
  "Silicon" "g.p_substrate"
)
(sdedr:define-refeval-window "ref.p_substrate" "Rectangle"
  (position 0 TotalW2 0) (position (- PTh) (- TotalW2) 0)
)


(sdedr:define-refeval-window "ref.n_interface" "Rectangle"
  (position InterfaceW2 TotalW2 0) (position (- InterfaceW2) (- TotalW2) 0)
)


## Define the Contact Metalization
(sdegeo:create-rectangle
  (position NTh (- TotalW2) 0)
  (position (+ NTh MTh) TotalW2 0)
  "Aluminum"
  "g.n_contact"
)
(sdedr:define-refeval-window "ref.n_implant" "Line"
  (position NTh (- TotalW2) 0) (position NTh TotalW2 0)
)

(sdegeo:create-rectangle
  (position (- PTh) TotalW2 0)
  (position (- (+ PTh MTh)) (- TotalW2) 0)
  "Aluminum"
  "g.p_contact"
)
(sdedr:define-refeval-window "ref.p_implant" "Line"
  (position (- PTh) TotalW2 0) (position (- PTh) (- TotalW2) 0)
)


# Define the doping profiles
(sdedr:define-constant-profile "CP.n_interface" "PhosphorusActiveConcentration" IDoping)
(sdedr:define-constant-profile "CP.n_substrate" "PhosphorusActiveConcentration" NDoping)
(sdedr:define-constant-profile "CP.p_substrate" "BoronActiveConcentration" PDoping)

(sdedr:define-gaussian-profile "AP.n_implant" "PhosphorusActiveConcentration"
  "PeakPos" 0  "PeakVal" CDoping
  "ValueAtDepth" NDoping "Depth" CD
  "Gauss"  "Factor" 0.4)
(sdedr:define-gaussian-profile "AP.p_implant" "BoronActiveConcentration"
  "PeakPos" 0  "PeakVal" CDoping
  "ValueAtDepth" PDoping "Depth" CD
  "Gauss"  "Factor" 0.4)


# Place the substrate and contact doping
(sdedr:define-constant-profile-placement "placeCP.n_interface"
  "CP.n_interface" "ref.n_interface")

(sdedr:define-constant-profile-placement "placeCP.n_substrate"
  "CP.n_substrate" "ref.n_substrate")
(sdedr:define-constant-profile-placement "placeCP.p_substrate"
  "CP.p_substrate" "ref.p_substrate")

(sdedr:define-analytical-profile-placement "placeAP.n_implant"
  "AP.n_implant" "ref.n_implant" "Both" "NoReplace" "Eval")
(sdedr:define-analytical-profile-placement "placeAP.p_implant"
  "AP.p_implant" "ref.p_implant" "Both" "NoReplace" "Eval")



# Define the Contacts
(sdegeo:define-contact-set "N" 4 (color:rgb 0 0 1 ) "##" )
(sdegeo:define-contact-set "P" 4 (color:rgb 0 0 1 ) "##" )

(sdegeo:set-contact (find-edge-id (position (+ NTh MTh) 0 0)) "N")
(sdegeo:set-contact (find-edge-id (position (- (+ PTh MTh)) 0 0)) "P")



# Substrate Refinement
(sdedr:define-refinement-size "rf.substrate" 40 200 0.01 0.01 )
(sdedr:define-refinement-placement "placeRF.n_substrate" "rf.substrate" "ref.n_substrate" )
(sdedr:define-refinement-placement "placeRF.p_substrate" "rf.substrate" "ref.p_substrate" )
(sdedr:define-refinement-function "rf.substrate" "DopingConcentration" "MaxTransDiff" 1)

# Interface Refinement
(sdedr:define-refeval-window "ref.interface" "Rectangle"
  (position (- 1) (- TotalW2) 0) (position 1 TotalW2 0)
)

(sdedr:define-refinement-size "rf.interface" 2 40 0.001 0.001 )
(sdedr:define-refinement-placement "placeRF.interface" "rf.interface" "ref.interface" )
(sdedr:define-refinement-function "rf.interface" "x" "MaxInterval" (- 1) 1)


## Meshing
(sde:set-meshing-command "snmesh -a -c boxmethod")
(sdedr:append-cmd-file "")
(sde:build-mesh "snmesh" "-a -c boxmethod" "@pwd@/generated/n@node@")
(sde:save-model "@pwd@/generated/n@node@")

exit
