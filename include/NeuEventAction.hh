/*!
  \class NeuEventActions
  
  \ingroup NeuFlux
  
  \brief Defines User Beginning of Event and End of Event actions.
  
      Primarily designed to modify and update the current
      "IncidentParticleType" which characterizes the primary vertex.
      This includes:
      1. PDG code
      2. TrackID
      3. ParentID
      4. PrimaryParentPDG
      5. CreatorProcess
      6. Vertex Volume
      7. Vertex Energy
      8. Vertex Position
  	   9. Incident Position
  	   10. Incident Momentum
  	   11. Dot Product Incident(Position Momentum)
  	   12. Incident Energy
  	   13. Time.
  
  	Also provides arrays for holding IncidentParticlesTypes for holding
  	particles in the various "stored trajectory" areas of the geometry..
  
  	These events are updated by the NeuSteppingAction.
  
  	I should consider changing this over to vectors.
  	Also, I should consider switching this over to a linked tree like structure.
  
  \author Kevin Wierman
  \author Michelle Leber
  
  \version $Revision: 1.5 $
  
  \date $Date: Tue Nov 20 12::33:51 2012 $
  
  Contact: kwierman@email.unc.edu
  
  Created on: Wed Apr 1 18:39:37 2005
  
 */

#ifndef NeuEventAction_hh_
#define NeuEventAction_hh_

#include "G4UserEventAction.hh"
#include "globals.hh"
#include "G4ThreeVector.hh"
#include "G4Event.hh"

#include "TFile.h"

#include "NeuRunAction.hh"

class NeuEventAction:public G4UserEventAction {

 public:
   NeuEventAction(NeuRunAction *);
   ~NeuEventAction();

 public:
   void BeginOfEventAction(const G4Event *);
   void EndOfEventAction(const G4Event *);

   typedef struct {
      G4int PDG;
      G4int TrackID;
      G4int ParentID;
      G4int PrimaryParentPDG;
      G4int CreatorProcess;
      G4int VertexVolume;
      G4double VertexEnergy;
      G4ThreeVector VertexPosition;
      G4ThreeVector IncidentPosition;
      G4ThreeVector IncidentMomentum;
      G4double DotProductIncPosMom;
      G4double IncidentEnergy;
      G4double Time;
   } IncidentParticleType;

   typedef struct {
      G4int PDG[kMax];
      G4int TrackID[kMax];
      G4int ParentID[kMax];
      G4int PrimaryParentPDG[kMax];
      G4int CreatorProcess[kMax];
      G4int VertexVolume[kMax];
      G4double VertexEnergykeV[kMax];
      G4double VertexPositionXcm[kMax];
      G4double VertexPositionYcm[kMax];
      G4double VertexPositionZcm[kMax];
      G4double IncidentPositionXcm[kMax];
      G4double IncidentPositionYcm[kMax];
      G4double IncidentPositionZcm[kMax];
      G4double IncidentMomentumX[kMax];
      G4double IncidentMomentumY[kMax];
      G4double IncidentMomentumZ[kMax];
      G4double DotProductIncPosMom[kMax];
      G4double IncidentEnergykeV[kMax];
      G4double Timens[kMax];
   } IncidentParticlesArray;


// These are for decay chain to identify the parent 
   void SetTopTrackID(G4int id) {
      fTopTrackID = id;
   };
   G4int GetTopTrackID() {
      return fTopTrackID;
   };

 public:

   // initial condition arrays
   void SetNInitial(G4int ngen) {
      fNIni = ngen;
      if (fNIni > kIMax) {
         G4cout << G4endl << " *** error: Initial arrays too small! *** "
             << G4endl;
         G4cout << "Number of particles " << fNIni << G4endl;
      }
   };
   void SetInitialEnergy(G4double initen, G4int i) {
      fIniEnergy[i] = initen / keV;
   };

   void SetInitialPlanePosition(G4ThreeVector inipos) {
      fIniPlanePositionX = inipos.x() / cm;
      fIniPlanePositionY = inipos.y() / cm;
      fIniPlanePositionZ = inipos.z() / cm;
   };

   void SetInitialPosition(G4ThreeVector inipos) {
      fIniPositionX = inipos.x() / cm;
      fIniPositionY = inipos.y() / cm;
      fIniPositionZ = inipos.z() / cm;
   };

