#include "NeuDetectorHit.hh"
#include "G4UnitsTable.hh"
#include "G4VVisManager.hh"
#include "G4Circle.hh"
#include "G4Colour.hh"
#include "G4VisAttributes.hh"

G4Allocator < NeuDetectorHit > NeuDetectorHitAllocator;

NeuDetectorHit::NeuDetectorHit()
{
}

NeuDetectorHit::~NeuDetectorHit()
{
}

NeuDetectorHit::
NeuDetectorHit(const NeuDetectorHit & right)
:G4VHit()
{
   fPanelID = right.fPanelID;
   edep = right.edep;
   globaltime = right.globaltime;
   pdg = right.pdg;
   nonionenergy = right.nonionenergy;

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

const NeuDetectorHit & NeuDetectorHit::
operator=(const NeuDetectorHit & right)
{
   fPanelID = right.fPanelID;
   edep = right.edep;
   globaltime = right.globaltime;
   pdg = right.pdg;
   nonionenergy = right.nonionenergy;

   return *this;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4int NeuDetectorHit::
operator==(const NeuDetectorHit & right) const
{
   return (this == &right) ? 1 : 0;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void NeuDetectorHit::Draw()
{
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void NeuDetectorHit::Print()
{
   G4cout << "  time: " << globaltime
       << "  energy deposit: " << G4BestUnit(edep, "Energy") << G4endl;

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
