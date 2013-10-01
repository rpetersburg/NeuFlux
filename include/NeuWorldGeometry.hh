/*!
  \class NeuWorldGeometry
 
  \ingroup NeuFlux
 
  \brief Code for defining the world geometry for the neutron flux at depth.
 
  \note Defaults to a predefined values
 
  \author Kevin Wierman
 
  \version 1.0 
  \revision 0.0 
 
  \date  Tue Nov 20 12::33:51 2012 $
 
  Contact: kwierman@email.unc.edu
 
  Created on: Tue Oct 1 8:39:37 2013
 
 */

#ifndef NeuWorldGeometry_hh
#define NeuWorldGeometry_hh

#include "globals.hh"
#include "G4VUserDetectorConstruction.hh"

#include "NeuDetector.hh"
#include "NeuEarthFields.hh"
#include "NeuDetectorMessenger.hh"

namespace NeuFlux
{

class NeuWorldGeometry : public G4UserDetectorConstruction
{
	/// Default Constructor for the geometry.
   NeuWorldGeometry();
   /// Default Destructor. This Class owns it's logical, physical volumes and sensitive detectors.
   ~NeuWorldGeometry();

 public:
   /// Called by the Geometry Manager upon initialization.
   G4VPhysicalVolume * Construct();
   /// Retrieves the Volume index for a given Logical Volume. See .cc file for details.
   G4int FindVertexVolumeIndex(const G4LogicalVolume * vertexLogicalVolume);
   /// Returns true if the particle is entering a stored trajectory region.
   G4bool StoreEnteringParticleInfo(G4VPhysicalVolume * postVolume);
   /// See .cc file for details.
   G4int FindPhysicalVolumeIndex(G4VPhysicalVolume * whichVolume);

private:
	G4double fWorldX;
	G4double fWorldY;
	G4double fWorldZ;

	G4double fRockX;
	G4double fRockY;
	G4double fRockZ;

	G4double fCementX;
	G4double fCementY;
	G4double fCementZ;
};

}
#endif     //NeuWorldGeometry_hh