#include <iostream>
#include <fstream>
#include <TH1F.h>
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

	int type_int=atoi(argv[1]);
	int signal_sample_num=atoi(argv[2]);

	int narrow_type=0;
	TString narrow[2] = {"","_narrow"};

	TString dir = "output_hist/v21/";

	gROOT->ProcessLine(".x /afs/cern.ch/work/n/nchernya/setTDRStyle.C");
	Double_t precision=0.01;
	TString binning;
	binning.Form("%f",precision);
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
	double start1=0.+precision;
//	double start1=0.;
	double start2=0.+2*precision;
	double start3=0.+3*precision;

	
	const int num_bgs=8;  //8; //BGs
	const int num_ss=3;   //3;		//Ss

//	int type_int; //double  =0; single=1
	
	TString type;
	if (type_int==0) type = "_double";
	if (type_int==1) type = "_single";
	TString text_type;
	if (type_int==0) text_type = "DoubleBtag";
	if (type_int==1) text_type = "SingleBtag";
	

	TString bg_names[num_bgs] = {"QCD_HT100to200", "QCD_HT200to300", "QCD_HT300to500","QCD_HT500to700", "QCD_HT700to1000", "QCD_HT1000to1500", "QCD_HT1500to2000", "QCD_HT2000toInf"};
	TString s_names[num_ss] = {"VBFHToBB_M-125_13TeV_powheg-ext", "VBFHToBB_M-130_13TeV_powheg", "VBFHToBB_M125_13TeV_amcatnlo"};
	TString tex_s_names[num_ss] = {"VBF powheg, m(H) = 125 GeV","VBF powheg, m(H) = 130 GeV", "VBF amc@NLO, m(H) = 125 GeV"};
	TString data_names[1] = {"BTagCSV"};

	TString ending = "";

	TFile *file_s =  TFile::Open(dir+"BDT_hist_"+s_names[signal_sample_num]+type+ending+".root");
	TH1F *hist_S = (TH1F*)file_s->Get("BDT_output");

	TFile *file_b[num_bgs];
	TH1F *hist_Bs[num_bgs];
/*
	file_b[0] = TFile::Open(dir+"BDT_hist_"+bg_names[0]+type+".root");
	hist_Bs[0] = (TH1F*)file_b[0]->Get("BDT_output"+narrow[narrow_type]);
	for (int i=1;i<num_bgs;i++){
		file_b[i] = TFile::Open(dir+"BDT_hist_"+bg_names[i]+type+".root");
		hist_Bs[i] = (TH1F*)file_b[i]->Get("BDT_output"+narrow[narrow_type]);
		hist_Bs[0]->Add(hist_Bs[i]);
	}
//	TH1F *hist_B = (TH1F*)hist_Bs[0]->Clone(); */
	TFile *file_data =  TFile::Open(dir+"BDT_hist_"+data_names[0]+type+ending+".root");
	TH1F *hist_D = (TH1F*)file_data->Get("BDT_output"+narrow[narrow_type]);
////if we use data as BG
	TH1F *hist_B = (TH1F*)hist_D->Clone(); 
	
	double END = hist_B->GetBinCenter(hist_B->FindLastBinAbove(0.)); //right end of BDT distibution


	TCanvas *c1 = new TCanvas();
	c1->SetBottomMargin(.12);
	c1->SetLogy();
	c1->cd();
	TH1F *frame2 = new TH1F("frame2","",400,-1.,1.);
