///     Geant4 user includes
#include "KDSRunAction.hh"
#include "KDSEventAction.hh"
///     Geant4 package includes
#include "G4RunManager.hh"
#include "G4Run.hh"
#include "G4UImanager.hh"
#include "G4VVisManager.hh"
#include "G4ios.hh"

///     ------++++++------++++++------++++++------++++++------
///                                     KDSRunAction()
///     ------++++++------++++++------++++++------++++++------
KDSRunAction::KDSRunAction(G4int time)
:  timeSeed(time)
{
   rootFile = new TFile();
   tree = new TTree();
}

//      ------++++++------++++++------++++++------++++++------
//                                      ~KDSRunAction()
//      ------++++++------++++++------++++++------++++++------
KDSRunAction::~KDSRunAction()
{
   delete rootFile;
   // don't delete tree because closing rootfile deletes the trees
}

//      ------++++++------++++++------++++++------++++++------
//                                      BeginOfRunAction()
//      ------++++++------++++++------++++++------++++++------
void KDSRunAction::BeginOfRunAction(const G4Run * aRun)
{
	std::cout<<"---------------------------------------"<<std::endl;
	std::cout<<"Beginning Run: "<<aRun->GetNumberOfEvent()<<std::endl;

   id = aRun->GetRunID();
   if (G4VVisManager::GetConcreteInstance()) {
      G4UImanager *UI = G4UImanager::GetUIpointer();
      UI->ApplyCommand("/vis/scene/notifyHandlers");
   }
   NameRootFile();
   SetRootBranches();
   std::cout<<"---------------------------------------"<<std::endl;
}

//      ------++++++------++++++------++++++------++++++------
//                                      EndOfRunAction()
//      ------++++++------++++++------++++++------++++++------
void KDSRunAction::EndOfRunAction(const G4Run * aRun)
{
	std::cout<<"---------------------------------------"<<std::endl;
	std::cout<<"Finishing up Run: "<<aRun->GetNumberOfEvent()<<std::endl;


   tree->Write();
   rootFile->Write();
   rootFile->Close();
   // closing file deletes tree

   if (G4VVisManager::GetConcreteInstance()) {
      G4UImanager::GetUIpointer()->ApplyCommand("/vis/viewer/update");
   }
   std::cout<<"---------------------------------------"<<std::endl;
}

void KDSRunAction::NameRootFile()
{
   // Create the filename and open the file for writing              
   KDSEventAction *theEvent = (KDSEventAction*)
       G4RunManager::GetRunManager()->GetUserEventAction();
   
   char timeString[100];
   sprintf(timeString, "%d", timeSeed);
  
   char RunString[100];
   sprintf(RunString, "%i", id);

   ///       Create fileName and rootName
   char rootName[1000];
   strcpy(rootName, "Katrin_");
   strcat(rootName, *theEvent->GetSpectrum());
   strcat(rootName, "_");
   strcat(rootName, timeString);
   strcat(rootName, RunString);
   strcat(rootName, ".root");
   ///       Create rootTitle   
   char rootTitle[100] = "Info from Katrin Det Simulation";
   std::cout<<"RootFile Title: "<<rootTitle<<std::endl;


   TFile *tempFile = new TFile(rootName, "RECREATE", rootTitle);
   rootFile = tempFile;
}

