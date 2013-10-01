NeuFlux::NeuWorldGeometry::NeuWorldGeometry() : G4UserDetectorConstruction(), 
												fWorldX(10.0),fWorldY(10.0),fWorldZ(10.0),
												fRockX(10.0),fRockY(10.0),fRockZ(9.0),
												fConcreteX(0.5),fConcreteY(0.5),fConcreteZ(0.5),
												fDetectorX(1.0),fDetectorY(1.0),fDetectorZ(1.0)
{

	//setup the messenger here... if you dare.
}
NeuFlux::NeuWorldGeometry::~NeuWorldGeometry()
{

	if(fDetector)
		delete fDetector;
}
G4VPhysicalVolume* NeuFlux::NeuWorldGeometry::Construct()
{
	//Clean old geometry, if any
	if (physiWorld) {
	  G4GeometryManager::GetInstance()->OpenGeometry();
	  G4PhysicalVolumeStore::GetInstance()->Clean();
	  G4LogicalVolumeStore::GetInstance()->Clean();
	  G4SolidStore::GetInstance()->Clean();
	}

	return ConstructWorld();
}
G4int FindVertexVolumeIndex(const G4LogicalVolume * vertexLogicalVolume)
{

}
G4bool NeuFlux::NeuWorldGeometry::StoreEnteringParticleInfo(G4VPhysicalVolume * postVolume)
{

}
G4int NeuFlux::NeuWorldGeometry::FindPhysicalVolumeIndex(G4VPhysicalVolume * whichVolume)
{

}

G4VPhysicalVolume* NeuFlux::NeuWorldGeometry::ConstructWorld()
{
	fLogicWorld = new G4LogicalVolume(
						new G4Box("World",
	                    fWorldX,
	                    fWorldY, fWorldZ),
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
	                    fRockX,
	                    fRockY, fRockZ),
	                new NeuRock(),
	                "Rock");

	fPhysiRock = new G4PVPlacement(0,
					G4ThreeVector( (fWorldX-fRockX)/2.0, (fWorldY-fRockY)/2.0,  0),
					fLogicRock, 
					"Rock", 
					fLogicWorld, false, 0);
	ConstructConcrete();
	return fPhysiRock;
}
G4VPhysicalVolume* NeuFlux::NeuWorldGeometry::ConstructConcrete()
{
	fLogicConcrete = new G4LogicalVolume(
						new G4Box("Concrete",
	                    fConcreteX,
	                    fConcreteY, fConcreteZ),
	                new NeuConcrete(),
	                "Concrete");

	fPhysiConcrete = new G4PVPlacement(0,
					G4ThreeVector( (fRockX-fConcreteX)/2.0, (fRockY-fConcreteY)/2.0,  0),
					fLogicConcrete, 
					"Concrete", 
					fLogicRock, false, 0);
	ConstructDetector();
	return fPhysiConcrete;
}
G4VPhysicalVolume* NeuFlux::NeuWorldGeometry::ConstructDetector()
{
	fLogicDetector = new G4LogicalVolume(
						new G4Box("Detector",
	                    fDetectorX,
	                    fDetectorY, fDetectorZ),
	                man->FindOrBuildMaterial("G4_AIR"),
	                "Detector");

	fPhysiDetector = new G4PVPlacement(0,
					G4ThreeVector(),
					fLogicDetector, 
					"Detector", 
					0, false, 0);



	G4SDManager *SDman = G4SDManager::GetSDMpointer();
	if(!fDetector)
	{
		fDetector = new NeuFlux::NeuDetector();	
		SDman->AddNewDetector(fDetector);	
	}
	fLogicDetector->SetSensitiveDetector(fDetector);
	return fPhysiDetector;
}


