import ROOT
from ROOT import gROOT
from ROOT import gStyle

gROOT.SetBatch(True)
gROOT.ProcessLineSync(".x /afs/cern.ch/work/n/nchernya/Hbb/setTDRStyle.C")
gROOT.ForceStyle()
gStyle.SetPadTopMargin(0.06)
gStyle.SetPadRightMargin(0.04)
gStyle.SetPadLeftMargin(0.15)


####### from 0,300 BRN
fdata_fit = ROOT.TFile.Open("/afs/cern.ch/work/n/nchernya/VBFHbb_2016/VBF_combine/toolkit/src/nolimit/run_from/mlfitfitToDataCAT0.root")
fAsimov = ROOT.TFile.Open("/afs/cern.ch/work/n/nchernya/VBFHbb_2016/VBF_combine/toolkit/src/nolimit/run_from/mlfitfitToDataCAT0Asimov.root")
#############freeze QCD###################
#fdata_fit = ROOT.TFile.Open("/afs/cern.ch/work/n/nchernya/VBFHbb_2016/VBF_combine/toolkit/src/nolimit/run_from/mlfitall_data_noQCD_freeze.root")
#fAsimov = ROOT.TFile.Open("/afs/cern.ch/work/n/nchernya/VBFHbb_2016/VBF_combine/toolkit/src/nolimit/run_from/mlfitall_Asimov_noQCD_freeze.root")


#data     = w.data("data_obs")
# w = fdatacard.Get("w");



files=[]

for i in range(0,100):
	#files.append("/afs/cern.ch/work/n/nchernya/VBFHbb_2016/VBF_combine/toolkit/src/nolimit/toys_Fit/all_toys//mlfittoys_2_num_%d.root"%i)
	## no options : np --minos none, no noerros
	files.append("/afs/cern.ch/work/n/nchernya/VBFHbb_2016/VBF_combine/toolkit/src/nolimit/toys_Fit/all_toys_CAT0/mlfitCAT0_2_num_%d.root"%i)
	##########freeeze QCD##########
#	files.append("/afs/cern.ch/work/n/nchernya/VBFHbb_2016/VBF_combine/toolkit/src/nolimit/toys_Fit/all_toys_freezeQCD//mlfitfreezeQCD_toys_2_num_%d.root"%i)

for cat in range(0,1):
	all_hists=[]
	all_toys_data=[]
	
