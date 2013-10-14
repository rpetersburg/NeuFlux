#include <map>
#include <utility>

#include "TROOT.h"
#include "TRandom3.h"

#include "G4RunManager.hh"
#include "G4VTouchable.hh"
#include "G4TouchableHistory.hh"
#include "G4TransportationManager.hh"
#include "G4Navigator.hh"
#include "G4HCofThisEvent.hh"
#include "G4Step.hh"
#include "G4ThreeVector.hh"
#include "G4SDManager.hh"
#include "G4ios.hh"

#include "NeuDetector.hh"
#include "NeuRunAction.hh"
#include "NeuTrackingAction.hh"

NeuFlux::NeuDetector::NeuDetector() : G4VSensitiveDetector("NeuDetector"), hitsCollection(NULL)
{

  collectionName.insert( G4String("NeuDetectorCollection") );
}


NeuFlux::NeuDetector::~NeuDetector()
{
}

void NeuFlux::NeuDetector::Initialize(G4HCofThisEvent* HCE)
{
   hitsCollection = new NeuDetectorHitsCollection(SensitiveDetectorName, collectionName[0]);

   static G4int HCID = -1;//hit collection ID
   if (HCID < 0) {
      HCID =
          G4SDManager::GetSDMpointer()->GetCollectionID(collectionName[0]);
   }

   HCE->AddHitsCollection(HCID, hitsCollection);

}

G4bool NeuFlux::NeuDetector::ProcessHits(G4Step * aStep,
                                         G4TouchableHistory *)
{
  
	G4double edep = aStep->GetTotalEnergyDeposit();
   if ( edep < 0.0000001 )
   {
     return false;
   }

   NeuDetectorHit *newHit = new NeuDetectorHit();
   /*
  G4TouchableHistory* theTouchable
     = (G4TouchableHistory*)(aStep->GetPreStepPoint()->GetTouchable());
   */

   hitsCollection->insert(newHit);
   return true;

}

void NeuFlux::NeuDetector::EndOfEvent(G4HCofThisEvent *)
{
}
