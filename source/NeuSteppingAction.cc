#include "NeuSteppingAction.hh"

#include "G4SteppingManager.hh"
#include "G4Step.hh"
#include "G4StepPoint.hh"
#include "G4Track.hh"
#include "G4ios.hh"


NeuFlux::NeuSteppingAction::NeuSteppingAction() : NeuOutputtingComponent(), fPreX(0), fPreY(0), fPreZ(0), fPreLocalT(0), fPreGlobalT(0), fPreProperT(0), fPreMomX(0), fPreMomY(0), fPreMomZ(0), fPreTotalE(0), fPreKinE(0),
 fPostX(0), fPostY(0), fPostZ(0), fPostLocalT(0), fPostGlobalT(0), fPostProperT(0), fPostMomX(0), fPostMomY(0), fPostMomZ(0), fPostTotalE(0), fPostKinE(0),
 fStepLength(0), fTotalEnergyDeposit(0), fTotalNonIEnergyDeposit(0),
 fDeltaX(0), fDeltaY(0), fDeltaZ(0), fDeltaT(0), fTrackID(0)
{

}


NeuFlux::NeuSteppingAction::~NeuSteppingAction()
{

}

void NeuFlux::NeuSteppingAction::UserSteppingAction(const G4Step *
                                                     theStep)
{
	fPreX = theStep->GetPreStepPoint()->GetPosition().x();
	fPreY = theStep->GetPreStepPoint()->GetPosition().y();
	fPreZ = theStep->GetPreStepPoint()->GetPosition().z();
	fPreLocalT =  theStep->GetPreStepPoint()->GetLocalTime();
	fPreGlobalT = theStep->GetPreStepPoint()->GetGlobalTime();
	fPreProperT = theStep->GetPreStepPoint()->GetProperTime();
	fPreMomX = theStep->GetPreStepPoint()->GetMomentum().x();
	fPreMomY = theStep->GetPreStepPoint()->GetMomentum().y();
	fPreMomZ = theStep->GetPreStepPoint()->GetMomentum().z();
	fPreTotalE = theStep->GetPreStepPoint()->GetTotalEnergy();
	fPreKinE = theStep->GetPreStepPoint()->GetKineticEnergy();

	fPostX = theStep->GetPostStepPoint()->GetPosition().x();
	fPostY = theStep->GetPostStepPoint()->GetPosition().y();
	fPostZ = theStep->GetPostStepPoint()->GetPosition().z();
	fPostLocalT = theStep->GetPostStepPoint()->GetLocalTime();
	fPostGlobalT = theStep->GetPostStepPoint()->GetGlobalTime();
	fPostProperT = theStep->GetPostStepPoint()->GetProperTime();
	fPostMomX = theStep->GetPostStepPoint()->GetMomentum().x();
	fPostMomY = theStep->GetPostStepPoint()->GetMomentum().y();
	fPostMomZ = theStep->GetPostStepPoint()->GetMomentum().z();
	fPostTotalE = theStep->GetPostStepPoint()->GetTotalEnergy();
	fPostKinE = theStep->GetPostStepPoint()->GetKineticEnergy();

	fStepLength = theStep->GetStepLength();
	fTotalEnergyDeposit = theStep->GetTotalEnergyDeposit();
	fTotalNonIEnergyDeposit = theStep->GetNonIonizingEnergyDeposit();
	fDeltaX = theStep->GetDeltaPosition().x();
	fDeltaY = theStep->GetDeltaPosition().y();
	fDeltaZ = theStep->GetDeltaPosition().z();
	fDeltaT = theStep->GetDeltaTime();

	fTrackID = theStep->GetTrack()->GetTrackID();

	NeuFlux::NeuRootOutput::GetInstance()->FillTree("NeuSteppingAction");
}

void NeuFlux::NeuSteppingAction::OnNewFileCreate()
{
	NeuFlux::NeuRootOutput* output =  NeuFlux::NeuRootOutput::GetInstance();
	output->AddTree("NeuSteppingAction");
	  output->AddBranch<Double_t>("NeuSteppingAction", "PreX", &fPreX,"D");
      output->AddBranch<Double_t>("NeuSteppingAction", "PreY", &fPreY,"D");
      output->AddBranch<Double_t>("NeuSteppingAction", "PreZ", &fPreZ,"D");
      output->AddBranch<Double_t>("NeuSteppingAction", "PreLocalT", &fPreLocalT,"D");
      output->AddBranch<Double_t>("NeuSteppingAction", "PreGlobalT", &fPreGlobalT,"D");
      output->AddBranch<Double_t>("NeuSteppingAction", "PreProperT", &fPreProperT,"D");
      output->AddBranch<Double_t>("NeuSteppingAction", "PreMomX", &fPreMomX,"D");
      output->AddBranch<Double_t>("NeuSteppingAction", "PreMomY", &fPreMomY,"D");
      output->AddBranch<Double_t>("NeuSteppingAction", "PreMomZ", &fPreMomZ,"D");
      output->AddBranch<Double_t>("NeuSteppingAction", "PreTotalE", &fPreTotalE,"D");
      output->AddBranch<Double_t>("NeuSteppingAction", "PreKinE", &fPreKinE,"D");

      output->AddBranch<Double_t>("NeuSteppingAction", "PostX", &fPostX,"D");
      output->AddBranch<Double_t>("NeuSteppingAction", "PostY", &fPostY,"D");
      output->AddBranch<Double_t>("NeuSteppingAction", "PostZ", &fPostZ,"D");
      output->AddBranch<Double_t>("NeuSteppingAction", "PostLocalT", &fPostLocalT,"D");
      output->AddBranch<Double_t>("NeuSteppingAction", "PostGlobalT", &fPostGlobalT,"D");
      output->AddBranch<Double_t>("NeuSteppingAction", "PostProperT", &fPostProperT,"D");
      output->AddBranch<Double_t>("NeuSteppingAction", "PostMomX", &fPostMomX,"D");
      output->AddBranch<Double_t>("NeuSteppingAction", "PostMomY", &fPostMomY,"D");
      output->AddBranch<Double_t>("NeuSteppingAction", "PostMomZ", &fPostMomZ,"D");
      output->AddBranch<Double_t>("NeuSteppingAction", "PostTotalE", &fPostTotalE,"D");
      output->AddBranch<Double_t>("NeuSteppingAction", "PostKinE", &fPostKinE,"D");

      output->AddBranch<Double_t>("NeuSteppingAction", "StepLength", &fStepLength,"D");
      output->AddBranch<Double_t>("NeuSteppingAction", "TotalEnergyDeposit", &fTotalEnergyDeposit,"D");
      output->AddBranch<Double_t>("NeuSteppingAction", "TotalNonIEnergyDeposit", &fTotalNonIEnergyDeposit,"D");

      output->AddBranch<Double_t>("NeuSteppingAction", "DeltaX", &fDeltaX,"D");
      output->AddBranch<Double_t>("NeuSteppingAction", "DeltaY", &fDeltaY,"D");
      output->AddBranch<Double_t>("NeuSteppingAction", "DeltaZ", &fDeltaZ,"D");
      output->AddBranch<Double_t>("NeuSteppingAction", "DeltaT", &fDeltaT,"D");	
      output->AddBranch<Int_t>("NeuSteppingAction", "TrackID", &fTrackID,"I");	
}

