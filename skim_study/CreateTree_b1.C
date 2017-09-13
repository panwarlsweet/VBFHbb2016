#define CreateTree_b1_cxx
#include "CreateTree_b1.h"

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

int find(Float_t *a, Float_t value, int n){
	int num=0;
	for (int i =0;i<n;i++){
		if (a[i]==value) {
			num = i;
			i=n;
		}
	}
	return num;
}



struct sort_pred {
    bool operator()(const std::pair<int,float> &left, const std::pair<int,float> &right) {
        return left.second > right.second;
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
	Float_t btagCSV;
	Float_t btagBDT;
   Int_t pt_idx;
   Int_t eta_idx;
	Int_t btagCSV_idx;
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

void CreateTree_b1::Loop()
{
   if (fChain == 0) return;

   Long64_t nentries = fChain->GetEntriesFast();

   Long64_t nbytes = 0, nb = 0;


	Float_t presel =0.;
	Float_t all =0.;


   for (Long64_t jentry=0; jentry<nentries;jentry++) {
//   for (Long64_t jentry=0; jentry<10;jentry++) {
	   Long64_t ientry = LoadTree(jentry);
	   if (ientry < 0) break;
	   nb = fChain->GetEntry(jentry);   nbytes += nb;
		 
	  	all+=1;

//		if (region.CompareTo("single")==0) if (HLT_BIT_HLT_QuadPFJet_BTagCSV_p016_VBF_Mqq500_v!=1) continue;
//		if (region.CompareTo("double")==0) if (HLT_BIT_HLT_QuadPFJet_BTagCSV_p016_p11_VBF_Mqq240_v!=1) continue;

if (!((HLT_BIT_HLT_QuadPFJet_BTagCSV_p016_p11_VBF_Mqq200_v==1) || (HLT_BIT_HLT_QuadPFJet_BTagCSV_p016_p11_VBF_Mqq240_v==1) || (HLT_BIT_HLT_QuadPFJet_BTagCSV_p016_VBF_Mqq460_v==1) || (HLT_BIT_HLT_QuadPFJet_BTagCSV_p016_VBF_Mqq500_v==1) )) continue;

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
		vector<pair<int, float> > pt_vec;	
		pair<int,float> aPair;

		for (int i=0;i<nJet;i++){
			TLorentzVector jet0;
			if (!((Jet_id[i]>2)&&(Jet_puId[i]>0))) continue;
			jet0.SetPtEtaPhiM(Jet_pt[i],Jet_eta[i],Jet_phi[i],Jet_mass[i]);
			jets_pv.push_back(jet0);
			jets_indices.push_back(i);
			aPair.first = good_jets;
			aPair.second = Jet_btagCMVA[i];
			btag_vec.push_back(aPair);
			aPair.first = good_jets;
			aPair.second = Jet_pt[i];
			pt_vec.push_back(aPair);
			good_jets++;
		}
		Float_t c=-0.853212; 
		for (int i=0;i<nJet;i++){
			if ((Jet_btagCMVA[i]>-0.853213) &&(Jet_btagCMVA[i]<-0.853211)) Jet_btagCMVA[i]=-10.;
		}
		for (int i=0;i<good_jets;i++){
			if ((btag_vec[i].second>-0.853213) &&(btag_vec[i].second<-0.853211)) 	btag_vec[i].second=-10.;
		}
	//	cout<<endl;
		if (good_jets<4) continue;
		
		int loopJet_max = min(10,good_jets);
		
		std::sort(btag_vec.begin(), btag_vec.begin()+loopJet_max,sort_pred() );
		std::sort(pt_vec.begin(), pt_vec.begin()+loopJet_max,sort_pred() );

		

 //btag then pt

		btag_num1=btag_vec[0].first;
		btag_num2=btag_vec[1].first;
		Bjet1.SetPtEtaPhiM(jets_pv[btag_num1].Pt(),jets_pv[btag_num1].Eta(),jets_pv[btag_num1].Phi(),jets_pv[btag_num1].M());	
		Bjet2.SetPtEtaPhiM(jets_pv[btag_num2].Pt(),jets_pv[btag_num2].Eta(),jets_pv[btag_num2].Phi(),jets_pv[btag_num2].M());	
		int qjet_count=0;
		for(int i = 0; i < loopJet_max; i++){
			if (qjet_count==2) break;
			if ((pt_vec[i].first==btag_num1) || (pt_vec[i].first==btag_num2)) continue;	
			if (qjet_count==0) pt_num1=pt_vec[i].first;
			if (qjet_count==1) pt_num2=pt_vec[i].first;
			qjet_count++;
		}
		Qjet1.SetPtEtaPhiM(jets_pv[pt_num1].Pt(),jets_pv[pt_num1].Eta(),jets_pv[pt_num1].Phi(),jets_pv[pt_num1].M());	
		Qjet2.SetPtEtaPhiM(jets_pv[pt_num2].Pt(),jets_pv[pt_num2].Eta(),jets_pv[pt_num2].Phi(),jets_pv[pt_num2].M());	
		
//		cout<<btag_num1<<"  "<<btag_num2<<"  "<<pt_num1<<"  "<<pt_num2<<endl;
//		cout<<btag_vec[0].second<<"  "<<btag_vec[1].second<<"  "<<jets_pv[pt_num1].Pt()<<"  "<<jets_pv[pt_num2].Pt()<<endl;
	int max_loop = loopJet_max;
		float max_mjj=-1;
		for (int i=0;i<max_loop-1;i++){
			for (int j=i+1;j<max_loop;j++){
				float inv = (jets_pv[i]+jets_pv[j]).M();
				if (inv > max_mjj)  max_mjj =  inv;
			}
		}
		if ((HLT_BIT_HLT_QuadPFJet_BTagCSV_p016_VBF_Mqq460_v==1) || (HLT_BIT_HLT_QuadPFJet_BTagCSV_p016_VBF_Mqq500_v==1)){
			if (max_mjj < 430) continue;
		}
		else{

		if ((HLT_BIT_HLT_QuadPFJet_BTagCSV_p016_p11_VBF_Mqq200_v==1) || (HLT_BIT_HLT_QuadPFJet_BTagCSV_p016_p11_VBF_Mqq240_v==1)) {
			
			float detaqq=TMath::Abs(Qjet1.Eta()-Qjet2.Eta());
			float dphibb=TMath::Abs(Bjet1.Phi()-Bjet2.Phi());
			if (! ( (detaqq>2.3) && (dphibb<2.1) && ((Qjet1+Qjet2).M()>216))) continue;
		}
	}
		presel+=1;
	}  

	cout<<"all = "<<all<<" , presel = "<<presel<<endl;

}

   



	
