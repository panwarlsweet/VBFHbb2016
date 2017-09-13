#include <iostream>
#include <fstream>
#include <algorithm>
#include <TH1F.h>
#include <TF1.h>
#include <TTree.h>
#include <TStyle.h>
#include <TCanvas.h>
#include "TLorentzVector.h"
#include <iomanip>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "TFile.h"
#include "THStack.h"
#include "TROOT.h"
#include "TLatex.h"
#include "TLegend.h"
#include "RooRealVar.h"
#include "RooDataHist.h"
#include "RooStats/SPlot.h"
#include "RooDataSet.h"
#include "RooRealVar.h"
#include "RooFormulaVar.h"
#include "RooGaussian.h"
#include "RooExponential.h"
#include "RooCBShape.h"
#include "RooChebychev.h"
#include "RooBernstein.h"
#include "RooAddPdf.h"
#include "RooProdPdf.h"
#include "RooAddition.h"
#include "RooProduct.h"
#include "TCanvas.h"
#include "RooAbsPdf.h"
#include "RooFit.h"
#include "RooFitResult.h"
#include "RooWorkspace.h"
#include "RooConstVar.h"
#include "RooPlot.h"
#include "TPaveText.h"
#include "TVirtualPad.h"


using namespace RooFit ;
using namespace std;


