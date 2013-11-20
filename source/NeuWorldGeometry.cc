#include "NeuWorldGeometry.hh"

#include "G4GeometryManager.hh"
#include "G4PhysicalVolumeStore.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4SolidStore.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4NistManager.hh"
#include "G4PVPlacement.hh"

#include "NeuMaterials.hh"


#include "G4SDManager.hh"


NeuFlux::NeuWorldGeometry::NeuWorldGeometry() : G4VUserDetectorConstruction(), fDetector(NULL), 
												fWorldX(50.0),fWorldY(50.0),fWorldZ(50.0),
												fRockX(fWorldX),fRockY(39.0),fRockZ(fWorldZ),
												fConcreteX(20.0),fConcreteY(5.0),fConcreteZ(20.0),
												fDetectorLength(3.0),fDetectorDiameter(0.05)
{
	fMessenger = new NeuFlux::NeuGeometryMessenger(this);	
}

NeuFlux::NeuWorldGeometry::~NeuWorldGeometry()
{
	delete fMessenger;
}

G4VPhysicalVolume* NeuFlux::NeuWorldGeometry::Construct(){

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
	                    fWorldX*0.5,
	                    fWorldY*0.5, fWorldZ*0.5),
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
	                    fRockX*0.5,
	                    fRockY*0.5, fRockZ*0.5),
	                new NeuRock(),
	                "Rock");

	fPhysiRock = new G4PVPlacement(0,
					G4ThreeVector(   0.0,(fRockY-fWorldY)*0.5, 0.0 ),
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
	                    fConcreteX*0.5,
	                    fConcreteY*0.5, fConcreteZ*0.5),
	                //new NeuConcrete(),
						man->FindOrBuildMaterial("G4_CONCRETE"),
	                "Concrete");

	fPhysiConcrete = new G4PVPlacement(0,
					G4ThreeVector(  0.0,(fConcreteY-fRockY)*0.5,  0.0 ),
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
						new G4Tubs("Detector",
						0,
						fDetectorDiameter*0.5,
	                    fDetectorLength*0.5,
						0,
						6.282),
	                man->FindOrBuildMaterial("G4_He"),
	                "Detector");

	fPhysiDetector = new G4PVPlacement(0,
					G4ThreeVector( 0.0,(fDetectorLength-fConcreteY)*0.5 ,   0.0 ),
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
		 <<fDetectorLength<<" , "		
		 <<fDetectorDiameter<<std::endl;		
}

