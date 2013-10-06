#ifndef NeuearthFields_hh_
#define NeuearthFields_hh_

#include "G4MagneticField.hh"
#include "G4UniformMagField.hh"

namespace NeuFlux
{
    /*!
    \class NeuEarthFields
   
    \ingroup NeuFlux
   
    \brief Simple Class for initializing and updating EM fields due to the Earth's magnetic field.
   
        Initally called within the Detector Geometry Setup, this initializes
        the field values and utilizes the KDSFieldMessenger Class to update
        field values and stepper action
   
    
    \author Kevin Wierman
    \version 1.0
    \date Oct1 ,2013 
    \contact kwierman@email.unc.edu
   */
  class NeuEarthFields
  {

  public:
    NeuEarthFields(G4ThreeVector) {}
    NeuEarthFields() {}

   ~NeuEarthFields() {} 

  };


}
#endif
