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

	int type_int = atoi(argv[1]);
	int type_jec = atoi(argv[2]);
	
//int JECR_unc_mbb(int type_int, int type_jec){
	gROOT->ProcessLine(".x /afs/cern.ch/work/n/nchernya/setTDRStyle.C");


//	int type_int; //double  =0; single=1
	
	string type;
	if (type_int==0) type = "double";
	if (type_int==1) type = "single";
	TString text_type;
	if (type_int==0) text_type = "DoubleB";
	if (type_int==1) text_type = "SingleB";
	TString jec;
	if (type_jec==0) jec="JER";
	if (type_jec==1) jec = "JES";

	int NCATS;
	Float_t cats[10]; 
	Float_t Nevt_up[10];
	Float_t Nevt_nom[10];
	Float_t Nevt_down[10];
	Float_t SysUnc[10];
	TString cats_names[10];
//	int NCATS_single = 0;
//	if (type_int==0) NCATS_single= 4;
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

	Float_t lumi = 35900.;
	Float_t xsec[2] =  {2.20,25.69};

	const int num_ss = 2;	
	TString s_names[num_ss] = {"VBFHbb","ggHbb"};
	TString tex_s_names[num_ss] = {"VBF", "GF"};


//up down variabtion loop

	TString corType[3] = {"down","up","nom"};
	TString corType_text[3] = {"Down","Up","Central"};

