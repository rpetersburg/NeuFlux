/*!
   \class NeuSteppingAction
   
   \ingroup NeuFlux
   
   \brief Defines information to be updated during stepping.
   
   \note See NeuEventAction for which information is available to access.
   
   \author Kevin Wierman
   
   \version 1.0
   
   \date Oct 1, 2013
   
   \contact kwierman@email.unc.edu

   
*/

#ifndef NeuSteppingAction_hh_
#define NeuSteppingAction_hh_ 

#include "G4UserSteppingAction.hh"
#include "G4UserEventAction.hh"
#include "G4Track.hh"
#include "globals.hh"

namespace NeuFlux
{
   class NeuSteppingAction : public G4UserSteppingAction 
   {

    public:
      NeuSteppingAction(NeuEventAction *,
                                  NeuTrackingAction *,
                                  NeuDetectorConstruction *);
      ~NeuSteppingAction();

      void UserSteppingAction(const G4Step * theStep);

    private:
      NeuEventAction * theEventAct;
      NeuTrackingAction *theTrackAct;
      NeuDetectorConstruction *theDet;

      void SetEnteringParticleInfo();

   };

}

#endif