   void SetInitialMomDir(G4ThreeVector mom, G4int i) {
      fIniMomX[i] = mom.x();
      fIniMomY[i] = mom.y();
      fIniMomZ[i] = mom.z();
   };

   void SetMomTheta(G4double momthet, G4int i) {
      fIniMomTheta[i] = momthet;
   };

   void SetMomPhi(G4double momp, G4int i) {
      fIniMomPhi[i] = momp;
   };

   void SetDotProduct(G4double dotpr, G4int i) {
      fIniDotProduct[i] = dotpr;
   };

   void SetParentElement(G4int id) {
      fIniParentElement = id;
   };

   void SetInitialPDG(G4int pdgcode, G4int i) {
      fIniPDG[i] = pdgcode;
   };

   void SetSpectrum(G4String val) {
      fSpctrmFlag = val;
   }
   //detector arrays
   void AddDetPart(G4int nDetP) {
      fNDet += nDetP;
      if (fNDet >= kMax) {
         G4cout << G4endl << " *** error: Detector arrays too small! *** "
             << G4endl;
         G4cout << "Number of particles " << fNDet << G4endl;
         fNDet = kMax - 1;      //to prevent exceeding size of array
      }
   };
   void SetDetIncidentParticle(G4int evntID,
                               IncidentParticleType & incidentParticle) {
      fDetIncidentParticle.PDG[evntID] = incidentParticle.PDG;
      fDetIncidentParticle.TrackID[evntID] = incidentParticle.TrackID;
      fDetIncidentParticle.ParentID[evntID] = incidentParticle.ParentID;
      fDetIncidentParticle.PrimaryParentPDG[evntID] =
          incidentParticle.PrimaryParentPDG;
      fDetIncidentParticle.CreatorProcess[evntID] =
          incidentParticle.CreatorProcess;
      fDetIncidentParticle.VertexVolume[evntID] =
          incidentParticle.VertexVolume;
      fDetIncidentParticle.VertexEnergykeV[evntID] =
          incidentParticle.VertexEnergy / keV;
      fDetIncidentParticle.VertexPositionXcm[evntID] =
          incidentParticle.VertexPosition.x() / cm;
      fDetIncidentParticle.VertexPositionYcm[evntID] =
          incidentParticle.VertexPosition.y() / cm;
      fDetIncidentParticle.VertexPositionZcm[evntID] =
          incidentParticle.VertexPosition.z() / cm;
      fDetIncidentParticle.IncidentPositionXcm[evntID] =
          incidentParticle.IncidentPosition.x() / cm;
      fDetIncidentParticle.IncidentPositionYcm[evntID] =
          incidentParticle.IncidentPosition.y() / cm;
      fDetIncidentParticle.IncidentPositionZcm[evntID] =
          incidentParticle.IncidentPosition.z() / cm;
      fDetIncidentParticle.IncidentMomentumX[evntID] =
          incidentParticle.IncidentMomentum.x();
      fDetIncidentParticle.IncidentMomentumY[evntID] =
          incidentParticle.IncidentMomentum.y();
      fDetIncidentParticle.IncidentMomentumZ[evntID] =
          incidentParticle.IncidentMomentum.z();
      fDetIncidentParticle.DotProductIncPosMom[evntID] =
          incidentParticle.DotProductIncPosMom;
      fDetIncidentParticle.IncidentEnergykeV[evntID] =
          incidentParticle.IncidentEnergy / keV;
      fDetIncidentParticle.Timens[evntID] = incidentParticle.Time / ns;
   };

   void AddScintPart(G4int nScintP) {
      fNScint += nScintP;
      if (fNScint >= kMax) {
         G4cout << G4endl <<
             " *** error: Scintillator Pointer arrays too small! *** " <<
             G4endl;
         G4cout << "Number of particles " << fNScint << G4endl;
         fNScint = kMax - 1;    //to prevent exceeding size of array
      }
   };

