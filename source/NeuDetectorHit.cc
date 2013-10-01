#include "NeuDetectorHit.hh"
#include "G4UnitsTable.hh"
#include "G4VVisManager.hh"
#include "G4Circle.hh"
#include "G4Colour.hh"
#include "G4VisAttributes.hh"

G4Allocator < NeuDetectorHit > NeuDetectorHitAllocator;

NeuFlux::NeuDetectorHit::NeuDetectorHit()
{
}

NeuFlux::NeuDetectorHit::~NeuDetectorHit()
{
}

NeuDetectorHit::NeuDetectorHit(const NeuDetectorHit & right) : G4VHit(), fEnergy(right.fEnergy), fGlobalTime(right.fGlobalTime), fPDG(right.fPDG), fTrackID(right.fPDG)
{
}

const NeuFlux::NeuDetectorHit & NeuFlux::NeuDetectorHit::operator=(const NeuFlux::NeuDetectorHit & right)
{
   fEnergy = right.fEnergy;
   fGlobalTime = right.fGlobalTime;
   fPDG = right.fPDG;
   fTrackID = right.fPDG;
   return *this;
}

G4int NeuFlux::NeuDetectorHit::operator==(const NeuDetectorHit & right) const
{
   if(fTrackID == right.fTrackID)
      if(fEnergy == right.fEnergy)
         if(fGlobalTime == right.fGlobalTime)
            if(fPDG == right.fPDG)
               return 1;
   return 0;

}

void NeuFlux::NeuDetectorHit::Draw()
{
}


void NeuFlux::NeuDetectorHit::Print()
{
   G4cout << "  time: " << fGlobalTime
       << "  energy deposit: " << G4BestUnit(fEnergy, "Energy") << G4endl;
}
