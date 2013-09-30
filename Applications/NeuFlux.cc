/*! \file NeuFlux.cc
    \brief The Main Executable for the NeuFlux
    \author Kevin Wierman

    This is a copied example of the standard Geant4 main executable.
    This is to be used for main simulation execution only.
    \warning For testing and debugging purposes, other executables should be used.

    \fn int main(int argc, char **argv)
    \brief The main execution point for the program.
    \param The name of a valid macro file, or nothing

*/

#include "G4RunManager.hh"
#include "G4UImanager.hh"
#include "G4UIterminal.hh"
#include "G4UItcsh.hh"

#ifdef G4UI_USE_XM
#include "G4UIXm.hh"
#endif

#include "NeuFlux.hh"

#ifdef G4VIS_USE
#include "NeuFluxVisManager.hh"
#endif

#include "TRandom3.h"


//#include "TROOT.h"

///     CLHEP includes
// #include "Randomize.hh"

int main(int argc, char **argv)
{

   ///  Set the random seed using TRandom3, with
   TRandom3 r3(0);
   // CLHEP::HepRandom::setTheSeed() accepts long, not unsigned
   //Using the full UInt by utilizing the 8th Mersenne Prime.
   UInt_t rSeed   = static_cast<UInt_t> (2147483647.*r3.Rndm());
   std::cout << "Randomization Seed: " << rSeed << std::endl;

   std::cout<<"  Setting up Run Manager"<<std::endl;
   ///  Run manager initialization
   G4RunManager *runManager = new G4RunManager;
   //KDSDetectorConstruction *KDSDetector =
   //    new KDSDetectorConstruction;
   //runManager->SetUserInitialization(KDSDetector);
   //runManager->SetUserInitialization(new KDSPhysicsList);

   /// Construct and initialize the Visualization Manager
#ifdef G4VIS_USE
   std::cout<<"  Setting up Visualization Manager"<<std::endl;
   //G4VisManager *visManager = new KDSVisManager;
   //visManager->SetVerboseLevel(0);
   //visManager->Initialize();
#endif


   std::cout<<"  Setting up User Action Classes"<<std::endl;
   ///  UserAction classes
   //KDSRunAction *KDSRun = new KDSRunAction(rSeed);
   //runManager->SetUserAction(KDSRun);
   std::cout<<"    done setting run action"<<std::endl;
   //KDSEventAction *KDSEvent =
   //    new KDSEventAction(KDSRun);
   //runManager->SetUserAction(KDSEvent);
   //runManager->SetUserAction( new KDSPrimaryGeneratorAction(
   //                    KDSEvent) );
   //KDSTrackingAction *KDSTracking =
   //    new KDSTrackingAction;
   //runManager->SetUserAction(KDSTracking);
   /*runManager->
       SetUserAction(new
                     KDSSteppingAction(KDSEvent,
					     KDSTracking, KDSDetector));
    */

   std::cout<<"  Initializing the G4 kernel"<<std::endl;
   ///  Initialize G4 kernel
   //runManager->Initialize();

   ///  Get the pointer to the User Interface manager 
   G4UImanager *UI = G4UImanager::GetUIpointer();

   ///  Default generator is the HepJamesRandom, based on RANMAR
   //CLHEP::HepRandom::setTheSeed(rSeed);
 
   /// run the DAWNfile creation
//   UI->ApplyCommand("/control/execute KDSVis.macro");

   if (argc == 1) 
   {
      ///       Define (G)UI terminal for interactive mode  
      ///       G4UIterminal is a (dumb) terminal.


      G4UIsession *session = new G4UIterminal(
      #ifdef G4UI_USE_TCSH
    		  new G4UItcsh
      #endif
    		);

      /// run the OGLIX file creation
//      UI->ApplyCommand("/control/execute vis.macro");

      session->SessionStart();
      delete session;
   } 
   else 
   {
      ///       Batch mode
      G4String command = "/control/execute ";
      G4String fileName = argv[1];
      UI->ApplyCommand(command + fileName);
   }

   ///  Cleanup
   delete runManager;
#ifdef G4VIS_USE
   delete visManager;
#endif

   return 0;
}
