/*!
	\class NeuDetector
	
	\ingroup NeuFlux
	
	\brief Sensitive Detector Definition for an arbitrary air-based detector
	
	Stores the hits for the scintillator, and processes incoming tracks.
	No wait. That's backwards.
	
	Stores these to file after we're all done.
	
	\author Kevin Wierman

	\version 1.0
	\revision 1.5 
	
	\date $Date: Tue Nov 20 12::33:51 2012 $
	
	Contact: kwierman@email.unc.edu
	
	Created on: Wed Apr 1 18:39:37 2005
	
 */
#ifndef NeuDetector_hh_
#define NeuDetector_hh_ 

#include "G4VSensitiveDetector.hh"
#include "G4Step.hh"
#include "G4HcofThisEvent.hh"
#include "G4Navigator.hh"

#include "NeuDetectorHit.hh"

#include <vector>


namespace NeuFlux {
	class NeuDetector : public G4VSensitiveDetector {
	public:
		NeuDetector();
		NeuDetector(G4String);
	   	~NeuDetector();

	   void Initialize(G4HCofThisEvent *);
	   G4bool ProcessHits(G4Step *, G4TouchableHistory *);
	   void EndOfEvent(G4HCofThisEvent *);
	   void SetRootBranches();
	   G4int* GetNHits() {
	      return &fNHitsAll;
	   };


	 private:
	   G4int fNHitsAll;
	   G4double fEtotalAll;
	   G4int fNEventsTotal;
	   
	   G4int fPDGCode;
	   G4double fEnergy;
	   G4Double fGlobalTime;


	   NeuDetectorHitsCollection* hitsCollection;
	   G4Navigator* theNav;
	};
}

#endif