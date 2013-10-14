

#ifndef NeuWorldGeometry_hh
#define NeuWorldGeometry_hh

#include "globals.hh"
#include "G4VUserDetectorConstruction.hh"
#include "G4VPhysicalVolume.hh"
#include "G4LogicalVolume.hh"

#include "NeuDetector.hh"
#include "NeuEarthFields.hh"
#include "NeuGeometryMessenger.hh"

namespace NeuFlux
{

	/*!
	  \class NeuWorldGeometry
	 
	  \ingroup NeuFlux
	 
	  \brief Code for defining the world geometry for the neutron flux at depth.
	 
	  \note Defaults to a predefined values
	 
	  \author Kevin Wierman
	 
	  \version 1.0 
	 
	  \date  Tue Nov 20 12::33:51 2012 $
	 
	  \contact kwierman@email.unc.edu
	   
	 */

	class NeuWorldGeometry : public G4VUserDetectorConstruction
	{
	public:
	   NeuWorldGeometry();
	   ~NeuWorldGeometry();

	 public:
	   G4VPhysicalVolume * Construct();
	   /*
	   G4int FindVertexVolumeIndex(const G4LogicalVolume * vertexLogicalVolume);
	   G4bool StoreEnteringParticleInfo(G4VPhysicalVolume * postVolume);
	   G4int FindPhysicalVolumeIndex(G4VPhysicalVolume * whichVolume);
	   */
	   void PrintGeometry();

	private:
		G4VPhysicalVolume* ConstructWorld();
		G4VPhysicalVolume* ConstructRock();
		G4VPhysicalVolume* ConstructConcrete();
		G4VPhysicalVolume* ConstructDetector();

	private:
		NeuFlux::NeuDetector* fDetector;
		NeuFlux::NeuGeometryMessenger* fMessenger;

		G4double fWorldX;						/*!<World X-dimension Value*/
		G4double fWorldY;						/*!<World X-dimension Value*/
		G4double fWorldZ;						/*!<World X-dimension Value*/

		G4double fRockX;						/*!<Rock X Dimension Value*/
		G4double fRockY;						/*!<Rock X Dimension Value*/
		G4double fRockZ;						/*!<Rock X Dimension Value*/

		G4double fConcreteX;					/*!< Concrete X Dimension */
		G4double fConcreteY;					/*!< Concrete X Dimension */
		G4double fConcreteZ;					/*!< Concrete X Dimension */

		G4double fDetectorX;					/*!< Detector X Dimension */
		G4double fDetectorY;					/*!< Detector Y Dimension */
		G4double fDetectorZ;					/*!< Detector Z Dimension */

		G4LogicalVolume* fLogicWorld;						/*!< an integer value */
   		G4VPhysicalVolume* fPhysiWorld;						/*!< an integer value */

   		G4LogicalVolume* fLogicRock;						/*!< an integer value */
   		G4VPhysicalVolume* fPhysiRock;						/*!< an integer value */

   		G4LogicalVolume* fLogicConcrete;						/*!< an integer value */
   		G4VPhysicalVolume* fPhysiConcrete;						/*!< an integer value */

   		G4LogicalVolume* fLogicDetector;						/*!< an integer value */
   		G4VPhysicalVolume* fPhysiDetector;						/*!< an integer value */

public:
   		void SetWorldX(G4double X)
   			{fWorldX = X;}
   		void SetWorldY(G4double Y)
   			{fWorldY = Y;}
   		void SetWorldZ(G4double Z)
   			{fWorldZ = Z;}

   		void SetRockX(G4double X)
   			{fRockX = X;}
   		void SetRockY(G4double Y)
   			{fRockY = Y;}
   		void SetRockZ(G4double Z)
   			{fRockZ = Z;}

   		void SetConcreteX(G4double X)
   			{fConcreteX = X;}
   		void SetConcreteY(G4double Y)
   			{fConcreteY = Y;}
   		void SetConcreteZ(G4double Z)
   			{fWorldZ = Z;}

   		void SetDetectorX(G4double X)
   			{fDetectorX = X;}
   		void SetDetectorY(G4double Y)
   			{fDetectorY = Y;}
   		void SetDetectorZ(G4double Z)
   			{fDetectorZ = Z;}

	};

	

}
#endif     //NeuWorldGeometry_hh