//	frame2->SetMinimum(1e-1);
//   frame2->SetMaximum(1e7);
	frame2->SetMinimum(hist_S->GetMinimum()+0.001);
	frame2->SetMaximum(hist_B->GetMaximum()*1e04);
   frame2->GetYaxis()->SetTitleOffset(1.4);
   frame2->GetXaxis()->SetTitleOffset(1.);
   frame2->SetStats(0);
   frame2->SetTitleFont(42,"x");
	frame2->SetTitleFont(42,"y");
   frame2->SetTitleSize(0.05, "XYZ");
	frame2->SetYTitle("Events / 2320 pb^{-1}");
	frame2->SetXTitle("BDT output");	
	frame2->GetXaxis()->SetLabelSize(0.05);
	frame2->Draw();
	TLatex* tex = new TLatex(0.95,0.95,"13 TeV, bx = 25 ns, 2320 pb^{-1}");
   tex->SetNDC();
	tex->SetTextAlign(35);
   tex->SetTextFont(42);
   tex->SetTextSize(0.04);
   tex->SetLineWidth(2);
   TLatex *tex1 = new TLatex(0.2,0.83,"CMS");
   tex1->SetNDC();
   tex1->SetTextAlign(20);
   tex1->SetTextFont(61);
   tex1->SetTextSize(0.06);
   tex1->SetLineWidth(2);
   TLatex* tex2 = new TLatex(0.27,0.77,"Preliminary 2015");
   tex2->SetNDC();
   tex2->SetTextAlign(20);
   tex2->SetTextFont(52);
   tex2->SetTextSize(0.04);
  	tex2->SetLineWidth(2);	
	TLatex* tex_file = new TLatex(0.3,0.95,text_type);
   tex_file->SetNDC();
	tex_file->SetTextAlign(35);
   tex_file->SetTextFont(42);
   tex_file->SetTextSize(0.04);
   tex_file->SetLineWidth(2);	
	tex->Draw();
	tex1->Draw();
	tex2->Draw();
	tex_file->Draw();
	hist_S->SetLineColor(2);
	hist_S->SetLineWidth(2);
	hist_B->SetLineColor(4);
	hist_B->SetLineWidth(2);
	hist_S->Draw("same");
	hist_B->Draw("same");
	TLegend *leg = new TLegend(0.42,0.7,0.92,0.93);
	leg->SetFillColor(0);
	leg->SetBorderSize(0);
	leg->SetTextSize(0.04);
	leg->AddEntry(hist_S,tex_s_names[signal_sample_num],"L");
//	leg->AddEntry(hist_B,"QCD, H_{T} = 100 - #infty GeV","L");
	leg->AddEntry(hist_B,"Data BTagCSV","L");
	leg->Draw("same");
	c1->Print("plots/v21/BDT_output_signal_bg_"+s_names[signal_sample_num]+type+narrow[narrow_type]+ending+".png");
		


	int num_of_bins = hist_S->GetNbinsX();

	int i=0; int j=0; int k=0; int l=0; int m=0; int p=0;
	double bin=0.;

max=0;	
		do	{
			s1=hist_S->GetBinContent(i+1);
			b1=hist_B->GetBinContent(i+1);
			bin=(double) hist_S->GetBinCenter(i+1+1);
			if (b1!=0) max += pow(s1,2)/b1;
			i++;
		} while (bin < END);


	cout<<max<<endl;
 

/*



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
			if (b2!=0)max2=pow(s2,2)/(b2+s2);
			start3=start2+precision;
			do {
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
				if (b3!=0)	max3=pow(s3,2)/(b3+s3);
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
					if (b4!=0 )max4=pow(s4,2)/(b4+s4);
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
	out.open("output_txt/v21/4categories_"+s_names[signal_sample_num]+type+binning+narrow[narrow_type]+ending+"_splusb.txt");
	out<<"borders of categories : "<<border1<<"   "<<border2<<"   "<<border3<< "    , END = "<< END <<endl;
	out<<"S**2/B in each category : "<<max1_final<<"   "<<max2_final<<"   " << max3_final<<"   "<<max4_final<<"     , max = "<<max<<endl;
	out.close();
	cout<<border1<<"   "<<border2<<"   "<<border3<< "   , END = "<< END <<endl;
	cout<<max1_final<<"   "<<max2_final<<"   " << max3_final<<"   "<<max4_final<<"    , max = "<<max<<endl;
*/
return 0;

}

