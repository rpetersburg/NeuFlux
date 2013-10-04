#include "NeuTrackingAction.hh"


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
	theTrack->GetTrackID();
	theTrack->GetParentID();
	theTrack->GetPosition().x();
	theTrack->GetPosition().y();
	theTrack->GetPosition().z();
	theTrack->GetLocalTime()
	theTrack->GetGlobalTime();

}
