
#ifndef NeuVisManager_hh_
#define NeuVisManager_hh_

#ifdef G4VIS_USE

#include "G4VisManager.hh"

namespace NeuFlux
{
	/*!
		\class NeuVisManager
		
		\ingroup NeuFlux
		
		\brief Sets up all of the visualizers.
		
		  Sets up the visualizers.
		
		\author Kevin Wierman
		
		\version 1.0
		
		\date Oct 1, 2013
		
		\constact kwierman@email.unc.edu
		
	*/
	class NeuVisManager : public G4VisManager 
	{

	public:
		NeuVisManager();

	private:
		void RegisterGraphicsSystems();

	};
}

#endif

#endif
