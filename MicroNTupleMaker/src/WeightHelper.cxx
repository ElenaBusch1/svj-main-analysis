/* ====================================================================================================================== */
void MicroNTupleMaker::SetWeight(double sumWInput){

        //Int_t dsid_int;
        fChain->GetEntry(0);
	dsid_int = mcChannelNumber;
        string dsid = to_string(dsid_int); 

	sumw = sumWInput;
	double gfe = GetGenFilterEff(dsid);
	double xs = GetXSection(dsid);

	weight_scale = xs*gfe/sumw;
}

/* ====================================================================================================================== */
double MicroNTupleMaker::GetSumW(string dsid){

	// Eventually: read from cutflow table
	// Temp solution: input by hand
	
        double my_sumw = 0.0;

        //my_sumw = MetaData_EventCount->GetBinContent(3)

        /*
	// Cross section in nb
	ma
	// Multijet
	sumw["364702"] = 121027;       
	sumw["364703"] = 4772.79;
	sumw["364704"] = 107.418;
	sumw["364705"] = 3.00517;
	sumw["364706"] = 0.0889688;
	sumw["364707"] = 0.0122396;
	sumw["364708"] = 0.00354308;
	sumw["364709"] = 0.000661628;
	sumw["364710"] = 7.54144e-05;
	sumw["364711"] = 4.15448e-05;
	sumw["364712"] = 2.41811e-05;

	// Signal
	sumw["508547"] = 52946.2;       
	sumw["508548"] = 51757.8;     
	sumw["508549"] = 995391;       
	sumw["508550"] = 1.01754e+06;  
	
	//Z+jets
	sumw["700323"] = 4.51978e+14 ; 
	sumw["700324"] = 1.5935e+15  ; 
	sumw["700325"] = 4.45063e+15 ; 
	sumw["700326"] = 2.28232e+14 ; 
	sumw["700327"] = 6.29402e+14 ; 
	sumw["700328"] = 6.34815e+14 ; 
	sumw["700329"] = 2.25487e+14 ; 
	sumw["700330"] = 6.71013e+14 ; 
	sumw["700331"] = 5.4226e+14  ; 
	sumw["700332"] = 1.84023e+14 ; 
	sumw["700333"] = 4.70829e+14 ; 
	sumw["700334"] = 4.25959e+14 ; 
	sumw["700335"] = 3.9533e+14  ; 
	sumw["700336"] = 5.09234e+14 ; 
	sumw["700337"] = 7.70998e+14 ; 
	
	//W+jets
	sumw["700338"] = 4.05101e+15 ; 
	sumw["700339"] = 1.78335e+16 ; 
	sumw["700340"] = 9.41937e+16 ; 
	sumw["700341"] = 3.77004e+15 ; 
	sumw["700342"] = 2.1413e+16  ; 
	sumw["700343"] = 9.48676e+16 ; 
	sumw["700344"] = 7.74448e+14 ; 
	sumw["700345"] = 5.75794e+15 ; 
	sumw["700346"] = 2.30811e+16 ; 
	sumw["700347"] = 4.52994e+14 ; 
	sumw["700348"] = 2.30502e+15 ; 
	sumw["700349"] = 2.30821e+16 ; 

	//ttbar
	sumw["410470"] = 3.41682e+11; 
	sumw["410471"] = 1.28473e+11; 
	sumw["410644"] = 1.58214e+07; 
	sumw["410645"] = 9.91738e+06; 
	sumw["410646"] = 1.48172e+09; 
	sumw["410647"] = 1.47944e+09; 
	sumw["410658"] = 3.60382e+09; 
	sumw["410659"] = 2.15396e+09; 
	sumw["363355"] = 1.27821e+07; 
	sumw["363357"] = 2.04357e+06; 
	sumw["363359"] = 8.23153e+06; 
	sumw["363360"] = 5.01748e+06; 
        sumw["363489"] = 8.62635e+06;


        map<string, double>::iterator iter = sumw.find(dsid);
	if (iter != sumw.end()) my_sumw = sumw[dsid];
	else cout << "ERROR: No SumW info found for DSID " << dsid << endl;
        */
	return my_sumw;

}

