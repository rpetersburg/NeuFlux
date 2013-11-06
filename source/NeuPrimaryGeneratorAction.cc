#include "NeuPrimaryGeneratorAction.hh"

#include "G4Event.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "globals.hh"
#include "G4UImanager.hh"


NeuFlux::NeuPrimaryGeneratorAction::NeuPrimaryGeneratorAction() : G4VUserPrimaryGeneratorAction(), fUseGPS(false)
{
   fGPS = new G4ParticleGun(1);
   theCosmicRayGun = new NeuCosmicGenerator();

   G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
   G4String pname = "neutron";
   G4ParticleDefinition* particle = particleTable->FindParticle(pname);
   fGPS->SetParticleDefinition(particle);
   fGPS->SetParticleMomentumDirection(G4ThreeVector(0., 0., -1.));
   fGPS->SetParticleEnergy(10.0*GeV);
   fGPS->SetParticlePosition(G4ThreeVector(0.*cm, 0.*cm, 0.0*cm) );
}
NeuFlux::NeuPrimaryGeneratorAction::~NeuPrimaryGeneratorAction()
{
   delete theCosmicRayGun;
   if(fGPS)
      delete fGPS;
}

NeuFlux::NeuPrimaryGeneratorAction* NeuFlux::NeuPrimaryGeneratorAction::SetNeutronFun()
{
   fUseGPS = true;
 return this;  
}


void NeuFlux::NeuPrimaryGeneratorAction::GeneratePrimaries(G4Event* theEvent)
{
   if(fUseGPS)
   {
      fGPS->GeneratePrimaryVertex(theEvent);
      return;
   }

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
