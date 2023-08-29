#include "fastjet/ClusterSequence.hh"
#include "fastjet/PseudoJet.hh"
#include <fastjet/contrib/Nsubjettiness.hh>
#include <fastjet/contrib/EnergyCorrelator.hh>
#include <fastjet/contrib/LundGenerator.hh>

using namespace fastjet;

std::vector<float> MicroNTupleMaker::Jet_nSubjettiness(std::vector<fastjet::PseudoJet> clusters){
  std::vector<float> tau_vars;
  tau_vars.clear();

  fastjet::JetDefinition jet_rebuild_def(fastjet::antikt_algorithm, 0.4, fastjet::E_scheme, fastjet::Best);
  //Rebuilding jet from the clusters
  fastjet::ClusterSequence clust_seq_rebuild = fastjet::ClusterSequence(clusters, jet_rebuild_def);
  std::vector<fastjet::PseudoJet> rebuilt_jets = fastjet::sorted_by_pt(clust_seq_rebuild.inclusive_jets(0.0));

  fastjet::PseudoJet correctedJet = rebuilt_jets[0]; //sometime upon reclustering, jet split into 2 jets with second jet having very small pt. So, keeping only the first

  //Nsubjettinges variables
  //fastjet::contrib::Nsubjettiness nSub1_beta1(1, fastjet::contrib::OnePass_WTA_KT_Axes(), fastjet::contrib::UnnormalizedMeasure(1.0));
  //fastjet::contrib::Nsubjettiness nSub2_beta1(2, fastjet::contrib::OnePass_WTA_KT_Axes(), fastjet::contrib::UnnormalizedMeasure(1.0));
  //fastjet::contrib::Nsubjettiness nSub3_beta1(3, fastjet::contrib::OnePass_WTA_KT_Axes(), fastjet::contrib::UnnormalizedMeasure(1.0));
  //Used in the code (https://github.com/juliagonski/pyjet/blob/dev_jgonski/examples/test_substructure.py)
  fastjet::contrib::Nsubjettiness nSub1_beta1(1, fastjet::contrib::KT_Axes(), fastjet::contrib::NormalizedMeasure(1.0,1.0));
  fastjet::contrib::Nsubjettiness nSub2_beta1(2, fastjet::contrib::KT_Axes(), fastjet::contrib::NormalizedMeasure(1.0,1.0));
  fastjet::contrib::Nsubjettiness nSub3_beta1(3, fastjet::contrib::KT_Axes(), fastjet::contrib::NormalizedMeasure(1.0,1.0));

  float tau1(-999.),tau2(-999.),tau3(-999.);
  tau1 = nSub1_beta1.result(correctedJet);
  tau2 = nSub2_beta1.result(correctedJet);
  tau3 = nSub3_beta1.result(correctedJet);

  float tau21_cluster = std::abs(tau1) > 1e-8 ? tau2/tau1 : -999.;
  float tau32_cluster = std::abs(tau2) > 1e-8 ? tau3/tau2 : -999.;

  tau_vars.push_back(tau1);
  tau_vars.push_back(tau2);
  tau_vars.push_back(tau3);
  tau_vars.push_back(tau21_cluster);
  tau_vars.push_back(tau32_cluster);

  return tau_vars;

}

std::vector<float> MicroNTupleMaker::Jet_energyCorrelator(std::vector<fastjet::PseudoJet> clusters){

  std::vector<float> EnergyCorr;
  EnergyCorr.clear();

  fastjet::JetDefinition jet_rebuild_def(fastjet::antikt_algorithm, 0.4, fastjet::E_scheme, fastjet::Best);
  //Rebuilding jet from the clusters
  fastjet::ClusterSequence clust_seq_rebuild = fastjet::ClusterSequence(clusters, jet_rebuild_def);
  std::vector<fastjet::PseudoJet> rebuilt_jets = fastjet::sorted_by_pt(clust_seq_rebuild.inclusive_jets(0.0));

  fastjet::PseudoJet correctedJet = rebuilt_jets[0]; //sometime upon reclustering, jet split into 2 jets with second jet having very small pt. So, keeping only the first

  //Energy Correlator functions
  fastjet::contrib::EnergyCorrelator ECF1(1, 1.0, fastjet::contrib::EnergyCorrelator::pt_R);
  fastjet::contrib::EnergyCorrelator ECF2(2, 1.0, fastjet::contrib::EnergyCorrelator::pt_R);
  fastjet::contrib::EnergyCorrelator ECF3(3, 1.0, fastjet::contrib::EnergyCorrelator::pt_R);

  float vECF1(-999.),vECF2(-999.),vECF3(-999.);
  vECF1 = ECF1.result(correctedJet);
  vECF2 = ECF2.result(correctedJet);
  vECF3 = ECF3.result(correctedJet);

  float C2_cluster = std::abs(vECF2) > 1e-8 ? vECF3 * vECF1 / (vECF2 * vECF2) : -999.;
  float D2_cluster = std::abs(vECF2) > 1e-8 ? vECF3 * vECF1* vECF1* vECF1 / (vECF2 * vECF2 * vECF2) : -999.;

  EnergyCorr.push_back(vECF1);
  EnergyCorr.push_back(vECF2);
  EnergyCorr.push_back(vECF3);
  EnergyCorr.push_back(C2_cluster);
  EnergyCorr.push_back(D2_cluster);

  return EnergyCorr;

}

