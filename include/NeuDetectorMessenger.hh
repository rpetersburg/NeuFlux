
/**
 * \class NeuDetectorMessenger
 *
 * \ingroup Neu
 *
 * \brief Messenger Class for Geometry, materials, and cuts.
 *
 *     Provides commands to the Intercom for setting new materials
 *     and *some* geometry commands, as well as basic cuts.Primarily
 *     interfaces with NeuDetectorConstruction.
 *
 * \note Defaults to Muon spectrum.
 *
 * \author Kevin Wierman
 * \author Michelle Leber
 *
 * \version $Revision: 1.5 $
 *
 * \date $Date: Tue Nov 20 12::33:51 2012 $
 *
 * Contact: kwierman@email.unc.edu
 *
 * Created on: Wed Apr 1 18:39:37 2005
 *
 */

#ifndef NeuDetectorMessenger_hh_
#define NeuDetectorMessenger_hh_ 

#include "globals.hh"
#include "G4UImessenger.hh"
#include "G4UIdirectory.hh"
#include "G4UIcmdWithAnInteger"
#include "G4UIcmdWithoutParameter"
#include "G4UIcmdWithAString"
#include "G4UIcmdWithADoubleAndUnit"

#include "NeuWorldGeometry.hh"

class NeuDetectorMessenger:public G4UImessenger {
 public:
   NeuDetectorMessenger(NeuWorldGeometry *);
   virtual ~ NeuDetectorMessenger();

   virtual void SetNewValue(G4UIcommand *, G4String);

 private:
    NeuWorldGeometry* fGeometry;

    G4UIdirectory* neuFluxDir;
    
    G4UIdirectory* geometryDir;
    
    G4UIDirectory* worldDir;
    G4UIDirectory* rockDir;
    G4UIDirectory* concreteDir;
    G4UIDirectory* detectorDir;

};


#endif
