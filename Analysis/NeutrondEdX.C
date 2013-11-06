void NeutrondEdX(TString pattern = "NeuFlux_XXXX_")
{
	//prepare the output file
	TFile* outputFile = new TFile("analysisOutput.root","RECREATE");



	//for(Int_t i=0; i<1; i++)
	{
		Int_t i =0;
		TString name = pattern;
		name+=i;
		name+=".root";

		TFile* inputFile = new TFile(name,"READ");
		if( inputFile->IsZombie() )
			continue;

		//find all of the neutron tack IDS
		std::vector<Int_t> neutronTrackIDs;
		{
			TTree* trackingTree = (TTree*) inputFile->Get("NeuTrackingAction");
			if(!trackingTree)
			{
				std::cout<<"No Tracking Tree in input File. Exiting..."<<std::endl;
				continue;
			}	
			Int_t trackID, pdgCode;
			TBranch* IDBranch=trackingTree->GetBranch("TrackID");
			IDBranch->SetAddress(&trackID);
			TBranch* PDGBranch=trackingTree->GetBranch("TrackPDGEncoding");
			PDGBranch->SetAddress(&pdgCode);

			Int_t nEvents = trackingTree->GetEntries();
			//This is the main analysis loop	
			for(Int_t j =0; j<nEvents; ++j)
			{
				trackingTree->GetEvent(j);
				if(pdgCode==2112)
					neutronTrackIDs.push_back(trackID);
			}

		}

		//pull out the relevent tree
		//needs to have the highest cycle, due to ecessively large size		
		TTree* trackingTree = (TTree*) inputFile->Get("NeuSteppingAction");
		if(!trackingTree)
		{
			std::cout<<"No Stepping Tree in input File. Exiting..."<<std::endl;
			continue;
		}

		//declare variables, we want to analyze
		Double_t stepLength, preE, postE;
		Int_t trackID;
		//Similarly, the cuts need to be delt with
		Int_t pdgEncoding;
		TString outHistName = "lengthsmm";
		outHistName+=i;	
		TH1D* lengths = new TH1D(outHistName,outHistName, 10000, 0, 2000);
		outHistName = "energiesMeV";
		outHistName+=i;
		TH1D* energies = new TH1D(outHistName,outHistName, 10000, 0, 2000);
		outHistName = "dEdX";
		outHistName+=i;
		TH1D* differential = new TH1D(outHistName,outHistName, 10000, 0, 2000);
		//Get the corresponding branches

		TBranch* lengthBranch = trackingTree->GetBranch("StepLength");
		lengthBranch->SetAddress(&stepLength);
		TBranch* preEnergyBranch = trackingTree->GetBranch("TotalEnergyDeposit");
		preEnergyBranch->SetAddress(&preE);
		TBranch* postEnergyBranch = trackingTree->GetBranch("PostKinE");
		postEnergyBranch->SetAddress(&postE);
		TBranch* trackIDBranch = trackingTree->GetBranch("TrackID");
		postEnergyBranch->SetAddress(&trackID);

		//How many of these are there?
		Int_t nEvents = trackingTree->GetEntries();
		//This is the main analysis loop	
		//std::vector<Int_t>:iterator neutronIDIt = neutronTrackIDs.begin();
		for(Int_t j =0; j<nEvents; ++j)
		{
			trackingTree->GetEvent(j);//read in the tree branches into memory
			//now the values are stored in the values given above.

			//if the track id is the same as the 
			/*
			Int_t theNextID = neutronIDIt++;
			if(trackID != neutronTrackIDs.front()  && trackID== theNextID )
				neutronTrackIDs.pop_front();
			if(trackID !=  neutronTrackIDs.front()  )
				continue;
				*/

			if(trackID==0)
			{
				double value = TMath::Abs(preE);//TMath::Abs(postE-preE) ;
				if( TMath::IsNaN(value) ) continue;
				lengths->Fill(stepLength);
				energies->Fill(value);
				if(stepLength!=0.0)
					differential->Fill(value/stepLength);

			}
		}

		/*
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
		*/
		TCanvas* c1 = new TCanvas("c1","c1",1);
		lengths->Draw();
		TCanvas* c2 = new TCanvas("c2","c2",1);
		energies->Draw();
		TCanvas* c3 = new TCanvas("c3","c3",1);
		differential->Draw();
	}

/*
	TGraphErrors* graph = new TGraphErrors(n_points, energies, decayRate, energyError, decayError);
	graph->Write();


	outputFile->Close();
	*/

}