   void SetScintIncidentParticle(G4int evntID,
                                 IncidentParticleType & incidentParticle) {
      fScintIncidentParticle.PDG[evntID] = incidentParticle.PDG;
      fScintIncidentParticle.TrackID[evntID] = incidentParticle.TrackID;
      fScintIncidentParticle.ParentID[evntID] = incidentParticle.ParentID;
      fScintIncidentParticle.PrimaryParentPDG[evntID] =
          incidentParticle.PrimaryParentPDG;
      fScintIncidentParticle.CreatorProcess[evntID] =
          incidentParticle.CreatorProcess;
      fScintIncidentParticle.VertexVolume[evntID] =
          incidentParticle.VertexVolume;
      fScintIncidentParticle.VertexEnergykeV[evntID] =
          incidentParticle.VertexEnergy / keV;
      fScintIncidentParticle.VertexPositionXcm[evntID] =
          incidentParticle.VertexPosition.x() / cm;
      fScintIncidentParticle.VertexPositionYcm[evntID] =
          incidentParticle.VertexPosition.y() / cm;
      fScintIncidentParticle.VertexPositionZcm[evntID] =
          incidentParticle.VertexPosition.z() / cm;
      fScintIncidentParticle.IncidentPositionXcm[evntID] =
          incidentParticle.IncidentPosition.x() / cm;
      fScintIncidentParticle.IncidentPositionYcm[evntID] =
          incidentParticle.IncidentPosition.y() / cm;
      fScintIncidentParticle.IncidentPositionZcm[evntID] =
          incidentParticle.IncidentPosition.z() / cm;
      fScintIncidentParticle.IncidentMomentumX[evntID] =
          incidentParticle.IncidentMomentum.x();
      fScintIncidentParticle.IncidentMomentumY[evntID] =
          incidentParticle.IncidentMomentum.y();
      fScintIncidentParticle.IncidentMomentumZ[evntID] =
          incidentParticle.IncidentMomentum.z();
      fScintIncidentParticle.DotProductIncPosMom[evntID] =
          incidentParticle.DotProductIncPosMom;
      fScintIncidentParticle.IncidentEnergykeV[evntID] =
          incidentParticle.IncidentEnergy / keV;
      fScintIncidentParticle.Timens[evntID] = incidentParticle.Time / ns;
   };
   void SetScintLastTrackID(G4int tid) {
      fScintLastTrackID = tid;
   };

