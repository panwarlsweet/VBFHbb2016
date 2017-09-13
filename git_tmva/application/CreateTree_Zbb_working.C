#define CreateTree_Zbb_cxx
#include "CreateTree_Zbb.h"

#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include "TLorentzVector.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <vector>
#include <utility>
#include "TMVA/Factory.h"
#include "TMVA/Tools.h"
#include "TMVA/Reader.h"
#include "/afs/cern.ch/work/n/nchernya/VBFHbb_2016/plotter/preselection_double.C"
#include "/afs/cern.ch/work/n/nchernya/VBFHbb_2016/plotter/preselection_single.C"


using namespace std;

typedef std::map<Float_t, Int_t> JetList;

#define SWAP(A, B) { Float_t t = A; A = B; B = t; }
void bubblesort(Float_t *a, int n){
  int i, j;
  for (i = 0; i<n-1; i++){
    for (j = 0; j < n-1-i; j++){
      if (a[j] > a[j + 1]){
        SWAP( a[j], a[j + 1] );
		}
    }
  }
}
void bubblesort2(Float_t *a, int n){
  int i, j;
  //for (i = n - 1; i >= 0; i--){
    //for (j = 0; j < i; j++){
  for (i = 0; i<n-1; i++){
    for (j = 0; j < n-1-i; j++){
      if (a[j] < a[j + 1]){
        SWAP( a[j], a[j + 1] );
		}
    }
  }
}

int find_old(Float_t *a, Float_t value, int n){
	int num=0;
	for (int i =0;i<n;i++){
		if (a[i]==value) {
			num = i;
			i=n;
		}
	}
	return num;
}

int find(vector<pair<int,float> > a, Float_t value, int n){
	int num=0;
	for (int i =0;i<n;i++){
		if (a[i].second==value) {
			num = i;
			return num;
		}
	}
	return -1;
}



struct sort_pred {
    bool operator()(const std::pair<int,float> &left, const std::pair<int,float> &right) {
        return left.second > right.second;
    }
};
struct sort_pred_less {
    bool operator()(const std::pair<int,float> &left, const std::pair<int,float> &right) {
        return left.second < right.second;
    }
};
struct sort_pred2 {
    bool operator()(const std::pair<pair<int, int> ,float> &left, const std::pair<pair<int, int> ,float> &right) {
        return left.second > right.second;
    }
};
	

	
const Int_t njets = 25;

typedef struct {
   Float_t pt[njets];
   Float_t eta[njets];
	Float_t btagCMVA[njets];
	Float_t btagBDT[njets];
   Int_t pt_idx[njets];
   Int_t eta_idx[njets];
	Int_t btagCMVA_idx[njets];
	Int_t btag_idx[njets];
	Int_t type[njets];
	Float_t blike_b[njets];
	Float_t blike_q[njets];
	Int_t ch_mult[njets];
	Float_t leadTrPt[njets];
	Float_t axis2[njets];
	Float_t ptd[njets];
	Int_t b_matched[njets];
	Int_t q_matched[njets];
	Int_t bb_chosen;
} TreeJets;


