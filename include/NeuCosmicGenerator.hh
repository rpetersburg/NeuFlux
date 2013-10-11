

#ifndef NeuCosmicGenerator_hh_
#define NeuCosmicGenerator_hh_

#include "globals.hh"
#include "G4ParticleGun.hh"
#include "G4ThreeVector.hh"
#include "G4ParticleDefinition.hh"
#include "G4PrimaryVertex.hh"
#include "G4ParticleMomentum.hh"

#include "G4ParticleGun.hh"


class TRandom3;
class G4Event;

namespace NeuFlux
{

/*!
  \class NeuCosmicGenerator
 
  \ingroup NeuFlux
 
  \brief Code for defining the primary vertex of cosmic rays
 
      Energy and zenith angle defined for muons, neutrons, and nucleons.
      To save time, first pick a position on the x equals 0 plane near
      the detector plane_position, then use the zenith angle to pick a
      position outside the detector global_position aimed in to the
      plane_position.
 
  \note Defaults to Muon spectrum.
 
  \author Kevin Wierman
 
  \version 1.0
 
  \date Oct 1, 2013
 
  \contact kwierman@email.unc.edu
 
 */

class NeuCosmicGenerator:public G4ParticleGun {
  
public:
  NeuCosmicGenerator();
  virtual ~NeuCosmicGenerator();
  
public:
  virtual void GeneratePrimaryVertex(G4Event * evt);
};

}
#endif
