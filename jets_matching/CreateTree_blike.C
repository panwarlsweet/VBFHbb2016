#define CreateTree_blike_cxx
#include "CreateTree_blike.h"

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
	cout<<value<<" value not found"<<endl;
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
	

	


typedef struct {
   Float_t pt;
   Float_t eta;
	Float_t btagCMVA;
	Float_t btagBDT;
   Int_t pt_idx;
   Int_t eta_idx;
	Int_t btagCMVA_idx;
	Int_t btag_idx;
	Int_t type;
	Int_t ch_mult;
	Float_t ptd;
	Float_t leadTrPt;
	Float_t axis2;
	Int_t b_matched;
	Int_t q_matched;
	Int_t n_matched;
} TreeJets;

void CreateTree_blike::Loop(TString region)
{
   if (fChain == 0) return;

   Long64_t nentries = fChain->GetEntriesFast();

   Long64_t nbytes = 0, nb = 0;
	
	TFile file("blikelihood_v25_"+region+"_dR08.root","recreate");
	TTree *tree0 = new TTree("Jet_tree_b","Jet_tree_b");
	TreeJets TreeJet;
	tree0->Branch("Jet_pt",&TreeJet.pt,"Jet_pt/F");
	tree0->Branch("Jet_eta",&TreeJet.eta,"Jet_eta/F");
	tree0->Branch("Jet_btagCMVA",&TreeJet.btagCMVA,"Jet_btagCMVA/F");
	tree0->Branch("Jet_pt_idx",&TreeJet.pt_idx,"Jet_pt_idx/I");
	tree0->Branch("Jet_eta_idx",&TreeJet.eta_idx,"Jet_eta_idx/I");
	tree0->Branch("Jet_btagCMVA_idx",&TreeJet.btagCMVA_idx,"Jet_btagCMVA_idx/I");
//	tree0->Branch("Jet_chMult",&TreeJet.ch_mult,"Jet_chMult/I");
//	tree0->Branch("Jet_ptd",&TreeJet.ptd,"Jet_ptd/F");
//	tree0->Branch("Jet_leadTrackPt",&TreeJet.leadTrPt,"Jet_leadTrPt");
//	tree0->Branch("Jet_axis2",&TreeJet.axis2, "Jet_axis2");
	tree0->Branch("Jet_b_matched",&TreeJet.b_matched,"Jet_b_matched/I");
	tree0->Branch("Jet_q_matched",&TreeJet.q_matched,"Jet_q_matched/I");
	tree0->Branch("Jet_n_matched",&TreeJet.n_matched,"Jet_n_matched/I");


	Float_t bb_efficiency_find=0.;
	Float_t bb_efficiency=0.;
	Float_t qq_efficiency_find=0.;
	Float_t qq_efficiency=0.;
	Float_t presel =0.;


   for (Long64_t jentry=0; jentry<nentries;jentry++) {
//  for (Long64_t jentry=0; jentry<100;jentry++) {
	   Long64_t ientry = LoadTree(jentry);
	   if (ientry < 0) break;
	   nb = fChain->GetEntry(jentry);   nbytes += nb;
	 
		Float_t jet_isMatchedB = 0;
		Float_t jet_isMatchedQ = 0;
	  

		if (genWeight<0) continue;
		if (! ((Vtype==-1)||(Vtype>3))) continue;
	
		if (region.CompareTo("single")==0) if (HLT_BIT_HLT_QuadPFJet_BTagCSV_p016_VBF_Mqq500_v!=1) continue;
		if (region.CompareTo("double")==0) if (HLT_BIT_HLT_QuadPFJet_BTagCSV_p016_p11_VBF_Mqq240_v!=1) continue;

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

	   JetList jetList_CSV, jetList_pt, jetList_eta; 
		vector<pair<int, float> > btag_vec;	
		vector<pair<int, float> > abseta_vec;	
		vector<pair<int, float> > pt_vec;	
		pair<int,float> aPair;

		for (int i=0;i<nJet;i++){
			TLorentzVector jet0;
			if (!((Jet_id[i]>2)&&(Jet_puId[i]>0))) continue;
			jet0.SetPtEtaPhiM(Jet_pt[i],Jet_eta[i],Jet_phi[i],Jet_mass[i]);
			//	cout<<Jet_btagCMVA[i]<<endl;
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
	//	for (int i=0;i<good_jets;i++)
	//		cout<<btag_vec[i].second<<"  "<<Jet_btagCMVA[jets_indices[i]]<<endl;
	//	for (int i=0;i<nJet;i++)
	//		cout<<Jet_btagCMVA[i]<<endl;
			
		if (good_jets<4) continue;
		
		int loopJet_max = min(7,good_jets);
		
		std::sort(btag_vec.begin(), btag_vec.begin()+loopJet_max,sort_pred() );
		std::sort(abseta_vec.begin(), abseta_vec.begin()+loopJet_max,sort_pred_less());
//		for (int i=0;i<btag_vec.size();i++)
//			cout<<btag_vec[i].second<<"  ";
//		cout<<endl;
		
	Float_t bb_found = 0.;
	Float_t qq_found = 0.;
	float dR=0.8;

	  for(int i=0; i<loopJet_max; i++){
			TreeJet.b_matched=0;
			TreeJet.q_matched=0;
			TreeJet.n_matched=0;
		   TreeJet.pt=jets_pv[i].Pt();
			TreeJet.pt_idx = i;
		   TreeJet.eta=TMath::Abs(jets_pv[i].Eta()); 
			TreeJet.eta_idx = find(abseta_vec,TreeJet.eta,loopJet_max);
		   TreeJet.btagCMVA=Jet_btagCMVA[jets_indices[i]]; 
			TreeJet.btagCMVA_idx = find(btag_vec,TreeJet.btagCMVA,loopJet_max);

	//		cout<<TreeJet.pt<<" "<<TreeJet.pt_idx<<"   "<<TreeJet.btagCMVA<<" "<<TreeJet.btagCMVA_idx<<"  "<<TreeJet.eta<<"   "<<TreeJet.eta_idx<<endl;
	//		if (TMath::Abs(Jet_hadronFlavour[jets_indices[i]])==5) TreeJet.b_matched=1;
	//		if (TMath::Abs(Jet_partonFlavour[jets_indices[i]])==5) TreeJet.b_matched=1;
	//		else TreeJet.n_matched=1;

		   TLorentzVector hJ0;
		   hJ0.SetPtEtaPhiM(jets_pv[i].Pt(),jets_pv[i].Eta(),jets_pv[i].Phi(),jets_pv[i].M());	
		   for(int j =0; j<2; j++){
			   if(TMath::Abs(GenBQuarkFromH_pdgId[j])==5){
            	TLorentzVector hQQ;
               hQQ.SetPtEtaPhiM(GenBQuarkFromH_pt[j],GenBQuarkFromH_eta[j],GenBQuarkFromH_phi[j],GenBQuarkFromH_mass[j]);
              	if(hQQ.DeltaR(hJ0)<dR){ TreeJet.b_matched =1; bb_found++;  }
            } 
		   }
		   for(int j =0; j<2; j++){
				TLorentzVector hQ;
				hQ.SetPtEtaPhiM(GenHiggsSisters_pt[j],GenHiggsSisters_eta[j],GenHiggsSisters_phi[j],GenHiggsSisters_mass[j]);
				if(hQ.DeltaR(hJ0)<dR){TreeJet.q_matched = 1; qq_found++;}
		   }
			if ((TreeJet.b_matched==0)&&(TreeJet.q_matched==0)) TreeJet.n_matched=1;

		 	tree0->Fill();
		 }



		if (bb_found>=2) bb_efficiency_find+=TMath::Sign(1.,genWeight);
		if (qq_found>=2) qq_efficiency_find+=TMath::Sign(1.,genWeight);

		presel+=TMath::Sign(1.,genWeight);
	}  

	file.Write();
	file.Close();
}

   



	
