#define CreateTree_tmva_all_cxx
#include "CreateTree_tmva_all.h"
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
#include <TRandom.h>
#include <TRandom3.h>
#include "/afs/cern.ch/work/n/nchernya/VBFHbb_2016/plotter/preselection_single.C"
#include "/afs/cern.ch/work/n/nchernya/VBFHbb_2016/plotter/preselection_double.C"



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
	Float_t CMVAV2_1;
	Float_t CMVAV2_2;
	Float_t Mqq;
	Float_t Mbb;
	Float_t bb_pt;
	Float_t DeltaEtaQQ;
	Float_t DeltaEtaAveQB;
	Float_t DeltaPhiQQ;
	Float_t DeltaPhiBB;
	Int_t SoftN5;
	Int_t SoftN2;
	Int_t SoftN10;
	Float_t HTsoft;
	Float_t DeltaEtaQB1;
	Float_t DeltaEtaQB2;
	Float_t DeltaEtaQB;
	Float_t EtaBB;
	Float_t DeltaEtaQB_minus;
	Float_t cosOqqbb;
	Float_t qgl1_VBF;
	Float_t qgl2_VBF;
	Float_t x1;
	Float_t x2;
	Float_t VB1;
	Float_t VB2;
	Float_t Jet5_pt;
	Float_t Etot;
	Float_t blike1_VBF;
	Float_t blike2_VBF;
	Float_t axis2_jet1;
	Float_t axis2_jet2;
	Float_t qqbb_pt;
	Float_t qqbb_eta;
	Float_t qqbb_pz;
	Float_t qgl1;
	Float_t qgl2;
}TMVAstruct;


using namespace std;

