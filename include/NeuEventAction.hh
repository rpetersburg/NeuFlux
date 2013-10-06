#ifndef NeuEventAction_hh_
#define NeuEventAction_hh_

#include "G4UserEventAction.hh"
#include "globals.hh"
#include "G4ThreeVector.hh"
#include "G4Event.hh"

#include "NeuRootOutput.hh"

namespace NeuFlux
{
  /*!
    \class NeuEventAction
    
    \ingroup NeuFlux
    
    \brief Defines User Beginning of Event and End of Event actions.
    
        Primarily designed to modify and update the current
    
    \author Kevin Wierman
   
    \version 1.0
    
    \date Oct 1, 2013
    
    \contact kwierman@email.unc.edu
  
 */
  class NeuEventAction : public G4UserEventAction, public  NeuOutputtingComponent 
  {

    public:
      NeuEventAction();
      ~NeuEventAction();

   public:
     void BeginOfEventAction(const G4Event *);
     void EndOfEventAction(const G4Event *);
     void OnNewFileCreate();

   private:
    G4int fEventID;
    G4double fPrimaryX;
    G4double fPrimaryY;
    G4double fPrimaryZ;
    G4double fPrimaryT;
    G4int fPrimaryN;
  };

}
#endif
