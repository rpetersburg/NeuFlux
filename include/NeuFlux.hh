/*!
	\mainpage Neuflux

	\tableofcontents

	\section intro Introduction

	This is the placeholder simulation for Neutron Flux at low depths (NeutronFlux, or NeuFlux for short).
	The prupose of this software is to 

	Copyright © 2013 University of North Carolina at Chapel Hill. All rights reserved.

	---

	This software was prepared for the Regents of the University of <br>
	North Carolina at the Deptment of Physics and Astronomy sponsored <br>
	in part by the United States Department of Energy (DOE) under <br>
	Grant #DE-FG02-97ER41020. The University has certain rights in the <br> 
	software pursuant to the contract and the software should not be  <br>
	copied or distributed outside your organization.  The DOE and the  <br>
	University of North Carolina reserve all rights in the software.  <br>
	Neither the authors, University of North Carolina, or U.S. Government <br> 
	make any warranty, express or implied, or assume any liability or <br>
	responsibility for the use of this software.
	
	---
	
	\section downloading Downloading Software

	This software is hosted on <a href="https://github.com/">GitHub</a>. 
	The URL for the repository is: https://github.com/kwierman/NeuFlux .

	Pulling from the repository can be accomplished by downloading <a href="https://github.com/">Git</a>

		git clone https://github.com/kwierman/NeuFlux.git

	It is advisable that if the software is being worked on to create a separate branch. 
	This can be accomplished with the following line:

		git checkout -b <your_branch_name>

	Pushing to the repository can be accomplished with the following command:

		git push -u origin <your_branch_name>
	
	---

	\section dep Dependencies

	The following libraries must be built and in the paths in order to build properly:

	-  ROOT
		-  <a href="http://root.cern.ch/drupal/">ROOT Website</a> 
		- Required for file input and output
	-  Geant4
		- <a href="http://geant4.cern.ch/">Geant4 Website</a>
		- Required for the simulation libraries
		- Requires use of the following libraries:
			- G4EMLOW6.32
			- G4PII1.3
			- RadioactiveDecay3.6
			- G4NDL4.2
			- G4SAIDDATA1.1
			- RealSurface1.0
			- G4NEUTRONXS1.2
			- PhotonEvaporation2.3
		- It is advised to use CMake to build Geant4 as the CMake generated project files will make finding Geant4 easier when building NeuFlux
	-  CMake
		- <a href="http://www.cmake.org/">CMake Website</a>
		- Required for building the program


	---

	\section building Building

	In order to Build the program
	
	---
	\section running Running

	In order to run
	
	---
*/