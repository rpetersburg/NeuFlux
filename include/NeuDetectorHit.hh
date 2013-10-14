
#ifndef NeuDetectorHit_hh_
#define NeuDetectorHit_hh_

#include "G4VHit.hh"
#include "G4THitsCollection.hh"
#include "G4Allocator.hh"
#include "G4ThreeVector.hh"

namespace NeuFlux
{
  /*!
    \class NeuDetectorHit
    
    \ingroup NeuFlux
    
    \brief Container class for Detector Hits
    
    
    \author Kevin Wierman
    
    \version 1.0
    
    \date Oct 1, 2013
    
    \contact kwierman@email.unc.edu
    
  */
  class NeuDetectorHit : public G4VHit {
  private:
    /*
    G4double fEnergy;
    G4double fGlobalTime;
    G4int fPDG;
    G4int fTrackID;
    */

  public:

    NeuDetectorHit();
    ~NeuDetectorHit();
    NeuDetectorHit(const NeuDetectorHit &);
    const NeuDetectorHit & operator=(const NeuDetectorHit &);
    G4int operator==(const NeuDetectorHit &) const;

    inline void* operator  new(size_t);
    inline void operator  delete(void *);
  public:
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


