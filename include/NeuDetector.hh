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
#include "KDSScintHit.hh"
#include <vector>

const G4int kScintMax = 10000;

class G4Step;
class G4HCofThisEvent;

class NeuDetector:public G4VSensitiveDetector {
 public:
   NeuDetector(G4String);
   ~NeuDetector();

   void Initialize(G4HCofThisEvent *);
   G4bool ProcessHits(G4Step *, G4TouchableHistory *);
   void EndOfEvent(G4HCofThisEvent *);
   void SetRootBranches();
   G4int *GetNHits() {
      return &fNHitsAll;
   };


 private:
   G4int fNHitsAll;
   G4double fEtotalAll;
   G4int fNEventsTotal;

   /*
   struct ScintHitInfo
   {
	   G4int 	fPDGCode;    //stores the code of the particle that hit it
	   G4double fEDep;		 //stores the energy deposited in the hit
	   G4double fNonIonE;    //stores the non-ionizing energy deposited in the detector
	   G4double fGlobalTime; //Stores the global time of the incident hit.
	   G4int fPanelID;		 //Stores the Panel ID of the scintillator hit.
   };
   std::vector<ScintHitInfo> hitInfos;
   */


   G4int fPDGCode[kScintMax];
   G4double fEdep[kScintMax];
   G4double fNonIonE[kScintMax];
   G4double fGlobalTime[kScintMax];
   G4int fPanelID[kScintMax];

   KDSScintHitsCollection *scintillatorCollection;
   G4Navigator *theNav;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//I don't know if I told you this, but these delimiters suck so bad
#endif