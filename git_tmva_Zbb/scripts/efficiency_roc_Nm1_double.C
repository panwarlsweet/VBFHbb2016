#include <TH1D.h>
#include <TStyle.h>
#include <TCanvas.h>
#include "TLorentzVector.h"
#include <iomanip>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "TFile.h"
#include "TROOT.h"

//int main(){
void efficiency_roc_Nm1_double(){
	gROOT->ProcessLine(".x /afs/cern.ch/work/n/nchernya/setTDRStyle.C");
	const int n_variables =6 ;
//	TString variables_names[n_variables]={"Mqq", "DeltaEtaQQ", "DeltaPhiQQ", "SoftN5","CMVAV2_1", "CMVAV2_2" , "DeltaEtaQB",  "Jet5_pt", "qgl1", "qgl2", "qqbb_pt","qqbb_pz", "all"};  
//	TString variables_names[n_variables]={ "DeltaEtaQQ", "CMVAV2_2" , "DeltaEtaQB",  "qgl1", "qgl2", "EtaBB", "all"};  
	TString variables_names[n_variables]={ "DeltaEtaQQ",  "DeltaEtaQB",  "qgl1", "qgl2", "EtaBB", "all"};  
	TString file_names[n_variables];
	TString file_names_single[n_variables];
	Double_t frame2_axisx[n_variables];
	for (int i=0;i<n_variables;i++){
		frame2_axisx[i] = 0.5+i;
	}

	TString end = "BDTIncl_try6";
	Double_t hist_integrals[n_variables];
	Double_t hist_integrals_single[n_variables];
	for (int i=0;i<n_variables;i++){
//		file_names[i].Prepend("dcap://t3se01.psi.ch:22125//pnfs/psi.ch/cms/trivcat/store/user/nchernya/VBFHbb2016/tmva_output/output/v25/TMVA_main_v25_Nm1_"+variables_names[i]);
		file_names[i].Prepend("/mnt/t3nfs01/data01/shome/nchernya/VBFHbb2016/Zbb_mva/output/v25/TMVA_main_v25_Nm1_"+variables_names[i]);
		file_names_single[i] = file_names[i];
		file_names[i].Append("double"+end+".root");
		file_names_single[i].Append("single"+end+".root");
	}

	for (int current_file=0;current_file<n_variables;current_file++){
//	for (int current_file=n_variables-1;current_file>=0;current_file--){
		TFile *file = TFile::Open(file_names[current_file]);
		file->cd("Method_BDT/BDTG");
		file->ls();
	//	TH1D *hist = (TH1D*) MVA_BDTG_rejBvsS->Clone(); 
		TH1D *hist = (TH1D*)file->Get("Method_BDT/BDTG/MVA_BDTG_rejBvsS"); 
		hist_integrals[current_file] = hist->Integral("width");
		cout<<hist_integrals[current_file]<<endl;
	file->Close();	
	}


		TCanvas *c2 = new TCanvas();
		c2->SetBottomMargin(.12);
		c2->cd();
		TH1F *frame2 = new TH1F("frame2","",n_variables,0.,n_variables);
		frame2->SetMinimum(0.75);
      frame2->SetMaximum(.84);
      frame2->SetMinimum(hist_integrals[n_variables-1]*0.9);
      frame2->SetMaximum(hist_integrals[n_variables-1]*1.05);
      frame2->GetYaxis()->SetTitleOffset(1.4);
      frame2->GetXaxis()->SetTitleOffset(1.);
      frame2->SetStats(0);
      frame2->SetTitleFont(42,"x");
		frame2->SetTitleFont(42,"y");
      frame2->SetTitleSize(0.05, "XYZ");
		frame2->SetYTitle("ROC Area");
		frame2->SetXTitle("");	
		frame2->GetXaxis()->SetLabelSize(0.05);
		for (int i=0;i<n_variables;i++){
			frame2->GetXaxis()->SetBinLabel(i+1,variables_names[i]);
		}
		frame2->Draw();
		TGraph *gr = new TGraph(n_variables,frame2_axisx,hist_integrals);
		gr->SetMarkerStyle(20);
		gr->SetLineWidth(2);
		gr->Draw("PLsame");
		TLegend *leg = new TLegend(0.7,0.86,0.9,0.9);
		leg->SetFillColor(0);
		leg->SetBorderSize(0);
		leg->SetTextSize(0.04);
		leg->AddEntry(gr,"Inclusive","PL");
		leg->Draw("same");
		TLine *line2 = new TLine(0.,hist_integrals[n_variables-1],(Double_t)n_variables,  hist_integrals[n_variables-1]);
		line2->SetLineStyle(2);
		line2->SetLineColor(2);
		line2->SetLineWidth(2);
		line2->Draw("Lsame");
		c2->Print("plots/v25/efficiency_v25_double_"+end+".png");


}
