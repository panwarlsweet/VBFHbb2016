#include <iostream>
#include <fstream>
#include <TH1F.h>
#include <TPaveText.h>
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

using namespace std;

int main(int argc, char* argv[]){
//int cat5(int type_int, int signal_sample_num){

	TString path="dcap://t3se01.psi.ch:22125//pnfs/psi.ch/cms/trivcat/store/user/nchernya/VBFHbb2016/plotterOutput/v25/";

	gROOT->ProcessLine(".x /afs/cern.ch/work/n/nchernya/setTDRStyle.C");
	Double_t precision=0.01;
	TString binning;
	binning.Form("%0.3f",precision);
	double NCAT=4;
	double max1=0; double max2=0; double max3=0; double max4=0;
	double max1_final=0; double max2_final=0; double max3_final=0; double max4_final=0;
	double s1=0; double s2=0;double s3=0;  double s4=0;
	double b1=0; double b2=0;double b3=0;  double b4=0; 
	double max = -10;
	double border1=0;
	double border2=0;
	double border3=0;
	double border4=0;
	
	const int num_bgs=8;  //8; //BGs
	const int num_ss=3;   //3;		//Ss

	int type_int = atoi(argv[1]); //double  =0; single=1
	
	TString text_type;
	TString text_type_str;
	if (type_int==1) {
		text_type="single"; 
		text_type_str="SingleB(High M_{jj})";
	}
	if (type_int==0) {
		text_type="double"; 
		text_type_str="DoubleB";
	}

	TString ending = "";

	TFile *file_s =  TFile::Open(path+"VBFHToBB_M-125_analysis_"+text_type+"_trignone_v25_VBFbdt.root");
	TH1F *hist_S = (TH1F*)file_s->Get("hbdt_fine");
	hist_S->Scale(35900.);

	TFile *file_data =  TFile::Open(path+"BTagCSV_analysis_"+text_type+"_trignone_v25_VBFbdt.root");
	TH1F *hist_D = (TH1F*)file_data->Get("hbdt_fine");
////if we use data as BG
	TH1F *hist_B = (TH1F*)hist_D->Clone(); 
	
	double END = hist_B->GetBinCenter(hist_B->FindLastBinAbove(0.)); //right end of BDT distibution
	double START = hist_B->GetBinCenter(hist_B->FindFirstBinAbove(0.)); //right end of BDT distibution
	cout<<"start = "<<START<<" , end = "<<END<<endl;
	double start1=START+precision;
	double start2=START+2*precision;
	double start3=START+3*precision;


	hist_S->SetLineColor(kRed);
	hist_S->SetFillColor(kRed-7);
	hist_S->SetLineWidth(2);
	hist_B->SetLineColor(kBlue+1);
	hist_B->SetFillColor(kBlue-10);
	hist_B->SetLineWidth(2);
	TH1F *hist_B2 = (TH1F*)hist_B->Clone("b_new");
	hist_B2->Rebin(4);
	TH1F *hist_S2 = (TH1F*)hist_S->Clone("b_new");
	hist_S2->Rebin(4);


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
	TPaveText pCMS12(left2+0.1,1.-top2*1.1,0.6,1.,"NDC");
	pCMS12.SetTextFont(52);
	pCMS12.SetTextSize(top2*0.75);
	pCMS12.SetTextAlign(12);
	pCMS12.SetFillStyle(-1);
	pCMS12.SetBorderSize(0);
	pCMS12.AddText("Preliminary");
	TPaveText pCMS2(0.5,1.-top2,1.-right2*0.5,1.,"NDC");
	pCMS2.SetTextFont(42);
	pCMS2.SetTextSize(top2*0.75);
	pCMS2.SetTextAlign(32);
	pCMS2.SetFillStyle(-1);
	pCMS2.SetBorderSize(0);
	pCMS2.AddText("L = 35.9 fb^{-1} (13 TeV)");


	TPaveText pave22(0.2,0.8,0.4,1.-top2*1.666,"NDC");
	pave22.SetTextAlign(11);
	pave22.SetFillStyle(-1);
	pave22.SetBorderSize(0);
	pave22.SetTextFont(62);
	pave22.SetTextSize(top2*0.5);
	pave22.AddText("Higgs search");

	TPaveText pave33(0.2,0.75,0.4,0.8,"NDC");
	pave33.SetTextAlign(11);
	pave33.SetFillStyle(-1);
	pave33.SetBorderSize(0);
	pave33.SetTextFont(42);
	pave33.SetTextColor(kBlue);
	pave33.SetTextSize(top2*0.5);
	pave33.AddText(text_type_str);





	TLegend *leg = new TLegend(0.72,0.78,0.85,0.9);
	leg->SetFillColor(0);
	leg->SetBorderSize(0);
	leg->SetTextFont(42);
	leg->SetTextSize(0.025);
	leg->AddEntry(hist_S,"VBF H#rightarrow b#bar{b}","F");
	leg->AddEntry(hist_B,"Data","F");


		


	int num_of_bins = hist_S->GetNbinsX();

	int i=0; int j=0; int k=0; int l=0; int m=0; int p=0;
	double bin=0.;

	float max_all=0;	
		do	{
			s1=hist_S->GetBinContent(i+1);
			b1=hist_B->GetBinContent(i+1);
			bin=(double) hist_S->GetBinCenter(i+1+1);
			if ((b1+s1)!=0) max_all += pow(s1,2)/(b1+s1);
			i++;
		} while (bin < END);


	cout<<max_all<<endl;
	cout<<sqrt(max_all)<<endl;
 


max=0;


	do {
		i=0;
		max1=0;
		s1=0;
		b1=0;
		do	{
			s1+=hist_S->GetBinContent(i+1);
			b1+=hist_B->GetBinContent(i+1);
			bin=(double) hist_S->GetBinCenter(i+1+1);
			i++;
		} while (bin < start1);
		if (b1!=0)max1=pow(s1,2)/(b1+s1);
	//	cout<<max1<<endl;
		start2=start1+precision;
		do {
			j=i;
			max2=0;
			s2=0;
			b2=0;
			do	{
				s2+=hist_S->GetBinContent(j+1);
				b2+=hist_B->GetBinContent(j+1);
				bin=(double) hist_S->GetBinCenter(j+1+1);
				j++;
			} while (bin < start2);
			if ((b2+s2)!=0)max2=pow(s2,2)/(b2+s2);
			start3=start2+precision;
		//	cout<<max2<<endl;
			do{
				m=j;
				max3=0;
				s3=0;
				b3=0;
				do	{
					s3+=hist_S->GetBinContent(m+1);
					b3+=hist_B->GetBinContent(m+1);
					bin=(double) hist_S->GetBinCenter(m+1+1);
					m++;
				} while (bin < start3);
				if ((b3+s3)!=0)	max3=pow(s3,2)/(b3+s3);
			//	cout<<max3<<endl;
					l=m;
					max4=0;
					s4=0;
					b4=0.;
					do  {
						s4+=hist_S->GetBinContent(l+1);
						b4+=hist_B->GetBinContent(l+1);
						bin=(double) hist_S->GetBinCenter(l+1+1);
						l++;
					} while (bin < END);
					if ((b4+s4)!=0 )max4=pow(s4,2)/(b4+s4);
					if ((max1+max2+max3+max4)>=max) {
						max = max1+max2+max3+max4;
						border1=start1;
						border2=start2;
						border3=start3;
						max1_final=max1;
						max2_final=max2;
						max3_final=max3;
						max4_final=max4;
					}
				start3+=precision;
			} while (start3<=(END-(NCAT-3)*precision));
			start2+=precision;
		} while (start2<=(END-(NCAT-2)*precision));
		start1+=precision;
	} while (start1<=(END-(NCAT-1)*precision));

	ofstream out;
	out.open("output_txt/4categories_splusb"+text_type+binning+".txt");
	out<<"max all, sqrt : "<<max_all<<"  , "<<sqrt(max_all)<<endl;
	out<<"borders of categories : "<<START<<"   "<<border1<<"   "<<border2<<"   "<<border3<<" , END = "<< END <<endl;
	out<<"S**2/S+B in each category : "<<max1_final<<"   "<<max2_final<<"   " << max3_final<<"  "<<max4_final<< "    , max = "<<max<<endl;
	out<<"sqrt(S**2/S+B) in each category : "<<sqrt(max1_final)<<"   "<<sqrt(max2_final)<<"   " << sqrt(max3_final)<<"   " << sqrt(max4_final) <<"    , max = "<<sqrt(max)<<endl;
	cout<<"max all, sqrt : "<<max_all<<"  , "<<sqrt(max_all)<<endl;
	cout<<"borders of categories : "<<START<<"   "<<border1<<"   "<<border2<<"   "<<border3<<" , END = "<< END <<endl;
	cout<<"S**2/S+B in each category : "<<max1_final<<"   "<<max2_final<<"   " << max3_final<<"  "<<max4_final<< "    , max = "<<max<<endl;
	cout<<"sqrt(S**2/S+B) in each category : "<<sqrt(max1_final)<<"   "<<sqrt(max2_final)<<"   " << sqrt(max3_final)<<"   " << sqrt(max4_final) <<"    , max = "<<sqrt(max)<<endl;
	out.close();




	float ymin=0.5;
	float ymax=hist_B2->GetMaximum()*1e02;

	TLine line1(border1,ymin,border1,hist_B2->GetBinContent(hist_B2->FindBin(border1)));
	line1.SetLineStyle(9);
	line1.SetLineColor(1);
	line1.SetLineWidth(2);
	TLine line2(border2,ymin,border2,hist_B2->GetBinContent(hist_B2->FindBin(border2)));
	line2.SetLineStyle(9);
	line2.SetLineColor(1);
	line2.SetLineWidth(2);
	TLine line3(border3,ymin,border3,hist_B2->GetBinContent(hist_B2->FindBin(border3)));
	line3.SetLineStyle(9);
	line3.SetLineColor(1);
	line3.SetLineWidth(2);


	TCanvas *c1 = new TCanvas("Fit","",800,800);
	c1->SetLogy();
	c1->cd();
	TH1F *frame2 = new TH1F("frame2","",50,-1.,1.);
	frame2->GetXaxis()->SetNdivisions(505);
//	frame2->GetYaxis()->SetRangeUser(80,150);
   frame2->SetStats(0);
	frame2->SetYTitle("Events");
	frame2->SetXTitle("BDT output");	
	frame2->SetMinimum(ymin);
	frame2->SetMaximum(ymax);
	frame2->Draw();

	hist_B2->Draw("HISTsame");
	hist_S2->Draw("HISTsame");

	gPad->Update();
	pCMS1.Draw("same");
	pCMS2.Draw("same");
	pCMS12.Draw("same");
	pave22.Draw("same");
	pave33.Draw("same");
	leg->Draw("same");
	line1.Draw("same");
	line2.Draw("same");
	line3.Draw("same");
	gPad->RedrawAxis();
	c1->Print("plots/VBF_BDT_output_signal_bg_"+text_type+"cat4.png");



return 0;

}

