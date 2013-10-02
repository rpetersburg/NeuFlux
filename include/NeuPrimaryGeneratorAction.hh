/*!
	\class NeuPrimaryGeneratorAction
	
	\ingroup NeuFlux
	
	\brief Utility for generating primary vertices.
	
		Using the NeuPrimaryGeneratorActionMessenger, the
		primary vertex generator is selected from the available
		guns and sources:
		   G4ParticleGun: The pointer to the actual gun that is being used.
	  G4GeneralParticleSource:
	  G4ParticleGun
	  CosmicRayGun
	  RoomRadiationGun
	  CalibrationGenerator
	  KatrinBeamGun
	
	
	\author Kevin Wierman
	
	\version 1.0
	
	\date Oct 1, 2013
	
	Contact: kwierman@email.unc.edu
	
	Created on: Wed Apr 1 18:39:37 2005
	
 */

#ifndef NeuPrimaryGeneratorAction_hh_
#define NeuPrimaryGeneratorAction_hh_

///     Geant4 package includes
#include "globals.hh"
#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4GeneralParticleSource.hh"
#include "NeuCosmicGenerator.hh"

//forward declarations
class G4ParticleGun;
class TRandom3;
class G4Event;
class NeuEventAction;

namespace NeuFlux
{

	class NeuPrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction 
	{

	public:
	   NeuPrimaryGeneratorAction(NeuFlux::NeuEventAction *);
	   ~NeuPrimaryGeneratorAction();

	public:
	   void GeneratePrimaries(G4Event *);
	   void CurrentGenerator(G4Event *);
	   void GPSGenerator(G4Event *);
	   void CalGenerator(G4Event *);
	   void DecayFlux(G4Event *);
	   void (NeuPrimaryGeneratorAction::*Flux) (G4Event *);
	   G4ThreeVector (NeuPrimaryGeneratorAction::*PlanePos) ();
	   void SetNuclide();
	   void IdentifyParticle(G4int, G4int);
	   void SetSpectrumFlag(G4String);
	   void SetCalIsotope(G4String);
	   void SetEnergyRangeFlag(G4String);
	   void PrintGunParameters();
		CosmicRayGun *GetCosmicRayGun(){
			return theCosmicRayGun;
		}

	private:
		G4ThreeVector CosmicPlanePosition();
	   	DecayChain * uchain;
	   	NeuEventAction *theEvent;

	   G4String spctrmFlag;
	   G4String isoFlag;
	   G4String energyFlag;
	   TRandom3 *r3;
	protected:
	   G4ParticleGun * theCurrentGun;
	   G4GeneralParticleSource *theGPSGun;
	   G4ParticleGun *theParticleGun;
	   CosmicRayGun *theCosmicRayGun;
	};
}

#endif
