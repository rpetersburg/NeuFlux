#include "NeuTrackingAction.hh"

#include "G4RunManager.hh"
#include "G4TrackingManager.hh"
#include "G4Track.hh"
#include "G4ParticleDefinition.hh"

#include <string>

NeuFlux::NeuTrackingAction::NeuTrackingAction() : NeuOutputtingComponent(),  fTrackID(0), fParentID(0), fPreX(0), fPreY(0), fPreZ(0), fPreLT(0), fPreGT(0), fPrePT(0),
 fPostX(0), fPostY(0), fPostZ(0), fPostLT(0), fPostGT(0), fPostPT(0),
 fPDGMass(0), fPDGWidth(0), fPDGCharge(0), fPDGSpin(0), fPDGiSpin(0), fPDGiParity(0), fPDGiConjugation(0), fPDGIsospin(0), fPDGIsospin3(0), fPDGiIsospin(0), fPDGiIsospin3(0), 
 fPDGiGParity(0), fPDGMagneticMoment(0), fLeptonNumber(0), fBaryonNumber(0), fPDGEncoding(0), fAtomicNumber(0), fAtomicMass(0),fVolume(0), fNextVolume(0)
{}

NeuFlux::NeuTrackingAction::~NeuTrackingAction()
{}

void NeuFlux::NeuTrackingAction::PreUserTrackingAction(const G4Track* theTrack)
{
	fPreX = theTrack->GetPosition().x();
	fPreY = theTrack->GetPosition().y();
	fPreZ = theTrack->GetPosition().z();
	fPreLT = theTrack->GetLocalTime();
	fPreGT = theTrack->GetGlobalTime();
	fPrePT = theTrack->GetProperTime();
}

