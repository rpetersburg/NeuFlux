#include "NeuCosmicGenerator.hh"

#include "G4Event.hh"
#include "G4PrimaryParticle.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "globals.hh"
#include "G4ios.hh"
#include "G4MuonMinus.hh"
#include "G4Neutron.hh"

#include "TRandom3.h"
#include "TMath.h"
#include "TF1.h"
#include "TF2.h"

NeuFlux::NeuCosmicGenerator::NeuCosmicGenerator() :
		spctrmFlag("Muon") {

	SetInitialValues();
	InitializeEnergySpectra();
	CosmicRandomizer = &NeuCosmicGenerator::MuonRandomizer;

}

NeuFlux::NeuCosmicGenerator::~NeuCosmicGenerator() {
	delete fMuonE;
	delete fNeutronE;
	delete fNucleonE;
	delete fGammaE;
	delete r3;
}

void NeuFlux::NeuCosmicGenerator::SetInitialValues() {
	//global radius, distance from origin of world to starting position.
	//make sure this is larger than any object you want cosmic rays to interact with.
	//smaller objects
	fGlobalRadius2 = 100 * 100 * m2;
	fPlaneHalfLengthZ = 10 * m;
	fPlaneHalfLengthY = 10 * m;
	fPlaneOffsetZ = 0 * cm;
	fPlaneOffsetY = 0 * cm;

	cosmicTheta = 0;
	NumberOfParticlesToBeGenerated = 1;
	particle_definition = 0;
	G4ThreeVector zero;
	particle_momentum_direction = (G4ParticleMomentum) zero;
	particle_energy = 0.0;
	particle_position = zero;
	particle_time = 0.0;
	particle_polarization = zero;
	particle_charge = 0.0;
	particle_position_on_X_plane = CLHEP::Hep3Vector();
}

//we need to figure out how to do flux distribution
void NeuFlux::NeuCosmicGenerator::InitializeEnergySpectra() {
	//initalize energy spectra
	//Note all are functions of CosTheta, not Theta

	// _________________energy spectrum for muons_______________________
	// Da Silva, Angela Jane.  Development of a low Background Environment for the Cryogenic
	// Dark Matter Search.  Ph. D. diss., University of British Columbia
	// 0.0205 muons/cm2/sec for 100 keV low limit
	// parameters are in MeV
	// Jan 2009, switch low limit to 100 MeV kinetic energy
	// and switch to omnidirectional intensity or integrated intensity from flux
	// 0.0251 muons/cm2/sec
	// also change charge ratio to 1.2
	// Wentz et al PICRC 1995 8.54*10^-3 cm-2s-1sr-1 above 500 MeV measured in Karlsruhe
	// This spectra, 8.43 *10^-3 cm-2s-1sr-1 above 500 MeV

	fMuonE =
			new TF2("f2",
					".372*((x+105.66)*.001+15)/(((x+105.66)*.001*y+80)*((x+105.66)*.001+15/y)*(5*(x+105.66)*.001+10/y)^(2.57))",
					0.25 * GeV, 100 * GeV, 0, 1);
	fMuonE->SetNpx(500);
	fMuonE->SetNpy(400);

	// ______________energy spectrum for primary neutrons/protons_______________
	// S. Eidelmann et al., Phys. Letters B, 592, 1 , (2004) 24
	// Karlsruhe altitude 1020 g/cm2
	// 4.69 10^-5 neutrons/cm2/sec
	// 9.38 10^-5 protons/cm2/sec
	fNucleonE = new TF2("fNE", "226607*(x+939)^(-2.7) * exp(-8.429/y)",
			(1 - 0.939) * GeV, 20 * GeV, 1, 0.342);
	fNucleonE->SetNpx(400);
	fNucleonE->SetNpy(400);

	// -------------------energy spectrum for low energy neutrons-----------------
	// Mikio Yamashita et al., Journal of Geophysical Research, 71, 16 (1966) 3817-3834
	//0.00626 neutrons/cm2/sec
	//  parameters must be in MeV
	fNeutronE =
			new TF1("f1",
					"(.000223/x)*(x<=.1)+(.0023-.0007*x)*(x>.1 && x<=1)+(.0016/x^1.74)*(x>1)",
					0.4 * eV, 10 * MeV);
	fNeutronE->SetNpx(10000);

	//--------------------energy spectra for gammas-------------------------
	//integral vertical intensity from PDG, assuming g=1.7*e below 1 GeV, and 1.3 above:
	//above 10 MeV: 51 gammas/m2 s sr = 0.0051 gammas/cm2 s sr
	//above 100 MeV: 10.2 gammas/m2 s sr = 0.00102 gammas/cm2 s sr
	//and above 1 GeV: 0.26 gammas/m2 s sr = 0.000026 gammas/cm2 s sr
	//or 4.56 10^(-3)  electrons/cm2/s from Heusser, no energy cut-off listed
	//page 346 grieder, flux of photons above 100 MeV 0.0017 g/cm2 s
	//page 347 cos2theta for E<35 MeV

	//This function
	//mean ~40 MeV
	//integrate flux 0.0245721 gammas/cm2 s
	//compare to 0.0205 muons/cm2/sec
	//vertical flux above 1 MeV: 0.015 gammas/cm2 s
	//vertical flux above 10 MeV: 0.0075 gammas/cm2 s
	//from daniels figure 15, 0.006 g/cm2/s/sr above 10 MeV
	//vertical flux above 100 MeV: 0.0011 gammas/cm2 s
	//from figure 15, 0.001 g/cm2/s/sr above 10 MeV
	//vertical flux above 1 GeV: 4.5*10^-5 gammas/cm2 s

	fGammaE =
			new TF2("fGE",
					"((0.0034712*x^(-1.0055))*(x<=30)+(0.0378*x^(-1.7164))*(x>30 && x<=100)+(0.4551*x^(-2.2575))*(x>100 && x<=500)+(6.3257*x^(-2.6516))*(x>500))*y^2",
					1 * MeV, 10 * GeV, 0, 1);
	fGammaE->SetNpx(10000);
	fGammaE->SetNpy(400);

	//-----------------General random generator setup------------------------
	//warning!  TF1::GetRandom used
	//to randomize energy uses gRandom 
	//which is TRandom by default
	//and will repeat after 10^9 calls
	//so first set gRandom to a TRandom3
	//setting seed to 0 means using a TUUID to set the seed
	r3 = new TRandom3(0);
	gRandom = r3;

}