void KDSRunAction::SetRootBranches()
{

	//retrieve the eventAction
  KDSEventAction *theEvent = (KDSEventAction *)
       G4RunManager::GetRunManager()->GetUserEventAction();

   ///       Create rootTitle   
   char rootTitle[100] = "Info from Katrin Det Simulation";
   TTree *tempTree = new TTree("kdsTree", rootTitle);

   tempTree->Branch("Event", theEvent->GetEvent(), "Event/I");
   // initial condition arrays
   tempTree->Branch("numInitial", theEvent->GetNInitial(), "numInitial/I");
   tempTree->Branch("Initial Energy keV", theEvent->GetInitialEnergy(),
                    "InitialEnergykeV[numInitial]/D");
   tempTree->Branch("InitialPlanePositionX cm",
                    theEvent->GetInitialPlanePositionX(),
                    "InitialPlanePositionXcm/D");
   tempTree->Branch("InitialPlanePositionY cm",
                    theEvent->GetInitialPlanePositionY(),
                    "InitialPlanePositionYcm/D");
   tempTree->Branch("InitialPlanePositionZ cm",
                    theEvent->GetInitialPlanePositionZ(),
                    "InitialPlanePositionZcm/D");
   tempTree->Branch("InitialPositionX cm", theEvent->GetInitialPositionX(),
                    "InitialPositionXcm/D");
   tempTree->Branch("InitialPositionY cm", theEvent->GetInitialPositionY(),
                    "InitialPositionYcm/D");
   tempTree->Branch("InitialPositionZ cm", theEvent->GetInitialPositionZ(),
                    "InitialPositionZcm/D");
   tempTree->Branch("InitialMomDirX", theEvent->GetInitialMomDirX(),
                    "InitialMomDirX[numInitial]/D");
   tempTree->Branch("InitialMomDirY", theEvent->GetInitialMomDirY(),
                    "InitialMomDirY[numInitial]/D");
   tempTree->Branch("InitialMomDirZ", theEvent->GetInitialMomDirZ(),
                    "InitialMomDirZ[numInitial]/D");
   tempTree->Branch("InitialMomTheta", theEvent->GetMomTheta(),
                    "InitialMomTheta[numInitial]/D");
   tempTree->Branch("InitialMomPhi", theEvent->GetMomPhi(),
                    "InitialMomPhi[numInitial]/D");
   tempTree->Branch("Initial Dot Product Pos Mom",
                    theEvent->GetDotProduct(),
                    "InitialDotProductPosMom[numInitial]/D");
   tempTree->Branch("Initial PDG Code", theEvent->GetInitialPDG(),
                    "InitialPDGCode[numInitial]/I");
   tempTree->Branch("ParentElement", theEvent->GetParentElement(),
                    "ParentElement/I");
	// decay arrays              
   tempTree->Branch("num Decay", theEvent->GetNDecay(), "numDecay/I");
   tempTree->Branch("Decay PDG Code",
                    theEvent->GetDecayIncidentParticles()->PDG,
                    "DecayPDGCode[numDecay]/I");
   tempTree->Branch("Decay Track ID",
                    theEvent->GetDecayIncidentParticles()->TrackID,
                    "DecayTrackID[numDecay]/I");
   tempTree->Branch("Decay Parent ID ",
                    theEvent->GetDecayIncidentParticles()->ParentID,
                    "DecayParentID[numDecay]/I");
   tempTree->Branch("DecayPrimaryParentPDG",
                    theEvent->GetDecayIncidentParticles()->
                    PrimaryParentPDG, "DecayPrimaryParentPDG[numDecay]/I");
   tempTree->Branch("DecayCreatorProcess ",
                    theEvent->GetDecayIncidentParticles()->CreatorProcess,
                    "DecayCreatorProcess[numDecay]/I");
   tempTree->Branch("DecayVertexVolume",
                    theEvent->GetDecayIncidentParticles()->VertexVolume,
                    "DecayVertexVolume[numDecay]/I");
   tempTree->Branch("DecayVertexEnergykeV",
                    theEvent->GetDecayIncidentParticles()->VertexEnergykeV,
                    "DecayVertexEnergykeV[numDecay]/D");
   tempTree->Branch("DecayVertexPositionXcm",
                    theEvent->GetDecayIncidentParticles()->
                    VertexPositionXcm,
                    "DecayVertexPositionXcm[numDecay]/D");
   tempTree->Branch("DecayVertexPositionYcm",
                    theEvent->GetDecayIncidentParticles()->
                    VertexPositionYcm,
                    "DecayVertexPositionYcm[numDecay]/D");
   tempTree->Branch("DecayVertexPositionZcm",
                    theEvent->GetDecayIncidentParticles()->
                    VertexPositionZcm,
                    "DecayVertexPositionZcm[numDecay]/D");
   tempTree->Branch("DecayIncidentPositionXcm",
                    theEvent->GetDecayIncidentParticles()->
                    IncidentPositionXcm,
                    "DecayIncidentPositionXcm[numDecay]/D");
   tempTree->Branch("DecayIncidentPositionYcm",
                    theEvent->GetDecayIncidentParticles()->
                    IncidentPositionYcm,
                    "DecayIncidentPositionYcm[numDecay]/D");
   tempTree->Branch("DecayIncidentPositionZcm",
                    theEvent->GetDecayIncidentParticles()->
                    IncidentPositionZcm,
                    "DecayIncidentPositionZcm[numDecay]/D");
   tempTree->Branch("DecayIncidentMomentumX",
                    theEvent->GetDecayIncidentParticles()->
                    IncidentMomentumX,
                    "DecayIncidentMomentumX[numDecay]/D");
   tempTree->Branch("DecayIncidentMomentumY",
                    theEvent->GetDecayIncidentParticles()->
                    IncidentMomentumY,
                    "DecayIncidentMomentumY[numDecay]/D");
   tempTree->Branch("DecayIncidentMomentumZ",
                    theEvent->GetDecayIncidentParticles()->
                    IncidentMomentumZ,
                    "DecayIncidentMomentumZ[numDecay]/D");
   tempTree->Branch("Decay DotProduct Incident Pos Mom",
                    theEvent->GetDecayIncidentParticles()->
                    DotProductIncPosMom,
                    "DecayDotProductIncidentPosMom[numDecay]/D");
   tempTree->Branch("Decay Incident Energy keV",
                    theEvent->GetDecayIncidentParticles()->
                    IncidentEnergykeV,
                    "DecayIncidentEnergykeV[numDecay]/D");
   tempTree->Branch("Decay Time ns",
                    theEvent->GetDecayIncidentParticles()->Timens,
                    "DecayTimens[numDecay]/D");
	
	// Killed arrays              
   tempTree->Branch("num Killed", theEvent->GetNKilled(), "numKilled/I");
   tempTree->Branch("Killed PDG Code",
                    theEvent->GetKilledIncidentParticles()->PDG,
                    "KilledPDGCode[numKilled]/I");
   tempTree->Branch("Killed Track ID",
                    theEvent->GetKilledIncidentParticles()->TrackID,
                    "KilledTrackID[numKilled]/I");
   tempTree->Branch("Killed Parent ID ",
                    theEvent->GetKilledIncidentParticles()->ParentID,
                    "KilledParentID[numKilled]/I");
   tempTree->Branch("KilledPrimaryParentPDG",
                    theEvent->GetKilledIncidentParticles()->
                    PrimaryParentPDG, "KilledPrimaryParentPDG[numKilled]/I");
   tempTree->Branch("KilledCreatorProcess ",
                    theEvent->GetKilledIncidentParticles()->CreatorProcess,
                    "KilledCreatorProcess[numKilled]/I");
   tempTree->Branch("KilledVertexVolume",
                    theEvent->GetKilledIncidentParticles()->VertexVolume,
                    "KilledVertexVolume[numKilled]/I");
   tempTree->Branch("KilledVertexEnergykeV",
                    theEvent->GetKilledIncidentParticles()->VertexEnergykeV,
                    "KilledVertexEnergykeV[numKilled]/D");
   tempTree->Branch("KilledVertexPositionXcm",
                    theEvent->GetKilledIncidentParticles()->
                    VertexPositionXcm,
                    "KilledVertexPositionXcm[numKilled]/D");
   tempTree->Branch("KilledVertexPositionYcm",
                    theEvent->GetKilledIncidentParticles()->
                    VertexPositionYcm,
                    "KilledVertexPositionYcm[numKilled]/D");
   tempTree->Branch("KilledVertexPositionZcm",
                    theEvent->GetKilledIncidentParticles()->
                    VertexPositionZcm,
                    "KilledVertexPositionZcm[numKilled]/D");
   tempTree->Branch("KilledIncidentPositionXcm",
                    theEvent->GetKilledIncidentParticles()->
                    IncidentPositionXcm,
                    "KilledIncidentPositionXcm[numKilled]/D");
   tempTree->Branch("KilledIncidentPositionYcm",
                    theEvent->GetKilledIncidentParticles()->
                    IncidentPositionYcm,
                    "KilledIncidentPositionYcm[numKilled]/D");
   tempTree->Branch("KilledIncidentPositionZcm",
                    theEvent->GetKilledIncidentParticles()->
                    IncidentPositionZcm,
                    "KilledIncidentPositionZcm[numKilled]/D");
   tempTree->Branch("KilledIncidentMomentumX",
                    theEvent->GetKilledIncidentParticles()->
                    IncidentMomentumX,
                    "KilledIncidentMomentumX[numKilled]/D");
   tempTree->Branch("KilledIncidentMomentumY",
                    theEvent->GetKilledIncidentParticles()->
                    IncidentMomentumY,
                    "KilledIncidentMomentumY[numKilled]/D");
   tempTree->Branch("KilledIncidentMomentumZ",
                    theEvent->GetKilledIncidentParticles()->
                    IncidentMomentumZ,
                    "KilledIncidentMomentumZ[numKilled]/D");
   tempTree->Branch("Killed DotProduct Incident Pos Mom",
                    theEvent->GetKilledIncidentParticles()->
                    DotProductIncPosMom,
                    "KilledDotProductIncidentPosMom[numKilled]/D");
   tempTree->Branch("Killed Incident Energy keV",
                    theEvent->GetKilledIncidentParticles()->
                    IncidentEnergykeV,
                    "KilledIncidentEnergykeV[numKilled]/D");
   tempTree->Branch("Killed Time ns",
                    theEvent->GetKilledIncidentParticles()->Timens,
                    "KilledTimens[numKilled]/D");
   //the following are detector-geometry specific	
// detector arrays              
   tempTree->Branch("num Det", theEvent->GetNDet(), "numDet/I");
   tempTree->Branch("Det PDG Code",
                    theEvent->GetDetIncidentParticles()->PDG,
                    "DetPDGCode[numDet]/I");
   tempTree->Branch("Det Track ID",
                    theEvent->GetDetIncidentParticles()->TrackID,
                    "DetTrackID[numDet]/I");
   tempTree->Branch("Det Parent ID ",
                    theEvent->GetDetIncidentParticles()->ParentID,
                    "DetParentID[numDet]/I");
   tempTree->Branch("DetPrimaryParentPDG",
                    theEvent->GetDetIncidentParticles()->PrimaryParentPDG,
                    "DetPrimaryParentPDG[numDet]/I");
   tempTree->Branch("DetCreatorProcess ",
                    theEvent->GetDetIncidentParticles()->CreatorProcess,
                    "DetCreatorProcess[numDet]/I");
   tempTree->Branch("DetVertexVolume",
                    theEvent->GetDetIncidentParticles()->VertexVolume,
                    "DetVertexVolume[numDet]/I");
   tempTree->Branch("DetVertexEnergykeV",
                    theEvent->GetDetIncidentParticles()->VertexEnergykeV,
                    "DetVertexEnergykeV[numDet]/D");
   tempTree->Branch("DetVertexPositionXcm",
                    theEvent->GetDetIncidentParticles()->VertexPositionXcm,
                    "DetVertexPositionXcm[numDet]/D");
   tempTree->Branch("DetVertexPositionYcm",
                    theEvent->GetDetIncidentParticles()->VertexPositionYcm,
                    "DetVertexPositionYcm[numDet]/D");
   tempTree->Branch("DetVertexPositionZcm",
                    theEvent->GetDetIncidentParticles()->VertexPositionZcm,
                    "DetVertexPositionZcm[numDet]/D");
   tempTree->Branch("DetIncidentPositionXcm",
                    theEvent->GetDetIncidentParticles()->
                    IncidentPositionXcm,
                    "DetIncidentPositionXcm[numDet]/D");
   tempTree->Branch("DetIncidentPositionYcm",
                    theEvent->GetDetIncidentParticles()->
                    IncidentPositionYcm,
                    "DetIncidentPositionYcm[numDet]/D");
   tempTree->Branch("DetIncidentPositionZcm",
                    theEvent->GetDetIncidentParticles()->
                    IncidentPositionZcm,
                    "DetIncidentPositionZcm[numDet]/D");
   tempTree->Branch("DetIncidentMomentumX",
                    theEvent->GetDetIncidentParticles()->IncidentMomentumX,
                    "DetIncidentMomentumX[numDet]/D");
   tempTree->Branch("DetIncidentMomentumY",
                    theEvent->GetDetIncidentParticles()->IncidentMomentumY,
                    "DetIncidentMomentumY[numDet]/D");
   tempTree->Branch("DetIncidentMomentumZ",
                    theEvent->GetDetIncidentParticles()->IncidentMomentumZ,
                    "DetIncidentMomentumZ[numDet]/D");
   tempTree->Branch("Det DotProduct Incident Pos Mom",
                    theEvent->GetDetIncidentParticles()->
                    DotProductIncPosMom,
                    "DetDotProductIncidentPosMom[numDet]/D");
   tempTree->Branch("Det Incident Energy keV",
                    theEvent->GetDetIncidentParticles()->IncidentEnergykeV,
                    "DetIncidentEnergykeV[numDet]/D");
   tempTree->Branch("Det Time ns",
                    theEvent->GetDetIncidentParticles()->Timens,
                    "DetTimens[numDet]/D");
// air arrays
   tempTree->Branch("num Air", theEvent->GetNAir(), "numAir/I");
   tempTree->Branch("Air PDG Code",
                    theEvent->GetAirIncidentParticles()->PDG,
                    "AirPDGCode[numAir]/I");
   tempTree->Branch("Air Track ID",
                    theEvent->GetAirIncidentParticles()->TrackID,
                    "AirTrackID[numAir]/I");
   tempTree->Branch("Air Parent ID ",
                    theEvent->GetAirIncidentParticles()->ParentID,
                    "AirParentID[numAir]/I");
   tempTree->Branch("AirPrimaryParentPDG",
                    theEvent->GetAirIncidentParticles()->PrimaryParentPDG,
                    "AirPrimaryParentPDG[numAir]/I");
   tempTree->Branch("AirCreatorProcess ",
                    theEvent->GetAirIncidentParticles()->CreatorProcess,
                    "AirCreatorProcess[numAir]/I");
   tempTree->Branch("AirVertexVolume",
                    theEvent->GetAirIncidentParticles()->VertexVolume,
                    "AirVertexVolume[numAir]/I");
   tempTree->Branch("AirVertexEnergykeV",
                    theEvent->GetAirIncidentParticles()->VertexEnergykeV,
                    "AirVertexEnergykeV[numAir]/D");
   tempTree->Branch("AirVertexPositionXcm",
                    theEvent->GetAirIncidentParticles()->VertexPositionXcm,
                    "AirVertexPositionXcm[numAir]/D");
   tempTree->Branch("AirVertexPositionYcm",
                    theEvent->GetAirIncidentParticles()->VertexPositionYcm,
                    "AirVertexPositionYcm[numAir]/D");
   tempTree->Branch("AirVertexPositionZcm",
                    theEvent->GetAirIncidentParticles()->VertexPositionZcm,
                    "AirVertexPositionZcm[numAir]/D");
   tempTree->Branch("AirIncidentPositionXcm",
                    theEvent->GetAirIncidentParticles()->
                    IncidentPositionXcm,
                    "AirIncidentPositionXcm[numAir]/D");
   tempTree->Branch("AirIncidentPositionYcm",
                    theEvent->GetAirIncidentParticles()->
                    IncidentPositionYcm,
                    "AirIncidentPositionYcm[numAir]/D");
   tempTree->Branch("AirIncidentPositionZcm",
                    theEvent->GetAirIncidentParticles()->
                    IncidentPositionZcm,
                    "AirIncidentPositionZcm[numAir]/D");
   tempTree->Branch("AirIncidentMomentumX",
                    theEvent->GetAirIncidentParticles()->IncidentMomentumX,
                    "AirIncidentMomentumX[numAir]/D");
   tempTree->Branch("AirIncidentMomentumY",
                    theEvent->GetAirIncidentParticles()->IncidentMomentumY,
                    "AirIncidentMomentumY[numAir]/D");
   tempTree->Branch("AirIncidentMomentumZ",
                    theEvent->GetAirIncidentParticles()->IncidentMomentumZ,
                    "AirIncidentMomentumZ[numAir]/D");
   tempTree->Branch("AirDotProduct Incident Pos Mom",
                    theEvent->GetAirIncidentParticles()->
                    DotProductIncPosMom,
                    "AirDotProductIncidentPosMom[numAir]/D");
   tempTree->Branch("Air Incident Energy keV",
                    theEvent->GetAirIncidentParticles()->IncidentEnergykeV,
                    "AirIncidentEnergykeV[numAir]/D");
   tempTree->Branch("Air Time ns",
                    theEvent->GetAirIncidentParticles()->Timens,
                    "AirTimens[numAir]/D");
	// OShield arrays
   tempTree->Branch("num OShield", theEvent->GetNOShield(), "numOShield/I");
   tempTree->Branch("OShield PDG Code",
                    theEvent->GetOShieldIncidentParticles()->PDG,
                    "OShieldPDGCode[numOShield]/I");
   tempTree->Branch("OShield Track ID",
                    theEvent->GetOShieldIncidentParticles()->TrackID,
                    "OShieldTrackID[numOShield]/I");
   tempTree->Branch("OShield Parent ID ",
                    theEvent->GetOShieldIncidentParticles()->ParentID,
                    "OShieldParentID[numOShield]/I");
   tempTree->Branch("OShieldPrimaryParentPDG",
                    theEvent->GetOShieldIncidentParticles()->PrimaryParentPDG,
                    "OShieldPrimaryParentPDG[numOShield]/I");
   tempTree->Branch("OShieldCreatorProcess ",
                    theEvent->GetOShieldIncidentParticles()->CreatorProcess,
                    "OShieldCreatorProcess[numOShield]/I");
   tempTree->Branch("OShieldVertexVolume",
                    theEvent->GetOShieldIncidentParticles()->VertexVolume,
                    "OShieldVertexVolume[numOShield]/I");
   tempTree->Branch("OShieldVertexEnergykeV",
                    theEvent->GetOShieldIncidentParticles()->VertexEnergykeV,
                    "OShieldVertexEnergykeV[numOShield]/D");
   tempTree->Branch("OShieldVertexPositionXcm",
                    theEvent->GetOShieldIncidentParticles()->VertexPositionXcm,
                    "OShieldVertexPositionXcm[numOShield]/D");
   tempTree->Branch("OShieldVertexPositionYcm",
                    theEvent->GetOShieldIncidentParticles()->VertexPositionYcm,
                    "OShieldVertexPositionYcm[numOShield]/D");
   tempTree->Branch("OShieldVertexPositionZcm",
                    theEvent->GetOShieldIncidentParticles()->VertexPositionZcm,
                    "OShieldVertexPositionZcm[numOShield]/D");
   tempTree->Branch("OShieldIncidentPositionXcm",
                    theEvent->GetOShieldIncidentParticles()->
                    IncidentPositionXcm,
                    "OShieldIncidentPositionXcm[numOShield]/D");
   tempTree->Branch("OShieldIncidentPositionYcm",
                    theEvent->GetOShieldIncidentParticles()->
                    IncidentPositionYcm,
                    "OShieldIncidentPositionYcm[numOShield]/D");
   tempTree->Branch("OShieldIncidentPositionZcm",
                    theEvent->GetOShieldIncidentParticles()->
                    IncidentPositionZcm,
                    "OShieldIncidentPositionZcm[numOShield]/D");
   tempTree->Branch("OShieldIncidentMomentumX",
                    theEvent->GetOShieldIncidentParticles()->IncidentMomentumX,
                    "OShieldIncidentMomentumX[numOShield]/D");
   tempTree->Branch("OShieldIncidentMomentumY",
                    theEvent->GetOShieldIncidentParticles()->IncidentMomentumY,
                    "OShieldIncidentMomentumY[numOShield]/D");
   tempTree->Branch("OShieldIncidentMomentumZ",
                    theEvent->GetOShieldIncidentParticles()->IncidentMomentumZ,
                    "OShieldIncidentMomentumZ[numOShield]/D");
   tempTree->Branch("OShieldDotProduct Incident Pos Mom",
                    theEvent->GetOShieldIncidentParticles()->
                    DotProductIncPosMom,
                    "OShieldDotProductIncidentPosMom[numOShield]/D");
   tempTree->Branch("OShield Incident Energy keV",
                    theEvent->GetOShieldIncidentParticles()->IncidentEnergykeV,
                    "OShieldIncidentEnergykeV[numOShield]/D");
   tempTree->Branch("OShield Time ns",
                    theEvent->GetOShieldIncidentParticles()->Timens,
                    "OShieldTimens[numOShield]/D");
	// det Vacuum arrays
   tempTree->Branch("num DetVac", theEvent->GetNDetVac(), "numDetVac/I");
   tempTree->Branch("DetVac PDG Code",
                    theEvent->GetDetVacIncidentParticles()->PDG,
                    "DetVacPDGCode[numDetVac]/I");
   tempTree->Branch("DetVac Track ID",
                    theEvent->GetDetVacIncidentParticles()->TrackID,
                    "DetVacTrackID[numDetVac]/I");
   tempTree->Branch("DetVac Parent ID ",
                    theEvent->GetDetVacIncidentParticles()->ParentID,
                    "DetVacParentID[numDetVac]/I");
   tempTree->Branch("DetVacPrimaryParentPDG",
                    theEvent->GetDetVacIncidentParticles()->
                    PrimaryParentPDG,
                    "DetVacPrimaryParentPDG[numDetVac]/I");
   tempTree->Branch("DetVacCreatorProcess ",
                    theEvent->GetDetVacIncidentParticles()->CreatorProcess,
                    "DetVacCreatorProcess[numDetVac]/I");
   tempTree->Branch("DetVacVertexVolume",
                    theEvent->GetDetVacIncidentParticles()->VertexVolume,
                    "DetVacVertexVolume[numDetVac]/I");
   tempTree->Branch("DetVacVertexEnergykeV",
                    theEvent->GetDetVacIncidentParticles()->
                    VertexEnergykeV, "DetVacVertexEnergykeV[numDetVac]/D");
   tempTree->Branch("DetVacVertexPositionXcm",
                    theEvent->GetDetVacIncidentParticles()->
                    VertexPositionXcm,
                    "DetVacVertexPositionXcm[numDetVac]/D");
   tempTree->Branch("DetVacVertexPositionYcm",
                    theEvent->GetDetVacIncidentParticles()->
                    VertexPositionYcm,
                    "DetVacVertexPositionYcm[numDetVac]/D");
   tempTree->Branch("DetVacVertexPositionZcm",
                    theEvent->GetDetVacIncidentParticles()->
                    VertexPositionZcm,
                    "DetVacVertexPositionZcm[numDetVac]/D");
   tempTree->Branch("DetVacIncidentPositionXcm",
                    theEvent->GetDetVacIncidentParticles()->
                    IncidentPositionXcm,
                    "DetVacIncidentPositionXcm[numDetVac]/D");
   tempTree->Branch("DetVacIncidentPositionYcm",
                    theEvent->GetDetVacIncidentParticles()->
                    IncidentPositionYcm,
                    "DetVacIncidentPositionYcm[numDetVac]/D");
   tempTree->Branch("DetVacIncidentPositionZcm",
                    theEvent->GetDetVacIncidentParticles()->
                    IncidentPositionZcm,
                    "DetVacIncidentPositionZcm[numDetVac]/D");
   tempTree->Branch("DetVacIncidentMomentumX",
                    theEvent->GetDetVacIncidentParticles()->
                    IncidentMomentumX,
                    "DetVacIncidentMomentumX[numDetVac]/D");
   tempTree->Branch("DetVacIncidentMomentumY",
                    theEvent->GetDetVacIncidentParticles()->
                    IncidentMomentumY,
                    "DetVacIncidentMomentumY[numDetVac]/D");
   tempTree->Branch("DetVacIncidentMomentumZ",
                    theEvent->GetDetVacIncidentParticles()->
                    IncidentMomentumZ,
                    "DetVacIncidentMomentumZ[numDetVac]/D");
   tempTree->Branch("DetVac DotProduct Incident Pos Mom",
                    theEvent->GetDetVacIncidentParticles()->
                    DotProductIncPosMom,
                    "DetVacDotProductIncidentPosMom[numDetVac]/D");
   tempTree->Branch("DetVac Incident Energy keV",
                    theEvent->GetDetVacIncidentParticles()->
                    IncidentEnergykeV,
                    "DetVacIncidentEnergykeV[numDetVac]/D");
   tempTree->Branch("DetVac Time ns",
                    theEvent->GetDetVacIncidentParticles()->Timens,
                    "DetVacTimens[numDetVac]/D");
// scintillator arrays              
   tempTree->Branch("num Scint", theEvent->GetNScint(), "numScint/I");
   tempTree->Branch("Scint PDG Code",
                    theEvent->GetScintIncidentParticles()->PDG,
                    "ScintPDGCode[numScint]/I");
   tempTree->Branch("Scint Track ID",
                    theEvent->GetScintIncidentParticles()->TrackID,
                    "ScintTrackID[numScint]/I");
   tempTree->Branch("Scint Parent ID ",
                    theEvent->GetScintIncidentParticles()->ParentID,
                    "ScintParentID[numScint]/I");
   tempTree->Branch("ScintPrimaryParentPDG",
                    theEvent->GetScintIncidentParticles()->
                    PrimaryParentPDG, "ScintPrimaryParentPDG[numScint]/I");
   tempTree->Branch("ScintCreatorProcess ",
                    theEvent->GetScintIncidentParticles()->CreatorProcess,
                    "ScintCreatorProcess[numScint]/I");
   tempTree->Branch("ScintVertexVolume",
                    theEvent->GetScintIncidentParticles()->VertexVolume,
                    "ScintVertexVolume[numScint]/I");
   tempTree->Branch("ScintVertexEnergykeV",
                    theEvent->GetScintIncidentParticles()->VertexEnergykeV,
                    "ScintVertexEnergykeV[numScint]/D");
   tempTree->Branch("ScintVertexPositionXcm",
                    theEvent->GetScintIncidentParticles()->
                    VertexPositionXcm,
                    "ScintVertexPositionXcm[numScint]/D");
   tempTree->Branch("ScintVertexPositionYcm",
                    theEvent->GetScintIncidentParticles()->
                    VertexPositionYcm,
                    "ScintVertexPositionYcm[numScint]/D");
   tempTree->Branch("ScintVertexPositionZcm",
                    theEvent->GetScintIncidentParticles()->
                    VertexPositionZcm,
                    "ScintVertexPositionZcm[numScint]/D");
   tempTree->Branch("ScintIncidentPositionXcm",
                    theEvent->GetScintIncidentParticles()->
                    IncidentPositionXcm,
                    "ScintIncidentPositionXcm[numScint]/D");
   tempTree->Branch("ScintIncidentPositionYcm",
                    theEvent->GetScintIncidentParticles()->
                    IncidentPositionYcm,
                    "ScintIncidentPositionYcm[numScint]/D");
   tempTree->Branch("ScintIncidentPositionZcm",
                    theEvent->GetScintIncidentParticles()->
                    IncidentPositionZcm,
                    "ScintIncidentPositionZcm[numScint]/D");
   tempTree->Branch("ScintIncidentMomentumX",
                    theEvent->GetScintIncidentParticles()->
                    IncidentMomentumX,
                    "ScintIncidentMomentumX[numScint]/D");
   tempTree->Branch("ScintIncidentMomentumY",
                    theEvent->GetScintIncidentParticles()->
                    IncidentMomentumY,
                    "ScintIncidentMomentumY[numScint]/D");
   tempTree->Branch("ScintIncidentMomentumZ",
                    theEvent->GetScintIncidentParticles()->
                    IncidentMomentumZ,
                    "ScintIncidentMomentumZ[numScint]/D");
   tempTree->Branch("Scint DotProduct Incident Pos Mom",
                    theEvent->GetScintIncidentParticles()->
                    DotProductIncPosMom,
                    "ScintDotProductIncidentPosMom[numScint]/D");
   tempTree->Branch("Scint Incident Energy keV",
                    theEvent->GetScintIncidentParticles()->
                    IncidentEnergykeV,
                    "ScintIncidentEnergykeV[numScint]/D");
   tempTree->Branch("Scint Time ns",
                    theEvent->GetScintIncidentParticles()->Timens,
                    "ScintTimens[numScint]/D");

   tree = tempTree;

}
