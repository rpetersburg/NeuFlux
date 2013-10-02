#include "NeuCuts.hh"
#include "G4VParticleChange.hh"
#include "G4Track.hh"
#include "G4Step.hh"

NeuFlux::NeuCuts::NeuCuts(const G4String & aName)
:G4VProcess(aName)
{
   if (verboseLevel > 1) {
      G4cout << GetProcessName() << " is created " << G4endl;
   }
}

NeuFlux::NeuCuts::~NeuCuts()
{
}

G4VParticleChange* NeuFlux::NeuCuts::PostStepDoIt(const G4Track & aTrack, const G4Step &)                                                                          
{
   aParticleChange.Initialize(aTrack);
   aParticleChange.ProposeEnergy(0.);
   aParticleChange.ProposeLocalEnergyDeposit(aTrack.GetKineticEnergy());
   aParticleChange.ProposeTrackStatus(fStopButAlive);
   return &aParticleChange;
}

G4double NeuFlux::NeuCuts::PostStepGetPhysicalInteractionLength(const G4Track &, G4double,
                                     G4ForceCondition *)
{
   return DBL_MAX;
}
