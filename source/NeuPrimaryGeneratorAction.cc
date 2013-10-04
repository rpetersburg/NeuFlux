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

	//for random numbers
   //setting seed to 0 means using a TUUID to set the seed
	r3 = new TRandom3(0);
   //output->
}
NeuFlux::NeuPrimaryGeneratorAction::~NeuPrimaryGeneratorAction()
{
   delete theCosmicRayGun;
}


void NeuFlux::NeuPrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{
   theCosmicRayGun->GeneratePrimaryVertex(anEvent);
   //store the initial information to file.   
}
