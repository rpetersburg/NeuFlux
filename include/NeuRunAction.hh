/*!
   \class NeuRunAction
   
   \ingroup Neu
   
   \brief Defines behavior at beginning and end of Run.
   
      At the beginning of each run, 
   
   \note The default root file name is: <Katrin_<spectrum>_<timeSeed><runNumber>.root>
   
   
   \author Kevin Wierman
   
   \version $Revision: 1.5 $
   
   \date $Date: Tue Nov 20 12::33:51 2012 $
   
   Contact: kwierman@email.unc.edu
   
   Created on: Wed Apr 1 18:39:37 2005
   
 */

#ifndef NeuRunAction_hh_
#define NeuRunAction_hh_ 

#include "G4UserRunAction.hh"
#include "globals.hh"
#include "G4Run.hh"

#include "TROOT.h"
#include "TFile.h"
#include "TTree.h"

namespace NeuFlux
{
   class NeuRunAction : public G4UserRunAction {

   public:
      NeuRunAction(G4int);
      ~NeuRunAction();

   public:
      void BeginOfRunAction(const G4Run *);
      void EndOfRunAction(const G4Run *);

      G4int GetRunInt() {
         return fID;
      };

      TFile * GetRootFile() {
         return fOutput;
      };
      TTree *GetTree() {
         return fTree;
      };

      void SetRootFile(TFile * file) {
         fOutput = file;
      };
      void SetTree(TTree * newTree) {
         fTree = newTree;
      };

   private:
      G4int fID;
      TFile * fOutput;
      TTree * fTree;
      G4int fTimeSeed;
   };
}

#endif
