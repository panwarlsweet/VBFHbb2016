#include <ctype.h>
#include <iomanip>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <cstdlib>
#include "TFile.h"
#include "TH1.h"
#include "TH1F.h"
#include "TH2.h"
#include "TTree.h"
#include "TChain.h"
#include <vector>
#include <utility>
#include <iostream>
#include <fstream>
#include <cstdio>
#include <TROOT.h>
#include <TString.h>
#include <TStyle.h>
#include <TSystem.h>
#include <TCanvas.h>
#include <TMarker.h>
#include <THStack.h>
#include <TLegend.h>
#include <TLatex.h>
#include <TCut.h>
#include <TGraph.h>
#include <TGraphErrors.h>
#include <TLorentzVector.h>
#include <TMath.h>
#include <TF1.h>
#include <TProfile.h>
#include "math.h"
#include "/afs/cern.ch/work/n/nchernya/VBFHbb_2016/plotter/preselection_single.C"
#include "/afs/cern.ch/work/n/nchernya/VBFHbb_2016/plotter/preselection_double.C"


/*
Double_t erf( Double_t *x, Double_t *par){
  return par[0]/2.*(1.+TMath::Erf((x[0]-par[1])/par[2]));
}
Double_t erf2( Double_t *x, Double_t *par){
  return par[0]/2.*(1.+TMath::Erf((x[0]-par[1])/par[2]))+ (1.-par[0]);
}
#define SWAP2(A, B) { TLorentzVector t = A; A = B; B = t; }
void SortByEta(std::vector<TLorentzVector> &jets){
  int i, j;
	int n=jets.size();
  for (i = n - 1; i >= 0; i--){
    for (j = 0; j < i; j++){
      if (jets[j].Eta() < jets[j + 1].Eta() ){
        SWAP2( jets[j], jets[j + 1] );
		}
    }
	}
}
*/

Double_t erf( Double_t *x, Double_t *par){
  return par[0]/2.*(1.+TMath::Erf((x[0]-par[1])/par[2]));
}

struct sort_pred {
    bool operator()(const std::pair<int,float> &left, const std::pair<int,float> &right) {
        return left.second > right.second;
    }
};




typedef std::map<double, int> JetList;
const int njets = 50;

typedef struct {
   Float_t eta[njets];
   Float_t pt[njets];
   Float_t JEC_corr[njets];
   Float_t JEC_corr_up[njets];
   Float_t JEC_corr_down[njets];
   Float_t JER_corr[njets];
   Float_t JER_corr_up[njets];
   Float_t JER_corr_down[njets];
   Float_t phi[njets];
	Float_t mass[njets];
	Float_t btagCMVAV2[njets];
	Float_t btagCMVAV2_weight[njets];
	Float_t btagCSV[njets];
	Int_t nsoft;
	Float_t soft_pt[njets];
	Float_t soft_eta[njets];
	Float_t soft_mass[njets];
	Float_t qgl[njets];
	Int_t nsoft2;
	Int_t nsoft5;
	Int_t nsoft10;
	Int_t id[njets];
	Int_t puId[njets];
	Float_t HTsoft;
	Float_t pt_reg[njets];	
	Float_t ptd[njets];
	Float_t axis2[njets];
	Int_t mult[njets];
	Float_t leadTrackPt[njets];
	Float_t blike_VBF[njets];
	Int_t partonFlavour[njets];
} Jets;

using namespace std;


