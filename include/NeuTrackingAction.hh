#ifndef NeuTrackingAction_hh_
#define NeuTrackingAction_hh_

#include "NeuRootOutput.hh"

#include "G4UserTrackingAction.hh"
#include "globals.hh"

namespace NeuFlux
{
  /*!
    \class NeuTrackingAction
   
    \ingroup NeuFlux
   
    \brief Header file for defining the actions to take at the beginning and end of a track.
   
    The only capability programmed in at the moment is set parentPDG. This helps to identify
    a track with it's parent track to find where products come from. This modifies the event
    so that the top track is always pointed at the correct track.
   
    \note Position calculation is still rough, given that paths may curve
   
    \author Kevin Wierman
   
    \version 1.0
   
    \date Oct 1, 2013
   
    \contact kwierman@email.unc.edu
   
   */
   class NeuTrackingAction : public G4UserTrackingAction , public NeuOutputtingComponent
   {
   public:
      NeuTrackingAction();
      ~NeuTrackingAction();
      void PreUserTrackingAction(const G4Track*);
      void PostUserTrackingAction(const G4Track*);

      void OnNewFileCreate();

    private:
      Double_t fTrackID ;
      Double_t fParentID ;
      
      Double_t fPreX ;
      Double_t fPreY ;
      Double_t fPreZ ;
      Double_t fPreLT ;
      Double_t fPreGT ;
      Double_t fPrePT ;
      
      Double_t fPostX ;
      Double_t fPostY ;
      Double_t fPostZ ;
      Double_t fPostLT ;
      Double_t fPostGT ;
      Double_t fPostPT ;

      Double_t fPDGMass    ;
      Double_t fPDGWidth    ;
      Double_t fPDGCharge   ;
      Double_t fPDGSpin   ;

      Double_t fPDGiSpin    ;
      Double_t fPDGiParity  ;
      Double_t fPDGiConjugation;
      Double_t fPDGIsospin  ;
      Double_t fPDGIsospin3 ;
      Double_t fPDGiIsospin ;
      Double_t fPDGiIsospin3  ;

      Double_t fPDGiGParity  ;
      Double_t fPDGMagneticMoment   ;
      Double_t fLeptonNumber;
      Double_t fBaryonNumber  ;
      Int_t fPDGEncoding ;

      Double_t fAtomicNumber;
      Double_t fAtomicMass  ;

      Double_t fVolume;
      Double_t fNextVolume;
   };

}

#endif
