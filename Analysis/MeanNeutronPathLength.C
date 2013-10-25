/*!
	\file MeanNeutronPathLength.C
	This is a basic analysis to pull out the mean path length

	Output of this will contain a histogram for every
*/


void MeanNeutronPathLength(TString input="NeuFlux_XXXX_")
{
	//prepare the output file
	TFile* outputFile = new TFile("analysisOutput.root","RECREATE");

	double energies[100];//this is in MeV
	double energyError[100];
	double decayRate[100];
	double decayError[100];
	int n_points=0;

	for(Int_t i=0; i<100; i++)
	{
		energies[i]=i+1;//keep this in MeV
		energyError[i]=0;
		decayRate[i]=0;
		decayError[i]=0;
		TString name = input;
		name+=i;
		name+=".root";

		TFile* inputFile = new TFile(name,"READ");
		if( inputFile->IsZombie() )
			continue;

		//pull out the relevent tree
		//needs to have the highest cycle, due to ecessively large size		
		TTree* trackingTree = (TTree*) inputFile->Get("NeuTrackingAction");
		if(!trackingTree)
		{
			std::cout<<"No Tracking Tree in input File. Exiting..."<<std::endl;
			continue;
		}

		//declare variables, we want to analyze
		Double_t preX, preY, preZ, postX, postY, postZ;
		//Similarly, the cuts need to be delt with
		Int_t pdgEncoding;
		TString outHistName = "lengthscm";
		outHistName+=energies[i];	
		TH1D* lengths = new TH1D(outHistName,outHistName, 10000, 0, 2000);
		//Get the corresponding branches

		TBranch* PreX = trackingTree->GetBranch("TrackPreX");
		PreX->SetAddress(&preX);
		TBranch* PreY = trackingTree->GetBranch("TrackPreY");
		PreX->SetAddress(&preY);
		TBranch* PreZ = trackingTree->GetBranch("TrackPreZ");
		PreX->SetAddress(&preZ);

		TBranch* PostX = trackingTree->GetBranch("TrackPostX");
		PreX->SetAddress(&postX);
		TBranch* PostY = trackingTree->GetBranch("TrackPostY");
		PreX->SetAddress(&postY);
		TBranch* PostZ = trackingTree->GetBranch("TrackPostZ");
		PreX->SetAddress(&postZ);

		TBranch* PDGBranch = trackingTree->GetBranch("TrackPDGEncoding");
		PDGBranch->SetAddress(&pdgEncoding);

		//How many of these are there?
		Int_t nEvents = trackingTree->GetEntries();
		//This is the main analysis loop	
		for(Int_t j =0; j<nEvents; ++j)
		{
			trackingTree->GetEvent(j);//read in the tree branches into memory
			//now the values are stored in the values given above.
			if(pdgEncoding !=2112)//cut on non-neutrons
			{
			}
			else
			{
				double value = TMath::Sqrt( (postX-preX)*(postX-preX) + (postY-preY)*(postY-preY) + (postZ-preZ)*(postZ-preZ)     );
				if( TMath::IsNaN(value) ) continue;
				lengths->Fill(value);
			}
		}

		lengths->Fit("expo","Q");
		std::cout<<"Fitting Energy: "<<energies[i]<<std::endl;
		TF1* expoFit = lengths->GetFunction("expo");
		decayRate[i] = expoFit->GetParameter(1)!=0.0 ? -1.0/expoFit->GetParameter(1) : 0.0;
		decayError[i] = TMath::Abs( decayRate[i] * expoFit->GetParError(1)/expoFit->GetParameter(1) );

		if( TMath::IsNaN( decayRate[i] ) )
			decayRate[i]=0;
		if( TMath::IsNaN( decayError[i] ) )
			decayError[i] = 100;


		decayError[i] *=decayError[i];
		outputFile->cd();
		lengths->Write();
		n_points++;
		std::cout<<"\t\tValue: "<<decayRate[i]<<" +/-"<<decayError[i]<<std::endl;
	}

	TGraphErrors* graph = new TGraphErrors(n_points, energies, decayRate, energyError, decayError);
	graph->Write();


	outputFile->Close();

}