int main(int argc, char* argv[]){

	int type_jec = atoi(argv[1]);
	
//int JECR_unc_mbb(int type_int, int type_jec){
	gROOT->ProcessLine(".x /afs/cern.ch/work/n/nchernya/setTDRStyle.C");


//	int type_int; //double  =0; single=1
	
	int type_int=0;
	TString type;
	TString text_type;
	type = "_double";
	if (type_int==0) text_type = "DoubleB";
	TString jec;
	if (type_jec==0) jec="JER";
	if (type_jec==1) jec = "JEC";

	int NCATS;
	Float_t cats[10]; 
	Float_t Nevt_up[10];
	Float_t Nevt_nom[10];
	Float_t Nevt_down[10];
	Float_t SysUnc[10];
	TString cats_names[10];
//	int NCATS_single = 0;
//	if (type_int==0) NCATS_single= 4;
	if (type_int==0) NCATS=4;
Float_t cats_new[10]={-1., -0.2275 ,  0.1125 ,  0.3425  , 1. };  //0.9725
memcpy(cats, cats_new, sizeof cats_new);
	TString tmp;
	for (int i=0;i<NCATS;i++){
		tmp.Form("%1d",i);
		cats_names[i] = "CAT";
		cats_names[i].Append(tmp);
	} 
//		Float_t cats[10] = {-1.,0.12,0.44,0.57,0.6725};

	Float_t lumi = 35900.;

		

//up down variabtion loop

	TString corType[3] = {"down","up","nom"};
	TString corType_text[3] = {"Down","Up","Central"};

RooWorkspace w("w","workspace");
for (int i=0;i<3;i++){
 for (int cat_num=0;cat_num<(NCATS);cat_num++){
	char cmd[50];
	char cmd2[50];
	char cmd3[50];








	TCanvas *c3 = new TCanvas();
	TFile *file =  new TFile("root/DYJetsToQQ_analysis_double_trignone_v25_"+jec+corType[i]+"2.root");
	char hist_name[50];
	sprintf(hist_name,"hMbb_Zbbcat\%d",cat_num);
	TH1F *hist_mbb_JEdown= (TH1F*)file->Get(hist_name);
	hist_mbb_JEdown->Sumw2(kTRUE);
	hist_mbb_JEdown->GetXaxis()->SetTitle("m_{bb} (GeV)");
	
	TH1F *hist_mbb_scaled = (TH1F*)hist_mbb_JEdown->Clone("hist_mbb_scaled"+jec+corType[i]);
	hist_mbb_scaled->Scale(lumi);
	hist_mbb_scaled->Rebin(2);
	

	TH1F *hist_mbb = (TH1F*)hist_mbb_scaled->Clone("zbb");


////////

 /// Draw 
 	TCanvas* c_roo = new TCanvas("RooFit","",800,800) ;

	hist_mbb->SetFillColor(kRed-10);
	THStack *hS = new THStack("hs","hs");
	hS->Add(hist_mbb);
	hS->Draw("hist");
	gPad->RedrawAxis();
/*
	TF1 *ftmp= (TF1*) model.asTF(RooArgList(x),RooArgList(fsig),RooArgSet(x));
	float y0       = ftmp->GetMaximum();
	float x0 = ftmp->GetMaximumX();
	float x1       = ftmp->GetX(y0/2.,80,x0);
	float x2 =ftmp->GetX(y0/2.,x0,200);
	float fwhm        = x2-x1;
	width.setVal(fwhm);
//	float y1          = opts.dX[iS]*25*0.5*y0*(yVBF.getVal()+yGF.getVal())/ftmp->Integral(80.,200.);
///	TLine *line        = new TLine(x1,y1,x2,y1);
//	line->SetLineColor(kMagenta+3);
//	line->SetLineStyle(7);
//	line->SetLineWidth(2);
//	line->Draw("same");*/


	float right   = gStyle->GetPadRightMargin();
	float top = gStyle->GetPadTopMargin();
	float left =  gStyle->GetPadLeftMargin();
	float bottom = gStyle->GetPadBottomMargin();


//	TLegend *leg = new TLegend(0.65,0.35,1.-right-top*0.3333,0.45);
	TLegend *leg = new TLegend(0.2,0.87,0.4,0.93);
	leg->AddEntry(hist_mbb,"Z(bb) + jets","F");
	leg->SetFillStyle(-1);
	leg->SetBorderSize(0);
	leg->SetTextFont(42);
	leg->SetTextSize(top*0.75);
	leg->SetY1(leg->GetY2()-top*leg->GetNRows()*0.87);
	leg->Draw("same");


	TPaveText pave(0.65,0.65,1.-right-top*0.5333,1.-top*1.666,"NDC");
	pave.SetTextAlign(11);
	pave.SetFillStyle(-1);
	pave.SetBorderSize(0);
	pave.SetTextFont(42);
	pave.SetTextSize(top*0.5);
	pave.SetTextColor(kBlue+1);
	sprintf(cmd,"CAT\%d",cat_num)	;
	pave.AddText(cmd);
	pave.AddText(tmp.Format("%s var %s",jec.Data(),corType_text[i].Data()));
	sprintf(cmd,"Mean = \%.1f #pm \%.1f",hist_mbb->GetMean(), hist_mbb->GetMeanError())	;
	pave.AddText(cmd);
	sprintf(cmd,"RMS = \%.1f #pm \%.1f",hist_mbb->GetRMS(),hist_mbb->GetRMSError())	;
	pave.AddText(cmd);
	pave.Draw("same");


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

	c_roo->Print("plots/simple"+jec+"_mbb_"+cats_names[cat_num]+corType[i]+"_v25.png");



/*	
	TCanvas *c11 = new TCanvas();
	c11->SetBottomMargin(.15);
	c11->SetRightMargin(.25);
	c11->cd();
	TH1F *frame3 = new TH1F("frame3","",15,50.,200.);
	frame3->SetMinimum(0.);
   frame3->SetMaximum(hist_mbb_JEdown->GetMaximum()*1.6);
   frame3->SetStats(0);
	frame3->SetYTitle("Events");
	frame3->SetXTitle(hist_mbb_JEdown->GetXaxis()->GetTitle());
	frame3->GetYaxis()->SetNdivisions(505);
	frame3->GetXaxis()->SetLabelSize(0.0);
  	frame3->GetXaxis()->SetTitleSize(0.05);
  	frame3->GetXaxis()->SetLabelSize(0.04);
	frame3->Draw();
	TLatex* tex = new TLatex(0.75,0.95,"13 TeV");
   tex->SetNDC();
	tex->SetTextAlign(35);
   tex->SetTextFont(42);
   tex->SetTextSize(0.035);
   tex->SetLineWidth(2);
   TLatex *tex1 = new TLatex(0.17,0.95,"CMS");
   tex1->SetNDC();
   tex1->SetTextAlign(20);
   tex1->SetTextFont(61);
   tex1->SetTextSize(0.04);
   tex1->SetLineWidth(2);
   TLatex* tex2 = new TLatex(0.25,0.89,"Work in progress");
   tex2->SetNDC();
   tex2->SetTextAlign(20);
   tex2->SetTextFont(52);
   tex2->SetTextSize(0.035);
  	tex2->SetLineWidth(2);	
	TLatex* tex_file = new TLatex(0.36,0.95,text_type);
   tex_file->SetNDC();
	tex_file->SetTextAlign(35);
   tex_file->SetTextFont(42);
   tex_file->SetTextSize(0.04);
   tex_file->SetLineWidth(2);	
	tex->Draw();
	tex1->Draw();
	tex2->Draw();
//	tex_file->Draw();
	hist_mbb_JEdown->SetLineColor(8);
	hist_mbb_JEdown->SetLineWidth(2);
	hist_mbb_JEdown->Draw("PEsame");
	TLegend *leg = new TLegend(0.77,0.6,0.92,0.9);
	leg->SetFillColor(0);
//	leg->SetBorderSize(0);
	leg->SetTextFont(42);
	leg->SetTextSize(0.025);
	leg->SetHeader(jec+" variation");
//	leg->AddEntry(hist_mbb_JEnom,"central","L");
//	leg->AddEntry(hist_mbb_JEdown,jec+" down","L");
//	leg->AddEntry(hist_mbb_JEup,jec+" up","L");
	
//	leg->Draw("same");
//	c11->Print("plots/shape/v14_vbf"+type+"_"+jec+"_mbb_"+cats_names[cat_num]+corType[i]+".png");
*/
}
}

//w.writeToFile("plots/shape/v25/workspace"+type+"_"+jec+"_mbb_v25.root");
	return 0;

}

