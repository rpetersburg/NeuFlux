/*!
   \class NeuRunAction
   
   \ingroup Neu
   
   \brief Defines behavior at beginning and end of Run.
   
      Mostly is an input/output manager. Just deals with the output root file.
   
   \note The default root file name is: <Katrin_<spectrum>_<timeSeed><runNumber>.root>
   
   
   \author Kevin Wierman
   
   \version $Revision: 1.5 $
   
   \date $Date: Tue Nov 20 12::33:51 2012 $
   
   Contact: kwierman@email.unc.edu
   
   Created on: Wed Apr 1 18:39:37 2005
   
 */

#ifndef NeuRunAction_hh_
#define NeuRunAction_hh_ 

///     Geant4 package includes
#include "G4UserRunAction.hh"
#include "globals.hh"
#include "G4Run.hh"


///     ROOT includes
#include "TROOT.h"
#include "TFile.h"
#include "TTree.h"

namespace NeuFlux
{
class NeuRunAction:public G4UserRunAction {

 public:
   NeuRunAction(G4int);
   ~NeuRunAction();

 public:
   void BeginOfRunAction(const G4Run *);
   void EndOfRunAction(const G4Run *);
   G4int GetRunInt() {
      return id;
   };
   void NameRootFile();
   void SetRootBranches();

   TFile * GetRootFile() {
      return rootFile;
   };
   TTree *GetTree() {
      return tree;
   };

   void SetRootFile(TFile * file) {
      rootFile = file;
   };
   void SetTree(TTree * newTree) {
      tree = newTree;
   };

 private:
   G4int id;
   TFile * rootFile;
   TTree *tree;
   G4int timeSeed;

};
}

#endif
