

#ifndef NeuSteppingAction_hh_
#define NeuSteppingAction_hh_ 

#include "G4UserSteppingAction.hh"
#include "G4UserEventAction.hh"
#include "G4Track.hh"
#include "globals.hh"

namespace NeuFlux
{
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
   class NeuSteppingAction : public G4UserSteppingAction 
   {

    public:
      NeuSteppingAction();
      ~NeuSteppingAction();

      void UserSteppingAction(const G4Step * theStep);

    private:
      double fPreX;
      double fPreY;
      double fPreZ;
      double fPreLocalT;
      double fPreGlobalT;
      double fPreProperT;
      double fPreMomX;
      double fPreMomY;
      double fPreMomZ;
      double fPreTotalE;
      double fPreKinE;

      double fPostX;
      double fPostY;
      double fPostZ;
      double fPostLocalT;
      double fPostGlobalT;
      double fPostProperT;
      double fPostMomX;
      double fPostMomY;
      double fPostMomZ;
      double fPostTotalE;
      double fPostKinE;

      double fStepLength;
      double fTotalEnergyDeposit;
      double fTotalNonIEnergyDeposit;

      double fDeltaX;
      double fDeltaY;
      double fDeltaZ;
      double fDeltaT;

   };

}

#endif