/* ====================================================================================================================== */
double MicroNTupleMaker::GetGenFilterEff(string dsid){

        double my_gfe = 0.0;

	// Gen Filter Eff
	map<string, double> gfe;
	// Multijet
	gfe["364702"] = 9.86e-3; 
	gfe["364703"] = 1.17e-2;
	gfe["364704"] = 1.34e-2;
	gfe["364705"] = 1.45e-2;
	gfe["364706"] = 9.47e-3;
	gfe["364707"] = 1.11e-2;
	gfe["364708"] = 1.02e-2;
	gfe["364709"] = 1.21e-2;
	gfe["364710"] = 5.89e-3;
	gfe["364711"] = 2.67e-3;
	gfe["364712"] = 4.29e-4;

	// Signal
	//R&D samples
	gfe["508547"] = 1.0; 
	gfe["508548"] = 1.0;
	gfe["508549"] = 1.0;
	gfe["508550"] = 1.0;
	//Grid
	gfe["509962"] = 1.0;
	gfe["509963"] = 1.0;
	gfe["509964"] = 1.0;
	gfe["509965"] = 1.0;
	gfe["509966"] = 1.0;
	gfe["509967"] = 1.0;
	gfe["509968"] = 1.0;
	gfe["509969"] = 1.0;
	gfe["509970"] = 1.0;
	gfe["509971"] = 1.0;
	gfe["515479"] = 1.0; 
	gfe["515480"] = 1.0; 
	gfe["515481"] = 1.0; 
	gfe["515482"] = 1.0; 
	gfe["515483"] = 1.0; 
	gfe["515484"] = 1.0; 
	gfe["515485"] = 1.0; 
	gfe["515486"] = 1.0; 
	gfe["515487"] = 1.0; 
	gfe["515488"] = 1.0; 
	gfe["515489"] = 1.0; 
	gfe["515490"] = 1.0; 
	gfe["515491"] = 1.0; 
	gfe["515492"] = 1.0; 
	gfe["515493"] = 1.0; 
	gfe["515494"] = 1.0; 
	gfe["515495"] = 1.0; 
	gfe["515496"] = 1.0; 
	gfe["515497"] = 1.0; 
	gfe["515498"] = 1.0; 
	gfe["515499"] = 1.0; 
	gfe["515500"] = 1.0; 
	gfe["515501"] = 1.0; 
	gfe["515502"] = 1.0; 
	gfe["515503"] = 1.0; 
	gfe["515504"] = 1.0; 
	gfe["515505"] = 1.0; 
	gfe["515506"] = 1.0; 
	gfe["515507"] = 1.0; 
	gfe["515508"] = 1.0; 
	gfe["515509"] = 1.0; 
	gfe["515510"] = 1.0; 
	gfe["515511"] = 1.0; 
	gfe["515512"] = 1.0; 
	gfe["515513"] = 1.0; 
	gfe["515514"] = 1.0; 
	gfe["515515"] = 1.0; 
	gfe["515516"] = 1.0; 
	gfe["515517"] = 1.0; 
	gfe["515518"] = 1.0; 
	gfe["515519"] = 1.0; 
	gfe["515520"] = 1.0; 
	gfe["515521"] = 1.0; 
	gfe["515522"] = 1.0; 
	gfe["515523"] = 1.0; 
	gfe["515524"] = 1.0; 
	gfe["515525"] = 1.0; 
	gfe["515526"] = 1.0; 

	//W+jets
	gfe["700323"] = 0.02439439; 
	gfe["700324"] = 0.13003; 
	gfe["700325"] = 0.84639; 
	gfe["700326"] = 0.0249068; 
	gfe["700327"] = 0.1254; 
	gfe["700328"] = 0.85036; 
	gfe["700329"] = 0.024395; 
	gfe["700330"] = 0.12542; 
	gfe["700331"] = 0.85022; 
	gfe["700332"] = 0.024585; 
	gfe["700333"] = 0.1247522; 
	gfe["700334"] = 0.85004; 
	gfe["700335"] = 0.0842665; 
	gfe["700336"] = 0.202381; 
	gfe["700337"] = 0.712717; 
	
	//Z+jets
	gfe["700338"] = 0.0093902; 
	gfe["700339"] = 0.1489766; 
	gfe["700340"] = 0.8436; 
	gfe["700341"] = 0.0097968; 
	gfe["700342"] = 0.1460112; 
	gfe["700343"] = 0.84355; 
	gfe["700344"] = 0.0090177; 
	gfe["700345"] = 0.146033; 
	gfe["700346"] = 0.84747; 
	gfe["700347"] = 0.00867775; 
	gfe["700348"] = 0.14337; 
	gfe["700349"] = 0.84746; 

	//ttbar
	gfe["410470"] = 0.5438; 
	gfe["410471"] = 0.45623; 
	gfe["410644"] = 1.0; 
	gfe["410645"] = 1.0; 
	gfe["410646"] = 1.0; 
	gfe["410647"] = 1.0; 
	gfe["410658"] = 1.0; 
	gfe["410659"] = 1.0; 
	gfe["363355"] = 0.28003; 
	gfe["363357"] = 1.0; 
	gfe["363359"] = 1.0; 
	gfe["363360"] = 1.0; 
        gfe["363489"] = 1.0;
	
        map<string, double>::iterator iter = gfe.find(dsid);
	if (iter != gfe.end()) my_gfe = gfe[dsid];
	else cout << "ERROR: No GenFilterEff info found for DSID " << dsid << endl;

	return my_gfe;

}

