#include "NeuTrackingAction.hh"

#include "G4RunManager.hh"
#include "G4TrackingManager.hh"
#include "G4Track.hh"
#include "G4ParticleDefinition.hh"

#include <string>

NeuFlux::NeuTrackingAction::NeuTrackingAction() : NeuOutputtingComponent(),  fTrackID(0), fParentID(0), fX(0), fY(0), fZ(0), fLT(0), fGT(0), fPT(0), fVolume(0), fNextVolume(0)
{}

NeuFlux::NeuTrackingAction::~NeuTrackingAction()
{}

void NeuFlux::NeuTrackingAction::PreUserTrackingAction(const G4Track* /*theTrack*/)
{
	//UpdateBranches(theTrack);

	//NeuFlux::NeuRootOutput::GetInstance()->FillTree("NeuTrackingAction");
}

void NeuFlux::NeuTrackingAction::PostUserTrackingAction(const G4Track* theTrack)
{
	UpdateBranches( theTrack);
	NeuFlux::NeuRootOutput::GetInstance()->FillTree("NeuTrackingAction");
}

void NeuFlux::NeuTrackingAction::OnNewFileCreate()
{
	NeuFlux::NeuRootOutput::GetInstance()->AddTree("NeuTrackingAction");
    NeuFlux::NeuRootOutput::GetInstance()->AddBranch<double>("NeuTrackingAction"," TrackID", &fTrackID );              
    NeuFlux::NeuRootOutput::GetInstance()->AddBranch<double>("NeuTrackingAction"," ParentID", &fParentID);               
    NeuFlux::NeuRootOutput::GetInstance()->AddBranch<double>("NeuTrackingAction"," X", &fX       );        
    NeuFlux::NeuRootOutput::GetInstance()->AddBranch<double>("NeuTrackingAction"," Y", &fY       );        
    NeuFlux::NeuRootOutput::GetInstance()->AddBranch<double>("NeuTrackingAction"," Z", &fZ       );        
    NeuFlux::NeuRootOutput::GetInstance()->AddBranch<double>("NeuTrackingAction"," LT", &fLT      );         
    NeuFlux::NeuRootOutput::GetInstance()->AddBranch<double>("NeuTrackingAction"," GT", &fGT      );         
    NeuFlux::NeuRootOutput::GetInstance()->AddBranch<double>("NeuTrackingAction"," PT", &fPT      );
    NeuFlux::NeuRootOutput::GetInstance()->AddBranch<double>("NeuTrackingAction"," Volume", &fVolume      );
    NeuFlux::NeuRootOutput::GetInstance()->AddBranch<double>("NeuTrackingAction"," NextVolume", &fNextVolume      );         
}

void NeuFlux::NeuTrackingAction::UpdateBranches(const G4Track* theTrack)
{
	fTrackID = theTrack->GetTrackID();
	fParentID = theTrack->GetParentID();
	fX = theTrack->GetPosition().x();
	fY = theTrack->GetPosition().y();
	fZ = theTrack->GetPosition().z();
	fLT = theTrack->GetLocalTime();
	fGT = theTrack->GetGlobalTime();
	fPT = theTrack->GetProperTime();


	//#ifdef NeuDebug_tracks	
	const G4ParticleDefinition* def = theTrack->GetParticleDefinition();

	G4cout<<def->GetParticleType()<<"\t"<<def->GetParticleSubType()<<"\t"<<def->GetPDGEncoding()<<std::endl;
	if(def->GetPDGEncoding() == 2112)
	{
		G4cout<<"Beginning Neutron Track, slowing down"<<std::endl;
	}

	//if(def->GetPDGEncoding() != 2112 && def->GetPDGEncoding() != 13)
	//	theTrack->SetGoodForTrackingFlag(false);
	//#endif
	/*

	std::string name = theTrack->GetVolume()->GetName();
	if(name == "World")
		fVolume = 1;
	else if(name == "Rock")
		fVolume = 2;
	else if(name == "Concrete")
		fVolume = 3;
	else if (name == "Detector")
		fVolume = 4;

	std::string nextname = theTrack->GetNextVolume()->GetName();
	if(nextname == "World")
		fNextVolume = 1;
	else if(nextname == "Rock")
		fNextVolume = 2;
	else if(nextname == "Concrete")
		fNextVolume = 3;
	else if (nextname == "Detector")
		fNextVolume = 4;
		*/
}


