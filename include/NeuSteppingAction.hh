/**
 * \class KDSSteppingAction
 *
 * \ingroup KDS
 *
 * \brief Defines information to be updated during stepping.
 *
 * At each step, this is called to update the information on the event and
 * the track.
 *
 * \note See KDSEventAction for which information is available to access.
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

#ifndef KDSSteppingAction_h
#define KDSSteppingAction_h 1


///     Geant4 package includes
#include "G4UserSteppingAction.hh"
#include "G4UserEventAction.hh"
#include "G4Track.hh"
#include "globals.hh"


class KDSEventAction;
class KDSTrackingAction;
class KDSDetectorConstruction;

class KDSSteppingAction:public G4UserSteppingAction {

 public:
   KDSSteppingAction(KDSEventAction *,
                               KDSTrackingAction *,
                               KDSDetectorConstruction *);
   ~KDSSteppingAction();

   void UserSteppingAction(const G4Step * theStep);

 private:
   KDSEventAction * theEventAct;
   KDSTrackingAction *theTrackAct;
   KDSDetectorConstruction *theDet;

   const G4Track *theTrack;
   G4VPhysicalVolume *preVolume;
   G4VPhysicalVolume *postVolume;
   const G4LogicalVolume *vertexLogicalVolume;
   G4double edep;
   G4int processType;
   G4int trackID;
   G4int parentID;
   G4int PDG;
   G4double KE;
   G4double time;
   G4ThreeVector incidentPosition;
   G4ThreeVector incidentMomentum;

   KDSEventAction::IncidentParticleType incidentParticle;
   G4int volumeIndex;

   void SetEnteringParticleInfo();

};

#endif
