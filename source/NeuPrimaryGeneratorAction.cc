#include "NeuPrimaryGeneratorAction.hh"
#include "NeuEventAction.hh"


#include "G4Event.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "globals.hh"
#include "G4UImanager.hh"

#include "TMath.h"
#include "TRandom3.h"


NeuFlux::NeuPrimaryGeneratorAction::NeuPrimaryGeneratorAction(NeuFlux::NeuEventAction * theEA)
:  theEvent(theEA), spctrmFlag("ParticleGun"), isoFlag("U238Cal"),
energyFlag("All")
{
   G4int n_particle = 1;
   theParticleGun = new G4ParticleGun(n_particle);
   
   theCurrentGun = theParticleGun;
   
   //Flux = &NeuPrimaryGeneratorAction::CurrentGenerator;
   theEvent->SetSpectrum(spctrmFlag);
   // default particle
   G4ParticleTable *particleTable = G4ParticleTable::GetParticleTable();
   G4ParticleDefinition *particle = particleTable->FindParticle("e-");
   theCurrentGun->SetParticleDefinition(particle);

   //other guns, can be chosen with /Katrin/gun/Spectrum
   theCosmicRayGun = new CosmicRayGun();
   theRoomRadiationGun = new RoomRadiationGun();
   theGPSGun = new G4GeneralParticleSource();
   theBeamGun = new KatrinBeamGun();
   PlanePos = &NeuPrimaryGeneratorAction::CosmicPlanePosition;
	//actually uses the GPS, but this sets energy
   theCalibrationGenerator = new CalibrationGenerator();

   //for radioactive decay
   uchain = new DecayChain();

	//for random numbers
   //setting seed to 0 means using a TUUID to set the seed
	r3 = new TRandom3(0);
   
   
}
NeuFlux::NeuPrimaryGeneratorAction::~NeuPrimaryGeneratorAction()
{
   delete theParticleGun;
   delete theGPSGun;
   delete theBeamGun;
   delete theCosmicRayGun;
   delete theRoomRadiationGun;
   delete uchain;
	delete r3;
}

void NeuFlux::NeuPrimaryGeneratorAction::GeneratePrimaries(G4Event *
                                                            anEvent)
{
   (this->*Flux) (anEvent);

}
void NeuFlux::NeuPrimaryGeneratorAction::CurrentGenerator(G4Event *
                                                           anEvent)
{
   //using particle gun UI to set particle type
   theCurrentGun->SetParticleDefinition(theParticleGun->
                                        GetParticleDefinition());
   //randomization done within this function
   theCurrentGun->GeneratePrimaryVertex(anEvent);
   //store initial values in root file  
   theEvent->SetInitialPDG(theCurrentGun->GetParticleDefinition()->
                           GetPDGEncoding(), 0);
   theEvent->SetNInitial(theCurrentGun->GetNumberOfParticles());
   theEvent->SetInitialEnergy(theCurrentGun->GetParticleEnergy(), 0);
   //Plane Position only meaningful for cosmic rays and room radiation
   theEvent->SetInitialPlanePosition((this->*PlanePos)());
   G4ThreeVector position(theCurrentGun->GetParticlePosition());
   G4ThreeVector mom(theCurrentGun->GetParticleMomentumDirection());
   theEvent->SetInitialPosition(position);
   theEvent->SetInitialMomDir(mom, 0);
   theEvent->SetDotProduct(position.dot(mom) / position.mag() / mom.mag(),
                           0);
   theEvent->SetMomTheta(mom.angle(G4ThreeVector(-1, 0, 0)), 0);
   //theta is angle wrt straight down
   mom.setX(0);
   theEvent->SetMomPhi(mom.angle(G4ThreeVector(0, 1, 0)), 0);
   //phi is angle wrt y-axis (in x-plane)
}

