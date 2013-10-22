
#include "G4RunManager.hh"
#include "G4Run.hh"
#include "G4UImanager.hh"
#include "G4VVisManager.hh"
#include "G4ios.hh"

#include "NeuRunAction.hh"
#include "NeuRandom.hh"


NeuFlux::NeuRunAction::NeuRunAction() : G4UserRunAction(), NeuOutputtingComponent() 
{
  fTimeSeed = NeuFlux::NeuRandom::GetInstance()->GetRandom();
}

NeuFlux::NeuRunAction::~NeuRunAction()
{
  NeuFlux::NeuRootOutput::GetInstance()->Finish(); 
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
   
   std::stringstream ss;
   ss<<"NeuFlux_"<<fTimeSeed<<"_"<<fID<<".root";
  
  
   G4cout<<"Output Title: "<<ss.str()<<std::endl;

   NeuFlux::NeuRootOutput::GetInstance()->CreateNewFile( ss.str() );

   G4cout<<"---------------------------------------"<<std::endl;
}

void NeuFlux::NeuRunAction::EndOfRunAction(const G4Run * aRun)
{
	G4cout<<"---------------------------------------"<<std::endl;
	G4cout<<"Finishing up Run: "<<aRun->GetNumberOfEvent()<<std::endl;
  G4cout<<"With output title: "<<"NeuFlux_"<<fTimeSeed<<"_"<<fID<<".root"<<std::endl;
  

  NeuFlux::NeuRootOutput* output = NeuFlux::NeuRootOutput::GetInstance();
  output->FillTree("RunAction");
  output->WriteAllTrees();
  output->Finish();

  if (G4VVisManager::GetConcreteInstance())
    G4UImanager::GetUIpointer()->ApplyCommand("/vis/viewer/update");
  G4cout<<"---------------------------------------"<<std::endl;
}

void NeuFlux::NeuRunAction::OnNewFileCreate()
{

  NeuFlux::NeuRootOutput* output = NeuFlux::NeuRootOutput::GetInstance();
  output->AddTree("RunAction");
  output->AddBranch<G4int>("RunAction", "TimeSeed", &fTimeSeed,"I");
  output->AddBranch<G4int>("RunAction", "ID", &fID,"I");
  //output->FillTree("RunAction");
}

