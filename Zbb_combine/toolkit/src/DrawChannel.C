
#include <iostream>
#include <fstream>
#include <algorithm>
#include <TH1F.h>
#include <TH2F.h>
#include <TBox.h>
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
#include "TCanvas.h"
#include "TPaveText.h"
#include "TVirtualPad.h"
#include "TLine.h"
#include "TGraphAsymmErrors.h"
#include "TPad.h"
#include "TFrame.h"


void DrawChannel()
{ 
  gROOT->ProcessLine(".x ../common/styleCMSTDR.C");

	gROOT->ForceStyle();
  gStyle->SetOptStat(0);
  gStyle->SetOptTitle(0);
  gROOT->SetBatch(1);
  gStyle->SetPadRightMargin(0.04);
  gStyle->SetPadLeftMargin(0.16);
  gStyle->SetPadTopMargin(0.08);
  gStyle->SetPadBottomMargin(0.15);
  gStyle->SetTitleFont(42,"XY");
  gStyle->SetTitleSize(0.0475,"XY");
  gStyle->SetTitleOffset(0.9,"X");
  gStyle->SetTitleOffset(1.5,"Y");
  gStyle->SetLabelSize(0.0375,"XY");
	int nChann=4;
 TH2F *frame = new TH2F("frame",";best fit #sigma/#sigma_{SM};",1,-5,13,nChann,0,nChann);
TString channel_name[10] = {"CAT0","CAT1","CAT2","CAT3"};
	Float_t mus[10] = {11.5, 0.78,0.81, 0.85};
	Float_t mus_down[10] = {-6.6,-0.46,-0.26,-0.17};
	Float_t mus_up[10] = {7.7,0.50,0.27,0.17};
 TGraphAsymmErrors *points = new TGraphAsymmErrors(nChann);
	for (int iChann=0;iChann<nChann;iChann++){
		points->SetPoint(iChann,mus[iChann] ,iChann+0.5);
      points->SetPointError(iChann,TMath::Abs(mus_down[iChann]),mus_up[iChann] ,0,0);
		frame->GetYaxis()->SetBinLabel(iChann+1, channel_name[iChann]);
	}

  points->SetLineColor(kRed);
  points->SetLineWidth(3);
  points->SetMarkerStyle(21);
	
	
	Float_t combined_fit = 0.81;
	Float_t combined_fit_down = -0.15;
	Float_t combined_fit_up =0.15;



 TCanvas *can = new TCanvas("Channel","Channel",900,600);
  frame->GetXaxis()->SetNdivisions(505);
  frame->GetXaxis()->SetTitleSize(0.06);
  frame->GetXaxis()->SetTitleOffset(0.9);
  frame->GetXaxis()->SetLabelSize(0.05);
  frame->GetYaxis()->SetLabelSize(0.1);
  frame->Draw(); 
  //gStyle->SetOptStat(0);
  TBox globalFitBand(combined_fit+combined_fit_down, 0, combined_fit+combined_fit_up, nChann);
  //TBox globalFitBand(rFit->getVal()-rFit->getAsymErrorHi(), 0, rFit->getVal()+rFit->getAsymErrorHi(), nChann);
  globalFitBand.SetFillStyle(3013);
  globalFitBand.SetFillColor(65);
  globalFitBand.SetLineStyle(0);
  globalFitBand.DrawClone();
  TLine globalFitLine(combined_fit, 0,combined_fit,  nChann);
  globalFitLine.SetLineWidth(4);
  globalFitLine.SetLineColor(214);
  globalFitLine.DrawClone();
  points->Draw("P SAME");
  gPad->Update();

  TPaveText *pave = new TPaveText(0.6,0.7,0.9,0.9,"NDC");
  pave->AddText("Fit for the Z-boson");
  pave->AddText(TString::Format("combined fit: %.2f^{ +%.2f}_{ %.2f}",combined_fit,combined_fit_up,combined_fit_down));
  pave->SetFillColor(0);
  pave->SetTextFont(62);
  pave->SetTextSize(0.05);
  pave->SetBorderSize(0);
  pave->Draw();

  TLine *ln0 = new TLine(1,gPad->GetFrame()->GetY1(),1,gPad->GetFrame()->GetY2());
  ln0->SetLineColor(kBlack);
  ln0->SetLineWidth(1);
  ln0->SetLineStyle(2);
  ln0->Draw("same");


	float left2 = gStyle->GetPadLeftMargin();
	float right2 = gStyle->GetPadRightMargin();
	float top2 = gStyle->GetPadTopMargin();
	float bottom2 = gStyle->GetPadBottomMargin();
	TPaveText *paveCMS = new TPaveText(left2,1.-top2,0.4,1.,"NDC");
	 paveCMS->SetTextFont(62);
	 paveCMS->SetTextSize(gStyle->GetPadTopMargin()*3./4.);
	 paveCMS->SetBorderSize(0);
	 paveCMS->SetFillStyle(-1);
	 paveCMS->SetTextAlign(12);
	 paveCMS->AddText("CMS");
	 paveCMS->Draw();
	 gPad->Update();
	TPaveText pCMS12(left2+0.08,1.-top2*1.13,0.57,1.,"NDC");
	pCMS12.SetTextFont(52);
	pCMS12.SetTextSize(top2*0.73);
	pCMS12.SetTextAlign(12);
	pCMS12.SetFillStyle(-1);
	pCMS12.SetBorderSize(0);
	pCMS12.AddText("Preliminary");
	pCMS12.Draw();
	 gPad->Update();
	 paveCMS->SetY1NDC(paveCMS->GetY2NDC()-paveCMS->GetListOfLines()->GetSize()*gStyle->GetPadTopMargin());

	 TPaveText *paveLumi = new TPaveText(0.5,1.-gStyle->GetPadTopMargin(),0.98,1.00,"NDC");
	 paveLumi->SetTextFont(42);
	 paveLumi->SetTextSize(gStyle->GetPadTopMargin()*3./4.);
	 paveLumi->SetBorderSize(0);
	 paveLumi->SetFillStyle(-1);
	 paveLumi->SetTextAlign(32);
	 paveLumi->AddText("35.9 fb^{-1} (13TeV)"); 
	 paveLumi->Draw();



	  TPaveText *paveNumbers = new TPaveText(left2,bottom2+0.01,0.4,.93,"NDC");
	 paveNumbers->SetTextFont(42);
	 paveNumbers->SetTextSize(gStyle->GetPadTopMargin()*2./5.);
	 paveNumbers->SetBorderSize(0);
	 paveNumbers->SetFillStyle(-1);
	 paveNumbers->SetTextAlign(12);
	 //paveNumbers->SetMargin(1);
	 for (int i=nChann-1;i>=0;i--){
	 paveNumbers->AddText(TString::Format("%.2f^{+%.2f}_{%.2f}",mus[i],mus_up[i],mus_down[i]));
	}
	 paveNumbers->Draw();
	 gPad->Update();
	
	can->Print("channels_zbb.pdf");
}