void NeuFlux::NeuCosmicGenerator::GeneratePrimaryVertex(G4Event * evt) {
	if (particle_definition == 0)
		return;
	//randomize starting values for this event
	(this->*CosmicRandomizer)();

	// create a new vertex
	G4PrimaryVertex *vertex = new G4PrimaryVertex(particle_position,
			particle_time);

	// create new primaries and set them to the vertex
	G4double mass = particle_definition->GetPDGMass();
	G4double energy = particle_energy + mass;
	G4double pmom = std::sqrt(energy * energy - mass * mass);
	G4double px = pmom * particle_momentum_direction.x();
	G4double py = pmom * particle_momentum_direction.y();
	G4double pz = pmom * particle_momentum_direction.z();
	for (G4int i = 0; i < NumberOfParticlesToBeGenerated; i++) {
		G4PrimaryParticle *particle = new G4PrimaryParticle(particle_definition,
				px, py, pz);
		particle->SetMass(mass);
		particle->SetCharge(particle_charge);
		vertex->SetPrimary(particle);
	}

	evt->AddPrimaryVertex(vertex);
}
void NeuFlux::NeuCosmicGenerator::NeutronRandomizer() {
	particle_energy = fNeutronE->GetRandom();    //independent of zenith angle
	G4double costheta = 2 * r3->Rndm() - 1; //isotropic, entire sphere
	// or could be TF1 fNeutronT = new TF1("fNT", "sin(x)", 0, TMath::Pi()/2 );
	cosmicTheta = TMath::ACos(costheta);
	SetRandomPlanePosition();
	SetRandomMomentumDirection();
}

void NeuFlux::NeuCosmicGenerator::NucleonRandomizer() {

	G4double costheta = 0;
	fNucleonE->GetRandom2(particle_energy, costheta);
	//generate costheta instead of theta
	cosmicTheta = TMath::ACos(costheta);
	SetRandomPlanePosition();
	SetRandomMomentumDirection();
}

void NeuFlux::NeuCosmicGenerator::MuonRandomizer() {
	G4double costheta = 0;
	fMuonE->GetRandom2(particle_energy, costheta);
	//generate costheta instead of theta
	cosmicTheta = TMath::ACos(costheta);
	SetRandomPlanePosition();
	SetRandomMomentumDirection();
}