#	tmp_file = ROOT.TFile.Open(files[0])
#	main_hist = tmp_file.Get("shapes_fit_s/CAT%d/total"%cat)
#	main_hist.SetBit(ROOT.TH1F.kIsAverage)
#	violin_hist = ROOT.TH2F("violin_CAT%d"%cat,"violin_CAT%d"%cat,10,80,200,10,0,10000)
#	all_hists.append(main_hist)
	
	len=0
	for num,file in enumerate(files):
		tmp_file = ROOT.TFile.Open(file)
		if tmp_file.cd("shapes_fit_b")==False : continue
		tmp_hist = tmp_file.Get("shapes_fit_b/CAT%d/total"%cat)
		for i in range(0,tmp_hist.GetNbinsX()):
			tmp_hist.SetBinContent(i+1,tmp_hist.GetBinContent(i+1)*tmp_hist.GetBinWidth(i+1))
		all_hists.append(tmp_hist)

		data_gr = tmp_file.Get("shapes_fit_b/CAT%d/data"%cat)
		data_hist = ROOT.TH1F("data_hist_CAT%d"%cat,"data_hist_CAT%d"%cat,1200,80,200)
		for bin in range(0,1200):
			tmp_x=ROOT.Double(0)
			tmp_y=ROOT.Double(0)
			data_gr.GetPoint(bin,tmp_x,tmp_y)
			data_hist.SetBinContent(bin+1,tmp_y)
			data_hist.SetBinError(bin+1,data_gr.GetErrorYhigh(bin))
			#print tmp_x, tmp_y, data_hist.GetBinCenter(bin+1),data_hist.GetBinContent(bin+1)
		for i in range(0,data_hist.GetNbinsX()):
			data_hist.SetBinContent(i+1,data_hist.GetBinContent(i+1)*data_hist.GetBinWidth(i+1))
			data_hist.SetBinError(i+1,data_hist.GetBinError(i+1)*data_hist.GetBinWidth(i+1))
		all_toys_data.append(data_hist)


		len=len+1




	c = ROOT.TCanvas("c","c",900,900)
	all_hists[0].GetYaxis().SetTitle("Events/(1 GeV)")
	all_hists[0].GetXaxis().SetTitle("M_{bb} in CAT%d (GeV)"%cat)
	all_hists[0].Rebin(50)
	all_hists[0].SetLineColor(ROOT.kGreen+2)
	all_hists[0].Draw("H")	
	for num in range(1,len):
		all_hists[num].Rebin(50)
		all_hists[num].SetLineColor(ROOT.kGreen+2)
		all_hists[num].Draw("Hsame")
	for num in range(0,len):
		all_toys_data[num].Rebin(50)
		all_toys_data[num].SetLineColor(ROOT.kCyan+1)
		all_toys_data[num].SetMarkerColor(ROOT.kCyan+1)
		all_toys_data[num].SetMarkerStyle(26)
		all_toys_data[num].SetLineStyle(2)
		all_toys_data[num].Draw("PEsame")


	Asimov_gr = fAsimov.Get("shapes_fit_b/CAT%d/data"%cat)
	Asimov_hist = ROOT.TH1F("Asimov_hist_CAT%d"%cat,"Asimov_hist_CAT%d"%cat,1200,80,200)
	for bin in range(0,1200):
		tmp_x=ROOT.Double(0)
		tmp_y=ROOT.Double(0)
		Asimov_gr.GetPoint(bin,tmp_x,tmp_y)
		Asimov_hist.SetBinContent(bin+1,tmp_y)
		Asimov_hist.SetBinError(bin+1,Asimov_gr.GetErrorYhigh(bin))
		#print tmp_x, tmp_y, Asimov_hist.GetBinCenter(bin+1),Asimov_hist.GetBinContent(bin+1)
	for i in range(0,Asimov_hist.GetNbinsX()):
		Asimov_hist.SetBinContent(i+1,Asimov_hist.GetBinContent(i+1)*Asimov_hist.GetBinWidth(i+1))
		Asimov_hist.SetBinError(i+1,Asimov_hist.GetBinError(i+1)*Asimov_hist.GetBinWidth(i+1))
	Asimov_hist.Rebin(50)
	Asimov_hist.SetMarkerColor(1)
	Asimov_hist.SetMarkerStyle(20)
	Asimov_hist.Draw("Psame")





	data_fit = fdata_fit.Get("shapes_fit_b/CAT%d/total"%cat)
	data_fit.SetLineWidth(2)
	data_fit.SetLineColor(ROOT.kRed)
#	data_fit.SetMarkerColor(ROOT.kRed)
	for i in range(0,data_fit.GetNbinsX()):
		data_fit.SetBinContent(i+1,data_fit.GetBinContent(i+1)*data_fit.GetBinWidth(i+1))
		data_fit.SetBinError(i+1,data_fit.GetBinError(i+1)*data_fit.GetBinWidth(i+1))
	data_fit.Rebin(50)
	data_fit.Draw("HISTsame")

	leg = ROOT.TLegend(0.7,0.7,0.9,0.9)
	#leg.AddEntry(data_hist,"Frozen QCD nuisance","")
	leg.AddEntry(data_hist,"Toys","LP")
	leg.AddEntry(all_hists[0],"Fit to toys","L")
	leg.AddEntry(data_fit,"Fit to data","L")
	leg.AddEntry(Asimov_hist,"Asimov","LP")
	leg.SetFillStyle(-1)
	leg.SetBorderSize(0)
	leg.SetTextFont(42)
	leg.SetTextSize(0.03)
	leg.Draw()
	c.SaveAs("plot/toys_fit_nolimit_noopt_bg_CAT0_accum_cat%d.png"%cat)