void NeuPrimaryGeneratorAction::GPSGenerator(G4Event * anEvent)
{
   //randomization done within this function
   theGPSGun->GeneratePrimaryVertex(anEvent);

   //store intial values in root file
   G4ThreeVector zero;          //only meaniningfull for cosmic rays
   theEvent->SetInitialPlanePosition(zero);
   G4ThreeVector position(theGPSGun->GetParticlePosition());
   theEvent->SetInitialPosition(position);
   G4int numSource = theGPSGun->GetNumberofSource();
   theEvent->SetNInitial(numSource);
   for (G4int j = 0; j < numSource; j++ ) {
      theGPSGun->SetCurrentSourceto(j);
      theEvent->SetInitialPDG(theGPSGun->GetParticleDefinition()->
                              GetPDGEncoding(), j);
      theEvent->SetInitialEnergy(theGPSGun->GetParticleEnergy(), j);
      G4ThreeVector mom(theGPSGun->GetParticleMomentumDirection());
      theEvent->SetInitialMomDir(mom, j);
      theEvent->SetDotProduct(position.dot(mom) / position.mag(), j);
      theEvent->SetMomTheta(mom.angle(G4ThreeVector(-1, 0, 0)), j);
      //theta is angle wrt straight down
      mom.setX(0);
      theEvent->SetMomPhi(mom.angle(G4ThreeVector(0, 1, 0)), j);
      
   }
}

void NeuPrimaryGeneratorAction::CalGenerator(G4Event * anEvent)
{
	//energy is set by CalibrationGenerator, position, direction set by GPS
	//energy randomization done within this function
   G4double energy = theCalibrationGenerator->GetCalibrationEnergy();
	theGPSGun->GetCurrentSource()->GetEneDist()->SetMonoEnergy(energy);
   //all angles, positions set by UI commands
   theGPSGun->GeneratePrimaryVertex(anEvent);
   //store intial values in root file
   theEvent->SetInitialPDG(theGPSGun->GetParticleDefinition()->
                           GetPDGEncoding(), 0);
   theEvent->SetNInitial(theGPSGun->GetNumberOfParticles());
   theEvent->SetInitialEnergy(theGPSGun->GetParticleEnergy(), 0);
   G4ThreeVector zero;          //only meaniningfull for cosmic rays
   theEvent->SetInitialPlanePosition(zero);
   G4ThreeVector position(theGPSGun->GetParticlePosition());
   G4ThreeVector mom(theGPSGun->GetParticleMomentumDirection());
   theEvent->SetInitialPosition(position);
   theEvent->SetInitialMomDir(mom, 0);
   theEvent->SetDotProduct(position.dot(mom) / position.mag(), 0);
   theEvent->SetMomTheta(mom.angle(G4ThreeVector(-1, 0, 0)), 0);
   //theta is angle wrt straight down
   mom.setX(0);
   theEvent->SetMomPhi(mom.angle(G4ThreeVector(0, 1, 0)), 0);
}