void CreateTree_tmva_all::Loop(TString output_dir, int data, int set_type)
{
   if (fChain == 0) return;

   Long64_t nentries = fChain->GetEntries();

   Long64_t nbytes = 0, nb = 0;
	TMVAstruct TMVA;

	TString dataset_type_array[2] = {"double","single"};	
	TString dataset_type;
	if (set_type==0) dataset_type = "double";
	if (set_type==1) dataset_type = "single";

	int events_saved=0;

	float weight;	
 

	TFile file("main_tmva_tree_"+output_dir+"_v25_"+dataset_type+"_RandomNew2Incl2.root","recreate");
	TTree *tree0 = new TTree("TMVA","TMVA");
	tree0->Branch("CMVAV2_1",&TMVA.CMVAV2_1,"CMVAV@_1/F");
	tree0->Branch("CMVAV2_2",&TMVA.CMVAV2_2,"CMVAV2_2/F");
	tree0->Branch("Mqq",&TMVA.Mqq,"Mqq/F");
	tree0->Branch("Mbb",&TMVA.Mbb,"Mbb/F");
	tree0->Branch("bb_pt",&TMVA.bb_pt,"bb_pt/F");
	tree0->Branch("DeltaEtaQQ",&TMVA.DeltaEtaQQ,"DeltaEtaQQ/F");
	tree0->Branch("EtaBB",&TMVA.EtaBB,"EtaBB/F");
	tree0->Branch("DeltaPhiQQ",&TMVA.DeltaPhiQQ,"DeltaPhiQQ/F");
	tree0->Branch("DeltaPhiBB",&TMVA.DeltaPhiBB,"DeltaPhiBB/F");
	tree0->Branch("SoftN5",&TMVA.SoftN5,"SoftN5/I");
	tree0->Branch("SoftN2",&TMVA.SoftN2,"SoftN2/I");
	tree0->Branch("SoftN10",&TMVA.SoftN10,"SoftN10/I");
	tree0->Branch("HTsoft",&TMVA.HTsoft,"HTsoft/F");
	tree0->Branch("axis2_jet1",&TMVA.axis2_jet1,"axis2_jet1/F");
	tree0->Branch("axis2_jet2",&TMVA.axis2_jet2,"axis2_jet2/F");
	tree0->Branch("DeltaEtaQB1",&TMVA.DeltaEtaQB1,"DeltaEtaQB1/F");
	tree0->Branch("DeltaEtaQB2",&TMVA.DeltaEtaQB2,"DeltaEtaQB2/F");
	tree0->Branch("DeltaEtaQB",&TMVA.DeltaEtaQB,"DeltaEtaQB/F");
	tree0->Branch("DeltaEtaQB_minus",&TMVA.DeltaEtaQB_minus,"DeltaEtaQB_minus/F");
	tree0->Branch("DeltaEtaAveQB",&TMVA.DeltaEtaAveQB,"DeltaEtaAveQB/F");
	tree0->Branch("cosOqqbb",&TMVA.cosOqqbb,"cosOqqbb/F");
	tree0->Branch("qqbb_pt",&TMVA.qqbb_pt,"qqbb_pt/F");
	tree0->Branch("qqbb_eta",&TMVA.qqbb_eta,"qqbb_eta/F");
	tree0->Branch("qqbb_pz",&TMVA.qqbb_pz,"qqbb_pz/F");
	tree0->Branch("qgl1",&TMVA.qgl1,"qgl1/F");
	tree0->Branch("qgl2",&TMVA.qgl2,"qgl2/F");
	tree0->Branch("Etot",&TMVA.Etot,"Etot/F");
	tree0->Branch("Jet5_pt",&TMVA.Jet5_pt,"Jet5_pt/F");
	tree0->Branch("x1",&TMVA.x1,"x1/F");
	tree0->Branch("x2",&TMVA.x2,"x2/F");
	tree0->Branch("blike1_VBF",&TMVA.blike1_VBF,"blike1_VBF/F");
	tree0->Branch("blike2_VBF",&TMVA.blike2_VBF,"blike2_VBF/F");
	tree0->Branch("weight",&weight);


	TF1 *func_r = new TF1("erffunc",erf,0.,1000.,3);
	TF1 *func_erf_btag= new TF1("func_erf_btag","1.+ [3] + [0]/2.*(1.-TMath::Erf((x-[1])/[2]))",-10.,600.);


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
//pythia8 gluon (|eta|<2.0, pT inclusive, pythia ): -55.7067*x^7 + 113.218*x^6 -21.1421*x^5 -99.927*x^4 + 92.8668*x^3 -34.3663*x^2 + 6.27*x + 0.612992

	cout<<nentries<<endl;
/*	 TBits *bits = new TBits(nentries); //see http://root.cern.ch/root/html534/TBits.html
   //now assume you want to read N=1000 entries out of nentries
    Int_t N = 162000; 
    Int_t i=0;
    TRandom3 rand(0);
	 while(i<N) {
      Int_t j = rand.Uniform(0,nentries);
      if (bits->TestBitNumber(j)) continue;  //we have already seen this entry
      bits->SetBitNumber(j);
      i++;
  	 }

*/
	Int_t fbit = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry+=70) {
  // for (Long64_t jentry=0; jentry<nentries;jentry++) {
	   Long64_t ientry = LoadTree(jentry);
///   for (Long64_t ii=0; ii<N;ii++) {
///		 Long64_t jentry = bits->FirstSetBit(fbit);
	 //  Long64_t ientry = LoadTree(jentry);
	 //  if (ientry < 0) break;
	   nb = fChain->GetEntry(jentry);   nbytes += nb;

		if (data==1) genWeight = 1.;
		if (genWeight <0) continue;
		if (json!=1) continue;

		weight = puWeight;


		if (!((Vtype==-1)||(Vtype>3))) continue;


		int good_jets = 0;
		vector<TLorentzVector> jets_pv;
		vector<int> jets_indices;
		vector<pair<int, float> > btag_vec;	
		vector<pair<int, float> > blike_vec;	
		vector<pair<int, float> > pt_vec;	
		pair<int,float> aPair;
		float jets_btag_weight=1.;
		for (int i=0;i<nJet;i++){
			TLorentzVector jet0;
			if (!((Jet_id[i]>2)&&(Jet_puId[i]>0)&&(Jet_pt[i]>20) )) continue;
			jet0.SetPtEtaPhiM(Jet_pt[i],Jet_eta[i],Jet_phi[i],Jet_mass[i]);
			jets_pv.push_back(jet0);
			jets_indices.push_back(i);
			aPair.first = good_jets;
			aPair.second = Jet_btagCMVAV2[i];
			btag_vec.push_back(aPair);
			aPair.first = good_jets;
			aPair.second = Jet_pt[i];
			pt_vec.push_back(aPair);
			aPair.first = good_jets;
			aPair.second = Jet_blikelihood_b[good_jets]; ////_VBF[good_jets] !!!!!!
			blike_vec.push_back(aPair);
			good_jets++;
		}

		if (good_jets<4)continue;

		Float_t c=-0.853212; 
		for (int i=0;i<nJet;i++){
			if ((Jet_btagCMVAV2[i]>-0.853213) &&(Jet_btagCMVAV2[i]<-0.853211)) Jet_btagCMVAV2[i]=-10.;
		}
		for (int i=0;i<good_jets;i++){
			if ((btag_vec[i].second>-0.853213) &&(btag_vec[i].second<-0.853211)) 	btag_vec[i].second=-10.;
		}



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
		
		int loopJet_max = min(7,good_jets);

		std::sort(btag_vec.begin(), btag_vec.begin()+loopJet_max,sort_pred() );
		std::sort(blike_vec.begin(), blike_vec.begin()+loopJet_max,sort_pred() );
		std::sort(pt_vec.begin(), pt_vec.begin()+loopJet_max,sort_pred() );


		Int_t trigger_single=HLT_BIT_HLT_QuadPFJet_BTagCSV_p016_VBF_Mqq460_v || HLT_BIT_HLT_QuadPFJet_BTagCSV_p016_VBF_Mqq500_v;
		Int_t trigger_double=HLT_BIT_HLT_QuadPFJet_BTagCSV_p016_p11_VBF_Mqq200_v || HLT_BIT_HLT_QuadPFJet_BTagCSV_p016_p11_VBF_Mqq240_v;


		if (dataset_type.CompareTo("double")==0){
	//		if (preselection_single(trigger_single, loopJet_max, jets_pv, blike_vec, pt_vec, btag_num1, btag_num2, pt_num1, pt_num2)==0) continue;   //if passes single -> we don't want to put it in double set
			if (preselection_double(trigger_double, loopJet_max, jets_pv, btag_vec, pt_vec, btag_num1, btag_num2, pt_num1, pt_num2)!=0) continue;   //should pass double selection
//			if (preselection_double(trigger_double, loopJet_max, jets_pv, csv_vec, pt_vec, btag_num1, btag_num2, pt_num1, pt_num2)!=0) continue;   //should pass double selection
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




//////////////////////////////////btag Weights start////////////////////////
	if (data!=1) {
		jets_btag_weight*=Jet_btagWeightCMVAV2[jets_indices[btag_num1]];
		jets_btag_weight*=Jet_btagWeightCMVAV2[jets_indices[btag_num2]];
		weight*=jets_btag_weight;
	}
//////////////////////////////////btag Weights end////////////////////////

//////////////////////////////////// QGL weights start //////////////////////
		float qgl_weight=1.;
		if (!( (data==1)|| (Jet_partonFlavour[jets_indices[pt_num1]] ==0 ) || (TMath::Abs(Jet_eta[jets_indices[pt_num1]])>=2) || (Jet_qgl[jets_indices[pt_num1]] < 0) ) ) {
			if (TMath::Abs(Jet_partonFlavour[jets_indices[pt_num1]]) < 4 ) qgl_weight=func_qgl_q->Eval(Jet_qgl[jets_indices[pt_num1]]);
			if (TMath::Abs(Jet_partonFlavour[jets_indices[pt_num1]]) ==21 ) qgl_weight=func_qgl_g->Eval(Jet_qgl[jets_indices[pt_num1]]);
		}
		weight*=qgl_weight;
		qgl_weight=1.;
		if (!( (data==1)|| (Jet_partonFlavour[jets_indices[pt_num2]] ==0 ) || (TMath::Abs(Jet_eta[jets_indices[pt_num2]])>=2) || (Jet_qgl[jets_indices[pt_num2]] < 0)) ) {
			if (TMath::Abs(Jet_partonFlavour[jets_indices[pt_num2]]) < 4 ) qgl_weight=func_qgl_q->Eval(Jet_qgl[jets_indices[pt_num2]]);
			if (TMath::Abs(Jet_partonFlavour[jets_indices[pt_num2]]) ==21 ) qgl_weight=func_qgl_g->Eval(Jet_qgl[jets_indices[pt_num2]]);
		}
		weight*=qgl_weight;


//////////////////////////////////// QGL weights  end//////////////////////

////////////////////////////////trig Weights start //////////////////////////////////////

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
		weight*=trigWeight;
////////////////////////////////trig Weights end //////////////////////////////////////



		Float_t alpha_bjet1_reg = 1.;
		Float_t alpha_bjet2_reg = 1.;
		if (Jet_pt_regNew[btag_num1]>0.) alpha_bjet1_reg = Jet_pt_regNew[btag_num1]/Jet_pt[jets_indices[btag_num1]];
		if (Jet_pt_regNew[btag_num2]>0.) alpha_bjet2_reg = Jet_pt_regNew[btag_num2]/Jet_pt[jets_indices[btag_num2]];
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


		Float_t Jet5_pt = 0;
		for (int i=0;i<loopJet_max;i++){
			if ((i==btag_num1)||(i==btag_num2)||(i==pt_num1)||(i==pt_num2)) continue;
			Jet5_pt=jets_pv[i].Pt();
			break;
		}




		
		qq = Qjet1+Qjet2;
		Float_t Mqq = qq.M();
		Float_t bbDeltaPhi = TMath::Abs(Bjet1.DeltaPhi(Bjet2));
		Double_t qqDeltaPhi = TMath::Abs(Qjet1.DeltaPhi(Qjet2));
		Float_t qqDeltaEta = TMath::Abs(Qjet1.Eta()-Qjet2.Eta());
		Float_t bbDeltaEta = TMath::Abs(Bjet1.Eta()-Bjet2.Eta());
		TLorentzVector bb;
		bb = Bjet1+Bjet2;
		Float_t Mbb = bb.M();
		TLorentzVector bbqq;
		bbqq = Bjet1 + Bjet2 + Qjet1 + Qjet2;
		Float_t cosOqqbb =TMath::Cos( ( ( Bjet1.Vect() ).Cross(Bjet2.Vect()) ).Angle( ( Qjet1.Vect() ).Cross(Qjet2.Vect()) ) );	

		
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



		TMVA.Mqq = Mqq;
		TMVA.CMVAV2_1 = Jet_btagCMVAV2[jets_indices[btag_num1]];	
		TMVA.CMVAV2_2 = Jet_btagCMVAV2[jets_indices[btag_num2]];	
		TMVA.DeltaEtaQQ = qqDeltaEta;
		TMVA.EtaBB = TMath::Abs(bb.Eta());
		TMVA.DeltaPhiQQ = qqDeltaPhi;
		TMVA.DeltaPhiBB = bbDeltaPhi;
		TMVA.SoftN5 = softActivity_njets5;
		TMVA.SoftN2 = softActivity_njets2;
		TMVA.SoftN10 = softActivity_njets10;
		TMVA.HTsoft = softActivity_HT;
		TMVA.DeltaEtaQB1 = EtaBQ1;
		TMVA.DeltaEtaQB2 = EtaBQ2;
		TMVA.DeltaEtaQB = (EtaBQ1 + EtaBQ2);
		TMVA.DeltaEtaAveQB = (Qjet1.Eta()+Qjet2.Eta()) - (Bjet1.Eta()+Bjet2.Eta());
		TMVA.cosOqqbb = cosOqqbb;
		TMVA.Jet5_pt = Jet5_pt;
		TMVA.Etot = Etot;
		TMVA.x1 = x1;
		TMVA.x2 = x2;
		TMVA.blike1_VBF = Jet_blikelihood_b[btag_num1];
		TMVA.blike2_VBF = Jet_blikelihood_b[btag_num2];
		TMVA.Mbb = Mbb;
		TMVA.axis2_jet1 = Jet_axis2[jets_indices[pt_num1]];
		TMVA.axis2_jet2 = Jet_axis2[jets_indices[pt_num2]];
		TMVA.qgl1 = Jet_qgl[jets_indices[pt_num1]];
		TMVA.qgl2 = Jet_qgl[jets_indices[pt_num2]];
		TMVA.bb_pt = bb.Pt();
		TMVA.DeltaEtaQB_minus = (EtaBQ1 - EtaBQ2);
		TMVA.qqbb_pt = (Bjet1+Bjet2+Qjet1+Qjet2).Pt();
		TMVA.qqbb_eta = (Bjet1+Bjet2+Qjet1+Qjet2).Eta();
		TMVA.qqbb_pz = (Bjet1+Bjet2+Qjet1+Qjet2).Pz();

		tree0->Fill();	
		events_saved++;		
//		cout<<events_saved<<endl;
	   if (dataset_type.CompareTo("double")==0) if (events_saved>=60500) break; 
      if (dataset_type.CompareTo("single")==0) if (events_saved>=81019) break; 
//	   if (dataset_type.CompareTo("double")==0) if (events_saved>=12100) break; 
 //     if (dataset_type.CompareTo("single")==0) if (events_saved>=16200) break; 
	//	fbit = jentry+1;
	}  

	file.Write();
	file.Close();

}

