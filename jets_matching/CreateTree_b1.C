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

void CreateTree_b1::Loop(TString region)
{
   if (fChain == 0) return;

   Long64_t nentries = fChain->GetEntriesFast();

   Long64_t nbytes = 0, nb = 0;


	Float_t bb_efficiency_find=0.;
	Float_t bb_efficiency=0.;
	Float_t qq_efficiency_find=0.;
	Float_t qq_efficiency=0.;
	Float_t presel =0.;


   for (Long64_t jentry=0; jentry<nentries;jentry++) {
//   for (Long64_t jentry=0; jentry<10;jentry++) {
	   Long64_t ientry = LoadTree(jentry);
	   if (ientry < 0) break;
	   nb = fChain->GetEntry(jentry);   nbytes += nb;
	 
		Float_t jet_isMatchedB = 0;
		Float_t jet_isMatchedQ = 0;
	  

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
		vector<pair<int, float> > blike_vec;	
		vector<pair<int, float> > blike_old_vec;	
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
			aPair.first = good_jets;
			aPair.second = Jet_blikelihood_b[i];
			blike_vec.push_back(aPair);
			aPair.first = good_jets;
			aPair.second = Jet_blike_VBF[i];
			blike_old_vec.push_back(aPair);
	//		cout<<Jet_pt[i]<<"  "<<Jet_btagCMVA[i]<<"  ";
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
		
		int loopJet_max = min(7,good_jets);
		
		vector<pair<pair<int, int >, float> > deta_vec;	
		vector<float> deta_vec_simple;	
		pair<int,int> bPair;
		pair<pair<int, int> ,float> cPair;
		for (int i=0;i<loopJet_max-1;i++){
			for (int j=i+1;j<loopJet_max;j++){
				bPair.first = i;	
				bPair.second = j;
				cPair.first = bPair;
				cPair.second = TMath::Abs(jets_pv[i].Eta() - jets_pv[j].Eta());
				deta_vec.push_back(cPair);
				deta_vec_simple.push_back(TMath::Abs(jets_pv[i].Eta() - jets_pv[j].Eta()));
		//		cout<<(TMath::Abs(jets_pv[i].Eta() - jets_pv[j].Eta()))<<" "<<i<<" "<<j<<endl;
			}
		}	


		std::sort(btag_vec.begin(), btag_vec.begin()+loopJet_max,sort_pred() );
		std::sort(blike_vec.begin(), blike_vec.begin()+loopJet_max,sort_pred() );
		std::sort(blike_old_vec.begin(), blike_old_vec.begin()+loopJet_max,sort_pred() );
		std::sort(pt_vec.begin(), pt_vec.begin()+loopJet_max,sort_pred() );
		std::sort(deta_vec.begin(), deta_vec.end(),sort_pred2() );
		
	//	for (int i=0;i<deta_vec_simple.size();i++)
	//		cout<<deta_vec_simple[i]<<"  ";
	//	cout<<endl;
	//	cout<<"eta max "<<deta_vec[0].second<<"  "<<(deta_vec[0].first).first<<"  "<<(deta_vec[0].first).second<<endl;


 //blikelihood then pt

		btag_num1=blike_vec[0].first;
		btag_num2=blike_vec[1].first;
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




/*
//first btag then deta
		btag_num1=btag_vec[0].first;
		btag_num2=btag_vec[1].first;
		Bjet1.SetPtEtaPhiM(jets_pv[btag_num1].Pt(),jets_pv[btag_num1].Eta(),jets_pv[btag_num1].Phi(),jets_pv[btag_num1].M());	
		Bjet2.SetPtEtaPhiM(jets_pv[btag_num2].Pt(),jets_pv[btag_num2].Eta(),jets_pv[btag_num2].Phi(),jets_pv[btag_num2].M());	
		for(int i = 0; i < deta_vec.size(); i++){
			if (( (deta_vec[i].first).first==btag_num1) ||((deta_vec[i].first).first==btag_num2) || ( (deta_vec[i].first).second==btag_num1) ||((deta_vec[i].first).second==btag_num2) ) continue;	
			pt_num1=(deta_vec[i].first).first;
			pt_num2=(deta_vec[i].first).second;
			break;
		}
		Qjet1.SetPtEtaPhiM(jets_pv[pt_num1].Pt(),jets_pv[pt_num1].Eta(),jets_pv[pt_num1].Phi(),jets_pv[pt_num1].M());	
		Qjet2.SetPtEtaPhiM(jets_pv[pt_num2].Pt(),jets_pv[pt_num2].Eta(),jets_pv[pt_num2].Phi(),jets_pv[pt_num2].M());	*/

/*
		//deta then btag
		pt_num1=(deta_vec[0].first).first;
		pt_num2=(deta_vec[0].first).second;
		Qjet1.SetPtEtaPhiM(jets_pv[pt_num1].Pt(),jets_pv[pt_num1].Eta(),jets_pv[pt_num1].Phi(),jets_pv[pt_num1].M());	
		Qjet2.SetPtEtaPhiM(jets_pv[pt_num2].Pt(),jets_pv[pt_num2].Eta(),jets_pv[pt_num2].Phi(),jets_pv[pt_num2].M());	
		int bjet_count=0;
		for(int i = 0; i < loopJet_max; i++){
			if (bjet_count==2) break;
			if ((btag_vec[i].first==pt_num1) ||(btag_vec[i].first==pt_num2)) continue;	
			if (bjet_count==0) btag_num1=btag_vec[i].first;
			if (bjet_count==1) btag_num2=btag_vec[i].first;
			bjet_count++;
		}
		Bjet1.SetPtEtaPhiM(jets_pv[btag_num1].Pt(),jets_pv[btag_num1].Eta(),jets_pv[btag_num1].Phi(),jets_pv[btag_num1].M());	
		Bjet2.SetPtEtaPhiM(jets_pv[btag_num2].Pt(),jets_pv[btag_num2].Eta(),jets_pv[btag_num2].Phi(),jets_pv[btag_num2].M());	
*/

/*
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

*/

/*	
//pt then btag
 	
		pt_num1=pt_vec[0].first;
		pt_num2=pt_vec[1].first;
		Qjet1.SetPtEtaPhiM(jets_pv[pt_num1].Pt(),jets_pv[pt_num1].Eta(),jets_pv[pt_num1].Phi(),jets_pv[pt_num1].M());	
		Qjet2.SetPtEtaPhiM(jets_pv[pt_num2].Pt(),jets_pv[pt_num2].Eta(),jets_pv[pt_num2].Phi(),jets_pv[pt_num2].M());	
		int bjet_count=0;
		for(int i = 0; i < loopJet_max; i++){
			if (bjet_count==2) break;
			if ((btag_vec[i].first==pt_num1) ||(btag_vec[i].first==pt_num2)) continue;	
			if (bjet_count==0) btag_num1=btag_vec[i].first;
			if (bjet_count==1) btag_num2=btag_vec[i].first;
			bjet_count++;
		}
	//	cout<<pt_num1<<"  "<<pt_num2<<"  "<<btag_num1<<"  "<<btag_num2<<endl;	
		Bjet1.SetPtEtaPhiM(jets_pv[btag_num1].Pt(),jets_pv[btag_num1].Eta(),jets_pv[btag_num1].Phi(),jets_pv[btag_num1].M());	
		Bjet2.SetPtEtaPhiM(jets_pv[btag_num2].Pt(),jets_pv[btag_num2].Eta(),jets_pv[btag_num2].Phi(),jets_pv[btag_num2].M());	
	
*/		

	Float_t bb_found = 0.;
	Float_t qq_found = 0.;
	float dR=0.8;
/*
	for(int j =0; j<2; j++){
		if(TMath::Abs(GenBQuarkFromH_pdgId[j])==5)
		{
			TLorentzVector hQ;
			hQ.SetPtEtaPhiM(GenBQuarkFromH_pt[j],GenBQuarkFromH_eta[j],GenBQuarkFromH_phi[j],GenBQuarkFromH_mass[j]);
			if(hQ.DeltaR(Bjet1)<dR || hQ.DeltaR(Bjet2)<dR) jet_isMatchedB++;
		}
	}
*/

	if (TMath::Abs(Jet_hadronFlavour[jets_indices[btag_num1]])==5) jet_isMatchedB++;	
	if (TMath::Abs(Jet_hadronFlavour[jets_indices[btag_num2]])==5) jet_isMatchedB++;	

	for(int j =0; j<2; j++){
		TLorentzVector hQ;
		hQ.SetPtEtaPhiM(GenHiggsSisters_pt[j],GenHiggsSisters_eta[j],GenHiggsSisters_phi[j],GenHiggsSisters_mass[j]);
		if((hQ.DeltaR(Qjet1)<dR)||(hQ.DeltaR(Qjet2)<dR))  jet_isMatchedQ++;
	}

	   for(int i=0; i<loopJet_max; i++){
		   TLorentzVector hJ0;
		   hJ0.SetPtEtaPhiM(jets_pv[i].Pt(),jets_pv[i].Eta(),jets_pv[i].Phi(),jets_pv[i].M());	
		   for(int j =0; j<2; j++){
			   if(TMath::Abs(GenBQuarkFromH_pdgId[j])==5){
            	TLorentzVector hQQ;
               hQQ.SetPtEtaPhiM(GenBQuarkFromH_pt[j],GenBQuarkFromH_eta[j],GenBQuarkFromH_phi[j],GenBQuarkFromH_mass[j]);
              	if(hQQ.DeltaR(hJ0)<dR) bb_found++;  
            } 
		   }
		   for(int j =0; j<2; j++){
				TLorentzVector hQ;
				hQ.SetPtEtaPhiM(GenHiggsSisters_pt[j],GenHiggsSisters_eta[j],GenHiggsSisters_phi[j],GenHiggsSisters_mass[j]);
				if(hQ.DeltaR(hJ0)<dR) qq_found++;
		   }
		 }



		if (jet_isMatchedB==2) bb_efficiency+=TMath::Sign(1.,genWeight);
		if (jet_isMatchedQ==2) qq_efficiency+=TMath::Sign(1.,genWeight);
		if (bb_found>=2) bb_efficiency_find+=TMath::Sign(1.,genWeight);
		if (qq_found>=2) qq_efficiency_find+=TMath::Sign(1.,genWeight);

		presel+=TMath::Sign(1.,genWeight);
	}  

	ofstream out("VBFHbb_jets_matching_"+region+"_dR08Try1Training_hadronFl_blike_pt.txt"); 
	out<<"bb efficiency to find b-jets = "<<bb_efficiency_find/presel<<endl;
	out<<"bb efficiency to match b-jets = "<<bb_efficiency/presel<<endl;
	out<<"qq efficiency to find q-jets = "<<qq_efficiency_find/presel<<endl;
	out<<"qq efficiency to match q-jets = "<<qq_efficiency/presel<<endl;
	out<<"presel = "<<presel<<endl;
	cout<<"bb efficiency to find b-jets = "<<bb_efficiency_find/presel<<endl;
	cout<<"bb efficiency to match b-jets = "<<bb_efficiency/presel<<endl;
	cout<<"qq efficiency to find q-jets = "<<qq_efficiency_find/presel<<endl;
	cout<<"qq efficiency to match q-jets = "<<qq_efficiency/presel<<endl;
	cout<<"presel = "<<presel<<endl;

}

   



	
