/*!
  \class NeuTrackingAction
 
  \ingroup NeuFlux
 
  \brief Header file for defining the actions to take at the beginning and end of a track.
 
 	The only capability programmed in at the moment is set parentPDG. This helps to identify
 	a track with it's parent track to find where products come from. This modifies the event
 	so that the top track is always pointed at the correct track.
 
  \note Post Action is still available to be updated.
 
  \author Kevin Wierman
  \author Michelle Leber
 
  \version $Revision: 1.5 $
 
  \date $Date: Tue Nov 20 12::33:51 2012 $
 
  Contact: kwierman@email.unc.edu
 
  Created on: Oct 1, 2013
 
 */

#ifndef NeuTrackingAction_hh_
#define NeuTrackingAction_hh_

#include "G4UserTrackingAction.hh"
#include "globals.hh"

namespace NeuFlux
{
   class NeuTrackingAction : public G4UserTrackingAction 
   {
   public:
      NeuTrackingAction();
      ~NeuTrackingAction();
      void PreUserTrackingAction(const G4Track *);
      //void PostUserTrackingAction(const G4Track*);//Not Used.

      void SetPrimaryParentPDG(G4int pdg) {
         fParentPDG = pdg;
      };
      G4int GetPrimaryParentPDG() {
         return fParentPDG;
      };

    private:
      G4int fParentPDG;
   };

}

#endif
