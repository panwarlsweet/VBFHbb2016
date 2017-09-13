#include <stdio.h>
#include <iomanip>
#include <string>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include "TFile.h"
#include "TH1.h"
#include "TH1F.h"
#include "TH2.h"
#include "TTree.h"
#include <TROOT.h>
#include <TString.h>
#include <TStyle.h>
#include <TSystem.h>
#include <TCanvas.h>
#include <TMarker.h>
#include <THStack.h>
#include <TLegend.h>
#include <TLatex.h>
#include <TCut.h>
#include <TGraph.h>
#include <TGraphErrors.h>
#include <TLorentzVector.h>
#include <TMath.h>
#include <TF1.h>
#include "TROOT.h"
#include "TPaveText.h"
#include "TPad.h"
#include "TGaxis.h"
#include <boost/format.hpp>
#include <array>
#include <algorithm>
#include <iterator>

#define SWAP(A, B) { Float_t t = A; A = B; B = t; }
#define SWAP2(A, B) { B.swap(A); }

void bubblesort(Float_t *a, std::string *str, int n)
{
  int i, j;
  for (i = n - 1; i >= 0; i--)
  {
    for (j = 0; j < i; j++)
    {
      if (a[j] < a[j + 1]){
        SWAP( a[j], a[j + 1] );
	//	cout<<str[j]<<"   "<<str[j+1]<<endl;
		SWAP2( str[j], str[j+1]);
	//	cout<<str[j]<<"   "<<str[j+1]<<endl;
		}
    }
  }
}


Float_t Discr(TH1F *h1, TH1F *h2){  
  Int_t h1s = h1->GetNbinsX();
  Int_t h2s = h2->GetNbinsX();
  if (h1s != h2s) {
  	printf("h1 size %d   h2 size %d \n",h1s,h2s);
  	return -1;
  }
  if (h1->Integral()!=0 ) h1->Scale(1./h1->Integral());
  if (h2->Integral()!=0 ) h2->Scale(1./h2->Integral());
  Float_t adiff = 0;
  for (Int_t i=0;i<h1s;i++){
	adiff +=  TMath::Abs(h1->GetBinContent(i) - h2->GetBinContent(i));
	//cout << "h1 bin " << i << " " << h1->GetBinContent(i) << endl;
	}
  return adiff/2;
}

using namespace std;

