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
#include "RooFitResult.h"
#include "RooWorkspace.h"
#include "RooConstVar.h"
#include "RooPlot.h"
#include "TPaveText.h"
#include "TVirtualPad.h"
#include "/mnt/t3nfs01/data01/shome/nchernya/CMSSW_7_4_7/src/HiggsAnalysis/CombinedLimit/interface/RooMultiPdf.h"
#include <TSystem.h>

//#include "RooMultiPdf.h"

//int main(int arg,char* argv[]){
void makeRooMultiPdfWorkspace(){

   TFile *fout = new TFile("qcd_pdfs.root","RECREATE");
   // Load the combine Library 
   gSystem->Load("libHiggsAnalysisCombinedLimit.so");

	TString par_names[10] = {"b0_CAT0","b1_CAT0","b2_CAT0","b3_CAT0","b4_CAT0","b5_CAT0","b6_CAT0","b7_CAT0","b8_CAT0"};
//	RooAbsArg *arg[10];
	RooRealVar *arg[10];
	Float_t par_values[10];
for (int num=0;num<4;num++){

	TString tmp;
 /*  TFile *f_expPow = TFile::Open("v25_cat4_test/root/biasCATS_shapes_workspace_expPow.root");
   RooWorkspace *w_expPow = (RooWorkspace*)f_expPow->Get("w");
   // The observable Mbb

   RooRealVar *mass =  w_expPow->var(tmp.Format("mbbReg_CAT%d",num));
   // Get expPow
   RooAbsPdf *pdf_expPow = w_expPow->pdf(tmp.Format("qcd_model_POL1_CAT%d",num));
   RooDataSet *data = (RooDataSet*)w_expPow->data(tmp.Format("data_hist_CAT%d",num));

   TFile *f_modG = TFile::Open("v25_cat4_test/root/biasCATS_shapes_workspace_modG.root");
   RooWorkspace *w_modG = (RooWorkspace*)f_modG->Get("w");
   // Get modG
   RooAbsPdf *pdf_modG = w_modG->pdf(tmp.Format("qcd_model_POL1_CAT%d",num));


   TFile *f_Pol6 = TFile::Open("v25_cat4_test/root/biasCATS_shapes_workspace_Pol6.root");
   RooWorkspace *w_Pol6 = (RooWorkspace*)f_Pol6->Get("w");
   // Get Pol6
   RooAbsPdf *pdf_Pol6 = w_Pol6->pdf(tmp.Format("qcd_model_POL1_CAT%d",num));
 //  RooAbsPdf *pdf_Pol6_full = w_Pol6->pdf(tmp.Format("bkg_model_POL1_CAT%d",num));

   TFile *f_Pol7 = TFile::Open("v25_cat4_test/root/biasCATS_shapes_workspace_Pol7.root");
   RooWorkspace *w_Pol7 = (RooWorkspace*)f_Pol7->Get("w");
   // Get Pol7
   RooAbsPdf *pdf_Pol7 = w_Pol7->pdf(tmp.Format("qcd_model_POL1_CAT%d",num));
	

   TFile *f_Pol8 = TFile::Open("v25_cat4_test/root/biasCATS_shapes_workspace_Pol8.root");
   RooWorkspace *w_Pol8 = (RooWorkspace*)f_Pol8->Get("w");
   // Get Pol8
   RooAbsPdf *pdf_Pol8 = w_Pol8->pdf(tmp.Format("qcd_model_POL1_CAT%d",num));
*/
  // TFile *f_Pol8 = TFile::Open("v25_cat4_test/root/data_shapes_workspace.root");
   TFile *f_Pol8 = TFile::Open("v25_cat4_test/root/biasCATS_shapes_workspace_Pol8.root");
   RooWorkspace *w_Pol8 = (RooWorkspace*)f_Pol8->Get("w");
   // Get Pol8
   RooAbsPdf *pdf_Pol8 = w_Pol8->pdf(tmp.Format("qcd_model_POL1_CAT%d",num));
   RooRealVar *mass =  w_Pol8->var(tmp.Format("mbbReg_CAT%d",num));
   RooDataSet *data = (RooDataSet*)w_Pol8->data(tmp.Format("data_hist_CAT%d",num));
   RooAbsPdf *pdf_Pol8_full = w_Pol8->pdf(tmp.Format("bkg_model_POL1_CAT%d",num));	
	cout<<"Printing full model"<<endl;
	pdf_Pol8_full->Print();
	if (num==0){
		arg[0] = w_Pol8->var(par_names[0]);
		arg[1] = w_Pol8->var(par_names[1]);
		arg[2] = w_Pol8->var(par_names[2]);
		arg[3] = w_Pol8->var(par_names[3]);
		arg[4] = w_Pol8->var(par_names[4]);
		arg[5] = w_Pol8->var(par_names[5]);
		arg[6] = w_Pol8->var(par_names[6]);
		arg[7] = w_Pol8->var(par_names[7]);
//		arg[8] = w_Pol8->var(par_names[8]);
	}
	else  {
		for (int i=0;i<8;i++)
			(w_Pol8->var(par_names[i]))->setConstant(kTRUE);
		
	}
//	RooArgSet arg = w_Pol6->argSet("b0_CAT0,b1_CAT0");
//	RooArgSet arg = pdf_Pol6_full->getParameters("b0_CAT0,b1_CAT0");
//	RooArgSet *arg = pdf_Pol6_full->getParameters(RooArgSet("b0_CAT0,b1_CAT0"));
	
   // Fit the functions to the data to set the "prefit" state (note this can and should be redone with combine when doing 
   // bias studies as one typically throws toys from the "best-fit"
//   pdf_expPow->fitTo(*data);  // index 0
 //  pdf_modG->fitTo(*data); // index 1 
     pdf_Pol8_full->fitTo(*data);   // index 2
	  pdf_Pol8_full->Print();
  // pdf_Pol7->fitTo(*data);   // index 2
  // pdf_Pol8->fitTo(*data);   // index 2
	cout<<"here"<<endl;
//	arg[0]->Print();
//	for (int i=0;i<6;i++)
//		par_values[i] = arg[i];

   // Make a plot (data is a toy dataset)
   TCanvas *can =  new TCanvas(tmp.Format("can%d",num),"",600,600);
   RooPlot *plot = mass->frame();   data->plotOn(plot);
 //  pdf_expPow->plotOn(plot,RooFit::LineColor(kGreen));
 //  pdf_modG->plotOn(plot,RooFit::LineColor(kBlue));
   pdf_Pol8_full->plotOn(plot,RooFit::LineColor(kRed));
//   pdf_Pol7->plotOn(plot,RooFit::LineColor(kYellow));
 //  pdf_Pol8->plotOn(plot,RooFit::LineColor(kOrange));
   plot->SetTitle("PDF fits to toy data");
   plot->Draw();

	for (int i=0;i<8;i++)
		(w_Pol8->var(par_names[i]))->setConstant(kFALSE);
//	(w_Pol8->var(tmp.Format("trans_POL1_CAT%d_p1",num)))->setConstant(kFALSE);
	if (num!=0)(w_Pol8->var(tmp.Format("trans_POL1_CAT%d_p1",num)))->setConstant(kFALSE);

   // Make a RooCategory object. This will control which of the pdfs is "active"
   RooCategory cat("pdf_index","Index of Pdf which is active");

   // Make a RooMultiPdf object. The order of the pdfs will be the order of their index, ie for below 
   // 0 == exponential
   // 1 == linear function
   // 2 == powerlaw
   RooArgList mypdfs;
//   mypdfs.add(*pdf_expPow); //0
  // mypdfs.add(*pdf_modG); //1
//   mypdfs.add(*pdf_Pol6); //2
 //  mypdfs.add(*pdf_Pol7);//3
   mypdfs.add(*pdf_Pol8);//4
   
   RooMultiPdf multipdf(tmp.Format("QCD_multi_pdf_CAT%d",num),"QCD pdfs",cat,mypdfs);
   
   // As usual make an extended term for the background with _norm for freely floating yield
   RooRealVar norm(tmp.Format("QCD_multi_pdf_CAT%d_norm",num),"Number of qcd events",0,10000);
   
  //  Save to a new workspace
  	fout->cd();	
   RooWorkspace wout(tmp.Format("qcds_CAT%d",num),tmp.Format("qcds_CAT%d",num));
   wout.import(cat);
   wout.import(norm);
   wout.import(multipdf);
 //  wout.Print();
   wout.Write();
	}

}
