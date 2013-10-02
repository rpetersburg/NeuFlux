#include "NeuPrimaryGeneratorAction.hh"

#include "NeuEventAction.hh"


#include "G4Event.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "globals.hh"
#include "G4UImanager.hh"

#include "TMath.h"
#include "TRandom3.h"


NeuFlux::NeuPrimaryGeneratorAction::NeuPrimaryGeneratorAction(NeuFlux::NeuEventAction * theEA) :  theEvent(theEA)
{
   
   theCosmicRayGun = new NeuCosmicGenerator();

	//for random numbers
   //setting seed to 0 means using a TUUID to set the seed
	r3 = new TRandom3(0);
}
NeuFlux::NeuPrimaryGeneratorAction::~NeuPrimaryGeneratorAction()
{
   delete theCosmicRayGun;
}

/*
void NeuFlux::NeuPrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{
   /*
   //using particle gun UI to set particle type
   theCosmicRayGun->SetParticleDefinition(theParticleGun->
                                        GetParticleDefinition());
   //randomization done within this function
   theCosmicRayGun->GeneratePrimaryVertex(anEvent);
   //store initial values in root file  
   theEvent->SetInitialPDG(theCosmicRayGun->GetParticleDefinition()->
                           GetPDGEncoding(), 0);
   theEvent->SetNInitial(theCosmicRayGun->GetNumberOfParticles());
   theEvent->SetInitialEnergy(theCosmicRayGun->GetParticleEnergy(), 0);
   //Plane Position only meaningful for cosmic rays and room radiation
   theEvent->SetInitialPlanePosition((this->*PlanePos)());
   G4ThreeVector position(theCosmicRayGun->GetParticlePosition());
   G4ThreeVector mom(theCosmicRayGun->GetParticleMomentumDirection());
   theEvent->SetInitialPosition(position);
   theEvent->SetInitialMomDir(mom, 0);
   theEvent->SetDotProduct(position.dot(mom) / position.mag() / mom.mag(),
                           0);
   theEvent->SetMomTheta(mom.angle(G4ThreeVector(-1, 0, 0)), 0);
   //theta is angle wrt straight down
   mom.setX(0);
   theEvent->SetMomPhi(mom.angle(G4ThreeVector(0, 1, 0)), 0);
   //phi is angle wrt y-axis (in x-plane)

}
*/

void NeuFlux::NeuPrimaryGeneratorAction::IdentifyParticle(G4int pid,
                                                           G4int i)
{
   if (pid == 0) {
      G4ParticleTable *particleTable = G4ParticleTable::GetParticleTable();
      G4ParticleDefinition *particle =
          particleTable->FindParticle("gamma");
      //theEvent->SetInitialPDG(particle->GetPDGEncoding(), i);
      theCosmicRayGun->SetParticleDefinition(particle);
   } else if (pid == 1) {
      G4ParticleTable *particleTable = G4ParticleTable::GetParticleTable();
      G4ParticleDefinition *particle = particleTable->FindParticle("e-");
      //theEvent->SetInitialPDG(particle->GetPDGEncoding(), i);
      theCosmicRayGun->SetParticleDefinition(particle);
   } else if (pid == 2) {
      G4ParticleTable *particleTable = G4ParticleTable::GetParticleTable();
      G4ParticleDefinition *particle =
          particleTable->FindParticle("alpha");
      //theEvent->SetInitialPDG(particle->GetPDGEncoding(), i);
      theCosmicRayGun->SetParticleDefinition(particle);
   } else {
      G4cout << G4endl << " *** can't find particle " << pid << G4endl;
   }

}

void NeuFlux::NeuPrimaryGeneratorAction::PrintGunParameters()
{
   ;
}
G4ThreeVector NeuFlux::NeuPrimaryGeneratorAction::CosmicPlanePosition() {
   return theCosmicRayGun->GetParticlePlanePosition();
}