void NeuFlux::NeuCosmicGenerator::GammaRandomizer() {
	G4double costheta = 0;
	fGammaE->GetRandom2(particle_energy, costheta);
	//generate costheta instead of theta
	cosmicTheta = TMath::ACos(costheta);
	SetRandomPlanePosition();
	SetRandomMomentumDirection();
}

void NeuFlux::NeuCosmicGenerator::SetRandomPlanePosition() {
	// Warning, beam axis is z axis, so define theta and zenith angle wrt x axis

	// chose random position on plane at x = 0
	if (fPlaneHalfLengthZ * fPlaneHalfLengthZ
			+ fPlaneHalfLengthY * fPlaneHalfLengthY > fGlobalRadius2) {
		G4cout << "Warning: need to increase the global radius for cosmic rays"
				<< G4endl;
			}
			G4ThreeVector pp(0, fPlaneOffsetY + fPlaneHalfLengthY * (2 * r3->Rndm() - 1),
					fPlaneOffsetZ + fPlaneHalfLengthZ * (2 * r3->Rndm() - 1));
			particle_position_on_X_plane = pp;

		}

void NeuFlux::NeuCosmicGenerator::SetRandomMomentumDirection() {
	// warning: must set zenith angle and plane postion before calling this function

	//this function sets momentum direction and "global position"
	// theta already set, now randomize phi and direction up from plane
	G4double phi = r3->Rndm() * 2 * TMath::Pi();

	//plane position + local position should intersect sphere of radius "fGlobalRadius"
	//solve vector equation (plane_position + local_position)^2 = global_radius^2 
	//for local radius magnitude
	// lr^2 + 2 lp.pp + (pr^2-gr^2) = 0
	// lr^2 + b * lr + c = 0
	//b = 2 * plane_position dot local_position_unit
	//c = plane_position^2 - global_position^2
	G4double b = 2 * TMath::Sin(cosmicTheta)
			* (particle_position_on_X_plane.y() / cm * TMath::Cos(phi)
					+ particle_position_on_X_plane.z() / cm * TMath::Sin(phi));
	G4double c = (particle_position_on_X_plane.mag2() - fGlobalRadius2) / cm2;
	//now use quadratic formula
	G4double localradius = (-b + TMath::Sqrt(b * b - 4 * c)) / 2 * cm;

	G4double x = localradius * TMath::Cos(cosmicTheta);
	G4double y = localradius * TMath::Cos(phi) * TMath::Sin(cosmicTheta);
	G4double z = localradius * TMath::Sin(phi) * TMath::Sin(cosmicTheta);
	G4ThreeVector local_position(x, y, z);

	particle_position = particle_position_on_X_plane + local_position;
	particle_momentum_direction = -local_position / local_position.mag();

}

void NeuFlux::NeuCosmicGenerator::SetSpectrumFlag(G4String val) {

	spctrmFlag = val;
	if (spctrmFlag == "Muon") {
		CosmicRandomizer = &NeuCosmicGenerator::MuonRandomizer;
		this->SetParticleDefinition(G4MuonMinus::Definition());
		particle_definition = G4MuonMinus::Definition();
	} else if (spctrmFlag == "Neutron") {
		CosmicRandomizer = &NeuCosmicGenerator::NeutronRandomizer;
		this->SetParticleDefinition(G4Neutron::Definition());
	} else if (spctrmFlag == "Nucleon") {
		CosmicRandomizer = &NeuCosmicGenerator::NucleonRandomizer;
	} else if (spctrmFlag == "Gamma") {
		CosmicRandomizer = &NeuCosmicGenerator::GammaRandomizer;
	}
}
void NeuFlux::NeuCosmicGenerator::SetPlaneHalfLengthZ(G4double lenZ) {

	fPlaneHalfLengthZ = lenZ;
}
void NeuFlux::NeuCosmicGenerator::SetPlaneHalfLengthY(G4double lenY) {

	fPlaneHalfLengthY = lenY;
}
void NeuFlux::NeuCosmicGenerator::SetPlaneOffsetZ(G4double lenZ) {

	fPlaneOffsetZ = lenZ;
}
void NeuFlux::NeuCosmicGenerator::SetPlaneOffsetY(G4double lenY) {

	fPlaneOffsetY = lenY;
}
void NeuFlux::NeuCosmicGenerator::SetGlobalRadius(G4double Rlen) {

	fGlobalRadius2 = Rlen * Rlen;
}
