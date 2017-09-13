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
	TString type_unc = "trigWeight";
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
	Float_t Nevt_down[10];
	Float_t SysUnc[10];
	Float_t SysUnc2[10];
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
	Float_t xsec[2] =  {2.20, 25.69};

	const int num_ss = 2;	

	TString s_names[num_ss] = {"VBFHbb","ggHbb"};
	TString tex_s_names[num_ss] = {"VBF", "GF"};
		


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
	sprintf(cmd2,"(\%sPassSelection_nom==1)*(\%strigWeight_nom*puWeight*Jet_btagWeightCMVAV2[\%sbtag_num1]*Jet_btagWeightCMVAV2[\%sbtag_num2]*\%sQGLweight)",(type.c_str()),(type.c_str()),(type.c_str()),(type.c_str()),(type.c_str()));	
	tree_bdt_JEnom->Draw(cmd,cmd2);
//	tree_bdt_JEnom->Draw(cmd3,cmd2);
	hist_bdt_JEnom->Scale(scale);
	hist_mbb_JEnom->Scale(scale);
	for (int i=0;i<NCATS;i++)
		Nevt_nom[i] = hist_bdt_JEnom->GetBinContent(i+1);

	TCanvas *c3 = new TCanvas();
	TH1F *hist_bdt_JEdown= new TH1F("hist_bdt_down","",NCATS,cats);
	hist_bdt_JEdown->GetXaxis()->SetTitle("BDT output"); 
	TH1F *hist_mbb_JEdown= new TH1F("hist_mbb_down","",60,50,200);
	hist_mbb_JEdown->GetXaxis()->SetTitle("m_{bb} (GeV)");
	sprintf(cmd,"\%s\%s>>\%s",(type.c_str()),("VBF_bdt"),("hist_bdt_down"));	
//	sprintf(cmd3,"\%s\%s>>\%s",(type),("Mbb"),("hist_mbb_down"));
//	sprintf(cmd2,"(\%sPassSelection_nom==1)*(\%strigWeight_nom*puWeightDown*Jet_btagWeightCMVAV2[\%sbtag_num1]*Jet_btagWeightCMVAV2[\%sbtag_num2]*\%sQGLweight)",(type.c_str()),(type.c_str()),(type.c_str()),(type.c_str()),(type.c_str()));	
	sprintf(cmd2,"(\%sPassSelection_nom==1)*(\%strigWeightDown*puWeight*Jet_btagWeightCMVAV2[\%sbtag_num1]*Jet_btagWeightCMVAV2[\%sbtag_num2]*\%sQGLweight)",(type.c_str()),(type.c_str()),(type.c_str()),(type.c_str()),(type.c_str()));	
//	sprintf(cmd2,"(\%sPassSelection_nom==1)*(\%strigWeight_nom*puWeight*Jet_btagWeightCMVAV2[\%sbtag_num1]*Jet_btagWeightCMVAV2[\%sbtag_num2]*\%sQGLweight*LHE_weights_scale_wgt[5])",(type.c_str()),(type.c_str()),(type.c_str()),(type.c_str()),(type.c_str()));	
	tree_bdt_JEnom->Draw(cmd,cmd2);
//	tree_bdt_JEnom->Draw(cmd3,cmd2);
	hist_bdt_JEdown->Scale(scale);
	hist_mbb_JEdown->Scale(scale);
	for (int i=0;i<NCATS;i++)
		Nevt_down[i] = hist_bdt_JEdown->GetBinContent(i+1);


	TCanvas *c2 = new TCanvas();
	TH1F * hist_bdt_JEup= new TH1F("hist_bdt_up","",NCATS,cats);
	hist_bdt_JEup->GetXaxis()->SetTitle("BDT output");
	TH1F *hist_mbb_JEup= new TH1F("hist_mbb_up","",60,50,200);
	hist_mbb_JEup->GetXaxis()->SetTitle("m_{bb} (GeV)");
	sprintf(cmd,"\%s\%s>>\%s",(type.c_str()),("VBF_bdt"),("hist_bdt_up"));	
//	sprintf(cmd3,"\%s\%s>>\%s",(type),("Mbb"),("hist_mbb_up"));	
	sprintf(cmd2,"(\%sPassSelection_nom==1)*(\%strigWeightUp*puWeight*Jet_btagWeightCMVAV2[\%sbtag_num1]*Jet_btagWeightCMVAV2[\%sbtag_num2]*\%sQGLweight)",(type.c_str()),(type.c_str()),(type.c_str()),(type.c_str()),(type.c_str()));	
//	sprintf(cmd2,"(\%sPassSelection_nom==1)*(\%strigWeight_nom*puWeight*Jet_btagWeightCMVAV2[\%sbtag_num1]*Jet_btagWeightCMVAV2[\%sbtag_num2]*\%sQGLweight*LHE_weights_scale_wgt[4])",(type.c_str()),(type.c_str()),(type.c_str()),(type.c_str()),(type.c_str()));	
	tree_bdt_JEnom->Draw(cmd,cmd2);
