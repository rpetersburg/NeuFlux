///
///     KDSSteppingAction.cc
///
///     Code file for defining the steps to take at the beginning
///     and end of a step.
///
///     Michelle Leber, 1 April 2005
///

///     Geant4 user includes
#include "KDSEventAction.hh"
#include "KDSSteppingAction.hh"
#include "KDSTrackingAction.hh"
#include "KDSDetectorConstruction.hh"
///     Geant4 package includes
#include "G4SteppingManager.hh"
#include "G4Step.hh"
#include "G4StepPoint.hh"
#include "G4Track.hh"
#include "G4ios.hh"

///     ------++++++------++++++------++++++------++++++------
///                             KDSSteppingAction()
///     ------++++++------++++++------++++++------++++++------
KDSSteppingAction::KDSSteppingAction(KDSEventAction * theEA,
                            KDSTrackingAction * theTA,
                            KDSDetectorConstruction * det)
:  theEventAct(theEA), theTrackAct(theTA), theDet(det), theTrack(0),
preVolume(0), postVolume(0), vertexLogicalVolume(0), edep(0),
processType(10), trackID(0), parentID(0), PDG(0),
KE(0), time(0), incidentPosition(0), incidentMomentum(0)
{


}

///     ------++++++------++++++------++++++------++++++------
///                             ~KDSSteppingAction()
///     ------++++++------++++++------++++++------++++++------
KDSSteppingAction::~KDSSteppingAction()
{

}

