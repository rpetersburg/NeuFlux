#include "NeuEventAction.hh"
#include "NeuRootOutput.hh"

#include "G4Event.hh"


NeuFlux::NeuEventAction::NeuEventAction() : fEventID(0), fPrimaryX(0), fPrimaryY(0), fPrimaryZ(0), fPrimaryT(0), fPrimaryN(0)
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

NeuFlux::NeuEventAction::~NeuEventAction()
{
}

void NeuFlux::NeuEventAction::BeginOfEventAction(const G4Event *event)
{
	G4cout<<std::endl;
	G4cout<<"---------------------------------------"<<std::endl;
	G4cout<<"Beginning Event: "<<event->GetEventID()<<std::endl;
	
	fEventID = event->GetEventID();
	fPrimaryX = 	event->GetPrimaryVertex()->GetX0();
	fPrimaryY = 	event->GetPrimaryVertex()->GetY0();
	fPrimaryZ = 	event->GetPrimaryVertex()->GetZ0();
	fPrimaryT = 	event->GetPrimaryVertex()->GetT0();
	fPrimaryN = 	event->GetPrimaryVertex()->GetNumberOfParticle();

	NeuFlux::NeuRootOutput* output = NeuFlux::NeuRootOutput::GetInstance();
	output->FillTree("NeuEventAction");
}

void NeuFlux::NeuEventAction::EndOfEventAction(const G4Event * evt)
{
	G4cout<<std::endl;
	G4cout<<"End of event"<<std::endl;
	G4cout<<"---------------------------------------"<<std::endl;
	
	fEventID = evt->GetEventID();
	
	NeuFlux::NeuRootOutput* output = NeuFlux::NeuRootOutput::GetInstance();
	output->FillTree("NeuEventAction");
}
