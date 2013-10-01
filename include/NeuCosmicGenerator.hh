/**
 * \class NeuCosmicGenerator
 *
 * \ingroup NeuFlux
 *
 * \brief Code for defining the primary vertex of cosmic rays in the KDS Monte Carlo.
 *
 *     Energy and zenith angle defined for muons, neutrons, and nucleons.
 *     To save time, first pick a position on the x equals 0 plane near
 *     the detector plane_position, then use the zenith angle to pick a
 *     position outside the detector global_position aimed in to the
 *     plane_position.
 *
 * \note Defaults to Muon spectrum.
 *
 * \author Kevin Wierman
 * \author Michelle Leber
 *
 * \version $Revision: 1.5 $
 *
 * \date $Date: Tue Nov 20 12::33:51 2012 $
 *
 * Contact: kwierman@email.unc.edu
 *
 * Created on: Wed Apr 1 18:39:37 2005
 *
 */

#ifndef NeuCosmicGenerator_hh_
#define NeuCosmicGenerator_hh_

#include "globals.hh"
#include "G4ParticleGun.hh"
#include "G4ThreeVector.hh"
#include "G4ParticleDefinition.hh"
#include "G4PrimaryVertex.hh"
#include "G4ParticleMomentum.hh"

#include "TF2.h"
#include "TF1.h"
#include "TMath.h"

namespace NeuFlux
{

class TRandom3;
class G4Event;

class NeuCosmicGenerator:public G4ParticleGun {
  
public:
  NeuCosmicGenerator();
  virtual ~NeuCosmicGenerator();
  
public:
  /// Set to Muon Nucleon Neutron or Gamma to generate corresponding spectra
  virtual void SetSpectrumFlag(G4String);
  /// Sets the radius at which events will be generated. Do not exceed 68.923cm
  virtual void SetGlobalRadius(G4double);
  /// Set the incident plane half width.
  virtual void SetPlaneHalfLengthZ(G4double);
  /// Sets the incident place half length.
  virtual void SetPlaneHalfLengthY(G4double);
  ///  Sets the Z coordinate of the incident plane.
  virtual void SetPlaneOffsetZ(G4double);
  /// Sets the Y coordinate of the incident plane.
  virtual void SetPlaneOffsetY(G4double);
  /// Called by the Event Manager to Generate a vertex and add to the event.
  virtual void GeneratePrimaryVertex(G4Event * evt);
  
public:
  /// Sets the Target plane via 3Vector
  virtual void SetParticlePlanePosition(G4ThreeVector vec) 
  {particle_position_on_X_plane = vec;}
  /// Getter for the target plane.
  virtual G4ThreeVector GetParticlePlanePosition() 
  {return particle_position_on_X_plane;}
  /// Getter for the global Radius.
  virtual G4double GetGlobalRadius() {
    return TMath::Sqrt(fGlobalRadius2);
  }
  ///Getter for the Incident Plane.
  virtual G4double GetPlaneHalfLengthY() {
    return fPlaneHalfLengthY;
  }
  /// Getter for the Incident Plane.
  virtual G4double GetPlaneHalfLengthZ() {
    return fPlaneHalfLengthZ;
  }
  
  
private:
  void NeutronRandomizer();
  void NucleonRandomizer();
  void MuonRandomizer();
  void GammaRandomizer();
  void SetRandomPlanePosition();
  void SetRandomMomentumDirection();
  G4String spctrmFlag;                   ///< This is a flag set for the messenger.
  G4double fGlobalRadius2;               ///< Square Radius of Generation Sphere
  G4double fPlaneHalfLengthZ;            ///< Don't know
  G4double fPlaneHalfLengthY;            ///< Don't know
  G4double fPlaneOffsetZ;                ///< Don't know
  G4double fPlaneOffsetY;                ///< Don't know

  G4double cosmicTheta;        ///< zenith angle
  G4double globalradius2;      ///< start on sphere this far from origin of world
  TF2 *fMuonE;                 ///< Some sort of function for the muon energy
  TF2 *fNucleonE;              ///< Some sort of function for the Nucleon Energy
  TF1 *fNeutronE;              ///< Some sort of function for the Neutron Energy
  TF2 *fGammaE;                ///< Some sort fo function for the Gamma Energy
  TRandom3 *r3;                ///< RandomIzer
protected:
  virtual void SetInitialValues();
  virtual void InitializeEnergySpectra();
  ///Pointer to Randomizer function. Select Neutron, Nucleon, Muon or Gamma
  void (CosmicRayGun::*CosmicRandomizer)();
 
  G4ThreeVector particle_position_on_X_plane; ///< Points to the initial position on the plane the particle lies at.
  
};

}
#endif
