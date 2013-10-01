#include "NeuDetectorMessenger.hh"
#include "NeuDetectorConstruction.hh"

//Geant4 headers
#include "G4Material.hh"
#include "G4UIdirectory.hh"
#include "G4UIcmdWithAnInteger.hh"
#include "G4UIcmdWithoutParameter.hh"
#include "G4UIcmdWithAString.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"
#include "G4ios.hh"

NeuFlux::NeuDetectorMessenger::NeuDetectorMessenger(NeuWorldGeometry*
                               geometry)
:  fGeometry(geometry)
{

/*
  neuFluxDir = new G4UIdirectory("/NeuFlux");
  geometryDir = new G4UIdirectory("/NeuFlux/Geometry/");  
  worldDir = new G4UIdirectory("/NeuFlux/Geometry/world");
  rockDir = new G4UIdirectory("/NeuFlux/Geometry/rock");
  concreteDir = new G4UIdirectory("/NeuFlux/Geometry/concrete");
  detectorDir = new G4UIdirectory("/NeuFlux/Geometry/detector");

  neuFluxDir->SetGuidance("UI Commands for NeuFlux Geometry");
  geometryDir->SetGuidance("UI Commands for NeuFlux Geometry");  
  worldDir->SetGuidance("UI Commands for NeuFlux Geometry");
  rockDir->SetGuidance("UI Commands for NeuFlux Geometry");
  concreteDir->SetGuidance("UI Commands for NeuFlux Geometry");
  detectorDir->SetGuidance("UI Commands for NeuFlux Geometry");

   ScintMatCmd = new G4UIcmdWithAString("/Katrin/KatrinGeometry/ScintMat", this);
   ScintMatCmd->SetGuidance("Set Scintillator material.");
   ScintMatCmd->SetParameterName("scintmat", false);
   ScintMatCmd->SetGuidance("  Choice : Plastic(default), Argon");
   ScintMatCmd->SetDefaultValue("Plastic");
   ScintMatCmd->SetCandidates("Plastic Argon");
   ScintMatCmd->AvailableForStates(G4State_PreInit, G4State_Idle);

   OutShieldMatCmd =
       new G4UIcmdWithAString("/Katrin/KatrinGeometry/OutShieldMat", this);
   OutShieldMatCmd->SetGuidance("Set Shield material.");
   OutShieldMatCmd->SetParameterName("OutShieldMat", false);
   OutShieldMatCmd->SetGuidance("  Choice : Cu(default), Pb, W");
   OutShieldMatCmd->SetDefaultValue("Cu");
   OutShieldMatCmd->SetCandidates("Cu Pb W");
   OutShieldMatCmd->AvailableForStates(G4State_PreInit, G4State_Idle);

   CoilThckCmd =
       new G4UIcmdWithADoubleAndUnit("/Katrin/KatrinGeometry/Coil_Thickness", this);
   CoilThckCmd->SetGuidance("Set thickness of magnet coils.");
   CoilThckCmd->SetParameterName("thickness", false);
   CoilThckCmd->SetDefaultUnit("cm");
   CoilThckCmd->SetUnitCategory("Length");
   CoilThckCmd->AvailableForStates(G4State_PreInit, G4State_Idle);

   UpdateCmd = new G4UIcmdWithoutParameter("/Katrin/KatrinGeometry/Update", this);
   UpdateCmd->SetGuidance("Update geometry.");
   UpdateCmd->AvailableForStates(G4State_PreInit, G4State_Idle);

   DetOffsetCmd =
       new G4UIcmdWithADoubleAndUnit("/Katrin/KatrinGeometry/DetOffset", this);
   DetOffsetCmd->SetGuidance("Set offset of detector");
   DetOffsetCmd->SetParameterName("offset", false);
   DetOffsetCmd->SetDefaultUnit("cm");
   DetOffsetCmd->SetUnitCategory("Length");
   DetOffsetCmd->AvailableForStates(G4State_PreInit, G4State_Idle);


   VisAngleCmd =
       new G4UIcmdWithADoubleAndUnit("/Katrin/KatrinGeometry/VisualizationAngle",
                                     this);
   VisAngleCmd->
       SetGuidance
       ("Set Angle of cylinders, for visualization cut-away less than 360");
   VisAngleCmd->SetParameterName("angle", false);
   VisAngleCmd->SetDefaultUnit("deg");
   VisAngleCmd->SetUnitCategory("Angle");
   VisAngleCmd->AvailableForStates(G4State_PreInit, G4State_Idle);

   DumpG4MaterialsCmd =
       new G4UIcmdWithoutParameter("/Katrin/KatrinGeometry/dumpG4materials", this);
   DumpG4MaterialsCmd->SetGuidance("Dump materials defined in G4.");
   DumpG4MaterialsCmd->AvailableForStates(G4State_Idle);

   DumpMassesCmd =
       new G4UIcmdWithoutParameter("/Katrin/KatrinGeometry/DumpMasses", this);
   DumpMassesCmd->SetGuidance("Print masses of volumes in detector.");
   DumpMassesCmd->AvailableForStates(G4State_Idle);


   CalGeomCmd = new G4UIcmdWithAString("/Katrin/KatrinGeometry/cal_geom", this);
   CalGeomCmd->SetGuidance("Toggle calibration geometry.");
   CalGeomCmd->SetParameterName("cal_geom", false);
   CalGeomCmd->
       SetGuidance("  Choice : Am-241, electron-gun, off(default)");
   CalGeomCmd->SetDefaultValue("off");
   CalGeomCmd->SetCandidates("Am-241 electron-gun off");
   CalGeomCmd->AvailableForStates(G4State_PreInit, G4State_Idle);

   AmWindowThckCmd =
       new
       G4UIcmdWithADoubleAndUnit
       ("/Katrin/KatrinGeometry/Am-241_Window_Thickness", this);
   AmWindowThckCmd->SetGuidance("Set thickness of Am-241 window");
   AmWindowThckCmd->SetParameterName("thickness", false);
   AmWindowThckCmd->SetDefaultUnit("mm");
   AmWindowThckCmd->SetUnitCategory("Length");
   AmWindowThckCmd->SetRange("thickness >= 0 && thickness < 4");
   AmWindowThckCmd->AvailableForStates(G4State_PreInit, G4State_Idle);

   CapOffsetCmd =
		new G4UIcmdWithADoubleAndUnit("/Katrin/KatrinGeometry/CapOffset", this);
   CapOffsetCmd->SetGuidance("Set offset of Americum capsule");
   CapOffsetCmd->SetParameterName("offset", false);
   CapOffsetCmd->SetDefaultUnit("cm");
   CapOffsetCmd->SetUnitCategory("Length");
   CapOffsetCmd->AvailableForStates(G4State_PreInit, G4State_Idle);
	
   cutDir = new G4UIdirectory("/Katrin/Cuts/");
   cutDir->
       SetGuidance
       ("UI commands to change energy and time cuts of detector");
   UserLmtCmd = new G4UIcmdWithAString("/Katrin/Cuts/UserLimits", this);
   UserLmtCmd->SetGuidance("Set user limits on");
   UserLmtCmd->SetParameterName("ulimit", false);
   UserLmtCmd->SetGuidance("  Choice : off(default), on");
   UserLmtCmd->SetDefaultValue("off");
   UserLmtCmd->SetCandidates("on off");
   UserLmtCmd->AvailableForStates(G4State_PreInit, G4State_Idle);
   RoomEKineCutCmd =
       new G4UIcmdWithADoubleAndUnit("/Katrin/Cuts/RoomMinEnergyCut", this);
   RoomEKineCutCmd->SetGuidance("Minimum Charged particle cut in ROOM");
   RoomEKineCutCmd->SetParameterName("ECut", false, false);
   RoomEKineCutCmd->SetRange("ECut>=250.0");
   RoomEKineCutCmd->SetDefaultUnit("eV");
   RoomEKineCutCmd->SetUnitCategory("Energy");
   RoomEKineCutCmd->AvailableForStates(G4State_PreInit, G4State_Idle);

   EKineCutCmd =
       new G4UIcmdWithADoubleAndUnit("/Katrin/Cuts/MinEnergyCut", this);
   EKineCutCmd->
       SetGuidance("Minimum Charged particle cut inside detector");
   EKineCutCmd->SetParameterName("ECut", false, false);
   EKineCutCmd->SetRange("ECut>=250.0");
   EKineCutCmd->SetDefaultUnit("eV");
   EKineCutCmd->SetUnitCategory("Energy");
   EKineCutCmd->AvailableForStates(G4State_PreInit, G4State_Idle);

   RoomTimeCutCmd =
       new G4UIcmdWithADoubleAndUnit("/Katrin/Cuts/RoomTimeCut", this);
   RoomTimeCutCmd->SetGuidance("Set Time Cut (for neutrons) inside ROOM");
   RoomTimeCutCmd->SetParameterName("RTCut", false, false);
   RoomTimeCutCmd->SetDefaultUnit("ns");
   RoomTimeCutCmd->SetUnitCategory("Time");
   RoomTimeCutCmd->AvailableForStates(G4State_PreInit, G4State_Idle);

   TimeCutCmd = new G4UIcmdWithADoubleAndUnit("/Katrin/Cuts/TimeCut", this);
   TimeCutCmd->SetGuidance("Set Time Cut (for neutrons) inside detector");
   TimeCutCmd->SetParameterName("TCut", false, false);
   TimeCutCmd->SetRange("TCut>0.");
   TimeCutCmd->SetDefaultUnit("ns");
   TimeCutCmd->SetUnitCategory("Time");
   TimeCutCmd->AvailableForStates(G4State_PreInit, G4State_Idle);
   */

}

