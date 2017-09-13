import ROOT
from ROOT import gROOT
from ROOT import gStyle

gROOT.SetBatch(True)
gROOT.ProcessLineSync(".x /afs/cern.ch/work/n/nchernya/Hbb/setTDRStyle.C")
gROOT.ForceStyle()
gStyle.SetPadTopMargin(0.06)
gStyle.SetPadRightMargin(0.04)
gStyle.SetPadLeftMargin(0.15)

#fdata = ROOT.TFile.Open("/afs/cern.ch/work/n/nchernya/VBFHbb_2016/VBF_combine/toolkit/src/combination/toys_Fit/toys_seeds/mlfittoys_2_num_0.root")
fdata = ROOT.TFile.Open("/afs/cern.ch/work/n/nchernya/VBFHbb_2016/VBF_combine/toolkit/src/combination/run_v9/mlfitnormal_fit_v9_Freq_shapes.root")

#fdata = ROOT.TFile.Open("/afs/cern.ch/work/n/nchernya/VBFHbb_2016/VBF_combine/toolkit/src/combination/toys_Fit/toys_noFreq/mlfittoys_2_num_0.root")
fdata_fit = ROOT.TFile.Open("/afs/cern.ch/work/n/nchernya/VBFHbb_2016/VBF_combine/toolkit/src/combination/combine_2016_results/mlfitdataShapes3.root")

files=[]

for i in range(0,100):
	files.append("/afs/cern.ch/work/n/nchernya/VBFHbb_2016/VBF_combine/toolkit/src/combination/toys_Fit/toys_seeds/mlfittoys_2_num_%d.root"%i)
#	files.append("/afs/cern.ch/work/n/nchernya/VBFHbb_2016/VBF_combine/toolkit/src/combination/toys_Fit/toys_noFreq/mlfittoys_2_num_%d.root"%i)

#bad_list = [1,22,3,38,51,58,9,64,6]
#len = len(bad_list)
for cat in range(0,1):
	all_hists=[]
	
#	tmp_file = ROOT.TFile.Open(files[0])
#	main_hist = tmp_file.Get("shapes_fit_s/CAT%d/total"%cat)
#	main_hist.SetBit(ROOT.TH1F.kIsAverage)
#	violin_hist = ROOT.TH2F("violin_CAT%d"%cat,"violin_CAT%d"%cat,10,80,200,10,0,10000)
#	all_hists.append(main_hist)
	
	len=0
	for num,file in enumerate(files):
		if num==64 : continue
		tmp_file = ROOT.TFile.Open(file)
		if tmp_file.cd("shapes_fit_s")==False : continue
	#	print tmp_file.cd("shapes_fit_s")
		tmp_hist = tmp_file.Get("shapes_fit_s/CAT%d/total"%cat)
		for i in range(0,tmp_hist.GetNbinsX()):
			tmp_hist.SetBinContent(i+1,tmp_hist.GetBinContent(i+1)*tmp_hist.GetBinWidth(i+1))
		all_hists.append(tmp_hist)
		len=len+1
	#	tmp_hist.SetBit(ROOT.TH1F.kIsAverage)
	#	main_hist.Add(tmp_hist)

	print len

	c = ROOT.TCanvas("c","c",900,900)
	all_hists[1].GetYaxis().SetTitle("Events/(1 GeV)")
	all_hists[1].GetXaxis().SetTitle("M_{bb} in CAT%d (GeV)"%cat)
	all_hists[1].Rebin(50)
	all_hists[1].SetLineColor(ROOT.kCyan)
	all_hists[1].Draw("H")	
	for num in range(2,len):
		all_hists[num].Rebin(50)
		all_hists[num].SetLineColor(ROOT.kCyan)
		all_hists[num].Draw("Hsame")
	if fdata.cd("shapes_fit_s")==False : continue
	data_gr = fdata.Get("shapes_fit_s/CAT%d/data"%cat)
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
	data_hist.Rebin(50)
	data_hist.Draw("same")

	data_fit = fdata_fit.Get("shapes_fit_s/CAT%d/total"%cat)
	data_fit.SetLineWidth(2)
	data_fit.SetLineColor(ROOT.kRed)
	for i in range(0,data_fit.GetNbinsX()):
		data_fit.SetBinContent(i+1,data_fit.GetBinContent(i+1)*data_fit.GetBinWidth(i+1))
		#data_fit.SetBinContent(i+1,data_fit.GetBinContent(i+1)*data_fit.GetBinWidth(i+1))
	data_fit.Rebin(50)
	data_fit.Draw("same")

	leg = ROOT.TLegend(0.7,0.7,0.9,0.9)
	leg.AddEntry(data_hist,"Asimov","LP")
	leg.AddEntry(all_hists[0],"Toys ensemble","L")
	leg.AddEntry(data_fit,"Fit to data","L")
	leg.SetFillStyle(-1)
	leg.SetBorderSize(0)
	leg.SetTextFont(42)
	leg.SetTextSize(0.03)
	leg.Draw()
	c.SaveAs("toys_fit_Freq_Asimov_accum_cat%d.png"%cat)
