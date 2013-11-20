
#ifndef NeuGeometryMessenger_hh_
#define NeuGeometryMessenger_hh_

#include "globals.hh"
#include "G4UImessenger.hh"
#include "G4UIdirectory.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"
#include "G4UIcmdWithoutParameter.hh"



namespace NeuFlux
{
	class NeuWorldGeometry;

	/*!
	  \class NeuGeometryMessenger
	 
	  \ingroup NeuFlux
	 
	  \brief Messenger Class for the geometry
	 
	  \note Defaults to a small Geometry
	 
	  \author Kevin Wierman
	 
	  \version 1.0
	 
	  \date Oct 1, 2013
	 
	  Contact: kwierman@email.unc.edu

	 */

	class NeuGeometryMessenger : public G4UImessenger 
	{
	public:
		NeuGeometryMessenger(NeuWorldGeometry*);
		virtual ~ NeuGeometryMessenger();

		virtual void SetNewValue(G4UIcommand *, G4String);

	private:
		NeuWorldGeometry* fGeometry;

		G4UIdirectory* fNeuFluxDir;
			G4UIdirectory* fGeometryDir;
				G4UIcmdWithoutParameter* fDumpGeometry;
				G4UIdirectory* fWorldDir;
					G4UIcmdWithADoubleAndUnit* fWorldX;
					G4UIcmdWithADoubleAndUnit* fWorldY;
					G4UIcmdWithADoubleAndUnit* fWorldZ;
				G4UIdirectory* fRockDir;
					G4UIcmdWithADoubleAndUnit* fRockX;
					G4UIcmdWithADoubleAndUnit* fRockY;
					G4UIcmdWithADoubleAndUnit* fRockZ;
				G4UIdirectory* fConcreteDir;
					G4UIcmdWithADoubleAndUnit* fConcreteX;
					G4UIcmdWithADoubleAndUnit* fConcreteY;
					G4UIcmdWithADoubleAndUnit* fConcreteZ;
				G4UIdirectory* fDetectorDir;
					G4UIcmdWithADoubleAndUnit* fDetectorLength;
					G4UIcmdWithADoubleAndUnit* fDetectorDiameter;

	};

}
#endif
