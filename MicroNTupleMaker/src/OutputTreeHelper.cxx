/* =============================================================================================== */
void MicroNTupleMaker::DeclareOutputTrees(){
	treenames = {"PostSel"};

	vector<string> myvars = {
        	 
		// -- EventLevel -- //
		"runNumber", "eventNumber","mcEventWeight",

		// -- JetLevel -- //
		"n_r04_jets", "n_r10_jets",
		"maxphi_minphi", "dphi_min", "dphi_max",
                "pt_balance_12", "pt_balance_sa",
                "mjj_12", "mjj_sa",
        	"jet1_pt", "jet1_eta", "jet1_phi", "jet1_m", "jet1_nConstituents",
        	"jet2_pt", "jet2_eta", "jet2_phi", "jet2_m", "jet2_nConstituents",
        	"r04_jet1_pt", "r04_jet1_eta", "r04_jet1_phi", "r04_jet1_E", //"jet1_nConstituents",
        	"r04_jet2_pt", "r04_jet2_eta", "r04_jet2_phi", "r04_jet2_E", //"jet2_nConstituents",
        	"jet_svj_pt", "jet_svj_eta", "jet_svj_phi", "jet_svj_m", "jet_svj_n", "jet_svj_nConstituents",
        	"jet_asvj_pt", "jet_asvj_eta", "jet_asvj_phi", "jet_asvj_m", "jet_asvj_n", "jet_asvj_nConstituents",
        	//"jet_xd1_matched_pt", "jet_xd1_matched_eta", "jet_xd1_matched_phi", "jet_xd1_matched_m", "jet_xd1_matched_n", "jet_xd1_matched_nConstituents",
        	//"jet_xd2_matched_pt", "jet_xd2_matched_eta", "jet_xd2_matched_phi", "jet_xd2_matched_m", "jet_xd2_matched_n", "jet_xd2_matched_nConstituents",
		"jet1_mT", "jet1_Split12", "jet1_Split23", "jet1_tau32", "jet1_C2", "jet1_D2", "jet1_nTracks",
		"jet2_mT", "jet2_Split12", "jet2_Split23", "jet2_tau32", "jet2_C2", "jet2_D2", "jet2_nTracks",
		"jet_asvj_mT", "jet_asvj_Split12", "jet_asvj_Split23", "jet_asvj_tau32", "jet_asvj_C2", "jet_asvj_D2", "jet_asvj_nTracks",
		"jet_svj_mT", "jet_svj_Split12", "jet_svj_Split23", "jet_svj_tau32", "jet_svj_C2", "jet_svj_D2", "jet_svj_nTracks",

		// -- MET -- //
		"MET_TruthMET_TruthPhi","MET_TruthMET_TruthSumEt",
        	"met_met", "met_phi"
        };
	
	for (auto treename: treenames){
		tree_output[treename] = new TTree( Form("%s",treename.c_str()), Form("%s",treename.c_str()) );
		
		for (auto var: myvars) tree_output[treename]->Branch( Form("%s",var.c_str()), &tree_output_vars[var]);
	}
}

