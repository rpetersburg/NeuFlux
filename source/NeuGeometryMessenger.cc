#include "NeuGeometryMessenger.hh"
#include "NeuWorldGeometry.hh"

#include "G4UIdirectory.hh"
#include "G4UIcmdWithAnInteger.hh"
#include "G4UIcmdWithoutParameter.hh"
#include "G4UIcmdWithAString.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"
#include "G4ios.hh"

NeuFlux::NeuGeometryMessenger::NeuGeometryMessenger(NeuFlux::NeuWorldGeometry* geometry)
:  fGeometry(geometry)
{
     fNeuFluxDir = new G4UIdirectory("/NeuFlux/");
     fNeuFluxDir->SetGuidance("NeuFlux Commands");
       fGeometryDir = new G4UIdirectory("/NeuFlux/Geometry/");
       fGeometryDir->SetGuidance("Neuflux Geometry Commands");
        fDumpGeometry = new G4UIcmdWithoutParameter("/NeuFlux/Geometry/Dump", this);

         fWorldDir = new G4UIdirectory("/NeuFlux/Geometry/World/");
         fWorldDir->SetGuidance("World Geometry Dimensions");
          fWorldX = new G4UIcmdWithADoubleAndUnit("/NeuFlux/Geometry/World/WorldX", this);
          fWorldY = new G4UIcmdWithADoubleAndUnit("/NeuFlux/Geometry/World/WorldY", this);
          fWorldZ = new G4UIcmdWithADoubleAndUnit("/NeuFlux/Geometry/World/WorldZ", this);
          fWorldX->SetGuidance("World Geometry Dimension");
          fWorldY->SetGuidance("World Geometry Dimension");
          fWorldZ->SetGuidance("World Geometry Dimension");
          fWorldX->SetParameterName("WorldX",false);
          fWorldY->SetParameterName("WorldY",false);
          fWorldZ->SetParameterName("WorldZ",false);
          fWorldX->SetDefaultUnit("m");
          fWorldY->SetDefaultUnit("m");
          fWorldZ->SetDefaultUnit("m");
          fWorldX->SetUnitCategory("Length");
          fWorldY->SetUnitCategory("Length");
          fWorldZ->SetUnitCategory("Length");
          fWorldX->SetUnitCategory("Length");
          fWorldY->SetUnitCategory("Length");
          fWorldZ->SetUnitCategory("Length");
          fWorldX->AvailableForStates(G4State_PreInit, G4State_Idle);
          fWorldY->AvailableForStates(G4State_PreInit, G4State_Idle);
          fWorldZ->AvailableForStates(G4State_PreInit, G4State_Idle);

         fRockDir = new G4UIdirectory("/NeuFlux/Geometry/Rock/");
         fRockDir->SetGuidance("Rock Geometry Dimensions");
          fRockX = new G4UIcmdWithADoubleAndUnit("/NeuFlux/Geometry/Rock/RockX", this);
          fRockY = new G4UIcmdWithADoubleAndUnit("/NeuFlux/Geometry/Rock/RockY", this);
          fRockZ = new G4UIcmdWithADoubleAndUnit("/NeuFlux/Geometry/Rock/RockZ", this);
          fRockX->SetGuidance("Rock Geometry Dimension");
          fRockY->SetGuidance("Rock Geometry Dimension");
          fRockZ->SetGuidance("Rock Geometry Dimension");
          fRockX->SetParameterName("RockX",false);
          fRockY->SetParameterName("RockY",false);
          fRockZ->SetParameterName("RockZ",false);
          fRockX->SetDefaultUnit("m");
          fRockY->SetDefaultUnit("m");
          fRockZ->SetDefaultUnit("m");
          fRockX->SetUnitCategory("Length");
          fRockY->SetUnitCategory("Length");
          fRockZ->SetUnitCategory("Length");
          fRockX->SetUnitCategory("Length");
          fRockY->SetUnitCategory("Length");
          fRockZ->SetUnitCategory("Length");
          fRockX->AvailableForStates(G4State_PreInit, G4State_Idle);
          fRockY->AvailableForStates(G4State_PreInit, G4State_Idle);
          fRockZ->AvailableForStates(G4State_PreInit, G4State_Idle);

         fConcreteDir = new G4UIdirectory("/NeuFlux/Geometry/Concrete/");
         fConcreteDir->SetGuidance("Concrete Geometry Dimensions");
          fConcreteX = new G4UIcmdWithADoubleAndUnit("/NeuFlux/Geometry/Concrete/ConcreteX", this);
          fConcreteY = new G4UIcmdWithADoubleAndUnit("/NeuFlux/Geometry/Concrete/ConcreteY", this);
          fConcreteZ = new G4UIcmdWithADoubleAndUnit("/NeuFlux/Geometry/Concrete/ConcreteZ", this);
          fConcreteX->SetGuidance("Concrete Geometry Dimension");
          fConcreteY->SetGuidance("Concrete Geometry Dimension");
          fConcreteZ->SetGuidance("Concrete Geometry Dimension");
          fConcreteX->SetParameterName("ConcreteX",false);
          fConcreteY->SetParameterName("ConcreteY",false);
          fConcreteZ->SetParameterName("ConcreteZ",false);
          fConcreteX->SetDefaultUnit("m");
          fConcreteY->SetDefaultUnit("m");
          fConcreteZ->SetDefaultUnit("m");
          fConcreteX->SetUnitCategory("Length");
          fConcreteY->SetUnitCategory("Length");
          fConcreteZ->SetUnitCategory("Length");
          fConcreteX->SetUnitCategory("Length");
          fConcreteY->SetUnitCategory("Length");
          fConcreteZ->SetUnitCategory("Length");
          fConcreteX->AvailableForStates(G4State_PreInit, G4State_Idle);
          fConcreteY->AvailableForStates(G4State_PreInit, G4State_Idle);
          fConcreteZ->AvailableForStates(G4State_PreInit, G4State_Idle);

         fDetectorDir = new G4UIdirectory("/NeuFlux/Geometry/Detector/");
         fDetectorDir->SetGuidance("Detector Geometry Dimensions");
          fDetectorLength = new G4UIcmdWithADoubleAndUnit("/NeuFlux/Geometry/Detector/DetectorLength", this);
          fDetectorDiameter = new G4UIcmdWithADoubleAndUnit("/NeuFlux/Geometry/Detector/DetectorDiameter", this);
          fDetectorLength->SetGuidance("Detector Geometry Dimension");
          fDetectorDiameter->SetGuidance("Detector Geometry Dimension");
          fDetectorLength->SetParameterName("DetectorLength",false);
          fDetectorDiameter->SetParameterName("DetectorDiameter",false);
          fDetectorLength->SetDefaultUnit("m");
          fDetectorDiameter->SetDefaultUnit("m");
          fDetectorLength->SetUnitCategory("Length");
          fDetectorDiameter->SetUnitCategory("Length");
          fDetectorLength->SetUnitCategory("Length");
          fDetectorDiameter->SetUnitCategory("Length");
          fDetectorLength->AvailableForStates(G4State_PreInit, G4State_Idle);
          fDetectorDiameter->AvailableForStates(G4State_PreInit, G4State_Idle);
}