   // Air arrays 
   void AddAirPart(G4int nAirP) {
      fNAir += nAirP;
      if (fNAir >= kMax) {
         G4cout << G4endl << " *** error: Air arrays too small! *** " <<
             G4endl;
         G4cout << "Number of particles " << fNAir << G4endl;
         fNAir = kMax - 1;      //to prevent exceeding size of array
      }
   };
   void SetAirIncidentParticle(G4int evntID,
                               IncidentParticleType & incidentParticle) {
      fAirIncidentParticle.PDG[evntID] = incidentParticle.PDG;
      fAirIncidentParticle.TrackID[evntID] = incidentParticle.TrackID;
      fAirIncidentParticle.ParentID[evntID] = incidentParticle.ParentID;
      fAirIncidentParticle.PrimaryParentPDG[evntID] =
          incidentParticle.PrimaryParentPDG;
      fAirIncidentParticle.CreatorProcess[evntID] =
          incidentParticle.CreatorProcess;
      fAirIncidentParticle.VertexVolume[evntID] =
          incidentParticle.VertexVolume;
      fAirIncidentParticle.VertexEnergykeV[evntID] =
          incidentParticle.VertexEnergy / keV;
      fAirIncidentParticle.VertexPositionXcm[evntID] =
          incidentParticle.VertexPosition.x() / cm;
      fAirIncidentParticle.VertexPositionYcm[evntID] =
          incidentParticle.VertexPosition.y() / cm;
      fAirIncidentParticle.VertexPositionZcm[evntID] =
          incidentParticle.VertexPosition.z() / cm;
      fAirIncidentParticle.IncidentPositionXcm[evntID] =
          incidentParticle.IncidentPosition.x() / cm;
      fAirIncidentParticle.IncidentPositionYcm[evntID] =
          incidentParticle.IncidentPosition.y() / cm;
      fAirIncidentParticle.IncidentPositionZcm[evntID] =
          incidentParticle.IncidentPosition.z() / cm;
      fAirIncidentParticle.IncidentMomentumX[evntID] =
          incidentParticle.IncidentMomentum.x();
      fAirIncidentParticle.IncidentMomentumY[evntID] =
          incidentParticle.IncidentMomentum.y();
      fAirIncidentParticle.IncidentMomentumZ[evntID] =
          incidentParticle.IncidentMomentum.z();
      fAirIncidentParticle.DotProductIncPosMom[evntID] =
          incidentParticle.DotProductIncPosMom;
      fAirIncidentParticle.IncidentEnergykeV[evntID] =
          incidentParticle.IncidentEnergy / keV;
      fAirIncidentParticle.Timens[evntID] = incidentParticle.Time / ns;
   };
   void SetAirLastTrackID(G4int tid) {
      fAirLastTrackID = tid;
   };
   // OShield arrays 
   void AddOShieldPart(G4int nOShieldP) {
      fNOShield += nOShieldP;
      if (fNOShield >= kMax) {
         G4cout << G4endl << " *** error: OShield arrays too small! *** " <<
			G4endl;
         G4cout << "Number of particles " << fNOShield << G4endl;
         fNOShield = kMax - 1;      //to prevent exceeding size of array
      }
   };
   void SetOShieldIncidentParticle(G4int evntID,
                               IncidentParticleType & incidentParticle) {
      fOShieldIncidentParticle.PDG[evntID] = incidentParticle.PDG;
      fOShieldIncidentParticle.TrackID[evntID] = incidentParticle.TrackID;
      fOShieldIncidentParticle.ParentID[evntID] = incidentParticle.ParentID;
      fOShieldIncidentParticle.PrimaryParentPDG[evntID] =
			incidentParticle.PrimaryParentPDG;
      fOShieldIncidentParticle.CreatorProcess[evntID] =
			incidentParticle.CreatorProcess;
      fOShieldIncidentParticle.VertexVolume[evntID] =
			incidentParticle.VertexVolume;
      fOShieldIncidentParticle.VertexEnergykeV[evntID] =
			incidentParticle.VertexEnergy / keV;
      fOShieldIncidentParticle.VertexPositionXcm[evntID] =
			incidentParticle.VertexPosition.x() / cm;
      fOShieldIncidentParticle.VertexPositionYcm[evntID] =
			incidentParticle.VertexPosition.y() / cm;
      fOShieldIncidentParticle.VertexPositionZcm[evntID] =
			incidentParticle.VertexPosition.z() / cm;
      fOShieldIncidentParticle.IncidentPositionXcm[evntID] =
			incidentParticle.IncidentPosition.x() / cm;
      fOShieldIncidentParticle.IncidentPositionYcm[evntID] =
			incidentParticle.IncidentPosition.y() / cm;
      fOShieldIncidentParticle.IncidentPositionZcm[evntID] =
			incidentParticle.IncidentPosition.z() / cm;
      fOShieldIncidentParticle.IncidentMomentumX[evntID] =
			incidentParticle.IncidentMomentum.x();
      fOShieldIncidentParticle.IncidentMomentumY[evntID] =
			incidentParticle.IncidentMomentum.y();
      fOShieldIncidentParticle.IncidentMomentumZ[evntID] =
			incidentParticle.IncidentMomentum.z();
      fOShieldIncidentParticle.DotProductIncPosMom[evntID] =
			incidentParticle.DotProductIncPosMom;
      fOShieldIncidentParticle.IncidentEnergykeV[evntID] =
			incidentParticle.IncidentEnergy / keV;
      fOShieldIncidentParticle.Timens[evntID] = incidentParticle.Time / ns;
   };
   void SetOShieldLastTrackID(G4int tid) {
      fOShieldLastTrackID = tid;
   };
	
