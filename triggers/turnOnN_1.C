#include <ctype.h>
#include <iomanip>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "TFile.h"
#include "TH1.h"
#include "TH1F.h"
#include "TH2.h"
#include "TH2F.h"
#include "TTree.h"
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
#include "/afs/cern.ch/work/n/nchernya/VBFHbb_2016/plotter/preselection_single_trig.C"
#include "/afs/cern.ch/work/n/nchernya/VBFHbb_2016/plotter/preselection_double_trig.C"

Double_t erf( Double_t *x, Double_t *par){
  return par[0]/2.*(1.+TMath::Erf((x[0]-par[1])/par[2]));
}

struct sort_pred {
    bool operator()(const std::pair<int,float> &left, const std::pair<int,float> &right) {
        return left.second > right.second;
    }
};



const int njets = 300;

typedef struct {
   Float_t eta[njets];
   Float_t pt[njets];
   Float_t phi[njets];
	Float_t mass[njets];
	Float_t btagCSV[njets];
	Float_t btagCMVA[njets];
	Float_t blike_VBF[njets];
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
	Float_t btagCMVAV2_weight[njets];
} Jets;

using namespace std;

//void turnOnN_1(int files, int files_max, int set_type, int trigger){
int main(int argc, char* argv[]){  

TString file_name = std::string(argv[1]);
TString file_tag = std::string(argv[2]);
TString dataset_type = std::string(argv[3]);
int data = atoi(argv[4]);
int trigger=atoi(argv[5]);
TString ending  = std::string(argv[6]);
TString output = std::string(argv[7]);
 
//set_type = 0 double, set_type = 1 single
TString type[2] = {"_double","_single"};

std::map <TString, float> xsec;
xsec["QCD_HT100to200"] = 27990000;
xsec["QCD_HT200to300"] = 1712000 ;
xsec["QCD_HT300to500"] = 347700;
xsec["QCD_HT500to700"] = 32100 ;
xsec["QCD_HT700to1000"] = 6831;
xsec["QCD_HT1000to1500"] = 1207 ;
xsec["QCD_HT1500to2000"] =  119.9;
xsec["QCD_HT2000toInf"] = 25.24;
xsec["JetHT"] = 1.;
xsec["VBFHToBB_M-125"] =  2.20;

	
	Float_t presel=0;
	Float_t cut1 = 0;
	Float_t cut2 = 0;
	Float_t cut3 = 0;
	Float_t genweight=1.;
	Float_t puweight=1.;
	Int_t global_counter = 0;
	Int_t HLT_BIT_HLT_QuadPFJet_BTagCSV_p016_p11_VBF_Mqq200_v;
	Int_t HLT_BIT_HLT_QuadPFJet_BTagCSV_p016_p11_VBF_Mqq240_v;
	Int_t HLT_BIT_HLT_QuadPFJet_BTagCSV_p016_VBF_Mqq460_v;
	Int_t HLT_BIT_HLT_QuadPFJet_BTagCSV_p016_VBF_Mqq500_v;

	Int_t  HLT_BIT_HLT_DiPFJetAve40_v;
	Int_t  HLT_BIT_HLT_DiPFJetAve60_v;
	Int_t  HLT_BIT_HLT_DiPFJetAve80_v;
	Int_t  HLT_BIT_HLT_PFJet40_v;
	Int_t  HLT_BIT_HLT_PFJet60_v;
	Int_t  HLT_BIT_HLT_PFJet80_v;
	Int_t  HLT_BIT_HLT_QuadPFJet_VBF_v;

	TString denominator_trigger_names[7] = {"PF40","PF60","PF80","DiPF40","DiPF60","DiPF80","VBF" };

	TFile *file_initial;
	file_initial = TFile::Open(file_name);

   TTree *tree_initial = (TTree*)file_initial->Get("tree");
	TH1F *countPos;
	TH1F *countNeg;
	TH1F *countWeighted;
	Float_t events_generated;
	if (data!=1){
		countPos = (TH1F*)file_initial->Get("CountPosWeight");
 		countNeg = (TH1F*)file_initial->Get("CountNegWeight");
 		countWeighted = (TH1F*)file_initial->Get("CountWeighted");
		events_generated = countWeighted->GetBinContent(1);
		if (events_generated==0) events_generated =  countPos->GetBinContent(1) - countNeg->GetBinContent(1);
	} else events_generated = 1;
    Jets Jet;
   Int_t nJets;
	float counter = 0.;
	float counter_tr1=0.;
	Float_t JSON = 0;


	

    tree_initial->SetBranchAddress("nJet",&nJets);
    tree_initial->SetBranchAddress("genWeight",&genweight);
	tree_initial->SetBranchAddress("puWeight",&puweight);
    tree_initial->SetBranchAddress("Jet_pt",Jet.pt);
    tree_initial->SetBranchAddress("Jet_eta",Jet.eta);
    tree_initial->SetBranchAddress("Jet_phi",Jet.phi);
	tree_initial->SetBranchAddress("Jet_mass",Jet.mass);
	tree_initial->SetBranchAddress("Jet_btagCSV",Jet.btagCSV);
	tree_initial->SetBranchAddress("Jet_btagCMVAV2",Jet.btagCMVA);
	tree_initial->SetBranchAddress("Jet_btagWeightCMVAV2",Jet.btagCMVAV2_weight);
	tree_initial->SetBranchAddress("Jet_id",Jet.id);	
	tree_initial->SetBranchAddress("Jet_puId",Jet.puId);	
	tree_initial->SetBranchAddress("json",&JSON);

 	tree_initial->SetBranchAddress("HLT_BIT_HLT_QuadPFJet_BTagCSV_p016_p11_VBF_Mqq200_v",&HLT_BIT_HLT_QuadPFJet_BTagCSV_p016_p11_VBF_Mqq200_v);
 	tree_initial->SetBranchAddress("HLT_BIT_HLT_QuadPFJet_BTagCSV_p016_p11_VBF_Mqq240_v",&HLT_BIT_HLT_QuadPFJet_BTagCSV_p016_p11_VBF_Mqq240_v);
 	tree_initial->SetBranchAddress("HLT_BIT_HLT_QuadPFJet_BTagCSV_p016_VBF_Mqq460_v",&HLT_BIT_HLT_QuadPFJet_BTagCSV_p016_VBF_Mqq460_v);
 	tree_initial->SetBranchAddress("HLT_BIT_HLT_QuadPFJet_BTagCSV_p016_VBF_Mqq500_v",&HLT_BIT_HLT_QuadPFJet_BTagCSV_p016_VBF_Mqq500_v);


	tree_initial->SetBranchAddress("HLT_BIT_HLT_PFJet40_v",&HLT_BIT_HLT_PFJet40_v);
	tree_initial->SetBranchAddress("HLT_BIT_HLT_PFJet60_v",&HLT_BIT_HLT_PFJet60_v);
	tree_initial->SetBranchAddress("HLT_BIT_HLT_PFJet80_v",&HLT_BIT_HLT_PFJet80_v);
	tree_initial->SetBranchAddress("HLT_BIT_HLT_DiPFJetAve40_v",&HLT_BIT_HLT_DiPFJetAve40_v);
	tree_initial->SetBranchAddress("HLT_BIT_HLT_DiPFJetAve60_v",&HLT_BIT_HLT_DiPFJetAve60_v);
	tree_initial->SetBranchAddress("HLT_BIT_HLT_DiPFJetAve80_v",&HLT_BIT_HLT_DiPFJetAve80_v);
	tree_initial->SetBranchAddress("HLT_BIT_HLT_QuadPFJet_VBF_v",&HLT_BIT_HLT_QuadPFJet_VBF_v);




	Float_t jet1pt_binx[30] = {0,20,40,60,80,100,120,140,160,180,200,240,300,550};   
	Float_t jet2pt_binx[30] = {0,20,40,60,80,100,120,140,160,200,250,330,550};   
	Float_t jet3pt_binx[30] = {0,20,40,60,80,100,120,150,220,390,550};   
	Float_t jet4pt_binx[30] = {0,20,40,60,80,100,200};	
	Float_t mqq_bins[40] = {0,30,60,90,120,150,180,210,240,270,300,330,360,390,420,450,480,510,540,570,600,650,720,800,900,1100,1500,2600};   


 
    TH1F *hJet1_pt = new TH1F("hJet1_pt", "", 13, jet1pt_binx);
    hJet1_pt->GetXaxis()->SetTitle("1^{st} Jet p_{T} (GeV)");
    TH1F *hJet2_pt = new TH1F("hJet2_pt", "", 12, jet2pt_binx);
    hJet2_pt->GetXaxis()->SetTitle("2^{nd} Jet p_{T} (GeV)");
    TH1F *hJet3_pt = new TH1F("hJet3_pt", "", 9, jet3pt_binx);
    hJet3_pt->GetXaxis()->SetTitle("3^{rd} Jet p_{T} (GeV)");
    TH1F *hJet4_pt = new TH1F("hJet4_pt", "", 6, jet4pt_binx);
    hJet4_pt->GetXaxis()->SetTitle("4^{th} Jet p_{T} (GeV)");
	 TH1F *hMqq = new TH1F("hMqq","",27, mqq_bins);
	hMqq->GetXaxis()->SetTitle("m_{qq} (GeV)");
	TH1F *hbtag = new TH1F("hbtag","",20,-1.,1.);
	hbtag->GetXaxis()->SetTitle("CMVAV2 1^{st} b-jet"); 
	TH1F *hbtag2 = new TH1F("hbtag2","",20,-1.,1.);
	hbtag2->GetXaxis()->SetTitle("CMVAV2 2^{nd} b-jet");
	TH1F *hDeltaEta = new TH1F("hDeltaEta","",80.,0.,8.);
	hDeltaEta->GetXaxis()->SetTitle("|#Delta#eta_{qq}|");
	TH1F *hDeltaPhi = new TH1F("hDeltaPhi","",32,0.,3.2);
	hDeltaPhi->GetXaxis()->SetTitle("|#Delta#phi_{bb}|");
	TH1F *hbtag_log = new TH1F("hbtag_log","",24,-2.,10.);
	hbtag_log->GetXaxis()->SetTitle("-log(1-CMVAV2) 1^{st} b-jet"); 
	TH1F *hbtag2_log = new TH1F("hbtag2_log","",24,-2.,10.);
	hbtag2_log->GetXaxis()->SetTitle("-log(1-CMVAV2) 2^{nd} b-jet");


    TH1F *hJet1_pt_trigger = new TH1F("hJet1_pt_trigger", "", 13, jet1pt_binx);
    hJet1_pt_trigger->GetXaxis()->SetTitle("1^{st} Jet p_{T} (GeV)");
    TH1F *hJet2_pt_trigger = new TH1F("hJet2_pt_trigger", "",12, jet2pt_binx);
    hJet2_pt_trigger->GetXaxis()->SetTitle("2^{nd} Jet p_{T} (GeV)");
    TH1F *hJet3_pt_trigger = new TH1F("hJet3_pt_trigger", "",9, jet3pt_binx);
    hJet3_pt_trigger->GetXaxis()->SetTitle("3^{rd} Jet p_{T} (GeV)");
    TH1F *hJet4_pt_trigger = new TH1F("hJet4_pt_trigger", "", 6, jet4pt_binx);
    hJet4_pt_trigger->GetXaxis()->SetTitle("4^{th} Jet p_{T} (GeV)");
	 TH1F *hMqq_trigger = new TH1F("hMqq_trigger","",27, mqq_bins);
	hMqq_trigger->GetXaxis()->SetTitle("m_{qq} (GeV)");
	TH1F *hbtag_trigger = new TH1F("hbtag_trigger","",20,-1.,1.);
	hbtag_trigger->GetXaxis()->SetTitle("CMVAV2 1^{st} b-jet"); 
	TH1F *hbtag2_trigger = new TH1F("hbtag2_trigger","",20,-1.,1.);
	hbtag2_trigger->GetXaxis()->SetTitle("CMVAV2 2^{nd} b-jet");
	TH1F *hDeltaEta_trigger= new TH1F("hDeltaEta_trigger","",80.,0.,8.);
	hDeltaEta_trigger->GetXaxis()->SetTitle("|#Delta#eta_{qq}|");
	TH1F *hDeltaPhi_trigger = new TH1F("hDeltaPhi_trigger","",32,0.,3.2);
	hDeltaPhi_trigger->GetXaxis()->SetTitle("|#Delta#phi_{bb}|");
	TH1F *hbtag_log_trigger = new TH1F("hbtag_log_trigger","",24,-2.,10.);
	hbtag_log_trigger->GetXaxis()->SetTitle("-log(1-CMVAV2) 1^{st} b-jet"); 
	TH1F *hbtag2_log_trigger = new TH1F("hbtag2_log_trigger","",24,-2.,10.);
	hbtag2_log_trigger->GetXaxis()->SetTitle("-log(1-CMVAV2) 2^{nd} b-jet");


 
   		const int numArray= 11;
			const int numArray_notrigger = numArray;
   		TH1F* histArray[numArray] = {hJet1_pt_trigger,hJet2_pt_trigger,hJet3_pt_trigger,hJet4_pt_trigger, hMqq_trigger, hbtag_trigger, hbtag2_trigger, hDeltaEta_trigger, hDeltaPhi_trigger, hbtag_log_trigger,  hbtag2_log_trigger};
			TH1F *histArray_notrigger[numArray_notrigger] = {hJet1_pt,hJet2_pt,hJet3_pt,hJet4_pt, hMqq, hbtag, hbtag2, hDeltaEta, hDeltaPhi, hbtag_log, hbtag2_log};
	

		for (int i=0;i<numArray;i++){	
			histArray[i]->Sumw2();
			histArray_notrigger[i]->Sumw2();
		}


	TF1 *func_r = new TF1("erffunc",erf,0.,1000.,3);
	TF1 *func_erf_btag= new TF1("func_erf_btag","1.+ [3] + [0]/2.*(1.-TMath::Erf((x-[1])/[2]))",-10.,600.);



	int nentries = tree_initial->GetEntries() ;
    for (int entry= 0; entry<nentries;++entry){
//    for (int entry= 0; entry<100;++entry){
    	tree_initial->GetEntry(entry);

		Int_t nominator_trigger[4] = {HLT_BIT_HLT_QuadPFJet_BTagCSV_p016_p11_VBF_Mqq200_v,HLT_BIT_HLT_QuadPFJet_BTagCSV_p016_p11_VBF_Mqq240_v,HLT_BIT_HLT_QuadPFJet_BTagCSV_p016_VBF_Mqq460_v,HLT_BIT_HLT_QuadPFJet_BTagCSV_p016_VBF_Mqq500_v}; 
		Int_t denominator_trigger[7] = {HLT_BIT_HLT_PFJet40_v,HLT_BIT_HLT_PFJet60_v, HLT_BIT_HLT_PFJet80_v, HLT_BIT_HLT_DiPFJetAve40_v, HLT_BIT_HLT_DiPFJetAve60_v, HLT_BIT_HLT_DiPFJetAve80_v, HLT_BIT_HLT_QuadPFJet_VBF_v };
	
		if (JSON!=1) {
			continue;
		}

		int good_jets = 0;
		vector<TLorentzVector> jets_pv;
		vector<int> jets_indices;
		vector<pair<int, float> > btag_vec;	
		vector<pair<int, float> > pt_vec;	
		pair<int,float> aPair;
	//	float jets_btag_weight=1.;
		for (int i=0;i<nJets;i++){
	//		jets_btag_weight*=Jet_btagWeightCMVAV2[i];
			TLorentzVector jet0;
			if (!((Jet.id[i]>2)&&(Jet.puId[i]>0)&&(Jet.pt[i]>20) )) continue;
			jet0.SetPtEtaPhiM(Jet.pt[i],Jet.eta[i],Jet.phi[i],Jet.mass[i]);
			jets_pv.push_back(jet0);
			jets_indices.push_back(i);
			aPair.first = good_jets;
			aPair.second = Jet.btagCMVA[i];
			btag_vec.push_back(aPair);
			aPair.first = good_jets;
			aPair.second = Jet.pt[i];
			pt_vec.push_back(aPair);
			good_jets++;
		}
		
		Float_t c=-0.853212; 
		for (int i=0;i<nJets;i++){
			if ((Jet.btagCMVA[i]>-0.853213) &&(Jet.btagCMVA[i]<-0.853211)) Jet.btagCMVA[i]=-10.;
		}
		for (int i=0;i<good_jets;i++){
			if ((btag_vec[i].second>-0.853213) &&(btag_vec[i].second<-0.853211)) 	btag_vec[i].second=-10.;
		}

		if (good_jets<4)continue;


		genweight=TMath::Abs(genweight)/genweight*puweight;
		if (data!=1) genweight/=events_generated/xsec[file_tag]; 


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
		std::sort(pt_vec.begin(), pt_vec.begin()+loopJet_max,sort_pred() );

		int preselection_pass=-100;
		int preselection_single_pass=-100;
		int cut_count=0;


		Int_t trigger_single=HLT_BIT_HLT_QuadPFJet_BTagCSV_p016_VBF_Mqq460_v || HLT_BIT_HLT_QuadPFJet_BTagCSV_p016_VBF_Mqq500_v;
		Int_t trigger_double=HLT_BIT_HLT_QuadPFJet_BTagCSV_p016_p11_VBF_Mqq200_v || HLT_BIT_HLT_QuadPFJet_BTagCSV_p016_p11_VBF_Mqq240_v;

		if (dataset_type.CompareTo("double")==0){
			preselection_single_pass = preselection_single(trigger_single, loopJet_max, jets_pv, btag_vec, pt_vec, btag_num1, btag_num2, pt_num1, pt_num2,cut_count);   //if passes single -> we don't want to put it in double set
			preselection_pass = preselection_double(1, loopJet_max, jets_pv, btag_vec, pt_vec, btag_num1, btag_num2, pt_num1, pt_num2, cut_count);  //should pass double selection
			if (preselection_single_pass==0) preselection_pass=-1;//if it does pass the Single presel+trigger then it does NOT pass Double
		}
		else {
			if (dataset_type.CompareTo("single")==0){
			 preselection_pass = preselection_single(1, loopJet_max, jets_pv, btag_vec, pt_vec, btag_num1, btag_num2, pt_num1, pt_num2,cut_count);
			}
		}
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



//////////////////////////////////btag Weights start////////////////////////
	float jets_btag_weight=1.;
	if (data!=1) {
		jets_btag_weight*=Jet.btagCMVAV2_weight[jets_indices[btag_num1]];
		jets_btag_weight*=Jet.btagCMVAV2_weight[jets_indices[btag_num2]];
		genweight*=jets_btag_weight;
	}
//////////////////////////////////btag Weights end////////////////////////



	
//		if ((denominator_trigger[trigger]==1)|| (denominator_trigger[trigger-1]==1)){  //only for ave 40 or ave 60
		if (denominator_trigger[trigger]==1){ 
			if (preselection_pass==0)counter+=genweight;
		
			if ((preselection_pass==0)||((preselection_pass==-2)&&(cut_count==1))) hJet1_pt->Fill(jets_pv[0].Pt(),genweight);
			if ((preselection_pass==0)||((preselection_pass==-3)&&(cut_count==1))) hJet2_pt->Fill(jets_pv[1].Pt(),genweight);
			if ((preselection_pass==0)||((preselection_pass==-4)&&(cut_count==1))) hJet3_pt->Fill(jets_pv[2].Pt(),genweight);
			if ((preselection_pass==0)||((preselection_pass==-5)&&(cut_count==1))) hJet4_pt->Fill(jets_pv[3].Pt(),genweight);

			if ((preselection_pass==0)||((preselection_pass==-7)&&(cut_count==1))) hDeltaEta->Fill(qqDeltaEta,genweight);
			if ((preselection_pass==0)||((preselection_pass==-8)&&(cut_count==1))) hDeltaPhi->Fill(bbDeltaPhi,genweight);
			if ((preselection_pass==0)) {hbtag->Fill(Jet.btagCMVA[jets_indices[btag_num1]],genweight); hbtag_log->Fill(-1.*TMath::Log(1-Jet.btagCMVA[jets_indices[btag_num1]]),genweight);}
			if ((preselection_pass==0)) {hbtag2->Fill(Jet.btagCMVA[jets_indices[btag_num2]],genweight);hbtag2_log->Fill(-1.*TMath::Log(1-Jet.btagCMVA[jets_indices[btag_num2]]),genweight);}

			if ((preselection_pass==0)||((preselection_pass==-6)&&(cut_count==1))) hMqq->Fill(Mqq, genweight);

		}
/*		float trigWeight = 1.;
		float trigCor1_nom[10] = {8.27936e+01 , 6.14282e+01};
		float trigCor2_nom[10] = {2.30286e+01,  3.08334e+01};
		if (data!=1) {
			func_r->FixParameter(0,1.);
			func_r->FixParameter(1,trigCor1_nom[0] );
			func_r->FixParameter(2,trigCor2_nom[0] );
			trigWeight*=func_r->Eval(jets_pv[0].Pt());
			func_r->FixParameter(1,trigCor1_nom[1] );
			func_r->FixParameter(2,trigCor2_nom[1] );
			trigWeight*=func_r->Eval(jets_pv[1].Pt());
		}

*/
		float trigCor_1btag_double[10] = { 5.65460e-01 ,-3.76206e-01 ,   9.45785e-01};
		float trigCor_1btag_single[10] = {  2.13366e-01, 2.43250e-01, 4.53758e-01 };
		float trigWeight = 1.;
		if (dataset_type.CompareTo("double")==0){
			func_erf_btag->FixParameter(0,trigCor_1btag_double[0]);
			func_erf_btag->FixParameter(1,trigCor_1btag_double[1]);
			func_erf_btag->FixParameter(2,trigCor_1btag_double[2]);
			func_erf_btag->FixParameter(3,0.);
		}
		if (dataset_type.CompareTo("single")==0){
			func_erf_btag->FixParameter(0,trigCor_1btag_single[0]);
			func_erf_btag->FixParameter(1,trigCor_1btag_single[1]);
			func_erf_btag->FixParameter(2,trigCor_1btag_single[2]);
			func_erf_btag->FixParameter(3,0.);
		}
		trigWeight*=func_erf_btag->Eval(-1.*TMath::Log(1-Jet.btagCMVA[jets_indices[btag_num1]]));
		


		int trigger_nominator = 0;
		if (dataset_type.CompareTo("single")==0) trigger_nominator = (((nominator_trigger[2]==1)||(nominator_trigger[3]==1))&&(denominator_trigger[trigger]==1));
		if (dataset_type.CompareTo("double")==0) trigger_nominator = (((nominator_trigger[0]==1)||(nominator_trigger[1]==1))&&(denominator_trigger[trigger]==1));
		if (trigger_nominator==1) {
			genweight*=trigWeight; 
			if (preselection_pass==0) counter_tr1+=genweight; 
	/*		if ((preselection_pass==0)||(preselection_pass==-2)||(preselection_pass==-3)||(preselection_pass==-4)||(preselection_pass==-5)) hJet1_pt_trigger->Fill(Jet.pt[0],genweight);
			if ((preselection_pass==0)||(preselection_pass==-2)||(preselection_pass==-3)||(preselection_pass==-4)||(preselection_pass==-5)) hJet2_pt_trigger->Fill(Jet.pt[1],genweight);
			if ((preselection_pass==0)||(preselection_pass==-2)||(preselection_pass==-3)||(preselection_pass==-4)||(preselection_pass==-5)) hJet3_pt_trigger->Fill(Jet.pt[2],genweight);
			if ((preselection_pass==0)||(preselection_pass==-2)||(preselection_pass==-3)||(preselection_pass==-4)||(preselection_pass==-5)) hJet4_pt_trigger->Fill(Jet.pt[3],genweight);*/

			if ((preselection_pass==0)||((preselection_pass==-2)&&(cut_count==1))) hJet1_pt_trigger->Fill(jets_pv[0].Pt(),genweight);
			if ((preselection_pass==0)||((preselection_pass==-3)&&(cut_count==1))) hJet2_pt_trigger->Fill(jets_pv[1].Pt(),genweight);
			if ((preselection_pass==0)||((preselection_pass==-4)&&(cut_count==1))) hJet3_pt_trigger->Fill(jets_pv[2].Pt(),genweight);
			if ((preselection_pass==0)||((preselection_pass==-5)&&(cut_count==1))) hJet4_pt_trigger->Fill(jets_pv[3].Pt(),genweight);

			if ((preselection_pass==0)||((preselection_pass==-7)&&(cut_count==1))) hDeltaEta_trigger->Fill(qqDeltaEta,genweight);
			if ((preselection_pass==0)||((preselection_pass==-8)&&(cut_count==1))) hDeltaPhi_trigger->Fill(bbDeltaPhi,genweight);
			
			if ((preselection_pass==0)) {hbtag_trigger->Fill(Jet.btagCMVA[jets_indices[btag_num1]],genweight); hbtag_log_trigger->Fill(-1.*TMath::Log(1-Jet.btagCMVA[jets_indices[btag_num1]]),genweight);}
			if ((preselection_pass==0)) {hbtag2_trigger->Fill(Jet.btagCMVA[jets_indices[btag_num2]],genweight);hbtag2_log_trigger->Fill(-1.*TMath::Log(1-Jet.btagCMVA[jets_indices[btag_num2]]),genweight);}

			if ((preselection_pass==0)||((preselection_pass==-6)&&(cut_count==1))) hMqq_trigger->Fill(Mqq, genweight);
			

		}

		

}

	TFile *f_output = new TFile(output+"/"+file_tag+"_"+dataset_type+"_trig"+std::to_string(trigger)+ending+".root","recreate");
	f_output->cd();
	for (int i=0;i<numArray;i++){
   	histArray[i]->Write();
   	histArray_notrigger[i]->Write();
	}
   f_output->Write();
	f_output->Close();
	
	ofstream out;
	out.open(output+"/"+file_tag+"_"+dataset_type+"_trig"+std::to_string(trigger)+ending+".txt");	
	out<<counter_tr1<<"\t"<<counter<<endl;
	out.close();



return 0; 

    
}
