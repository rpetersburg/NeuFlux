#ifndef NeuRandom_hh_
#define NeuRandom_hh_

#include "TRandom3.h"

namespace NeuFlux
{
	/*!
		\class NeuRandom
		\brief Random Number interface for the NeuFlux simulation
	*/
	class NeuRandom
	{
	private:

		TRandom3* r3; ///Contains the random number generator. Replace this when necessary

		static NeuRandom* single;
		NeuRandom();
		virtual ~NeuRandom()
		{
			single = NULL;
		}

		NeuRandom(NeuRandom const&){}
   		NeuRandom& operator=(NeuRandom const&){return *this;}

	public:
		static NeuRandom* GetInstance()
		{
			if (! single)
				single = new NeuRandom;
			return single;
		}

		/*!
			The Primary Call for getting random numbers
			\return A random double between 0 and 1. 
		*/
		double GetRandom();
		/*
			Resets the seed in a machine predictable way
		*/
		void ResetSeed();

	};


}

#endif

