
#include "NeuEventAction.hh"
#include "NeuRunAction.hh"
#include "NeuDetectorHit.hh"


#include "G4Event.hh"
#include "G4EventManager.hh"
#include "G4TrajectoryContainer.hh"
#include "G4Trajectory.hh"
#include "G4VVisManager.hh"
#include "G4ios.hh"


#include "TROOT.h"

NeuFlux::NeuEventAction::NeuEventAction()
{
}

NeuFlux::NeuEventAction::~NeuEventAction()
{
}

void NeuFlux::NeuEventAction::BeginOfEventAction(const G4Event *event)
{
	G4cout<<std::endl;
	G4cout<<"---------------------------------------"<<std::endl;
	G4cout<<"Beginning Event: "<<event->GetEventID()<<std::endl;
}

void NeuFlux::NeuEventAction::EndOfEventAction(const G4Event * evt)
{
}