void CreateTree_Zbb::Loop(TString inputfile, TString output_dir, int sel_type_int)
//void CreateTree_Zbb::Loop()
{
   if (fChain == 0) return;

   Long64_t nentries = fChain->GetEntriesFast();

   Long64_t nbytes = 0, nb = 0;

	TString sel_type;
	if (sel_type_int==0) sel_type="double";
	if (sel_type_int==1) sel_type="single";


	TFile *output = TFile::Open(output_dir+".root","recreate");
	TTree *tree = fChain->CloneTree(0);
	TreeJets TreeJet;
	const int Nsyst=5;
	float VBF_bdt[Nsyst];
	int pass_sel[Nsyst];
	TBranch *branchVBF_bdt[Nsyst];
	TString VBF_bdt_names[Nsyst] = {"VBF_bdt_JES_up","VBF_bdt_JES_down","VBF_bdt_JER_up","VBF_bdt_JER_down","VBF_bdt"};
	TBranch *branchPassSel[Nsyst];
	TString pass_sel_names[Nsyst] = {"PassSelection_JES_up","PassSelection_JES_down","PassSelection_JER_up","PassSelection_JER_down","PassSelection_nom"};
	for (int je_type=0;je_type<Nsyst;je_type++){
		branchVBF_bdt[je_type] = tree->Branch(sel_type+VBF_bdt_names[je_type],&VBF_bdt[je_type],sel_type+VBF_bdt_names[je_type]+"/F");
		branchPassSel[je_type] = tree->Branch(sel_type+pass_sel_names[je_type],&pass_sel[je_type],sel_type+pass_sel_names[je_type]+"/I");
	}
	TString weightfile;
	if (sel_type_int==0) weightfile="/mnt/t3nfs01/data01/shome/nchernya/VBFHbb2016/main_mva/weights/TMVAClassification_BDTG_alldoubletryOpt9_v25/Classification_BDTG.weights.xml";
	if (sel_type_int==1) weightfile="/mnt/t3nfs01/data01/shome/nchernya/VBFHbb2016/main_mva/weights/TMVAClassification_BDTG_allsingletryOpt2_v25/Classification_BDTG.weights.xml";
   TMVA::Reader *reader = new TMVA::Reader("Silent");
	float var1,var2,var3,var4,var5,var6,var7,var8,var9,var10, var11;
	//Mqq   ,   DeltaEtaQQ   ,   DeltaPhiQQ   ,   SoftN5   ,   CMVAV2_1   ,   CMVAV2_2   ,   qgl1   ,   qgl2   ,   DeltaEtaQB   ,   qqbb_pz  
	reader->AddVariable("Mqq",&var1);
	reader->AddVariable("DeltaEtaQQ",&var2);
	reader->AddVariable("DeltaPhiQQ",&var3);
	reader->AddVariable("SoftN5",&var4);
	reader->AddVariable("CMVAV2_1",&var5);
	reader->AddVariable("CMVAV2_2",&var6);
	reader->AddVariable("qgl1",&var7);
	reader->AddVariable("qgl2",&var8);
	reader->AddVariable("DeltaEtaQB",&var9);
	reader->AddVariable("qqbb_pz",&var10);
	reader->AddSpectator("Mbb",&var11);
	reader->BookMVA("BDTG", weightfile);
	

	TFile *input_file = TFile::Open(inputfile);
	TH1F*	Count = (TH1F*)input_file->Get("Count");
	TH1F*	CountPosWeight = (TH1F*)input_file->Get("CountPosWeight");
	TH1F*	CountNegWeight =(TH1F*)input_file->Get("CountNegWeight");
	TH1F*	CountWeighted =(TH1F*)input_file->Get("CountWeighted");
	TH1F* CountFullWeighted  = (TH1F*)input_file->Get("CountFullWeighted");
	TH1F* CountWeightedLHEWeightScale  = (TH1F*)input_file->Get("CountWeightedLHEWeightScale");
	TH1F* CountWeightedLHEWeightPdf  = (TH1F*)input_file->Get("CountWeightedLHEWeightPdf");




   for (Long64_t jentry=0; jentry<nentries;jentry++) {
//  for (Long64_t jentry=0; jentry<1000;jentry++) {
	 
	
///////////////////////////SYStematics loop////////////////////
		bool passes_any=false;	
     for (int current_syst=0;current_syst<Nsyst;current_syst++){
  //   for (int current_syst=1;current_syst<3;current_syst++){
  //
	   Long64_t ientry = LoadTree(jentry);
	   if (ientry < 0) break;
	   nb = fChain->GetEntry(jentry);   nbytes += nb;

		if (json!=1) continue;
		pass_sel[current_syst] = 0;	
		if ((isData==1) && (current_syst!=4)) continue;

		for (int i=0;i<nJet;i++){
			if (current_syst==0) {
				if ((Jet_corr_JECUp[i]<=0)||(Jet_corr[i]<=0)){ Jet_pt[i] = Jet_pt[i]; Jet_mass[i] = Jet_mass[i];}
				else {
					Jet_pt[i] = Jet_pt[i]*Jet_corr_JECUp[i]/Jet_corr[i];  Jet_mass[i]=Jet_mass[i]*Jet_corr_JECUp[i]/Jet_corr[i]; 
				} 
			}
			if (current_syst==1) {
		//		cout<<Jet_pt[0]<<"  ";
				if ((Jet_corr_JECDown[i]<=0)||(Jet_corr[i]<=0)){ Jet_pt[i] = Jet_pt[i]; Jet_mass[i] = Jet_mass[i];}
				else {
					Jet_pt[i] = Jet_pt[i]*Jet_corr_JECDown[i]/Jet_corr[i];Jet_mass[i]=Jet_mass[i]*Jet_corr_JECDown[i]/Jet_corr[i];
		//		cout<<Jet_pt[0]<<endl;
				}
			}
			if (current_syst==2) {
				if ((Jet_corr_JERUp[i]<=0)||(Jet_corr_JER[i]<=0)){ Jet_pt[i] = Jet_pt[i]; Jet_mass[i] = Jet_mass[i];}
				else	{
					Jet_pt[i] =  Jet_pt[i]*Jet_corr_JERUp[i]/Jet_corr_JER[i]; 
					Jet_mass[i]=Jet_mass[i]*Jet_corr_JERUp[i]/Jet_corr_JER[i];
				}
			}
			if (current_syst==3) {
				if ((Jet_corr_JERDown[i]<=0)||(Jet_corr_JER[i]<=0)){ Jet_pt[i] = Jet_pt[i]; Jet_mass[i] = Jet_mass[i];}
				else {
					Jet_pt[i] =  Jet_pt[i]*Jet_corr_JERDown[i]/Jet_corr_JER[i];
					Jet_mass[i]=Jet_mass[i]*Jet_corr_JERDown[i]/Jet_corr_JER[i];
				} 
			}
		}




		int pt_num1 = -1;
		int pt_num2 = -1;
		int btag_num1 = -1;
		int btag_num2 = -1;
		TLorentzVector Qjet1;
		TLorentzVector Qjet2;
		TLorentzVector Bjet1;
		TLorentzVector Bjet2;
		TLorentzVector qq;
		TLorentzVector bb;
		int good_jets = 0;
		vector<TLorentzVector> jets_pv;
		vector<int> jets_indices;

		vector<pair<int, float> > btag_vec;	
		vector<pair<int, float> > blike_vec;	
		vector<pair<int, float> > abseta_vec;	
		vector<pair<int, float> > pt_vec;	
		pair<int,float> aPair;

		for (int i=0;i<nJet;i++){
			TLorentzVector jet0;
			if (!((Jet_id[i]>2)&&(Jet_puId[i]>0)&&(Jet_pt[i]>20))) continue;
			jet0.SetPtEtaPhiM(Jet_pt[i],Jet_eta[i],Jet_phi[i],Jet_mass[i]);
			jets_pv.push_back(jet0);
			jets_indices.push_back(i);
			aPair.first = good_jets;
			aPair.second = Jet_btagCMVA[i];
			btag_vec.push_back(aPair);
			aPair.first = good_jets;
			aPair.second = Jet_pt[i];
			pt_vec.push_back(aPair);
			aPair.first = good_jets;
			aPair.second = TMath::Abs(Jet_eta[i]);
			abseta_vec.push_back(aPair);
			aPair.first = good_jets;
			aPair.second = Jet_blikelihood_b[good_jets]; ////_VBF[good_jets] !!!!!!
			blike_vec.push_back(aPair);
			good_jets++;
		}
	
		Float_t c=-0.853212; 
		for (int i=0;i<nJet;i++){
			if ((Jet_btagCMVA[i]>-0.853213) &&(Jet_btagCMVA[i]<-0.853211)) Jet_btagCMVA[i]=-10.;
		}
		for (int i=0;i<good_jets;i++){
			if ((btag_vec[i].second>-0.853213) &&(btag_vec[i].second<-0.853211)) 	btag_vec[i].second=-10.;
		}
		
		int loopJet_max = min(7,good_jets);
	
		if (good_jets<4) continue;
	
		std::sort(btag_vec.begin(), btag_vec.begin()+loopJet_max,sort_pred() );
		std::sort(blike_vec.begin(), blike_vec.begin()+loopJet_max,sort_pred() );
		std::sort(pt_vec.begin(), pt_vec.begin()+loopJet_max,sort_pred() );
		
		Int_t trigger_single=HLT_BIT_HLT_QuadPFJet_BTagCSV_p016_VBF_Mqq460_v || HLT_BIT_HLT_QuadPFJet_BTagCSV_p016_VBF_Mqq500_v;
		Int_t trigger_double=HLT_BIT_HLT_QuadPFJet_BTagCSV_p016_p11_VBF_Mqq200_v || HLT_BIT_HLT_QuadPFJet_BTagCSV_p016_p11_VBF_Mqq240_v;

	//	if (preselection_double(trigger_double, loopJet_max, jets_pv, btag_vec, pt_vec, btag_num1, btag_num2, pt_num1, pt_num2)!=0) 
		if   (preselection_single(trigger_single, loopJet_max, jets_pv, blike_vec, pt_vec, btag_num1, btag_num2, pt_num1, pt_num2)!=0) 
		{
			VBF_bdt[current_syst] = -10;		
			pass_sel[current_syst]=0;
		//		cout <<"oops"<<endl;
		//		cout<<evt<<endl;				
		//		cout<<good_jets<<endl;				
		//		cout<<btag_num1<<"   "<<btag_num2<<endl;				
		//		cout<<pt_num1<<"   "<<pt_num2<<endl;				
		} else {
		passes_any=true;
		pass_sel[current_syst]=1;

		Bjet1.SetPtEtaPhiM(jets_pv[btag_num1].Pt(),jets_pv[btag_num1].Eta(),jets_pv[btag_num1].Phi(),jets_pv[btag_num1].M());	
		Bjet2.SetPtEtaPhiM(jets_pv[btag_num2].Pt(),jets_pv[btag_num2].Eta(),jets_pv[btag_num2].Phi(),jets_pv[btag_num2].M());	
		Qjet1.SetPtEtaPhiM(jets_pv[pt_num1].Pt(),jets_pv[pt_num1].Eta(),jets_pv[pt_num1].Phi(),jets_pv[pt_num1].M());	
		Qjet2.SetPtEtaPhiM(jets_pv[pt_num2].Pt(),jets_pv[pt_num2].Eta(),jets_pv[pt_num2].Phi(),jets_pv[pt_num2].M());	

		Float_t alpha_bjet1_reg = 1.;
		Float_t alpha_bjet2_reg = 1.;
		if (Jet_pt_regNew[btag_num1]>0.) alpha_bjet1_reg = Jet_pt_regNew[btag_num1]/Jet_pt[jets_indices[btag_num1]];
		if (Jet_pt_regNew[btag_num2]>0.) alpha_bjet2_reg = Jet_pt_regNew[btag_num2]/Jet_pt[jets_indices[btag_num2]];
		Bjet1*=alpha_bjet1_reg;	
		Bjet2*=alpha_bjet2_reg;	
		qq = Qjet1+Qjet2;
		float Mqq = qq.M();
		TLorentzVector bb;
		bb = Bjet1+Bjet2;
		float Mbb = bb.M();
		Float_t qqDeltaEta = TMath::Abs(Qjet1.Eta()-Qjet2.Eta());
		Double_t qqDeltaPhi = TMath::Abs(Qjet1.DeltaPhi(Qjet2));

	//1			2						3						4				5						6				7				8			9						10	
	//Mqq   ,   DeltaEtaQQ   ,   DeltaPhiQQ   ,   SoftN5   ,   CMVAV2_1   ,   CMVAV2_2   ,   qgl1   ,   qgl2   ,   DeltaEtaQB   ,   qqbb_pz  
		
		var1 = Mqq;
		var2 = qqDeltaEta;
		var3 = qqDeltaPhi;
		var4 = softActivity_njets5;
		var5 = Jet_btagCMVAV2[jets_indices[btag_num1]];	
		var6 = Jet_btagCMVAV2[jets_indices[btag_num2]];	
		var7 = Jet_qgl[jets_indices[pt_num1]];
		var8 = Jet_qgl[jets_indices[pt_num2]];
		var9 = (Qjet1.Eta()+Qjet2.Eta()) - (Bjet1.Eta()+Bjet2.Eta());
		var10 = (Bjet1+Bjet2+Qjet1+Qjet2).Pz();
		var11 = Mbb;
		VBF_bdt[current_syst] = reader->EvaluateMVA("BDTG");
		} //preselection loop ends
	  } //// systematics loop ends
	//	if (passes_any==true)	tree->Fill();
		tree->Fill();
	}  

	delete reader;
	output->cd();
	tree->AutoSave();
	Count->Write();
	CountPosWeight->Write();
	CountNegWeight->Write();
	CountWeighted->Write();
	CountFullWeighted->Write();
	CountWeightedLHEWeightScale->Write();
	CountWeightedLHEWeightPdf->Write();
	output->Close();
	input_file->Close();
}

   



	
