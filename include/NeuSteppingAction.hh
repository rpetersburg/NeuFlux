#ifndef NeuSteppingAction_hh_
#define NeuSteppingAction_hh_ 

#include "NeuRootOutput.hh"


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
   class NeuSteppingAction : public G4UserSteppingAction , public NeuOutputtingComponent
   {

    public:
      NeuSteppingAction();
      ~NeuSteppingAction();
      void OnNewFileCreate();

      void UserSteppingAction(const G4Step * theStep);

    private:
      Double_t fPreX;
      Double_t fPreY;
      Double_t fPreZ;
      Double_t fPreLocalT;
      Double_t fPreGlobalT;
      Double_t fPreProperT;
      Double_t fPreMomX;
      Double_t fPreMomY;
      Double_t fPreMomZ;
      Double_t fPreTotalE;
      Double_t fPreKinE;

      Double_t fPostX;
      Double_t fPostY;
      Double_t fPostZ;
      Double_t fPostLocalT;
      Double_t fPostGlobalT;
      Double_t fPostProperT;
      Double_t fPostMomX;
      Double_t fPostMomY;
      Double_t fPostMomZ;
      Double_t fPostTotalE;
      Double_t fPostKinE;

      Double_t fStepLength;
      Double_t fTotalEnergyDeposit;
      Double_t fTotalNonIEnergyDeposit;

      Double_t fDeltaX;
      Double_t fDeltaY;
      Double_t fDeltaZ;
      Double_t fDeltaT;

      Int_t fTrackID;

   };

}

#endif
