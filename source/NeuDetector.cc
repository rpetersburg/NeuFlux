#include "NeuDetector.hh"
#include "NeuRunAction.hh"
#include "NeuTrackingAction.hh"

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

#include <map>
#include <utility>

//root includes
#include "TROOT.h"
#include "TRandom3.h"

using namespace std;
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

NeuDetector::NeuDetector(G4String name)
:  G4VSensitiveDetector(name), theNav(0)
{
   G4String HCname;
   collectionName.insert(HCname = "scintillatorCollection");
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

NeuDetector::~NeuDetector()
{
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void NeuDetector::Initialize(G4HCofThisEvent* HCE)
{
   scintillatorCollection = new NeuScintHitsCollection
       (SensitiveDetectorName, collectionName[0]);
   static G4int HCID = -1;//hit collection ID
   if (HCID < 0) {
      HCID =
          G4SDManager::GetSDMpointer()->GetCollectionID(collectionName[0]);
   }
   HCE->AddHitsCollection(HCID, scintillatorCollection);
   SetRootBranches();
   fNHitsAll = 0;
   fEtotalAll =  0;
   fNEventsTotal =  0;
	for (G4int i = 0; i < kScintMax; i++) {
		fEdep[i] = fGlobalTime[i] = fNonIonE[i]= 0;
		fPanelID[i] = fPDGCode[i] = 0;
	}
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4bool NeuDetector::ProcessHits(G4Step * aStep,
                                         G4TouchableHistory *)
{
	G4double edep = aStep->GetTotalEnergyDeposit();

   if ( edep < 0.0000001 )
   {
	   return false;
   }
   //std::cout<<"Adding in new scint hit"<<std::endl;

   NeuScintHit *newHit = new NeuScintHit();

  G4TouchableHistory* theTouchable
     = (G4TouchableHistory*)(aStep->GetPreStepPoint()->GetTouchable());

  if (!theNav){ theNav = new G4Navigator();
     theNav->SetWorldVolume(
            G4TransportationManager::GetTransportationManager()->GetNavigatorForTracking()->GetWorldVolume()
       );
   }

  G4VPhysicalVolume * physVol = theTouchable->GetVolume();
  G4int panel = physVol->GetCopyNo();
  newHit->SetPanelID(panel);
  newHit->SetEdep(edep);
  newHit->SetGlobalTime(aStep->GetPreStepPoint()->GetGlobalTime());
   newHit->SetPDGCode(aStep->GetTrack()->GetDefinition()->GetPDGEncoding());
   newHit->SetNonIonEnergy(aStep->GetNonIonizingEnergyDeposit());
   newHit->SetTrackID(aStep->GetTrack()->GetTrackID());

  scintillatorCollection->insert(newHit);
   return true;

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void NeuDetector::EndOfEvent(G4HCofThisEvent *)
{
	
   fNHitsAll = scintillatorCollection->entries();//total number of hits in any panel
	
   //separate hits into panels and 100 ns "events"
   G4double timeStamp;  //time of earliest hit, save as time of 1st event
   G4int eventCounter = 0; //reset each run
   G4int hitMarker = 0;
	
	//loop over panels
	for (G4int j = 0; j < kNPanels; j++) {
		multimap<double, int> E0; //time ns, energy keV container
		 fEtotalAll = 0;//reset for each panel because only need to sum once
		//loop over all hits
      for (G4int i = 0; i < fNHitsAll; i++) {
			//Sum up total energies		
			fEtotalAll += (*scintillatorCollection)[i]->GetEdep() / keV;
			//for each panel create container of hits ordered by time
			if ((*scintillatorCollection)[i]->GetPanelID() == j) { 
				E0.insert(pair<double,
							 int>((*scintillatorCollection)[i]->GetGlobalTime() / ns, i));
			}
		}
		//if there were hits in this panel
		if ( E0.size() >0 ) {
			eventCounter++;
			multimap<double, int>::iterator one = E0.begin();
			timeStamp = one->first; //time of first hit
			//for every hit in this panel
			for (multimap<double, int>::iterator it = E0.begin();
				it != E0.end();
				++it) {
			 // if within 100 ns of first hit, sum into one event
			 if ( it->first - timeStamp < 100 * ns ) {
             hitMarker = it->second;  
             fNonIonE[eventCounter-1]+= (*scintillatorCollection)[hitMarker]->GetNonIonEnergy() / keV;
				 fEdep[eventCounter-1]+=(*scintillatorCollection)[hitMarker]->GetEdep() / keV;
				 fGlobalTime[eventCounter-1] = timeStamp;
				 fPanelID[eventCounter-1] = j; 
             fPDGCode[eventCounter-1] = (*scintillatorCollection)[hitMarker]->GetPDGCode();
			 } else {
				 timeStamp = it->first;
              eventCounter++;
				  fEdep[eventCounter-1]+=(*scintillatorCollection)[hitMarker]->GetEdep() / keV;
             fNonIonE[eventCounter-1]+= (*scintillatorCollection)[hitMarker]->GetNonIonEnergy() / keV;
              fGlobalTime[eventCounter-1] = timeStamp;
				  fPanelID[eventCounter-1] = j; 
             fPDGCode[eventCounter-1] = (*scintillatorCollection)[hitMarker]->GetPDGCode();
			 }
       } //close loop over hits
     } 
		fNEventsTotal = eventCounter;//should equal sum of fNevents
  }//close loop over panels
   //check to make sure arrays are large enough
   if ( fNEventsTotal >= kScintMax ) {
      G4cout << G4endl << " *** error: ScintSD arrays too small! *** " << G4endl;
      G4cout << "Number of particles "<< fNEventsTotal << G4endl;
    }


}

void NeuDetector::SetRootBranches(){
   G4RunManager *runManager = G4RunManager::GetRunManager();
   NeuRunAction *theRun =
       (NeuRunAction *) runManager->GetUserRunAction();
   char nHitsBranch[100] = "ScintSDNHits";
   if (!theRun->GetTree()->GetBranchStatus(nHitsBranch)) {
     theRun->GetTree()->Branch(nHitsBranch, &fNHitsAll,
                                "ScintSDNHits/I");
		
     theRun->GetTree()->Branch("ScintSDEdepTotal", &fEtotalAll,
                                "ScintSDEdepTotal/D");
	  
     theRun->GetTree()->Branch("ScintSDNEventsTotal", &fNEventsTotal,
                                "ScintSDNEventsTotal/I");
	  
     theRun->GetTree()->Branch("ScintSDEdep", fEdep,
										 "ScintSDEdep[ScintSDNEventsTotal]/D");
	  
      theRun->GetTree()->Branch("ScintSDNonIonizingEnergy", fNonIonE,
                                "ScintSDNonIonizingEnergy[ScintSDNEventsTotal]/D");
      
      theRun->GetTree()->Branch("ScintSDGlobalTime", fGlobalTime,
									  "ScintSDGlobalTIme[ScintSDNEventsTotal]/D");
	  
	  theRun->GetTree()->Branch("ScintSDPanelID", fPanelID,
										 "ScintSDPanelID[ScintSDNEventsTotal]/I");

     	theRun->GetTree()->Branch("ScintSDPDGCode", fPDGCode,
                                "ScintSDPDGCode[ScintSDNEventsTotal]/I");

  }
}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