   // Det Vacuum arrays 
   void AddDetVacPart(G4int nDetVacP) {
      fNDetVac += nDetVacP;
      if (fNDetVac >= kMax) {
         G4cout << G4endl << " *** error: DetVac arrays too small! *** " <<
             G4endl;
         G4cout << "Number of particles " << fNDetVac << G4endl;
         fNDetVac = kMax - 1;   //to prevent exceeding size of array
      }
   };
   void SetDetVacIncidentParticle(G4int evntID,
                                  IncidentParticleType & incidentParticle)
   {
      fDetVacIncidentParticle.PDG[evntID] = incidentParticle.PDG;
      fDetVacIncidentParticle.TrackID[evntID] = incidentParticle.TrackID;
      fDetVacIncidentParticle.ParentID[evntID] = incidentParticle.ParentID;
      fDetVacIncidentParticle.PrimaryParentPDG[evntID] =
          incidentParticle.PrimaryParentPDG;
      fDetVacIncidentParticle.CreatorProcess[evntID] =
          incidentParticle.CreatorProcess;
      fDetVacIncidentParticle.VertexVolume[evntID] =
          incidentParticle.VertexVolume;
      fDetVacIncidentParticle.VertexEnergykeV[evntID] =
          incidentParticle.VertexEnergy / keV;
      fDetVacIncidentParticle.VertexPositionXcm[evntID] =
          incidentParticle.VertexPosition.x() / cm;
      fDetVacIncidentParticle.VertexPositionYcm[evntID] =
          incidentParticle.VertexPosition.y() / cm;
      fDetVacIncidentParticle.VertexPositionZcm[evntID] =
          incidentParticle.VertexPosition.z() / cm;
      fDetVacIncidentParticle.IncidentPositionXcm[evntID] =
          incidentParticle.IncidentPosition.x() / cm;
      fDetVacIncidentParticle.IncidentPositionYcm[evntID] =
          incidentParticle.IncidentPosition.y() / cm;
      fDetVacIncidentParticle.IncidentPositionZcm[evntID] =
          incidentParticle.IncidentPosition.z() / cm;
      fDetVacIncidentParticle.IncidentMomentumX[evntID] =
          incidentParticle.IncidentMomentum.x();
      fDetVacIncidentParticle.IncidentMomentumY[evntID] =
          incidentParticle.IncidentMomentum.y();
      fDetVacIncidentParticle.IncidentMomentumZ[evntID] =
          incidentParticle.IncidentMomentum.z();
      fDetVacIncidentParticle.DotProductIncPosMom[evntID] =
          incidentParticle.DotProductIncPosMom;
      fDetVacIncidentParticle.IncidentEnergykeV[evntID] =
          incidentParticle.IncidentEnergy / keV;
      fDetVacIncidentParticle.Timens[evntID] = incidentParticle.Time / ns;
   };
   void SetDVLastTrackID(G4int tid) {
      fDVLastTrackID = tid;
   };

   // decay arrays
   void AddDecayPart(G4int nDecayP) {
      fNDecay += nDecayP;
      if (fNDecay >= kMax) {
         G4cout << G4endl << " *** error: Decay arrays too small! *** " <<
             G4endl;
         G4cout << "Number of particles " << fNDecay << G4endl;
         fNDecay = kMax - 1;
      }
   };
   void SetDecayIncidentParticle(G4int evntID,
                                 IncidentParticleType & incidentParticle) {
      fDecayIncidentParticle.PDG[evntID] = incidentParticle.PDG;
      fDecayIncidentParticle.TrackID[evntID] = incidentParticle.TrackID;
      fDecayIncidentParticle.ParentID[evntID] = incidentParticle.ParentID;
      fDecayIncidentParticle.PrimaryParentPDG[evntID] =
          incidentParticle.PrimaryParentPDG;
      fDecayIncidentParticle.CreatorProcess[evntID] =
          incidentParticle.CreatorProcess;
      fDecayIncidentParticle.VertexVolume[evntID] =
          incidentParticle.VertexVolume;
      fDecayIncidentParticle.VertexEnergykeV[evntID] =
          incidentParticle.VertexEnergy / keV;
      fDecayIncidentParticle.VertexPositionXcm[evntID] =
          incidentParticle.VertexPosition.x() / cm;
      fDecayIncidentParticle.VertexPositionYcm[evntID] =
          incidentParticle.VertexPosition.y() / cm;
      fDecayIncidentParticle.VertexPositionZcm[evntID] =
          incidentParticle.VertexPosition.z() / cm;
      fDecayIncidentParticle.IncidentPositionXcm[evntID] =
          incidentParticle.IncidentPosition.x() / cm;
      fDecayIncidentParticle.IncidentPositionYcm[evntID] =
          incidentParticle.IncidentPosition.y() / cm;
      fDecayIncidentParticle.IncidentPositionZcm[evntID] =
          incidentParticle.IncidentPosition.z() / cm;
      fDecayIncidentParticle.IncidentMomentumX[evntID] =
          incidentParticle.IncidentMomentum.x();
      fDecayIncidentParticle.IncidentMomentumY[evntID] =
          incidentParticle.IncidentMomentum.y();
      fDecayIncidentParticle.IncidentMomentumZ[evntID] =
          incidentParticle.IncidentMomentum.z();
      fDecayIncidentParticle.DotProductIncPosMom[evntID] =
          incidentParticle.DotProductIncPosMom;
      fDecayIncidentParticle.IncidentEnergykeV[evntID] =
          incidentParticle.IncidentEnergy / keV;
      fDecayIncidentParticle.Timens[evntID] = incidentParticle.Time / ns;
   };

