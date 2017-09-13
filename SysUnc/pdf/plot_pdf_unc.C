#include <iostream>
#include <fstream>
#include <algorithm>
#include <TH1F.h>
#include <TH1.h>
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
	
	TString type_unc = "pdf scale";
	TString type;
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
	TString cats_names[10];
	if (type_int==0) NCATS=3+1;
	else if (type_int==1) NCATS=4+1;
	for (int i=0;i<NCATS;i++){
		TString tmp;
		tmp.Form("%1d",i);
		cats_names[i] = "CAT";
		cats_names[i].Append(tmp);
	} 

	Float_t lumi = 35900.;
	Float_t xsec[2] =  {2.20, 25.69};

	const int num_ss = 2;	

	TString s_names[num_ss] = {"VBFHbb","ggHbb"};
	TString tex_s_names[num_ss] = {"VBF", "GF"};
		


	ofstream out;
	out.open("output_txt/sysUnc_"+s_names[sig_num]+type+"_pdf_cat.txt");
	out <<"Systematic uncertainties pdf scale for "<<type<<"  "<<" "<<s_names[sig_num]<<"  " <<endl;



	TCanvas *c0 = new TCanvas();
	TFile *file_nom =  new TFile("output/"+s_names[sig_num]+"_"+type+"_pdf_unc.root");
	TH1F *hist[10];
for (int cat_num=0;cat_num<NCATS;cat_num++){
	TString tmp_str_num;
	hist[cat_num] = (TH1F*)file_nom->Get("acceptance_cat"+tmp_str_num.Format("\%d",cat_num));


	Float_t actual_acceptance[10];
/*	if ((type_int==1)&&(sig_num==0))  {Float_t actual_acceptance_new[10] = {20.49,	20.31,	13.96,	7.33,	4.24};  memcpy(actual_acceptance, actual_acceptance_new, sizeof actual_acceptance_new); }
	if ((type_int==1)&&(sig_num==1))  {Float_t actual_acceptance_new[10] = {12.21,	5.79,	1.85,	0.64,	0.22};  memcpy(actual_acceptance, actual_acceptance_new, sizeof actual_acceptance_new); }
	if ((type_int==0)&&(sig_num==0))  {Float_t actual_acceptance_new[10] = {31.28,	22.87,	10.70,	3.89};  memcpy(actual_acceptance, actual_acceptance_new, sizeof actual_acceptance_new); }
	if ((type_int==0)&&(sig_num==1))  {Float_t actual_acceptance_new[10] = {121.12,	20.24,	3.20,	0.65};  memcpy(actual_acceptance, actual_acceptance_new, sizeof actual_acceptance_new); }
*/

 	TCanvas* c1 = new TCanvas("pdf","",800,800) ;
	c1->cd();
	Double_t xmin = hist[cat_num]->GetBinCenter(hist[cat_num]->FindFirstBinAbove(0))*0.95;
	Double_t xmax = hist[cat_num]->GetBinCenter(hist[cat_num]->FindLastBinAbove(0))*1.05;
	TH1F *frame2 = new TH1F("frame2","",50, xmin,xmax);
	frame2->SetMinimum(0.);
	frame2->GetXaxis()->SetNdivisions(505);
   frame2->SetMaximum(hist[cat_num]->GetMaximum()*1.3);
//	if (type_int==1)  frame2->SetMaximum(0.005);
   frame2->SetStats(0);
	frame2->SetXTitle(hist[cat_num]->GetXaxis()->GetTitle());
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
	pave.AddText(tmp.Format("\%s","pdf scale "));
	TString tmp2;
	pave.AddText(tmp.Format("RMS = \%s",  (tmp2.Format("\%4.2f",hist[cat_num]->GetRMS() )).Data() ));
	pave.AddText(tmp.Format("mean = \%s",  (tmp2.Format("\%4.2f",hist[cat_num]->GetMean() )).Data() ));
	float ratio=hist[cat_num]->GetRMS()/hist[cat_num]->GetMean();  
	pave.AddText(tmp.Format("RMS/mean = \%s", (tmp2.Format("\%4.3f",ratio)).Data() ));
//	pave.AddText(tmp.Format("central = \%s",  (tmp2.Format("\%4.2f",actual_acceptance[cat_num] )).Data() ));
	pave.Draw("same");
	

//	out<<std::fixed<<std::setprecision(3)<< hist[cat_num]->GetRMS()/actual_acceptance[cat_num]  <<"\t";	
	out<<std::fixed<<std::setprecision(3)<< ratio  <<"\t";	


	TLegend *leg = new TLegend(0.2,0.76,0.5,1.-top*1.666);
	leg->SetFillColor(0);
	leg->SetFillStyle(-1);
	leg->SetBorderSize(0);
	leg->SetTextFont(42);
	leg->SetTextColor(kBlue+1);
	leg->SetTextSize(top*0.5);
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

	hist[cat_num]->SetLineColor(kBlue+1);
	hist[cat_num]->SetLineWidth(3);
	hist[cat_num]->Draw("same");
////////

	c1->Print("plots/"+s_names[sig_num]+type+"_pdf_cat"+tmp_str_num.Format("\%d",cat_num).Data()+".png");
	

}

	out<<endl;	
	out.close();

	return 0;
}

