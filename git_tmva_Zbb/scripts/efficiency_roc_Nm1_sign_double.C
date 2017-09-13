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
#include "algorithm"
#include "TProfile.h"

//int main(){
void efficiency_roc_Nm1_sign_double(){
	gROOT->ProcessLine(".x /afs/cern.ch/work/n/nchernya/setTDRStyle.C");
	const int n_variables =7  ;
//	TString variables_names[n_variables]={"Mqq", "DeltaEtaQQ", "DeltaPhiQQ", "SoftN5","CMVAV2_1", "CMVAV2_2" , "DeltaEtaQB",  "Jet5_pt", "qgl1", "qgl2", "qqbb_pt","qqbb_pz", "all"};  
//	TString variables_names[n_variables]={"Mqq", "DeltaEtaQQ", "DeltaPhiQQ",  "SoftN5","CMVAV2_1", "CMVAV2_2" ,  "DeltaEtaQB", "Jet5_pt", "qgl1", "qgl2","qqbb_pz", "all"};  
//	TString variables_names[n_variables]={ "DeltaEtaQQ", "CMVAV2_2" , "DeltaEtaQB",  "qgl1", "qgl2", "EtaBB", "all"};  
	TString variables_names[n_variables]={ "DeltaEtaQQ", "CMVAV2_2" ,"DeltaEtaQB",  "qgl1", "qgl2", "EtaBB", "all"};  
	TString file_names[n_variables];
	TString file_names_single[n_variables];
	Double_t frame2_axisx[n_variables];
	for (int i=0;i<n_variables;i++){
		frame2_axisx[i] = 0.5+i;
	}

	TString end = "BDTIncl_try5";
	TString v="v25";

	Double_t hist_integrals[n_variables];
	Double_t hist_integrals_single[n_variables];
	for (int i=0;i<n_variables;i++){
//		file_names[i].Prepend("dcap://t3se01.psi.ch:22125//pnfs/psi.ch/cms/trivcat/store/user/nchernya/VBFHbb2016/tmva_output//output/"+v+"/TMVA_main_"+v+"_Nm1_"+variables_names[i]);
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
	//	TH1D *hist_S = (TH1D*) MVA_BDTG_S->Clone(); 	
		TH1D *hist_S = (TH1D*)file->Get("Method_BDT/BDTG/MVA_BDTG_S"); 
		hist_S->Scale( 1./hist_S->Integral() );
		hist_S->Scale(47065.135);
		TH1D *hist_B = (TH1D*)file->Get("Method_BDT/BDTG/MVA_BDTG_B"); 
	//	TH1D *hist_B = (TH1D*) MVA_BDTG_B->Clone();
		hist_B->Scale( 1./hist_B->Integral() );
		hist_B->Scale(17488845.);
/*		if (current_file==n_variables-1){
			TCanvas * c_test = new TCanvas();
//			gPad->SetLogy(1);
			hist_B->Draw("AXIS HIST");
//			hist_B->SetMinimum(1e-02);
			hist_B->Draw("HIST SAME");
			hist_S->Draw("HIST SAME");
			
			TTree *treeTrain = (TTree*)file->Get("TrainTree");
			TH1F *hist_bdt_purity;	 
			TH1F *hist_b_signal = new TH1F("hbdt_signal","",100,-1,1.);	 
			TH1F *hist_b_bg = new TH1F("hbdt_bg","",100,-1,1.);	 
			TH1F *hist_b_purity;	 
			TProfile *hprof = new TProfile("hprof","",100,-1,1,0,200);
			float bdt;
			int index;
			float weight;
			float Mbb;
			treeTrain->SetBranchAddress("BDTG",&bdt);
			treeTrain->SetBranchAddress("classID",&index);
			treeTrain->SetBranchAddress("weight",&weight);
			treeTrain->SetBranchAddress("Mbb",&Mbb);
			for (int evt=0;evt<treeTrain->GetEntries();evt++){
				treeTrain->GetEntry(evt);
				if (index==0) hist_b_signal->Fill(bdt,weight);
				if (index==1) hist_b_bg->Fill(bdt,weight);
				if (index==1) hprof->Fill(bdt,Mbb);
			}
			TCanvas * c_purity2 = new TCanvas();
			cout<<hist_b_signal->Integral()<<endl;
			cout<<hist_b_bg->Integral()<<endl;
			hist_b_purity=(TH1F*)hist_b_signal->Clone("purity");
			hist_b_purity->Divide(hist_b_bg);
			hist_b_purity->Draw("AXIS HE");
			hist_b_purity->SetLineWidth(2);
			hist_b_purity->Draw("HE same");
			c_purity2->Print("plots/"+v+"/purity_double_"+end+".png");
			TCanvas * c_prof = new TCanvas();
			hprof->GetYaxis()->SetRangeUser(40,140);
			hprof->Draw("AXIS HE");
			hprof->SetLineWidth(2);
			hprof->Draw("HE same");
			c_prof->Print("plots/"+v+"/profile_double_"+end+".png");
			
			
		}
*/
//			gPad->SetLogy(0);
		int i=0; 
		double max=0; double max_single=0;
		double s1=0; double s1_single=0;
		double b1=0; double b1_single=0;
		double bin=-1.; double bin_single=-1;
		double END = hist_B->GetNbinsX(); //right end of BDT distibution
		do	{
			s1=hist_S->GetBinContent(i+1);
			b1=hist_B->GetBinContent(i+1);
			bin=(double) hist_S->GetBinCenter(i+1+1);
			if ((s1+b1) > 0) max += pow(s1,2)/(b1+s1);
//			cout<<s1<<" , "<<b1+s1<<" , "<<max<<endl;
			i++;
		} while (bin < END);
 
		hist_integrals[current_file] = TMath::Sqrt(max);



}
		TCanvas *c2 = new TCanvas();
		c2->SetBottomMargin(.12);
		c2->cd();
		TH1F *frame2 = new TH1F("frame2","",n_variables,0.,n_variables);
		frame2->SetMinimum(0.81);
      frame2->SetMaximum(.84);
      frame2->SetMinimum(hist_integrals[0]*0.8);
      frame2->SetMaximum(hist_integrals[n_variables-1]*1.2);
      frame2->GetYaxis()->SetTitleOffset(1.4);
      frame2->GetXaxis()->SetTitleOffset(1.);
      frame2->SetStats(0);
      frame2->SetTitleFont(42,"x");
		frame2->SetTitleFont(42,"y");
      frame2->SetTitleSize(0.05, "XYZ");
		frame2->SetYTitle("S/#sqrt{S+B}");
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
		c2->Print("plots/"+v+"/efficiency_Sign_"+v+"_Nm1_double_"+end+".png");

}
