/*!
  \class NeuEventActions
  
  \ingroup NeuFlux
  
  \brief Defines User Beginning of Event and End of Event actions.
  
      Primarily designed to modify and update the current
  
  \author Kevin Wierman
 
  \version 1.0
  
  \date Oct 1, 2013
  
  Contact: kwierman@email.unc.edu
  
 */

#ifndef NeuEventAction_hh_
#define NeuEventAction_hh_

#include "G4UserEventAction.hh"
#include "globals.hh"
#include "G4ThreeVector.hh"
#include "G4Event.hh"

#include "TFile.h"

#include "NeuRunAction.hh"

namespace NeuFlux
{

  class NeuEventAction : public G4UserEventAction {

  public:
    NeuEventAction();
    ~NeuEventAction();

 public:
   void BeginOfEventAction(const G4Event *);
   void EndOfEventAction(const G4Event *);
};

}
#endif
