#include "fastjet/ClusterSequence.hh"
#include "fastjet/PseudoJet.hh"
//#include "src/JetSubstructure.cxx"
void MicroNTupleMaker::Loop()
{
//   In a ROOT session, you can do:
//      root> .L MicroNTupleMaker.C
//      root> MicroNTupleMaker t
//      root> t.GetEntry(12); // Fill t data members with entry number 12
//      root> t.Show();       // Show values of entry 12
//      root> t.Show(16);     // Read and show values of entry 16
//      root> t.Loop();       // Loop on all entries
//

//     This is the loop skeleton where:
//    jentry is the global entry number in the chain
//    ientry is the entry number in the current Tree
//  Note that the argument to GetEntry must be:
//    jentry for TChain::GetEntry
//    ientry for TTree::GetEntry and TBranch::GetEntry
//
//       To read only selected branches, Insert statements like:
// METHOD1:
//    fChain->SetBranchStatus("*",0);  // disable all branches
//    fChain->SetBranchStatus("branchname",1);  // activate branchname
// METHOD2: replace line
//    fChain->GetEntry(jentry);       //read all branches
//by  b_branchname->GetEntry(ientry); //read only this branch
	if (fChain == 0) return;

	Long64_t nentries = fChain->GetEntries();
	
	cout << "Initial events: " << nentries << endl;
	int finalEntries = 0;
	int processedEntries = 0;
	Long64_t nbytes = 0, nb = 0;
	for (Long64_t jentry=0; jentry<nentries;jentry++) {
	  //for (Long64_t jentry=0; jentry<50;jentry++) {
		Long64_t ientry = LoadTree(jentry);
		if (ientry < 0) break;
		nb = fChain->GetEntry(jentry);   nbytes += nb;
		processedEntries++;

		if (processedEntries % 10000 == 0 && nentries <= 2000000) cout << "Processed " << processedEntries << " events..." << endl;
		if (processedEntries % 100000 == 0 && nentries > 2000000) cout << "Processed " << processedEntries << " events..." << endl;
		
                // check DSID
                if (dsid_int != mcChannelNumber) cout << "ERROR: Entry 0 DSID " << dsid_int << " does not match event " << mcEventNumber << "(" << jentry << ") DSID" << mcChannelNumber << endl;

		// create relevant 4 vectors
		TLorentzVector v1, v2, met_v;

		// MET preselection
		if(metFinalClus < 200) continue;
		cutflow->Fill(16);
		cutflow_weighted->Fill(16,mcEventWeight);
                
		v1.SetPtEtaPhiE(jet_pt->at(0), jet_eta->at(0), jet_phi->at(0), jet_E->at(0));
		v2.SetPtEtaPhiE(jet_pt->at(1), jet_eta->at(1), jet_phi->at(1), jet_E->at(1));
		//v_svj.SetPtEtaPhiE(jet_pt->at(n_svj), jet_eta->at(n_svj), jet_phi->at(n_svj), jet_E->at(n_svj));
		//v_asvj.SetPtEtaPhiE(jet_pt->at(n_asvj), jet_eta->at(n_asvj), jet_phi->at(n_asvj), jet_E->at(n_asvj));
		met_v.SetPtEtaPhiM(metFinalClus,0,metFinalClusPhi,0.0);

		// y* preselection
		deltaY_12 = GetDeltaY(v1,v2);
                float dPhi1 = GetDPhi(v1,met_v);
                float dPhi2 = GetDPhi(v2,met_v);
		dphi_min = min(dPhi1,dPhi2);		
		dphi_max = max(dPhi1,dPhi2);		
		// svj variablei
		maxphi_minphi = dphi_max - dphi_min;

		// distance between jets
		dR_12 = GetdR(v1,v2);
		deta_12 = GetDEta(v1.Eta(),v2.Eta());
        	dphi_12 = GetDPhi(v1,v2);
	
		// pt balance
		pt_balance_12 = GetPtBalance(v1,v2);
	
		//mT
                mT_jj = GetMt(v1,v2,met_v);

		// -j1_pT -j2_pT
		met_jj_neg = jet_pt->at(0) + jet_pt->at(1);
		mT_jj_neg = GetMtNeg(v1,v2);
		//dphi_MET_j1j2 = GetDPhiMET(v1,v2,met_v);

		// rT
		rT = metFinalClus / mT_jj;

		/* 
 		// SR selection
		// apply dEta < 1.5
		if ( deltaY_12 >= 1.5) continue;
		cutflow->Fill(5);
		// apply rT > 0.15
		if ( rT <= 0.15) continue;
		cutflow->Fill(6);
		// apply mT > 1.5 TeV
		if ( mT_jj <= 1500) continue;
		cutflow->Fill(7);
		// apply dphi < 0.8
		if ( dphi_min >= 0.8) continue;
		cutflow->Fill(7);
		*/

		/*if ( rT > 0.25){
			mT_jj_highRT = mT_jj;
			mT_jj_neg_highRT = mT_jj_neg;
			mT_jj_lowRt = -999;
			mT_jj_neg_lowRt = -999;
                }else {
			mT_jj_highRT = -999;
			mT_jj_neg_highRT = -999;
			mT_jj_lowRt = mT_jj;
			mT_jj_neg_lowRt = mT_jj_neg;
		}*/

		// event shape variables
		map<string,float> shape_variables = GetShapeVariables(jet_pt, jet_eta, jet_phi, jet_E, true);
		aplanarity = shape_variables["Aplanarity"];
		sphericity = shape_variables["Sphericity"];
		sphericity_T = shape_variables["Transverse_Sphericity"];		

		// 2 fatjet situation
		/*if (nfatjet > 1) {
			//cout << "fat jets" <<endl;
			//cout << "nfatjet: " << nfatjet <<endl;
			//cout << "size fatjet_pt: " << fatjet_pt->size() << endl;
			v1fat.SetPtEtaPhiM(fatjet_pt->at(0), fatjet_eta->at(0), fatjet_phi->at(0), fatjet_m->at(0));
			v2fat.SetPtEtaPhiM(fatjet_pt->at(1), fatjet_eta->at(1), fatjet_phi->at(1), fatjet_m->at(1));
                	mT_JJ = GetMt(v1fat,v2fat,metFinalClus, metFinalClusPhi);
			mJJ_12 = GetMjj(v1fat,v2fat);      
		} else {
			mT_JJ = -999;
			mJJ_12 = -999;	
		}*/
		// HT
		hT = GetHT(jet_pt);

		//Jet Substructure variables
		//Jet substrucutre variables for leading jet
		std::vector<float> leadjet_GhostTrack_pt = jet_GhostTrack_pt->at(0);
		std::vector<float> leadjet_GhostTrack_eta = jet_GhostTrack_eta->at(0);
		std::vector<float> leadjet_GhostTrack_phi = jet_GhostTrack_phi->at(0);
		std::vector<float> leadjet_GhostTrack_e = jet_GhostTrack_e->at(0);

		std::vector<fastjet::PseudoJet> leadjet_clusters;
		leadjet_clusters.clear();

		for(int leadjet_trk=0; leadjet_trk<leadjet_GhostTrack_pt.size();leadjet_trk++){
		  TLorentzVector temp_p4;
		  temp_p4.SetPtEtaPhiE(leadjet_GhostTrack_pt.at(leadjet_trk), leadjet_GhostTrack_eta.at(leadjet_trk), leadjet_GhostTrack_phi.at(leadjet_trk), leadjet_GhostTrack_e.at(leadjet_trk));

		  fastjet::PseudoJet p(temp_p4.Px(), temp_p4.Py(), temp_p4.Pz(), temp_p4.E());
		  leadjet_clusters.push_back(p);
		}

		leadjet_NsubJettiness_vars.clear();
		leadjet_ECFs.clear();
		leadjet_ktscale.clear();
		leadjet_lundPlane_x_lnDeltaInv.clear();
		leadjet_lundPlane_y_lnKt.clear();
		if(leadjet_clusters.size() > 0){
		  leadjet_NsubJettiness_vars = Jet_nSubjettiness(leadjet_clusters);
		  leadjet_ECFs = Jet_energyCorrelator(leadjet_clusters);
		  leadjet_ktscale = Jet_KTsplittingScale(leadjet_clusters);
		  leadjet_qw = Jet_qw(leadjet_clusters);

		  std::pair<std::vector<double>, std::vector<double>> leadjet_lundplane = LundJetPlane(leadjet_clusters);
		  leadjet_lundPlane_x_lnDeltaInv = leadjet_lundplane.first;
		  leadjet_lundPlane_y_lnKt = leadjet_lundplane.second;
		}

		//Jet substrucutre variables for subleading jet
		std::vector<float> subleadjet_GhostTrack_pt = jet_GhostTrack_pt->at(1);
		std::vector<float> subleadjet_GhostTrack_eta = jet_GhostTrack_eta->at(1);
		std::vector<float> subleadjet_GhostTrack_phi = jet_GhostTrack_phi->at(1);
		std::vector<float> subleadjet_GhostTrack_e = jet_GhostTrack_e->at(1);

		std::vector<fastjet::PseudoJet> subleadjet_clusters;
		subleadjet_clusters.clear();

		for(int subleadjet_trk=0; subleadjet_trk<subleadjet_GhostTrack_pt.size();subleadjet_trk++){
		  TLorentzVector temp_p4;
		  temp_p4.SetPtEtaPhiE(subleadjet_GhostTrack_pt.at(subleadjet_trk), subleadjet_GhostTrack_eta.at(subleadjet_trk), subleadjet_GhostTrack_phi.at(subleadjet_trk), subleadjet_GhostTrack_e.at(subleadjet_trk));

		  fastjet::PseudoJet p(temp_p4.Px(), temp_p4.Py(), temp_p4.Pz(), temp_p4.E());
		  subleadjet_clusters.push_back(p);
		}

		subleadjet_NsubJettiness_vars.clear();
		subleadjet_ECFs.clear();
		subleadjet_ktscale.clear();
		subleadjet_lundPlane_x_lnDeltaInv.clear();
		subleadjet_lundPlane_y_lnKt.clear();
		if(subleadjet_clusters.size() > 0){
		  subleadjet_NsubJettiness_vars = Jet_nSubjettiness(subleadjet_clusters);
		  subleadjet_ECFs = Jet_energyCorrelator(subleadjet_clusters);
		  subleadjet_ktscale = Jet_KTsplittingScale(subleadjet_clusters);
		  subleadjet_qw = Jet_qw(subleadjet_clusters);

		  std::pair<std::vector<double>, std::vector<double>> subleadjet_lundplane = LundJetPlane(subleadjet_clusters);
		  subleadjet_lundPlane_x_lnDeltaInv = subleadjet_lundplane.first;
		  subleadjet_lundPlane_y_lnKt = subleadjet_lundplane.second;

		}
		// save output tree
		//cout << "Filling" << endl;
		FillOutputTrees("PostSel");
		finalEntries++;
	}
	cout << "Events passing cutflow: " << finalEntries << endl;

}

