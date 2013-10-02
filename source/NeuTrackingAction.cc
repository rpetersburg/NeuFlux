#include "NeuTrackingAction.hh"
#include "NeuEventAction.hh"


#include "G4RunManager.hh"
#include "G4TrackingManager.hh"
#include "G4Track.hh"
#include "G4ParticleDefinition.hh"


NeuFlux::NeuTrackingAction::NeuTrackingAction()
{
}

NeuFlux::NeuTrackingAction::~NeuTrackingAction()
{
}

void NeuFlux::NeuTrackingAction::PreUserTrackingAction(const G4Track* theTrack)
{
   NeuFlux::NeuEventAction* theEvent = (NeuEventAction*)
       G4RunManager::GetRunManager()->GetUserEventAction();
}