/* =============================================================================================== */
void MicroNTupleMaker::FillOutputTrees(string treename){

	if (debug) cout << "MicroNTupleMaker::FillOutputTrees()" << endl;

	tree_output_vars["runNumber"] = runNumber;
	tree_output_vars["eventNumber"] = eventNumber;
	tree_output_vars["mcEventWeight"] = mcEventWeight;

	tree_output_vars["n_r04_jets"] = na4_pflowjets;
	tree_output_vars["n_r10_jets"] = na10_lctopojets;

	tree_output_vars["jet1_pt"] = a10_lctopojets_pt->at(0); // GeV
	tree_output_vars["jet1_eta"] = a10_lctopojets_eta->at(0);
	tree_output_vars["jet1_phi"] = a10_lctopojets_phi->at(0);
	tree_output_vars["jet1_m"] = a10_lctopojets_m->at(0);
	tree_output_vars["jet1_mT"] = jet1_mT;
	tree_output_vars["jet1_Split12"] = a10_lctopojets_Split12->at(0);
	tree_output_vars["jet1_Split23"] = a10_lctopojets_Split23->at(0);
	tree_output_vars["jet1_tau32"] = a10_lctopojets_tau32_wta->at(0);
	tree_output_vars["jet1_C2"] = a10_lctopojets_C2->at(0);
	tree_output_vars["jet1_D2"] = a10_lctopojets_D2->at(0);
	tree_output_vars["jet1_nTracks"] = a10_lctopojets_nTracks->at(0);

	tree_output_vars["jet2_pt"] = a10_lctopojets_pt->at(1);
	tree_output_vars["jet2_eta"] = a10_lctopojets_eta->at(1);
	tree_output_vars["jet2_phi"] = a10_lctopojets_phi->at(1);
	tree_output_vars["jet2_m"] = a10_lctopojets_m->at(1);
	tree_output_vars["jet2_mT"] = jet2_mT;
	tree_output_vars["jet2_Split12"] = a10_lctopojets_Split12->at(1);
	tree_output_vars["jet2_Split23"] = a10_lctopojets_Split23->at(1);
	tree_output_vars["jet2_tau32"] = a10_lctopojets_tau32_wta->at(1);
	tree_output_vars["jet2_C2"] = a10_lctopojets_C2->at(1);
	tree_output_vars["jet2_D2"] = a10_lctopojets_D2->at(1);
	tree_output_vars["jet2_nTracks"] = a10_lctopojets_nTracks->at(1);
      
        tree_output_vars["jet_svj_n"] = n_svj;
	tree_output_vars["jet_svj_pt"] = a10_lctopojets_pt->at(n_svj);
	tree_output_vars["jet_svj_eta"] = a10_lctopojets_eta->at(n_svj);
	tree_output_vars["jet_svj_phi"] = a10_lctopojets_phi->at(n_svj);
	tree_output_vars["jet_svj_m"] = a10_lctopojets_m->at(n_svj);
	tree_output_vars["jet_svj_mT"] = jet_svj_mT;
	tree_output_vars["jet_svj_Split12"] = a10_lctopojets_Split12->at(n_svj);
	tree_output_vars["jet_svj_Split23"] = a10_lctopojets_Split23->at(n_svj);
	tree_output_vars["jet_svj_tau32"] = a10_lctopojets_tau32_wta->at(n_svj);
	tree_output_vars["jet_svj_C2"] = a10_lctopojets_C2->at(n_svj);
	tree_output_vars["jet_svj_D2"] = a10_lctopojets_D2->at(n_svj);
	tree_output_vars["jet_svj_nTracks"] = a10_lctopojets_nTracks->at(n_svj);

        tree_output_vars["jet_asvj_n"] = n_asvj;
	tree_output_vars["jet_asvj_pt"] = a10_lctopojets_pt->at(n_asvj);
	tree_output_vars["jet_asvj_eta"] = a10_lctopojets_eta->at(n_asvj);
	tree_output_vars["jet_asvj_phi"] = a10_lctopojets_phi->at(n_asvj);
	tree_output_vars["jet_asvj_m"] = a10_lctopojets_m->at(n_asvj);
	tree_output_vars["jet_asvj_mT"] = jet_asvj_mT;
	tree_output_vars["jet_asvj_Split12"] = a10_lctopojets_Split12->at(n_asvj);
	tree_output_vars["jet_asvj_Split23"] = a10_lctopojets_Split23->at(n_asvj);
	tree_output_vars["jet_asvj_tau32"] = a10_lctopojets_tau32_wta->at(n_asvj);
	tree_output_vars["jet_asvj_C2"] = a10_lctopojets_C2->at(n_asvj);
	tree_output_vars["jet_asvj_D2"] = a10_lctopojets_D2->at(n_asvj);
	tree_output_vars["jet_asvj_nTracks"] = a10_lctopojets_nTracks->at(n_asvj);

	tree_output_vars["r04_jet1_pt"] = a4_pflowjets_pt->at(0); // GeV
	tree_output_vars["r04_jet1_eta"] = a4_pflowjets_eta->at(0);
	tree_output_vars["r04_jet1_phi"] = a4_pflowjets_phi->at(0);
	tree_output_vars["r04_jet1_e"] = a4_pflowjets_E->at(0);
	tree_output_vars["r04_jet2_pt"] = a4_pflowjets_pt->at(1);
	tree_output_vars["r04_jet2_eta"] = a4_pflowjets_eta->at(1);
	tree_output_vars["r04_jet2_phi"] = a4_pflowjets_phi->at(1);
	tree_output_vars["r04_jet2_e"] = a4_pflowjets_E->at(1);

	tree_output_vars["met_met"] = metFinalTrkSumEt;
	tree_output_vars["met_phi"] = metFinalTrkPhi;
	tree_output_vars["MET_TruthMET_TruthSumEt"] = MET_TruthMET_TruthSumEt;
	tree_output_vars["MET_TruthMET_TruthPhi"] = MET_TruthMET_TruthPhi;

	tree_output_vars["maxphi_minphi"] = maxphi_minphi;
        tree_output_vars["pt_balance_12"] = pt_balance_12;
        tree_output_vars["pt_balance_sa"] = pt_balance_sa;
        tree_output_vars["mjj_12"] = mjj_12;
        tree_output_vars["mjj_sa"] = mjj_sa;
	tree_output_vars["dphi_min"] = dphi_min;
	tree_output_vars["dphi_max"] = dphi_max;

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
