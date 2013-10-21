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
      double fTrackID ;
      double fParentID ;
      
      double fPreX ;
      double fPreY ;
      double fPreZ ;
      double fPreLT ;
      double fPreGT ;
      double fPrePT ;
      
      double fPostX ;
      double fPostY ;
      double fPostZ ;
      double fPostLT ;
      double fPostGT ;
      double fPostPT ;

      double fPDGMass    ;
      double fPDGWidth    ;
      double fPDGCharge   ;
      double fPDGSpin   ;

      double fPDGiSpin    ;
      double fPDGiParity  ;
      double fPDGiConjugation;
      double fPDGIsospin  ;
      double fPDGIsospin3 ;
      double fPDGiIsospin ;
      double fPDGiIsospin3  ;

      double fPDGiGParity  ;
      double fPDGMagneticMoment   ;
      double fLeptonNumber;
      double fBaryonNumber  ;
      int fPDGEncoding ;

      double fAtomicNumber;
      double fAtomicMass  ;

      double fVolume;
      double fNextVolume;
   };

}

#endif
