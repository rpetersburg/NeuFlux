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
	output->AddBranch<G4int>("NeuEventAction", "EventID", &fEventID,"I");
	output->AddBranch<G4double>("NeuEventAction", "PrimaryEventX",		&fPrimaryX,"D" );
	output->AddBranch<G4double>("NeuEventAction", "PrimaryEventY",		&fPrimaryY,"D");
	output->AddBranch<G4double>("NeuEventAction", "PrimaryEventZ",		&fPrimaryZ,"D");
	output->AddBranch<G4double>("NeuEventAction", "PrimaryEventT",		&fPrimaryT,"D");
	output->AddBranch<G4int>("NeuEventAction", "PrimaryEventN" ,		&fPrimaryN,"D");
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
		G4cout<<"\t\tX: "<<vertex->GetX0()<<std::endl;
		G4cout<<"\t\tY: "<<vertex->GetY0()<<std::endl;
		G4cout<<"\t\tZ: "<<vertex->GetZ0()<<std::endl;
		G4cout<<"\t\tT: "<<vertex->GetT0()<<std::endl;
		G4cout<<"\t\tN: "<<vertex->GetNumberOfParticle()<<std::endl;
		for(G4int j=0; j<vertex->GetNumberOfParticle(); ++j )
		{
			G4PrimaryParticle* particle = vertex->GetPrimary(j);
			G4cout<<"\t\t\tParticle: "<<j<<std::endl;
			G4cout<<"\t\t\tPDG:"<<particle->GetPDGcode()<<std::endl;
			G4cout<<"\t\t\tKE:"<<particle->GetKineticEnergy()<<std::endl;
			G4cout<<"\t\t\tMomentum:"<<particle->GetTotalMomentum()<<std::endl;
			G4cout<<"\t\t\tTotalE:"<<particle->GetTotalEnergy()<<std::endl;
			G4cout<<"\t\t\tGetPx:"<<particle->GetPx()<<std::endl;
			G4cout<<"\t\t\tGetPy:"<<particle->GetPy()<<std::endl;
			G4cout<<"\t\t\tGetPz:"<<particle->GetPz()<<std::endl;

		}
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