RooWorkspace w("w","workspace");
for (int i=0;i<3;i++){
 for (int cat_num=0;cat_num<(NCATS);cat_num++){
	char cmd[500];
	char cmd2[500];
	char cmd3[500];








	TCanvas *c3 = new TCanvas();
	TFile *file_nom =  TFile::Open("dcap://t3se01.psi.ch:22125//pnfs/psi.ch/cms/trivcat/store/user/nchernya/VBFHbb2016/v25_VBF_mva_JESR_full/"+type+"VBFMvaJESR_v25_weights_new"+s_names[0]+".root");
	TH1F*	CountPosWeight = (TH1F*)file_nom->Get("CountPosWeight");
	TH1F*	CountNegWeight =(TH1F*)file_nom->Get("CountNegWeight");
 	TH1F*		countWeighted = (TH1F*)file_nom->Get("CountWeighted");
	float events_generated_nom = countWeighted->GetBinContent(1);
	if (events_generated_nom==0) events_generated_nom =  CountPosWeight->GetBinContent(1) - CountNegWeight->GetBinContent(1);

	TTree *tree_bdt_JEnom = (TTree*)file_nom->Get("tree");
	TH1F *hist_mbb_JEdown= new TH1F("hist_mbb_"+jec+"_"+corType[i],"",48,80,200);
	hist_mbb_JEdown->Sumw2(kTRUE);
	hist_mbb_JEdown->GetXaxis()->SetTitle("m_{bb} (GeV)");
	if (i==2) sprintf(cmd3,"\%sMbb>>\%s",(type.c_str()),("hist_mbb_"+jec+"_"+corType[i]).Data());
	else sprintf(cmd3,"\%sMbb_\%s_\%s>>\%s",(type.c_str()),(jec.Data()),(corType[i].Data()),("hist_mbb_"+jec+"_"+corType[i]).Data());
	if (i==2) sprintf(cmd2,"((\%sPassSelection_nom==1)&&(Vtype==-1||Vtype>3)&&((\%sVBF_bdt>\%.2f) && (\%sVBF_bdt<=\%.2f)))*(\%strigWeight_nom*puWeight*TMath::Abs(genWeight)/genWeight)",(type.c_str()),(type.c_str()),cats[cat_num],(type.c_str()),cats[cat_num+1],(type.c_str()));
	else 	sprintf(cmd2,"((\%sPassSelection_\%s_\%s==1)&&(Vtype==-1||Vtype>3)&&((\%sVBF_bdt_\%s_\%s>\%.2f) && (\%sVBF_bdt_\%s_\%s<=\%.2f)))*(\%strigWeight_\%s_\%s*puWeight*TMath::Abs(genWeight)/genWeight)",(type.c_str()),jec.Data(),corType[i].Data(),(type.c_str()),jec.Data(),corType[i].Data(),cats[cat_num],(type.c_str()),jec.Data(),corType[i].Data(),cats[cat_num+1],(type.c_str()),jec.Data(),corType[i].Data());
//	else 	sprintf(cmd2,"((\%sPassSelection_\%s_\%s==1)&&(Vtype==-1||Vtype>3)&&((\%sVBF_bdt>\%.2f) && (\%sVBF_bdt<=\%.2f)))*(\%strigWeight_nom*puWeight*TMath::Abs(genWeight)/genWeight)",(type.c_str()),jec.Data(),corType[i].Data(),(type.c_str()),cats[cat_num],(type.c_str()),cats[cat_num+1],(type.c_str()));
		
	cout<<cmd2<<"  "<<cmd3<<endl;
	tree_bdt_JEnom->Draw(cmd3,cmd2);
	
//	hist_mbb_JEdown->Rebin(2);

	TH1F *hist_mbb_scaled = (TH1F*)hist_mbb_JEdown->Clone("hist_mbb_scaled"+jec+corType[i]);
	hist_mbb_scaled->Scale(lumi*xsec[0]/events_generated_nom);
///////// GF
	
	TCanvas *cgf = new TCanvas();
	TFile *file_gf =  TFile::Open("dcap://t3se01.psi.ch:22125//pnfs/psi.ch/cms/trivcat/store/user/nchernya/VBFHbb2016/v25_VBF_mva_JESR_full/"+type+"VBFMvaJESR_v25_weights_new"+s_names[1]+".root");
	TH1F*	CountPosWeight_gf = (TH1F*)file_gf->Get("CountPosWeight");
	TH1F*	CountNegWeight_gf =(TH1F*)file_gf->Get("CountNegWeight");
 	TH1F*		countWeighted_gf = (TH1F*)file_gf->Get("CountWeighted");
	float events_generated_gf = countWeighted_gf->GetBinContent(1);
	if (events_generated_gf==0) events_generated_gf =  CountPosWeight_gf->GetBinContent(1) - CountNegWeight_gf->GetBinContent(1);
	TTree *tree_bdt_JEdown_gf = (TTree*)file_gf->Get("tree");
	TH1F *hist_mbb_JEdown_gf= new TH1F("hist_mbb_"+jec+"_"+corType[i]+"_gf","",48,80,200);
	hist_mbb_JEdown_gf->Sumw2(kTRUE);
	cout<<"gf"<<endl;
	hist_mbb_JEdown_gf->GetXaxis()->SetTitle("m_{bb} (GeV)");
	if (i==2) sprintf(cmd3,"\%sMbb>>\%s",(type.c_str()),("hist_mbb_"+jec+"_"+corType[i]+"_gf").Data());
	else sprintf(cmd3,"\%sMbb_\%s_\%s>>\%s",(type.c_str()),(jec.Data()),(corType[i].Data()),("hist_mbb_"+jec+"_"+corType[i]+"_gf").Data());
	if (i==2) sprintf(cmd2,"((\%sPassSelection_nom==1)&&(Vtype==-1||Vtype>3)&&((\%sVBF_bdt>\%.2f) && (\%sVBF_bdt<=\%.2f)))*(\%strigWeight_nom*puWeight*TMath::Abs(genWeight)/genWeight)",(type.c_str()),type.c_str(),cats[cat_num],type.c_str(),cats[cat_num+1],(type.c_str()));
	else 	sprintf(cmd2,"((\%sPassSelection_\%s_\%s==1)&& (Vtype==-1||Vtype>3)&& ((\%sVBF_bdt_\%s_\%s>\%.2f) && (\%sVBF_bdt_\%s_\%s<=\%.2f)))*(\%strigWeight_\%s_\%s*puWeight*TMath::Abs(genWeight)/genWeight)",(type.c_str()),jec.Data(),corType[i].Data(),(type.c_str()),jec.Data(),corType[i].Data(),cats[cat_num],(type.c_str()),jec.Data(),corType[i].Data(),cats[cat_num+1],(type.c_str()),jec.Data(),corType[i].Data());
//	else 	sprintf(cmd2,"((\%sPassSelection_\%s_\%s==1)&&(Vtype==-1||Vtype>3)&&((\%sVBF_bdt>\%.2f) && (\%sVBF_bdt<=\%.2f)))*(\%strigWeight_nom*puWeight*TMath::Abs(genWeight)/genWeight)",(type.c_str()),jec.Data(),corType[i].Data(),(type.c_str()),cats[cat_num],(type.c_str()),cats[cat_num+1],(type.c_str()));
	
	tree_bdt_JEdown_gf->Draw(cmd3,cmd2);
	
//	hist_mbb_JEdown_gf->Rebin(2);

	TH1F *hist_mbb_scaled_gf = (TH1F*)hist_mbb_JEdown_gf->Clone("hist_mbb_scaled"+jec+corType[i]+"_gf");
	hist_mbb_scaled_gf->Scale(lumi*xsec[1]/events_generated_gf);


	TH1F *hist_mbb_vbf = (TH1F*)hist_mbb_scaled->Clone("vbf");
	TH1F *hist_mbb_gf = (TH1F*)hist_mbb_scaled_gf->Clone("gf");


	hist_mbb_JEdown->Add(hist_mbb_JEdown_gf);
	hist_mbb_scaled->Add(hist_mbb_scaled_gf);
/////////
//workspaces
	

	char nVar[50], xVar[50], Nb[50];
	sprintf(xVar,"mbb_\%s_\%s_CAT\%d",jec.Data(),corType[i].Data(),cat_num);
	RooRealVar x(xVar,xVar,50,250);
	sprintf(xVar,"roofit_hist_mbb_\%s_\%s_CAT\%d",jec.Data(),corType[i].Data(),cat_num);
	RooDataHist rh(xVar,xVar,RooArgList(x),hist_mbb_JEdown);
	sprintf(xVar,"yield_signal_VBF_\%s_\%s_CAT\%d",jec.Data(),corType[i].Data(),cat_num);
	sprintf(Nb,"CAT\%d",cat_num);
	TString tmp;
	RooRealVar m(tmp.Format("mean_CAT%d_%s",cat_num,corType[i].Data()),tmp.Format("mean_CAT%d_%s",cat_num,corType[i].Data()),125,115,135);
	RooRealVar s(tmp.Format("sigma_CAT%d_%s",cat_num,corType[i].Data()),tmp.Format("sigma_CAT%d_%s",cat_num,corType[i].Data()),12,7,20);
	RooRealVar width(tmp.Format("fwhm_CAT%d_%s",cat_num,corType[i].Data()),tmp.Format("fwhm_CAT%d_%s",cat_num,corType[i].Data()),25,0,50);
	RooRealVar a(tmp.Format("alpha_CAT%d_%s",cat_num,corType[i].Data()),tmp.Format("alpha_CAT%d_%s",cat_num,corType[i].Data()),1,-10,10);
	RooFormulaVar mShift(tmp.Format("mean_shifted_CAT%d_%s",cat_num,corType[i].Data()),tmp.Format("mean_shifted_CAT%d_%s",cat_num,corType[i].Data()),"@0",RooArgList(m));
	RooFormulaVar sShift(tmp.Format("sigma_shifted_CAT%d_%s",cat_num,corType[i].Data()),tmp.Format("mean_shifted_CAT%d_%s",cat_num,corType[i].Data()),"@0",RooArgList(s));
	RooRealVar n(tmp.Format("exp_CAT%d_%s",cat_num,corType[i].Data()),tmp.Format("exp_CAT%d_%s",cat_num,corType[i].Data()),1,0,100);
	RooRealVar b0(tmp.Format("b0_CAT%d_%s",cat_num,corType[i].Data()),tmp.Format("b0_CAT%d_%s",cat_num,corType[i].Data()),0.5,0.,1.);
	RooRealVar b1(tmp.Format("b1_CAT%d_%s",cat_num,corType[i].Data()),tmp.Format("b1_CAT%d_%s",cat_num,corType[i].Data()),0.5,0.,1.);
	RooRealVar b2(tmp.Format("b2_CAT%d_%s",cat_num,corType[i].Data()),tmp.Format("b2_CAT%d_%s",cat_num,corType[i].Data()),0.5,0.,1.);
	RooRealVar b3(tmp.Format("b3_CAT%d_%s",cat_num,corType[i].Data()),tmp.Format("b3_CAT%d_%s",cat_num,corType[i].Data()),0.5,0.,1.);
 /// Bkg part: Bernste[i].Data()n     
	RooBernstein bkg(tmp.Format("signal_bkg_CAT%d_%s",cat_num,corType[i].Data()),tmp.Format("signal_bkg_CAT%d_%s",cat_num,corType[i].Data()),x,RooArgList(b0,b1,b2));
 /// Sig part: Crystal Ball   
	RooRealVar fsig(tmp.Format("fsig_CAT%d_%s",cat_num,corType[i].Data()),tmp.Format("fsig_CAT%d_%s",cat_num,corType[i].Data()),0.7,0.,1.);
	RooCBShape sig(tmp.Format("signal_gauss_CAT%d_%s",cat_num,corType[i].Data()),tmp.Format("signal_gauss_CAT%d_%s",cat_num,corType[i].Data()),x,mShift,sShift,a,n);
 //// Combined model
	RooAddPdf model(tmp.Format("signal_model_CAT%d_%s",cat_num,corType[i].Data()),tmp.Format("signal_model_CAT%d_%s",cat_num,corType[i].Data()),RooArgList(sig,bkg),RooArgList(fsig));
 //// Fit 
 
	model.fitTo(rh,RooFit::SumW2Error(kFALSE));
//	model.fitTo(rh,RooFit::SumW2Error(kTRUE));


	b0.setConstant(kTRUE);
	b1.setConstant(kTRUE);
	b2.setConstant(kTRUE);
	b3.setConstant(kTRUE);
	a.setConstant(kTRUE);
	m.setConstant(kTRUE);
	s.setConstant(kTRUE);
	n.setConstant(kTRUE);
	fsig.setConstant(kTRUE);
	w.import(rh);
	w.import(model);
	w.import(width);
////////

 /// Draw 
	 // 			RooDraw(opts,canM,x,rhs[N],hVBF[N],hGF[N],hTOT[N],yVBF[N],yGF[N],model,bkg,fsig,width,mass,m,s,iS,S,C,Cp,archive)
 	TCanvas* c_roo = new TCanvas("RooFit","",800,800) ;
//	hist_mbb_JEdown->Draw("HIST");
	RooPlot *frame_roo = x.frame(Name("Mbb")) ;
	RooDataHist hScale("tmp","tmp",RooArgList(x),hist_mbb_scaled);
	hScale.plotOn(frame_roo) ;
	model.plotOn(frame_roo);
	frame_roo->GetXaxis()->SetNdivisions(505);
	frame_roo->GetXaxis()->SetTitle("M_{bb} (GeV)");
	RooArgSet bkgplot(bkg);
	model.plotOn(frame_roo,Components(bkgplot),LineColor(kBlue),LineWidth(2),LineStyle(kDashed));
  	frame_roo->Draw() ;




	hist_mbb_gf->SetFillColor(kGreen-8);
	hist_mbb_vbf->SetFillColor(kRed-10);
	THStack *hS = new THStack("hs","hs");
	hS->Add(hist_mbb_gf);
	hS->Add(hist_mbb_vbf);
	hS->Draw("same,hist");
	frame_roo->Draw("same");
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


	TLegend *leg = new TLegend(0.65,0.35,1.-right-top*0.3333,0.45);
	leg->AddEntry(hist_mbb_vbf,"VBF","F");
	leg->AddEntry(hist_mbb_gf,"GF","F");
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
	pave.AddText("M_{H} = 125 GeV");

	sprintf(cmd,"\%s selection",text_type.Data())	;
	pave.AddText(cmd);
	sprintf(cmd,"CAT\%d",cat_num)	;
	pave.AddText(cmd);
	pave.AddText(tmp.Format("%s var %s",jec.Data(),corType_text[i].Data()));
	sprintf(cmd,"m = \%.2f #pm \%.2f",m.getVal(),m.getError())	;
	pave.AddText(cmd);
	sprintf(cmd,"#sigma = \%.2f #pm \%.2f",s.getVal(),s.getError())	;
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

	c_roo->Print("plots/"+type+"_"+jec+"_mbb_"+cats_names[cat_num]+corType[i]+".png");



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

w.writeToFile("plots/workspace"+type+"_"+jec+"_mbb.root");
	return 0;

}

