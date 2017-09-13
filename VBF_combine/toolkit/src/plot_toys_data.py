import ROOT
from ROOT import gROOT
from ROOT import gStyle

gROOT.SetBatch(True)
gROOT.ProcessLineSync(".x /afs/cern.ch/work/n/nchernya/Hbb/setTDRStyle.C")
gROOT.ForceStyle()
gStyle.SetPadTopMargin(0.06)
gStyle.SetPadRightMargin(0.04)
gStyle.SetPadLeftMargin(0.15)

#f = ROOT.TFile.Open("/afs/cern.ch/work/n/nchernya/VBFHbb_2016/VBF_combine/toolkit/src/combination/toys_Fit/mlfittoys_20_num_all.MaxLikelihoodFit.root")
#fdata = ROOT.TFile.Open("/afs/cern.ch/work/n/nchernya/VBFHbb_2016/VBF_combine/toolkit/src/combination/combine_2016_results/mlfitunblinded6.root")
fdata = ROOT.TFile.Open("/afs/cern.ch/work/n/nchernya/VBFHbb_2016/VBF_combine/toolkit/src/combination/toys_Fit/all_toys/mlfittoys_20_num_0.root")
fdata_fit = ROOT.TFile.Open("/afs/cern.ch/work/n/nchernya/VBFHbb_2016/VBF_combine/toolkit/src/combination/combine_2016_results/mlfitdata.root")

files=[]

for i in range(0,100):
	files.append("/afs/cern.ch/work/n/nchernya/VBFHbb_2016/VBF_combine/toolkit/src/combination/toys_Fit/all_toys/mlfittoys_20_num_%d.root"%i)

for cat in range(0,7):
	tmp_file = ROOT.TFile.Open(files[0])
	main_hist = tmp_file.Get("shapes_fit_s/CAT%d/total"%cat)
	main_hist.SetBit(ROOT.TH1F.kIsAverage)
	
	for num,file in enumerate(files):
		if num==0 : continue
		tmp_file = ROOT.TFile.Open(file)
		tmp_hist = tmp_file.Get("shapes_fit_s/CAT%d/total"%cat)
		tmp_hist.SetBit(ROOT.TH1F.kIsAverage)
		main_hist.Add(tmp_hist)

	c = ROOT.TCanvas("c","c",900,900)
	main_hist.SetLineWidth(2)
	main_hist.SetLineColor(ROOT.kRed)
	main_hist.GetYaxis().SetTitle("Events/(1 GeV)")
	main_hist.GetXaxis().SetTitle("M_{bb} in CAT%d (GeV)"%cat)
	main_hist.Draw("H")	
	main_hist.Rebin(10)
	data_gr = fdata.Get("shapes_fit_s/CAT%d/data"%cat)
	data_hist = ROOT.TH1F("data_hist_CAT%d"%cat,"data_hist_CAT%d"%cat,1200,80,200)
	for bin in range(0,1200):
		tmp_x=ROOT.Double(0)
		tmp_y=ROOT.Double(0)
		data_gr.GetPoint(bin,tmp_x,tmp_y)
		data_hist.SetBinContent(bin+1,tmp_y)
		data_hist.SetBinError(bin+1,data_gr.GetErrorYhigh(bin))
		#print tmp_x, tmp_y, data_hist.GetBinCenter(bin+1),data_hist.GetBinContent(bin+1)
	data_hist.Rebin(10)
	data_hist.Draw("same")

	data_fit = fdata_fit.Get("shapes_fit_s/CAT%d/total"%cat)
	data_fit.SetLineWidth(2)
	data_fit.SetLineColor(ROOT.kGreen)
	data_fit.Rebin(10)
	data_fit.Draw("same")

	leg = ROOT.TLegend(0.7,0.7,0.9,0.9)
	leg.AddEntry(data_hist,"Data","LP")
	leg.AddEntry(main_hist,"Toys ensemble","L")
	leg.AddEntry(data_fit,"Fit to data","L")
	leg.SetFillStyle(-1)
	leg.SetBorderSize(0)
	leg.SetTextFont(42)
	leg.SetTextSize(0.03)
	leg.Draw()
	c.SaveAs("toys_fit_cat%d.png"%cat)

if (0>1):
#for cat in range(6,6):
	hist = f.Get("shapes_fit_s/CAT%d/total"%cat)
#	hist_mc_s = hist.Clone("hist_mc_CAT%d"%cat)
	#hist_data = TH1F("hist_data_CAT%d"%cat)
	#for point in range(0,data_gr.GetN()):
	#	hist_data.SetBinContent(



	hist.GetYaxis().SetTitle("N_{events}")
	ymax=hist.GetMaximum()*1.6
	hist.GetYaxis().SetRangeUser(0.,ymax)
	#hist.GetXaxis().SetNdivisions(505)
	hist.GetXaxis().SetTitle("M_{bb} (GeV)")
	c = ROOT.TCanvas("c","c",900,900)
	hist.Draw("H")
	data_gr.Draw("same")



	pave = ROOT.TPaveText(0.7,0.8,0.9,0.9,"NDC")
	pave.AddText("CAT%d" %cat)
	pave.SetFillColor(0)
	pave.SetTextFont(62)
	pave.SetTextColor(2)
	pave.SetTextSize(0.04)
	pave.SetBorderSize(0)
	pave.Draw()

	c.SaveAs("plot_toys_fit_CAT%d.pdf"%cat)
	c.SaveAs("plot_toys_fit_CAT%d.png"%cat)
