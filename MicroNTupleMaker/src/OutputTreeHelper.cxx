/* =============================================================================================== */
void MicroNTupleMaker::DeclareOutputTrees(){
	treenames = {"PostSel"};

	vector<string> myvars = {
        	 
		// -- EventLevel -- //
		"runNumber", "eventNumber","mcEventWeight","weight","sumw",

		// -- JetLevel -- //
		"n_jets",
        	"jet1_pt", "jet1_eta", "jet1_phi", "jet1_E", 
        	"jet2_pt", "jet2_eta", "jet2_phi", "jet2_E", 
		"jet1_DL1dv01", "jet1_GN1", "jet1_EMFrac", "jet1_FracSamplingMax", "jet1_Width",
		"jet2_DL1dv01", "jet2_GN1", "jet2_EMFrac", "jet2_FracSamplingMax", "jet2_Width",
       		"jet1_NumTrkPt500PV", "jet1_NumTrkPt1000PV", "jet1_SumPtTrkPt500PV", "jet1_TrackWidthPt1000PV",
       		"jet2_NumTrkPt500PV", "jet2_NumTrkPt1000PV", "jet2_SumPtTrkPt500PV", "jet2_TrackWidthPt1000PV",

		// -- Jet Substructure calculations -- //
		"jet1_tau1", "jet1_tau2", "jet1_tau3", "jet1_tau21", "jet1_tau32", 
		"jet2_tau1", "jet2_tau2", "jet2_tau3", "jet2_tau21", "jet2_tau32", 
		"jet1_ECF_C2", "jet1_ECF_D2", 
		"jet2_ECF_C2", "jet2_ECF_D2", 
		"jet1_ktsplit12", "jet1_ktsplit23", "jet1_qw",
		"jet2_ktsplit12", "jet2_ktsplit23", "jet2_qw",

		// -- Jet Calculations -- //
		"maxphi_minphi", "dphi_min", "dphi_max",
		"dphi_MET_j1j2",
                "pt_balance_12", //"pt_balance_sa",
                "mjj_12", "mT_jj", 
		"mT_jj_neg", "met_jj_neg",
		//"mJJ_12", "mT_JJ",
		"dR_12", "deta_12", "dphi_12",
		"deltaY_12", //"deltaY_sa",
		"hT", "rT",
		"aplanarity", "sphericity", "sphericity_T",	

		// -- MET -- //
        	"met_met", "met_phi"
        };

	vector<string> myvars_string = {
		"year"
	};
	
	vector<string> myvars_vector = {
		"all_jets_pt",
		"all_jets_eta",
		"all_jets_phi",
		"all_jets_E",
		"all_jets_NumTrkPt500PV",
		"all_jets_NumTrkPt1000PV",
		//"all_jets_SumPtTrkPt500PV",
		//"all_jets_TrackWidthPt1000PV",
		"all_jets_Width",
		//"all_jets_EMFrac",
		//"all_jets_DL1dv01",
		//"all_jets_GN1",
		//"all_jets_FracSamplingMax"
		//"all_fatjets_pt",
		//"all_fatjets_eta",
		//"all_fatjets_phi",
		//"all_fatjets_m",
	};


	for (auto treename: treenames){
		tree_output[treename] = new TTree( Form("%s",treename.c_str()), Form("%s",treename.c_str()) );
		
                //for( auto var: myvars_vector ) 
		//	tree_output[treename]->Branch( Form("%s",var.c_str()), &tree_output_vars_vector[var] );

                for( auto var: myvars_string ) 
			tree_output[treename]->Branch( Form("%s",var.c_str()), &tree_output_vars_string[var] );

		for (auto var: myvars)
			tree_output[treename]->Branch( Form("%s",var.c_str()), &tree_output_vars[var]);

	}
}

