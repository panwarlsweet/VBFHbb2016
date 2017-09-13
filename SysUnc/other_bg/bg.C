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
	
//	TString type_unc = "puWeight";
	TString type_unc = "UEPS";
//	TString type_unc = "QCDScale";
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

	const int num_ss = 10;	

	TString s_names[num_ss] = {"bbH_yb2","bbH_ybyt","ttHbb","ttHnonbb","WminusHbb_powheg","WplusHbb_powheg","ZHbb_powheg","WW","ZZ","WZ"};
	Float_t xsec[10] =  {		0.3104 ,		-0.0262	, .295  , .2117,     1.940120e-01,      3.057600e-01,    3.093083e-01,  118.7, 16.523, 47.13		};
		


	TCanvas *c0 = new TCanvas();
	TFile *file_nom =  TFile::Open("dcap://t3se01.psi.ch:22125//pnfs/psi.ch/cms/trivcat/store/user/nchernya/VBFHbb2016/v25_VBF_mva_JESR_full/"+type+"VBFMvaJESR_v25_weights_new"+s_names[sig_num]+".root");
	TH1F*	countPos = (TH1F*)file_nom->Get("CountPosWeight");
 	TH1F*		countNeg = (TH1F*)file_nom->Get("CountNegWeight");
 	TH1F*		countWeighted = (TH1F*)file_nom->Get("CountWeighted");
 	TH1F *countLHEScale = (TH1F*)file_nom->Get("CountWeightedLHEWeightScale");
	float events_generated_nom = countWeighted->GetBinContent(1);
	float events_generated_up = countLHEScale->GetBinContent( countLHEScale->FindBin( 4) );
	float events_generated_down = countLHEScale->GetBinContent( countLHEScale->FindBin( 5) );
	if (events_generated_nom==0) events_generated_nom =  countPos->GetBinContent(1) - countNeg->GetBinContent(1);

	float scale; float scale_down; float scale_up;
	scale=lumi*xsec[sig_num]/events_generated_nom;
	scale_down=lumi*xsec[sig_num]/events_generated_down;
	scale_up=lumi*xsec[sig_num]/events_generated_up;
	TTree *tree_bdt_JEnom = (TTree*)file_nom->Get("tree");
	TH1F *hist_bdt_JEnom= new TH1F("hist_bdt_nom","",NCATS,cats);
	hist_bdt_JEnom->GetXaxis()->SetTitle("BDT output");
	TH1F *hist_mbb_JEnom= new TH1F("hist_mbb_nom","",60,50,200);
	hist_mbb_JEnom->GetXaxis()->SetTitle("m_{bb} (GeV)");
	char cmd[500];
	char cmd2[500];
	char cmd3[500];
	sprintf(cmd,"\%s\%s>>\%s",(type.c_str()),("VBF_bdt"),("hist_bdt_nom"));	
//	sprintf(cmd3,"\%s\%s >>\%s",(type),("Mbb"),("hist_mbb_nom"));	
//	sprintf(cmd2,"(\%sPassSelection_nom==1)*(\%strigWeight_nom*puWeight*Jet_btagWeightCMVAV2[\%sbtag_num1]*Jet_btagWeightCMVAV2[\%sbtag_num2]*\%sQGLweight)",(type.c_str()),(type.c_str()),(type.c_str()),(type.c_str()),(type.c_str()));	
//	sprintf(cmd2,"((\%sPassSelection_nom==1) && ((Vtype==-1)||(Vtype>3)))*(\%strigWeight_nom*puWeight*Jet_btagWeightCMVAV2[\%sbtag_num1]*Jet_btagWeightCMVAV2[\%sbtag_num2]*\%sQGLweight*TMath::Abs(genWeight)/genWeight)",(type.c_str()),(type.c_str()),(type.c_str()),(type.c_str()),(type.c_str()));	
	sprintf(cmd2,"((\%sPassSelection_nom==1) && ((Vtype==-1)||(Vtype>3)))*(\%strigWeight_nom*puWeight*TMath::Abs(genWeight)/genWeight)",(type.c_str()),(type.c_str()));	
//	sprintf(cmd2,"(\%sPassSelection_nom==1)*(\%strigWeight_nom*puWeight*\%sQGLweight)",(type.c_str()),(type.c_str()),(type.c_str()));	
	tree_bdt_JEnom->Draw(cmd,cmd2);
//	tree_bdt_JEnom->Draw(cmd3,cmd2);
	hist_bdt_JEnom->Scale(scale);
	hist_mbb_JEnom->Scale(scale);
	for (int i=0;i<NCATS;i++){
		Nevt_nom[i] = hist_bdt_JEnom->GetBinContent(i+1);
		Nevt_nom_er[i] = hist_bdt_JEnom->GetBinError(i+1);
	}

	
	ofstream out;
	out.open("output_txt/"+s_names[sig_num]+type+type_unc+".txt");
	out <<"Yields and stat errors for "<<type<<"  "<<type_unc<<"  "<<s_names[sig_num]<<"  " <<endl;
	for (int i=0;i<NCATS;i++)
		out<<cats_names[i]<<"\t";
	out<<endl;	
	for (int i=0;i<NCATS;i++)
		out<<std::fixed<<std::setprecision(5)<<Nevt_nom[i]<<"\t";
		out<<endl;
	for (int i=0;i<NCATS;i++)
		out<<std::fixed<<std::setprecision(5)<<Nevt_nom_er[i]<<"\t";	
	out<<endl;	
	out.close();




	return 0;
}

