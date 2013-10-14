#include "NeuRootOutput.hh"

//! Initial State of this class is empty
NeuFlux::NeuRootOutput* NeuFlux::NeuRootOutput::single = NULL;


NeuFlux::NeuOutputtingComponent::NeuOutputtingComponent()
{
	NeuRootOutput::GetInstance()->RegisterNewFileComponent(this);
}


