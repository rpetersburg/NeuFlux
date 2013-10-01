/*!
  \class NeuDetectorHit
  
  \ingroup NeuFlux
  
  \brief Container class for Detector Hits
  
  Contains this information:
    G4int fPanelID;
    G4double edep;
    G4double globaltime;
    G4int pdg;
    G4double nonionenergy;
  
  \author Kevin Wierman
  
  \version $Revision: 1.5 $
  
  \date $Date: Tue Nov 20 12::33:51 2012 $
  
  Contact: kwierman@email.unc.edu
  
  Created on: Wed Apr 1 18:39:37 2013
  
 */
#ifndef NeuDetectorHit_hh_
#define NeuDetectorHit_hh_

#include "G4VHit.hh"
#include "G4THitsCollection.hh"
#include "G4Allocator.hh"
#include "G4ThreeVector.hh"

class NeuDetectorHit:public G4VHit {
 public:

   NeuDetectorHit();
   ~NeuDetectorHit();
   NeuDetectorHit(const NeuDetectorHit &);
   const NeuDetectorHit & operator=(const NeuDetectorHit &);
   G4int operator==(const NeuDetectorHit &) const;

   inline void *operator  new(size_t);
   inline void operator  delete(void *);

   void Draw();
   void Print();

 public:

   void SetPanelID(G4int panel) {
      fPanelID = panel;
   };
   void SetEdep( G4double de) {
       edep = de;
  };
   void SetGlobalTime(G4double t) {
       globaltime = t;
  };
   void SetPDGCode(G4int id) {
      pdg = id;
   };
	void SetNonIonEnergy(G4double ke) {
      nonionenergy = ke;
   };
	void SetTrackID(G4int i){
		trackID=i;
	}
   
   G4int GetPanelID() {
      return fPanelID;
   };
   G4double GetEdep() {
      return edep;
   };
   G4double GetGlobalTime() {
      return globaltime;
   };
   G4int GetPDGCode() {
      return pdg;
   };
	G4double GetNonIonEnergy() {
      return nonionenergy;
   };
	G4int GetTrackID(){
		return trackID;
	}
   
 private:
   G4int fPanelID;
   G4double edep;
   G4double globaltime;
   G4int pdg;
   G4double nonionenergy;
   G4int trackID;
   
};
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

typedef G4THitsCollection < NeuDetectorHit >
    NeuDetectorHitsCollection;

extern G4Allocator < NeuDetectorHit >
    NeuDetectorHitAllocator;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

inline void *NeuDetectorHit::operator  new(size_t)
{
   void *aHit;
   aHit = (void *) NeuDetectorHitAllocator.MallocSingle();
   return aHit;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

inline void NeuDetectorHit::operator  delete(void *aHit)
{
   NeuDetectorHitAllocator.
       FreeSingle((NeuDetectorHit *) aHit);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif