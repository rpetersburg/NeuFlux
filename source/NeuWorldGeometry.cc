#include "NeuWorldGeometry.hh"

#include "G4GeometryManager.hh"
#include "G4PhysicalVolumeStore.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4SolidStore.hh"
#include "G4Box.hh"
#include "G4NistManager.hh"
#include "G4PVPlacement.hh"

#include "NeuMaterials.hh"


#include "G4SDManager.hh"


NeuFlux::NeuWorldGeometry::NeuWorldGeometry() : G4VUserDetectorConstruction(), fDetector(NULL), 
												fWorldX(1000.0),fWorldY(1000.0),fWorldZ(1000.0),
												fRockX(1000.0),fRockY(900.0),fRockZ(1000.0),
												fConcreteX(150.0),fConcreteY(150.0),fConcreteZ(150.0),
												fDetectorX(100),fDetectorY(100.0),fDetectorZ(100.0)
{
	fMessenger = new NeuFlux::NeuGeometryMessenger(this);	
}

NeuFlux::NeuWorldGeometry::~NeuWorldGeometry()
{
	delete fMessenger;
}

G4VPhysicalVolume* NeuFlux::NeuWorldGeometry::Construct()
{
	if (fPhysiWorld) 
	{
	  G4GeometryManager::GetInstance()->OpenGeometry();
	  G4PhysicalVolumeStore::GetInstance()->Clean();
	  G4LogicalVolumeStore::GetInstance()->Clean();
	  G4SolidStore::GetInstance()->Clean();
	}
	return ConstructWorld();
}

/*
G4int FindVertexVolumeIndex(const G4LogicalVolume * vertexLogicalVolume)
{
	return 0;
}
G4bool NeuFlux::NeuWorldGeometry::StoreEnteringParticleInfo(G4VPhysicalVolume * postVolume)
{
	return false;
}
G4int NeuFlux::NeuWorldGeometry::FindPhysicalVolumeIndex(G4VPhysicalVolume * whichVolume)
{
	return 0;
}
*/

G4VPhysicalVolume* NeuFlux::NeuWorldGeometry::ConstructWorld()
{
	G4NistManager* man = G4NistManager::Instance();
	fLogicWorld = new G4LogicalVolume(
						new G4Box("World",
	                    fWorldX*2.0,
	                    fWorldY*2.0, fWorldZ*2.0),
	                man->FindOrBuildMaterial("G4_AIR"),
	                "World");

	fPhysiWorld = new G4PVPlacement(0,
					G4ThreeVector(),
					fLogicWorld, 
					"World", 
					0, false, 0);
	ConstructRock();
	return fPhysiWorld;
}
G4VPhysicalVolume* NeuFlux::NeuWorldGeometry::ConstructRock()
{
	fLogicRock = new G4LogicalVolume(
						new G4Box("Rock",
	                    fRockX*2.0,
	                    fRockY*2.0, fRockZ*2.0),
	                new NeuRock(),
	                "Rock");

	fPhysiRock = new G4PVPlacement(0,
					G4ThreeVector(   0.0,(fRockY-fWorldY)*2.0, 0.0 ),
					fLogicRock, 
					"Rock", 
					fLogicWorld, 
					false, 
					0);
	ConstructConcrete();
	return fPhysiRock;
}
G4VPhysicalVolume* NeuFlux::NeuWorldGeometry::ConstructConcrete()
{
	G4NistManager* man = G4NistManager::Instance();
	fLogicConcrete = new G4LogicalVolume(
						new G4Box("Concrete",
	                    fConcreteX*2.0,
	                    fConcreteY*2.0, fConcreteZ*2.0),
	                //new NeuConcrete(),
						man->FindOrBuildMaterial("G4_CONCRETE"),
	                "Concrete");

	fPhysiConcrete = new G4PVPlacement(0,
					G4ThreeVector(  0.0,(fConcreteY-fRockY)*2.0,  0.0 ),
					fLogicConcrete, 
					"Concrete", 
					fLogicRock, 
					false, 
					0);
	ConstructDetector();
	return fPhysiConcrete;
}
G4VPhysicalVolume* NeuFlux::NeuWorldGeometry::ConstructDetector()
{
	G4NistManager* man = G4NistManager::Instance();

	fLogicDetector = new G4LogicalVolume(
						new G4Box("Detector",
	                    fDetectorX*2.0,
	                    fDetectorY*2.0, fDetectorZ*2.0),
	                man->FindOrBuildMaterial("G4_POLYTRIFLUOROCHLOROETHYLENE"),
	                "Detector");

	fPhysiDetector = new G4PVPlacement(0,
					G4ThreeVector( 0.0,(fDetectorY-fConcreteY)*2.0 ,   0.0 ),
					fLogicDetector, 
					"Detector", 
					fLogicConcrete, 
					false, 
					0);



	G4SDManager *SDman = G4SDManager::GetSDMpointer();
	if(!fDetector)
	{
		fDetector = new NeuFlux::NeuDetector();	
		SDman->AddNewDetector(fDetector);	
		fLogicDetector->SetSensitiveDetector(fDetector);
	}
	return fPhysiDetector;
}

void NeuFlux::NeuWorldGeometry::PrintGeometry()
{
	G4cout<<"World Geometry: "
		 <<fWorldX<<" , "		
		 <<fWorldY<<" , "			
		 <<fWorldZ<<std::endl;			

	G4cout<<"Rock Geometry: "
		 <<fRockX<<" , "			
		 <<fRockY<<" , "			
		 <<fRockZ<<std::endl;		

	G4cout<<"Concrete Geometry: "
		 <<fConcreteX<<" , "		
		 <<fConcreteY<<" , "		
		 <<fConcreteZ<<std::endl;	
	G4cout<<"Detector Geometry: "
		 <<fDetectorX<<" , "		
		 <<fDetectorY<<" , "		
		 <<fDetectorZ<<std::endl;		
}

