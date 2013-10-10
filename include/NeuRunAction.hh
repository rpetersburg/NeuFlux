
#ifndef NeuRunAction_hh_
#define NeuRunAction_hh_ 

#include "NeuRootOutput.hh"

#include "G4UserRunAction.hh"
#include "globals.hh"
#include "G4Run.hh"


namespace NeuFlux
{
   /*!
      \class NeuRunAction
      
      \ingroup NeuFlux
      
      \brief Defines behavior at beginning and end of Run.
      
         At the beginning of each run, 
      
      \note The default root file name is: <Katrin_<spectrum>_<timeSeed><runNumber>.root>
      
      
      \author Kevin Wierman
      
      \version $Revision: 1.5 $
      
      \date $Date: Tue Nov 20 12::33:51 2012 $
      
      Contact: kwierman@email.unc.edu
      
      Created on: Wed Apr 1 18:39:37 2005
      
    */

   class NeuRunAction : public G4UserRunAction , public NeuOutputtingComponent {

   public:
      NeuRunAction();
      ~NeuRunAction();

   public:
      void BeginOfRunAction(const G4Run *);
      void EndOfRunAction(const G4Run *);

      void OnNewFileCreate();

   private:
      G4int fID;
      G4int fTimeSeed;
   };
}

#endif
