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
		{
		}

NeuFlux::NeuCosmicGenerator::~NeuCosmicGenerator() 
{
	delete r3;
}

/*!
	The order of operations goes as this:
		1. Generate the energy and position distribution of the particles.

*/
void NeuFlux::NeuCosmicGenerator::GeneratePrimaryVertex(G4Event * evt) {



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
	muonE =
			new TF2("f2",
					".372*((x+105.66)*.001+15)/(((x+105.66)*.001*y+80)*((x+105.66)*.001+15/y)*(5*(x+105.66)*.001+10/y)^(2.57))",
					0.25 * GeV, 100 * GeV, 0, 1);
	muonE->SetNpx(500);
	muonE->SetNpy(400);


	//generate the random variables in regard to energy and costheta
	G4double costheta = 0;
	G4double particle_energy;

	muonE->GetRandom2(particle_energy, costheta);
	costheta = TMath::ACos(costheta);
	G4double phi = r3->Rndm() * 2 * TMath::Pi();

	G4ThreeVector pp(0, fPlaneOffsetY + fPlaneHalfLengthY * (2 * r3->Rndm() - 1),
					fPlaneOffsetZ + fPlaneHalfLengthZ * (2 * r3->Rndm() - 1));
			particle_position_on_X_plane = pp;


	

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




	G4PrimaryVertex *vertex = new G4PrimaryVertex(particle_position,
			particle_time);


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