void NeuPrimaryGeneratorAction::DecayFlux(G4Event * anEvent)
{
   if (anEvent->GetEventID() == 0) {
      SetNuclide();
   }
   //-------------- randomizing initial position for event-----------
   G4ThreeVector iniposition(0, 0, 0);
   iniposition = theParticleGun->GetParticlePosition();
   // generating chain
   uchain->GenerateDecayChain();
   G4int n = uchain->GetNGenerated();
   theEvent->SetNInitial(n);
   theEvent->SetParentElement(uchain->GetElementNumber());
   for (G4int i = 0; i < n; i++) {
      //-------------- randomizing direction for each particle-----------
      //theta defined wrt z axiz, unlike other flux methods
      G4double costheta = r3->Rndm();
      G4double mtheta = TMath::ACos(costheta);
//      G4double mtheta = r3->Rndm() * TMath::Pi();
      G4double mphi = r3->Rndm() * 2 * TMath::Pi();
      G4double mx = TMath::Cos(mphi) * TMath::Sin(mtheta);
      G4double my = TMath::Sin(mphi) * TMath::Sin(mtheta);
      G4double mz = TMath::Cos(mtheta);
      G4ThreeVector momdir(mx, my, mz);
      theParticleGun->SetParticleMomentumDirection(momdir);
      theEvent->SetMomTheta(mtheta, i);
      theEvent->SetMomPhi(mphi, i);
      //Is it aimed toward the detector 
      theEvent->SetDotProduct(iniposition.dot(momdir) / iniposition.mag(),
                              i);
      //Set the energy
      G4double InitialEnergy = uchain->GetEventEnergy(i);
      theEvent->SetInitialEnergy(InitialEnergy, i);
      G4double energy = uchain->GetEventEnergy(i);
      theParticleGun->SetParticleEnergy(energy);
      IdentifyParticle(uchain->GetEventID(i), i);
      theParticleGun->GeneratePrimaryVertex(anEvent);
   }
}
void NeuPrimaryGeneratorAction::SetNuclide()
{
   if (spctrmFlag == "232Th" || spctrmFlag == "238U" || spctrmFlag == "241Am") {
      delete uchain;
      char chainType[20];
      strcpy(chainType, spctrmFlag);
      uchain = new DecayChain(chainType);
      uchain->ReadInputFile(uchain->GetChainName());
      G4cout << G4endl << " *** setting the nuclide to " << spctrmFlag 
      << ". *** " << G4endl;
   } else {
      G4cout << G4endl <<
          "------------------ nuclide not found________________ " <<
          G4endl;
   }
}
void NeuPrimaryGeneratorAction::IdentifyParticle(G4int pid,
                                                           G4int i)
{
   if (pid == 0) {
      G4ParticleTable *particleTable = G4ParticleTable::GetParticleTable();
      G4ParticleDefinition *particle =
          particleTable->FindParticle("gamma");
      theEvent->SetInitialPDG(particle->GetPDGEncoding(), i);
      theParticleGun->SetParticleDefinition(particle);
   } else if (pid == 1) {
      G4ParticleTable *particleTable = G4ParticleTable::GetParticleTable();
      G4ParticleDefinition *particle = particleTable->FindParticle("e-");
      theEvent->SetInitialPDG(particle->GetPDGEncoding(), i);
      theParticleGun->SetParticleDefinition(particle);
   } else if (pid == 2) {
      G4ParticleTable *particleTable = G4ParticleTable::GetParticleTable();
      G4ParticleDefinition *particle =
          particleTable->FindParticle("alpha");
      theEvent->SetInitialPDG(particle->GetPDGEncoding(), i);
      theParticleGun->SetParticleDefinition(particle);
   } else {
      G4cout << G4endl << " *** can't find particle " << pid << G4endl;
   }

}
void NeuPrimaryGeneratorAction::SetSpectrumFlag(G4String val)
{
   spctrmFlag = val;
   if (spctrmFlag == "Beam") {
      theCurrentGun = theBeamGun;
      Flux = &NeuPrimaryGeneratorAction::CurrentGenerator;
   } else if (spctrmFlag == "GPS") {
      Flux = &NeuPrimaryGeneratorAction::GPSGenerator;
   } else if (spctrmFlag == "ParticleGun") {
      theCurrentGun = theParticleGun;
      Flux = &NeuPrimaryGeneratorAction::CurrentGenerator;
   } else if (spctrmFlag == "CalGen") {
      Flux = &NeuPrimaryGeneratorAction::CalGenerator;
   } else if ( spctrmFlag == "KRoom" || spctrmFlag == "URoom" 
              || spctrmFlag == "ThRoom") {
/*      Flux = &NeuPrimaryGeneratorAction::CalGenerator;
		theCalibrationGenerator->SetSource(spctrmFlag);
      if ( !theCalibrationGenerator->IsRootFile() )
      {
         spctrmFlag = "U238Cal";
      }*/
      theRoomRadiationGun->SetSpectrumFlag(spctrmFlag);
      theCurrentGun = theRoomRadiationGun;
      Flux = &NeuPrimaryGeneratorAction::CurrentGenerator;
      PlanePos = &NeuPrimaryGeneratorAction::RoomRadiationPlanePosition;
      if ( !theRoomRadiationGun->IsRootFile() )
      {
         spctrmFlag = "CalGen";
         Flux = &NeuPrimaryGeneratorAction::CalGenerator;
         theCalibrationGenerator->SetSource("U238Cal");
      }
      
   } else if (spctrmFlag == "Muon" || spctrmFlag == "Neutron" 
              || spctrmFlag == "Nucleon" || spctrmFlag == "Gamma" ) {
      theCosmicRayGun->SetSpectrumFlag(spctrmFlag);
      theCurrentGun = theCosmicRayGun;
      Flux = &NeuPrimaryGeneratorAction::CurrentGenerator;
      PlanePos = &NeuPrimaryGeneratorAction::CosmicPlanePosition;
   } else if (spctrmFlag == "DecayChain") {
         Flux = &NeuPrimaryGeneratorAction::DecayFlux;
   }
   PrintGunParameters();
   theEvent->SetSpectrum(spctrmFlag);
   //set plane position to zero b/c only meaningful for cosmic rays
   G4ThreeVector zero;
   theCosmicRayGun->SetParticlePlanePosition(zero);

}
void NeuPrimaryGeneratorAction::SetCalIsotope(G4String val)
{
   isoFlag = val;
   SetSpectrumFlag("CalGen");
	theCalibrationGenerator->SetSource(val);
   theEvent->SetSpectrum(val);
}      
void NeuPrimaryGeneratorAction::SetEnergyRangeFlag(G4String val)
{
   energyFlag = val;
   theBeamGun->SetEnergyRangeFlag(energyFlag);
   theCalibrationGenerator->SetEnergyRangeFlag(energyFlag);
   PrintGunParameters();
}
void NeuPrimaryGeneratorAction::PrintGunParameters()
{
   G4cout << G4endl <<
       "--------------------------Gun Settings-----------------" << G4endl;
   if (spctrmFlag == "GPS") {
      G4cout <<
          " *** Energy and position are set by the user with /gps/ UI commands. *** "
          << G4endl;
   } else if (spctrmFlag == "ParticleGun") {
      G4cout <<
          " *** Energy and position are set by the user with /gun/ UI commands. *** "
          << G4endl;
   } else if (spctrmFlag == "CalGen") {
      G4cout <<
		" *** Energy Specctrum from " << energyFlag << " " << isoFlag;
      G4cout << " decay gammas *** " << G4endl;
      G4cout << "*** Set particle type and position with /gps/ UI commands *** ";

		G4cout << G4endl;
   } else if ( spctrmFlag == "KRoom" || spctrmFlag == "URoom" 
              || spctrmFlag == "ThRoom") {
      
      G4cout <<
		" *** Energy Specctrum from " << spctrmFlag << " **** " << G4endl;
      G4cout << "*** Random initial positions " << theRoomRadiationGun->GetGlobalRadius()/cm;
      G4cout << " cm from the origin of the world. ***"  << G4endl;
      G4cout << "*** Positions aimed onto " << theRoomRadiationGun->GetPositionGenFlag();
      G4cout << " *** " << G4endl;
      if (theRoomRadiationGun->GetPositionGenFlag() =="Sphere" ){
         G4cout << "*** Sphere Radius " << theRoomRadiationGun->GetPosSphereRadius()/cm;
         G4cout <<  " cm *** " << G4endl;
      } else{
         G4cout << "*** Plane size " << 2*theRoomRadiationGun->GetPlaneHalfLengthY()/cm << " by ";
         G4cout << 2*theRoomRadiationGun->GetPlaneHalfLengthZ()/cm << " cm *** " << G4endl;
      }
      G4cout << "*** Random initial angles in the " << theRoomRadiationGun->GetAngleRangeFlag();
      G4cout << " range. ***"  << G4endl;
      G4cout << "*** Set particle type with /gun/ UI commands *** " << G4endl;
      
      
   } else if (spctrmFlag == "Muon" || spctrmFlag == "Neutron" 
              || spctrmFlag == "Nucleon" || spctrmFlag == "Gamma" ) {
      G4cout << " *** Energy is given by the Cosmic " << spctrmFlag << " spectrum. *** " <<
         G4endl;
         G4cout <<
			"*** Random initial positions " << theCosmicRayGun->GetGlobalRadius()/cm;
         G4cout << " cm from the origin of the world. ***"  << G4endl;
         G4cout << "*** Plane size " << 2*theCosmicRayGun->GetPlaneHalfLengthY()/cm << " by ";
         G4cout << 2*theCosmicRayGun->GetPlaneHalfLengthZ()/cm << " cm *** " << G4endl;
         G4cout << "*** Set particle type with /gun/ UI commands *** " << G4endl;
   } else if (spctrmFlag == "Beam") {
      G4cout <<
          " *** Energy is given by the spectrum in the KATRIN beam.\t***"
          << G4endl;
      G4cout << " *** Post Acceleration is in the " << energyFlag <<
          " energy region.\t***" << G4endl;
      G4cout << " *** Using random initial positions in flux tube.\t***"
          << G4endl;
      G4cout << "*** Set particle type with /gun/ UI commands *** " << G4endl;

   } else if (spctrmFlag == "DecayChain"){
      G4cout << " *** Energy is given by the DecayChain *** " << G4endl;
   }
   G4cout << "------------------------------------------------------------"
       << G4endl;

}
G4ThreeVector NeuPrimaryGeneratorAction::CosmicPlanePosition() {
   return theCosmicRayGun->GetParticlePlanePosition();
}
G4ThreeVector NeuPrimaryGeneratorAction::RoomRadiationPlanePosition() {
   return theRoomRadiationGun->GetParticlePlanePosition();
}
