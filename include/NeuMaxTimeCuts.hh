#ifndef NeuMaxTimeCuts_hh_
#define NeuMaxTimeCuts_hh_

#include "G4ios.hh"
#include "globals.hh"
#include "NeuCuts.hh"

namespace NeuFlux
{
  /*!
    \class NeuMaxTimeCuts
   
    \ingroup NeuFlux
   
    \brief Physics Process to cut on maximum amount of time.

    \note This is defined for neutrons only
   
    \author Kevin Wierman
   
    \version 1.0
   
    \date Oct 1, 2013

    \contact kwierman@email.unc.edu
   
  */

  class NeuMaxTimeCuts:public NeuCuts {
   public:

     NeuMaxTimeCuts(const G4String & processName =
                              "NeuMaxTimeCuts");

      virtual ~ NeuMaxTimeCuts();

     // PostStep GPIL
     virtual G4double PostStepGetPhysicalInteractionLength(const G4Track &
                                                           track,
                                                           G4double
                                                           previousStepSize,
                                                           G4ForceCondition *
                                                           condition);


   private:

     // hide assignment operator as private 
      NeuMaxTimeCuts(NeuMaxTimeCuts &);
      NeuMaxTimeCuts & operator=(const NeuMaxTimeCuts &
                                           right);

  };
}

#endif
