#define CreateTree_Zbb_cxx
#include "CreateTree_Zbb.h"

#include <TH2.h>
#include <TF1.h>
#include <TH1F.h>
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


Double_t erf( Double_t *x, Double_t *par){
  return par[0]/2.*(1.+TMath::Erf((x[0]-par[1])/par[2]));
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
	float trigWeight_JE[Nsyst];
	float trigWeight_up;
	float trigWeight_down;
	TBranch *branchVBF_bdt[Nsyst];
	TBranch *branchMbb[Nsyst];
	TBranch *branchTrigWeight[Nsyst];
	TBranch *branchTrigWeightUp;
	TBranch *branchTrigWeightDown;
	TBranch *branchBtag1num;
	TBranch *branchBtag2num;
	TBranch *branchQjet1num;
	TBranch *branchQjet2num;
	TBranch *branchQGL;
	int btag_number1 = -1;
	int btag_number2 = -1;
	int qjet_number1 = -1;
	int qjet_number2 = -1;
	float QGLweight = 1.;
	Float_t Mbb_reg_fsr_JE[Nsyst];
	TString VBF_bdt_names[Nsyst] = {"VBF_bdt_JES_up","VBF_bdt_JES_down","VBF_bdt_JER_up","VBF_bdt_JER_down","VBF_bdt"};
	TString Mbb_names[Nsyst] = {"Mbb_JES_up","Mbb_JES_down","Mbb_JER_up","Mbb_JER_down","Mbb"};
	TBranch *branchPassSel[Nsyst];
	TString pass_sel_names[Nsyst] = {"PassSelection_JES_up","PassSelection_JES_down","PassSelection_JER_up","PassSelection_JER_down","PassSelection_nom"};
	TString trigWeight_sel_names[Nsyst] = {"trigWeight_JES_up","trigWeight_JES_down","trigWeight_JER_up","trigWeight_JER_down","trigWeight_nom"};
	for (int je_type=0;je_type<Nsyst;je_type++){
		branchVBF_bdt[je_type] = tree->Branch(sel_type+VBF_bdt_names[je_type],&VBF_bdt[je_type],sel_type+VBF_bdt_names[je_type]+"/F");
		branchPassSel[je_type] = tree->Branch(sel_type+pass_sel_names[je_type],&pass_sel[je_type],sel_type+pass_sel_names[je_type]+"/I");
		branchTrigWeight[je_type] = tree->Branch(sel_type+trigWeight_sel_names[je_type],&trigWeight_JE[je_type],sel_type+trigWeight_sel_names[je_type]+"/F");
		branchMbb[je_type] = tree->Branch(sel_type+Mbb_names[je_type],&Mbb_reg_fsr_JE[je_type],sel_type+Mbb_names[je_type]+"/F");
	}
	branchBtag1num = tree->Branch(sel_type+"btag_num1",&btag_number1,sel_type+"btag_num1"+"/I");
	branchBtag2num = tree->Branch(sel_type+"btag_num2",&btag_number2,sel_type+"btag_num2"+"/I");
	branchQjet1num = tree->Branch(sel_type+"qjet_num1",&qjet_number1,sel_type+"qjet_num1"+"/I");
	branchQjet2num = tree->Branch(sel_type+"qjet_num2",&qjet_number2,sel_type+"qjet_num2"+"/I");
	branchTrigWeightUp = tree->Branch(sel_type+"trigWeightUp",&trigWeight_up,sel_type+"trigWeightUp"+"/F");
	branchTrigWeightUp = tree->Branch(sel_type+"trigWeightDown",&trigWeight_down,sel_type+"trigWeightDown"+"/F");
	branchQGL = tree->Branch(sel_type+"QGLweight",&QGLweight,sel_type+"QGLweight"+"/F");
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


	TF1 *func_r = new TF1("erffunc",erf,0.,1000.,3);
	TF1 *func_r_up = new TF1("erffunc_up",erf,0.,1000.,3);
	TF1 *func_r_down = new TF1("erffunc_down",erf,0.,1000.,3);
	TF1 *func_erf_btag= new TF1("func_erf_btag","1.+ [3] + [0]/2.*(1.-TMath::Erf((x-[1])/[2]))",-10.,600.);
	TF1 *func_erf_btag_up= new TF1("func_erf_btag_up","1.+ [3] + [0]/2.*(1.-TMath::Erf((x-[1])/[2]))",-10.,600.);
	TF1 *func_erf_btag_down= new TF1("func_erf_btag_down","1.+ [3] + [0]/2.*(1.-TMath::Erf((x-[1])/[2]))",-10.,600.);

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
//pythia8 quark (|eta|<2.0, pT inclusive, pythia ): -0.666978*x*x*x + 0.929524*x*x -0.255505*x + 0.981581



   for (Long64_t jentry=0; jentry<nentries;jentry++) {
//	 for (Long64_t jentry=8; jentry<20;jentry++) {
	 
	
///////////////////////////SYStematics loop////////////////////
		bool passes_any=false;	
     for (int current_syst=0;current_syst<Nsyst;current_syst++){
  //   for (int current_syst=0;current_syst<5;current_syst++){
  
//  		cout<<current_syst<<endl;
//	   Long64_t ientry = LoadTree(jentry);
//	   if (ientry < 0) break;
	   nb = fChain->GetEntry(jentry);   nbytes += nb;

		if (json!=1) continue;
		pass_sel[current_syst] = 0;	
		if ((isData==1) && (current_syst!=4)) continue;

		float Jet_pt_original[50];
		for (int i=0;i<nJet;i++)
			Jet_pt_original[i] = Jet_pt[i];


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
	
/*
		cout<<Jet_pt_original[0]<<"   "<<Jet_pt[0]<<endl;
		cout<<Jet_pt_original[1]<<"   "<<Jet_pt[1]<<endl;
		cout<<Jet_pt_original[2]<<"   "<<Jet_pt[2]<<endl;
		cout<<Jet_pt_original[3]<<"   "<<Jet_pt[3]<<endl;

		cout<<endl;
		cout<<endl;
*/
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

	//	if ((preselection_double(trigger_double, loopJet_max, jets_pv, btag_vec, pt_vec, btag_num1, btag_num2, pt_num1, pt_num2)!=0)||(preselection_single(trigger_single, loopJet_max, jets_pv, blike_vec, pt_vec, btag_num1, btag_num2, pt_num1, pt_num2)==0)) 
		if   (preselection_single(trigger_single, loopJet_max, jets_pv, blike_vec, pt_vec, btag_num1, btag_num2, pt_num1, pt_num2)!=0) 
		{
			VBF_bdt[current_syst] = -10;		
			pass_sel[current_syst]=0;
			trigWeight_JE[current_syst]=1.;
			trigWeight_up=1.;
			trigWeight_down=1.;
			Mbb_reg_fsr_JE[current_syst]=0.;
			btag_number1=-1.;
			btag_number2=-1.;
			qjet_number1=-1.;
			qjet_number2=-1.;
			QGLweight=1.;
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
	//	cout<<Bjet1.Pt()<<"  ";

		Float_t alpha_bjet1_reg = 1.;
		Float_t alpha_bjet2_reg = 1.;
		if (Jet_pt_regNew[btag_num1]>0.) alpha_bjet1_reg = Jet_pt_regNew[btag_num1]/Jet_pt_original[jets_indices[btag_num1]];
		if (Jet_pt_regNew[btag_num2]>0.) alpha_bjet2_reg = Jet_pt_regNew[btag_num2]/Jet_pt_original[jets_indices[btag_num2]];
		Bjet1*=alpha_bjet1_reg;	
		Bjet2*=alpha_bjet2_reg;	
		qq = Qjet1+Qjet2;
		float Mqq = qq.M();
		TLorentzVector bb;
		bb = Bjet1+Bjet2;
		float Mbb = bb.M();
		Float_t qqDeltaEta = TMath::Abs(Qjet1.Eta()-Qjet2.Eta());
		Double_t qqDeltaPhi = TMath::Abs(Qjet1.DeltaPhi(Qjet2));
//		cout<<Bjet1.Pt()<<endl;


		if (current_syst==4) {
			btag_number1=jets_indices[btag_num1];
			btag_number2=jets_indices[btag_num2];
			qjet_number1=jets_indices[pt_num1];
			qjet_number2=jets_indices[pt_num2];
		}

////////////////////////////////trig Weights start //////////////////////////////////////

		trigWeight_JE[current_syst] = 1.;
		trigWeight_up = 1.;
		trigWeight_down = 1.;
		float trigCor1_nom[10] = {8.27936e+01 , 6.14282e+01,4.82877e+01 };
		float trigCor2_nom[10] = {2.30286e+01,  3.08334e+01,2.03703e+01};
		float trigCor1_up[10] = {   6.98042e+01, 5.73656e+01,  4.61869e+01   };
		float trigCor2_up[10] = {  4.32075e+01, 3.95342e+01,  2.47467e+01 };
		float trigCor1_down[10] = { 8.73145e+01,6.46045e+01,  4.98213e+01 };
		float trigCor2_down[10] = {1.98761e+01 , 2.59148e+01 ,  1.66816e+01 };
		float trigCor_1btag_single[10] = {  2.13366e-01,  2.43250e-01 ,  4.53758e-01 , -3.63544e-03 };
		float trigCor_1btag_single_up[10] = {   2.45483e-01,  2.17494e-02 , 6.02979e-01 };
		float trigCor_1btag_single_down[10] = { 2.40780e-01,  4.01189e-01, 4.70670e-01   };
		float trigCor_1btag_double[10] = { 5.65460e-01, -3.76206e-01 ,   9.45785e-01};
		float trigCor_1btag_double_up[10] = {7.81024e-01, -6.22089e-01, 1.00052e+00}; 
		float trigCor_1btag_double_down[10] = {4.77663e-01 ,  -1.66043e-01,1.00580e+00 };
		float trigCor_2btag_double[10] = { 1.54834e-01,  -3.25802e-01,  3.62393e-01, -4.95807e-02  };   //after first btag
		float trigCor_2btag_double_up[10] = {1.27846e-01,-3.18694e-01,1.61907e-01,-4.82113e-03  };   //after first btag
		float trigCor_2btag_double_down[10] = {  3.27936e+01 , -7.55034e+00 ,3.85816e+00, -1.35285e-01   };   //after first btag
		if (isData!=1) {
			func_r->FixParameter(0,1.);
			func_r->FixParameter(1,trigCor1_nom[0] );
			func_r->FixParameter(2,trigCor2_nom[0] );
			trigWeight_JE[current_syst]*=func_r->Eval(jets_pv[0].Pt());
			func_r->FixParameter(1,trigCor1_nom[1] );
			func_r->FixParameter(2,trigCor2_nom[1] );
			trigWeight_JE[current_syst]*=func_r->Eval(jets_pv[1].Pt());
			func_r->FixParameter(1,trigCor1_nom[2] );
			func_r->FixParameter(2,trigCor2_nom[2] );
			trigWeight_JE[current_syst]*=func_r->Eval(jets_pv[2].Pt());

			if (sel_type_int==0){
				func_erf_btag->FixParameter(0,trigCor_1btag_double[0]);
				func_erf_btag->FixParameter(1,trigCor_1btag_double[1]);
				func_erf_btag->FixParameter(2,trigCor_1btag_double[2]);
				func_erf_btag->FixParameter(3,0.);
				trigWeight_JE[current_syst]*=func_erf_btag->Eval(-1.*TMath::Log(1-btag_vec[0].second));
				func_erf_btag->FixParameter(0,trigCor_2btag_double[0]);
				func_erf_btag->FixParameter(1,trigCor_2btag_double[1]);
				func_erf_btag->FixParameter(2,trigCor_2btag_double[2]);
				func_erf_btag->FixParameter(3,trigCor_2btag_double[3]);
				trigWeight_JE[current_syst]*=func_erf_btag->Eval(-1.*TMath::Log(1-btag_vec[1].second));
			}
			if (sel_type_int==1){
				func_erf_btag->FixParameter(0,trigCor_1btag_single[0]);
				func_erf_btag->FixParameter(1,trigCor_1btag_single[1]);
				func_erf_btag->FixParameter(2,trigCor_1btag_single[2]);
				func_erf_btag->FixParameter(3,trigCor_1btag_single[3]);
				trigWeight_JE[current_syst]*=func_erf_btag->Eval(-1.*TMath::Log(1-btag_vec[0].second));
			}
		}
		if ((current_syst==4) && (isData!=1)) {
			func_r_up->FixParameter(0,1.);
			func_r_up->FixParameter(1,trigCor1_up[0] );
			func_r_up->FixParameter(2,trigCor2_up[0] );
			trigWeight_up*=func_r_up->Eval(jets_pv[0].Pt());
			func_r_up->FixParameter(1,trigCor1_up[1] );
			func_r_up->FixParameter(2,trigCor2_up[1] );
			trigWeight_up*=func_r_up->Eval(jets_pv[1].Pt());
			func_r_up->FixParameter(1,trigCor1_up[2] );
			func_r_up->FixParameter(2,trigCor2_up[2] );
			trigWeight_up*=func_r_up->Eval(jets_pv[2].Pt());
		
			func_r_down->FixParameter(0,1.);
			func_r_down->FixParameter(1,trigCor1_down[0] );
			func_r_down->FixParameter(2,trigCor2_down[0] );
			trigWeight_down*=func_r_down->Eval(jets_pv[0].Pt());
			func_r_down->FixParameter(1,trigCor1_down[1] );
			func_r_down->FixParameter(2,trigCor2_down[1] );
			trigWeight_down*=func_r_down->Eval(jets_pv[1].Pt());
			func_r_down->FixParameter(1,trigCor1_down[2] );
			func_r_down->FixParameter(2,trigCor2_down[2] );
			trigWeight_down*=func_r_down->Eval(jets_pv[2].Pt());



			if (sel_type_int==0){
				func_erf_btag_up->FixParameter(0,trigCor_1btag_double_up[0]);
				func_erf_btag_up->FixParameter(1,trigCor_1btag_double_up[1]);
				func_erf_btag_up->FixParameter(2,trigCor_1btag_double_up[2]);
				func_erf_btag_up->FixParameter(3,0.);
				trigWeight_up*=func_erf_btag_up->Eval(-1.*TMath::Log(1-btag_vec[0].second));
				func_erf_btag_up->FixParameter(0,trigCor_2btag_double_up[0]);
				func_erf_btag_up->FixParameter(1,trigCor_2btag_double_up[1]);
				func_erf_btag_up->FixParameter(2,trigCor_2btag_double_up[2]);
				func_erf_btag_up->FixParameter(3,trigCor_2btag_double_up[3]);
				trigWeight_up*=func_erf_btag_up->Eval(-1.*TMath::Log(1-btag_vec[1].second));

				func_erf_btag_down->FixParameter(0,trigCor_1btag_double_down[0]);
				func_erf_btag_down->FixParameter(1,trigCor_1btag_double_down[1]);
				func_erf_btag_down->FixParameter(2,trigCor_1btag_double_down[2]);
				func_erf_btag_down->FixParameter(3,0.);
				trigWeight_down*=func_erf_btag_down->Eval(-1.*TMath::Log(1-btag_vec[0].second));
				func_erf_btag_down->FixParameter(0,trigCor_2btag_double_down[0]);
				func_erf_btag_down->FixParameter(1,trigCor_2btag_double_down[1]);
				func_erf_btag_down->FixParameter(2,trigCor_2btag_double_down[2]);
				func_erf_btag_down->FixParameter(3,trigCor_2btag_double_down[3]);
				trigWeight_down*=func_erf_btag_down->Eval(-1.*TMath::Log(1-btag_vec[1].second));

			}
			if (sel_type_int==1){
				func_erf_btag_up->FixParameter(0,trigCor_1btag_single_up[0]);
				func_erf_btag_up->FixParameter(1,trigCor_1btag_single_up[1]);
				func_erf_btag_up->FixParameter(2,trigCor_1btag_single_up[2]);
				func_erf_btag_up->FixParameter(3,trigCor_1btag_single_up[3]);
				trigWeight_up*=func_erf_btag_up->Eval(-1.*TMath::Log(1-btag_vec[0].second));

				func_erf_btag_down->FixParameter(0,trigCor_1btag_single_down[0]);
				func_erf_btag_down->FixParameter(1,trigCor_1btag_single_down[1]);
				func_erf_btag_down->FixParameter(2,trigCor_1btag_single_down[2]);
				func_erf_btag_down->FixParameter(3,trigCor_1btag_single_down[3]);
				trigWeight_down*=func_erf_btag_down->Eval(-1.*TMath::Log(1-btag_vec[0].second));
			}
		}

//////////////////////////////////////////////



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

		if (fsr_bjet>0) Mbb_reg_fsr_JE[current_syst]=(Bjet1 + Bjet2 + FSRjet).M();
		else  Mbb_reg_fsr_JE[current_syst]=(Bjet1+Bjet2).M();



		if ((current_syst==4)&&(isData!=1)) {
/////////////////////////////////// QGL weights start //////////////////////
		float qgl_weight=1.;
		if (!(  (Jet_partonFlavour[jets_indices[pt_num1]] ==0 ) || (TMath::Abs(Jet_eta[jets_indices[pt_num1]])>=2) || (Jet_qgl[jets_indices[pt_num1]] < 0) ) ) {
			if (TMath::Abs(Jet_partonFlavour[jets_indices[pt_num1]]) < 4 ) qgl_weight=func_qgl_q->Eval(Jet_qgl[jets_indices[pt_num1]]);
			if (TMath::Abs(Jet_partonFlavour[jets_indices[pt_num1]]) ==21 ) qgl_weight=func_qgl_g->Eval(Jet_qgl[jets_indices[pt_num1]]);
		}
		QGLweight*=qgl_weight;
		qgl_weight=1.;
		if (!( (Jet_partonFlavour[jets_indices[pt_num2]] ==0 ) || (TMath::Abs(Jet_eta[jets_indices[pt_num2]])>=2) || (Jet_qgl[jets_indices[pt_num2]] < 0)) ) {
			if (TMath::Abs(Jet_partonFlavour[jets_indices[pt_num2]]) < 4 ) qgl_weight=func_qgl_q->Eval(Jet_qgl[jets_indices[pt_num2]]);
			if (TMath::Abs(Jet_partonFlavour[jets_indices[pt_num2]]) ==21 ) qgl_weight=func_qgl_g->Eval(Jet_qgl[jets_indices[pt_num2]]);
		}
		QGLweight*=qgl_weight;


//////////////////////////////////// QGL weights  end//////////////////////

		}






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
//		cout<<Mqq<<"  "<<qqDeltaEta<<endl;
//		cout<<VBF_bdt[current_syst]<<endl;
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

   



	
