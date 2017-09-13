#define skim_trees_macro_vbfhbb_cxx
#include "skim_trees_macro_vbfhbb.h"
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


void skim_trees_macro_vbfhbb::Loop(TString filename)
{
   if (fChain == 0) return;

   Long64_t nentries = fChain->GetEntries();
	std::cout<<nentries<<endl;

   Long64_t nbytes = 0, nb = 0;



	fChain->SetBranchStatus("*",0);



	fChain->SetBranchStatus("nJet",1);
   fChain->SetBranchStatus("genWeight",1.);
	fChain->SetBranchStatus("nTrueInt",1);
	fChain->SetBranchStatus("nPU0",1);
	fChain->SetBranchStatus("nPVs",1);
	fChain->SetBranchStatus("isData",1);
	fChain->SetBranchStatus("xsec",1);
   fChain->SetBranchStatus("Jet_pt",1.);
   fChain->SetBranchStatus("Jet_mt",1.);
   fChain->SetBranchStatus("Jet_eta",1.);
   fChain->SetBranchStatus("Jet_phi",1.);
	fChain->SetBranchStatus("Jet_mass",1.);
	fChain->SetBranchStatus("Jet_btagCSV*",1.);
	fChain->SetBranchStatus("Jet_btagCMVA*",1.);
	fChain->SetBranchStatus("Jet_btagCmva*",1.);
	fChain->SetBranchStatus("Jet_blike_VBF",1.);
	fChain->SetBranchStatus("Jet_id",1.);
	fChain->SetBranchStatus("Jet_puId",1.);
   fChain->SetBranchStatus("Jet_qgl",1.);
	fChain->SetBranchStatus("json",1.);
	fChain->SetBranchStatus("EX_MUON",1.);

// 	fChain->SetBranchStatus("HLT_BIT_HLT_QuadPFJet_BTagCSV_p016_p11_VBF_Mqq200_*",1.);
// 	fChain->SetBranchStatus("HLT_BIT_HLT_QuadPFJet_BTagCSV_p016_VBF_Mqq460_*",1.);
// 	fChain->SetBranchStatus("HLT_BIT_HLT_QuadJet45_DoubleBTagCSV_p087_v*",1.);

		  fChain->SetBranchStatus("*HLT_QuadPFJet_BTagCSV_p016_p11_VBF_Mqq240_v*",1.);
        fChain->SetBranchStatus("*HLT_QuadPFJet_BTagCSV_p016_p11_VBF_Mqq200_v*",1.);
        fChain->SetBranchStatus("*HLT_QuadPFJet_BTagCSV_p016_VBF_Mqq500_v*",1.);
        fChain->SetBranchStatus("*HLT_QuadPFJet_BTagCSV_p016_VBF_Mqq460_v*",1.);
        fChain->SetBranchStatus("*HLT_QuadPFJet_VBF_v*",1.);
        fChain->SetBranchStatus("*HLT_L1_TripleJet_VBF_v*",1.);
        fChain->SetBranchStatus("*HLT_PFHT650_WideJetMJJ900DEtaJJ1p5_v*",1.);
        fChain->SetBranchStatus("*HLT_PFHT650_WideJetMJJ950DEtaJJ1p5_v*",1.);
 	     fChain->SetBranchStatus("*HLT_DiPFJetAve*",1.);
 	     fChain->SetBranchStatus("*HLT_PFJet*",1.);
        fChain->SetBranchStatus("*HLT_DoubleJetsC100_DoubleBTagCSV_p026_DoublePFJetsC160_v*",1.);
        fChain->SetBranchStatus("*HLT_DoubleJetsC100_DoubleBTagCSV_p014_DoublePFJetsC100MaxDeta1p6_v*",1.);


/*	fChain->SetBranchStatus("HLT_BIT_HLT_IsoMu22*",1.);
	fChain->SetBranchStatus("HLT_BIT_HLT_IsoMu22_eta2p1*",1.);
	fChain->SetBranchStatus("HLT_BIT_HLT_IsoTkMu22*",1.);
	fChain->SetBranchStatus("HLT_BIT_HLT_IsoMu24*",1.);
	fChain->SetBranchStatus("HLT_BIT_HLT_IsoTkMu24*",1.);
	fChain->SetBranchStatus("HLT_BIT_HLT_IsoMu27*",1.);
	fChain->SetBranchStatus("HLT_BIT_HLT_IsoTkMu27*",1.);
	fChain->SetBranchStatus("HLT_BIT_HLT_Mu24_eta2p1*",1.);
	fChain->SetBranchStatus("HLT_BIT_HLT_TkMu24_eta2p1*",1.);
	fChain->SetBranchStatus("HLT_BIT_HLT_Ele27_eta2p1_WPLoose_Gsf*",1.);
	fChain->SetBranchStatus("HLT_BIT_HLT_Ele27_eta2p1_WPTight_Gsf_v*",1.);
 	fChain->SetBranchStatus("HLT_BIT_HLT_Ele27_WPLoose_Gsf_v*",1);
 	fChain->SetBranchStatus("HLT_BIT_HLT_Ele25*",1);
 	fChain->SetBranchStatus("HLT_BIT_HLT_Ele27*",1);
 	fChain->SetBranchStatus("HLT_BIT_HLT_*Ele*Ele*",1);
 	fChain->SetBranchStatus("HLT_BIT_HLT_DoubleEle*",1);
 	fChain->SetBranchStatus("HLT_BIT_HLT_*Mu*Mu*",1);*/


///////////////////for normal workflow////////////////not trigger////
   //fChain->SetBranchStatus("*",1.);

	fChain->SetBranchStatus("V_*",1.);
	fChain->SetBranchStatus("nGenVbosons",1.);
	fChain->SetBranchStatus("GenVbosons_pt",1.);
	fChain->SetBranchStatus("GenVbosons_eta",1.);
	fChain->SetBranchStatus("GenVbosons_phi",1.);
	fChain->SetBranchStatus("GenVbosons_mass",1.);
	fChain->SetBranchStatus("GenVbosons_pdgId",1.);
	fChain->SetBranchStatus("*vLeptons*",1.);
	fChain->SetBranchStatus("*selLeptons*",1.);
//	fChain->SetBranchStatus("*vLeptons*",1.);
//	fChain->SetBranchStatus("selLeptons_pdgId",1.);
//	fChain->SetBranchStatus("selLeptons_charge",1.);
 //  fChain->SetBranchStatus("selLeptons_tightId",1.);
  // fChain->SetBranchStatus("selLeptons_relIso03",1.);
//   fChain->SetBranchStatus("selLeptons_chargedHadRelIso0",1.);
 //  fChain->SetBranchStatus("selLeptons_pfRelIso03",1.);
//   fChain->SetBranchStatus("vLeptons_dz",1.);
//   fChain->SetBranchStatus("vLeptons_ed",1.);
   fChain->SetBranchStatus("nGenHiggsSisters",1.);
   fChain->SetBranchStatus("*GenHiggsSisters*",1.);
   fChain->SetBranchStatus("*GenHiggsBoson*",1.);
//   fChain->SetBranchStatus("GenHiggsSisters_pdgId",1.);
 //  fChain->SetBranchStatus("GenHiggsSisters_pt",1.);
  /// fChain->SetBranchStatus("GenHiggsSisters_eta",1.);
//   fChain->SetBranchStatus("GenHiggsSisters_phi",1.);
 //  fChain->SetBranchStatus("GenHiggsSisters_mass",1.);
//   fChain->SetBranchStatus("GenHiggsSisters_charge",1.);
   fChain->SetBranchStatus("Jet_corr*",1.);
   fChain->SetBranchStatus("Jet_leadTrackPt",1.);
   fChain->SetBranchStatus("Jet_leptonPtRel",1.);
   fChain->SetBranchStatus("Jet_leptonPt",1.);
   fChain->SetBranchStatus("Jet_leptonDeltaR",1.);
   fChain->SetBranchStatus("Jet_neHEF",1.);
   fChain->SetBranchStatus("Jet_neEmEF",1.);
   fChain->SetBranchStatus("Jet_vtxPt",1.);
   fChain->SetBranchStatus("Jet_vtxMass",1.);
   fChain->SetBranchStatus("Jet_vtx3DVal",1.);
   fChain->SetBranchStatus("Jet_vtxNtracks",1.);
   fChain->SetBranchStatus("Jet_vtx3DSig",1.);
   fChain->SetBranchStatus("Jet_pt*",1.);
   fChain->SetBranchStatus("btagWeight*",1.);
   fChain->SetBranchStatus("Jet_ptd",1.);
   fChain->SetBranchStatus("Jet_axis2",1.);
   fChain->SetBranchStatus("Jet_btagWeight*",1.);
   fChain->SetBranchStatus("Jet_mult",1.);
   fChain->SetBranchStatus("met_pt",1.);
   fChain->SetBranchStatus("met_phi",1.);
   fChain->SetBranchStatus("met_sumEt",1.);
   fChain->SetBranchStatus("met_shifted_JetEnUp_pt",1.);
   fChain->SetBranchStatus("met_shifted_JetEnDown_pt",1.);
   fChain->SetBranchStatus("*softActivity*",1.);
   fChain->SetBranchStatus("lumi",1.);
   fChain->SetBranchStatus("xsec",1.);
   fChain->SetBranchStatus("evt*",1.);
   fChain->SetBranchStatus("run*",1.);
   fChain->SetBranchStatus("puWeight*",1.);
   fChain->SetBranchStatus("json_silver",1.);
   fChain->SetBranchStatus("Vtype",1.);
   fChain->SetBranchStatus("VtypeSim",1.);
	fChain->SetBranchStatus("rho*",1.);
	fChain->SetBranchStatus("*GenBQuarkFromH*",1.);
//	fChain->SetBranchStatus("GenBQuarkFromH_pdgId",1.);
//	fChain->SetBranchStatus("GenBQuarkFromH_pt",1.);
//	fChain->SetBranchStatus("GenBQuarkFromH_phi",1.);
//	fChain->SetBranchStatus("GenBQuarkFromH_eta",1.);
//	fChain->SetBranchStatus("GenBQuarkFromH_mass",1.);
//	fChain->SetBranchStatus("GenBQuarkFromH_charge",1.);
//	fChain->SetBranchStatus("GenBQuarkFromHafterISR_pdgId",1.);
//	fChain->SetBranchStatus("GenBQuarkFromHafterISR_pt",1.);
//	fChain->SetBranchStatus("GenBQuarkFromHafterISR_phi",1.);
//	fChain->SetBranchStatus("GenBQuarkFromHafterISR_eta",1.);
//	fChain->SetBranchStatus("GenBQuarkFromHafterISR_mass",1.);
//	fChain->SetBranchStatus("GenBQuarkFromHafterISR_charge",1.);
	fChain->SetBranchStatus("nGenBQuarkFromH",1.);
	fChain->SetBranchStatus("nGenBQuarkFromHafterISR",1.);
	fChain->SetBranchStatus("Jet_*Flavour",1.);
	fChain->SetBranchStatus("Jet_mcMatchId",1.);
	fChain->SetBranchStatus("Jet_mc*",1.);
	fChain->SetBranchStatus("Jet_rawPt",1.);
	fChain->SetBranchStatus("LHE*",1.);
	fChain->SetBranchStatus("lhe*",1.);
	fChain->SetBranchStatus("nlhe*",1.);
	fChain->SetBranchStatus("nLHE*",1.);
//	fChain->SetBranchStatus("*trgObjects*",1);
//	fChain->SetBranchStatus(,1.);



/////////////////////////SingleElectron part///////////////////
/*
	fChain->SetBranchStatus("*",0);
	fChain->SetBranchStatus("nTrueInt",1);
	fChain->SetBranchStatus("nPU0",1);
	fChain->SetBranchStatus("isData",1);
	fChain->SetBranchStatus("xsec",1);
	fChain->SetBranchStatus("nJet",1);
	fChain->SetBranchStatus("Jet_pt",1);
	fChain->SetBranchStatus("Jet_pt*",1);
	fChain->SetBranchStatus("Jet_eta",1);
	fChain->SetBranchStatus("Jet_phi",1);
	fChain->SetBranchStatus("Jet_mass",1);
	fChain->SetBranchStatus("Jet_btagCSV",1);
	fChain->SetBranchStatus("Jet_id",1);
	fChain->SetBranchStatus("Jet_*",1);
	fChain->SetBranchStatus("met*",1);
	fChain->SetBranchStatus("nPVs",1);
   fChain->SetBranchStatus("*eight*",1);
   fChain->SetBranchStatus("*json*",1);
	 fChain->SetBranchStatus("HLT_*Mu*",1);
    fChain->SetBranchStatus("HLT_*Ele*",1);
    fChain->SetBranchStatus("HLT_*VBF*",1);
    fChain->SetBranchStatus("HLT_*Jet*",1);
	fChain->SetBranchStatus("*type",1);
	fChain->SetBranchStatus("*blike*",1);
	fChain->SetBranchStatus("*qgl*",1);
	fChain->SetBranchStatus("soft*",1);
	fChain->SetBranchStatus("GenHiggs*",1);
	fChain->SetBranchStatus("selLeptons*",1);

*/

/////////////////////////////////////////


	std::cout<<filename<<endl;
	TFile *output = TFile::Open(filename,"recreate");
	TTree *tree = fChain->CloneTree(0);
		//all fo histograms should be declared in the begining (members of skim_trees_macro_vbfhbb) where fChain is
		//when you initialize Init you do this (below) 
/*		//and in AddFile you grab them and hist1.Add(hist2)
	TFile *input_file = TFile::Open(input_filename);
	TH1F*	Count = (TH1F*)input_file->Get("Count");
	TH1F*	CountPosWeight = (TH1F*)input_file->Get("CountPosWeight");
	TH1F*	CountNegWeight =(TH1F*)input_file->Get("CountNegWeight");
	TH1F*	CountWeighted =(TH1F*)input_file->Get("CountWeighted");
	TH1F* CountFullWeighted  = (TH1F*)input_file->Get("CountFullWeighted");
	TH1F* CountWeightedLHEWeightScale  = (TH1F*)input_file->Get("CountWeightedLHEWeightScale");
	TH1F* CountWeightedLHEWeightPdf  = (TH1F*)input_file->Get("CountWeightedLHEWeightPdf");
*/
	
	Float_t looser_cuts_coef = 0.9;	

//	cout<< "I am here once"<<endl;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
	   Long64_t ientry = LoadTree(jentry);
	 //  if (ientry < 0) break;
	   nb = fChain->GetEntry(jentry);   nbytes += nb;

//		int btag_max1_number = -1;
//		int btag_max2_number = -1;
//		int pt_max1_number = -1;
//		int pt_max2_number = -1;
//		TLorentzVector Bjet1;
//		TLorentzVector Bjet2;
//		TLorentzVector Qjet1;
//		TLorentzVector Qjet2;
//		TLorentzVector qq;
	
//		if (preselection_single(nJet, Jet_pt,Jet_eta, Jet_phi, Jet_mass, Jet_btagCSV, Jet_id, btag_max1_number, btag_max2_number, pt_max1_number, pt_max2_number, /*HLT_BIT_HLT_QuadPFJet_SingleBTagCSV_VBF_Mqq460_v*/1., Bjet1, Bjet2, Qjet1, Qjet2, qq, looser_cuts_coef) !=0) continue;
	

//that one
//	if (preselection_single_blike(nJet, Jet_pt,Jet_eta, Jet_phi, Jet_mass, Jet_blike_VBF, Jet_id, btag_max1_number, btag_max2_number, pt_max1_number, pt_max2_number, /*HLT_BIT_HLT_QuadPFJet_SingleBTagCSV_VBF_Mqq460_v*/1., Bjet1, Bjet2, Qjet1, Qjet2, qq, looser_cuts_coef) !=0) continue;
	

//	if (!((HLT_BIT_HLT_QuadPFJet_SingleBTagCSV_VBF_Mqq460_v==1) || (HLT_BIT_HLT_QuadPFJet_DoubleBTagCSV_VBF_Mqq200_v==1))) continue; 
//	if (!( (Jet_pt[0] > 82.) && (Jet_pt[1] > 66.) && (Jet_pt[2] > 54.)  && (Jet_pt[3] > 20.))) continue;
	
//	if (nJet<4) continue;
//	if (!((HLT_BIT_HLT_QuadPFJet_VBF_v==1) || (HLT_BIT_HLT_DiPFJetAve60_v==1) || (HLT_BIT_HLT_DiPFJetAve40_v==1))) continue; 
//	if (HLT_BIT_HLT_QuadPFJet_VBF_v!=1) continue;

		//if (preselection_double(nJet, Jet_pt,Jet_eta, Jet_phi, Jet_mass, Jet_btagCSV, Jet_id, btag_max1_number, btag_max2_number, pt_max1_number, pt_max2_number, /*HLT_BIT_HLT_QuadPFJet_DoubleBTagCSV_VBF_Mqq200_v*/1., Bjet1, Bjet2, Qjet1, Qjet2, qq, looser_cuts_coef) !=0) continue;
		//
		
//		if (Jet_pt[0]< 80) continue;
//		if (Jet_pt[1]< 60) continue;
//		if (Jet_pt[2]< 40) continue;
//		if (Jet_pt[3]< 10) continue;
//		if	(HLT_BIT_HLT_QuadPFJet_DoubleBTagCSV_VBF_Mqq200_v!=1) continue;
//		if (nJet<4) continue;


////////////////////////VBF Hbb 2016 data//////////////////////////////


		
		vector<TLorentzVector> jets_pv;
		TLorentzVector Qjet1;
		TLorentzVector Qjet2;
		TLorentzVector Bjet1;
		TLorentzVector Bjet2;
		vector<pair<int, float> > btag_vec;	
		vector<pair<int, float> > pt_vec;	
		pair<int,float> aPair;
		vector<int> jets_indices;
		int good_jets=0;
		int pt_num1 = -1;
		int pt_num2 = -1;
		int btag_num1 = -1;
		int btag_num2 = -1;

	
	if (!((HLT_BIT_HLT_QuadPFJet_BTagCSV_p016_p11_VBF_Mqq200_v==1) || (HLT_BIT_HLT_QuadPFJet_BTagCSV_p016_p11_VBF_Mqq240_v==1) || (HLT_BIT_HLT_QuadPFJet_BTagCSV_p016_VBF_Mqq460_v==1) || (HLT_BIT_HLT_QuadPFJet_BTagCSV_p016_VBF_Mqq500_v==1) )) continue; 

		for (int i=0;i<nJet;i++){
			TLorentzVector jet0;
			if (!((Jet_id[i]>2)&&(Jet_puId[i]>0))) continue;
			jet0.SetPtEtaPhiM(Jet_pt[i],Jet_eta[i],Jet_phi[i],Jet_mass[i]);
			jets_pv.push_back(jet0);
			jets_indices.push_back(i);
			aPair.first = good_jets;
			aPair.second = Jet_btagCMVA[i];
			if ((Jet_btagCMVA[i]>-0.853213) &&(Jet_btagCMVA[i]<-0.853211)) aPair.second=-10;
			btag_vec.push_back(aPair);
			aPair.first = good_jets;
			aPair.second = Jet_pt[i];
			pt_vec.push_back(aPair);
			good_jets++;
		}
		if (good_jets<4) continue;
		if (jets_pv[0].Pt()<82) continue;
		if (jets_pv[1].Pt()<66) continue;
		if (jets_pv[2].Pt()<54) continue;
		if (jets_pv[3].Pt()<20) continue;

		int max_loop = std::min(good_jets,10);
		float max_mjj=-1;
		for (int i=0;i<max_loop-1;i++){
			for (int j=i+1;j<max_loop;j++){
				float inv = (jets_pv[i]+jets_pv[j]).M();
				if (inv > max_mjj)  max_mjj =  inv;
			}
		}

		if ((HLT_BIT_HLT_QuadPFJet_BTagCSV_p016_VBF_Mqq460_v==1) || (HLT_BIT_HLT_QuadPFJet_BTagCSV_p016_VBF_Mqq500_v==1)){
			if (max_mjj < 430) continue;
		} else {

			////sort btag_vec and pt_vec
			
		std::sort(btag_vec.begin(), btag_vec.begin()+max_loop,sort_pred() );
		std::sort(pt_vec.begin(), pt_vec.begin()+max_loop,sort_pred() );

		btag_num1=btag_vec[0].first;
		btag_num2=btag_vec[1].first;
		Bjet1.SetPtEtaPhiM(jets_pv[btag_num1].Pt(),jets_pv[btag_num1].Eta(),jets_pv[btag_num1].Phi(),jets_pv[btag_num1].M());	
		Bjet2.SetPtEtaPhiM(jets_pv[btag_num2].Pt(),jets_pv[btag_num2].Eta(),jets_pv[btag_num2].Phi(),jets_pv[btag_num2].M());	
		int qjet_count=0;
		for(int i = 0; i < max_loop; i++){
			if (qjet_count==2) break;
			if ((pt_vec[i].first==btag_num1) || (pt_vec[i].first==btag_num2)) continue;	
			if (qjet_count==0) pt_num1=pt_vec[i].first;
			if (qjet_count==1) pt_num2=pt_vec[i].first;
			qjet_count++;
		}
		Qjet1.SetPtEtaPhiM(jets_pv[pt_num1].Pt(),jets_pv[pt_num1].Eta(),jets_pv[pt_num1].Phi(),jets_pv[pt_num1].M());	
		Qjet2.SetPtEtaPhiM(jets_pv[pt_num2].Pt(),jets_pv[pt_num2].Eta(),jets_pv[pt_num2].Phi(),jets_pv[pt_num2].M());	


		if ((HLT_BIT_HLT_QuadPFJet_BTagCSV_p016_p11_VBF_Mqq200_v==1) || (HLT_BIT_HLT_QuadPFJet_BTagCSV_p016_p11_VBF_Mqq240_v==1)) {
			float detaqq=TMath::Abs(Qjet1.Eta()-Qjet2.Eta());
			float dphibb=TMath::Abs(Bjet1.Phi()-Bjet2.Phi());
			if (! ( (detaqq>2.3) && (dphibb<2.1) && ((Qjet1+Qjet2).M()>216))) continue;
		}
	}

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

