#include "TCanvas.h"
#include "TDirectory.h"
#include "TF1.h"
#include "TFile.h"
#include "TGraph.h"
#include "TGraphErrors.h"
#include "TGraphAsymmErrors.h"
#include "TH1D.h"
#include "TH2D.h"
#include "THStack.h"
#include "TLegend.h"
#include "TLatex.h"
#include "TMath.h"
#include "Math/ProbFunc.h"
#include "TProfile.h"
#include "TPaveStats.h"
#include "TPaveText.h"
#include "TROOT.h"
#include "TString.h"
#include "TStyle.h"
#include "TEfficiency.h"
#include "TArrow.h"
#include "TLine.h"
#include "TPad.h"
#include "TVirtualFitter.h"
#include "TRandom3.h"
#include "TTree.h"

#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <sstream>
#include <cmath>

using namespace ROOT;
using namespace ROOT::Math;

void comp() {


  float t_m, b_m, l_m, r_m;
  t_m = 0.06; //top margin
  b_m = 0.08; //botton margin
  l_m = 0.09; //left margin
  r_m = 0.03; //right margin

  gStyle->SetOptTitle(0);
  gStyle->SetPadTopMargin(t_m);
  gStyle->SetPadBottomMargin(b_m);
  gStyle->SetPadLeftMargin(l_m);
  gStyle->SetPadRightMargin(r_m);
  gStyle->SetCanvasBorderMode(0); gStyle->SetCanvasColor(kWhite);
  gStyle->SetPadColor(kWhite);
  gStyle->SetOptTitle(0);   gStyle->SetPadBorderMode(0);
  gStyle->SetCanvasBorderMode(0);
  gStyle->SetOptStat(0);
  gROOT->SetBatch(1);
  gStyle->SetPaintTextFormat("4.1f");

  TString f_qcd = "/eos/user/r/rgarg/Rocky/Analyses/SemiVisibleJets/Samples/v8/MicroNtuples/user.ebusch.364710.mc20e.root";
  TString f_znunu = "/eos/user/r/rgarg/Rocky/Analyses/SemiVisibleJets/Samples/v8/MicroNtuples/user.ebusch.700337.mc20e.root";
  TString f_2000_2 = "/eos/user/r/rgarg/Rocky/Analyses/SemiVisibleJets/Samples/v8/MicroNtuples/user.ebusch.515499.mc20e.root";
  TString f_2000_8 = "/eos/user/r/rgarg/Rocky/Analyses/SemiVisibleJets/Samples/v8/MicroNtuples/user.ebusch.515502.mc20e.root";
  TString f_5000_2 = "/eos/user/r/rgarg/Rocky/Analyses/SemiVisibleJets/Samples/v8/MicroNtuples/user.ebusch.515519.mc20e.root";
  TString f_5000_8 = "/eos/user/r/rgarg/Rocky/Analyses/SemiVisibleJets/Samples/v8/MicroNtuples/user.ebusch.515522.mc20e.root";

  TFile *qcd = new TFile(f_qcd, "READ");
  TFile *znunu = new TFile(f_znunu, "READ");
  TFile *sig_2000_2 = new TFile(f_2000_2, "READ");
  TFile *sig_2000_8 = new TFile(f_2000_8, "READ");
  TFile *sig_5000_2 = new TFile(f_5000_2, "READ");
  TFile *sig_5000_8 = new TFile(f_5000_8, "READ");

  TTree* T_qcd = (TTree*)qcd->Get("PostSel");
  TTree* T_znunu = (TTree*)znunu->Get("PostSel"); 
  TTree* T_2000_2 = (TTree*)sig_2000_2->Get("PostSel");
  TTree* T_2000_8 = (TTree*)sig_2000_8->Get("PostSel");
  TTree* T_5000_2 = (TTree*)sig_5000_2->Get("PostSel");
  TTree* T_5000_8 = (TTree*)sig_5000_8->Get("PostSel");
 
  TCanvas *c = new TCanvas("c", "c", 1000, 800);
  c->cd();
  //c->SetLogy();

  TH1F *h_qcd = new TH1F("h_qcd", "", 100, 0, 50);
  TH1F *h_znunu = new TH1F("h_znunu", "", 100, 0, 50);
  TH1F *h_2000_2 = new TH1F("h_2000_2", "", 100, 0, 50);
  TH1F *h_2000_8 = new TH1F("h_2000_8", "", 100, 0,50);
  TH1F *h_5000_2 = new TH1F("h_5000_2", "", 100, 0, 50);
  TH1F *h_5000_8 = new TH1F("h_5000_8", "", 100, 0, 50);

  h_qcd->GetXaxis()->SetTitle("Qw");
  h_qcd->GetYaxis()->SetTitle("Entries");
  h_qcd->SetLineColor(1);
  h_qcd->SetLineStyle(3);
  h_qcd->SetLineWidth(1);

  h_znunu->SetLineColor(kBlue);
  h_znunu->SetLineStyle(2);
  h_znunu->SetLineWidth(1);

  h_2000_2->SetLineColor(kRed);
  h_2000_2->SetLineStyle(1);
  h_2000_2->SetLineWidth(1);

  h_2000_8->SetLineColor(kMagenta);
  h_2000_8->SetLineStyle(1);
  h_2000_8->SetLineWidth(1);

  h_5000_2->SetLineColor(kGreen);
  h_5000_2->SetLineStyle(1);
  h_5000_2->SetLineWidth(1);

  h_5000_8->SetLineColor(kOrange);
  h_5000_8->SetLineStyle(1);
  h_5000_8->SetLineWidth(1);

  T_qcd->Draw("jet2_qw>>h_qcd");
  T_znunu->Draw("jet2_qw>>h_znunu");
  T_2000_2->Draw("jet2_qw>>h_2000_2");
  T_2000_8->Draw("jet2_qw>>h_2000_8");
  T_5000_2->Draw("jet2_qw>>h_5000_2");
  T_5000_8->Draw("jet2_qw>>h_5000_8");

  h_qcd->Scale(1.0/h_qcd->Integral());
  h_znunu->Scale(1.0/h_znunu->Integral());
  h_2000_2->Scale(1.0/h_2000_2->Integral());
  h_2000_8->Scale(1.0/h_2000_8->Integral());
  h_5000_2->Scale(1.0/h_5000_2->Integral());
  h_5000_8->Scale(1.0/h_5000_8->Integral());

  //h_2000_2->Draw("hist");
  h_znunu->Draw("hist ");
  h_qcd->Draw("hist same");
  //h_znunu->Draw("hist same");
  h_2000_2->Draw("hist same");
  h_2000_8->Draw("hist same");
  h_5000_2->Draw("hist same");
  h_5000_8->Draw("hist same");

  TLegend *leg = new TLegend(0.7, 0.7, 0.9, 0.9);
  leg->SetBorderSize(1); leg->SetFillColor(kWhite);
  leg->SetFillStyle(0);
  leg->SetFillColor(0);
  leg->SetTextFont(52);
  leg->SetTextSize(0.025);
  leg->SetLineColor(kWhite);
  leg->SetLineStyle(1);
  leg->SetLineWidth(1); 
  leg->AddEntry(h_qcd, "QCD Bkg", "L");
  leg->AddEntry(h_znunu, "Znunu Bkg", "L");
  leg->AddEntry(h_2000_2, "Sig:2000_0.2", "L");
  leg->AddEntry(h_2000_8, "Sig:2000_0.8", "L");
  leg->AddEntry(h_5000_2, "Sig:5000_0.2", "L");
  leg->AddEntry(h_5000_8, "Sig:5000_0.8", "L");

  leg->Draw("");
  
  c->Update();
  c->Draw();
  c->SaveAs("Jet2_qw.pdf");
  c->SaveAs("Jet2_qw.png");
}  
