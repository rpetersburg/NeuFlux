#ifndef NeuPrimaryGeneratorAction_hh_
#define NeuPrimaryGeneratorAction_hh_

#include "globals.hh"
#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4GeneralParticleSource.hh"
#include "G4ParticleGun.hh"

#include "NeuCosmicGenerator.hh"

class G4ParticleGun;
class TRandom3;
class G4Event;
class NeuEventAction;

namespace NeuFlux
{
	/*!
		\class NeuPrimaryGeneratorAction
		
		\ingroup NeuFlux
		
		\brief User Primary Classn
		
		
		\author Kevin Wierman
		
		\version 1.0
		
		\date Oct 1, 2013
		
		\contact kwierman@email.unc.edu
		
	 */

	class NeuPrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction 
	{

	public:
	   NeuPrimaryGeneratorAction();
	   virtual ~NeuPrimaryGeneratorAction();

	   void GeneratePrimaries(G4Event *);

	   NeuPrimaryGeneratorAction* SetNeutronFun();


	protected:
	   NeuFlux::NeuCosmicGenerator *theCosmicRayGun;
	   G4ParticleGun* fGPS;
	   bool fUseGPS;

	};
}

#endif