std::vector<float> MicroNTupleMaker::Jet_KTsplittingScale(std::vector<fastjet::PseudoJet> clusters){

  std::vector<float> KTsplit;
  KTsplit.clear();

  //KT splitting scale
  float split12 = -1;
  float split23 = -1;
  fastjet::JetDefinition jet_kt_def = fastjet::JetDefinition(fastjet::kt_algorithm, 1.5, fastjet::E_scheme, fastjet::Best);
  fastjet::ClusterSequence kt_clust_seq = fastjet::ClusterSequence(clusters, jet_kt_def);
  fastjet::PseudoJet kt_jet = fastjet::sorted_by_pt(kt_clust_seq.inclusive_jets()).front();
  split12 = 1.5*sqrt(kt_clust_seq.exclusive_subdmerge(kt_jet, 1));
  split23 = 1.5*sqrt(kt_clust_seq.exclusive_subdmerge(kt_jet, 2));

  KTsplit.push_back(split12);
  KTsplit.push_back(split23);

  return KTsplit;

}

float MicroNTupleMaker::Jet_qw(std::vector<fastjet::PseudoJet> clusters){

  //Qw
  float qw = -1;
  float scaleF = 1.0;
  int n_constituents = clusters.size();
  if(n_constituents < 3) return 0;

  fastjet::JetDefinition jet_def(fastjet::kt_algorithm, 1.0, fastjet::E_scheme, fastjet::Best);
  fastjet::ClusterSequence cs_build = fastjet::ClusterSequence(clusters, jet_def);

  std::vector<fastjet::PseudoJet> outjets = cs_build.exclusive_jets(3);

  double m12 = (outjets[0]+outjets[1]).m();
  double m23 = (outjets[2]+outjets[1]).m();
  double m13 = (outjets[2]+outjets[0]).m();

  qw = scaleF*std::min(m12, std::min(m23,m13) );

  return qw;
}

std::pair<std::vector<double>,std::vector<double>> MicroNTupleMaker::LundJetPlane(std::vector<fastjet::PseudoJet> clusters){

  std::pair<std::vector<double>,std::vector<double>> lundPlaneVars;
  
  // create an instance of LundGenerator, with default options
  contrib::LundGenerator lund;
  //std::cout << lund.description() << std::endl;

  fastjet::JetDefinition jet_rebuild_def(fastjet::antikt_algorithm, 0.4, fastjet::E_scheme, fastjet::Best);
  //Rebuilding jet from the clusters
  fastjet::ClusterSequence clust_seq_rebuild = fastjet::ClusterSequence(clusters, jet_rebuild_def);
  std::vector<fastjet::PseudoJet> jets = fastjet::sorted_by_pt(clust_seq_rebuild.inclusive_jets(0.0));

  std::vector<double> lund_x_lnDeltaInv, lund_y_lnKt;
  lund_x_lnDeltaInv.clear(); lund_y_lnKt.clear();

  for (unsigned int ijet = 0; ijet < jets.size(); ijet++) {    
    std::vector<contrib::LundDeclustering> declusts = lund(jets[ijet]); //this actually calls lund.result(jets[ijet])

    for (int idecl = 0; idecl < declusts.size(); idecl++) {

      std::pair<double,double> coords = declusts[idecl].lund_coordinates();
      lund_x_lnDeltaInv.push_back(coords.first);
      lund_y_lnKt.push_back(coords.second);

    }
    return std::pair<double,double>(lund_x_lnDeltaInv,lund_y_lnKt);
  }
