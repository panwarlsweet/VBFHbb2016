import ROOT
from ROOT import gROOT,TLine
from ROOT import gStyle
import sys

channel = sys.argv[1]
trigger = sys.argv[2]

trigger_names=['PFJet40','PFJet60','PFJet80','DiPFJetAve40','DiPFJetAve60','DiPFJetAve80','QuadPFJet_VBF']
if channel=="double" : channel_name = "DoubleB"
if channel=="single" : channel_name = "SingleB"

gROOT.SetBatch(True)
gROOT.ProcessLineSync(".x /afs/cern.ch/work/n/nchernya/Hbb/setTDRStyle.C")
gROOT.ForceStyle()
gStyle.SetPadTopMargin(0.06)
gStyle.SetPadRightMargin(0.04)
gStyle.SetPadLeftMargin(0.15)

f = ROOT.TFile.Open("dcap://t3se01.psi.ch:22125//pnfs/psi.ch/cms/trivcat//store/user/nchernya/VBFHbb2016/triggerOutput/v25/JetHT_%s_trig%s_first.root"%(channel,trigger))


#hist_names = ["hJet1_pt_trigger","hJet2_pt_trigger","hJet3_pt_trigger","hJet4_pt_trigger"] #, "hMqq_trigger", "hbtag_trigger", "hbtag2_trigger","hDeltaEta_trigger","hDeltaPhi_trigger", "hbtag_log_trigger", "hbtag2_log_trigger"]
#hist_names_notrigger = ["hJet1_pt","hJet2_pt","hJet3_pt","hJet4_pt"] #, "hMqq", "hbtag", "hbtag2","hDeltaEta","hDeltaPhi","hbtag_log", "hbtag2_log"]
hist_names = [ "hbtag_trigger", "hbtag2_trigger", "hbtag_log_trigger", "hbtag2_log_trigger"]
hist_names_notrigger = [ "hbtag", "hbtag2","hbtag_log", "hbtag2_log"]
btag=1

presel_cuts = [92.,76.,64.,30.]

list_hist = []
list_hist_notrigger = []
list_ratio = []

for i in range(0,len(hist_names)):	
  hist = f.Get(hist_names[i]) 
  hist_notrig = f.Get(hist_names_notrigger[i])
  list_hist.append(hist)
  list_hist_notrigger.append(hist_notrig)
  hist.Divide(hist_notrig)
  list_ratio.append(hist)


right = gStyle.GetPadRightMargin()
top = gStyle.GetPadTopMargin()
left = gStyle.GetPadLeftMargin()
bottom =  gStyle.GetPadBottomMargin()

pCMS1 = ROOT.TPaveText(left,1.-top,0.4,1.,"NDC")
pCMS1.SetTextFont(62)
pCMS1.SetTextSize(top*0.75)
pCMS1.SetTextAlign(12)
pCMS1.SetFillStyle(-1)
pCMS1.SetBorderSize(0)
pCMS1.AddText("CMS")

pCMS12 = ROOT.TPaveText(left+0.1,1.-top*1.13,0.57,1.,"NDC")
pCMS12.SetTextFont(52)
pCMS12.SetTextSize(top*0.73)
pCMS12.SetTextAlign(12)
pCMS12.SetFillStyle(-1)
pCMS12.SetBorderSize(0)
pCMS12.AddText("Work in progress")

pCMS11 = ROOT.TPaveText(left,1.-top*2,0.4,1.-top*1.5,"NDC")
pCMS11.SetTextFont(42)
pCMS11.SetTextSize(top*0.75)
pCMS11.SetTextAlign(12)
pCMS11.SetFillStyle(-1)
pCMS11.SetBorderSize(0)
pCMS11.AddText(trigger_names[int(trigger)])


pCMS22 = ROOT.TPaveText(0.5,1.-top*2,1.-right*0.5,1.-top*1.5,"NDC")
pCMS22.SetTextFont(42)
pCMS22.SetTextSize(top*0.75)
pCMS22.SetTextAlign(32)
pCMS22.SetFillStyle(-1)
pCMS22.SetBorderSize(0)
pCMS22.AddText(channel_name)


pCMS2 = ROOT.TPaveText(0.5,1.-top,1.-right*0.5,1.,"NDC")
pCMS2.SetTextFont(42)
pCMS2.SetTextSize(top*0.75)
pCMS2.SetTextAlign(32)
pCMS2.SetFillStyle(-1)
pCMS2.SetBorderSize(0)
pCMS2.AddText("35.9 fb^{-1} (13 TeV)")

for num in range(0,len(hist_names)):
	c = ROOT.TCanvas("c","c",900,900)
	c.cd()
	xmin = list_hist[num].GetXaxis().GetXmin()*0.9
	xmax = list_hist[num].GetXaxis().GetXmax()*1.1
	frame = ROOT.TH1F("frame","",1,xmin,xmax)
	frame.SetStats(0)
	frame.GetYaxis().SetTitle("Efficiency")
	frame.GetYaxis().SetLabelSize(0.04)
	frame.GetXaxis().SetTitle(list_hist[num].GetXaxis().GetTitle())
	y_min= list_ratio[num].GetMinimum()*0.9
	y_max = list_ratio[num].GetMaximum()*1.5
	frame.GetYaxis().SetRangeUser(y_min,y_max)
	frame.Draw()
	list_ratio[num].Draw("PEsame")
	pCMS1.Draw()
	pCMS11.Draw()
	pCMS12.Draw()
	pCMS2.Draw()
	pCMS22.Draw()
	leg = ROOT.TLegend(0.7,0.75,0.9,0.9)
	leg.AddEntry(list_ratio[num],"JetHT" ,"PE")
	leg.SetFillStyle(-1)
	leg.SetBorderSize(0)
	leg.SetTextFont(42)
	leg.SetTextSize(0.03)
	leg.Draw()

	if (btag==0):
		line = TLine(presel_cuts[num],y_min,presel_cuts[num],y_max)
		line.SetLineStyle(9)
		line.SetLineColor(8)
		line.SetLineWidth(3)
		line.Draw()


	ROOT.gPad.Update()
	ROOT.gPad.RedrawAxis()
	c.SaveAs("plots_data/plot_data_%s_%s_%s.png" %(list_hist[num].GetName(),channel,trigger_names[int(trigger)] ))

