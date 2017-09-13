#define skim_trees_macro_vbfhbb_triggers_cxx
#include "skim_trees_macro_vbfhbb_triggers.h"
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


struct sort_pred {
    bool operator()(const std::pair<int,float> &left, const std::pair<int,float> &right) {
        return left.second > right.second;
    }
};


void skim_trees_macro_vbfhbb_triggers::Loop(TString filename)
{
   if (fChain == 0) return;

   Long64_t nentries = fChain->GetEntries();
	std::cout<<nentries<<endl;

   Long64_t nbytes = 0, nb = 0;



	fChain->SetBranchStatus("*",0);



	fChain->SetBranchStatus("nJet",1);
   fChain->SetBranchStatus("genWeight",1.);
	fChain->SetBranchStatus("nPU0",1);
	fChain->SetBranchStatus("nPVs",1);
	fChain->SetBranchStatus("isData",1);
   fChain->SetBranchStatus("puWeight*",1.);
	fChain->SetBranchStatus("xsec",1);
   fChain->SetBranchStatus("evt*",1.);
   fChain->SetBranchStatus("run*",1.);
   fChain->SetBranchStatus("lumi",1.);
   fChain->SetBranchStatus("Vtype",1.);
   fChain->SetBranchStatus("VtypeSim",1.);
   fChain->SetBranchStatus("Jet_pt",1.);
   fChain->SetBranchStatus("Jet_eta",1.);
   fChain->SetBranchStatus("Jet_phi",1.);
	fChain->SetBranchStatus("Jet_mass",1.);
	fChain->SetBranchStatus("Jet_btagCSV*",1.);
	fChain->SetBranchStatus("Jet_btagCMVA*",1.);
	fChain->SetBranchStatus("Jet_btagWeightCMVAV2",1.);
	fChain->SetBranchStatus("Jet_hadronFlavour",1.);
	fChain->SetBranchStatus("Jet_id",1.);
	fChain->SetBranchStatus("Jet_puId",1.);
	fChain->SetBranchStatus("json",1.);


   fChain->SetBranchStatus("*HLT_QuadPFJet_VBF_v*",1.);
   fChain->SetBranchStatus("*HLT_DiPFJetAve*",1.);
 	fChain->SetBranchStatus("*HLT_PFJet*",1.);
   fChain->SetBranchStatus("*HLT_L1_TripleJet_VBF_v*",1.);
	fChain->SetBranchStatus("*HLT_QuadPFJet_BTagCSV_p016_p11_VBF_Mqq240_v*",1.);
   fChain->SetBranchStatus("*HLT_QuadPFJet_BTagCSV_p016_p11_VBF_Mqq200_v*",1.);
   fChain->SetBranchStatus("*HLT_QuadPFJet_BTagCSV_p016_VBF_Mqq500_v*",1.);
   fChain->SetBranchStatus("*HLT_QuadPFJet_BTagCSV_p016_VBF_Mqq460_v*",1.);



		//or of 

/////////////////////////////////////////


	std::cout<<filename<<endl;
	TFile *output = TFile::Open(filename,"recreate");
	TTree *tree = fChain->CloneTree(0);
	
	Float_t looser_cuts_coef = 0.9;	

   for (Long64_t jentry=0; jentry<nentries;jentry++) {
	   Long64_t ientry = LoadTree(jentry);
	 //  if (ientry < 0) break;
	   nb = fChain->GetEntry(jentry);   nbytes += nb;

	if (nJet<4) continue;
	//	if (! ( (HLT_BIT_HLT_DiPFJetAve40_v==1) || (HLT_BIT_HLT_DiPFJetAve60_v==1) || (HLT_BIT_HLT_DiPFJetAve80_v==1)  ||  (HLT_BIT_HLT_PFJet40_v==1) || (HLT_BIT_HLT_PFJet60_v==1)  || (HLT_BIT_HLT_PFJet80_v==1) ||  (HLT_BIT_HLT_QuadPFJet_VBF_v==1))  ) continue;
		if (! (   HLT_BIT_HLT_QuadPFJet_VBF_v==1)  ) continue;

		vector<TLorentzVector> jets_pv;
		int good_jets=0;
		for (int i=0;i<nJet;i++){
			TLorentzVector jet0;
			if (!((Jet_id[i]>2)&&(Jet_puId[i]>0))) continue;
			jet0.SetPtEtaPhiM(Jet_pt[i],Jet_eta[i],Jet_phi[i],Jet_mass[i]);
			jets_pv.push_back(jet0);
			good_jets++;
		}
		if (good_jets<4) continue;




//jetHT and QCD and signal

//////////////////////////////////////////////////////

		tree->Fill();		

	}  
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
	delete output;
	
}