   // Killed arrays
   void AddKilledPart(G4int nKilledP) {
      fNKilled += nKilledP;
      if (fNKilled >= kMax) {
         G4cout << G4endl << " *** error: Killed arrays too small! *** " <<
         G4endl;
         G4cout << "Number of particles " << fNKilled << G4endl;
         fNKilled = kMax - 1;
      }
   };
   void SetKilledIncidentParticle(G4int evntID,
                                 IncidentParticleType & incidentParticle) {
      fKilledIncidentParticle.PDG[evntID] = incidentParticle.PDG;
      fKilledIncidentParticle.TrackID[evntID] = incidentParticle.TrackID;
      fKilledIncidentParticle.ParentID[evntID] = incidentParticle.ParentID;
      fKilledIncidentParticle.PrimaryParentPDG[evntID] =
      incidentParticle.PrimaryParentPDG;
      fKilledIncidentParticle.CreatorProcess[evntID] =
      incidentParticle.CreatorProcess;
      fKilledIncidentParticle.VertexVolume[evntID] =
      incidentParticle.VertexVolume;
      fKilledIncidentParticle.VertexEnergykeV[evntID] =
      incidentParticle.VertexEnergy / keV;
      fKilledIncidentParticle.VertexPositionXcm[evntID] =
      incidentParticle.VertexPosition.x() / cm;
      fKilledIncidentParticle.VertexPositionYcm[evntID] =
      incidentParticle.VertexPosition.y() / cm;
      fKilledIncidentParticle.VertexPositionZcm[evntID] =
      incidentParticle.VertexPosition.z() / cm;
      fKilledIncidentParticle.IncidentPositionXcm[evntID] =
      incidentParticle.IncidentPosition.x() / cm;
      fKilledIncidentParticle.IncidentPositionYcm[evntID] =
      incidentParticle.IncidentPosition.y() / cm;
      fKilledIncidentParticle.IncidentPositionZcm[evntID] =
      incidentParticle.IncidentPosition.z() / cm;
      fKilledIncidentParticle.IncidentMomentumX[evntID] =
      incidentParticle.IncidentMomentum.x();
      fKilledIncidentParticle.IncidentMomentumY[evntID] =
      incidentParticle.IncidentMomentum.y();
      fKilledIncidentParticle.IncidentMomentumZ[evntID] =
      incidentParticle.IncidentMomentum.z();
      fKilledIncidentParticle.DotProductIncPosMom[evntID] =
      incidentParticle.DotProductIncPosMom;
      fKilledIncidentParticle.IncidentEnergykeV[evntID] =
      incidentParticle.IncidentEnergy / keV;
      fKilledIncidentParticle.Timens[evntID] = incidentParticle.Time / ns;
   };
   
//Get methods
   Int_t *GetEvent() {
      return &fEvent;
   };
   // initial condition arrays
   Int_t *GetNInitial() {
      return &fNIni;
   };
   G4double *GetInitialEnergy() {
      return fIniEnergy;
   };
   Double_t *GetInitialPlanePositionX() {
      return &fIniPlanePositionX;
   };
   Double_t *GetInitialPlanePositionY() {
      return &fIniPlanePositionY;
   };
   Double_t *GetInitialPlanePositionZ() {
      return &fIniPlanePositionZ;
   };
   Double_t *GetInitialPositionX() {
      return &fIniPositionX;
   };
   Double_t *GetInitialPositionY() {
      return &fIniPositionY;
   };
   Double_t *GetInitialPositionZ() {
      return &fIniPositionZ;
   };
   Double_t *GetInitialMomDirX() {
      return fIniMomX;
   };
   Double_t *GetInitialMomDirY() {
      return fIniMomY;
   };
   Double_t *GetInitialMomDirZ() {
      return fIniMomZ;
   };
   Double_t *GetMomTheta() {
      return fIniMomTheta;
   };
   Double_t *GetMomPhi() {
      return fIniMomPhi;
   };
   Double_t *GetDotProduct() {
      return fIniDotProduct;
   };
   Int_t *GetParentElement() {
      return &fIniParentElement;
   };
   Int_t *GetInitialPDG() {
      return fIniPDG;
   };

