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
void makeRooMultiPdfWorkspace_simple(){

   // Load the combine Library 
   gSystem->Load("libHiggsAnalysisCombinedLimit.so");

   TFile *f_expPow = TFile::Open("v25_cat4_test/root/bias_shapes_workspace_expPow.root");
   RooWorkspace *w_expPow = (RooWorkspace*)f_expPow->Get("w");
   // The observable Mbb
   RooRealVar *mass =  w_expPow->var("mbbReg_CAT0");
   // Get expPow
   RooAbsPdf *pdf_expPow = w_expPow->pdf("qcd_model_expPow_CAT0");
   RooDataSet *data = (RooDataSet*)w_expPow->data("data_hist_CAT0");

   TFile *f_modG = TFile::Open("v25_cat4_test/root/bias_shapes_workspace_modG.root");
   RooWorkspace *w_modG = (RooWorkspace*)f_modG->Get("w");
   // Get modG
   RooAbsPdf *pdf_modG = w_modG->pdf("qcd_model_modG_CAT0");


   TFile *f_Pol6 = TFile::Open("v25_cat4_test/root/bias_shapes_workspace_Pol6.root");
   RooWorkspace *w_Pol6 = (RooWorkspace*)f_Pol6->Get("w");
   // Get Pol6
   RooAbsPdf *pdf_Pol6 = w_Pol6->pdf("qcd_model_Pol6_CAT0");

   TFile *f_Pol7 = TFile::Open("v25_cat4_test/root/bias_shapes_workspace_Pol7.root");
   RooWorkspace *w_Pol7 = (RooWorkspace*)f_Pol7->Get("w");
   // Get Pol7
   RooAbsPdf *pdf_Pol7 = w_Pol7->pdf("qcd_model_Pol7_CAT0");


   TFile *f_Pol8 = TFile::Open("v25_cat4_test/root/bias_shapes_workspace_Pol8.root");
   RooWorkspace *w_Pol8 = (RooWorkspace*)f_Pol8->Get("w");
   // Get Pol8
   RooAbsPdf *pdf_Pol8 = w_Pol8->pdf("qcd_model_Pol8_CAT0");


   // Fit the functions to the data to set the "prefit" state (note this can and should be redone with combine when doing 
   // bias studies as one typically throws toys from the "best-fit"
   pdf_expPow->fitTo(*data);  // index 0
   pdf_modG->fitTo(*data); // index 1 
   pdf_Pol6->fitTo(*data);   // index 2
   pdf_Pol7->fitTo(*data);   // index 2
   pdf_Pol8->fitTo(*data);   // index 2

   // Make a plot (data is a toy dataset)
   RooPlot *plot = mass->frame();   data->plotOn(plot);
   pdf_expPow->plotOn(plot,RooFit::LineColor(kGreen));
   pdf_modG->plotOn(plot,RooFit::LineColor(kBlue));
   pdf_Pol6->plotOn(plot,RooFit::LineColor(kRed));
   pdf_Pol7->plotOn(plot,RooFit::LineColor(kYellow));
   pdf_Pol8->plotOn(plot,RooFit::LineColor(kOrange));
   plot->SetTitle("PDF fits to toy data");
   plot->Draw();

   // Make a RooCategory object. This will control which of the pdfs is "active"
   RooCategory cat("pdf_index","Index of Pdf which is active");

   // Make a RooMultiPdf object. The order of the pdfs will be the order of their index, ie for below 
   // 0 == exponential
   // 1 == linear function
   // 2 == powerlaw
   RooArgList mypdfs;
   mypdfs.add(*pdf_expPow);
   mypdfs.add(*pdf_modG);
   mypdfs.add(*pdf_Pol6);
   mypdfs.add(*pdf_Pol7);
   mypdfs.add(*pdf_Pol8);
   
   RooMultiPdf multipdf("QCD_multi_pdf","QCD pdfs",cat,mypdfs);
   
   // As usual make an extended term for the background with _norm for freely floating yield
   RooRealVar norm("roomultipdf_norm","Number of qcd events",0,10000);
   
   // Save to a new workspace
   TFile *fout = new TFile("qcd_pdfs.root","RECREATE");
   RooWorkspace wout("qcds","qcds");
   wout.import(cat);
   wout.import(norm);
   wout.import(multipdf);
   wout.Print();
   wout.Write();

}
