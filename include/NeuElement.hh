#ifndef NeuElement_hh_
#define NeuElement_hh_

#include "G4Element.hh"
#include "G4Isotope.hh"
/*!
	\file NeuElement.hh
	\brief Header file containing the isotopic definitions of common elements in rock

	\author Kevin Wierman
*/
namespace NeuFlux
{

class NeuHydrogen : G4Element
{
public:
	NeuHydrogen() : G4Element("Natural H", "natH", 3)
	{
		h1 = new G4Isotope( "H1", 1, 1, 1.00794*g/mole );
		h2 = new G4Isotope( "H2", 1, 2, 2.01410178*g/mole );
		h3 = new G4Isotope( "H3", 1, 3, 3.0160492*g/mole );
		this->AddIsotope( h1, 99.98*perCent-1.0/(1.e12)*perCent );
		this->AddIsotope( h2, 0.02*perCent );
		this->AddIsotope( h3, 1.0/(1.e12)*perCent );
	}
	~NeuHydrogen()
	{
		delete h1;
		delete h2;
		delete h3;
	}
private:
	G4Isotope* h1;
	G4Isotope* h2;
	G4Isotope* h3;
};

class NeuCarbon : G4Element
{
public:
	NeuCarbon() : G4Element("Natural C", "natC", 3)
	{
		c12 = new G4Isotope( "C12", 6, 12, 12.0*g/mole );
	 	c13 = new G4Isotope( "C13", 6, 13, 13.00335*g/mole );
	 	c14 = new G4Isotope( "C14", 6, 14, 14.003241*g/mole );
	 	this->AddIsotope( c12, 98.89*perCent-1.0/(1.e12)*perCent );
		this->AddIsotope( c13, 1.109*perCent );
		this->AddIsotope( c14, 1.0/(1.e12)*perCent );
	}
	~NeuCarbon()
	{
		delete c12;
		delete c13;
		delete c14;
	}
private:
	G4Isotope* c12;
	G4Isotope* c13;
	G4Isotope* c14;
};

class NeuOxygen : G4Element
{
public:
	NeuOxygen() : G4Element( "Natural O", "natO", 3 )
	{
		O16 = new G4Isotope( "O16", 8, 16, 15.99491463*g/mole );
		O17 = new G4Isotope( "O17", 8, 17, 16.9991312*g/mole );
		O18 = new G4Isotope( "O18", 8, 18, 17.9991603*g/mole );
		this->AddIsotope( O16, 99.757*perCent );
		this->AddIsotope( O17, 0.038*perCent );
		this->AddIsotope( O18, 0.205*perCent );
	}
	~NeuOxygen()
	{
		delete O16;
		delete O17;
		delete O18;
	}
private:
	G4Isotope* O16;
	G4Isotope* O17;
	G4Isotope* O18;
};
class NeuSilicon : G4Element
{
public:
	NeuSilicon() : G4Element( "Natural Si", "natSi", 3 )
	{
		Si28 = new G4Isotope( "Si28", 14, 28, 27.9769265325*g/mole );
   		Si29 = new G4Isotope( "Si28", 14, 29, 28.976494700*g/mole );
   		Si30 = new G4Isotope( "Si28", 14, 30, 29.97377017*g/mole );
   		this->AddIsotope( Si28, 92.223*perCent );
   		this->AddIsotope( Si29, 4.685*perCent );
   		this->AddIsotope( Si30, 3.092*perCent );
	}
	~NeuSilicon()
	{
		delete Si28;
		delete Si29;
		delete Si30;
	}
private:
	G4Isotope* Si28;
	G4Isotope* Si29;
	G4Isotope* Si30;
};
class NeuAluminum : G4Element
{
public:
	NeuAluminum() : G4Element( "Natural Al", "natAl", 2 )
	{
		Al26 = new G4Isotope( "Al26", 13, 26, 25.98689169*g/mole );
   		Al27 = new G4Isotope( "Al27", 13, 27, 26.98153863*g/mole );
   		this->AddIsotope( Al26, 99.999*perCent );
   		this->AddIsotope( Al27, 0.001*perCent );
	}
	~NeuAluminum()
	{
		delete Al26;
		delete Al27;
	}
private:
	G4Isotope* Al26;
	G4Isotope* Al27;
};
class NeuIron : G4Element
{
public:
	NeuIron() : G4Element( "Natural Fe", "natFe", 4 )
	{
		Fe54 = new G4Isotope( "Fe54", 26, 54, 53.9396105*g/mole );
   		Fe56 = new G4Isotope( "Fe56", 26, 56, 55.9349375*g/mole );
		Fe57 = new G4Isotope( "Fe57", 26, 57, 56.9353940*g/mole );
   		Fe58 = new G4Isotope( "Fe58", 26, 58, 57.9332756*g/mole );
   		this->AddIsotope( Fe54, 5.845*perCent );
   		this->AddIsotope( Fe56, 91.754*perCent );
   		this->AddIsotope( Fe57, 2.119*perCent );
   		this->AddIsotope( Fe58, 0.282*perCent );
	}
	~NeuIron()
	{
		delete Fe54;
		delete Fe56;
		delete Fe57;
		delete Fe58;
	}
private:
	G4Isotope* Fe54;
	G4Isotope* Fe56;
	G4Isotope* Fe57;
	G4Isotope* Fe58;
};
class NeuCalcium : G4Element
{
public:
	NeuCalcium() : G4Element( "Natural Ca", "natCa", 6 )
	{
		Ca40 = new G4Isotope( "Ca40", 20, 40, 39.962591*g/mole );
   		Ca42 = new G4Isotope( "Ca42", 20, 42, 41.958622*g/mole );
		Ca43 = new G4Isotope( "Ca43", 20, 43, 42.958770*g/mole );
   		Ca44 = new G4Isotope( "Ca44", 20, 44, 43.955485*g/mole );
   		Ca46 = new G4Isotope( "Ca46", 20, 46, 45.953689*g/mole );
   		Ca48 = new G4Isotope( "Ca48", 20, 48, 47.952532*g/mole );
   		this->AddIsotope( Ca40, 96.95*perCent );
   		this->AddIsotope( Ca42, 0.65*perCent );
   		this->AddIsotope( Ca43, 0.14*perCent );
   		this->AddIsotope( Ca44, 2.086*perCent );
   		this->AddIsotope( Ca43, 0.004*perCent );
   		this->AddIsotope( Ca44, 0.19*perCent );
	}
	~NeuCalcium()
	{
		delete Ca40;
		delete Ca42;
		delete Ca43;
		delete Ca44;
		delete Ca46;
		delete Ca48;
	}
private:
	G4Isotope* Ca40;
	G4Isotope* Ca42;
	G4Isotope* Ca43;
	G4Isotope* Ca44;
	G4Isotope* Ca46;
	G4Isotope* Ca48;
};
class NeuSodium : G4Element
{
public: 
	NeuSodium() : G4Element("Natural Na","natNa", 1)
	{
		Na23 = new G4Isotope("Na23", 11, 23, 22.989770);
		this->AddIsotope(Na23, 100.00*perCent);
	}
	~NeuSodium()
	{
		delete Na23;
	}
private:
	G4Isotope* Na23;
};
class NeuPotassium : G4Element
{
public:
	NeuPotassium() : G4Element( "Natural K", "natK", 3 )
	{
		K39 = new G4Isotope( "K39", 19, 39, 38.963708*g/mole );
		K40 = new G4Isotope( "K40", 19, 40, 39.963999*g/mole );
		K41 = new G4Isotope( "K41", 19, 41, 40.961825*g/mole );
		this->AddIsotope( K39, 93.20*perCent );
		this->AddIsotope( K40, 0.012*perCent );
		this->AddIsotope( K41, 6.73*perCent );
	}
	~NeuPotassium()
	{
		delete K39;
		delete K40;
		delete K41;
	}
private:
	G4Isotope* K39;
	G4Isotope* K40;
	G4Isotope* K41;
};
class NeuMagnesium : G4Element
{
public:
	NeuMagnesium() : G4Element( "Natural Mg", "natMg", 3 )
	{
		Mg24 = new G4Isotope( "Mg24", 12, 24, 23.985045*g/mole );
		Mg25 = new G4Isotope( "Mg25", 12, 25, 24.985839*g/mole );
		Mg26 = new G4Isotope( "Mg26", 12, 26, 25.982595*g/mole );
		this->AddIsotope( Mg24, 78.90*perCent );
		this->AddIsotope( Mg25, 10.00*perCent );
		this->AddIsotope( Mg26, 11.10*perCent );
	}
	~NeuMagnesium()
	{
		delete Mg24;
		delete Mg25;
		delete Mg26;
	}
private:
	G4Isotope* Mg24;
	G4Isotope* Mg25;
	G4Isotope* Mg26;
};

}

#endif //NeuElement_hh_


