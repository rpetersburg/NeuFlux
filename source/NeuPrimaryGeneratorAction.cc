#include "NeuPrimaryGeneratorAction.hh"

#include "G4Event.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "globals.hh"
#include "G4UImanager.hh"

#include "TRandom3.h"

NeuFlux::NeuPrimaryGeneratorAction::NeuPrimaryGeneratorAction() 
{
   
   theCosmicRayGun = new NeuCosmicGenerator();
   theCosmicRayGun->SetPlaneHalfLengthZ(1000.0);
   theCosmicRayGun->SetPlaneHalfLengthY(1000.0);
   theCosmicRayGun->SetPlaneOffsetZ(1000.0);
   theCosmicRayGun->SetPlaneOffsetY(1000.0);
   theCosmicRayGun->SetGlobalRadius(1000.0);

	//for random numbers
   //setting seed to 0 means using a TUUID to set the seed
	r3 = new TRandom3(0);
   //output->
}
NeuFlux::NeuPrimaryGeneratorAction::~NeuPrimaryGeneratorAction()
{
   delete theCosmicRayGun;
}


void NeuFlux::NeuPrimaryGeneratorAction::GeneratePrimaries(G4Event* theEvent)
{
   theCosmicRayGun->SetParticleDefinition( G4ParticleTable::GetParticleTable()->FindParticle("mu-") ) ;
   theCosmicRayGun->GeneratePrimaryVertex(theEvent);

   /*

   theEvent->SetInitialPDG(G4ParticleTable::GetParticleTable()->FindParticle("muon")->GetPDGEncoding(), 0);
   theEvent->SetNInitial( 1 );
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

   */
}
