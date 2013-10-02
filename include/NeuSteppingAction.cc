
#include "NeuEventAction.hh"
#include "NeuSteppingAction.hh"
#include "NeuTrackingAction.hh"
#include "NeuDetectorConstruction.hh"

#include "G4SteppingManager.hh"
#include "G4Step.hh"
#include "G4StepPoint.hh"
#include "G4Track.hh"
#include "G4ios.hh"


NeuSteppingAction::NeuSteppingAction(NeuEventAction * theEA,
                            NeuTrackingAction * theTA,
                            NeuDetectorConstruction * det)
:  theEventAct(theEA), theTrackAct(theTA), theDet(det)
{


}


NeuSteppingAction::~NeuSteppingAction()
{

}

void NeuSteppingAction::UserSteppingAction(const G4Step *
                                                     theStep)
{
}

