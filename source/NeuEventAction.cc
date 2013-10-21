#include "NeuEventAction.hh"


#include "G4Event.hh"


NeuFlux::NeuEventAction::NeuEventAction() : NeuOutputtingComponent(), fEventID(0), fPrimaryX(0), fPrimaryY(0), fPrimaryZ(0), fPrimaryT(0), fPrimaryN(0)
{

}

NeuFlux::NeuEventAction::~NeuEventAction()
{
}

void NeuFlux::NeuEventAction::OnNewFileCreate()
{
	NeuFlux::NeuRootOutput* output = NeuFlux::NeuRootOutput::GetInstance();
	output->AddTree("NeuEventAction");
	output->AddBranch<G4int>("NeuEventAction", "EventID", &fEventID);
	output->AddBranch<G4double>("NeuEventAction", "PrimaryEventX",		&fPrimaryX );
	output->AddBranch<G4double>("NeuEventAction", "PrimaryEventY",		&fPrimaryY);
	output->AddBranch<G4double>("NeuEventAction", "PrimaryEventZ",		&fPrimaryZ);
	output->AddBranch<G4double>("NeuEventAction", "PrimaryEventT",		&fPrimaryT);
	output->AddBranch<G4int>("NeuEventAction", "PrimaryEventN" ,		&fPrimaryN);
}

void NeuFlux::NeuEventAction::BeginOfEventAction(const G4Event *event)
{
	G4cout<<std::endl;
	G4cout<<"---------------------------------------"<<std::endl;
	G4cout<<"Beginning Event: "<<event->GetEventID()<<std::endl;
	G4cout<<"\tEvent ID:\t"<<event->GetEventID()<<std::endl;
	G4int nPrimaries = event->GetNumberOfPrimaryVertex();
	G4cout<<"\tN Events:\t"<<nPrimaries<<std::endl;
	for(G4int i=0; i<nPrimaries;i++)
	{
		G4PrimaryVertex* vertex = event->GetPrimaryVertex(i);
		G4cout<<"\tVertex:\t"<<i<<std::endl;
		G4cout<<"\t\t"<<vertex->GetX0()<<std::endl;
		G4cout<<"\t\t"<<vertex->GetY0()<<std::endl;
		G4cout<<"\t\t"<<vertex->GetZ0()<<std::endl;
		G4cout<<"\t\t"<<vertex->GetT0()<<std::endl;
	}
}

void NeuFlux::NeuEventAction::EndOfEventAction(const G4Event * evt)
{
	G4cout<<std::endl;
	G4cout<<"End of event"<<std::endl;
	G4cout<<"---------------------------------------"<<std::endl;
	
	fEventID = evt->GetEventID();
	
	fPrimaryX = 	evt->GetPrimaryVertex()->GetX0();
	fPrimaryY = 	evt->GetPrimaryVertex()->GetY0();
	fPrimaryZ = 	evt->GetPrimaryVertex()->GetZ0();
	fPrimaryT = 	evt->GetPrimaryVertex()->GetT0();
	
	fPrimaryN = 	evt->GetPrimaryVertex()->GetNumberOfParticle();	
	NeuFlux::NeuRootOutput* output = NeuFlux::NeuRootOutput::GetInstance();
	output->FillTree("NeuEventAction");	
}


