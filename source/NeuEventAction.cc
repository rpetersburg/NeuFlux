///
///     KDSEventAction.cc
///
///     Code file for defining the steps to take at the beginning
///     and end of an event.
///
///     Michelle Leber, 1 April 2005
///

///     Geant4 user includes
#include "KDSEventAction.hh"
#include "KDSRunAction.hh"
#include "KDSScintHit.hh"
#include "KDSSilicHit.hh"
///     Geant4 package includes
#include "G4Event.hh"
#include "G4EventManager.hh"
#include "G4TrajectoryContainer.hh"
#include "G4Trajectory.hh"
#include "G4VVisManager.hh"
#include "G4ios.hh"
//root includes
#include "TROOT.h"


///     ------++++++------++++++------++++++------++++++------
///                                     KDSEventAction()
///     ------++++++------++++++------++++++------++++++------
KDSEventAction::KDSEventAction(KDSRunAction *
                                                   theRA)
:  theRun(theRA), fNOShield(0), fScintLastTrackID(0),
   fOShieldLastTrackID(0),fNDetVac(0), fTopTrackID(0),
   fIniParentElement(0),fEvent(0),fIniPlanePositionY(0),
   fIniPositionY(0),fNDet(0),fNIni(0),fNScint(0),fNKilled(0),
   fNPairs(0),fDVLastTrackID(0),fNAir(0),fIniPositionX(0),
   fIniPositionZ(0),fNDecay(0),fAirLastTrackID(0),
   fIniPlanePositionX(0),fIniPlanePositionZ(0)
{
   // initializing arrrays
   for (G4int i = 0; i < kMax; i++) {
      fDetIncidentParticle.PDG[i] = 0;
      fDetIncidentParticle.TrackID[i] = 0;
      fDetIncidentParticle.ParentID[i] = 0;
      fDetIncidentParticle.PrimaryParentPDG[i] = 0;
      fDetIncidentParticle.CreatorProcess[i] = 0;
      fDetIncidentParticle.VertexVolume[i] = 0;
      fDetIncidentParticle.VertexEnergykeV[i] = 0;
      fDetIncidentParticle.VertexPositionXcm[i] = 0;
      fDetIncidentParticle.VertexPositionYcm[i] = 0;
      fDetIncidentParticle.VertexPositionZcm[i] = 0;
      fDetIncidentParticle.IncidentPositionXcm[i] = 0;
      fDetIncidentParticle.IncidentPositionYcm[i] = 0;
      fDetIncidentParticle.IncidentPositionZcm[i] = 0;
      fDetIncidentParticle.IncidentMomentumX[i] = 0;
      fDetIncidentParticle.IncidentMomentumY[i] = 0;
      fDetIncidentParticle.IncidentMomentumZ[i] = 0;
      fDetIncidentParticle.DotProductIncPosMom[i] = 0;
      fDetIncidentParticle.IncidentEnergykeV[i] = 0;
      fDetIncidentParticle.Timens[i] = 0;
   }
   for (G4int i = 0; i < kMax; i++) {
      fScintIncidentParticle.PDG[i] = 0;
      fScintIncidentParticle.TrackID[i] = 0;
      fScintIncidentParticle.ParentID[i] = 0;
      fScintIncidentParticle.PrimaryParentPDG[i] = 0;
      fScintIncidentParticle.CreatorProcess[i] = 0;
      fScintIncidentParticle.VertexVolume[i] = 0;
      fScintIncidentParticle.VertexEnergykeV[i] = 0;
      fScintIncidentParticle.VertexPositionXcm[i] = 0;
      fScintIncidentParticle.VertexPositionYcm[i] = 0;
      fScintIncidentParticle.VertexPositionZcm[i] = 0;
      fScintIncidentParticle.IncidentPositionXcm[i] = 0;
      fScintIncidentParticle.IncidentPositionYcm[i] = 0;
      fScintIncidentParticle.IncidentPositionZcm[i] = 0;
      fScintIncidentParticle.IncidentMomentumX[i] = 0;
      fScintIncidentParticle.IncidentMomentumY[i] = 0;
      fScintIncidentParticle.IncidentMomentumZ[i] = 0;
      fScintIncidentParticle.DotProductIncPosMom[i] = 0;
      fScintIncidentParticle.IncidentEnergykeV[i] = 0;
      fScintIncidentParticle.Timens[i] = 0;
   }
   for (G4int i = 0; i < kMax; i++) {
      fAirIncidentParticle.PDG[i] = 0;
      fAirIncidentParticle.TrackID[i] = 0;
      fAirIncidentParticle.ParentID[i] = 0;
      fAirIncidentParticle.PrimaryParentPDG[i] = 0;
      fAirIncidentParticle.CreatorProcess[i] = 0;
      fAirIncidentParticle.VertexVolume[i] = 0;
      fAirIncidentParticle.VertexEnergykeV[i] = 0;
      fAirIncidentParticle.VertexPositionXcm[i] = 0;
      fAirIncidentParticle.VertexPositionYcm[i] = 0;
      fAirIncidentParticle.VertexPositionZcm[i] = 0;
      fAirIncidentParticle.IncidentPositionXcm[i] = 0;
      fAirIncidentParticle.IncidentPositionYcm[i] = 0;
      fAirIncidentParticle.IncidentPositionZcm[i] = 0;
      fAirIncidentParticle.IncidentMomentumX[i] = 0;
      fAirIncidentParticle.IncidentMomentumY[i] = 0;
      fAirIncidentParticle.IncidentMomentumZ[i] = 0;
      fAirIncidentParticle.IncidentEnergykeV[i] = 0;
      fAirIncidentParticle.DotProductIncPosMom[i] = 0;
      fAirIncidentParticle.Timens[i] = 0;
   }
   for (G4int i = 0; i < kMax; i++) {
      fOShieldIncidentParticle.PDG[i] = 0;
      fOShieldIncidentParticle.TrackID[i] = 0;
      fOShieldIncidentParticle.ParentID[i] = 0;
      fOShieldIncidentParticle.PrimaryParentPDG[i] = 0;
      fOShieldIncidentParticle.CreatorProcess[i] = 0;
      fOShieldIncidentParticle.VertexVolume[i] = 0;
      fOShieldIncidentParticle.VertexEnergykeV[i] = 0;
      fOShieldIncidentParticle.VertexPositionXcm[i] = 0;
      fOShieldIncidentParticle.VertexPositionYcm[i] = 0;
      fOShieldIncidentParticle.VertexPositionZcm[i] = 0;
      fOShieldIncidentParticle.IncidentPositionXcm[i] = 0;
      fOShieldIncidentParticle.IncidentPositionYcm[i] = 0;
      fOShieldIncidentParticle.IncidentPositionZcm[i] = 0;
      fOShieldIncidentParticle.IncidentMomentumX[i] = 0;
      fOShieldIncidentParticle.IncidentMomentumY[i] = 0;
      fOShieldIncidentParticle.IncidentMomentumZ[i] = 0;
      fOShieldIncidentParticle.IncidentEnergykeV[i] = 0;
      fOShieldIncidentParticle.DotProductIncPosMom[i] = 0;
      fOShieldIncidentParticle.Timens[i] = 0;
   }
   for (G4int i = 0; i < kMax; i++) {
      fDetVacIncidentParticle.PDG[i] = 0;
      fDetVacIncidentParticle.TrackID[i] = 0;
      fDetVacIncidentParticle.ParentID[i] = 0;
      fDetVacIncidentParticle.PrimaryParentPDG[i] = 0;
      fDetVacIncidentParticle.CreatorProcess[i] = 0;
      fDetVacIncidentParticle.VertexVolume[i] = 0;
      fDetVacIncidentParticle.VertexEnergykeV[i] = 0;
      fDetVacIncidentParticle.VertexPositionXcm[i] = 0;
      fDetVacIncidentParticle.VertexPositionYcm[i] = 0;
      fDetVacIncidentParticle.VertexPositionZcm[i] = 0;
      fDetVacIncidentParticle.IncidentPositionXcm[i] = 0;
      fDetVacIncidentParticle.IncidentPositionYcm[i] = 0;
      fDetVacIncidentParticle.IncidentPositionZcm[i] = 0;
      fDetVacIncidentParticle.IncidentMomentumX[i] = 0;
      fDetVacIncidentParticle.IncidentMomentumY[i] = 0;
      fDetVacIncidentParticle.IncidentMomentumZ[i] = 0;
      fDetVacIncidentParticle.DotProductIncPosMom[i] = 0;
      fDetVacIncidentParticle.IncidentEnergykeV[i] = 0;
      fDetVacIncidentParticle.Timens[i] = 0;
   }
   for (G4int i = 0; i < kMax; i++) {
      fDecayIncidentParticle.PDG[i] = 0;
      fDecayIncidentParticle.TrackID[i] = 0;
      fDecayIncidentParticle.ParentID[i] = 0;
      fDecayIncidentParticle.PrimaryParentPDG[i] = 0;
      fDecayIncidentParticle.CreatorProcess[i] = 0;
      fDecayIncidentParticle.VertexVolume[i] = 0;
      fDecayIncidentParticle.VertexEnergykeV[i] = 0;
      fDecayIncidentParticle.VertexPositionXcm[i] = 0;
      fDecayIncidentParticle.VertexPositionYcm[i] = 0;
      fDecayIncidentParticle.VertexPositionZcm[i] = 0;
      fDecayIncidentParticle.IncidentPositionXcm[i] = 0;
      fDecayIncidentParticle.IncidentPositionYcm[i] = 0;
      fDecayIncidentParticle.IncidentPositionZcm[i] = 0;
      fDecayIncidentParticle.IncidentMomentumX[i] = 0;
      fDecayIncidentParticle.IncidentMomentumY[i] = 0;
      fDecayIncidentParticle.IncidentMomentumZ[i] = 0;
      fDecayIncidentParticle.DotProductIncPosMom[i] = 0;
      fDecayIncidentParticle.IncidentEnergykeV[i] = 0;
      fDecayIncidentParticle.Timens[i] = 0;
   }
   for (G4int i = 0; i < kMax; i++) {
      fKilledIncidentParticle.PDG[i] = 0;
      fKilledIncidentParticle.TrackID[i] = 0;
      fKilledIncidentParticle.ParentID[i] = 0;
      fKilledIncidentParticle.PrimaryParentPDG[i] = 0;
      fKilledIncidentParticle.CreatorProcess[i] = 0;
      fKilledIncidentParticle.VertexVolume[i] = 0;
      fKilledIncidentParticle.VertexEnergykeV[i] = 0;
      fKilledIncidentParticle.VertexPositionXcm[i] = 0;
      fKilledIncidentParticle.VertexPositionYcm[i] = 0;
      fKilledIncidentParticle.VertexPositionZcm[i] = 0;
      fKilledIncidentParticle.IncidentPositionXcm[i] = 0;
      fKilledIncidentParticle.IncidentPositionYcm[i] = 0;
      fKilledIncidentParticle.IncidentPositionZcm[i] = 0;
      fKilledIncidentParticle.IncidentMomentumX[i] = 0;
      fKilledIncidentParticle.IncidentMomentumY[i] = 0;
      fKilledIncidentParticle.IncidentMomentumZ[i] = 0;
      fKilledIncidentParticle.DotProductIncPosMom[i] = 0;
      fKilledIncidentParticle.IncidentEnergykeV[i] = 0;
      fKilledIncidentParticle.Timens[i] = 0;
   }
}

