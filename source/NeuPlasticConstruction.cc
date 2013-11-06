#include "NeuPlasticConstruction.hh"

#include "G4GeometryManager.hh"
#include "G4PhysicalVolumeStore.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4SolidStore.hh"
#include "G4Box.hh"
#include "G4NistManager.hh"
#include "G4PVPlacement.hh"

#include "NeuMaterials.hh"


#include "G4SDManager.hh"


NeuFlux::NeuPlasticConstruction::NeuPlasticConstruction() : G4VUserDetectorConstruction(),
												fWorldX(100000.0*m),fWorldY(100000.0*m),fWorldZ(100000.0*m),
												fLogicWorld(0),fPhysiWorld(0)
{}

NeuFlux::NeuPlasticConstruction::~NeuPlasticConstruction()
{}

G4VPhysicalVolume* NeuFlux::NeuPlasticConstruction::Construct()
{
	if (fPhysiWorld) 
	{
	  G4GeometryManager::GetInstance()->OpenGeometry();
	  G4PhysicalVolumeStore::GetInstance()->Clean();
	  G4LogicalVolumeStore::GetInstance()->Clean();
	  G4SolidStore::GetInstance()->Clean();
	}

	G4NistManager* man = G4NistManager::Instance();

	fLogicWorld = new G4LogicalVolume(
						new G4Box("World",
	                    fWorldX/2.0,
	                    fWorldY/2.0, fWorldZ/2.0),
	                //man->FindOrBuildMaterial("G4_POLYETHYLENE"),
					man->FindOrBuildMaterial("G4_WATER"),
	                "World");

	fPhysiWorld = new G4PVPlacement(0,
					G4ThreeVector( 0.0,0.0,0.0 ),
					fLogicWorld, 
					"World", 
					0, 
					false, 
					0);

	return fPhysiWorld;
}



void NeuFlux::NeuPlasticConstruction::PrintGeometry()
{
	G4cout<<"World Geometry: "
		 <<fWorldX<<" , "		
		 <<fWorldY<<" , "			
		 <<fWorldZ<<std::endl;			
}