   G4String *GetSpectrum() {
      return &fSpctrmFlag;
   }
   //Detector arrays
   Int_t *GetNDet() {
      return &fNDet;
   };
   IncidentParticlesArray *GetDetIncidentParticles() {
      return &fDetIncidentParticle;
   };
   //scintillator arrays
   Int_t *GetNScint() {
      return &fNScint;
   };
   IncidentParticlesArray *GetScintIncidentParticles() {
      return &fScintIncidentParticle;
   };
   G4int GetScintLastTrackID() {
      return fScintLastTrackID;
   };

   // Air arrays 
   Int_t *GetNAir() {
      return &fNAir;
   };
   IncidentParticlesArray *GetAirIncidentParticles() {
      return &fAirIncidentParticle;
   };
   G4int GetAirLastTrackID() {
      return fAirLastTrackID;
   };
	
   // OShield arrays 
   Int_t *GetNOShield() {
      return &fNOShield;
   };
   IncidentParticlesArray *GetOShieldIncidentParticles() {
      return &fOShieldIncidentParticle;
   };
   G4int GetOShieldLastTrackID() {
      return fOShieldLastTrackID;
   };
	
	
   // DetVac arrays 
   Int_t *GetNDetVac() {
      return &fNDetVac;
   };
   IncidentParticlesArray *GetDetVacIncidentParticles() {
      return &fDetVacIncidentParticle;
   };
   G4int GetDVLastTrackID() {
      return fDVLastTrackID;
   };

   // Decay arrays 
   Int_t *GetNDecay() {
      return &fNDecay;
   };
   IncidentParticlesArray *GetDecayIncidentParticles() {
      return &fDecayIncidentParticle;
   };
   // Killed arrays 
   Int_t *GetNKilled() {
      return &fNKilled;
   };
   IncidentParticlesArray *GetKilledIncidentParticles() {
      return &fKilledIncidentParticle;
   };
   

 private:
   Int_t fEvent;
   G4String fSpctrmFlag;

   // initial condition arrays
   Int_t fNIni;
   Double_t fIniEnergy[kIMax];
   Double_t fIniMomPhi[kIMax];
   Double_t fIniMomTheta[kIMax];
   Int_t fIniPDG[kIMax];
   Double_t fIniDotProduct[kIMax];
   Double_t fIniMomX[kIMax];
   Double_t fIniMomY[kIMax];
   Double_t fIniMomZ[kIMax];
   Double_t fIniPlanePositionX;
   Double_t fIniPlanePositionY;
   Double_t fIniPlanePositionZ;
   Double_t fIniPositionX;
   Double_t fIniPositionY;
   Double_t fIniPositionZ;
   Int_t fIniParentElement;

   // Detector arrays
   Int_t fNDet;
   IncidentParticlesArray fDetIncidentParticle;
   // scintillator arrays
   Int_t fNScint;
   IncidentParticlesArray fScintIncidentParticle;
   G4int fScintLastTrackID;
   // Air arrays
   Int_t fNAir;
   IncidentParticlesArray fAirIncidentParticle;
   G4int fAirLastTrackID;
   // OShield arrays
   Int_t fNOShield;
   IncidentParticlesArray fOShieldIncidentParticle;
   G4int fOShieldLastTrackID;
   // DetVac arrays
   Int_t fNDetVac;
   G4int fDVLastTrackID;
   IncidentParticlesArray fDetVacIncidentParticle;

   // Decay arrays
   Int_t fNDecay;
   IncidentParticlesArray fDecayIncidentParticle;
   // Killed arrays
   Int_t fNKilled;
   IncidentParticlesArray fKilledIncidentParticle;
   Int_t fNPairs;

 private:
   NeuRunAction * theRun;
   G4int fTopTrackID;
};

#endif