int main(int argc, char* argv[]){


TString file_name = std::string(argv[1]);
TString file_tag = std::string(argv[2]);
TString dataset_type = std::string(argv[3]);
TString region = std::string(argv[4]); 
int data = atoi(argv[5]);
int applyTrigWeight = atoi(argv[6]);
TString trigWeight_str = std::string(argv[7]);
TString heppyVersion = std::string(argv[8]);
TString postfix = std::string(argv[9]);
TString output = std::string(argv[10]);


std::map <TString, float> xsec;
xsec["BTagCSV"] = 1.;
xsec["BTagCSV0"] = 1.;
xsec["BTagCSV1"] = 1.;
xsec["BTagCSV2"] = 1.;
xsec["BTagCSV3"] = 1.;
xsec["BTagCSV4"] = 1.;
xsec["BTagCSV5"] = 1.;
xsec["VBFHToBB_M-125"] =  2.20;
xsec["GluGluHToBB_M-125"] = 25.69;
xsec["QCD_HT100to200"] = 27990000;
xsec["QCD_HT200to300"] = 1712000 ;
xsec["QCD_HT300to500"] = 347700;
xsec["QCD_HT500to700"] = 32100 ;
xsec["QCD_HT700to1000"] = 6831;
xsec["QCD_HT1000to1500"] = 1207 ;
xsec["QCD_HT1500to2000"] =  119.9;
xsec["QCD_HT2000toInf"] = 25.24;
xsec["TT"] = 831.76;
xsec["ST_tW_top"] = 35.85  ;			//inclusive decays
xsec["ST_tW_antitop"] = 35.85  ;			//inclusive decays
xsec["ST_s-channel"] = 3.36; //leptonic decays
xsec["ST_s_inclusive"] = 10.32; //inclusive decays
xsec["ST_t-channel_top_4f_inclusiveDecays"] = 136.02;
xsec["ST_t-channel_antitop_4f_inclusiveDecays"] = 80.95;

xsec["WJetsToLNu_amc"]  = 61526.7; //not going to use these ones
xsec["WJetsToLNu"]  = 61526.7;
xsec["DYJetsToLL"] = 6025.2;
xsec["DYJetstoLL_amc_0J"] = 4585.27; //4732.;  normalize to 5765.4 pb, 1.032 
xsec["DYJetstoLL_amc_1J"] = 853.198;//880.5; 
xsec["DYJetstoLL_amc_2J"] = 325.194;//335.6; 
xsec["DYJetsToQQ"] = 1461.02;
xsec["WJetsToQQ"] = 3539.25 ;

xsec["ttHTobb_M125"]  = .295;
xsec["ttHToNonbb_M125"]  = .2117 ;
xsec["ZH_HToBB"] = 3.093083e-01; //to qq
xsec["WplusH_HToBB"] = 3.057600e-01; 
xsec["WminusH_HToBB"] = 1.940120e-01;
xsec["WW"] = 118.7 ;
xsec["ZZ"] = 16.523 ;
xsec["WZ"] = 47.13;
xsec["bbHSusy120"] = 0.284;
xsec["bbHToBB_yb2"] = 0.3104;
xsec["bbHToBB_ybyt"] = -0.0262;
xsec["VBFHToBB_M-125_amc"] = 2.20;
xsec["GluGluHToBB_M-125_amc"] = 25.69;
xsec["VBFHToBB_M-125_ueps_up"] = 2.20;
xsec["VBFHToBB_M-125_ueps_down"] = 2.20;
xsec["VBFHToBB_M-125_herwig"] = 2.20;
xsec["GluGluHToBB_M-125_ueps_up"] = 25.69;
xsec["GluGluHToBB_M-125_ueps_down"] = 25.69;
xsec["GluGluHToBB_M-125_herwig"] = 25.69;


std::map <TString, float> qgl_norm;
if (dataset_type.CompareTo("single")==0) {
qgl_norm["ST_tW_top"]=0.969027362;
qgl_norm["ST_tW_antitop"]=0.966305594;
qgl_norm["ST_s-channel"]=0.969012219;
qgl_norm["ST_t-channel_top_4f_inclusiveDecays"]=0.981936118;
qgl_norm["ST_t-channel_antitop_4f_inclusiveDecays"]=0.980760064;
qgl_norm["QCD_HT100to200"]=1;
qgl_norm["QCD_HT200to300"]=0.972104286;
qgl_norm["QCD_HT300to500"]=0.986218526;
qgl_norm["QCD_HT500to700"]=0.98425371;
qgl_norm["QCD_HT700to1000"]=0.976825118;
qgl_norm["QCD_HT1000to1500"]=0.964332988;
qgl_norm["QCD_HT1500to2000"]=0.943468494;
qgl_norm["QCD_HT2000toInf"]=0.931756232;
qgl_norm["VBFHToBB_M-125"]=0.978234492;
qgl_norm["GluGluHToBB_M-125"]=0.985054953;
qgl_norm["WJetsToQQ"]=0.971988179;
qgl_norm["DYJetsToQQ"]=0.975317594;
qgl_norm["TT"]=0.984415933;
qgl_norm["DYJetstoLL_amc_0J"]=1.;
qgl_norm["DYJetstoLL_amc_1J"]=1.;
qgl_norm["DYJetstoLL_amc_2J"]=1.;
qgl_norm["WJetsToLNu"]=1.;

qgl_norm["VBFHToBB_M-125_amc"]=0.978234492;
qgl_norm["VBFHToBB_M-125_ueps_up"]=0.978234492;
qgl_norm["VBFHToBB_M-125_ueps_down"]=0.978234492;
qgl_norm["VBFHToBB_M-125_herwig"]=1.;
qgl_norm["GluGluHToBB_M-125_amc"]=0.985054953;
qgl_norm["GluGluHToBB_M-125_ueps_up"]=0.985054953;
qgl_norm["GluGluHToBB_M-125_ueps_down"]=0.985054953;
qgl_norm["GluGluHToBB_M-125_herwig"]=1.;
qgl_norm["WW"]=1.;
qgl_norm["ZZ"]=1.;
qgl_norm["WZ"]=1.;
qgl_norm["ST_s_inclusive"]=1.;
qgl_norm["bbHToBB_yb2"]=1.;
qgl_norm["bbHToBB_ybyt"]=1.;
qgl_norm["ZH_HToBB"]=1.;
qgl_norm["WplusH_HToBB"]=1.;
qgl_norm["WminusH_HToBB"]=1.;
qgl_norm["ttHTobb_M125"]=1.;
qgl_norm["ttHToNonbb_M125"]=1.;
}

if (dataset_type.CompareTo("double")==0) {
qgl_norm["ST_tW_top"]=0.958732717;
qgl_norm["ST_tW_antitop"]=0.955997449;
qgl_norm["ST_s-channel"]=0.970870396;
qgl_norm["ST_t-channel_top_4f_inclusiveDecays"]=0.963252452;
qgl_norm["ST_t-channel_antitop_4f_inclusiveDecays"]=0.959430186;
qgl_norm["QCD_HT100to200"]=1.008803524;
qgl_norm["QCD_HT200to300"]=1.006402971;
qgl_norm["QCD_HT300to500"]=0.995691058;
qgl_norm["QCD_HT500to700"]=0.993618415;
qgl_norm["QCD_HT700to1000"]=0.982397299;
qgl_norm["QCD_HT1000to1500"]=0.962535992;
qgl_norm["QCD_HT1500to2000"]=0.940583926;
qgl_norm["QCD_HT2000toInf"]=0.919402112;
qgl_norm["VBFHToBB_M-125"]=0.957131979;
qgl_norm["GluGluHToBB_M-125"]=0.995103933;
qgl_norm["WJetsToQQ"]=0.961346624;
qgl_norm["DYJetsToQQ"]=0.961970054;
qgl_norm["TT"]=0.972793373;
qgl_norm["DYJetstoLL_amc_0J"]=1.;
qgl_norm["DYJetstoLL_amc_1J"]=1.;
qgl_norm["DYJetstoLL_amc_2J"]=1.;
qgl_norm["WJetsToLNu"]=1.;

qgl_norm["VBFHToBB_M-125_amc"]=0.978234492;
qgl_norm["VBFHToBB_M-125_ueps_up"]=0.978234492;
qgl_norm["VBFHToBB_M-125_ueps_down"]=0.978234492;
qgl_norm["VBFHToBB_M-125_herwig"]=1.;
qgl_norm["GluGluHToBB_M-125_amc"]=0.985054953;
qgl_norm["GluGluHToBB_M-125_ueps_up"]=0.985054953;
qgl_norm["GluGluHToBB_M-125_ueps_down"]=0.985054953;
qgl_norm["GluGluHToBB_M-125_herwig"]=1.;
qgl_norm["WW"]=1.;
qgl_norm["ZZ"]=1.;
qgl_norm["WZ"]=1.;
qgl_norm["ST_s_inclusive"]=1.;
qgl_norm["bbHToBB_yb2"]=1.;
qgl_norm["bbHToBB_ybyt"]=1.;
qgl_norm["ZH_HToBB"]=1.;
qgl_norm["WplusH_HToBB"]=1.;
qgl_norm["WminusH_HToBB"]=1.;
qgl_norm["ttHTobb_M125"]=1.;
qgl_norm["ttHToNonbb_M125"]=1.;
}


 int counter=0;

Int_t NCATS;
Int_t NCATS_Zbb;
Float_t cats[10];
Float_t cats_Zbb[10];

int set_type;
if (dataset_type.CompareTo("double")==0) set_type=0;
if (dataset_type.CompareTo("single")==0) set_type=1;
int whichTrigWeight;
if ((trigWeight_str.CompareTo("none")==0)||(trigWeight_str.CompareTo("nom")==0)) whichTrigWeight=0;
if (trigWeight_str.CompareTo("up")==0) whichTrigWeight=1;
if (trigWeight_str.CompareTo("down")==0) whichTrigWeight=2;

if (set_type==0) NCATS=4;  //3+1
else if (set_type==1) NCATS=5;//
if (set_type==1) {
	Float_t cats_new[10]={-1.,0.28  , 0.72 ,  0.87,  0.93    ,1. };  //0.9825
	memcpy(cats, cats_new, sizeof cats_new);
}
else if (set_type==0) { 
	Float_t cats_new[10]={-1.,0.36 ,  0.76,   0.89   , 1. };  //0.9725
	memcpy(cats, cats_new, sizeof cats_new);
}
NCATS_Zbb=4;
Float_t cats_new_Zbb[10]={-1., -0.2275 ,  0.1125 ,  0.3425  , 1. };  //0.9725
memcpy(cats_Zbb, cats_new_Zbb, sizeof cats_new_Zbb);



Float_t events_in_cats[10] = {0,0,0,0,0,0,0,0,0,0};
Float_t events_in_cats_80_200[10] = {0,0,0,0,0,0,0,0,0,0};
Float_t events_in_cats_er[10] = {0,0,0,0,0,0,0,0,0,0};
Float_t events_in_cats_er_true[10] = {0,0,0,0,0,0,0,0,0,0};
Float_t events_in_cats_er_true_80_200[10] = {0,0,0,0,0,0,0,0,0,0};
Float_t events_in_cats_er_plus[10] = {0,0,0,0,0,0,0,0,0,0};
Float_t events_in_cats_er_minus[10] = {0,0,0,0,0,0,0,0,0,0};

ULong64_t evt;
UInt_t run;
 
float gen_pos=0; 
float gen_neg=0; 
float gen_pos_weight=0; 
float gen_neg_weight=0; 


int whichJESWeight=0;

	
	Float_t presel=0;
	Float_t presel_vtype[10] = {0,0,0,0,0,0,0,0,0};
	Float_t pos_puweight=0;
	Float_t all_puweight=0.;
	Float_t puweight;
	Float_t PU=1.;
	Float_t genweight;
	Float_t bTagWeight;
	Float_t genweight0;
	float  trigWeight_tree;
	Int_t global_counter = 0;
	Int_t HLT_BIT_HLT_QuadPFJet_BTagCSV_p016_p11_VBF_Mqq200_v;
	Int_t HLT_BIT_HLT_QuadPFJet_BTagCSV_p016_p11_VBF_Mqq240_v;
	Int_t HLT_BIT_HLT_QuadPFJet_BTagCSV_p016_VBF_Mqq460_v;
	Int_t HLT_BIT_HLT_QuadPFJet_BTagCSV_p016_VBF_Mqq500_v;
	TFile *file_initial;
	


	TChain *tree_initial;


	TF1* func_qgl_q = new TF1("func_qgl_q","pol3",0.,1.);
	func_qgl_q->FixParameter(0,0.981581);
	func_qgl_q->FixParameter(1,-0.255505);
	func_qgl_q->FixParameter(2,0.929524);
	func_qgl_q->FixParameter(3,-0.666978);
	TF1* func_qgl_g = new TF1("func_qgl_g","pol7",0.,1.);
	func_qgl_g->FixParameter(0,0.612992);
	func_qgl_g->FixParameter(1,6.27);
	func_qgl_g->FixParameter(2,-34.3663);
	func_qgl_g->FixParameter(3,92.8668);
	func_qgl_g->FixParameter(4,-99.927);
	func_qgl_g->FixParameter(5,-21.1421);
	func_qgl_g->FixParameter(6, 113.218);
	func_qgl_g->FixParameter(7,-55.7067);


	TF1* func_qgl_g_herwig = new TF1("func_qgl_g_herwig","pol7",0.,1.);
	func_qgl_g_herwig->FixParameter(0,0.919838);
	func_qgl_g_herwig->FixParameter(1,3.41825);
	func_qgl_g_herwig->FixParameter(2,-19.2979);
	func_qgl_g_herwig->FixParameter(3,56.7714);
	func_qgl_g_herwig->FixParameter(4,-72.8429);
	func_qgl_g_herwig->FixParameter(5,-16.7487);
	func_qgl_g_herwig->FixParameter(6,111.455);
	func_qgl_g_herwig->FixParameter(7,-63.2397);

	TF1* func_qgl_q_herwig = new TF1("func_qgl_q_herwig","pol3",0.,1.);
	func_qgl_q_herwig->FixParameter(0,0.596896);
	func_qgl_q_herwig->FixParameter(1,1.86096);
	func_qgl_q_herwig->FixParameter(2, -2.45101);
	func_qgl_q_herwig->FixParameter(3,1.16636);



//pythia8 quark (|eta|<2.0, pT inclusive, pythia ): -0.666978*x*x*x + 0.929524*x*x -0.255505*x + 0.981581
//pythia8 gluon (|eta|<2.0, pT inclusive, pythia ): -55.7067*x^7 + 113.218*x^6 -21.1421*x^5 -99.927*x^4 + 92.8668*x^3 -34.3663*x^2 + 6.27*x + 0.612992



	file_initial = TFile::Open(file_name);


	
	tree_initial = (TChain*)file_initial->Get("tree");
	Int_t events_generated;
	TH1F *countPos;
	TH1F *countNeg;
	TH1F *countLHEScale;
	TH1F *countLHEPdf;
	TH1F *countWeighted;
	if ((data!=1)){
		countPos = (TH1F*)file_initial->Get("CountPosWeight");
 		countNeg = (TH1F*)file_initial->Get("CountNegWeight");
 		countWeighted = (TH1F*)file_initial->Get("CountWeighted");
 		countLHEScale = (TH1F*)file_initial->Get("CountWeightedLHEWeightScale");
		countLHEPdf=	(TH1F*)file_initial->Get("CountWeightedLHEWeightPdf");
		events_generated = countWeighted->GetBinContent(1);
		if (events_generated==0) events_generated =  countPos->GetBinContent(1) - countNeg->GetBinContent(1);
	} else events_generated = 1;
    Jets Jet;
    Float_t v_type;
    Float_t wrong_type=0.;
    Int_t nJets;
	Float_t JSON;	
	Float_t nPVs;	
	Float_t rho;	
	Float_t lheHT;	

	Float_t bdt_Zbb, bdt_Zbb_JES_up, bdt_Zbb_JES_down, bdt_Zbb_JER_up, bdt_Zbb_JER_down;
	Float_t bdt_VBF, bdt_VBF_JES_up, bdt_VBF_JES_down, bdt_VBF_JER_up, bdt_VBF_JER_down;
	Int_t passSel_JE[5];
	Int_t VBFpassSel_JE[5];
	Float_t bdt_Zbb_JE[5];
	Float_t bdt_VBF_JE[5];
	Float_t met_pt;
	Float_t met_phi;
	Float_t Jet_corr_JECUp[30], Jet_corr_JECDown[30], Jet_corr[30], Jet_corr_JER[30], Jet_corr_JERUp[30], Jet_corr_JERDown[30];

	Jets GenHiggsSisters;

	int pos_weight_presel=0;
	Int_t  nselLeptons;
 	Int_t selLeptons_tightId[20];
	Float_t selLeptons_relIso03[20] ,selLeptons_relIso04[20], selLeptons_chargedHadRelIso03[20], selLeptons_pfRelIso03[20];
	Float_t vLeptons_dz[20], vLeptons_edz[20];
	Int_t  selLeptons_eleMVAIdSppring16GenPurp[30],selLeptons_charge[30], selLeptons_pdgId[30], selLeptons_looseIdPOG[30]; 



Float_t LHE_weights_pdf_wgt[103];
Float_t LHE_weights_scale_wgt[10];

    tree_initial->SetBranchAddress("Vtype",&v_type);
    tree_initial->SetBranchAddress("rho",&rho);
    tree_initial->SetBranchAddress("nJet",&nJets);
    tree_initial->SetBranchAddress("Jet_pt",Jet.pt);
    tree_initial->SetBranchAddress("Jet_corr_JECUp",Jet.JEC_corr_up);
    tree_initial->SetBranchAddress("Jet_corr_JECDown",Jet.JEC_corr_down);
    tree_initial->SetBranchAddress("Jet_corr",Jet.JEC_corr);
    tree_initial->SetBranchAddress("Jet_corr_JERUp",Jet.JER_corr_up);
    tree_initial->SetBranchAddress("Jet_corr_JERDown",Jet.JER_corr_down);
    tree_initial->SetBranchAddress("Jet_corr_JER",Jet.JER_corr);
    tree_initial->SetBranchAddress("Jet_eta",Jet.eta);
    tree_initial->SetBranchAddress("Jet_phi",Jet.phi);
	tree_initial->SetBranchAddress("Jet_mass",Jet.mass);
	tree_initial->SetBranchAddress("Jet_btagCMVAV2",Jet.btagCMVAV2);
	tree_initial->SetBranchAddress("Jet_btagWeightCMVAV2",Jet.btagCMVAV2_weight);
	tree_initial->SetBranchAddress("Jet_btagCSV",Jet.btagCSV);
	tree_initial->SetBranchAddress("Jet_blikelihood_b",Jet.blike_VBF);
	tree_initial->SetBranchAddress("Jet_id",Jet.id);	
	tree_initial->SetBranchAddress("Jet_puId",Jet.puId);
 	tree_initial->SetBranchAddress("Jet_partonFlavour",Jet.partonFlavour);
 	tree_initial->SetBranchAddress("Jet_leadTrackPt",Jet.leadTrackPt);
	tree_initial->SetBranchAddress("met_pt",&met_pt);
	tree_initial->SetBranchAddress("met_phi",&met_phi);
	
	tree_initial->SetBranchAddress("softActivityJets_pt",Jet.soft_pt);
	tree_initial->SetBranchAddress("softActivityJets_eta",Jet.soft_eta);
	tree_initial->SetBranchAddress("softActivityJets_mass",Jet.soft_mass);
	tree_initial->SetBranchAddress("softActivity_HT",&Jet.HTsoft);
	tree_initial->SetBranchAddress("softActivity_njets2",&Jet.nsoft2);
	tree_initial->SetBranchAddress("softActivity_njets5",&Jet.nsoft5);
	tree_initial->SetBranchAddress("softActivity_njets10",&Jet.nsoft10);
	tree_initial->SetBranchAddress("Jet_qgl",Jet.qgl);
	tree_initial->SetBranchAddress("genWeight",&genweight);
	tree_initial->SetBranchAddress("bTagWeight",&bTagWeight);
	tree_initial->SetBranchAddress("puWeight",&puweight);
	tree_initial->SetBranchAddress("nPVs",&nPVs);
	tree_initial->SetBranchAddress("Jet_ptd",Jet.ptd);
	tree_initial->SetBranchAddress("Jet_axis2",Jet.axis2);
	tree_initial->SetBranchAddress("Jet_mult",Jet.mult);
 	tree_initial->SetBranchAddress("HLT_BIT_HLT_QuadPFJet_BTagCSV_p016_p11_VBF_Mqq200_v",&HLT_BIT_HLT_QuadPFJet_BTagCSV_p016_p11_VBF_Mqq200_v);
 	tree_initial->SetBranchAddress("HLT_BIT_HLT_QuadPFJet_BTagCSV_p016_p11_VBF_Mqq240_v",&HLT_BIT_HLT_QuadPFJet_BTagCSV_p016_p11_VBF_Mqq240_v);
 	tree_initial->SetBranchAddress("HLT_BIT_HLT_QuadPFJet_BTagCSV_p016_VBF_Mqq460_v",&HLT_BIT_HLT_QuadPFJet_BTagCSV_p016_VBF_Mqq460_v);
 	tree_initial->SetBranchAddress("HLT_BIT_HLT_QuadPFJet_BTagCSV_p016_VBF_Mqq500_v",&HLT_BIT_HLT_QuadPFJet_BTagCSV_p016_VBF_Mqq500_v);
//	tree_initial->SetBranchAddress("Jet_pt_reg",Jet.pt_reg);
	tree_initial->SetBranchAddress("Jet_pt_regNew",Jet.pt_reg);
//	tree_initial->SetBranchAddress("Jet_pt_reg_corrJECUp",Jet.pt_reg);
//	tree_initial->SetBranchAddress("Jet_pt_reg_corrJECDown",Jet.pt_reg);
//	tree_initial->SetBranchAddress("Jet_pt_reg_corrJERUp",Jet.pt_reg);
//	tree_initial->SetBranchAddress("Jet_pt_reg_corrJERDown",Jet.pt_reg);
	tree_initial->SetBranchAddress("json",&JSON);
    
	tree_initial->SetBranchAddress("GenHiggsSisters_pt",GenHiggsSisters.pt);
    tree_initial->SetBranchAddress("GenHiggsSisters_eta",GenHiggsSisters.eta);
    tree_initial->SetBranchAddress("GenHiggsSisters_phi",GenHiggsSisters.phi);
	tree_initial->SetBranchAddress("GenHiggsSisters_mass",GenHiggsSisters.mass);

	tree_initial->SetBranchAddress("nselLeptons",&nselLeptons);
	tree_initial->SetBranchAddress("selLeptons_tightId",selLeptons_tightId);
	tree_initial->SetBranchAddress("selLeptons_relIso03",selLeptons_relIso03);
	tree_initial->SetBranchAddress("selLeptons_relIso04",selLeptons_relIso04);
	tree_initial->SetBranchAddress("selLeptons_chargedHadRelIso03",selLeptons_chargedHadRelIso03);
	tree_initial->SetBranchAddress("selLeptons_pdgId",selLeptons_pdgId);
	tree_initial->SetBranchAddress("selLeptons_charge",selLeptons_charge);
	tree_initial->SetBranchAddress("selLeptons_looseIdPOG",selLeptons_looseIdPOG);
   tree_initial->SetBranchAddress("selLeptons_eleMVAIdSppring16GenPurp",selLeptons_eleMVAIdSppring16GenPurp); 
	tree_initial->SetBranchAddress("selLeptons_pfRelIso03",selLeptons_pfRelIso03);
	tree_initial->SetBranchAddress("vLeptons_dz",vLeptons_dz);
	tree_initial->SetBranchAddress("vLeptons_edz",vLeptons_edz);


	tree_initial->SetBranchAddress("Zbb_bdt",&bdt_Zbb);
	tree_initial->SetBranchAddress("Zbb_bdt_JES_up",&bdt_Zbb_JE[0]);
	tree_initial->SetBranchAddress("Zbb_bdt_JES_down",&bdt_Zbb_JE[1]);
	tree_initial->SetBranchAddress("Zbb_bdt_JER_up",&bdt_Zbb_JE[2]);
	tree_initial->SetBranchAddress("Zbb_bdt_JER_down",&bdt_Zbb_JE[3]);
	tree_initial->SetBranchAddress("PassSelection_JES_up",&passSel_JE[0]);
	tree_initial->SetBranchAddress("PassSelection_JES_down",&passSel_JE[1]);
	tree_initial->SetBranchAddress("PassSelection_JER_up",&passSel_JE[2]);
	tree_initial->SetBranchAddress("PassSelection_JER_down",&passSel_JE[3]);
	tree_initial->SetBranchAddress("PassSelection_nom",&passSel_JE[4]);


	tree_initial->SetBranchAddress(dataset_type+"VBF_bdt",&bdt_VBF);
	tree_initial->SetBranchAddress(dataset_type+"VBF_bdt_JES_up",&bdt_VBF_JE[0]);
	tree_initial->SetBranchAddress(dataset_type+"VBF_bdt_JES_down",&bdt_VBF_JE[1]);
	tree_initial->SetBranchAddress(dataset_type+"VBF_bdt_JER_up",&bdt_VBF_JE[2]);
	tree_initial->SetBranchAddress(dataset_type+"VBF_bdt_JER_down",&bdt_VBF_JE[3]);
	tree_initial->SetBranchAddress(dataset_type+"PassSelection_JES_up",&VBFpassSel_JE[0]);
	tree_initial->SetBranchAddress(dataset_type+"PassSelection_JES_down",&VBFpassSel_JE[1]);
	tree_initial->SetBranchAddress(dataset_type+"PassSelection_JER_up",&VBFpassSel_JE[2]);
	tree_initial->SetBranchAddress(dataset_type+"PassSelection_JER_down",&VBFpassSel_JE[3]);
	tree_initial->SetBranchAddress(dataset_type+"PassSelection_nom",&VBFpassSel_JE[4]);


	tree_initial->SetBranchAddress("trigWeight",&trigWeight_tree);
	tree_initial->SetBranchAddress("LHE_weights_pdf_wgt",LHE_weights_pdf_wgt);
	tree_initial->SetBranchAddress("LHE_weights_scale_wgt",LHE_weights_scale_wgt);
	tree_initial->SetBranchAddress("lheHT",&lheHT);

	tree_initial->SetBranchAddress("Jet_corr_JECUp",Jet_corr_JECUp);
	tree_initial->SetBranchAddress("Jet_corr_JECDown",Jet_corr_JECDown);
	tree_initial->SetBranchAddress("Jet_corr",Jet_corr);
	tree_initial->SetBranchAddress("Jet_corr_JERUp",Jet_corr_JERUp);
	tree_initial->SetBranchAddress("Jet_corr_JERDown",Jet_corr_JERDown);
	tree_initial->SetBranchAddress("Jet_corr_JER",Jet_corr_JER);
	tree_initial->SetBranchAddress("evt",&evt);
	tree_initial->SetBranchAddress("run",&run);




	if (data==1){
		genweight = 1.;
		bTagWeight = 1.;
		puweight=1.;
	}

 	
    TH1F *hJet1_pt_bin = new TH1F("hJet1_pt_bin", "", 50, 90., 140.);
    hJet1_pt_bin->GetXaxis()->SetTitle("1^{st} Jet p_{T} (GeV)");
    TH1F *hJet2_pt_bin = new TH1F("hJet2_pt_bin", "", 40, 70., 110.);
    hJet2_pt_bin->GetXaxis()->SetTitle("2^{nd} Jet p_{T} (GeV)");
    TH1F *hJet3_pt_bin = new TH1F("hJet3_pt_bin", "", 30, 60., 90.);
    hJet3_pt_bin->GetXaxis()->SetTitle("3^{rd} Jet p_{T} (GeV)");
    TH1F *hJet4_pt_bin = new TH1F("hJet4_pt_bin", "", 40, 30., 70.);
    hJet4_pt_bin->GetXaxis()->SetTitle("4^{th} Jet p_{T} (GeV)");
	TH1F *hMqq_bin;
	TH1F *hEtaQQ_bin;
	TH1F *hPhiBB_bin;
	TH1F *hMqq_bin2;
	if (dataset_type.CompareTo("double")==0){ 
		 hMqq_bin = new TH1F("hMqq_bin","",60.,240.,300.);
		 hEtaQQ_bin = new TH1F("hEtaQQ_bin","",50,2.3,2.8);
		 hPhiBB_bin = new TH1F("hPhiBB_bin","",30,1.8,2.1);
	}
	if (dataset_type.CompareTo("single")==0) {
		 hMqq_bin = new TH1F("hMqq_bin","",60.,500.,560.);
		 hEtaQQ_bin = new TH1F("hEtaQQ_bin","",50,4.2,4.7);
		 hPhiBB_bin = new TH1F("hPhiBB_bin","",30,1.3,1.6);
	}
	hMqq_bin->GetXaxis()->SetTitle("m_{qq} (GeV)");
	hMqq_bin2 = new TH1F("hMqq_bin2","",200.,500.,700.);
	hMqq_bin2->GetXaxis()->SetTitle("m_{qq} (GeV)");
   
    TH1F *hJet1_pt = new TH1F("hJet1_pt", "", 30, 0., 600.);
    hJet1_pt->GetXaxis()->SetTitle("1^{st} Jet p_{T} (GeV)");
    TH1F *hJet2_pt = new TH1F("hJet2_pt", "", 30, 0., 600.);
    hJet2_pt->GetXaxis()->SetTitle("2^{nd} Jet p_{T} (GeV)");
    TH1F *hJet3_pt = new TH1F("hJet3_pt", "", 20, 0., 400.);
    hJet3_pt->GetXaxis()->SetTitle("3^{rd} Jet p_{T} (GeV)");
    TH1F *hJet4_pt = new TH1F("hJet4_pt", "", 20, 0., 400.);
    hJet4_pt->GetXaxis()->SetTitle("4^{th} Jet p_{T} (GeV)");
    
    TH1F *hJet5_pt = new TH1F("hJet5_pt", "", 25, 0., 500.);
    hJet5_pt->GetXaxis()->SetTitle("5^{th} Jet p_{T} (GeV)");
    
	TH1F *hJet1_eta = new TH1F("hJet1_eta", "", 80, -5., 5.);
    hJet1_eta->GetXaxis()->SetTitle("1^{st} Jet #eta");
    TH1F *hJet2_eta = new TH1F("hJet2_eta", "", 80, -5., 5.);
    hJet2_eta->GetXaxis()->SetTitle("2^{nd} Jet #eta");
    TH1F *hJet3_eta = new TH1F("hJet3_eta", "", 80, -5., 5.);
    hJet3_eta->GetXaxis()->SetTitle("3^{rd} Jet #eta");
    TH1F *hJet4_eta = new TH1F("hJet4_eta", "", 80, -5., 5.);
    hJet4_eta->GetXaxis()->SetTitle("4^{th} Jet #eta");
    
    TH1F *hJet1_phi = new TH1F("hJet1_phi", "", 32,-3.2,3.2);
    hJet1_phi->GetXaxis()->SetTitle("1^{st} Jet #phi");
    TH1F *hJet2_phi = new TH1F("hJet2_phi", "", 32,-3.2,3.2);
    hJet2_phi->GetXaxis()->SetTitle("2^{nd} Jet #phi");
    TH1F *hJet3_phi = new TH1F("hJet3_phi", "", 32,-3.2,3.2);
    hJet3_phi->GetXaxis()->SetTitle("3^{rd} Jet #phi");
    TH1F *hJet4_phi = new TH1F("hJet4_phi", "", 32,-3.2,3.2);
    hJet4_phi->GetXaxis()->SetTitle("4^{th} Jet #phi");
    TH1F *hVtype = new TH1F("hVtype","", 6,-1.,6.);
    hVtype->GetXaxis()->SetTitle("vtype");

	TH1F *hMqq = new TH1F("hMqq","",100.,0.,3000.);
	hMqq->GetXaxis()->SetTitle("m_{qq} (GeV)");
   
	TH1F *hEtaQQ = new TH1F("hEtaQQ","",80,0.,8.);
	hEtaQQ->GetXaxis()->SetTitle("|#Delta#eta_{qq}|");

	TH1F *hPhiQQ = new TH1F("hPhiQQ","",32,0.,3.2);
	hPhiQQ->GetXaxis()->SetTitle("|#Delta#phi_{qq}|");
    
	TH1F *hPhiBB = new TH1F("hPhiBB","",32,0.,3.2);
	hPhiBB->GetXaxis()->SetTitle("|#Delta#phi_{bb}|");
	
	TH1F *hEtaSoftJets = new TH1F("hEtaSoftJets","",12,-3.,3.);
	hEtaSoftJets->GetXaxis()->SetTitle("|#eta^{soft}|");
    
	
	TH1F *hMassSoftJets = new TH1F("hMassSoftJets","",10,0.,100.);
	hMassSoftJets->GetXaxis()->SetTitle("m^{soft}");

	TH1F *hHTsoft = new TH1F("hHTsoft","",60,0.,600.);
	hHTsoft->GetXaxis()->SetTitle("H_{T}^{soft} (GeV)" );
	TH1F *hSoft_n2 = new TH1F("hSoft_n2","",25,0.,25.);
	hSoft_n2->GetXaxis()->SetTitle("N soft jets, p_{T} > 2 GeV");
	TH1F *hSoft_n5 = new TH1F("hSoft_n5","",10,0.,10.);
	hSoft_n5->GetXaxis()->SetTitle("N soft jets, p_{T} > 5 GeV");
	TH1F *hSoft_n10 = new TH1F("hSoft_n10","",6,0.,6.);
	hSoft_n10->GetXaxis()->SetTitle("N soft jets, p_{T} > 10 GeV");
	
	TH1F* hMbb = new TH1F("hMbb","",50,0.,250.);
	hMbb->GetXaxis()->SetTitle("m_{bb} (GeV)");
	TH1F* hqgl = new TH1F("hqgl","",20.,0.,1.);
	hqgl->GetXaxis()->SetTitle("QGL 1^{st} q-jet");
	
	TH1F* hqgl2 = new TH1F("hqgl2","",20.,0.,1.);
	hqgl2->GetXaxis()->SetTitle("QGL 2^{nd} q-jet");

	TH1F *hbtag = new TH1F("hbtag","",100,-1.,1.);
	hbtag->GetXaxis()->SetTitle("CMVAV2 1^{st} b-jet");
 
	TH1F *hbtag2 = new TH1F("hbtag2","",100,-1,1.);
	hbtag2->GetXaxis()->SetTitle("CMVAV2 2^{nd} b-jet");
	
	TH1F *hPtSoftJets = new TH1F("hPtSoftJets","",30,0.,300);
	hPtSoftJets->GetXaxis()->SetTitle("p_{T}^{soft} (GeV)");
    TH1F *hPtSoftJets2 = new TH1F("hPtSoftJets2", "", 20, 0., 200.);
    hPtSoftJets2->GetXaxis()->SetTitle("2nd Soft Jet p_{T} (GeV)");
    TH1F *hPtSoftJets3 = new TH1F("hPtSoftJets3", "", 20, 0., 200.);
    hPtSoftJets3->GetXaxis()->SetTitle("3rd Soft Jet p_{T} (GeV)");
	
	TH1F *hcosOqqbb = new TH1F("hcosOqqbb","",100,-1.,1.);
	hcosOqqbb->GetXaxis()->SetTitle("cos(#theta_{bb_qq})");
	TH1F *hEtaQB1 = new TH1F("hEtaQB1","",160.,-8.,8.);
	hEtaQB1->GetXaxis()->SetTitle("#Delta#eta_{qb}^{forward}");
	TH1F *hEtaQB2 = new TH1F("hEtaQB2","",160.,-8.,8.);
	hEtaQB2->GetXaxis()->SetTitle("#Delta#eta_{qb}^{backward}");
	TH1F *hPhiQB1 = new TH1F("hPhiQB1","",32,0.,3.2);
	hPhiQB1->GetXaxis()->SetTitle("#Delta#phi_{qb}^{forward}");
	TH1F *hPhiQB2 = new TH1F("hPhiQB2","",32,0.,3.2);
	hPhiQB2->GetXaxis()->SetTitle("#Delta#phi_{qb}^{backward}");
	TH1F *hx1 = new TH1F("hx1","",100.,0.,1.);
	hx1->GetXaxis()->SetTitle("x_{1}");
	TH1F *hx2 = new TH1F("hx2","",100.,0.,1.);
	hx2->GetXaxis()->SetTitle("x_{2}");
	TH1F *hVB1_mass = new TH1F("hVB1_mass","",100,0.,1000.);
	hVB1_mass->GetXaxis()->SetTitle("M_{W'_{1}} (GeV)");
	TH1F *hVB2_mass = new TH1F("hVB2_mass","",100.,0.,1000.);
	hVB2_mass->GetXaxis()->SetTitle("M_{W'_{2}} (GeV)");

	TH1F* hEtot = new TH1F("hEtot","",150.,0.,6000.);
	hEtot->GetXaxis()->SetTitle("E^{tot} (GeV)");
	TH1F* hPxtot= new TH1F("hPxtot","",100,-500.,500.);
	hPxtot->GetXaxis()->SetTitle("P_{x}^{tot} (GeV)");
	TH1F* hPytot= new TH1F("hPytot","",100,-500.,500.);
	hPytot->GetXaxis()->SetTitle("P_{y}^{tot} (GeV)");
	TH1F* hPztot= new TH1F("hPztot","",100,-5000.,5000);
	hPztot->GetXaxis()->SetTitle("P_{z}^{tot} (GeV)");

	
	TH1F *hPtqqbb = new TH1F("hPtqqbb","",50.,0.,500.);
	hPtqqbb->GetXaxis()->SetTitle("p_{T} of qqbb system (GeV)");
	TH1F *hPhiqqbb = new TH1F("hPhiqqbb","",32,-3.2,3.2);
	hPhiqqbb->GetXaxis()->SetTitle("-#phi of qqbb system");
	TH1F *hEtaqqbb = new TH1F("hEtaqqbb","",160,0,8);
	hEtaqqbb->GetXaxis()->SetTitle("#eta of qqbb system");

	TH1F *hnPVs = new TH1F("hPVs","",50,0,50);
	hnPVs->GetXaxis()->SetTitle("nPVs");
	
	TH1F* hMbb_regVBF = new TH1F("hMbb_regVBF","",50,0.,250.);
	hMbb_regVBF->GetXaxis()->SetTitle("m_{bb} [Reg] (GeV)");

	TH1F* hMbb_regVBF_fsr = new TH1F("hMbb_regVBF_fsr","",50,0.,250.);
	hMbb_regVBF_fsr->GetXaxis()->SetTitle("m_{bb} [Reg + FSR] (GeV)");
	
	TH1F* hMbb_regVBF_fsr_high = new TH1F("hMbb_regVBF_fsr_high","",200,150.,4150.);
	hMbb_regVBF_fsr_high->GetXaxis()->SetTitle("m_{bb} [Reg + FSR] (GeV)");
	
	TH1F* hMbb_regVBF_fsr_high_cat = new TH1F("hMbb_regVBF_fsr_high_cat","",200,150.,4150.);
	hMbb_regVBF_fsr_high_cat->GetXaxis()->SetTitle("m_{bb} [Reg + FSR] CAT3 (GeV)");
	TH1F* hMbb_regVBF_fsr_high_cat2 = new TH1F("hMbb_regVBF_fsr_high_cat2","",200,150.,4150.);
	hMbb_regVBF_fsr_high_cat2->GetXaxis()->SetTitle("m_{bb} [Reg + FSR] CAT23 (GeV)");

	TH1F *hJet1q_pt = new TH1F("hJet1q_pt","",30,0,600.);
	hJet1q_pt->GetXaxis()->SetTitle("p_{T} 1^{st} q-jet");
	TH1F *hJet1q_eta = new TH1F("hJet1q_eta","",20,-5,5);
	hJet1q_eta->GetXaxis()->SetTitle("#eta 1^{st} q-jet");

	TH1F *hJet1q_phi = new TH1F("hJet1q_phi","",32,-3.2,3.2);
	hJet1q_phi->GetXaxis()->SetTitle("#phi 1^{st} q-jet");
	TH1F *hJet2q_phi = new TH1F("hJet2q_phi","",32,-3.2,3.2);
	hJet2q_phi->GetXaxis()->SetTitle("#phi 2^{nd} q-jet");

	TH1F *hJet1q_ptd = new TH1F("hJet1q_ptd","",100,0,1);
	hJet1q_ptd->GetXaxis()->SetTitle("ptd 1^{st} q-jet");
	TH1F *hJet1q_axis2= new TH1F("hJet1q_axis2","",80,0.,0.16);
	hJet1q_axis2->GetXaxis()->SetTitle("#sigma_{2} 1^{st} q-jet");
	TH1F *hJet1q_mult= new TH1F("hJet1q_mult","",30,0,30.);
	hJet1q_mult->GetXaxis()->SetTitle("N 1^{st} q-jet");
	TH1F *hJet1q_leadTrackPt= new TH1F("hJet1q_leadTrackPt","",20,0,100.);
	hJet1q_leadTrackPt->GetXaxis()->SetTitle("leading track p_{T} 1^{st} q-jet");


	TH1F *hJet2q_pt = new TH1F("hJet2q_pt","",30,0,600);
	hJet2q_pt->GetXaxis()->SetTitle("p_{T} 2^{nd} q-jet");
	TH1F *hJet2q_eta = new TH1F("hJet2q_eta","",20,-5,5);
	hJet2q_eta->GetXaxis()->SetTitle("#eta 2^{nd} q-jet");
	TH1F *hJet2q_ptd = new TH1F("hJet2q_ptd","",100,0,1);
	hJet2q_ptd->GetXaxis()->SetTitle("ptd 2^{nd} q-jet");
	TH1F *hJet2q_axis2= new TH1F("hJet2q_axis2","",80,0.,0.16);
	hJet2q_axis2->GetXaxis()->SetTitle("#sigma_{2} 2^{nd} q-jet");

	TH1F *hist_bins = new TH1F("bins","",80,0.,0.16);
	


	TH1F *hJet2q_mult= new TH1F("hJet2q_mult","",30,0,30.);
	hJet2q_mult->GetXaxis()->SetTitle("N 2^{nd} q-jet");
	TH1F *hJet2q_leadTrackPt= new TH1F("hJet2q_leadTrackPt","",20,0,100.);
	hJet2q_leadTrackPt->GetXaxis()->SetTitle("leading track p_{T} 2^{nd} q-jet");

	TH1F *hblike1 = new TH1F("hblike1","",100,-1,1);
	hblike1->GetXaxis()->SetTitle("b-likelihood of 1^{st} b-jet");
	TH1F *hblike2 = new TH1F("hblike2","",100,-1,1);
	hblike2->GetXaxis()->SetTitle("b-likelihood of 2^{nd} b-jet");

	TH1F *hmet = new TH1F("hmet","",100,0.,1000.);
	hmet->GetXaxis()->SetTitle("MET p_{T} (GeV)");
	TH1F *hrho = new TH1F("hrho","",60,0.,30.);
	hrho->GetXaxis()->SetTitle("rho");


	TH1F *hselLeptons_tightId = new TH1F("hselLeptons_tightId","",8,-2.5,5.5 );
	hselLeptons_tightId->GetXaxis()->SetTitle("selLeptons_tightId[0]");
	TH1F *hselLeptons_relIso03= new TH1F("hselLeptons_relIso03","",55,-5.5,0. );
	hselLeptons_relIso03->GetXaxis()->SetTitle("selLeptons_relIso03[0]");
	TH1F *hselLeptons_chargedHadRelIso03 = new TH1F("hselLeptons_chargedHadRelIso03","",55,-5.5,0. );
	hselLeptons_chargedHadRelIso03->GetXaxis()->SetTitle("selLeptons_chargedHadRelIso03[0]");
	TH1F *hselLeptons_pfRelIso03= new TH1F("hselLeptons_pfRelIso03","",55,-5.5,0. );
	hselLeptons_pfRelIso03->GetXaxis()->SetTitle("selLeptons_pfRelIso03[0]");

	TH1F *hselLeptons_relIso03_2= new TH1F("hselLeptons_relIso03_2","",55,-5.5,0. );
	hselLeptons_relIso03_2->GetXaxis()->SetTitle("selLeptons_relIso03[1]");
	TH1F *hselLeptons_chargedHadRelIso03_2 = new TH1F("hselLeptons_chargedHadRelIso03_2","",55,-5.5,0. );
	hselLeptons_chargedHadRelIso03_2->GetXaxis()->SetTitle("selLeptons_chargedHadRelIso03[1]");
	TH1F *hselLeptons_pfRelIso03_2= new TH1F("hselLeptons_pfRelIso03_2","",55,-5.5,0. );
	hselLeptons_pfRelIso03_2->GetXaxis()->SetTitle("selLeptons_pfRelIso03[1]");



	TH1F *hbdt = new TH1F("hbdt","",100,-1,1);
	hbdt->GetXaxis()->SetTitle("BDT output");
	TH1F *hbdt_fine = new TH1F("hbdt_fine","",400,-1,1);
	hbdt_fine->GetXaxis()->SetTitle("BDT output");

	TH1F *hbdt_Zbb = new TH1F("hbdt_Zbb","",100,-1,1);
	hbdt_Zbb->GetXaxis()->SetTitle("BDT output");
	
	TH1F *hbdt_Zbb_fine = new TH1F("hbdt_Zbb_fine","",400,-1,1);
	hbdt_Zbb_fine->GetXaxis()->SetTitle("BDT output");

	TH1F *hbdt_first = new TH1F("hbdt_first","",1000,-1,1);
	hbdt_first->GetXaxis()->SetTitle("BDT output");

	TH1F *hbdt_second = new TH1F("hbdt_second","",1000,-1,1);
	hbdt_second->GetXaxis()->SetTitle("BDT output");

	
	TH1F *hbtag_log = new TH1F("hbtag_log","",120,-2.,10);
	hbtag_log->GetXaxis()->SetTitle("-log(1-CMVAV2), 1^{st} b-jet");
	TH1F *hbtag2_log = new TH1F("hbtag2_log","",120,-2.,10);
	hbtag2_log->GetXaxis()->SetTitle("-log(1-CMVAV2), 2^{nd} b-jet");

 	TProfile *hprof_VBF  = new TProfile("hprof_VBF","",100,-1.,1.,0.,200.);
	hprof_VBF->GetXaxis()->SetTitle("BDT output");
	hprof_VBF->GetYaxis()->SetTitle("<m_{bb}> (GeV)");

 	TProfile *hprof_VBF_range  = new TProfile("hprof_VBF_range","",100,-1.,1.,0.,200.);
	hprof_VBF_range->GetXaxis()->SetTitle("BDT output");
	hprof_VBF_range->GetYaxis()->SetTitle("<m_{bb}> (GeV)");

 	TProfile *hprof_Zbb  = new TProfile("hprof_Zbb","",100,-1.,1.,0.,200.);
	hprof_Zbb->GetXaxis()->SetTitle("BDT output");
	hprof_Zbb->GetYaxis()->SetTitle("<m_{bb}> (GeV)");

 	TProfile *hprof_Zbb_range  = new TProfile("hprof_Zbb_range","",100,-1.,1.,0.,200.);
	hprof_Zbb_range->GetXaxis()->SetTitle("BDT output");
	hprof_Zbb_range->GetYaxis()->SetTitle("<m_{bb}> (GeV)");

	
	TH1F *hMbbcat3 = new TH1F("hMbbcat3","",300.,200.,3200.);
	hMbbcat3->GetXaxis()->SetTitle("m_{bb} (GeV)");
	TH1F* hMbbcat2 = new TH1F("hMbbcat2","",300,200.,3200.);
	hMbbcat2->GetXaxis()->SetTitle("m_{bb} (GeV)");
	TH1F* hMbbcat1 = new TH1F("hMbbcat1","",300,200.,3200.);
	hMbbcat1->GetXaxis()->SetTitle("m_{bb} (GeV)");

	TH1F *hMbb_Zbbcat3 = new TH1F("hMbb_Zbbcat3","",70.,60.,130.);
	hMbb_Zbbcat3->GetXaxis()->SetTitle("m_{bb} (GeV)");
	TH1F* hMbb_Zbbcat2 = new TH1F("hMbb_Zbbcat2","",70,60.,130.);
	hMbb_Zbbcat2->GetXaxis()->SetTitle("m_{bb} (GeV)");
	TH1F* hMbb_Zbbcat1 = new TH1F("hMbb_Zbbcat1","",70,60.,130.);
	hMbb_Zbbcat1->GetXaxis()->SetTitle("m_{bb} (GeV)");
	TH1F* hMbb_Zbbcat0 = new TH1F("hMbb_Zbbcat0","",70,60.,130.);
	hMbb_Zbbcat0->GetXaxis()->SetTitle("m_{bb} (GeV)");


	TH1F *hvLeptons_dz = new TH1F("hvLeptons_dz","",100,0.,0.2);
	hvLeptons_dz->GetXaxis()->SetTitle("vLeptons_dz");
	TH1F *hvLeptons_edz = new TH1F("hvLeptons_edz","",100,0.,0.2);
	hvLeptons_edz->GetXaxis()->SetTitle("vLeptons_edz");
	TH1F *hvLeptons_sig = new TH1F("hvLeptons_sig","",200,0.,10.);
	hvLeptons_sig->GetXaxis()->SetTitle("vLeptons_significance");



	///// for JEC and JER
	
	TH1F *hbdt_JECnom = new TH1F("hbdt_JECnom","",NCATS,cats);
	hbdt_JECnom->GetXaxis()->SetTitle("BDT output");
	TH1F *hbdt_JECup = new TH1F("hbdt_JECup","",NCATS,cats);
	hbdt_JECup->GetXaxis()->SetTitle("BDT output");
	TH1F *hbdt_JECdown = new TH1F("hbdt_JECdown","",NCATS,cats);
	hbdt_JECdown->GetXaxis()->SetTitle("BDT output");
	TH1F *hbdt_JERnom = new TH1F("hbdt_JERnom","",NCATS,cats);
	hbdt_JERnom->GetXaxis()->SetTitle("BDT output");
	TH1F *hbdt_JERup = new TH1F("hbdt_JERup","",NCATS,cats);
	hbdt_JERup->GetXaxis()->SetTitle("BDT output");
	TH1F *hbdt_JERdown = new TH1F("hbdt_JERdown","",NCATS,cats);
	hbdt_JERdown->GetXaxis()->SetTitle("BDT output");

		
    TH1F *hJet1b_pt = new TH1F("hJet1b_pt", "", 30, 0., 600.);
    hJet1b_pt->GetXaxis()->SetTitle("1^{st}b-jet p_{T} (GeV)");
    TH1F *hJet2b_pt = new TH1F("hJet2b_pt", "", 30, 0., 600.);
    hJet2b_pt->GetXaxis()->SetTitle("2^{nd} b-jet p_{T} (GeV)");
    TH1F *hJetbb_pt = new TH1F("hJetbb_pt", "", 30, 0., 600.);
    hJetbb_pt->GetXaxis()->SetTitle("bb p_{T} (GeV)");
    TH1F *hJetqqbb_pz = new TH1F("hJetqqbb_pz", "", 30, 0., 1800.);
    hJetqqbb_pz->GetXaxis()->SetTitle("qqbb p_{z} (GeV)");
    
    TH1F *hJet1cvs_pt = new TH1F("hJet1cvs_pt", "", 45, 0., 900.);
    hJet1cvs_pt->GetXaxis()->SetTitle("highest CSV jet p_{T} (GeV)");
    
	TH1F *hJet1b_eta = new TH1F("hJet1b_eta", "", 80, -5., 5.);
    hJet1b_eta->GetXaxis()->SetTitle("1^{st} b-jet #eta");
    TH1F *hJet2b_eta = new TH1F("hJet2b_eta", "", 80, -5., 5.);
    hJet2b_eta->GetXaxis()->SetTitle("2^{nd} b-jet #eta");
	TH1F *hEtaQBplus = new TH1F("hEtaQBplus","",160.,-8.,8.);
	hEtaQBplus->GetXaxis()->SetTitle("#Delta#eta_{qb}^{forward}+#Delta#eta_{qb}^{backward}");
	TH1F *hEtaQBminus = new TH1F("hEtaQBminus","",160.,-8.,8.);
	hEtaQBminus->GetXaxis()->SetTitle("#Delta#eta_{qb}^{forward}-#Delta#eta_{qb}^{backward}");
	

	TH1F *hlheHT = new TH1F("hlheHT","",100,0.,6000.);
	hlheHT->GetXaxis()->SetTitle("lhe H_{T} (GeV)" );


    TH1F *hphi_metJet = new TH1F("hphi_metJet", "", 32,0,3.2);
    hphi_metJet->GetXaxis()->SetTitle("min #Delta#phi(met,jet)");


   		const int numArray= 108; 
   		TH1F* histArray[numArray] = {hJet1_pt,hJet2_pt,hJet3_pt,hJet4_pt,  hJet1_eta,hJet2_eta,hJet3_eta,hJet4_eta,  hJet1_phi,hJet2_phi,hJet3_phi,hJet4_phi, hMqq, hEtaQQ, hPhiBB, hEtaSoftJets, hPtSoftJets,hMassSoftJets,hHTsoft,hSoft_n2,hSoft_n5,hSoft_n10,hMbb,hqgl,hbtag,hqgl2,hbtag2,hPtSoftJets2,hPtSoftJets3,hcosOqqbb,hEtaQB1, hEtaQB2, hPhiQB1, hPhiQB2,hx1,hx2,hVB1_mass, hVB2_mass, hEtot, hPxtot, hPytot, hPztot, hJet5_pt,hPtqqbb, hPhiqqbb, hEtaqqbb, hJet1_pt_bin,hJet2_pt_bin,hJet3_pt_bin,hJet4_pt_bin, hMqq_bin,hMqq_bin2,hEtaQQ_bin, hPhiBB_bin, hnPVs, hMbb_regVBF, hMbb_regVBF_fsr, hJet1q_pt, hJet1q_eta, hJet1q_ptd, hJet1q_axis2, hJet1q_mult, hJet2q_pt, hJet2q_eta, hJet2q_ptd, hJet2q_axis2, hJet2q_mult,hblike1,hblike2, hmet,  hselLeptons_tightId , hselLeptons_relIso03 , hselLeptons_chargedHadRelIso03, hselLeptons_pfRelIso03, hPhiQQ,  hbtag_log, hbtag2_log, hMbb_regVBF_fsr_high,    hvLeptons_dz, hvLeptons_edz, hvLeptons_sig, hrho, hJet1q_leadTrackPt, hJet2q_leadTrackPt, hJet1b_pt, hJet2b_pt, hJet1b_eta, hJet2b_eta, hJetbb_pt, hJetqqbb_pz, hEtaQBplus, hEtaQBminus,hlheHT,hJet1cvs_pt ,hphi_metJet, hselLeptons_relIso03_2 , hselLeptons_chargedHadRelIso03_2, hselLeptons_pfRelIso03_2, hbdt_Zbb,hbdt_Zbb_fine,hbdt, hbdt_fine,  hMbb_Zbbcat3, hMbb_Zbbcat2, hMbb_Zbbcat1, hMbb_Zbbcat0 , hJet1q_phi, hJet2q_phi};
			for (int i=0;i<numArray;i++){
				histArray[i]->Sumw2();
			}



	TH1F *hGenerated = new TH1F("Generated","",1,0.,1.);
	hGenerated->GetXaxis()->SetTitle("total events weighted");
	TFile outputtree_fileZbb(output+"/FitZbb_"+file_tag+"_"+region+"_"+dataset_type+"_trig"+trigWeight_str+"_"+heppyVersion+"_"+postfix+".root","recreate");
	TDirectory *tree_dir = outputtree_fileZbb.mkdir("Zbb");
	tree_dir->cd();
	TTree *output_tree = new TTree("events","events");
	float treeZbb_mbbRegFSR=0;
	float treeZbb_bdt_Zbb=0;
	float treeZbb_totalWeight=0.;
	float treeZbb_xsec=1.;
	output_tree->Branch("mbbRegFSR",&treeZbb_mbbRegFSR,"mbbRegFSR/F");
	output_tree->Branch("bdt_Zbb",&treeZbb_bdt_Zbb,"bdt_Zbb/F");
	output_tree->Branch("totalWeight",&treeZbb_totalWeight,"totalWeight/F");
	output_tree->Branch("xsec",&treeZbb_xsec,"xsec/F");


	
	TFile outputtree_fileVBF(output+"/FitVBF_"+file_tag+"_"+region+"_"+dataset_type+"_trig"+trigWeight_str+"_"+heppyVersion+"_"+postfix+".root","recreate");
	TDirectory *tree_dir_VBF = outputtree_fileVBF.mkdir("VBF");
	tree_dir_VBF->cd();
	TTree *output_tree_VBF = new TTree("events","events");
	float treeVBF_mbbRegFSR=0;
	float treeVBF_bdt_VBF=0;
	float treeVBF_totalWeight=0.;
	float treeVBF_xsec=1.;
	output_tree_VBF->Branch("mbbRegFSR",&treeVBF_mbbRegFSR,"mbbRegFSR/F");
	output_tree_VBF->Branch("bdt_VBF",&treeVBF_bdt_VBF,"bdt_VBF/F");
	output_tree_VBF->Branch("totalWeight",&treeVBF_totalWeight,"totalWeight/F");
	output_tree_VBF->Branch("xsec",&treeVBF_xsec,"xsec/F");




	TF1 *func_r = new TF1("erffunc",erf,0.,1000.,3);
	TF1 *func_erf_btag= new TF1("func_erf_btag","1.+ [3] + [0]/2.*(1.-TMath::Erf((x-[1])/[2]))",-10.,600.);

	int nentries = tree_initial->GetEntries() ;

	int all_loop=0;	

	for (int entry=0; entry<nentries;++entry){
//	for (int entry=0; entry<200;++entry){
        tree_initial->GetEntry(entry);

	//	if (run<281613) continue; //runH only

		for (int i=0;i<nJets;i++){
			if (whichJESWeight==1) {
				if ((Jet_corr_JECUp[i]<=0)||(Jet_corr[i]<=0)){ Jet.pt[i] = Jet.pt[i]; Jet.mass[i] = Jet.mass[i];}
				else {
					Jet.pt[i] = Jet.pt[i]*Jet_corr_JECUp[i]/Jet_corr[i];  Jet.mass[i]=Jet.mass[i]*Jet_corr_JECUp[i]/Jet_corr[i]; 
				} 
			}

			if (whichJESWeight==2) {
				if ((Jet_corr_JECDown[i]<=0)||(Jet_corr[i]<=0)){ Jet.pt[i] = Jet.pt[i]; Jet.mass[i] = Jet.mass[i];}
				else {
					Jet.pt[i] = Jet.pt[i]*Jet_corr_JECDown[i]/Jet_corr[i];Jet.mass[i]=Jet.mass[i]*Jet_corr_JECDown[i]/Jet_corr[i];
				}	
			}
		}



		if (JSON!=1) {
			continue;
		}
	
		int pass_el=0;
		int pass_mu=0;
		int count_l_el=0;
		int count_l_mu=0;
		int idx_1stLepton_el = 0;
		int idx_2ndLepton_el = 0;
		int idx_1stLepton_mu = 0;
		int idx_2ndLepton_mu = 0;
		all_loop+=1;
		int good_jets = 0;
		vector<TLorentzVector> jets_pv;
		vector<int> jets_indices;
		vector<pair<int, float> > btag_vec;	
		vector<pair<int, float> > csv_vec;	
		vector<pair<int, float> > blike_vec;	
		vector<pair<int, float> > pt_vec;	
		pair<int,float> aPair;
		float jets_btag_weight=1.;

		int current_syst = 10; 

		for (int i=0;i<nJets;i++){
	//	cout<<Jet.pt[i]<<" , ";
			if (current_syst==0) {
				if ((Jet_corr_JECUp[i]<=0)||(Jet_corr[i]<=0)){ Jet.pt[i] = Jet.pt[i]; Jet.mass[i] = Jet.mass[i];}
				else {
					Jet.pt[i] = Jet.pt[i]*Jet_corr_JECUp[i]/Jet_corr[i];  Jet.mass[i]=Jet.mass[i]*Jet_corr_JECUp[i]/Jet_corr[i]; 
				} 
			}
			if (current_syst==1) {
		//		cout<<Jet_pt[0]<<"  ";
				if ((Jet_corr_JECDown[i]<=0)||(Jet_corr[i]<=0)){ Jet.pt[i] = Jet.pt[i]; Jet.mass[i] = Jet.mass[i];}
				else {
					Jet.pt[i] = Jet.pt[i]*Jet_corr_JECDown[i]/Jet_corr[i];Jet.mass[i]=Jet.mass[i]*Jet_corr_JECDown[i]/Jet_corr[i];
		//		cout<<Jet_pt[0]<<endl;
				}
			}
			if (current_syst==2) {
				if ((Jet_corr_JERUp[i]<=0)||(Jet_corr_JER[i]<=0)){ Jet.pt[i] = Jet.pt[i]; Jet.mass[i] = Jet.mass[i];}
				else	{
					Jet.pt[i] =  Jet.pt[i]*Jet_corr_JERUp[i]/Jet_corr_JER[i]; 
					Jet.mass[i]=Jet.mass[i]*Jet_corr_JERUp[i]/Jet_corr_JER[i];
				}
			}
			if (current_syst==3) {
				if ((Jet_corr_JERDown[i]<=0)||(Jet_corr_JER[i]<=0)){ Jet.pt[i] = Jet.pt[i]; Jet.mass[i] = Jet.mass[i];}
				else {
					Jet.pt[i] =  Jet.pt[i]*Jet_corr_JERDown[i]/Jet_corr_JER[i];
					Jet.mass[i]=Jet.mass[i]*Jet_corr_JERDown[i]/Jet_corr_JER[i];
				} 
			}
		}
//		cout<<"after"<<endl;

		for (int i=0;i<nJets;i++){
//			cout<<Jet.pt[i]<<" , ";
			TLorentzVector jet0;
			if (!((Jet.id[i]>2)&&(Jet.puId[i]>0)&&(Jet.pt[i]>20) )) continue;
			jet0.SetPtEtaPhiM(Jet.pt[i],Jet.eta[i],Jet.phi[i],Jet.mass[i]);
			jets_pv.push_back(jet0);
			jets_indices.push_back(i);
			aPair.first = good_jets;
			aPair.second = Jet.btagCMVAV2[i];
			btag_vec.push_back(aPair);
			aPair.first = good_jets;
			aPair.second = Jet.pt[i];
			pt_vec.push_back(aPair);
			aPair.first = good_jets;
			aPair.second = Jet.blike_VBF[good_jets]; ////_VBF[good_jets] !!!!!!
			blike_vec.push_back(aPair);
			aPair.first = good_jets;
			aPair.second = Jet.btagCSV[i];
			csv_vec.push_back(aPair);
			good_jets++;
		}
	//	cout<<endl;
	
		if (good_jets<4)continue;

		Float_t c=-0.853212; 
		for (int i=0;i<nJets;i++){
			if ((Jet.btagCMVAV2[i]>-0.853213) &&(Jet.btagCMVAV2[i]<-0.853211)) Jet.btagCMVAV2[i]=-10.;
		}
		for (int i=0;i<good_jets;i++){
			if ((btag_vec[i].second>-0.853213) &&(btag_vec[i].second<-0.853211)) 	btag_vec[i].second=-10.;
		}



		if (region.CompareTo("analysis")==0) {
			if (!((v_type==-1)||(v_type>3))) continue;
	
		} 
		else if (region.CompareTo("controlTop")==0) {
			if (!((v_type==2)||(v_type==3))) continue;  ///leave it as it is
			if (met_pt<50) continue;
			if (!(selLeptons_relIso03[0]<0.15)) continue;
	//		if (!(selLeptons_chargedHadRelIso03[0]<0.05)) continue;
		}
		else if (region.CompareTo("controlDY")==0) {
			// either muons or electrons, looseId and looseIso (0.15 for eelectrons for Iso, 0.25 for muons) 
			for (int i=0; i<nselLeptons;i++ ){
				if (!((selLeptons_eleMVAIdSppring16GenPurp[i]>=1)&& (selLeptons_relIso03[i]<0.15)&& (TMath::Abs(selLeptons_pdgId[i])==11))) continue;
				if (count_l_el==0) idx_1stLepton_el=i;
				if (count_l_el==1) idx_2ndLepton_el=i;
				count_l_el++;
			}
			for (int i=0; i<nselLeptons;i++ ){
				if (!((selLeptons_looseIdPOG[i]>0) && (selLeptons_relIso04[i]<0.25) && (TMath::Abs(selLeptons_pdgId[i])==13 )) ) continue;
				if (count_l_mu==0) idx_1stLepton_mu=i;
				if (count_l_mu==1) idx_2ndLepton_mu=i;
				count_l_mu++;
			}
		if (! ((count_l_el>=2)||(count_l_mu>=2)) )  continue;
		if (count_l_el>=2) if ((selLeptons_charge[idx_1stLepton_el]*selLeptons_charge[idx_2ndLepton_el]) < 0) pass_el=1;
		if (count_l_mu>=2) if ((selLeptons_charge[idx_1stLepton_mu]*selLeptons_charge[idx_2ndLepton_mu]) < 0) pass_mu=1;
		if (! ((pass_el==1)|| (pass_mu==1)) ) continue;
		}
		

		if (data==1) PU=1.;
		else PU=puweight;
		genweight0 = genweight/TMath::Abs(genweight);
		genweight=genweight/TMath::Abs(genweight)*PU;
	

/////////////////////////preselection////////////////////////////////////////
////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////

		int btag_num1 = -1;
		int btag_num2 = -1;
		int pt_num1 = -1;
		int pt_num2 = -1;
		TLorentzVector Bjet1;
		TLorentzVector Bjet2;
		TLorentzVector Qjet1;
		TLorentzVector Qjet2;
		TLorentzVector qq;
		TLorentzVector bb;
		
		int loopJet_max = min(7,good_jets);

		std::sort(btag_vec.begin(), btag_vec.begin()+loopJet_max,sort_pred() );
		std::sort(blike_vec.begin(), blike_vec.begin()+loopJet_max,sort_pred() );
		std::sort(pt_vec.begin(), pt_vec.begin()+loopJet_max,sort_pred() );
		std::sort(csv_vec.begin(), csv_vec.begin()+loopJet_max,sort_pred() );


		Int_t trigger_single=HLT_BIT_HLT_QuadPFJet_BTagCSV_p016_VBF_Mqq460_v || HLT_BIT_HLT_QuadPFJet_BTagCSV_p016_VBF_Mqq500_v;
		Int_t trigger_double=HLT_BIT_HLT_QuadPFJet_BTagCSV_p016_p11_VBF_Mqq200_v || HLT_BIT_HLT_QuadPFJet_BTagCSV_p016_p11_VBF_Mqq240_v;
		if (dataset_type.CompareTo("double")==0){
			if (preselection_single(trigger_single, loopJet_max, jets_pv, blike_vec, pt_vec, btag_num1, btag_num2, pt_num1, pt_num2)==0) continue;   //if passes single -> we don't want to put it in double set
			if (preselection_double(trigger_double, loopJet_max, jets_pv, btag_vec, pt_vec, btag_num1, btag_num2, pt_num1, pt_num2)!=0) continue;   //should pass double selection
		}
		if (dataset_type.CompareTo("single")==0){
			if (preselection_single(trigger_single, loopJet_max, jets_pv, blike_vec, pt_vec, btag_num1, btag_num2, pt_num1, pt_num2)!=0) continue;
		}


////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////
		Bjet1.SetPtEtaPhiM(jets_pv[btag_num1].Pt(),jets_pv[btag_num1].Eta(),jets_pv[btag_num1].Phi(),jets_pv[btag_num1].M());	
		Bjet2.SetPtEtaPhiM(jets_pv[btag_num2].Pt(),jets_pv[btag_num2].Eta(),jets_pv[btag_num2].Phi(),jets_pv[btag_num2].M());	
		Qjet1.SetPtEtaPhiM(jets_pv[pt_num1].Pt(),jets_pv[pt_num1].Eta(),jets_pv[pt_num1].Phi(),jets_pv[pt_num1].M());	
		Qjet2.SetPtEtaPhiM(jets_pv[pt_num2].Pt(),jets_pv[pt_num2].Eta(),jets_pv[pt_num2].Phi(),jets_pv[pt_num2].M());	
		qq=Qjet1+Qjet2;
		bb=Bjet1+Bjet2;
		Float_t Mqq = qq.M();
		Float_t bbDeltaPhi = TMath::Abs(Bjet1.DeltaPhi(Bjet2));
		Float_t qqDeltaEta = TMath::Abs(Qjet1.Eta()-Qjet2.Eta());
		Float_t qqDeltaPhi = TMath::Abs(Qjet1.DeltaPhi(Qjet2));
		Float_t Mbb = bb.M();
//		cout<<Bjet1.Pt()<<"  "<<Bjet2.Pt()<<endl;


		Float_t alpha_bjet1_reg = 1.;
		Float_t alpha_bjet2_reg = 1.;
		if (Jet.pt_reg[btag_num1]>0.) alpha_bjet1_reg = Jet.pt_reg[btag_num1]/Jet.pt[jets_indices[btag_num1]];
		if (Jet.pt_reg[btag_num2]>0.) alpha_bjet2_reg = Jet.pt_reg[btag_num2]/Jet.pt[jets_indices[btag_num2]];
		Float_t Mbb_reg = (alpha_bjet1_reg*Bjet1 + alpha_bjet2_reg*Bjet2).M(); 
		Float_t Mbb_reg_fsr=0;
		int fsr_bjet=0;
		TLorentzVector FSRjet;

		for (int i=0;i<good_jets;i++){
			if ((i!=btag_num1)&&(i!=btag_num2)&&(i!=pt_num1)&&(i!=pt_num2)){
				FSRjet.SetPtEtaPhiM(jets_pv[i].Pt(),jets_pv[i].Eta(),jets_pv[i].Phi(),jets_pv[i].M());
				if ((FSRjet.DeltaR(Bjet1)<0.8) || (FSRjet.DeltaR(Bjet2)<0.8)) {
					fsr_bjet++;
					break;
				} 
			}
		}

		if (fsr_bjet>0) Mbb_reg_fsr=(alpha_bjet1_reg*Bjet1 + alpha_bjet2_reg*Bjet2 + FSRjet).M();
		else  Mbb_reg_fsr=(alpha_bjet1_reg*Bjet1 + alpha_bjet2_reg*Bjet2).M();


		Bjet1*=alpha_bjet1_reg;	
		Bjet2*=alpha_bjet2_reg;	

//		cout<<Bjet1.Pt()<<"  "<<Bjet2.Pt()<<endl;

		TLorentzVector bbqq;
		bbqq = Bjet1 + Bjet2 + Qjet1 + Qjet2;

		Float_t cosObbqq =TMath::Cos( ( ( Bjet1.Vect() ).Cross(Bjet2.Vect()) ).Angle( ( Qjet1.Vect() ).Cross(Qjet2.Vect()) ) );	

		Float_t EtaBQ1;
	 	Float_t EtaBQ2;
		Float_t PhiBQ1; 	
		Float_t PhiBQ2;
		 if (Qjet1.Eta() >= Qjet2.Eta()) {
			if (Bjet1.Eta() >= Bjet2.Eta())  {
				EtaBQ1 = Qjet1.Eta()-Bjet1.Eta();
				PhiBQ1 = TMath::Abs(Bjet1.DeltaPhi(Qjet1));		
			}
			else {
				EtaBQ1 = Qjet1.Eta()-Bjet2.Eta();
				PhiBQ1 = TMath::Abs(Bjet2.DeltaPhi(Qjet1));	
			}	
		} else if (Bjet1.Eta() >= Bjet2.Eta()) {
				EtaBQ1 = Qjet2.Eta()-Bjet1.Eta();
				PhiBQ1 = TMath::Abs(Bjet1.DeltaPhi(Qjet2));	
				
				}
			else {
				EtaBQ1 = Qjet2.Eta()-Bjet2.Eta();
				PhiBQ1 = TMath::Abs(Bjet2.DeltaPhi(Qjet2));	
			}


		 if (Qjet1.Eta() <= Qjet2.Eta()) {
			if (Bjet1.Eta() <= Bjet2.Eta())  {
				EtaBQ2 = Qjet1.Eta()-Bjet1.Eta();
				PhiBQ2 = TMath::Abs(Bjet1.DeltaPhi(Qjet1));		
			}
			else {
				EtaBQ2 = Qjet1.Eta()-Bjet2.Eta();
				PhiBQ2 = TMath::Abs(Bjet2.DeltaPhi(Qjet1));	
			}	
		} else if (Bjet1.Eta() <= Bjet2.Eta()) {
				EtaBQ2 = Qjet2.Eta()-Bjet1.Eta();
				PhiBQ2 = TMath::Abs(Bjet1.DeltaPhi(Qjet2));	
				
				}
			else {
				EtaBQ2 = Qjet2.Eta()-Bjet2.Eta();
				PhiBQ2 = TMath::Abs(Bjet2.DeltaPhi(Qjet2));	
			}
		


		Float_t Etot = Bjet1.E()+Bjet2.E()+Qjet1.E()+Qjet2.E();
		Float_t PzTot = Bjet1.Pz()+Bjet2.Pz()+Qjet1.Pz()+Qjet2.Pz();
		Float_t PxTot = Bjet1.Px()+Bjet2.Px()+Qjet1.Px()+Qjet2.Px();
		Float_t PyTot = Bjet1.Py()+Bjet2.Py()+Qjet1.Py()+Qjet2.Py();
	
		Float_t x1 = 0.;
		Float_t x2 = 0.;
		x1 = (Etot + PzTot)/2./13000.;
		x2 = (Etot - PzTot)/2./13000.;

		TLorentzVector q1,q2,q1_after,q2_after, VB1, VB2;
		Float_t VB1_mass = -1;
		Float_t VB2_mass = -1.;
		
		q1.SetPxPyPzE(0.,0.,13000./2.*x1,13000./2.*x1);
		q2.SetPxPyPzE(0.,0.,-13000./2.*x2,13000./2.*x2);
		q1_after.SetPxPyPzE(Qjet1.Px(),Qjet1.Py(),Qjet1.Pz(),Qjet1.E());
		q2_after.SetPxPyPzE(Qjet2.Px(),Qjet2.Py(),Qjet2.Pz(),Qjet2.E());
		if (q1_after.Eta()>=0.) {
			VB1 = -q1_after+q1;
			VB2 = -q2_after+q2;
		} else {
			VB1 = -q2_after+q1;
			VB2 = -q1_after+q2;
		} 
		VB1_mass = TMath::Abs(VB1.M());
		VB2_mass = TMath::Abs(VB2.M()); 

		Float_t Jet5pt = 0;
		for (int i=0;i<loopJet_max;i++){
			if ((i==btag_num1)||(i==btag_num2)||(i==pt_num1)||(i==pt_num2)) continue;
			Jet5pt=jets_pv[i].Pt();
			break;
		}



//////////////////////////////////// QGL weights start //////////////////////
		float qgl_weight=1.;
		if (!( (data==1)|| (Jet.partonFlavour[jets_indices[pt_num1]] ==0 ) || (TMath::Abs(Jet.eta[jets_indices[pt_num1]])>=2) || (Jet.qgl[jets_indices[pt_num1]] < 0) ) ) {
			if (TMath::Abs(Jet.partonFlavour[jets_indices[pt_num1]]) < 4 ) qgl_weight=func_qgl_q->Eval(Jet.qgl[jets_indices[pt_num1]]);
			if (TMath::Abs(Jet.partonFlavour[jets_indices[pt_num1]]) ==21 ) qgl_weight=func_qgl_g->Eval(Jet.qgl[jets_indices[pt_num1]]);
//			if (TMath::Abs(Jet.partonFlavour[jets_indices[pt_num1]]) < 4 ) qgl_weight=func_qgl_q_herwig->Eval(Jet.qgl[jets_indices[pt_num1]]);
//			if (TMath::Abs(Jet.partonFlavour[jets_indices[pt_num1]]) ==21 ) qgl_weight=func_qgl_g_herwig->Eval(Jet.qgl[jets_indices[pt_num1]]);
	//	cout<<qgl_weight<<endl;
		}
		cout<<Jet.partonFlavour[jets_indices[pt_num1]]<<endl;
		genweight*=qgl_weight;
		qgl_weight=1.;
		if (!( (data==1)|| (Jet.partonFlavour[jets_indices[pt_num2]] ==0 ) || (TMath::Abs(Jet.eta[jets_indices[pt_num2]])>=2) || (Jet.qgl[jets_indices[pt_num2]] < 0)) ) {
			if (TMath::Abs(Jet.partonFlavour[jets_indices[pt_num2]]) < 4 ) qgl_weight=func_qgl_q->Eval(Jet.qgl[jets_indices[pt_num2]]);
			if (TMath::Abs(Jet.partonFlavour[jets_indices[pt_num2]]) ==21 ) qgl_weight=func_qgl_g->Eval(Jet.qgl[jets_indices[pt_num2]]);
	//		if (TMath::Abs(Jet.partonFlavour[jets_indices[pt_num2]]) < 4 ) qgl_weight=func_qgl_q_herwig->Eval(Jet.qgl[jets_indices[pt_num2]]);
	//		if (TMath::Abs(Jet.partonFlavour[jets_indices[pt_num2]]) ==21 ) qgl_weight=func_qgl_g_herwig->Eval(Jet.qgl[jets_indices[pt_num2]]);
		}
		if (data!=1) genweight*=qgl_norm[file_tag];
		genweight*=qgl_weight;


//////////////////////////////////// QGL weights  end//////////////////////

//////////////////////////////////btag Weights start////////////////////////
	if (data!=1) {
		jets_btag_weight*=Jet.btagCMVAV2_weight[jets_indices[btag_num1]];
		jets_btag_weight*=Jet.btagCMVAV2_weight[jets_indices[btag_num2]];
		genweight*=jets_btag_weight;
	}
//////////////////////////////////btag Weights end////////////////////////


////////////////////////////////trig Weights start //////////////////////////////////////
/*
		float trigWeight = 1.;
		float trigCor1_nom[10] = {8.27936e+01 , 6.14282e+01,4.82877e+01 };
		float trigCor2_nom[10] = {2.30286e+01,  3.08334e+01,2.03703e+01};
		float trigCor_1btag_single[10] = {  2.13366e-01,  2.43250e-01 ,  4.53758e-01 , -3.63544e-03 };
		float trigCor_1btag_double[10] = { 5.65460e-01, -3.76206e-01 ,   9.45785e-01};
//		float trigCor_2btag_double[10] = { 3.29330e-01  ,  -3.95357e-01,   5.44691e-01,-4.94898e-02 };
		float trigCor_2btag_double[10] = { 1.54834e-01,  -3.25802e-01,  3.62393e-01, -4.95807e-02  };   //after first btag
		if (data!=1) {
			func_r->FixParameter(0,1.);
			func_r->FixParameter(1,trigCor1_nom[0] );
			func_r->FixParameter(2,trigCor2_nom[0] );
			trigWeight*=func_r->Eval(jets_pv[0].Pt());
			func_r->FixParameter(1,trigCor1_nom[1] );
			func_r->FixParameter(2,trigCor2_nom[1] );
			trigWeight*=func_r->Eval(jets_pv[1].Pt());
			func_r->FixParameter(1,trigCor1_nom[2] );
			func_r->FixParameter(2,trigCor2_nom[2] );
			trigWeight*=func_r->Eval(jets_pv[2].Pt());

			if (dataset_type.CompareTo("double")==0){
				func_erf_btag->FixParameter(0,trigCor_1btag_double[0]);
				func_erf_btag->FixParameter(1,trigCor_1btag_double[1]);
				func_erf_btag->FixParameter(2,trigCor_1btag_double[2]);
				func_erf_btag->FixParameter(3,0.);
				trigWeight*=func_erf_btag->Eval(-1.*TMath::Log(1-btag_vec[0].second));
				func_erf_btag->FixParameter(0,trigCor_2btag_double[0]);
				func_erf_btag->FixParameter(1,trigCor_2btag_double[1]);
				func_erf_btag->FixParameter(2,trigCor_2btag_double[2]);
				func_erf_btag->FixParameter(3,trigCor_2btag_double[3]);
				trigWeight*=func_erf_btag->Eval(-1.*TMath::Log(1-btag_vec[1].second));
			}
			if (dataset_type.CompareTo("single")==0){
				func_erf_btag->FixParameter(0,trigCor_1btag_single[0]);
				func_erf_btag->FixParameter(1,trigCor_1btag_single[1]);
				func_erf_btag->FixParameter(2,trigCor_1btag_single[2]);
				func_erf_btag->FixParameter(3,trigCor_1btag_single[3]);
				trigWeight*=func_erf_btag->Eval(-1.*TMath::Log(1-btag_vec[0].second));
			}

		}
			genweight*=trigWeight; 
*/
////////////////////////////////trig Weights end //////////////////////////////////////

	/*		if (VBFpassSel_JE[4]!=1) { 
				cout <<"oops"<<endl;
				cout<<evt<<endl;				
				cout<<good_jets<<endl;				
				cout<<btag_num1<<"   "<<btag_num2<<endl;				
				cout<<pt_num1<<"   "<<pt_num2<<endl;				
			}
*/

			float AllWeight = genweight;
			genweight/=events_generated/xsec[file_tag];


			presel+=genweight;
			presel_vtype[(int)(v_type+1)]+=genweight;



			counter++;

            hJet1_pt->Fill(jets_pv[0].Pt(),genweight);
            hJet1_eta->Fill(jets_pv[0].Eta(),genweight);
            hJet1_phi->Fill(jets_pv[0].Phi(),genweight);
            hJet2_pt->Fill(jets_pv[1].Pt(),genweight);
            hJet2_eta->Fill(jets_pv[1].Eta(),genweight);
            hJet2_phi->Fill(jets_pv[1].Phi(),genweight);
            hJet3_pt->Fill(jets_pv[2].Pt(),genweight);
            hJet3_eta->Fill(jets_pv[2].Eta(),genweight);
            hJet3_phi->Fill(jets_pv[2].Phi(),genweight);
            hJet4_pt->Fill(jets_pv[3].Pt(),genweight);
            hJet4_eta->Fill(jets_pv[3].Eta(),genweight);
            hJet4_phi->Fill(jets_pv[3].Phi(),genweight);
            hVtype->Fill(v_type,genweight);
            hJet5_pt->Fill(Jet5pt,genweight);
			hMqq->Fill(Mqq,genweight);
			hEtaQQ->Fill(qqDeltaEta,genweight);
			hEtaQQ_bin->Fill(qqDeltaEta,genweight);
			hPhiQQ->Fill(qqDeltaPhi,genweight);
			hPhiBB->Fill(bbDeltaPhi,genweight);
			hPhiBB_bin->Fill(bbDeltaPhi,genweight);
			hEtaSoftJets->Fill(Jet.soft_eta[0],genweight);
			hPtSoftJets->Fill(Jet.soft_pt[0],genweight);
			hPtSoftJets2->Fill(Jet.soft_pt[1],genweight);
			hPtSoftJets3->Fill(Jet.soft_pt[2],genweight);
			hMassSoftJets->Fill(Jet.soft_mass[0],genweight);
			hHTsoft->Fill(Jet.HTsoft,genweight);
			hSoft_n2->Fill(Jet.nsoft2, genweight);
			hSoft_n5->Fill(Jet.nsoft5, genweight);
			hSoft_n10->Fill(Jet.nsoft10, genweight);
			hMbb->Fill(Mbb,genweight);
			hqgl->Fill(Jet.qgl[jets_indices[pt_num1]],genweight);
			hbtag->Fill(Jet.btagCMVAV2[jets_indices[btag_num1]],genweight);
			hqgl2->Fill(Jet.qgl[jets_indices[pt_num2]],genweight);
			hbtag2->Fill(Jet.btagCMVAV2[jets_indices[btag_num2]],genweight);
			hcosOqqbb->Fill(cosObbqq,genweight);
			hEtaQB1->Fill(EtaBQ1,genweight);
			hEtaQB2->Fill(EtaBQ2,genweight);
			hPhiQB1->Fill(PhiBQ1,genweight);
			hPhiQB2->Fill(PhiBQ2,genweight);
			hx1->Fill(x1,genweight);
			hx2->Fill(x2,genweight);
			hVB1_mass->Fill(VB1_mass,genweight);
			hVB2_mass->Fill(VB2_mass,genweight);
			hEtot->Fill(Etot,genweight);
			hPxtot->Fill(PxTot,genweight);
			hPytot->Fill(PyTot,genweight);
			hPztot->Fill(PzTot,genweight);
			hPtqqbb->Fill(bbqq.Pt(),genweight);
			hPhiqqbb->Fill((-1)*bbqq.Phi(),genweight);
			hEtaqqbb->Fill(TMath::Abs(bbqq.Eta()), genweight);
            hJet1_pt_bin->Fill(jets_pv[0].Pt(),genweight);
            hJet2_pt_bin->Fill(jets_pv[1].Pt(),genweight);
            hJet3_pt_bin->Fill(jets_pv[2].Pt(),genweight);
            hJet4_pt_bin->Fill(jets_pv[3].Pt(),genweight);
				hMqq_bin->Fill(Mqq,genweight);
				hMqq_bin2->Fill(Mqq,genweight);
				hnPVs->Fill(nPVs,genweight);
				hMbb_regVBF->Fill(Mbb_reg,genweight);
				hMbb_regVBF_fsr->Fill(Mbb_reg_fsr,genweight);
				hMbb_regVBF_fsr_high->Fill(Mbb_reg_fsr,genweight);
	/*			if (set_type==0) if (bdt[0]>cats[NCATS-1]) hMbb_regVBF_fsr_high_cat->Fill(Mbb_reg_fsr,genweight);
				if (set_type==1) if (bdt[0]>cats[NCATS-1]) hMbb_regVBF_fsr_high_cat->Fill(Mbb_reg_fsr,genweight);
				if (set_type==0) if (bdt[0]>cats[NCATS-2]) hMbb_regVBF_fsr_high_cat2->Fill(Mbb_reg_fsr,genweight);
				if (set_type==1) if (bdt[0]>cats[NCATS-2]) hMbb_regVBF_fsr_high_cat2->Fill(Mbb_reg_fsr,genweight);*/


				hJet1q_pt->Fill(Qjet1.Pt(),genweight);
				hJet1q_eta->Fill(Qjet1.Eta(),genweight);
				hJet1q_phi->Fill(Qjet1.Phi(),genweight);
				hJet1q_ptd->Fill(Jet.ptd[jets_indices[pt_num1]],genweight);
				hJet1q_axis2->Fill(TMath::Exp((-1)*Jet.axis2[jets_indices[pt_num1]]),genweight);
				hJet1q_mult->Fill(Jet.mult[jets_indices[pt_num1]],genweight);
				hJet1q_leadTrackPt->Fill(Jet.leadTrackPt[jets_indices[pt_num1]],genweight);
				hJet2q_pt->Fill(Qjet2.Pt(),genweight);
				hJet2q_eta->Fill(Qjet2.Eta(),genweight);
				hJet2q_phi->Fill(Qjet2.Phi(),genweight);
				hJet2q_ptd->Fill(Jet.ptd[jets_indices[pt_num2]],genweight);
				hJet2q_axis2->Fill(TMath::Exp((-1)*Jet.axis2[jets_indices[pt_num2]]),genweight);
				hJet2q_mult->Fill(Jet.mult[jets_indices[pt_num2]],genweight);
				hJet2q_leadTrackPt->Fill(Jet.leadTrackPt[jets_indices[pt_num2]],genweight);
				hblike1->Fill(Jet.blike_VBF[btag_num1],genweight);
				hblike2->Fill(Jet.blike_VBF[btag_num2],genweight);
				hmet->Fill(met_pt,genweight);
				hselLeptons_tightId->Fill(selLeptons_tightId[0],genweight);

				hJet1b_pt->Fill(Bjet1.Pt(),genweight);
				hJet1b_eta->Fill(Bjet1.Eta(),genweight);
				hJet2b_pt->Fill(Bjet2.Pt(),genweight);
				hJet2b_eta->Fill(Bjet2.Eta(),genweight);
				hJetqqbb_pz->Fill(bbqq.Pz(),genweight);
				hEtaQBplus->Fill(EtaBQ1+EtaBQ2 , genweight);
				hEtaQBminus->Fill(EtaBQ1-EtaBQ2, genweight);
				hJetbb_pt->Fill(bb.Pt() , genweight);
				hlheHT->Fill(lheHT ,genweight);

				hJet1cvs_pt->Fill(jets_pv[csv_vec[0].first].Pt(),genweight);
		///////////////////////Leptons   start //////////////////////////	
				int tmp_idx=0;
				int tmp_idx_2=0;
				if (region.CompareTo("controlTop")==0) 	tmp_idx=0;
				if (region.CompareTo("controlDY")==0) {
					if (pass_el==1) {
						tmp_idx = idx_1stLepton_el;
						tmp_idx_2 = idx_2ndLepton_el;
					}
					if (pass_mu==1) {
						tmp_idx = idx_1stLepton_mu;
						tmp_idx_2 = idx_2ndLepton_mu;
					}
	
				}
				Float_t logIso  = -5;
			
			if  ((region.CompareTo("controlTop")==0) || (region.CompareTo("controlDY")==0)) {  
				if (selLeptons_relIso03[tmp_idx] > TMath::Exp(-5)) logIso = TMath::Log(selLeptons_relIso03[tmp_idx]);
				hselLeptons_relIso03->Fill(logIso,genweight);
				logIso  = -5;
				if (selLeptons_chargedHadRelIso03[tmp_idx] > TMath::Exp(-5)) logIso = TMath::Log(selLeptons_chargedHadRelIso03[tmp_idx]);
				hselLeptons_chargedHadRelIso03->Fill(logIso,genweight);
				logIso  = -5;
				if (selLeptons_pfRelIso03[tmp_idx] > TMath::Exp(-5)) logIso = TMath::Log(selLeptons_pfRelIso03[tmp_idx]);
				hselLeptons_pfRelIso03->Fill(logIso,genweight);
			}
			if  (region.CompareTo("controlDY")==0) {  
				if (selLeptons_relIso03[tmp_idx_2] > TMath::Exp(-5)) logIso = TMath::Log(selLeptons_relIso03[tmp_idx_2]);
				hselLeptons_relIso03_2->Fill(logIso,genweight);
				logIso  = -5;
				if (selLeptons_chargedHadRelIso03[tmp_idx_2] > TMath::Exp(-5)) logIso = TMath::Log(selLeptons_chargedHadRelIso03[tmp_idx_2]);
				hselLeptons_chargedHadRelIso03_2->Fill(logIso,genweight);
				logIso  = -5;
				if (selLeptons_pfRelIso03[tmp_idx_2] > TMath::Exp(-5)) logIso = TMath::Log(selLeptons_pfRelIso03[tmp_idx_2]);
				hselLeptons_pfRelIso03_2->Fill(logIso,genweight);
			}
		///////////////////////Leptons   end //////////////////////////	

				


				float deltaPhi_met_jet = 5.;
				for (int i =0;i<4;i++){
					float tmp_deltaPhi = TMath::Abs(met_phi - jets_pv[i].Phi());
					if (tmp_deltaPhi<deltaPhi_met_jet) deltaPhi_met_jet = tmp_deltaPhi;
				}
				if(deltaPhi_met_jet > TMath::Pi()) deltaPhi_met_jet = TMath::TwoPi() - deltaPhi_met_jet;
				hphi_metJet->Fill(deltaPhi_met_jet,genweight);
				





 
			hbdt->Fill(bdt_VBF,genweight);
			hbdt_fine->Fill(bdt_VBF,genweight);
			if ((Mbb_reg_fsr>=80)&&(Mbb_reg_fsr<=200))  hprof_VBF_range->Fill(bdt_VBF,Mbb_reg_fsr,genweight);
			 hprof_VBF->Fill(bdt_VBF,Mbb_reg_fsr,genweight);




			hbtag_log->Fill(-1.*TMath::Log(1.-Jet.btagCMVAV2[jets_indices[btag_num1]]),genweight);
			hbtag2_log->Fill(-1.*TMath::Log(1.-Jet.btagCMVAV2[jets_indices[btag_num2]]),genweight);
			hrho->Fill(rho,genweight);

			hbdt_Zbb->Fill(bdt_Zbb,genweight);
			hbdt_Zbb_fine->Fill(bdt_Zbb,genweight);
			if ((Mbb_reg_fsr>=60)&&(Mbb_reg_fsr<=170))  hprof_Zbb_range->Fill(bdt_Zbb,Mbb_reg_fsr,genweight);
			 hprof_Zbb->Fill(bdt_Zbb,Mbb_reg_fsr,genweight);


			treeZbb_bdt_Zbb = bdt_Zbb;
			treeZbb_mbbRegFSR = Mbb_reg_fsr;	
			treeZbb_xsec = xsec[file_tag];
			treeZbb_totalWeight = AllWeight;
			output_tree->Fill();


			treeVBF_bdt_VBF = bdt_VBF;
			treeVBF_mbbRegFSR = Mbb_reg_fsr;	
			treeVBF_xsec = xsec[file_tag];
			treeVBF_totalWeight = AllWeight;
			output_tree_VBF->Fill();



	//		if (passSel_JE[current_syst]!=1) cout<<"oops"<<endl;

/*
			if ((bdt_Zbb_JE[current_syst]>cats_Zbb[NCATS-1])&&(passSel_JE[current_syst]==1)) hMbb_Zbbcat3->Fill(Mbb_reg_fsr,genweight);
			if ((bdt_Zbb_JE[current_syst]>cats_Zbb[NCATS-2])&&(bdt_Zbb_JE[current_syst]<=cats_Zbb[NCATS-1])&&(passSel_JE[current_syst]==1)) hMbb_Zbbcat2->Fill(Mbb_reg_fsr,genweight);
			if ((bdt_Zbb_JE[current_syst]>cats_Zbb[NCATS-3])&&(bdt_Zbb_JE[current_syst]<=cats_Zbb[NCATS-2])&&(passSel_JE[current_syst]==1)) hMbb_Zbbcat1->Fill(Mbb_reg_fsr,genweight);
			if ((bdt_Zbb_JE[current_syst]>cats_Zbb[NCATS-4])&&(bdt_Zbb_JE[current_syst]<=cats_Zbb[NCATS-3])&&(passSel_JE[current_syst]==1)) hMbb_Zbbcat0->Fill(Mbb_reg_fsr,genweight);
*/			
			if ((bdt_Zbb>cats_Zbb[NCATS-1])) hMbb_Zbbcat3->Fill(Mbb_reg_fsr,genweight);
			if ((bdt_Zbb>cats_Zbb[NCATS-2])&&(bdt_Zbb<=cats_Zbb[NCATS-1])) hMbb_Zbbcat2->Fill(Mbb_reg_fsr,genweight);
			if ((bdt_Zbb>cats_Zbb[NCATS-3])&&(bdt_Zbb<=cats_Zbb[NCATS-2])) hMbb_Zbbcat1->Fill(Mbb_reg_fsr,genweight);
			if ((bdt_Zbb>cats_Zbb[NCATS-4])&&(bdt_Zbb<=cats_Zbb[NCATS-3])) hMbb_Zbbcat0->Fill(Mbb_reg_fsr,genweight);

/*			///////////JER and JEC/////////////////////
			hbdt_JECnom->Fill(bdt[1],genweight);
			hbdt_JECup->Fill(bdt[2],genweight);
			hbdt_JECdown->Fill(bdt[3],genweight);
			hbdt_JERnom->Fill(bdt[4],genweight);
			hbdt_JERup->Fill(bdt[5],genweight);
			hbdt_JERdown->Fill(bdt[6],genweight);
*/			///////////////////////////////////////////

//			hvLeptons_dz->Fill(vLeptons_dz[0],genweight);
//			hvLeptons_edz->Fill(vLeptons_edz[0],genweight);
//			hvLeptons_sig->Fill(TMath::Abs(vLeptons_dz[0])/vLeptons_edz[0],genweight);




		

		if (genweight>0) gen_pos+=genweight0;
		if (genweight<0) gen_neg+=genweight0;
/*
		for (int i=0;i<NCATS;i++){
			if  ((bdt>cats[i])&&(bdt<=cats[i+1])) events_in_cats[i] += genweight;
			if  ((bdt>cats[i])&&(bdt<=cats[i+1])&&(Mbb_reg_fsr>=80)&&(Mbb_reg_fsr<=200)) events_in_cats_80_200[i] += genweight;
			if  ((bdt>cats[i])&&(bdt<=cats[i+1])) events_in_cats_er_true[i] += pow(mcweight,2);
			if  ((bdt>cats[i])&&(bdt<=cats[i+1])&&(Mbb_reg_fsr>=80)&&(Mbb_reg_fsr<=200)) events_in_cats_er_true_80_200[i] += pow(mcweight,2);
			if  ((bdt>cats[i])&&(bdt<=cats[i+1])) events_in_cats_er_plus[i] += TMath::Abs(genweight0);
			if  ((bdt>cats[i])&&(bdt<=cats[i+1])) events_in_cats_er_minus[i] += genweight0;
		}
			*/	
			global_counter++;



        }

		cout<<counter<<endl;
		TFile file(output+"/"+file_tag+"_"+region+"_"+dataset_type+"_trig"+trigWeight_str+"_"+heppyVersion+"_"+postfix+".root","recreate");
    
		for (int i=0;i<numArray;++i){
    	    	histArray[i]->SetLineWidth(2);
    	   	histArray[i]->GetYaxis()->SetTitle("N_{events}");
       		histArray[i]->GetYaxis()->SetTitleFont(42);
       		histArray[i]->GetYaxis()->SetTitleSize(0.060);
        		histArray[i]->GetYaxis()->SetTitleOffset(0.8);
        		histArray[i]->SetLineColor(kBlue);
        		histArray[i]->Draw();
        		histArray[i]->Write();
   		} 
			hprof_VBF->SetLineWidth(2);
        	hprof_VBF->SetLineColor(kBlue);
        	hprof_VBF->Draw();
        	hprof_VBF->Write();
			hprof_VBF_range->SetLineWidth(2);
        	hprof_VBF_range->SetLineColor(kBlue);
        	hprof_VBF_range->Draw();
        	hprof_VBF_range->Write();
			hprof_Zbb->SetLineWidth(2);
        	hprof_Zbb->SetLineColor(kBlue);
        	hprof_Zbb->Draw();
        	hprof_Zbb->Write();
			hprof_Zbb_range->SetLineWidth(2);
        	hprof_Zbb_range->SetLineColor(kBlue);
        	hprof_Zbb_range->Draw();
        	hprof_Zbb_range->Write();


    		file.Write();
    		file.Close();

	outputtree_fileZbb.cd();
	hGenerated->Fill(0.,events_generated);
	hGenerated->Write();
	tree_dir->cd();
	output_tree->AutoSave();
	outputtree_fileZbb.Close();


	outputtree_fileVBF.cd();
	hGenerated->Write();
	tree_dir_VBF->cd();
	output_tree_VBF->AutoSave();
	outputtree_fileVBF.Close();



	 ofstream out(output+"/"+file_tag+"_"+region+"_"+dataset_type+"_trig"+trigWeight_str+"_"+heppyVersion+"_"+postfix+".txt");
	float eff_lumi = events_generated/xsec[file_tag];
	out<< "positive pure selected = "<<gen_pos<<" , negative pure selected = "<<gen_neg<< ", all evetns in the begining = "<<events_generated<<" , xsec = "<<xsec[file_tag]<<"  , effective Lumi = "<<eff_lumi <<endl;
	out<<"rates for v_type : " <<endl;
	for (int i=0;i<7;i++){
		out<<i-1<<"    "<<(float)presel_vtype[i]<<endl;
	}
	out<<endl;
	out<<"after preselection left : "<<presel <<endl;
	out<<"all loop : "<<all_loop <<endl;
	out.close();


return 0;
    
}
