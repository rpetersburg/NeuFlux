
#ifndef NeuMinEkineCuts_hh_
#define NeuMinEkineCuts_hh_

#include "G4ios.hh"
#include "globals.hh"
#include "NeuCuts.hh"

namespace NeuFlux
{
  /*!
    \class NeuMinEkineCuts
   
    \ingroup Neu
   
    \brief Physics Process to cut on minimum kinetic energy.
   
    \author Kevin Wierman
   
    \version $Revision: 1.5 $
   
    \date $Date: Tue Nov 20 12::33:51 2012 $
   
    Contact: kwierman@email.unc.edu
   
    Created on: Wed Apr 1 18:39:37 2005
   
 */

  class NeuMinEkineCuts : public NeuCuts {
   public:

     NeuMinEkineCuts(const G4String & processName =
                               "NeuMinEkineCuts");

      virtual ~ NeuMinEkineCuts();

     // PostStep GPIL
     virtual G4double PostStepGetPhysicalInteractionLength(const G4Track &
                                                           track,
                                                           G4double
                                                           previousStepSize,
                                                           G4ForceCondition *
                                                           condition);


   private:

     // hide assignment operator as private 
      NeuMinEkineCuts(NeuMinEkineCuts &);
      NeuMinEkineCuts & operator=(const NeuMinEkineCuts &
                                            right);

  };

}
#endif
