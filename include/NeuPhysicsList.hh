


#ifndef NeuPhysicsList_hh_
#define NeuPhysicsList_hh_

#include "G4VUserPhysicsList.hh"
#include "globals.hh"

namespace NeuFlux
{
  /*!
    \class NeuPhysicsList
    
    \ingroup NeuFlux
    
    \brief Defines and adds all physics processes used in the simulation.
    
      Bosons:
       G4Geantino
        G4ChargedGeantino
        G4Gamma
        G4OpticalPhoton
    
     Leptons:
         G4Electron
         G4Positron
         G4MuonPlus
         G4MuonMinus
         G4NeutrinoE
         G4AntiNeutrinoE
         G4NeutrinoMu
         G4AntiNeutrinoMu
    
     Hadrons:
          Standard Constructor for Meson
          Standard Constructor for baryon
          Standard Constructor for ion
    
     Short Lived's:
          So Short, they didn't make it on here.
    
    \author Kevin Wierman
    
    \version 1.0
    
    \date Oct 1, 2013
    
    Contact: kwierman@email.unc.edu
    
    Created on: Wed Apr 1 18:39:37 2005
  
 */
  class NeuPhysicsList: public G4VUserPhysicsList
  {
  public:
    NeuPhysicsList();
    virtual ~NeuPhysicsList();

  public:
    virtual void SetCuts();

  protected:
    // Construct particle and physics
    virtual void ConstructParticle();
    virtual void ConstructProcess();
      
    // these methods Construct physics processes and register them
    virtual void ConstructGeneral();
    virtual void ConstructEM();
    virtual void ConstructHad();
    virtual void ConstructOp();


    /* these methods Construct all particles in each category
    virtual void ConstructAllBosons();
    virtual void ConstructAllLeptons();
    virtual void ConstructAllMesons();
    virtual void ConstructAllBaryons();
    virtual void ConstructAllIons();
    virtual void ConstructAllShortLiveds();
    */

    virtual void AddTransportation();

  private:
    G4int VerboseLevel;
    G4int OpVerbLevel;

    G4double cutForGamma;
    G4double cutForElectron;
    G4double cutForPositron;
    G4double cutForProton;
    G4double cutForAlpha;
    G4double cutForGenericIon;

    // these methods Construct particles 
    void ConstructMyBosons();
    void ConstructMyLeptons();
    void ConstructMyHadrons();
    void ConstructMyShortLiveds();

  };
}
#endif
