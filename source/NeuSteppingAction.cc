#include "NeuSteppingAction.hh"

#include "NeuEventAction.hh"
#include "NeuTrackingAction.hh"

#include "G4SteppingManager.hh"
#include "G4Step.hh"
#include "G4StepPoint.hh"
#include "G4Track.hh"
#include "G4ios.hh"


NeuFlux::NeuSteppingAction::NeuSteppingAction(NeuEventAction * theEA,
                            NeuTrackingAction * theTA,
                            NeuWorldGeometry * det)
:  theEventAct(theEA), theTrackAct(theTA), theDet(det)
{


}


NeuFlux::NeuSteppingAction::~NeuSteppingAction()
{

}

void NeuFlux::NeuSteppingAction::UserSteppingAction(const G4Step *
                                                     theStep)
{
}

