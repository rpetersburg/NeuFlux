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
		
	NeuFlux::NeuRootOutput::GetInstance()->FillTree("NeuTrackingAction");
}

void NeuFlux::NeuTrackingAction::OnNewFileCreate()
{
	NeuFlux::NeuRootOutput::GetInstance()->AddTree("NeuTrackingAction");
    NeuFlux::NeuRootOutput::GetInstance()->AddBranch<double>("NeuTrackingAction","TrackID", &fTrackID );              
    NeuFlux::NeuRootOutput::GetInstance()->AddBranch<double>("NeuTrackingAction","ParentID", &fParentID);               
    NeuFlux::NeuRootOutput::GetInstance()->AddBranch<double>("NeuTrackingAction","TrackPreX", &fPreX       );        
    NeuFlux::NeuRootOutput::GetInstance()->AddBranch<double>("NeuTrackingAction","TrackPreY", &fPreY       );        
    NeuFlux::NeuRootOutput::GetInstance()->AddBranch<double>("NeuTrackingAction","TrackPreZ", &fPreZ       );        
    NeuFlux::NeuRootOutput::GetInstance()->AddBranch<double>("NeuTrackingAction","TrackPreLT", &fPreLT      );         
    NeuFlux::NeuRootOutput::GetInstance()->AddBranch<double>("NeuTrackingAction","TrackPreGT", &fPreGT      );         
    NeuFlux::NeuRootOutput::GetInstance()->AddBranch<double>("NeuTrackingAction","TrackPrePT", &fPrePT      );
    NeuFlux::NeuRootOutput::GetInstance()->AddBranch<double>("NeuTrackingAction","TrackPostX", &fPostX       );        
    NeuFlux::NeuRootOutput::GetInstance()->AddBranch<double>("NeuTrackingAction","TrackPostY", &fPostY       );        
    NeuFlux::NeuRootOutput::GetInstance()->AddBranch<double>("NeuTrackingAction","TrackPostZ", &fPostZ       );        
    NeuFlux::NeuRootOutput::GetInstance()->AddBranch<double>("NeuTrackingAction","TrackPostLT", &fPostLT      );         
    NeuFlux::NeuRootOutput::GetInstance()->AddBranch<double>("NeuTrackingAction","TrackPostGT", &fPostGT      );         
    NeuFlux::NeuRootOutput::GetInstance()->AddBranch<double>("NeuTrackingAction","TrackPostPT", &fPostPT      );
    NeuFlux::NeuRootOutput::GetInstance()->AddBranch<double>("NeuTrackingAction","TrackVolume", &fVolume      );
    NeuFlux::NeuRootOutput::GetInstance()->AddBranch<double>("NeuTrackingAction","TrackVolumeNextVolume", &fNextVolume      );

    NeuFlux::NeuRootOutput::GetInstance()->AddBranch<double>("NeuTrackingAction","TrackPDGMass", &fPDGMass 			);
	NeuFlux::NeuRootOutput::GetInstance()->AddBranch<double>("NeuTrackingAction","TrackPDGWidth", &fPDGWidth 		);
	NeuFlux::NeuRootOutput::GetInstance()->AddBranch<double>("NeuTrackingAction","TrackPDGCharge", &fPDGCharge 		);
	NeuFlux::NeuRootOutput::GetInstance()->AddBranch<double>("NeuTrackingAction","TrackPDGSpin", &fPDGSpin 			);

	NeuFlux::NeuRootOutput::GetInstance()->AddBranch<double>("NeuTrackingAction","TrackPDGiSpin", &fPDGiSpin 		);
	NeuFlux::NeuRootOutput::GetInstance()->AddBranch<double>("NeuTrackingAction","TrackPDGiParity", &fPDGiParity 		);
	NeuFlux::NeuRootOutput::GetInstance()->AddBranch<double>("NeuTrackingAction","TrackPDGiConjugation", &fPDGiConjugation	);
	NeuFlux::NeuRootOutput::GetInstance()->AddBranch<double>("NeuTrackingAction","TrackPDGIsoSpin", &fPDGIsospin		);
	NeuFlux::NeuRootOutput::GetInstance()->AddBranch<double>("NeuTrackingAction","TrackPDGIsospin3", &fPDGIsospin3 		);
	NeuFlux::NeuRootOutput::GetInstance()->AddBranch<double>("NeuTrackingAction","TrackPDGiIsospin", &fPDGiIsospin 		);
	NeuFlux::NeuRootOutput::GetInstance()->AddBranch<double>("NeuTrackingAction","TrackPDGiIsospin3", &fPDGiIsospin3 	);

	NeuFlux::NeuRootOutput::GetInstance()->AddBranch<double>("NeuTrackingAction","TrackPDGiParity", &fPDGiGParity		);
	NeuFlux::NeuRootOutput::GetInstance()->AddBranch<double>("NeuTrackingAction","TrackPDGMagneticMoment", &fPDGMagneticMoment);
	NeuFlux::NeuRootOutput::GetInstance()->AddBranch<double>("NeuTrackingAction","TrackLeptonNumber", &fLeptonNumber		);
	NeuFlux::NeuRootOutput::GetInstance()->AddBranch<double>("NeuTrackingAction","TrackBaryonNumber", &fBaryonNumber 	);
	NeuFlux::NeuRootOutput::GetInstance()->AddBranch<double>("NeuTrackingAction","TrackPDGEncoding", &fPDGEncoding		);

	NeuFlux::NeuRootOutput::GetInstance()->AddBranch<double>("NeuTrackingAction","TrackAtomicNumber", &fAtomicNumber		);
	NeuFlux::NeuRootOutput::GetInstance()->AddBranch<double>("NeuTrackingAction","TrackAtomicMass", &fAtomicMass		);
}



