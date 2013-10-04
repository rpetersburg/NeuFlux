
#ifndef NeuDetector_hh_
#define NeuDetector_hh_ 

#include "G4VSensitiveDetector.hh"
#include "G4Step.hh"
#include "G4HcofThisEvent.hh"
#include "G4Navigator.hh"

#include "NeuDetectorHit.hh"

#include <vector>


namespace NeuFlux {
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
		
		\date Oct 1, 2013
		
		\contact kwierman@email.unc.edu	
 	*/
	class NeuDetector : public G4VSensitiveDetector {
	public:
		NeuDetector();
	   	~NeuDetector();

	   void Initialize(G4HCofThisEvent *);
	   G4bool ProcessHits(G4Step *, G4TouchableHistory *);
	   void EndOfEvent(G4HCofThisEvent *);


	 private:
	 	NeuDetectorHitsCollection* hitsCollection;
	};
}

#endif


