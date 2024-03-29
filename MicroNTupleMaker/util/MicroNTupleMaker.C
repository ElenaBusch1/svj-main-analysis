#define MicroNTupleMaker_cxx

using namespace std;

#include "../MicroNTupleMaker/MicroNTupleMaker.h"
#include "../src/FunctionHelper.cxx"
#include "../src/OutputTreeHelper.cxx"
#include "../src/HistHelper.cxx"
#include "../src/WeightHelper.cxx"
#include "../src/Loop.cxx"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>

using filesystem::directory_iterator;

void MicroNTupleMaker(string infiletag = "", bool local = false, string infilepath = ""){
	
	// Check for infile //
	
	string fullinfilepath;
	// Running remotely
	if( !local ) { // Path from base dir -- when ONLY file tag is provided
	        fullinfilepath = infiletag;
	        cout<< "running not locally"<<endl;	
 	// Running locally - must provide path to inputs and true flag
	} else {
                
	        cout<< "running locally"<<endl;	
		fullinfilepath = infilepath + infiletag;
	}
//added	
	cout << "infilepath "<< infilepath<<", infiletag "<<infiletag<<endl;	
	// ----- Read in File(s) & Tree ----- // 
	
	cout<<"Reading in fullinfilepath: "<<fullinfilepath<<endl;
	
	TChain *fChain = new TChain("outTree");
	TH1F *metadata;
	TH1F *cutflow;
	TH1F *cutflow_weighted;

	int file_count = 0;	
	if ( !local ){
		string tmp;
		stringstream ss(fullinfilepath);
		vector<string> files;

		while(getline(ss, tmp, ',')) files.push_back(tmp);

		for (auto &file: files){
  			file_count++;
			// Add tree to chain
			cout << "loading file " << file << endl;
			TString path_tstring = Form("%s", file.c_str());
			fChain->Add(path_tstring);
			// Get metadata
			
			std::unique_ptr<TFile> f1( TFile::Open(path_tstring, "READ") );
			cout << "ls file contents" << endl;
			f1->ls();
			cout << "Getting metadata" <<endl;
			TH1F* h1 = (TH1F*) f1->Get("MetaData_EventCount");
			TH1F* h2 = (TH1F*) f1->Get("cutflow");
			TH1F* h3 = (TH1F*) f1->Get("cutflow_weighted");
			if (file_count == 1){
				cout << "Cloning histograms" <<endl;
				metadata = (TH1F*) h1->Clone();
				cutflow = (TH1F*) h2->Clone();
				cutflow_weighted = (TH1F*) h3->Clone();
				cout << "Setting directory to 0" <<endl;
				metadata->SetDirectory(0);
				cutflow->SetDirectory(0);
				cutflow_weighted->SetDirectory(0);
			} else {
				cout << "Adding metadata and cutflow histograms" << endl;
				metadata->Add(h1);
				cutflow->Add(h2);
				cutflow_weighted->Add(h3);
			}
			cout << "Closing file" <<endl;
			f1->Close();
		}
	} else {
		for (const auto & entry : directory_iterator(fullinfilepath)){
			file_count++;
 			TString path_string = Form("%s",entry.path().string().c_str());
			cout << "path_string: " << path_string << endl;
			//TFile *f = new TFile( path_string, "READ");
			std::unique_ptr<TFile> f( TFile::Open(path_string, "READ") );
			TH1F* h1l = (TH1F*) f->Get("MetaData_EventCount");
			TH1F* h2l = (TH1F*) f->Get("cutflow");
			TH1F* h3l = (TH1F*) f->Get("cutflow_weighted");
			if (file_count ==1){
				metadata = (TH1F*) h1l->Clone();
				cutflow = (TH1F*) h2l->Clone();
				cutflow_weighted = (TH1F*) h3l->Clone();
				metadata->SetDirectory(0);
				cutflow->SetDirectory(0);
				cutflow_weighted->SetDirectory(0);
			} else {
				metadata->Add(h1l);
				cutflow->Add(h2l);
				cutflow_weighted->Add(h3l);
			}
			cout << "h sumW: " << h3l->GetBinContent(1) << endl;
			f->Close();
			cout << "cutflow_w sumW: " << cutflow_weighted->GetBinContent(1) << endl;
			fChain->Add(path_string);
			
		}
		cout << "Added " << file_count << " files to the chain" << endl;
	}

        // Weight from Metadata histogram
	double sumWInput = cutflow_weighted->GetBinContent(1);
	//double sumWInput = 1;

	// Create output file
	string dsid = "";
        string user = "user.ebusch.";
        if (local) dsid = infiletag.substr(user.length(),6);
	if (local) cout << "local DSID: " << dsid << endl;
        //string dsid = to_string(myMaker.dsid_int);
	string mc = "";
	if (infiletag.find("mc20a") != string::npos) mc = "mc20a";
	if (infiletag.find("mc20d") != string::npos) mc = "mc20d";
	if (infiletag.find("mc20e") != string::npos) mc = "mc20e";
	if (infiletag.find("data") != string::npos) mc = "data";
        if (local) cout <<"mc: "<<mc<<endl;
	string outfiletag = "user.ebusch." + dsid + "." + mc;
	//string outfiletag = "user.kipark." + infiletag + "." + mc;
        TString outfilename;
     
	if (local) outfilename = Form( "MicroNTuples/%s.root", outfiletag.c_str() );
	else outfilename = "output.root";
	//added
        //else outfilename = Form( "/eos/user/k/kipark/ana-exot-2021-19/MicroNTupleMaker/MicroNTuples/%s.root", outfiletag.c_str() );

	TFile *fout = new TFile( outfilename, "RECREATE" );	
	cout << "Will write to "<<outfilename<<endl;

	// Class instance
        cout << "Declaring class" <<endl;
	class MicroNTupleMaker myMaker(fChain);
	// find DSID and set weight
	myMaker.SetWeight();
        myMaker.year_mc = mc;
        myMaker.sumw = sumWInput;
	// Fill and loop
	myMaker.DeclareHistograms(metadata, cutflow, cutflow_weighted);
	myMaker.DeclareOutputTrees();
	myMaker.Loop();
	myMaker.WriteOutputTrees();
	myMaker.WriteHistograms();
}

int main(int argc, char** argv){

  int Nargs = argc;

  if( Nargs == 2 )
        MicroNTupleMaker( argv[1], false, "" );
  else if (Nargs == 4)
        MicroNTupleMaker( argv[1], argv[2], argv[3] );
  else
        cout<<"ERROR: Not enough arguments!"<<endl;

}

