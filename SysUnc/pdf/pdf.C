#include <iostream>
#include <fstream>
#include <algorithm>
#include <TH1F.h>
#include <TTree.h>
#include <TStyle.h>
#include <TCanvas.h>
#include "TLorentzVector.h"
#include <iomanip>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "TFile.h"
#include "TROOT.h"
#include "TLatex.h"
#include "TLegend.h"
#include "TPaveText.h"

using namespace std;

//int bTagWeight_unc(int type_int, int type_unc_int){
int main(int argc, char* argv[]){
	gROOT->ProcessLine(".x /afs/cern.ch/work/n/nchernya/setTDRStyle.C");
	int type_int = atoi(argv[1]);
	int sig_num = atoi(argv[2]);   //0 -vbf , 1 - gf

//	int type_int; //double  =0; single=1
	
	TString type_unc = "pdf";
	TString up_str = "Up";
	TString down_str = "Down";
	string type;
	if (type_int==0) type = "double";
	if (type_int==1) type = "single";
	TString text_type;
	if (type_int==0) text_type = "DoubleB";
	if (type_int==1) text_type = "SingleB";

	int NCATS;
	Float_t cats[10]; 
	Float_t Nevt_up[10];
	Float_t Nevt_nom[10];
	Float_t Nevt_nom_er[10];
	Float_t Nevt_down[10];
	Float_t SysUnc[10];
	TString cats_names[10];
	if (type_int==0) NCATS=3+1;
	else if (type_int==1) NCATS=4+1;
	if (type_int==1) {
		Float_t cats_new[10]={-1.,  0.0775 ,  0.5775 ,  0.7775  , 0.8775,1.};
		memcpy(cats, cats_new, sizeof cats_new);
	}
	if (type_int==0) {
		Float_t cats_new[10]={-1., 0.0875 ,  0.5775 ,  0.7875,1.};
		memcpy(cats, cats_new, sizeof cats_new);
	}
	for (int i=0;i<NCATS;i++){
		TString tmp;
		tmp.Form("%1d",i);
		cats_names[i] = "CAT";
		cats_names[i].Append(tmp);
	} 
//		Float_t cats[10] = {-1.,0.12,0.44,0.57,0.6725};

	Float_t lumi = 35900.;
	Float_t xsec[10] =  {2.20, 25.69};

	const int num_ss = 2;	

	TString s_names[num_ss] = {"VBFHbb","ggHbb"};
		


	TCanvas *c0 = new TCanvas();
	TFile *file_nom =  TFile::Open("dcap://t3se01.psi.ch:22125//pnfs/psi.ch/cms/trivcat/store/user/nchernya/VBFHbb2016/v25_VBF_mva_JESR_full/"+type+"VBFMvaJESR_v25_weights_new"+s_names[sig_num]+".root");
	TH1F*	countPos = (TH1F*)file_nom->Get("CountPosWeight");
 	TH1F*		countNeg = (TH1F*)file_nom->Get("CountNegWeight");
 	TH1F*		countWeighted = (TH1F*)file_nom->Get("CountWeighted");
 	TH1F *countLHEScale = (TH1F*)file_nom->Get("CountWeightedLHEWeightScale");
 	TH1F *countLHEpdf = (TH1F*)file_nom->Get("CountWeightedLHEWeightPdf");
	float events_generated_nom = countWeighted->GetBinContent(1);
	float events_generated_up = countLHEScale->GetBinContent( countLHEScale->FindBin( 4) );
	float events_generated_down = countLHEScale->GetBinContent( countLHEScale->FindBin( 5) );
	if (events_generated_nom==0) events_generated_nom =  countPos->GetBinContent(1) - countNeg->GetBinContent(1);

	float scale; float scale_down; float scale_up;

	TTree *tree_bdt_JEnom = (TTree*)file_nom->Get("tree");

TH1F *hist_acceptance[10];
float mean_acceptance[10];

if ((sig_num==0)&&(type_int==0)) {
		Float_t mean_acceptance_new[10]={293.42004	,352.87640,	221.94957,	104.09509 };
		memcpy(mean_acceptance, mean_acceptance_new, sizeof mean_acceptance_new);
	}
	if ((sig_num==1)&&(type_int==0)) {
		Float_t mean_acceptance_new[10]={803.73383,	321.67499,	95.81062,	21.09702 };
		memcpy(mean_acceptance, mean_acceptance_new, sizeof mean_acceptance_new);
	}
	if ((sig_num==0)&&(type_int==1)) {
		Float_t mean_acceptance_new[10]={305.0750, 384.49579, 280.74670,	203.55603,	151.15797};
		memcpy(mean_acceptance, mean_acceptance_new, sizeof mean_acceptance_new);
	}
	if ((sig_num==1)&&(type_int==1)) {
		Float_t mean_acceptance_new[10]={184.86885,	117.67667,	47.25767,	21.40868,	7.91522 };
		memcpy(mean_acceptance, mean_acceptance_new, sizeof mean_acceptance_new);
	}




for (int i=0;i<NCATS;i++){
	TString tmp;
	hist_acceptance[i] = new TH1F("acceptance_cat"+tmp.Format("%d",i),"",60,mean_acceptance[i]*0.85,mean_acceptance[i]*1.15);
	hist_acceptance[i]->GetXaxis()->SetTitle("acceptance in CAT"+tmp.Format("%d",i));
}



for (int pdf_counter=-1;pdf_counter<100;pdf_counter++){
	TH1F *hist_bdt_JEnom= new TH1F("hist_bdt_nom","",NCATS,cats);
	hist_bdt_JEnom->GetXaxis()->SetTitle("BDT output");
	char cmd[500];
	char cmd2[500];
	char cmd3[500];
	sprintf(cmd,"\%s\%s>>\%s",(type.c_str()),("VBF_bdt"),("hist_bdt_nom"));	
	sprintf(cmd2,"((\%sPassSelection_nom==1) && ((Vtype==-1)||(Vtype>3)))*(\%strigWeight_nom*puWeight*\%sQGLweight*TMath::Abs(genWeight)/genWeight*LHE_weights_pdf_wgt[%d])",(type.c_str()),(type.c_str()),(type.c_str()),pdf_counter);	
	tree_bdt_JEnom->Draw(cmd,cmd2);

	if (pdf_counter!=-1)scale=lumi*xsec[sig_num]/countLHEpdf->GetBinContent( countLHEpdf->FindBin(pdf_counter));
	else scale=lumi*xsec[sig_num]/events_generated_nom;

	hist_bdt_JEnom->Scale(scale);

	for (int i=0;i<NCATS;i++){
		Nevt_nom[i] = hist_bdt_JEnom->GetBinContent(i+1);
		Nevt_nom_er[i] = hist_bdt_JEnom->GetBinError(i+1);
		hist_acceptance[i]->Fill(Nevt_nom[i]);
	}
}
	

TFile file("output/"+s_names[sig_num]+"_"+type+"_pdf_unc.root","recreate");
file.cd();
		for (int i=0;i<NCATS;++i){
    	    	hist_acceptance[i]->SetLineWidth(2);
    	   	hist_acceptance[i]->GetYaxis()->SetTitle("N_{events}");
       		hist_acceptance[i]->GetYaxis()->SetTitleFont(42);
       		hist_acceptance[i]->GetYaxis()->SetTitleSize(0.060);
        		hist_acceptance[i]->GetYaxis()->SetTitleOffset(0.8);
        		hist_acceptance[i]->SetLineColor(kBlue);
        		hist_acceptance[i]->Draw();
        		hist_acceptance[i]->Write();
   		}

file.Close();

	return 0;
}