///     ------++++++------++++++------++++++------++++++------
///                                     ~KDSEventAction()
///     ------++++++------++++++------++++++------++++++------
KDSEventAction::~KDSEventAction()
{
}

///     ------++++++------++++++------++++++------++++++------
///                                     BeginOfEventAction()
///     ------++++++------++++++------++++++------++++++------
void KDSEventAction::BeginOfEventAction(const G4Event *event)
{
	std::cout<<std::endl;
	std::cout<<"---------------------------------------"<<std::endl;
	std::cout<<"Beginning Event: "<<event->GetEventID()<<std::endl;
   fNDecay = 0;
   fNKilled = 0;
   fNAir = 0;
   fNOShield = 0;
   fNDetVac = 0;
   fNDet = 0;
   fNScint = 0;
   fTopTrackID = 10;
   fAirLastTrackID = 0;
   fOShieldLastTrackID = 0;
   fDVLastTrackID = 0;
   fScintLastTrackID = 0;
}

///     ------++++++------++++++------++++++------++++++------
///                                     EndOfEventAction()
///     ------++++++------++++++------++++++------++++++------
void KDSEventAction::EndOfEventAction(const G4Event * evt)
{
	//evt->Print();
    fEvent = evt->GetEventID();
   theRun->GetTree()->Fill();

   // periodic saving
   if (fEvent % 10000 == 0) {
      theRun->GetTree()->AutoSave();
   }

   // get number of stored trajectories
   // extract the trajectories and draw them
   //
/*   if (G4VVisManager::GetConcreteInstance()) {
      G4cout << "concrete vis manager" << G4endl;
	  G4TrajectoryContainer *trajectoryContainer =
       evt->GetTrajectoryContainer();
      G4int n_trajectories = 0;
      if (trajectoryContainer) {
         n_trajectories = trajectoryContainer->entries();
      }
      for (G4int i = 0; i < n_trajectories; i++) {
         G4Trajectory *trj = (G4Trajectory *)
             ((*(evt->GetTrajectoryContainer()))[i]);
         trj->DrawTrajectory(1000);
      }
   }*/
   //std::cout<<"Event ID: "<<evt->GetEventID()<<std::endl;
   //std::cout<<"Number of Primary Vertex: "<<evt->GetNumberOfPrimaryVertex()<<std::endl;
   G4TrajectoryContainer *trajectoryContainer =
          evt->GetTrajectoryContainer();
   G4int n_trajectories = 0;
   if (trajectoryContainer) {
      n_trajectories = trajectoryContainer->entries();
   }
   //for(int i=0; i<evt->GetNumberOfPrimaryVertex();i++)
   //{
	//   G4PrimaryVertex* vert =  evt->GetPrimaryVertex(i);
	//   vert->Print();
   //}
   /*
   G4HCofThisEvent* hc = evt->GetHCofThisEvent();
   std::cout<<"Number of Hit Collections: "<<evt->GetHCofThisEvent()->GetNumberOfCollections()<<std::endl;
   KDSScintHitsCollection* scintHits =  (KDSScintHitsCollection*)(evt->GetHCofThisEvent()->GetHC(0));
   if(scintHits)
   {
	   std::cout<<"Found Scint hits"<<std::endl;
	   std::cout<<"  Size of Hits Collection: "<<(int)scintHits->GetSize()<<std::endl;
	   //scintHits->PrintAllHits();
	   for(int i =0; i<(int)scintHits->GetSize();i++)
	   {
		   //std::cout<<"  Processing Hit Number: "<<i<<std::endl;
		   KDSScintHit* hit =(KDSScintHit*)scintHits->GetHit((size_t)i);
		   //std::cout<<"  "<<hit->GetTrackID()<<" , "<<hit->GetPanelID()<<" , "<<hit->GetPDGCode()<<" , "<< hit->GetEdep()<<" , "<<hit->GetGlobalTime()<<" , "<<hit->GetNonIonEnergy()<<std::endl;
		   //std::cout<<"Panel ID: "<<hit->GetPanelID()<<std::endl;
		   //std::cout<<"Particle PDG Code: "<<hit->GetPDGCode()<<std::endl;

		   //hit->Print();
	   }
   }
   KDSSilicHitsCollection* silicHits = (KDSSilicHitsCollection*)(evt->GetHCofThisEvent()->GetHC(1));
   if(silicHits)
   {

	   std::cout<<"Found Silic Hits"<<std::endl;
	   std::cout<<"  Size of Hits Collection: "<<(int)silicHits->GetSize()<<std::endl;
	   for(int i =0; i<(int)silicHits->GetSize();i++)
	   {
		   //std::cout<<"  Processing Hit Number: "<<i<<std::endl;
		   KDSSilicHit* hit =(KDSSilicHit*)silicHits->GetHit((size_t)i);
		   //std::cout<<"  Pixel ID: "<<hit->GetPixelID()<<std::endl;
		   //std::cout<<"  Track ID"<<hit->GetTrackID()<<std::endl;
		   //std::cout<<"  Particle Type: "<<hit->GetPDGCode()<<std::endl;
		   //hit->Print();
	   }
		   //std::cout<<silicHits->GetHit()<<std::endl;
	   //silicHits->PrintAllHits();
   }
   */
   /*
   for (G4int i = 0; i < n_trajectories; i++) {
      G4Trajectory *trj = (G4Trajectory *)
          ((*(evt->GetTrajectoryContainer()))[i]);
      std::cout<<"Particle Name for traj: "<<i<<" : "<<trj->GetParticleName()<<std::endl;
      std::cout<<trj->GetTrackID()<<std::endl;
      std::cout<<trj->GetParentID()<<std::endl;
   }
   */

   //std::cout<<"---------------------------------------"<<std::endl;
	//std::cout<<std::endl;
}
