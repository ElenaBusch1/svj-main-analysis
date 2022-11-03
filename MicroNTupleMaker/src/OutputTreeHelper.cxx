/* =============================================================================================== */
void MicroNTupleMaker::DeclareOutputTrees(){
	treenames = {"PostSel"};

	vector<string> myvars = {
        	 
		// -- EventLevel -- //
		"runNumber", "eventNumber","mcEventWeight","weight","SumW",

		// -- JetLevel -- //
		"n_jets",
        	"jet1_pt", "jet1_eta", "jet1_phi", "jet1_E", 
        	"jet2_pt", "jet2_eta", "jet2_phi", "jet2_E", 
        	//"jet_svj_pt", "jet_svj_eta", "jet_svj_phi", "jet_svj_m", "jet_svj_n", "jet_svj_nConstituents",
        	//"jet_asvj_pt", "jet_asvj_eta", "jet_asvj_phi", "jet_asvj_m", "jet_asvj_n", "jet_asvj_nConstituents",
        	//"jet_xd1_matched_pt", "jet_xd1_matched_eta", "jet_xd1_matched_phi", "jet_xd1_matched_m", "jet_xd1_matched_n", "jet_xd1_matched_nConstituents",
        	//"jet_xd2_matched_pt", "jet_xd2_matched_eta", "jet_xd2_matched_phi", "jet_xd2_matched_m", "jet_xd2_matched_n", "jet_xd2_matched_nConstituents",
		//"jet1_Split12", "jet1_Split23", "jet1_tau32", "jet1_C2", "jet1_D2", "jet1_nTracks",
		//"jet2_Split12", "jet2_Split23", "jet2_tau32", "jet2_C2", "jet2_D2", "jet2_nTracks",
		//"jet_asvj_mT", "jet_asvj_Split12", "jet_asvj_Split23", "jet_asvj_tau32", "jet_asvj_C2", "jet_asvj_D2", "jet_asvj_nTracks",
		//"jet_svj_mT", "jet_svj_Split12", "jet_svj_Split23", "jet_svj_tau32", "jet_svj_C2", "jet_svj_D2", "jet_svj_nTracks",

		// -- Jet Calculations -- //
		"maxphi_minphi", "dphi_min", "dphi_max",
                "pt_balance_12", //"pt_balance_sa",
                "mjj_12", "mT_jj", 
		"dR_12", "deta_12",
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
	};

	for (auto treename: treenames){
		tree_output[treename] = new TTree( Form("%s",treename.c_str()), Form("%s",treename.c_str()) );
		
                for( auto var: myvars_vector ) 
			tree_output[treename]->Branch( Form("%s",var.c_str()), &tree_output_vars_vector[var] );

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

	tree_output_vars_vector["all_jets_pt"] = jet_pt;
	tree_output_vars_vector["all_jets_eta"] = jet_eta;
	tree_output_vars_vector["all_jets_phi"] = jet_phi;
	tree_output_vars_vector["all_jets_E"]= jet_E;	

	tree_output_vars["runNumber"] = runNumber;
	tree_output_vars["eventNumber"] = eventNumber;
	tree_output_vars["mcEventWeight"] = mcEventWeight;
	tree_output_vars["weight"] = mcEventWeight*weight_scale;
	tree_output_vars["SumW"] = sumw;

	tree_output_vars["n_jets"] = njet;

	tree_output_vars["jet1_pt"] = jet_pt->at(0); // GeV
	tree_output_vars["jet1_eta"] = jet_eta->at(0);
	tree_output_vars["jet1_phi"] = jet_phi->at(0);
	tree_output_vars["jet1_E"] = jet_E->at(0);
	tree_output_vars["jet2_pt"] = jet_pt->at(1);
	tree_output_vars["jet2_eta"] = jet_eta->at(1);
	tree_output_vars["jet2_phi"] = jet_phi->at(1);

	tree_output_vars["met_met"] = metFinalClus;
	tree_output_vars["met_phi"] = metFinalClusPhi;
	tree_output_vars["hT"] = hT;
	tree_output_vars["rT"] = rT;

	tree_output_vars["maxphi_minphi"] = maxphi_minphi;
        tree_output_vars["pt_balance_12"] = pt_balance_12;
        tree_output_vars["mjj_12"] = mjj_12;
        tree_output_vars["mT_jj"] = mT_jj;
	tree_output_vars["dR_12"] = dR_12;
	tree_output_vars["deta_12"] = deta_12;
        tree_output_vars["deltaY_12"] = deltaY_12;
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
