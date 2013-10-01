/*!
  \class NeuEarthFields
 
  \ingroup NeuFlux
 
  \brief Simple Class for initializing and updating EM fields due to the Earth's magnetic field.
 
      Initally called within the Detector Geometry Setup, this initializes
      the field values and utilizes the KDSFieldMessenger Class to update
      field values and stepper action
 
  
  \author Kevin Wierman
 
  \version 1.5 
 
  \date Tue Nov 20 12::33:51 2012 $
 
  Contact: kwierman@email.unc.edu
 
  Created on: Wed Apr 1 18:39:37 2005
 */

#ifndef NeuearthFields_hh_
#define NeuearthFields_hh_

#include "G4MagneticField.hh"
#include "G4UniformMagField.hh"

class NeuEarthFields
{
public:
  NeuEarthFields(G4ThreeVector) {}
  NeuEarthFields() {}

 ~NeuEarthFields() {} 

};

#endif