///     ------++++++------++++++------++++++------++++++------
///                                     UserSteppingAction()
///     ------++++++------++++++------++++++------++++++------
void KDSSteppingAction::UserSteppingAction(const G4Step *
                                                     theStep)
{
// update these each step
   theTrack = theStep->GetTrack();
   preVolume = theStep->GetPreStepPoint()->GetPhysicalVolume();
   postVolume = theStep->GetPostStepPoint()->GetPhysicalVolume();
   vertexLogicalVolume = theTrack->GetLogicalVolumeAtVertex();
   edep = theStep->GetTotalEnergyDeposit();
   KE = theStep->GetPreStepPoint()->GetKineticEnergy();
   time = theStep->GetPreStepPoint()->GetGlobalTime();
   incidentPosition = theStep->GetPostStepPoint()->GetPosition();
   incidentMomentum = theStep->GetPostStepPoint()->GetMomentumDirection();
   trackID = theTrack->GetTrackID();
   parentID = theTrack->GetParentID();
   PDG = 0;
   if (G4int(theTrack->GetDefinition()->GetPDGEncoding())) {
      PDG = G4int(theTrack->GetDefinition()->GetPDGEncoding());
   }
   if (PDG == 0) {
      if (theTrack->GetDefinition()->GetParticleType() == "nucleus") {
         PDG =
             10000000 +
             G4int(theTrack->GetDefinition()->GetBaryonNumber()) *
             1000 +
             G4int(theTrack->GetDefinition()->GetPDGCharge() / eplus);
      }
   }
   processType = 10;
   if (!(parentID == 0)) {
      processType = theTrack->GetCreatorProcess()->GetProcessType();
   }
   // update these at the begining of a track
   if (theTrack->GetCurrentStepNumber() == 1) {
      if (processType == 6) {
         if (theTrack->GetCreatorProcess()->GetProcessName() ==
             "RadioactiveDecay") {
            // difference of vertex and incident values should be step 0 to 1
            volumeIndex = 0;
            volumeIndex = theDet->FindVertexVolumeIndex(vertexLogicalVolume);
            KDSSteppingAction::SetEnteringParticleInfo();
            if (PDG==22&&KE<100*keV) {
               //kill this particle, intensity is wrong.
               G4int NKilled = *theEventAct->GetNKilled();
               theEventAct->SetKilledIncidentParticle(NKilled,
                                                      incidentParticle);
               theEventAct->AddKilledPart(1);
               theStep->GetTrack()->SetTrackStatus(fKillTrackAndSecondaries);
            } else {
               G4int NDecay = *theEventAct->GetNDecay();
               theEventAct->SetDecayIncidentParticle(NDecay,
                                                     incidentParticle);
               theEventAct->AddDecayPart(1);
               
            }
         }
      }
   }
   
   // Is the particle entering a new volume? 
   if (preVolume && postVolume) {
		if (!(preVolume == postVolume)) {
			
			if (theDet->StoreEnteringParticleInfo(postVolume) ) {
				volumeIndex = theDet->FindVertexVolumeIndex(vertexLogicalVolume);
				KDSSteppingAction::SetEnteringParticleInfo();
				if ( theDet->FindPhysicalVolumeIndex(postVolume) == 0) { 
					// silicon detector
					G4int NDet = *theEventAct->GetNDet();
					theEventAct->SetDetIncidentParticle(NDet, incidentParticle);
					theEventAct->AddDetPart(1);
				} else if ( theDet->FindPhysicalVolumeIndex(postVolume) == 1) { 
					//vacuum surronding the detector
					// don't double-count same particle spiraling in the field
					if (!(trackID == theEventAct->GetDVLastTrackID())) {
						G4int NDetVac = *theEventAct->GetNDetVac();
						theEventAct->SetDetVacIncidentParticle(NDetVac, incidentParticle);
						theEventAct->AddDetVacPart(1);
						theEventAct->SetDVLastTrackID(trackID);
					}
				} else if ( theDet->FindPhysicalVolumeIndex(postVolume) == 2) { 
					//Air inside the shield
					// don't double-count same particle spiraling in the field
					if (!(trackID == theEventAct->GetAirLastTrackID())) {
						G4int NAir = *theEventAct->GetNAir();
						theEventAct->SetAirIncidentParticle(NAir, incidentParticle);
						theEventAct->AddAirPart(1);
						theEventAct->SetAirLastTrackID(trackID);
					}		
				} else if ( theDet->FindPhysicalVolumeIndex(postVolume) == 3) { 
					// SCintillator
					// don't double-count same particle spiraling in the field
					if (!(trackID == theEventAct->GetScintLastTrackID())) {
						theEventAct->SetScintLastTrackID(trackID);
						G4int NScint = *theEventAct->GetNScint();
						theEventAct->SetScintIncidentParticle(NScint, incidentParticle);
						theEventAct->AddScintPart(1);
					}
				} else if ( theDet->FindPhysicalVolumeIndex(postVolume) == 4) { 
					// Outer shield
					// don't double-count same particle spiraling in the field
					if (!(trackID == theEventAct->GetOShieldLastTrackID())) {
						G4int NOShield = *theEventAct->GetNOShield();
						theEventAct->SetOShieldIncidentParticle(NOShield, incidentParticle);
						theEventAct->AddOShieldPart(1);
						theEventAct->SetOShieldLastTrackID(trackID);
					}		
				}
			}
      }
   }
}

void KDSSteppingAction::SetEnteringParticleInfo()
{
   incidentParticle.PDG = PDG;
   incidentParticle.TrackID = trackID;
   incidentParticle.ParentID = parentID;
   incidentParticle.PrimaryParentPDG = theTrackAct->GetPrimaryParentPDG();
   incidentParticle.CreatorProcess = processType;
   incidentParticle.VertexVolume = volumeIndex;
   incidentParticle.VertexEnergy = theTrack->GetVertexKineticEnergy();
   incidentParticle.VertexPosition = theTrack->GetVertexPosition();
   incidentParticle.IncidentPosition = incidentPosition;
   incidentParticle.IncidentMomentum = incidentMomentum;
   incidentParticle.DotProductIncPosMom =
       incidentPosition.dot(incidentMomentum) / incidentPosition.mag();
   incidentParticle.IncidentEnergy = KE;
   incidentParticle.Time = time;
}
