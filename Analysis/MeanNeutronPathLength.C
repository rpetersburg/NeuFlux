/*
	\file MeanNeutronPathLength.C
	This is a basic analysis to pull out the mean path length
*/


void MeanNeutronPathLength(TString input="NeuFlux_1392233522_0.root")
{
	TFile* inputFile = new TFile(input,"READ");
	//pull out the relevent tree

	TTree* trackingTree = (TTree*) inputFile->Get("NeuTrackingAction");
	if(!trackingTree)
	{
		std::cout<<"No Tracking Tree in input File. Exiting..."<<std::endl;
		exit(-1);
	}

	//declare variables, we want to analyze
	Double_t preX, preY, preZ, postX, postY, postZ;
	//Similarly, the cuts need to be delt with
	Int_t pdgEncoding;

	//Setup some containers to store these in
	std::vector<double> length;
	TH1D* lengths = new TH1D("lengthscm","lengthscm", 10000, 0, 100);
	double mean = 0.0;

	//Get the corresponding branches

	TBranch* PreX = trackingTree->GetBranch("TrackPreX");
	PreX->SetAddress(&preX);
	TBranch* PreY = trackingTree->GetBranch("TrackPreY");
	PreX->SetAddress(&preY);
	TBranch* PreZ = trackingTree->GetBranch("TrackPreZ");
	PreX->SetAddress(&preZ);

	TBranch* PostX = trackingTree->GetBranch("TrackPostX");
	PreX->SetAddress(&postX);
	TBranch* PostY = trackingTree->GetBranch("TrackPostX");
	PreX->SetAddress(&postY);
	TBranch* PostZ = trackingTree->GetBranch("TrackPostX");
	PreX->SetAddress(&postZ);

	TBranch* PDGBranch = trackingTree->GetBranch("TrackPDGEncoding");
	PDGBranch->SetAddress(&pdgEncoding);

	//How many of these are there?
	Int_t nEvents = trackingTree->GetEntries();


	//This is the main analysis loop	
	for(Int_t i =0; i<nEvents; ++i)
	{
		trackingTree->GetEvent(i);//read in the tree branches into memory
		//now the values are stored in the values given above.
		if(pdgEncoding !=2112)//cut on non-neutrons
		{
			//std::cout<<"Not a Neutron"<<std::endl;
			continue;
		}
		std::cout<<std::setprecision(15)<<preX<<", "<<preY<<", "<<preZ<<", "<<postX<<", "<<postY<<", "<<postZ<<std::endl;

		double value = TMath::Sqrt( (postX-preX)*(postX-preX) + (postY-preY)*(postY-preY) + (postZ-preZ)*(postZ-preZ)     );

		length.push_back(value);
		lengths->Fill(value);
		mean+=value;
	}

	lengths->Draw();
	std::cout<<std::setprecision(15)<<"Mean: "<<mean/( (double) length.size())<<std::endl;


}