/* =============================================================================================== */
void MicroNTupleMaker::FillOutputTrees(string treename){

	if (debug) cout << "MicroNTupleMaker::FillOutputTrees()" << endl;

	tree_output_vars_string["year"] = year_mc;

	//tree_output_vars_vector["all_jets_pt"] = jet_pt;
	//tree_output_vars_vector["all_jets_eta"] = jet_eta;
	//tree_output_vars_vector["all_jets_phi"] = jet_phi;
	//tree_output_vars_vector["all_jets_E"]= jet_E;	
	//tree_output_vars_vector["all_jets_NumTrkPt500PV"]= jet_NumTrkPt500PV;	
	//tree_output_vars_vector["all_jets_NumTrkPt1000PV"]= jet_NumTrkPt1000PV;	
	//tree_output_vars_vector["all_jets_SumPtTrkPt500PV"]= jet_SumPtTrkPt500PV;	
	//tree_output_vars_vector["all_jets_TrackWidthPt1000PV"]= jet_TrackWidthPt1000PV;	
	//tree_output_vars_vector["all_jets_Width"]= jet_Width;	
	//tree_output_vars_vector["all_jets_EMFrac"]= jet_EMFrac;	
	//tree_output_vars_vector["all_jets_DL1dv01"]= jet_DL1dv01;	
	//tree_output_vars_vector["all_jets_GN1"]= jet_GN1;	
	//tree_output_vars_vector["all_jets_FracSamplingMax"]= jet_FracSamplingMax;	
	
	tree_output_vars["runNumber"] = runNumber;
	tree_output_vars["eventNumber"] = eventNumber;
	tree_output_vars["mcEventWeight"] = mcEventWeight;
	tree_output_vars["weight"] = mcEventWeight*weight_scale;
	tree_output_vars["sumw"] = sumw;

	tree_output_vars["n_jets"] = njet;
	tree_output_vars["jet1_pt"] = jet_pt->at(0); // GeV
	tree_output_vars["jet1_eta"] = jet_eta->at(0);
	tree_output_vars["jet1_phi"] = jet_phi->at(0);
	tree_output_vars["jet1_E"] = jet_E->at(0);

        tree_output_vars["jet1_DL1dv01"] = jet_DL1dv01->at(0);
        tree_output_vars["jet1_GN1"] = jet_GN1->at(0);
        tree_output_vars["jet1_SumPtTrkPt500PV"] = jet_SumPtTrkPt500PV->at(0);
        tree_output_vars["jet1_NumTrkPt500PV"] = jet_NumTrkPt500PV->at(0);
        tree_output_vars["jet1_TrackWidthPt1000PV"] = jet_TrackWidthPt1000PV->at(0);
        tree_output_vars["jet1_NumTrkPt1000PV"] = jet_NumTrkPt1000PV->at(0);
        tree_output_vars["jet1_EMFrac"] = jet_EMFrac->at(0);
        tree_output_vars["jet1_FracSamplingMax"] = jet_FracSamplingMax->at(0);
        tree_output_vars["jet1_Width"] = jet_Width->at(0);
	if(leadjet_NsubJettiness_vars.size() > 0){
	  tree_output_vars["jet1_tau1"] = leadjet_NsubJettiness_vars.at(0);
	  tree_output_vars["jet1_tau2"] = leadjet_NsubJettiness_vars.at(1);
	  tree_output_vars["jet1_tau3"] = leadjet_NsubJettiness_vars.at(2);
	  tree_output_vars["jet1_tau21"] = leadjet_NsubJettiness_vars.at(3);
	  tree_output_vars["jet1_tau32"] = leadjet_NsubJettiness_vars.at(4);
	}else{
	tree_output_vars["jet1_tau1"] = -999;
	tree_output_vars["jet1_tau2"] = -999;
	tree_output_vars["jet1_tau3"] = -999;
	tree_output_vars["jet1_tau21"] = -999;
	tree_output_vars["jet1_tau32"] = -999;
	}
	if(leadjet_ECFs.size() > 0){
	  tree_output_vars["jet1_ECF_C2"] = leadjet_ECFs.at(0);
	  tree_output_vars["jet1_ECF_D2"] = leadjet_ECFs.at(1);
	}else{
	  tree_output_vars["jet1_ECF_C2"] = -999;
	  tree_output_vars["jet1_ECF_D2"] =-999;
	}
	if(leadjet_ktscale.size() > 0){
	  tree_output_vars["jet1_ktsplit12"] = leadjet_ktscale.at(0);
	  tree_output_vars["jet1_ktsplit23"] = leadjet_ktscale.at(1);
	}else{
	  tree_output_vars["jet1_ktsplit12"] = -999;
	  tree_output_vars["jet1_ktsplit23"] = -999;
	}
	tree_output_vars["jet1_qw"] = leadjet_qw;
	if (jet_pt->size() >= 2) {
		tree_output_vars["jet2_pt"] = jet_pt->at(1);
		tree_output_vars["jet2_eta"] = jet_eta->at(1);
		tree_output_vars["jet2_phi"] = jet_phi->at(1);
		tree_output_vars["jet2_E"] = jet_E->at(1);

        	tree_output_vars["jet2_DL1dv01"] = jet_DL1dv01->at(1);
        	tree_output_vars["jet2_GN1"] = jet_GN1->at(1);
        	tree_output_vars["jet2_SumPtTrkPt500PV"] = jet_SumPtTrkPt500PV->at(1);
        	tree_output_vars["jet2_NumTrkPt500PV"] = jet_NumTrkPt500PV->at(1);
        	tree_output_vars["jet2_TrackWidthPt1000PV"] = jet_TrackWidthPt1000PV->at(1);
        	tree_output_vars["jet2_NumTrkPt1000PV"] = jet_NumTrkPt1000PV->at(1);
        	tree_output_vars["jet2_EMFrac"] = jet_EMFrac->at(1);
        	tree_output_vars["jet2_FracSamplingMax"] = jet_FracSamplingMax->at(1);
        	tree_output_vars["jet2_Width"] = jet_Width->at(1);
		if(subleadjet_NsubJettiness_vars.size() > 0){
		  tree_output_vars["jet2_tau1"] = subleadjet_NsubJettiness_vars.at(0);
		  tree_output_vars["jet2_tau2"] = subleadjet_NsubJettiness_vars.at(1);
		  tree_output_vars["jet2_tau3"] = subleadjet_NsubJettiness_vars.at(2);
		  tree_output_vars["jet2_tau21"] = subleadjet_NsubJettiness_vars.at(3);
		  tree_output_vars["jet2_tau32"] = subleadjet_NsubJettiness_vars.at(4);
		}else{
		  tree_output_vars["jet2_tau1"] = -999;
		  tree_output_vars["jet2_tau2"] = -999;
		  tree_output_vars["jet2_tau3"] = -999;
		  tree_output_vars["jet2_tau21"] = -999;
		  tree_output_vars["jet2_tau32"] = -999;
		}
		if(subleadjet_ECFs.size() > 0){
		  tree_output_vars["jet2_ECF_C2"] = subleadjet_ECFs.at(0);
		  tree_output_vars["jet2_ECF_D2"] = subleadjet_ECFs.at(1);
		}else{
		  tree_output_vars["jet2_ECF_C2"] = -999;
		  tree_output_vars["jet2_ECF_D2"] =-999;
		}
		if(subleadjet_ktscale.size() > 0){
		  tree_output_vars["jet2_ktsplit12"] = subleadjet_ktscale.at(0);
		  tree_output_vars["jet2_ktsplit23"] = subleadjet_ktscale.at(1);
		}else{
		  tree_output_vars["jet2_ktsplit12"] = -999;
		  tree_output_vars["jet2_ktsplit23"] = -999;
		}
		tree_output_vars["jet2_qw"] = subleadjet_qw;
	
	} else {
	  tree_output_vars["jet2_pt"] = -999; 
	  tree_output_vars["jet2_eta"] = -999;
	  tree_output_vars["jet2_phi"] = -999;
	  tree_output_vars["jet2_E"] = -999;
	  
	  tree_output_vars["jet2_DL1dv01"] = -999;
	  tree_output_vars["jet2_GN1"] = -999;
	  tree_output_vars["jet2_SumPtTrkPt500PV"] = -999;
	  tree_output_vars["jet2_NumTrkPt500PV"] = -999;
	  tree_output_vars["jet2_TrackWidthPt1000PV"] = -999;
	  tree_output_vars["jet2_NumTrkPt1000PV"] = -999;
	  tree_output_vars["jet2_EMFrac"] = -999;
	  tree_output_vars["jet2_FracSamplingMax"] = -999;
	  tree_output_vars["jet2_Width"] = -999;
	  tree_output_vars["jet2_tau1"] = -999;
	  tree_output_vars["jet2_tau2"] = -999;
	  tree_output_vars["jet2_tau3"] = -999;
	  tree_output_vars["jet2_tau21"] = -999;
	  tree_output_vars["jet2_tau32"] = -999;
	  tree_output_vars["jet2_ECF_C2"] = -999;
	  tree_output_vars["jet2_ECF_D2"] = -999;
	  tree_output_vars["jet2_ktsplit12"] = -999;
	  tree_output_vars["jet2_ktsplit23"] = -999;
	  tree_output_vars["jet2_qw"] = -999;
	}

	tree_output_vars["met_met"] = metFinalClus;
	tree_output_vars["met_phi"] = metFinalClusPhi;
	tree_output_vars["hT"] = hT;
	tree_output_vars["rT"] = rT;

	tree_output_vars["maxphi_minphi"] = maxphi_minphi;
	tree_output_vars["dphi_MET_j1j2"] = dphi_MET_j1j2;
        tree_output_vars["pt_balance_12"] = pt_balance_12;

        tree_output_vars["mjj_12"] = mjj_12;
        tree_output_vars["mT_jj"] = mT_jj;
        tree_output_vars["mT_jj_neg"] = mT_jj_neg;
        tree_output_vars["met_jj_neg"] = met_jj_neg;

	tree_output_vars["dR_12"] = dR_12;
	tree_output_vars["deta_12"] = deta_12;
        tree_output_vars["deltaY_12"] = deltaY_12;
        tree_output_vars["dphi_12"] = dphi_12;
	tree_output_vars["dphi_min"] = dphi_min;
	tree_output_vars["dphi_max"] = dphi_max;
	tree_output_vars["aplanarity"] = aplanarity;
	tree_output_vars["sphericity"] = sphericity;
	tree_output_vars["sphericity_T"] = sphericity_T;


	tree_output[treename]->Fill();
}


/* ====================================================================================================================== */
void MicroNTupleMaker::WriteOutputTrees(){

        if( debug ) cout<<"MicroNTupleMaker::WriteOutputTrees()"<<endl;

        cout<<"Writing Tree(s)..."<<endl;

        for(map<string,TTree*>::iterator it = tree_output.begin(); it != tree_output.end(); ++it){
                tree_output[it->first]->Write("", TObject::kOverwrite);
        }

}
