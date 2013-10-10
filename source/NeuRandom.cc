#include "NeuRandom.hh"

NeuFlux::NeuRandom* NeuFlux::NeuRandom::single = NULL;


NeuFlux::NeuRandom::NeuRandom()
{
	r3 = new TRandom3(0);
}

double NeuFlux::NeuRandom::GetRandom()
{
	return r3->Rndm();
}

void NeuFlux::NeuRandom::ResetSeed()
{
	r3->SetSeed( r3->GetSeed() +1 );
}
