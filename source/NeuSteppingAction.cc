#include "NeuSteppingAction.hh"

#include "G4SteppingManager.hh"
#include "G4Step.hh"
#include "G4StepPoint.hh"
#include "G4Track.hh"
#include "G4ios.hh"


NeuFlux::NeuSteppingAction::NeuSteppingAction() : NeuOutputtingComponent(), fPreX(0), fPreY(0), fPreZ(0), fPreLocalT(0), fPreGlobalT(0), fPreProperT(0), fPreMomX(0), fPreMomY(0), fPreMomZ(0), fPreTotalE(0), fPreKinE(0),
 fPostX(0), fPostY(0), fPostZ(0), fPostLocalT(0), fPostGlobalT(0), fPostProperT(0), fPostMomX(0), fPostMomY(0), fPostMomZ(0), fPostTotalE(0), fPostKinE(0),
 fStepLength(0), fTotalEnergyDeposit(0), fTotalNonIEnergyDeposit(0),
 fDeltaX(0), fDeltaY(0), fDeltaZ(0), fDeltaT(0)
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

	//NeuFlux::NeuRootOutput::GetInstance()->FillTree("NeuSteppingAction");
}

void NeuFlux::NeuSteppingAction::OnNewFileCreate()
{
	NeuFlux::NeuRootOutput* output =  NeuFlux::NeuRootOutput::GetInstance();
	output->AddTree("NeuSteppingAction");
	  output->AddBranch<double>("NeuSteppingAction", "PreX", &fPreX);
      output->AddBranch<double>("NeuSteppingAction", "PreY", &fPreY);
      output->AddBranch<double>("NeuSteppingAction", "PreZ", &fPreZ);
      output->AddBranch<double>("NeuSteppingAction", "PreLocalT", &fPreLocalT);
      output->AddBranch<double>("NeuSteppingAction", "PreGlobalT", &fPreGlobalT);
      output->AddBranch<double>("NeuSteppingAction", "PreProperT", &fPreProperT);
      output->AddBranch<double>("NeuSteppingAction", "PreMomX", &fPreMomX);
      output->AddBranch<double>("NeuSteppingAction", "PreMomY", &fPreMomY);
      output->AddBranch<double>("NeuSteppingAction", "PreMomZ", &fPreMomZ);
      output->AddBranch<double>("NeuSteppingAction", "PreTotalE", &fPreTotalE);
      output->AddBranch<double>("NeuSteppingAction", "PreKinE", &fPreKinE);

      output->AddBranch<double>("NeuSteppingAction", "PostX", &fPostX);
      output->AddBranch<double>("NeuSteppingAction", "PostY", &fPostY);
      output->AddBranch<double>("NeuSteppingAction", "PostZ", &fPostZ);
      output->AddBranch<double>("NeuSteppingAction", "PostLocalT", &fPostLocalT);
      output->AddBranch<double>("NeuSteppingAction", "PostGlobalT", &fPostGlobalT);
      output->AddBranch<double>("NeuSteppingAction", "PostProperT", &fPostProperT);
      output->AddBranch<double>("NeuSteppingAction", "PostMomX", &fPostMomX);
      output->AddBranch<double>("NeuSteppingAction", "PostMomY", &fPostMomY);
      output->AddBranch<double>("NeuSteppingAction", "PostMomZ", &fPostMomZ);
      output->AddBranch<double>("NeuSteppingAction", "PostTotalE", &fPostTotalE);
      output->AddBranch<double>("NeuSteppingAction", "PostKinE", &fPostKinE);

      output->AddBranch<double>("NeuSteppingAction", "StepLength", &fStepLength);
      output->AddBranch<double>("NeuSteppingAction", "TotalEnergyDeposit", &fTotalEnergyDeposit);
      output->AddBranch<double>("NeuSteppingAction", "TotalNonIEnergyDeposit", &fTotalNonIEnergyDeposit);

      output->AddBranch<double>("NeuSteppingAction", "DeltaX", &fDeltaX);
      output->AddBranch<double>("NeuSteppingAction", "DeltaY", &fDeltaY);
      output->AddBranch<double>("NeuSteppingAction", "DeltaZ", &fDeltaZ);
      output->AddBranch<double>("NeuSteppingAction", "DeltaT", &fDeltaT);	
}

