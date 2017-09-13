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
//	Float_t Zbb_bdt;
} TreeJets;


void CreateTree_Zbb::Loop(TString inputfile, TString output_dir)
//void CreateTree_Zbb::Loop()
{
   if (fChain == 0) return;

   Long64_t nentries = fChain->GetEntriesFast();

   Long64_t nbytes = 0, nb = 0;

	TFile *output = TFile::Open(output_dir+".root","recreate");
	TTree *tree = fChain->CloneTree(0);
	TreeJets TreeJet;
	const int Nsyst=5;
	float Zbb_bdt[Nsyst];
	int pass_sel[Nsyst];
	TBranch *branchZbb_bdt[Nsyst];
	TString Zbb_bdt_names[Nsyst] = {"Zbb_bdt_JES_up","Zbb_bdt_JES_down","Zbb_bdt_JER_up","Zbb_bdt_JER_down","Zbb_bdt"};
	TBranch *branchPassSel[Nsyst];
	TString pass_sel_names[Nsyst] = {"PassSelection_JES_up","PassSelection_JES_down","PassSelection_JER_up","PassSelection_JER_down","PassSelection_nom"};
	for (int je_type=0;je_type<Nsyst;je_type++){
		branchZbb_bdt[je_type] = tree->Branch(Zbb_bdt_names[je_type],&Zbb_bdt[je_type],Zbb_bdt_names[je_type]+"/F");
		branchPassSel[je_type] = tree->Branch(pass_sel_names[je_type],&pass_sel[je_type],pass_sel_names[je_type]+"/I");
	}
//	TBranch *Zbb_bdt = tree->Branch("Zbb_bdt",&TreeJet.Zbb_bdt,"Zbb_bdt/F");
	TString weightfile = "/mnt/t3nfs01/data01/shome/nchernya/VBFHbb2016/Zbb_mva/weights/TMVAClassification_BDTG_alldoubleBDTIncl_try5_v25/Classification_BDTG.weights.xml";
   TMVA::Reader *reader = new TMVA::Reader("Silent");
	float var1,var2,var3,var4,var5,var6,var7,var8,var9,var10, var11;
	reader->AddVariable("DeltaEtaQQ",&var1);
	reader->AddVariable("CMVAV2_2",&var2);
	reader->AddVariable("qgl1",&var3);
	reader->AddVariable("qgl2",&var4);
	reader->AddVariable("DeltaEtaQB",&var5);
	reader->AddVariable("EtaBB",&var6);
	reader->AddSpectator("Mbb",&var7);
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
//  for (Long64_t jentry=0; jentry<100;jentry++) {
	 
	
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
		
		std::sort(btag_vec.begin(), btag_vec.begin()+loopJet_max,sort_pred() );
		std::sort(pt_vec.begin(), pt_vec.begin()+loopJet_max,sort_pred() );
		

		Int_t trigger_double=HLT_BIT_HLT_QuadPFJet_BTagCSV_p016_p11_VBF_Mqq200_v || HLT_BIT_HLT_QuadPFJet_BTagCSV_p016_p11_VBF_Mqq240_v;
		if (preselection_double(trigger_double, loopJet_max, jets_pv, btag_vec, pt_vec, btag_num1, btag_num2, pt_num1, pt_num2)!=0) 
		{
			Zbb_bdt[current_syst] = -10;		
			pass_sel[current_syst]=0;
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
		TLorentzVector bb;
		bb = Bjet1+Bjet2;
		Float_t qqDeltaEta = TMath::Abs(Qjet1.Eta()-Qjet2.Eta());


/*
	reader->AddVariable("DeltaEtaQQ",&var1);
	reader->AddVariable("CMVAV2_2",&var2);
	reader->AddVariable("qgl1",&var3);
	reader->AddVariable("qgl2",&var4);
	reader->AddVariable("DeltaEtaQB",&var5);
	reader->AddVariable("EtaBB",&var6);
*/
		var1 = qqDeltaEta;
		var2 = Jet_btagCMVAV2[jets_indices[btag_num2]];	
		var3 = Jet_qgl[jets_indices[pt_num1]];
		var4 = Jet_qgl[jets_indices[pt_num2]];
		var5 = (Qjet1.Eta()+Qjet2.Eta()) - (Bjet1.Eta()+Bjet2.Eta());
		var6 = TMath::Abs(bb.Eta());
		var7=bb.M();
		Zbb_bdt[current_syst] = reader->EvaluateMVA("BDTG");
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

   



	