NeuFlux::NeuDetectorMessenger::~NeuDetectorMessenger()
{
    delete neuFluxDir;
    
    delete geometryDir;
    
    delete worldDir;
    delete rockDir;
    delete concreteDir;
    delete detectorDir;

}

void NeuFlux::NeuDetectorMessenger::SetNewValue(G4UIcommand * command,
                                                 G4String newValue)
{
  /*
   if (command == ScintMatCmd) {
      NeuDetector->SetScintMat(newValue);
   } else if (command == CoilThckCmd) {
      NeuDetector->SetCoilThck(CoilThckCmd->
                                         GetNewDoubleValue(newValue));
   } else if (command == OutShieldMatCmd) {
      NeuDetector->SetOutShieldMat(newValue);
   } else if (command == UpdateCmd) {
      NeuDetector->UpdateGeometry();
   } else if (command == VisAngleCmd) {
      NeuDetector->SetVisualizationAngle(VisAngleCmd->
                                                   GetNewDoubleValue
                                                   (newValue));
   } else if (command == DumpG4MaterialsCmd) {
      G4cout << *(G4Material::GetMaterialTable());
   } else if (command == DetOffsetCmd) {
      NeuDetector->SetDetOffset(DetOffsetCmd->
                                          GetNewDoubleValue(newValue));
   } else if (command == DumpMassesCmd) {
      NeuDetector->PrintMasses();
   } else if (command == CalGeomCmd) {
      NeuDetector->SetCalibrationGeometry(newValue);
   } else if (command == AmWindowThckCmd) {
      NeuDetector->SetAmWindowThck(AmWindowThckCmd->
                                             GetNewDoubleValue(newValue));
   } else if (command == CapOffsetCmd) {
      NeuDetector->SetCalCapOffset(CapOffsetCmd->
                                          GetNewDoubleValue(newValue));
   } else if (command == UserLmtCmd) {
      NeuDetector->SetLimitOn(newValue);
   } else if (command == EKineCutCmd) {
      NeuDetector->SetEnergyCut(EKineCutCmd->GetNewDoubleValue(newValue));    //det
   } else if (command == RoomEKineCutCmd) {
      NeuDetector->
          SetRoomEnergyCut(RoomEKineCutCmd->GetNewDoubleValue(newValue));
   } else if (command == TimeCutCmd) {
      NeuDetector->
          SetTimeCut(TimeCutCmd->GetNewDoubleValue(newValue));
   } else if (command == RoomTimeCutCmd) {
      NeuDetector->
          SetRoomTimeCut(RoomTimeCutCmd->GetNewDoubleValue(newValue));
   }
   */
}
