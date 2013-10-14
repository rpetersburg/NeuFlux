#include "NeuDetectorHit.hh"

#include "G4UnitsTable.hh"
#include "G4VVisManager.hh"
#include "G4Circle.hh"
#include "G4Colour.hh"
#include "G4VisAttributes.hh"

G4Allocator < NeuFlux::NeuDetectorHit > NeuFlux::NeuDetectorHitAllocator;

NeuFlux::NeuDetectorHit::NeuDetectorHit()
{
}

NeuFlux::NeuDetectorHit::~NeuDetectorHit()
{
}

NeuFlux::NeuDetectorHit::NeuDetectorHit(const NeuDetectorHit& /*right*/) : G4VHit()
{
}

const NeuFlux::NeuDetectorHit& NeuFlux::NeuDetectorHit::operator=(const NeuFlux::NeuDetectorHit& /*right*/)
{
   return *this;
}

G4int NeuFlux::NeuDetectorHit::operator==(const NeuDetectorHit& /*right*/) const
{
   return 1;
}
