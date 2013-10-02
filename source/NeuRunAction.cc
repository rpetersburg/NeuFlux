
#include "G4RunManager.hh"
#include "G4Run.hh"
#include "G4UImanager.hh"
#include "G4VVisManager.hh"
#include "G4ios.hh"

#include "NeuRunAction.hh"
#include "NeuEventAction.hh"

NeuFlux::NeuRunAction::NeuRunAction(G4int time) : fTimeSeed(time), fOutput(0), fTree(0)
{
}

NeuFlux::NeuRunAction::~NeuRunAction()
{
  if(fOutput)
    delete fOutput;
}

void NeuFlux::NeuRunAction::BeginOfRunAction(const G4Run * aRun)
{
	G4cout<<"---------------------------------------"<<std::endl;
	G4cout<<"Beginning Run: "<<aRun->GetNumberOfEvent()<<std::endl;

   fID = aRun->GetRunID();
   if( G4VVisManager::GetConcreteInstance() ) {
      G4UImanager *UI = G4UImanager::GetUIpointer();
      UI->ApplyCommand("/vis/scene/notifyHandlers");
   }

   NeuEventAction *eventAction = (NeuEventAction*)
       G4RunManager::GetRunManager()->GetUserEventAction();
   
   std::stringstream ss;
   ss<<"NeuFlux_"<<fTimeSeed<<"_"<<fID<<eventAction->GetEventOption()<<".root";
  
  
   G4cout<<"Output Title: "<<ss.str()<<std::endl;

   if(fOutput)
      delete fOutput;
   fOutput = new TFile(ss.str().c_str(), "RECREATE", ss.str().c_str());

   fTree = new TTree("RunActionTree","RunActionTree");

   G4cout<<"---------------------------------------"<<std::endl;
}

void NeuFlux::NeuRunAction::EndOfRunAction(const G4Run * aRun)
{
	G4cout<<"---------------------------------------"<<std::endl;
	G4cout<<"Finishing up Run: "<<aRun->GetNumberOfEvent()<<std::endl;

   fTree->Write();
   fOutput->Write();
   fOutput->Close();
   
   fOutput = NULL;
   fTree=NULL;

   if (G4VVisManager::GetConcreteInstance()) {
      G4UImanager::GetUIpointer()->ApplyCommand("/vis/viewer/update");
   }
   G4cout<<"---------------------------------------"<<std::endl;
}


