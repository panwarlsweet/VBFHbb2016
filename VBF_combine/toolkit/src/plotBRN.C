#include <string>

using namespace RooFit;
void plotBRN(float BIN_SIZE=5.0,bool BLIND=false,TString MASS="125",TString NAME="",TString saveNAME="")
{
 // gROOT->ProcessLine(".x ../../common/styleCMSTDR.C");
  gROOT->ProcessLine(".x /afs/cern.ch/work/n/nchernya/Hbb/setTDRStyle.C");
  gSystem->Load("libHiggsAnalysisCombinedLimit.so");
  gROOT->ForceStyle();
  gStyle->SetOptStat(0);
  gStyle->SetOptTitle(0);
  gROOT->SetBatch(1);
  gStyle->SetPadRightMargin(0.04);
  gStyle->SetPadLeftMargin(0.16);
  gStyle->SetPadTopMargin(0.06);
  gStyle->SetPadBottomMargin(0.10);
  gStyle->SetTitleFont(42,"XY");
  gStyle->SetTitleSize(0.0475,"XY");
  gStyle->SetTitleOffset(0.9,"X");
  gStyle->SetTitleOffset(1.5,"Y");
  gStyle->SetLabelSize(0.0375,"XY");

  RooMsgService::instance().setSilentMode(kTRUE);
  for(int i=0;i<2;i++) {
    RooMsgService::instance().setStreamStatus(i,kFALSE);
  }
  float XMIN = 80;
  float XMAX = 200; 
/*
  TFile *f1 = TFile::Open("datacards/datacard_m"+MASS+"_"+NAME+".root");
  TFile *f2 = TFile::Open("combine/mlfit.vbfHbb_"+NAME+"_mH"+MASS+".root");
  TFile *f3 = TFile::Open("root/sig_shapes_workspace_B80-200.root");
  TFile *f4 = TFile::Open("root/data_shapes_workspace_"+NAME+".root");*/
  TFile *f1 = TFile::Open("test_Signal/datacards/datacard_vbfHbb_names_m125.root");
  TFile *f20 = TFile::Open("test_Signal/run_from/mlfitcat00.root");
  TFile *f21 = TFile::Open("test_Signal/run_from/mlfitcat01.root");
  TFile *f22 = TFile::Open("test_Signal/run_from/mlfitcat02_veto1.root");
  TFile *f2double = TFile::Open("test_Signal/run_from/mlfitcat02.root");
	TString f2_names[4]={"cat00","cat01","cat02_veto1","cat02"};
  TFile *f3 = TFile::Open("test_Signal/root//sig_shapes_workspace_2016.root");
  TFile *f4 = TFile::Open("test_Signal//root/data_shapes_workspace_2016.root");
/*  TFile *f1 = TFile::Open("/datacards/datacard_vbfHbb_m125"+NAME+"_woPS_woScale.root");
  TFile *f2 = TFile::Open("unblind_preparation/mlfitunblinded_woPS_woScale"+NAME+".root");
  TFile *f3 = TFile::Open("new/root/sig_shapes_workspace.root");
  TFile *f4 = TFile::Open("new/root/data_shapes_workspace.root");
*/
  RooWorkspace *w = (RooWorkspace*)f1->Get("w");
  //w->Print();
int increment=0;
    TCanvas* canFit = new TCanvas("Higgs_fit","Higgs_fit",900,750);
    TLegend *leg = new TLegend(0.70,0.61,0.94,1.-gStyle->GetPadTopMargin()-0.01);
  for (int name_order=0;name_order<4;name_order++){
	TFile *f2_new = TFile::Open("test_Signal/run_from/mlfit"+f2_names[name_order]+".root");
  RooAbsPdf *bkg_model = (RooAbsPdf*)w->pdf("model_s");
  RooFitResult *res_s  = (RooFitResult*)f2_new->Get("fit_s"); 
  RooFitResult *res_b  = (RooFitResult*)f2_new->Get("fit_b");
  RooRealVar *rFit     = dynamic_cast<RooRealVar *>(res_s->floatParsFinal()).find("r");
  RooDataSet *data     = (RooDataSet*)w->data("data_obs");
  
  int nparS=0,nparB=0;
  cout << res_s->floatParsFinal().getSize() << endl;
  cout << res_b->floatParsFinal().getSize() << endl;
  nparS = res_s->floatParsFinal().getSize();
  nparB = res_b->floatParsFinal().getSize();  
  float chi2sumS = 0.;
  float chi2sumB = 0.;
  int nparsum = 0;
//  if (BLIND) {
//    res_b->Print();
//  }
//  else {
//    res_s->Print();
//  }
  
  w->allVars().assignValueOnly(res_s->floatParsFinal());
//  w->Print();
//  w->allVars()->Print();

  RooWorkspace *wSig = (RooWorkspace*)f3->Get("w"); 
  RooWorkspace *wDat = (RooWorkspace*)f4->Get("w"); 

  const RooSimultaneous *sim = dynamic_cast<const RooSimultaneous *> (bkg_model);
  const RooAbsCategoryLValue &cat = (RooAbsCategoryLValue &) sim->indexCat();
  TList *datasets = data->split(cat,true);
	cout<<	datasets->GetSize()<<endl;
  TIter next(datasets);
  //int count = 0; 
//  for(RooAbsData *ds = (RooAbsData*)next();ds != 0; ds = (RooAbsData*)next()) {
  	RooAbsData *ds = (RooAbsData*)next();
	 //if (count > 0) return 0;
	 //count++;
    RooAbsPdf *pdfi = sim->getPdf(ds->GetName());
    RooArgSet *obs = (RooArgSet*)pdfi->getObservables(ds);
    RooRealVar *x = dynamic_cast<RooRealVar *>(obs->first());

    TString ds_name(ds->GetName());
	cout<<ds_name<<endl;
    //----- get the QCD normalization -----------
    RooRealVar *qcd_norm_final = dynamic_cast<RooRealVar *>(res_s->floatParsFinal()).find("CMS_vbfbb_qcd_norm_"+ds_name+"_13TeV");
    RooRealVar *qcd_yield      = (RooRealVar*)wDat->var("yield_data_"+ds_name);

    float Nqcd  = exp(log(1.5)*qcd_norm_final->getVal())*qcd_yield->getVal();
    float eNqcd = log(1.5)*qcd_norm_final->getError()*Nqcd;
    cout<<"QCD normalization = "<<Nqcd<<" +/- "<<eNqcd<<endl;
    
    TH1 *hCoarse = (TH1*)ds->createHistogram("coarseHisto_"+ds_name,*x);
    float norm = hCoarse->Integral();
  
	 int rebin = BIN_SIZE/hCoarse->GetBinWidth(1);
    hCoarse->Rebin(rebin);

    float MIN_VAL = TMath::Max(0.9*hCoarse->GetBinContent(hCoarse->GetMinimumBin()),1.0);
 //   float MIN_VAL = 1.;
//    float MAX_VAL = Nzjets+Ntop;
    float MAX_VAL = 1.3*hCoarse->GetBinContent(hCoarse->GetMaximumBin());
    RooDataHist ds_coarse("ds_coarse_"+ds_name,"ds_coarse_"+ds_name,*x,hCoarse);
    
    RooHist *hresid,*hresid0;
    RooPlot *frame1 = x->frame();
    RooPlot *frame2 = x->frame();
    
		//cout << "Non-blind case: " << ds_coarse.GetName() << endl;
	//	ds_coarse.plotOn(frame1);
     // pdfi->plotOn(frame1);
		//cout << pdfi->getParameters(ds_coarse)->selectByAttrib("Constant",kFALSE)->getSize() << endl;
    //  cout<<"chi2/ndof (bkg+sig) = "<<frame1->chiSquare()<<endl;
//		cout << ds_coarse.numEntries() << endl;
//		chi2sumS += frame1->chiSquare()*ds_coarse.numEntries();
//		nparsum += ds_coarse.numEntries();
		//hresid0 = frame1->residHist();
      //pdfi->plotOn(frame1,VisualizeError(*res_s,1,kTRUE),FillColor(0),MoveToBack());
      pdfi->plotOn(frame2,Components("shapeBkg_qcd_"+ds_name),LineWidth(2),LineStyle(increment),LineColor(increment+1));


		RooArgList brn_params;
		RooRealVar brn[6];
	//	for (int ii=0;ii<6;ii++){
	//		brn[ii] = new RooRealVar(TString::Format("brn%d",increment),TString::Format("brn%d",increment),0.5,0,1000);
		//	brn_params.add(brn[ii]);
	//		brn[ii]->setConstant(kTRUE);
//		}
		RooRealVar brn0("brn0","brn0",0.5,0,1000);
		RooRealVar brn1("brn1","brn1",0.5,0,1000);
		RooRealVar brn2("brn2","brn2",0.5,0,1000);
		RooRealVar brn3("brn3","brn3",0.5,0,1000);
		RooRealVar brn4("brn4","brn4",0.5,0,1000);
		RooRealVar brn5("brn5","brn5",0.5,0,1000);
		brn0.setConstant(kTRUE);
		brn1.setConstant(kTRUE);
		brn2.setConstant(kTRUE);
		brn3.setConstant(kTRUE);
		brn4.setConstant(kTRUE);
		brn5.setConstant(kTRUE);
		brn_params.add(brn0);
		brn_params.add(brn1);
		brn_params.add(brn2);
		brn_params.add(brn3);
		brn_params.add(brn4);
		brn_params.add(brn5);
		brn0.setVal(1.0443e+02 );
		brn1.setVal(8.2507e+01);
		brn2.setVal( 6.0351e+01);
		brn3.setVal(6.1431e+01);
		brn4.setVal( 4.7728e+01);
		brn5.setVal( 3.9773e+01);
//		for (int ii=0;ii<6;ii++)
	//		brn_params.add(brn[ii]);
	//	RooBernstein *qcd_pdf_aux = new RooBernstein("qcd_model","qcd_model",x,RooArgList(&brn[0],&brn[1],&brn[2],&brn[3],&brn[4],&brn[5]));
		RooBernstein qcd_pdf_aux("qcd_model","qcd_model",*x,brn_params);
	//	RooBernstein *qcd_pdf_aux = new RooBernstein("qcd_model","qcd_model",x,RooArgList(&brn[0],&brn[1],&brn[2],&brn[3],&brn[4],&brn[5]));
		if (increment==0) qcd_pdf_aux.plotOn(frame2,LineWidth(2),LineColor(kOrange));


		TH1F *fake_hist = new TH1F(TString::Format("gr_%d",increment),TString::Format("gr_%d",increment), 100,0,1);
		fake_hist->SetLineColor(increment+1);
		fake_hist->SetLineStyle(increment);
		fake_hist->SetLineWidth(2);
   //   hresid = frame1->residHist();
//      frame2->addPlotable(hresid,"pE1");
    

 //   canFit->cd(1)->SetBottomMargin(0.4);
    frame2->SetMinimum(0.0002);
    frame2->SetMaximum(0.0016);
    frame2->GetYaxis()->SetNdivisions(510);
  //  frame2->GetXaxis()->SetTitleSize(0);
  //  frame2->GetXaxis()->SetLabelSize(0);
    frame2->GetYaxis()->SetTitle(TString::Format("Events / %1.1f GeV",BIN_SIZE));
    if (increment==0)frame2->Draw();
	else frame2->Draw("same");
    gPad->Update();
    
    TList *list = (TList*)gPad->GetListOfPrimitives();
    RooCurve *errorBand,*gFit,*gQCDFit,*gBkgFit;
		gQCDFit = (RooCurve*)list->FindObject("pdf_bin"+ds_name+"_Norm[mbbReg_"+ds_name+"]"+"_Comp[shapeBkg_qcd_"+ds_name+"]");  
    //list->Print();
    TH1F *hUncH  = new TH1F("hUncH"+ds_name,"hUncH"+ds_name,(XMAX-XMIN)/BIN_SIZE,XMIN,XMAX);
    TH1F *hUncL  = new TH1F("hUncL"+ds_name,"hUncL"+ds_name,(XMAX-XMIN)/BIN_SIZE,XMIN,XMAX);
    TH1F *hUnc2H = new TH1F("hUnc2H"+ds_name,"hUnc2H"+ds_name,(XMAX-XMIN)/BIN_SIZE,XMIN,XMAX);
    TH1F *hUnc2L = new TH1F("hUnc2L"+ds_name,"hUnc2L"+ds_name,(XMAX-XMIN)/BIN_SIZE,XMIN,XMAX); 
    TH1F *hUncC  = new TH1F("hUncC"+ds_name,"hUncC"+ds_name,(XMAX-XMIN)/BIN_SIZE,XMIN,XMAX); 
    
    
	//list->Print();
      //errorBand = (RooCurve*)list->FindObject("pdf_bin"+ds_name+"_Norm[mbbReg_"+ds_name+"]_errorband");
      errorBand = (RooCurve*)list->FindObject("pdf_bin"+ds_name+"_Norm[mbbReg_"+ds_name+"]_errorband_Comp[shapeBkg_qcd_"+ds_name+",shapeBkg_top_"+ds_name+",shapeBkg_zjets_"+ds_name+"]");
      gFit = (RooCurve*)list->FindObject("pdf_bin"+ds_name+"_Norm[mbbReg_"+ds_name+"]");
    
/*    for(int i=0;i<hUncH->GetNbinsX();i++) {
      double x0 = hUncH->GetBinCenter(i+1);
      double e1 = fabs(errorBand->Eval(x0)-gBkgFit->Eval(x0));
      //double e1 = fabs(errorBand->Eval(x0)-gFit->Eval(x0));
      double e2 = eNqcd/hUncH->GetNbinsX();
      hUncH->SetBinContent(i+1,sqrt(pow(e2,2)+pow(e1,2)));
      hUnc2H->SetBinContent(i+1,2*sqrt(pow(e2,2)+pow(e1,2)));
      hUncL->SetBinContent(i+1,-sqrt(pow(e2,2)+pow(e1,2)));
      hUnc2L->SetBinContent(i+1,-2*sqrt(pow(e2,2)+pow(e1,2)));
		hUncC->SetBinContent(i+1,0.);
    }
   */
/*    TPad* pad = new TPad("pad", "pad", 0., 0., 1., 1.);
    pad->SetTopMargin(0.63);
    pad->SetFillColor(0);
    pad->SetFillStyle(0);
    pad->Draw();
    pad->cd(0);*/
//    hUnc2H->GetXaxis()->SetTitle("m_{bb} (GeV)");
//    hUnc2H->GetYaxis()->SetTitle("Data - Bkg");
    //hUnc2H->GetYaxis()->SetTitle("Data - Fit");
    double YMAX = 1.1*frame2->GetMaximum();
    double YMIN = -1.1*frame2->GetMaximum();
//    hUnc2H->GetYaxis()->SetRangeUser(YMIN,YMAX);
 //   hUnc2H->GetYaxis()->SetNdivisions(507);
//    hUnc2H->GetXaxis()->SetTitleOffset(0.9);
//    hUnc2H->GetYaxis()->SetTitleOffset(1.0);
 //   hUnc2H->GetYaxis()->SetTickLength(0.0);
//    hUnc2H->GetYaxis()->SetTitleSize(0.05);
//    hUnc2H->GetYaxis()->SetLabelSize(0.04);
/*    hUnc2H->GetYaxis()->CenterTitle(kTRUE);
    hUnc2H->SetFillColor(kGreen);
    hUnc2L->SetFillColor(kGreen);
    hUncH->SetFillColor(kYellow);
    hUncL->SetFillColor(kYellow);
	 hUncC->SetLineColor(kBlack);
	 hUncC->SetLineStyle(7);
    hUnc2H->Draw("HIST");
    hUnc2L->Draw("same HIST");
    hUncH->Draw("same HIST");
    hUncL->Draw("same HIST");
	 hUncC->Draw("same HIST");*/
	 frame2->GetYaxis()->SetTickLength(0.03/0.4);
    frame2->Draw("same");

    TList *list1 = (TList*)gPad->GetListOfPrimitives();
    //list1->Print();

	 //leg->SetHeader(ds_name+" (m_{H}="+MASS+")");
//    leg->SetHeader(TString::Format("CAT %d",atoi(ds_name(3,1).Data())+1));
//    leg->SetHeader(TString::Format("CAT %d",atoi(ds_name(3,1).Data())));
 //   leg->AddEntry(hBlind,"Data","P");
	 
	TLine *gEmpty = new TLine(0.0,0.0,0.0,0.0);
	 gEmpty->SetLineWidth(0);
//	 TLegendEntry *l1 = leg->AddEntry(gEmpty,"(m_{H} = "+MASS+" GeV)","");
//	 l1->SetTextSize(0.038*0.97*0.85);
	 leg->SetTextFont(42);
	 leg->SetFillStyle(-1);
   leg->SetFillColor(0);
    leg->SetBorderSize(0);
    leg->SetTextFont(42);
    leg->SetTextSize(0.038*0.98);
 //  leg->AddEntry(gQCDFit,TString::Format("From CAT 0-%d",increment),"L");
   leg->AddEntry(fake_hist,TString::Format("From CAT 0-%d",increment),"L");
  //  if (increment>=0) leg->AddEntry(gQCDFit,"line","L");
 //   leg->AddEntry(gZTFit,"ZT","L");
 //   leg->AddEntry(hUnc2H,"2#sigma bkg. unc.","F");
 //   leg->AddEntry(hUncH,"1#sigma bkg. unc.","F");
     
// CMS info
	float left2 = gStyle->GetPadLeftMargin();
	float right2 = gStyle->GetPadRightMargin();
	float top2 = gStyle->GetPadTopMargin();
	float bottom2 = gStyle->GetPadBottomMargin();
	TPaveText *paveCMS = new TPaveText(left2,1.-top2,0.4,1.,"NDC");
   // TPaveText *paveCMS = new TPaveText(gStyle->GetPadLeftMargin()+0.02,0.7,gStyle->GetPadLeftMargin()+0.15,1.-gStyle->GetPadTopMargin()-0.01,"NDC");
	 paveCMS->SetTextFont(62);
	 paveCMS->SetTextSize(gStyle->GetPadTopMargin()*3./4.);
	 paveCMS->SetBorderSize(0);
	 paveCMS->SetFillStyle(-1);
	 paveCMS->SetTextAlign(12);
	 paveCMS->AddText("CMS");
	 paveCMS->Draw();
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

	 TString path=".";
	 //TString path="BiasV10_limit_BRN5p4_dX0p1_B80-200_CAT0-6/output/";
	 system(TString::Format("[ ! -d %s/plot_brn ] && mkdir %s/plot",path.Data(),path.Data()).Data());
//	 canFit->SaveAs(TString::Format("%s/plot/fits/Fit_mH%s_%s_%s.pdf",path.Data(),MASS.Data(),ds_name.Data()).Data(),NAME.Data());
//	 canFit->SaveAs(TString::Format("%s/plot/fits/Fit_mH%s_%s_%s.png",path.Data(),MASS.Data(),ds_name.Data()).Data()),NAME.Data();
//	 canFit->SaveAs(TString::Format("%s/plot/fits/Fit_mH%s_%s_%s.eps",path.Data(),MASS.Data(),ds_name.Data()).Data(),NAME.Data());
	// TText *l = (TText*)paveCMS->AddText("Preliminary");
	// l->SetTextFont(52);
	// paveCMS->Draw();
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
   if (increment==3){ 	
		leg->Draw(); 
		leg->SetY1(leg->GetY2()-leg->GetNRows()*0.045*0.96);
	 		canFit->SaveAs(TString::Format("%s/plot_brn/Fit_mH%s_%s_double_separate_qcd.png",path.Data(),MASS.Data(),NAME.Data()).Data());
	}
	//	if (!(ds_name.CompareTo(saveNAME))){
//	}
		increment++;
    delete ds;
  }
	// canFit->SaveAs(TString::Format("%s/plot_brn/Fit_mH%s_%s_%s_qcd.png",path.Data(),MASS.Data(),ds_name.Data(),NAME.Data()).Data());
  delete datasets; 
}
