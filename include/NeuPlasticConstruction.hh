

#ifndef NeuPlasticConstruction_hh_
#define NeuPlasticConstruction_hh_

#include "globals.hh"
#include "G4VUserDetectorConstruction.hh"
#include "G4VPhysicalVolume.hh"
#include "G4LogicalVolume.hh"

namespace NeuFlux
{

	/*!
	  \class NeuPlasticConstruction
	 
	  \ingroup NeuFlux
	 
	  \brief Code for defining the world geometry for the neutron flux at depth.
	 
	  \note Defaults to a predefined values
	 
	  \author Kevin Wierman
	 
	  \version 1.0 
	 
	  \date  Tue Nov 20 12::33:51 2012 $
	 
	  \contact kwierman@email.unc.edu
	   
	 */

	class NeuPlasticConstruction : public G4VUserDetectorConstruction
	{
	public:
	   NeuPlasticConstruction();
	   ~NeuPlasticConstruction();

	 public:
	   G4VPhysicalVolume * Construct();
	   void PrintGeometry();


	private:
		G4double fWorldX;						/*!<World X-dimension Value*/
		G4double fWorldY;						/*!<World X-dimension Value*/
		G4double fWorldZ;						/*!<World X-dimension Value*/


		G4LogicalVolume* fLogicWorld;						/*!< an integer value */
   		G4VPhysicalVolume* fPhysiWorld;						/*!< an integer value */

public:
   		void SetWorldX(G4double X)
   			{fWorldX = X;}
   		void SetWorldY(G4double Y)
   			{fWorldY = Y;}
   		void SetWorldZ(G4double Z)
   			{fWorldZ = Z;}
	};	

}
#endif     //NeuPlasticConstruction_hh_