void NeuFlux::NeuTrackingAction::PostUserTrackingAction(const G4Track* theTrack)
{
	fTrackID = theTrack->GetTrackID();
	fParentID = theTrack->GetParentID();
	fPostX = theTrack->GetPosition().x();
	fPostY = theTrack->GetPosition().y();
	fPostZ = theTrack->GetPosition().z();
	fPostLT = theTrack->GetLocalTime();
	fPostGT = theTrack->GetGlobalTime();
	fPostPT = theTrack->GetProperTime();

	const G4ParticleDefinition* def = theTrack->GetParticleDefinition();
	fPDGMass 		= def->GetPDGMass();
	fPDGWidth 		= def->GetPDGWidth();
	fPDGCharge 		= def->GetPDGCharge();
	fPDGSpin 		= def->GetPDGSpin();

	fPDGiSpin 		= def->GetPDGiSpin();
	fPDGiParity 	= def->GetPDGiParity();
	fPDGiConjugation= def->GetPDGiConjugation();
	fPDGIsospin		= def->GetPDGIsospin();
	fPDGIsospin3 	= def->GetPDGIsospin3();
	fPDGiIsospin 	= def->GetPDGiIsospin();
	fPDGiIsospin3 	= def->GetPDGiIsospin3();

	fPDGiGParity		= def->GetPDGiGParity();
	fPDGMagneticMoment 		= def->GetPDGMagneticMoment();
	fLeptonNumber	= def->GetLeptonNumber();
	fBaryonNumber 	= def->GetBaryonNumber();
	fPDGEncoding	= def->GetPDGEncoding();

	fAtomicNumber	= def->GetAtomicNumber();
	fAtomicMass		= def->GetAtomicMass();
	
	NeuFlux::NeuRootOutput::GetInstance()->FillTree("NeuTrackingAction");

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

void NeuFlux::NeuTrackingAction::OnNewFileCreate()
{
	NeuFlux::NeuRootOutput::GetInstance()->AddTree("NeuTrackingAction");
    NeuFlux::NeuRootOutput::GetInstance()->AddBranch<Double_t>("NeuTrackingAction","TrackID", &fTrackID ,"D");              
    NeuFlux::NeuRootOutput::GetInstance()->AddBranch<Double_t>("NeuTrackingAction","ParentID", &fParentID,"D");               
    NeuFlux::NeuRootOutput::GetInstance()->AddBranch<Double_t>("NeuTrackingAction","TrackPreX", &fPreX       ,"D");        
    NeuFlux::NeuRootOutput::GetInstance()->AddBranch<Double_t>("NeuTrackingAction","TrackPreY", &fPreY       ,"D");        
    NeuFlux::NeuRootOutput::GetInstance()->AddBranch<Double_t>("NeuTrackingAction","TrackPreZ", &fPreZ       ,"D");        
    NeuFlux::NeuRootOutput::GetInstance()->AddBranch<Double_t>("NeuTrackingAction","TrackPreLT", &fPreLT      ,"D");         
    NeuFlux::NeuRootOutput::GetInstance()->AddBranch<Double_t>("NeuTrackingAction","TrackPreGT", &fPreGT      ,"D");         
    NeuFlux::NeuRootOutput::GetInstance()->AddBranch<Double_t>("NeuTrackingAction","TrackPrePT", &fPrePT      ,"D");
    NeuFlux::NeuRootOutput::GetInstance()->AddBranch<Double_t>("NeuTrackingAction","TrackPostX", &fPostX       ,"D");        
    NeuFlux::NeuRootOutput::GetInstance()->AddBranch<Double_t>("NeuTrackingAction","TrackPostY", &fPostY       ,"D");        
    NeuFlux::NeuRootOutput::GetInstance()->AddBranch<Double_t>("NeuTrackingAction","TrackPostZ", &fPostZ       ,"D");        
    NeuFlux::NeuRootOutput::GetInstance()->AddBranch<Double_t>("NeuTrackingAction","TrackPostLT", &fPostLT      ,"D");         
    NeuFlux::NeuRootOutput::GetInstance()->AddBranch<Double_t>("NeuTrackingAction","TrackPostGT", &fPostGT      ,"D");         
    NeuFlux::NeuRootOutput::GetInstance()->AddBranch<Double_t>("NeuTrackingAction","TrackPostPT", &fPostPT      ,"D");
    NeuFlux::NeuRootOutput::GetInstance()->AddBranch<Double_t>("NeuTrackingAction","TrackVolume", &fVolume      ,"D");
    NeuFlux::NeuRootOutput::GetInstance()->AddBranch<Double_t>("NeuTrackingAction","TrackVolumeNextVolume", &fNextVolume      ,"D");

    NeuFlux::NeuRootOutput::GetInstance()->AddBranch<Double_t>("NeuTrackingAction","TrackPDGMass", &fPDGMass 			,"D");
	NeuFlux::NeuRootOutput::GetInstance()->AddBranch<Double_t>("NeuTrackingAction","TrackPDGWidth", &fPDGWidth 		,"D");
	NeuFlux::NeuRootOutput::GetInstance()->AddBranch<Double_t>("NeuTrackingAction","TrackPDGCharge", &fPDGCharge 		,"D");
	NeuFlux::NeuRootOutput::GetInstance()->AddBranch<Double_t>("NeuTrackingAction","TrackPDGSpin", &fPDGSpin 			,"D");

	NeuFlux::NeuRootOutput::GetInstance()->AddBranch<Double_t>("NeuTrackingAction","TrackPDGiSpin", &fPDGiSpin 		,"D");
	NeuFlux::NeuRootOutput::GetInstance()->AddBranch<Double_t>("NeuTrackingAction","TrackPDGiParity", &fPDGiParity 		,"D");
	NeuFlux::NeuRootOutput::GetInstance()->AddBranch<Double_t>("NeuTrackingAction","TrackPDGiConjugation", &fPDGiConjugation	,"D");
	NeuFlux::NeuRootOutput::GetInstance()->AddBranch<Double_t>("NeuTrackingAction","TrackPDGIsoSpin", &fPDGIsospin		,"D");
	NeuFlux::NeuRootOutput::GetInstance()->AddBranch<Double_t>("NeuTrackingAction","TrackPDGIsospin3", &fPDGIsospin3 		,"D");
	NeuFlux::NeuRootOutput::GetInstance()->AddBranch<Double_t>("NeuTrackingAction","TrackPDGiIsospin", &fPDGiIsospin 		,"D");
	NeuFlux::NeuRootOutput::GetInstance()->AddBranch<Double_t>("NeuTrackingAction","TrackPDGiIsospin3", &fPDGiIsospin3 	,"D");

	NeuFlux::NeuRootOutput::GetInstance()->AddBranch<Double_t>("NeuTrackingAction","TrackPDGiParity", &fPDGiGParity		,"D");
	NeuFlux::NeuRootOutput::GetInstance()->AddBranch<Double_t>("NeuTrackingAction","TrackPDGMagneticMoment", &fPDGMagneticMoment,"D");
	NeuFlux::NeuRootOutput::GetInstance()->AddBranch<Double_t>("NeuTrackingAction","TrackLeptonNumber", &fLeptonNumber		,"D");
	NeuFlux::NeuRootOutput::GetInstance()->AddBranch<Double_t>("NeuTrackingAction","TrackBaryonNumber", &fBaryonNumber 	,"D");
	NeuFlux::NeuRootOutput::GetInstance()->AddBranch<Int_t>("NeuTrackingAction","TrackPDGEncoding", &fPDGEncoding		,"I");

	NeuFlux::NeuRootOutput::GetInstance()->AddBranch<Double_t>("NeuTrackingAction","TrackAtomicNumber", &fAtomicNumber		,"D");
	NeuFlux::NeuRootOutput::GetInstance()->AddBranch<Double_t>("NeuTrackingAction","TrackAtomicMass", &fAtomicMass		,"D");
}



