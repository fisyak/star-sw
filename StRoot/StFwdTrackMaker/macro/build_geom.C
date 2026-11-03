//usr/bin/env root4star -l -b -q  $0; exit $?
// that is a valid shebang to run script as executable


void build_geom( TString geomtag = "y2023", TString output="fGeom.root" ) {

    gSystem->Load( "libStarRoot.so" );
    
    // If running outside of the STAR standard environment, you may need to run gROOT->SetMacroPath by uncommenting the lines below
    /*
    TString macroPath = ".:/star-sw/StRoot/macros/:./StRoot/macros:./StRoot/macros/graphics:./StRoot/macros/analysis:./StRoot/macros/test:./StRoot/macros/examples:./StRoot/macros/html:./StRoot/macros/qa:./StRoot/macros/calib:./StRoot/macros/mudst:$STAR_BASE_PATH/packages/DEV/StRoot/macros:$STAR_BASE_PATH/packages/DEV/StRoot/macros/graphics:$STAR_BASE_PATH/packages/DEV/StRoot/macros/analysis:$STAR_BASE_PATH/packages/DEV/StRoot/macros/test:$STAR_BASE_PATH/packages/DEV/StRoot/macros/examples:$STAR_BASE_PATH/packages/DEV/StRoot/macros/html:$STAR_BASE_PATH/packages/DEV/StRoot/macros/qa:$STAR_BASE_PATH/packages/DEV/StRoot/macros/calib:$STAR_BASE_PATH/packages/DEV/StRoot/macros/mudst:$STAR_BASE_PATH/ROOT/36/5.34.38/.sl73_x8664_gcc485/rootdeb/macros:$STAR_BASE_PATH/ROOT/36/5.34.38/.sl73_x8664_gcc485/rootdeb/tutorials";

    gSystem->ExpandPathName(macroPath);
    gROOT->SetMacroPath(macroPath);
    */

    gROOT->LoadMacro("bfc.C");
    bfc(0, "fzin agml sdt20211016", "" );

    gSystem->Load("libStarClassLibrary.so");
    gSystem->Load("libStEvent.so" );

    // Force build of the geometry
    TFile *geom = TFile::Open( output.Data() );

    if ( 0 == geom ) {
        AgModule::SetStacker( new StarTGeoStacker() );
        AgPosition::SetDebug(2);
        cout << "Building geometry for tag [" << geomtag.Data() << "]" << endl;
        StarGeometry::Construct( geomtag.Data() );

        // Genfit requires the geometry is cached in a ROOT file
        gGeoManager->Export( output.Data() );
        cout << "Writing output to geometry file [" << output.Data() << "]" << endl;
    }
    else {
        cout << "WARNING:  Geometry file [" << output.Data() << "] already exists." << endl;
        cout << "Existting without doing anything!" << endl;
        delete geom;
    }

}