NeuFlux::NeuGeometryMessenger::~NeuGeometryMessenger()
{
  delete fNeuFluxDir;
  delete fGeometryDir;
  delete fWorldDir;
  delete fWorldX;
  delete fWorldY;
  delete fWorldZ;
  delete fRockDir;
  delete fRockX;
  delete fRockY;
  delete fRockZ;
  delete fConcreteDir;
  delete fConcreteX;
  delete fConcreteY;
  delete fConcreteZ;
  delete fDetectorDir;
  delete fDetectorLength;
  delete fDetectorDiameter;

}

void NeuFlux::NeuGeometryMessenger::SetNewValue(G4UIcommand * command, G4String newValue)
{
  if(command == fWorldX)
    fGeometry->SetWorldX(fWorldX->GetNewDoubleValue(newValue));
  else if(command == fWorldY)
    fGeometry->SetWorldY(fWorldY->GetNewDoubleValue(newValue));
  else if(command == fWorldZ)
    fGeometry->SetWorldZ(fWorldZ->GetNewDoubleValue(newValue));
  else if(command == fRockX)
    fGeometry->SetRockX(fRockX->GetNewDoubleValue(newValue));
  else if(command == fRockY)
    fGeometry->SetRockY(fRockY->GetNewDoubleValue(newValue));
  else if(command == fRockZ)
    fGeometry->SetRockZ(fRockZ->GetNewDoubleValue(newValue));
  else if(command == fConcreteX)
    fGeometry->SetConcreteX(fConcreteX->GetNewDoubleValue(newValue));
  else if(command == fConcreteY)
    fGeometry->SetConcreteY(fConcreteY->GetNewDoubleValue(newValue));
  else if(command == fConcreteZ)
    fGeometry->SetConcreteZ(fConcreteZ->GetNewDoubleValue(newValue));
  else if(command == fDetectorLength)
    fGeometry->SetDetectorLength(fDetectorLength->GetNewDoubleValue(newValue));
  else if(command == fDetectorDiameter)
    fGeometry->SetDetectorDiameter(fDetectorDiameter->GetNewDoubleValue(newValue));
  else if(command == fDumpGeometry)
    fGeometry->PrintGeometry();

}