/* ====================================================================================================================== */
double MicroNTupleMaker::GetXSection(string dsid){

        double my_xs = 0.0;

	// Cross section in nb
	map<string, double> xs;
	// Multijet
	xs["364702"] = 2.43e+6; 
	xs["364703"] = 2.65e+4;
	xs["364704"] = 2.55e+2;
	xs["364705"] = 4.55e0;
	xs["364706"] = 2.58e-1;
	xs["364707"] = 1.62e-2;
	xs["364708"] = 6.25e-4;
	xs["364709"] = 1.96e-5;
	xs["364710"] = 1.2e-6;
	xs["364711"] = 4.23e-8;  
	xs["364712"] = 1.04e-9;

	// Signal
	// R&D samples
	xs["508547"] = 3.95e-4;
	xs["508548"] = 3.95e-4;
	xs["508549"] = 7.37e-3;
	xs["508550"] = 7.37e-3;
	// grid
	xs["509962"] = 2.11e-3;
	xs["509963"] = 2.12e-3;
	xs["509964"] = 3.22e-5;
	xs["509965"] = 3.22e-5;
	xs["509966"] = 8.15e-6;
	xs["509967"] = 8.08e-6;
	xs["509968"] = 8.39e-7;
	xs["509969"] = 8.40e-7;
	xs["509970"] = 3.23e-8;
	xs["509971"] = 3.25e-8;
	xs["515479"] = 2.11e-3; 
	xs["515480"] = 2.12e-3; 
	xs["515481"] = 2.11e-3; 
	xs["515482"] = 2.11e-3; 
	xs["515483"] = 5.24e-4; 
	xs["515484"] = 5.24e-4; 
	xs["515485"] = 5.24e-4; 
	xs["515486"] = 5.23e-4; 
	xs["515487"] = 1.77e-4; 
	xs["515488"] = 1.77e-4; 
	xs["515489"] = 1.77e-4; 
	xs["515490"] = 1.77e-4; 
	xs["515491"] = 7.14e-5; 
	xs["515492"] = 7.16e-5; 
	xs["515493"] = 7.14e-5; 
	xs["515494"] = 7.18e-5; 
	xs["515495"] = 3.23e-5; 
	xs["515496"] = 3.22e-5; 
	xs["515497"] = 3.22e-5; 
	xs["515498"] = 3.22e-5; 
	xs["515499"] = 8.10e-6; 
	xs["515500"] = 8.10e-6; 
	xs["515501"] = 8.11e-6; 
	xs["515502"] = 8.09e-6; 
	xs["515503"] = 2.45e-6; 
	xs["515504"] = 2.46e-6; 
	xs["515505"] = 2.45e-6; 
	xs["515506"] = 2.45e-6; 
	xs["515507"] = 8.39e-7; 
	xs["515508"] = 8.40e-7; 
	xs["515509"] = 8.37e-7; 
	xs["515510"] = 8.40e-7; 
	xs["515511"] = 3.18e-7; //3.16e-7; 
	xs["515512"] = 3.19e-7; 
	xs["515513"] = 3.18e-7; 
	xs["515514"] = 3.18e-7; 
	xs["515515"] = 1.33e-7; 
	xs["515516"] = 1.33e-7; 
	xs["515517"] = 1.33e-7; 
	xs["515518"] = 1.33e-7; 
	xs["515519"] = 3.24e-8; 
	xs["515520"] = 3.22e-8; 
	xs["515521"] = 3.23e-8; 
	xs["515522"] = 3.24e-8; 
	xs["515523"] = 1.20e-8; 
	xs["515524"] = 1.20e-8; 
	xs["515525"] = 1.20e-8; 
	xs["515526"] = 1.20e-8; 
	
	//Z+jets
	xs["700323"] = 2.22; 
	xs["700324"] = 2.22; 
	xs["700325"] = 2.22; 
	xs["700326"] = 2.75e-1; 
	xs["700327"] = 2.75e-1; 
	xs["700328"] = 2.75e-1; 
	xs["700329"] = 1.01; 
	xs["700330"] = 1.01; 
	xs["700331"] = 1.01; 
	xs["700332"] = 9.33e-1; 
	xs["700333"] = 9.33e-1; 
	xs["700334"] = 9.33e-1; 
	xs["700335"] = 4.47e-1; 
	xs["700336"] = 4.47e-1; 
	xs["700337"] = 4.47e-1; 
	
	//W+jets
	xs["700338"] = 2.17e+1; 
	xs["700339"] = 2.17e+1; 
	xs["700340"] = 2.17e+1; 
	xs["700341"] = 2.18e+1; 
	xs["700342"] = 2.18e+1; 
	xs["700343"] = 2.18e+1; 
	xs["700344"] = 7.68; 
	xs["700345"] = 7.68; 
	xs["700346"] = 7.68; 
	xs["700347"] = 1.41e+1; 
	xs["700348"] = 1.41e+1; 
	xs["700349"] = 1.41e+1; 

	//ttbar
	xs["410470"] = 7.30e-1; 
	xs["410471"] = 7.30e-1; 
	xs["410644"] = 2.03e-3; 
	xs["410645"] = 1.27e-3; 
	xs["410646"] = 3.79e-2; 
	xs["410647"] = 3.79e-2; 
	xs["410658"] = 3.70e-2; 
	xs["410659"] = 2.22e-2; 
	xs["363355"] = 1.56e-2; 
	xs["363357"] = 6.80e-3; 
	xs["363359"] = 2.47e-2; 
	xs["363360"] = 2.47e-2; 
        xs["363489"] = 1.14e-2;

        map<string, double>::iterator iter = xs.find(dsid);
	if (iter != xs.end()) my_xs = xs[dsid];
	else cout << "ERROR: No XSection info found for DSID " << dsid << endl;

	return my_xs;

}
