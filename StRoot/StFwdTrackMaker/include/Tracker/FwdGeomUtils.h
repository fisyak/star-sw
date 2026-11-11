#ifndef FWD_GEOM_UTILS_H
#define FWD_GEOM_UTILS_H

#include "TGeoVolume.h"
#include "TGeoNode.h"
#include "TGeoMatrix.h"
#include "TGeoNavigator.h"

class FwdGeomUtils {
    public:



        FwdGeomUtils( TGeoManager * gMan ) {
            if ( gMan != nullptr ){
                _navigator = gMan->AddNavigator();
                _gMan = gMan;
            }
        }

        ~FwdGeomUtils(){
            if ( _gMan != nullptr && _navigator != nullptr){
                _gMan->RemoveNavigator( _navigator );
            }
        }

        bool cd( const char* path ){
            // Change to the specified path
            bool ret = _navigator -> cd(path);
            // If successful, set the node, the volume, and the GLOBAL transformation
            // for the requested node.  Otherwise, invalidate these
            if ( ret ) {
                _matrix = _navigator->GetCurrentMatrix();
                _node   = _navigator->GetCurrentNode();
                _volume = _node->GetVolume();
            } else {
                _matrix = 0; _node = 0; _volume = 0;
            }
            return ret;
        }

        vector<double> fttZ( vector<double> defaultZ ) {
            double z0 = fttZ(0);
            if ( z0 > 1.0 ) { // returns 0 on faiure
                vector<double> z = {z0, fttZ(1), fttZ(2), fttZ(3)};
                return z;
            }
            return defaultZ;
        }
        double fttZ( int index ) {

            // This ftt_z_delta is needed to match the z location of hits (midpint of active volume?) to the z location of the mother volume.
            // NOTE: It may be possible to improve this when the higher precision FTT geometry model is added
            const double ftt_z_delta = -0.5825245;
            stringstream spath;
            spath << "/HALL_1/CAVE_1/STGM_1/STFM_" << (index + 1) * 4 << "/";
            bool can = cd( spath.str().c_str() );
            if ( can && _matrix != nullptr ){
                return _matrix->GetTranslation()[2] + ftt_z_delta;
            }
            return 0.0;
        }


        TVector3 getFttQuadrant( int index, TVector3 &u, TVector3 &v){
            // 0 - 15 is the front face
            // 16 - 31 is the back face

            int iquad = index % 16 + 1; // geometry is 1 - 16
            int iplane = index / 16 + 1; // geometry is 1 - 2

            stringstream spath;
            spath << "/HALL_1/CAVE_1/STGM_1/STFM_" << (iquad) << "/STMG_" << iplane << "/";
            bool can = cd( spath.str().c_str() );
            if ( can && _matrix != nullptr ){
                double x = _matrix->GetTranslation()[0];
                double y = _matrix->GetTranslation()[1];
                double z = _matrix->GetTranslation()[2];
                // u' = R u, v' = R v
                // u = (1, 0, 0) and v = (0, 1, 0)
                // where R is the rotation matrix
                u.SetXYZ(_matrix->GetRotationMatrix()[0], _matrix->GetRotationMatrix()[1], _matrix->GetRotationMatrix()[2]);
                v.SetXYZ(_matrix->GetRotationMatrix()[3], _matrix->GetRotationMatrix()[4], _matrix->GetRotationMatrix()[5]);
                return TVector3(x, y, z);
            }
            std ::cerr << "Failed to get FTT quadrant origin for index " << index << std::endl;
            return TVector3(0,0,0);
        }
    protected:
    TGeoVolume    *_volume    = nullptr;
    TGeoNode      *_node      = nullptr;
    TGeoHMatrix   *_matrix    = nullptr;
    TGeoIterator  *_iter      = nullptr;
    TGeoNavigator *_navigator = nullptr;
    TGeoManager   *_gMan      = nullptr;
};

#endif