int main(int argc, char* argv[]){
//int analyzer_stackRatio(){
gROOT->ProcessLine(".x /afs/cern.ch/work/n/nchernya/setTDRStyle.C");
int set_type=atoi(argv[1]); // 0 - analysis, 1 - control region , top
 
const int nfiles  = 8; //9;  //11;
TString leg_names[nfiles] = {"Data","Z + jets","W + jets","Single Top","t#bar{t}","QCD","GF, m(H) = 125 GeV","VBF, m(H) = 125 GeV"};
TString leg_names_signals[nfiles] = {"VBF, m(H) = 125 GeV","GF, m(H) = 125 GeV"};
TString set_names[2] = {"DoubleB","SingleB"}; 


TString file_names[nfiles] = {"BTagCSV","DYJetsToQQ","WJetsToQQ","ST","TT","QCD","GluGluHToBB_M-125","VBFHToBB_M-125"};
int bg_begin;
 bg_begin=1;

int FILLCOLOR[nfiles] = {1,kYellow-9,kOrange-9,kYellow-10, kOrange-2,kRed-9,kBlue,kRed};
//int LINECOLOR[nfiles] = {1,kYellow-9,kOrange-9,kYellow-10, kOrange-2,kRed-9,kRed};
int LINECOLOR[nfiles] = {1,1,1,1,1,1,kBlue,kRed};
int LINESTYLE[nfiles] = {1,1,1,1,1,1,2,1};
int LINEWIDTH[nfiles] = {1,1,1,1,1,1,3,3};
int FILLSTYLE[nfiles] = {1001,1001,1001,1001,1001,1001,1001,1001};
	
int order[nfiles] = {0,1,2,3,4,5,6,7};// number in file_names array as they should appear in the legend
int order_legend[nfiles]; 
for (int i=0;i<nfiles;i++){
	order_legend[order[i]]=i;
}
	

TString set[3]={"_double","_single"}; 

for (int i=0;i<nfiles;i++){
   file_names[i].Prepend("dcap://t3se01.psi.ch:22125//pnfs/psi.ch/cms/trivcat//store/user/nchernya/VBFHbb2016/plotterOutput/v25/");
	file_names[i].Append("_analysis");
	file_names[i].Append(set[set_type]);
	file_names[i].Append("_trignone_v25_noregression");
	file_names[i].Append(".root");
}
TString trigger[2] = {"", ""};
TString dir_name= "plots_v25_noregression";
dir_name.Append(set[set_type]+"/");
Float_t lumi = 35900;

	


TLegend *leg = new TLegend(0.77,0.45,0.92,0.9); //without writing about SF
leg->SetFillColor(0);
leg->SetBorderSize(0);
leg->SetTextFont(42);
leg->SetTextSize(0.025);
TLegend *leg2 = new TLegend(0.77,0.35,0.92,0.4); //with  writing about SF
leg2->SetFillColor(0);
leg2->SetBorderSize(0);
leg2->SetTextFont(42);
leg2->SetTextSize(0.025);

const int nhistos = 83; //40//52
TString hist_names[nhistos]={"hJet1_pt","hJet2_pt","hJet3_pt","hJet4_pt","hJet1_eta","hJet2_eta","hJet3_eta","hJet4_eta","hJet1_phi","hJet2_phi","hJet3_phi","hJet4_phi","hMqq", "hEtaQQ", "hPhiBB","hMbb","hbtag","hbtag2","hcosOqqbb","hEtaQB1", "hEtaQB2", "hPhiQB1", "hPhiQB2","hx1","hx2","hVB1_mass","hVB2_mass","hEtot","hPxtot","hPytot","hPztot","hJet5_pt","hPtqqbb","hEtaqqbb","hPhiqqbb","hJet1_pt_bin","hJet2_pt_bin","hJet3_pt_bin","hJet4_pt_bin", "hEtaSoftJets", "hPtSoftJets","hMassSoftJets","hHTsoft","hSoft_n2","hSoft_n5","hSoft_n10","hqgl","hqgl2", "hPtSoftJets2","hPtSoftJets3","hPVs", "hJet1q_pt", "hJet1q_eta", "hJet1q_ptd", "hJet1q_axis2", "hJet1q_mult", "hJet2q_pt", "hJet2q_eta", "hJet2q_ptd", "hJet2q_axis2", "hJet2q_mult","hMbb_regVBF","hMbb_regVBF_fsr","hblike1","hblike2", "hmet", "hPhiQQ", "hMbb_regVBF_fsr_high","hselLeptons_relIso03", "hbtag_log","hbtag2_log","hrho","hJet1q_leadTrackPt","hJet2q_leadTrackPt" ,"hJet1b_pt", "hJet2b_pt", "hJet1b_eta", "hJet2b_eta", "hJetbb_pt", "hJetqqbb_pz", "hEtaQBplus", "hEtaQBminus","hlheHT"};

TString hist_names_sum[nhistos]={};
TString sum_histos_names[nhistos]={};
std::string hist_names_sort[nhistos];
for (int i=0;i<nhistos;i++){
	hist_names_sort[i] = hist_names[i];
	hist_names_sum[i] = hist_names[i];
	hist_names_sum[i].Append("_sum");
	sum_histos_names[i] = hist_names[i];
	sum_histos_names[i].Append("_sum0");
}
Float_t discriminators[nhistos];
TString stacks_names[nhistos];
for (int i=0;i<nhistos;i++){
	stacks_names[i] = hist_names[i];
	stacks_names[i].Prepend("s");
}
TString output_names[nhistos];
for (int i=0;i<nhistos;i++){
	output_names[i] = hist_names[i];
	output_names[i].Prepend(dir_name);
	output_names[i].Append(set[set_type]);
	output_names[i].Append(set[set_type]+"_v25.png");
}

TH1F *data_histos[nhistos];
TH1F *data_histos2[nhistos];
TH1F *data_histosQCDup[nhistos];
TH1F *data_histosQCDlo[nhistos];
TH1F *data_histosJESup[nhistos];
TH1F *data_histosJESlo[nhistos];
TH1F *data_histosTrig[nhistos];
TH1F *signal_histos[nhistos];
TH1F *signal_histos2[nhistos];
TH1F *tthbb_histos[nhistos];
TH1F *tthnbb_histos[nhistos];
TH1F *gf_histos[nhistos];
TH1F *sum_histos[nhistos];
TH1F *sum_histosUp[nhistos];
TH1F *sum_histosDown[nhistos];
TH1F *histos_forUnc[nhistos];
TH1F *histos_for_legened[nhistos];
TH1F *discr_histos[nhistos];//Mqq,delta eta, delta phi, qgl, btag //12,13,14,21,22
TH1F *hBkgVis[nhistos];
TH1F *hBkgUncUp[nhistos];
TH1F *hBkgUncLo[nhistos];
TH1F *hBkgUncUpTrig[nhistos];
TH1F *hBkgUncLoTrig[nhistos];
TH1F *hBkgQCDUp[nhistos];
TH1F *hBkgQCDLo[nhistos];
TH1F *hBkgJESUp[nhistos];
TH1F *hBkgJESLo[nhistos];


int files=0; 
THStack *stacks[nhistos];
for (int i=0;i<nhistos;++i){
	stacks[i] = new THStack(stacks_names[i],"");
}
Double_t totalBG=0.;
Double_t totalQCD=0.;
Double_t totalMC=0.;
Double_t totalData=0.;
Double_t totalDataQCD=0.;
ofstream out_efficiency;
ofstream out_discrimination;
out_efficiency.open(dir_name+"efficiency.txt"); 




float ratio[1];
int counter_ratio=0;
TString file_names_mc[nfiles];
do{
float dataInt = 0;
float MCint = 0;
float QCDint =0;
for (int i=0;i<nfiles;i++) {
	file_names_mc[i] = file_names[i];
}
files=0;
do{
	TFile *file_initial_mc;		
  	file_initial_mc = TFile::Open(file_names_mc[files]);
	string file_name_tag = file_names_mc[files].Data();
	TH1F *histos_mc[100];
	int hist=0;
	histos_mc[hist] = (TH1F*)file_initial_mc->Get(hist_names[hist])->Clone("mc");
	if (files!=0 )histos_mc[hist]->Scale(lumi);  
	if (files==0) dataInt = histos_mc[hist]->Integral(0,histos_mc[hist]->GetNbinsX()+1); 
	if (files!=0) {
		if (file_name_tag.find("QCD")!=std::string::npos)  QCDint= histos_mc[hist]->Integral(0,histos_mc[hist]->GetNbinsX()+1);
		else MCint+=histos_mc[hist]->Integral(0,histos_mc[hist]->GetNbinsX()+1); 
	}
	files++;	
} while (files<nfiles); 
float tmp_ratio = (dataInt-MCint)/QCDint;
ratio[counter_ratio] = tmp_ratio;
counter_ratio++;
} while (counter_ratio<1);



files=0;

do{
	TFile *file_initial;
  	file_initial = TFile::Open(file_names[files]);
	string file_name_tag = file_names[files].Data();
	string leg_name_tag = leg_names[files].Data();
	//cout<<file_names[files]<<endl;
	TH1F *histos[100];
	for (int hist=0;hist<nhistos;++hist){
		histos[hist] = (TH1F*)file_initial->Get(hist_names[hist])->Clone("h");
		if (files==0) data_histos[hist] = (TH1F*)file_initial->Get(hist_names[hist])->Clone("data");
		if (files>0)histos[hist]->Scale(lumi); 
		if (file_name_tag.find("QCD")!=std::string::npos)  histos[hist]->Scale(ratio[0]);  

////////////////////////////
////////////////////////////
////////////////////////////
// Signal now is included in the sum total MC
		if (files==1) 	sum_histos[hist] = (TH1F*)histos[hist]->Clone(sum_histos_names[hist]);
		if (files>1)	sum_histos[hist]->Add(histos[hist]); 
		if (files>0) histos[hist]->Sumw2(kFALSE);

		if (files==nfiles-1) {
			signal_histos[hist] = (TH1F*)file_initial->Get(hist_names[hist])->Clone(hist_names_sum[hist]+"newhist");
			signal_histos[hist]->Scale(lumi);
			signal_histos[hist]->Sumw2(kFALSE);
			signal_histos[hist]->SetLineColor(LINECOLOR[files]);
			signal_histos[hist]->SetLineStyle(LINESTYLE[files]);
			signal_histos2[hist]=(TH1F*)signal_histos[hist]->Clone("signalHist2");
		}
		if (files==nfiles-2) {
			gf_histos[hist] = (TH1F*)file_initial->Get(hist_names[hist])->Clone(hist_names_sum[hist]+"newhist_gf");
			gf_histos[hist]->Scale(lumi);
			gf_histos[hist]->Sumw2(kFALSE);
			gf_histos[hist]->SetLineColor(LINECOLOR[files]);
			gf_histos[hist]->SetLineStyle(LINESTYLE[files]);
		}
		histos[hist]->SetLineColor(LINECOLOR[files]);
		histos[hist]->SetLineStyle(LINESTYLE[files]);
		histos[hist]->SetLineWidth(LINEWIDTH[files]);
		histos[hist]->SetFillStyle(FILLSTYLE[files]);
		if ((files!=0)) histos[hist]->SetFillColor(FILLCOLOR[files]);
		
		if (files==0) {
			histos[hist]->SetMarkerStyle(20);
			data_histos[hist]->SetLineColor(1);
			data_histos[hist]->SetMarkerStyle(10);
			data_histos[hist]->SetMarkerSize(.8);
		}
	 	//if (files>=bg_begin) stacks[hist]->Add(histos[hist]);
	 	if ((files>=1)&&(files<(nfiles-2))) stacks[hist]->Add(histos[hist]);
		if (hist==0) histos_for_legened[files] = (TH1F*)histos[0]->Clone("newd");
		if (files==bg_begin)	discr_histos[hist] = (TH1F*)file_initial->Get(hist_names[hist])->Clone("discr");
		if ((files>bg_begin)&&(files<(nfiles-2))){
			discr_histos[hist]->Add(histos[hist]); 
   	}
		}
		if ((files>bg_begin)&&(files<(nfiles-2))) totalBG+=histos[0]->Integral(0,histos[0]->GetNbinsX()+1);
		if (files>0) totalMC+=histos[0]->Integral(0,histos[0]->GetNbinsX()+1);
		if (files==0) {totalData+=histos[0]->Integral(0,histos[0]->GetNbinsX()+1); }
		if (files==0) out_efficiency<<"Sample  \t\t\t yield(per "<< lumi<<" pb^-1)"<<endl;
		if (files==0) out_efficiency<<leg_names[order[files]]<<"\t \t \t"<< std::setprecision(8)<<histos[0]->Integral(0,histos[0]->GetNbinsX()+1) <<endl;
		else out_efficiency<<leg_names[order[files]]<<"\t\t\t  "<<std::setprecision(8)<<histos[0]->Integral(0,histos[0]->GetNbinsX()+1)<<endl;
		if (files==nfiles-1) out_efficiency<<"Total BG"<<"\t \t \t  "<<std::setprecision(8)<<totalBG<<endl;
		if (files==nfiles-1) out_efficiency<<"Total MC"<<"\t \t \t  "<<std::setprecision(8)<<totalMC<<endl;
		if (files==nfiles-1) out_efficiency<<"Data/MC"<<"\t \t \t  "<<std::setprecision(3)<<totalData/totalMC<<endl;
		if (files==nfiles-1) out_efficiency<<"QCD MC scaled with "<<"\t \t \t  "<<std::setprecision(13)<<ratio[0]<<endl;
files++;
}while (files<nfiles);
out_efficiency.close();


/////////////////////////////////////



for (int hist=0;hist<nhistos;hist++){
	hBkgUncUp[hist] = (TH1F*)sum_histos[hist]->Clone("hBkgUncUp");
	hBkgUncLo[hist] = (TH1F*)sum_histos[hist]->Clone("hBkgUncLo");
  	hBkgVis[hist]   = (TH1F*)sum_histos[hist]->Clone("hbkgVis");
  	for(int i=0;i<hBkgUncUp[hist]->GetNbinsX();i++) {
  		float e = 0.0;
    	if (sum_histos[hist]->GetBinContent(i+1) != 0) {
      	e = sum_histos[hist]->GetBinError(i+1)/sum_histos[hist]->GetBinContent(i+1);
   	}
    	hBkgUncUp[hist]->SetBinContent(i+1,e);
    	hBkgUncLo[hist]->SetBinContent(i+1,-e);
	}
  	hBkgVis[hist]->SetMarkerSize(0);
 	hBkgVis[hist]->SetFillColor(kBlack);
 	hBkgVis[hist]->SetFillStyle(3004);
 	hBkgUncUp[hist]->SetLineColor(kBlack);
 	hBkgUncUp[hist]->SetLineWidth(1);
 	hBkgUncUp[hist]->SetFillColor(kBlack);
 	hBkgUncUp[hist]->SetFillStyle(3004);
	hBkgUncLo[hist]->SetLineColor(kBlack);
 	hBkgUncLo[hist]->SetLineWidth(1);
  	hBkgUncLo[hist]->SetFillColor(kBlack);
	hBkgUncLo[hist]->SetFillStyle(3004);
}

Float_t TSF[2] = {1.,1.};
Float_t kfactors[2] = {0.,0.};
//kfactors[set_type] = 1./(MC_data[set_type] * TSF[set_type]);
kfactors[set_type] = 1./(ratio[0] * TSF[set_type]);
//cout<<"kfactor = "<<kfactors[set_type]<<endl;
//cout<<"Data/MC = "<< MC_data[set_type]<<endl;


leg->AddEntry(histos_for_legened[order_legend[0]],leg_names[0],"P");
leg->AddEntry(histos_for_legened[order_legend[nfiles-1]],leg_names_signals[0],"L");
leg->AddEntry(histos_for_legened[order_legend[nfiles-2]],leg_names_signals[1],"L");
for (int i=0;i<nfiles-3;i++){
	if (i>=bg_begin) leg->AddEntry(histos_for_legened[order_legend[i]],leg_names[i],"F");
}
TString tmp_str;
leg->AddEntry(histos_for_legened[nfiles-3],tmp_str.Format("QCD (#times %2.2f)",ratio[0]),"F");
leg->AddEntry(hBkgUncUp[0],"MC stat. unc.","F");



for (int d=0;d<nhistos;d++){
	discriminators[d] = Discr(discr_histos[d],signal_histos2[d]);
}

bubblesort(discriminators, hist_names_sort,nhistos);

out_discrimination.open(dir_name+"discrimination.txt");
for (int d=0;d<nhistos;d++){
	if (d==0) out_discrimination<<"Variable &\t d"<<endl;
	out_discrimination<<"$"<<hist_names_sort[d]<<"$"<<" & \t "<< std::setprecision(2)<< discriminators[d]<<endl;
}
out_discrimination.close();

TLatex* tex = new TLatex(0.75,0.95,"35.9 fb^{-1} (13 TeV)");
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
TLatex* tex2 = new TLatex(0.27,0.89,"Work in progress");
tex2->SetNDC();
tex2->SetTextAlign(20);
tex2->SetTextFont(52);
tex2->SetTextSize(0.035);
tex2->SetLineWidth(2);
TString temp_str;
temp_str.Form("%2.2f",kfactors[set_type]);
//		temp_str.Form("%2.2f",(1./MC_data[set_type]));
TString k_factor_str;
TLatex* tex_set = new TLatex(0.667,0.86,set_names[set_type]);
tex_set->SetNDC();
tex_set->SetTextAlign(20);
tex_set->SetTextFont(42);
tex_set->SetTextSize(0.03);
tex_set->SetLineWidth(2);
TLatex* tex_k = new TLatex(0.63,0.89,k_factor_str);
tex_k->SetNDC();
tex_k->SetTextAlign(20);
tex_k->SetTextFont(42);
tex_k->SetTextSize(0.03);
tex_k->SetLineWidth(2);
	float left2 = gStyle->GetPadLeftMargin();
	float right2 = gStyle->GetPadRightMargin();
	float top2 = gStyle->GetPadTopMargin();
	float bottom2 = gStyle->GetPadBottomMargin();
	TPaveText pCMSset(0.57,1.-top2*2.,0.67,0.92,"NDC");
	pCMSset.SetTextFont(42);
	pCMSset.SetTextSize(top2*0.75);
	pCMSset.SetTextAlign(12);
	pCMSset.SetFillStyle(-1);
	pCMSset.SetBorderSize(0);
	pCMSset.AddText(set_names[set_type]);


	

for (int i=0;i<nhistos;i++){
//	for (int i=0;i<4;i++){
		//temp_str.Form("%2.2f",Discr(discr_histos[i],signal_histos2[i]));
		Float_t d_value = Discr((TH1F*)data_histos[i]->Clone("data2"),signal_histos2[i]);
		temp_str.Form("%2.2f",d_value);
		TString disc_value = temp_str.Prepend(" d = ");
		TLatex *disc_value_text = new TLatex(0.62,0.83,disc_value);
      disc_value_text->SetNDC();
     	disc_value_text->SetTextAlign(20);
      disc_value_text->SetTextFont(42);
      disc_value_text->SetTextSize(0.03);
      disc_value_text->SetLineWidth(2);
		
		temp_str.Form("%2d",i);
		TString can_name="c1";
		can_name.Append(temp_str);
		TCanvas *c1 = new TCanvas(can_name,"",900,750);
		c1->cd();
		gPad->SetLogy(0);
		c1->SetBottomMargin(.3);
		c1->SetRightMargin(.25);
	
	//	bool LOGY=false;
	///	if (hist_names[i].CompareTo("hMqq")==0) LOGY=true; 
	//	if (hist_names[i].CompareTo("hqq_pt")==0) LOGY=true; 
		bool LOGY=true;

		
		Double_t xmin = signal_histos[i]->GetBinCenter(0);
		Double_t xmax = signal_histos[i]->GetBinCenter(signal_histos[i]->GetNbinsX())+signal_histos[i]->GetBinWidth(signal_histos[i]->GetNbinsX());
		if (hist_names[i].CompareTo("hPVs")==0) {
			xmax=30;
			LOGY=false;
		}
		string tmp_hist_name = hist_names[i].Data();
		TH1F *frame = new TH1F("frame","",1,xmin,xmax);
		TGaxis::SetExponentOffset(-0.07,0,"xy");
		frame->Reset();
		frame->SetMinimum(1E-01);
      frame->SetMaximum(std::max(data_histos[i]->GetMaximum()*1.2,sum_histos[i]->GetMaximum()*1.2) );
		if (LOGY==true) {
			gPad->SetLogy();	
      	frame->SetMaximum(std::max(data_histos[i]->GetMaximum()*100,sum_histos[i]->GetMaximum()*100) );
			if (hist_names[i].CompareTo("hHT")==0) frame->SetMaximum(sum_histos[i]->GetMaximum()*100 );
		}
		TGaxis::SetMaxDigits(4);
      frame->GetXaxis()->SetTitleOffset(0.91);
      frame->SetStats(0);
		frame->GetYaxis()->SetNdivisions(505);
	 	frame->GetXaxis()->SetLabelSize(0.0);
		char name[1000];
		if (tmp_hist_name.find("GeV")==std::string::npos) {
			if (data_histos[i]->GetBinWidth(1)>1) sprintf(name,"Events / %1.0f",data_histos[i]->GetBinWidth(1));
			else sprintf(name,"Events / %1.2f",data_histos[i]->GetBinWidth(1));
		} else {
      	sprintf(name,"Events / %1.0f %s",data_histos[i]->GetBinWidth(1),"GeV");
		}
		frame->GetYaxis()->SetTitle(name);

      frame->Draw();
		tex->Draw();
		tex1->Draw();
		tex2->Draw();
	pCMSset.Draw("same");
	//	tex_k->Draw();
//		tex_set->Draw();
		if ((d_value>0.1)&&(d_value<1.)) disc_value_text->Draw();
    	stacks[i]->Draw("same");	
		signal_histos[i]->Draw("same");
		gf_histos[i]->Draw("same");
/////////////////cross check of stupid THStack//////
//
//		sum_histos[i]->SetLineColor(kCyan);
//		sum_histos[i]->Scale(lumi);
//		sum_histos[i]->Draw("Lsame");
//
///////////////////////////////////////////////////
		data_histos[i]->Draw("Psame");
		hBkgVis[i]->Draw("same E2");

		leg->Draw("same");
	//	leg2->Draw("same");
  		gPad->RedrawAxis();
	
  		TPad* pad2 = new TPad("pad2", "pad2", 0., 0., 1., 1.);
 		pad2->SetTopMargin(0.73);
 		pad2->SetRightMargin(0.25);
 		pad2->SetFillColor(0);
  		pad2->SetFillStyle(0);
  		pad2->Draw();
  		pad2->cd(0);
  		gPad->SetGridy();

		TH1F *frame2 = new TH1F("frame2","",1,xmin,xmax);
		frame2->SetMinimum(-.5);
      frame2->SetMaximum(.5);
      frame2->SetStats(0);
      frame2->SetTitleFont(42,"x");
		frame2->SetTitleFont(42,"y");
      frame2->SetTitleSize(0.13, "XYZ");
		frame2->GetYaxis()->SetNdivisions(505);
 		frame2->GetYaxis()->SetTickLength(0.06);
  		frame2->GetYaxis()->SetTitleSize(0.04);
  		frame2->GetYaxis()->SetTitleOffset(1.5);
 		frame2->GetYaxis()->SetLabelSize(0.03);
  		frame2->GetYaxis()->CenterTitle(kTRUE);
  		frame2->GetXaxis()->SetTitleSize(0.05);
  		frame2->GetXaxis()->SetLabelSize(0.04);
		frame2->SetXTitle(signal_histos[i]->GetXaxis()->GetTitle());
		frame2->SetYTitle("Data / MC - 1");
		frame2->Draw();	

 		Double_t aa[2] = {xmin,xmax};
   	Double_t bb[2] = {0,0};
   	TGraph *cons = new TGraph(2,aa,bb);
    	cons->SetLineStyle(2);
		cons->Draw("Lsame");
		

		data_histos2[i] = (TH1F*)data_histos[i]->Clone("new");
		float chi2_data_mc = data_histos2[i]->Chi2Test(sum_histos[i],"UWCHI2/NDF");
		float ks = data_histos2[i]->KolmogorovTest(sum_histos[i]);
		data_histos2[i]->Add(sum_histos[i],-1);
		data_histos2[i]->Divide(sum_histos[i]);
		for (int j=0;j<data_histos2[i]->GetNbinsX();j++){
			if (sum_histos[i]->GetBinContent(j+1)!=0) data_histos2[i]->SetBinError(j+1, TMath::Sqrt(data_histos[i]->GetBinContent(j+1))/sum_histos[i]->GetBinContent(j+1)) ;
			else if (data_histos[i]->GetBinContent(j+1)!=0) data_histos2[i]->SetBinError(j+1, TMath::Sqrt(data_histos[i]->GetBinContent(j+1))/data_histos[i]->GetBinContent(j+1)) ;
					else data_histos2[i]->SetBinError(j+1,0.); 
		}
		data_histos2[i]->Draw("PEsame");
		hBkgUncUp[i]->Draw("HIST same");
		hBkgUncLo[i]->Draw("HIST same");
		
		temp_str.Form("%2.2f",chi2_data_mc);
		TString chi2_str = temp_str.Prepend("#chi^{2} = ");
		TLatex *chi2_latex = new TLatex(0.21,0.23,temp_str);
 	  	chi2_latex->SetNDC();
  	 	chi2_latex->SetTextAlign(20);
  		chi2_latex->SetTextFont(42);
   	chi2_latex->SetTextSize(0.025);
   	chi2_latex->SetLineWidth(2);
		chi2_latex->Draw();
		temp_str.Form("%2.2f",ks);
		TString ks_str = temp_str.Prepend(", KS = ");
		TLatex *ks_latex = new TLatex(0.31,0.23,temp_str);
 	  	ks_latex->SetNDC();
  	 	ks_latex->SetTextAlign(20);
  		ks_latex->SetTextFont(42);
   	ks_latex->SetTextSize(0.025);
   	ks_latex->SetLineWidth(2);
		ks_latex->Draw();

		pad2->RedrawAxis();
		c1->Print(output_names[i]);
		c1->Delete();
	}



return 0;
}