//	tree_bdt_JEnom->Draw(cmd3,cmd2);
	hist_bdt_JEup->Scale(scale);
	hist_mbb_JEup->Scale(scale);
	for (int i=0;i<NCATS;i++)
		Nevt_up[i] = hist_bdt_JEup->GetBinContent(i+1);

	
	for (int i=0;i<NCATS;i++){
	//	SysUnc[i] = max( TMath::Abs((Nevt_up[i] - Nevt_nom[i])), TMath::Abs((Nevt_nom[i] - Nevt_down[i])) ) / Nevt_nom[i];
		SysUnc[i] = (Nevt_up[i] - Nevt_nom[i])/(Nevt_up[i] + Nevt_nom[i])*2.;
		SysUnc2[i] = (Nevt_nom[i] - Nevt_down[i])/(Nevt_nom[i] + Nevt_down[i])*2.;
	}

	ofstream out;
	out.open("output_txt_pu/sysUnc_"+s_names[sig_num]+type+type_unc+".txt");
	out <<"Systematic uncertainties for "<<type<<"  "<<type_unc<<"  "<<s_names[sig_num]<<"  " <<endl;
	for (int i=0;i<NCATS;i++)
		out<<cats_names[i]<<"\t";
	out<<endl;	
	for (int i=0;i<NCATS;i++)
		out<<std::fixed<<std::setprecision(5)<<1+SysUnc[i]<<"\t";	
	out<<endl;
	for (int i=0;i<NCATS;i++)
		out<<std::fixed<<std::setprecision(5)<<1+SysUnc2[i]<<"\t";	
	out<<endl;	
	out.close();


 	TCanvas* c1 = new TCanvas("bdt","",800,800) ;
	c1->cd();
	TH1F *frame2 = new TH1F("frame2","",50,-1.,1.);
	frame2->SetMinimum(0.);
	frame2->GetXaxis()->SetNdivisions(505);
   frame2->SetMaximum(hist_bdt_JEnom->GetMaximum()*1.7);
//	if (type_int==1)  frame2->SetMaximum(0.005);
   frame2->SetStats(0);
	frame2->SetXTitle(hist_bdt_JEnom->GetXaxis()->GetTitle());
	frame2->SetYTitle("Events");
	frame2->Draw();

	TString tmp;
	float right   = gStyle->GetPadRightMargin();
	float top = gStyle->GetPadTopMargin();
	float left =  gStyle->GetPadLeftMargin();
	float bottom = gStyle->GetPadBottomMargin();
	TPaveText pave(0.65,0.65,1.-right-top*0.5333,1.-top*1.666,"NDC");
	pave.SetTextAlign(11);
	pave.SetFillStyle(-1);
	pave.SetBorderSize(0);
	pave.SetTextFont(42);
	pave.SetTextSize(top*0.5);
	pave.SetTextColor(kBlue+1);

	pave.AddText(tmp.Format("\%s",tex_s_names[sig_num].Data()));
	pave.AddText("M_{H} = 125 GeV");
	pave.AddText(tmp.Format("\%s selection",text_type.Data()));
	pave.AddText(tmp.Format("\%s",type_unc.Data()));
	pave.AddText(tmp);
	pave.Draw("same");

	TLegend *leg = new TLegend(0.2,0.76,0.5,1.-top*1.666);
	leg->SetFillColor(0);
	leg->SetFillStyle(-1);
	leg->SetBorderSize(0);
	leg->SetTextFont(42);
	leg->SetTextColor(kBlue+1);
	leg->SetTextSize(top*0.5);
	leg->AddEntry(hist_bdt_JEup,"Up","L");
	leg->AddEntry(hist_bdt_JEnom,"Central","L");
	leg->AddEntry(hist_bdt_JEdown,"Down","L");
	leg->Draw("same");

// CMS info

	float left2 = gStyle->GetPadLeftMargin();
	float right2 = gStyle->GetPadRightMargin();
	float top2 = gStyle->GetPadTopMargin();
	float bottom2 = gStyle->GetPadBottomMargin();

	TPaveText pCMS1(left2,1.-top2,0.4,1.,"NDC");
	pCMS1.SetTextFont(62);
	pCMS1.SetTextSize(top2*0.75);
	pCMS1.SetTextAlign(12);
	pCMS1.SetFillStyle(-1);
	pCMS1.SetBorderSize(0);
	pCMS1.AddText("CMS");
	TPaveText pCMS2(0.5,1.-top2,1.-right2*0.5,1.,"NDC");
	pCMS2.SetTextFont(42);
	pCMS2.SetTextSize(top2*0.75);
	pCMS2.SetTextAlign(32);
	pCMS2.SetFillStyle(-1);
	pCMS2.SetBorderSize(0);
	pCMS2.AddText("L = 35.9 fb^{-1} (13 TeV)");
	gPad->Update();
	pCMS1.Draw("same");
	pCMS2.Draw("same");
	gPad->Update();
	pave.Draw("same");
	pCMS1.Draw("same");
	pCMS2.Draw("same");

	hist_bdt_JEnom->SetLineColor(4);
	hist_bdt_JEnom->SetLineWidth(2);
	hist_bdt_JEup->SetLineColor(2);
	hist_bdt_JEup->SetLineWidth(2);
	hist_bdt_JEdown->SetLineColor(8);
	hist_bdt_JEdown->SetLineWidth(2);
	hist_bdt_JEnom->Draw("same");
	hist_bdt_JEup->Draw("same");
	hist_bdt_JEdown->Draw("same");

////////

	c1->Print("plots_pu/"+s_names[sig_num]+type+type_unc+".png");
	



	return 0;
}

