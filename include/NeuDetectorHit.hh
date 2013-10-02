/*!
  \class NeuDetectorHit
  
  \ingroup NeuFlux
  
  \brief Container class for Detector Hits
  
  Contains this information:
    Energy of the particle
    Global time
    Particle ID
    Track ID
  
  \author Kevin Wierman
  
  \version $Revision: 1.5 $
  
  \date $Date: Tue Nov 20 12::33:51 2012 $
  
  Contact: kwierman@email.unc.edu
  
  Created on: Wed Apr 1 18:39:37 2013
  
 */
#ifndef NeuDetectorHit_hh_
#define NeuDetectorHit_hh_

#include "G4VHit.hh"
#include "G4THitsCollection.hh"
#include "G4Allocator.hh"
#include "G4ThreeVector.hh"

namespace NeuFlux
{

  class NeuDetectorHit : public G4VHit {
  private:
    G4double fEnergy;
    G4double fGlobalTime;
    G4int fPDG;
    G4int fTrackID;

  public:

    NeuDetectorHit();
    ~NeuDetectorHit();
    NeuDetectorHit(const NeuDetectorHit &);
    const NeuDetectorHit & operator=(const NeuDetectorHit &);
    G4int operator==(const NeuDetectorHit &) const;

    inline void* operator  new(size_t);
    inline void operator  delete(void *);

    void Draw();
    void Print();

  public:
    void SetEnergy( G4double de) 
      {fEnergy = de;}
    void SetGlobalTime(G4double t) 
      {fGlobalTime = t;}
    void SetPDGCode(G4int id)
      {fPDG = id;}
	  void SetTrackID(G4int i)
      {fTrackID=i;}
   
    G4double GetEnergy()
      {return fEnergy;}
    G4double GetGlobalTime() 
      {return fGlobalTime;}
    G4int GetPDGCode() 
      {return fPDG;}
  	G4int GetTrackID()
    {return fTrackID;}    
  };

  typedef G4THitsCollection < NeuDetectorHit >
      NeuDetectorHitsCollection;

  extern G4Allocator < NeuDetectorHit >
      NeuDetectorHitAllocator;

  inline void* NeuDetectorHit::operator  new(size_t)
  {
     void *aHit;
     aHit = (void *) NeuDetectorHitAllocator.MallocSingle();
     return aHit;
  }


  inline void NeuDetectorHit::operator  delete(void *aHit)
  {
     NeuDetectorHitAllocator.
         FreeSingle((NeuDetectorHit *) aHit);
  }

}

#endif


