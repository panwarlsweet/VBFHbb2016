import ROOT
from ROOT import gROOT,TLine,TF1,TMath
from ROOT import gStyle
import sys
import math
import array


#channel = sys.argv[1]
trigger = sys.argv[1]

trigger_names=['PFJet40','PFJet60','PFJet80','DiPFJetAve40','DiPFJetAve60','DiPFJetAve80','QuadPFJet_VBF']
#if channel=="double" : channel_name = "DoubleB"
#if channel=="single" : channel_name = "SingleB"

gROOT.SetBatch(True)
gROOT.ProcessLineSync(".x /afs/cern.ch/work/n/nchernya/Hbb/setTDRStyle.C")
gROOT.ForceStyle()
gStyle.SetPadTopMargin(0.06)
gStyle.SetPadRightMargin(0.04)
gStyle.SetPadLeftMargin(0.15)

channel='double'
f0 = ROOT.TFile.Open("dcap://t3se01.psi.ch:22125//pnfs/psi.ch/cms/trivcat//store/user/nchernya/VBFHbb2016/triggerOutput/v25/JetHT_%s_trig%s_first.root"%(channel,trigger))
channel='single'
f1 = ROOT.TFile.Open("dcap://t3se01.psi.ch:22125//pnfs/psi.ch/cms/trivcat//store/user/nchernya/VBFHbb2016/triggerOutput/v25/JetHT_%s_trig%s_first.root"%(channel,trigger))

path='dcap://t3se01.psi.ch:22125//pnfs/psi.ch/cms/trivcat//store/user/nchernya/VBFHbb2016/triggerOutput/v25/'
channel='double'
#file_name_end0='_%s_trig%s_first.root'%(channel,trigger)
#file_name_end0='_%s_trig%s_erf_1jet.root'%(channel,trigger)
file_name_end0='_%s_trig%s_erf_2jet.root'%(channel,trigger)
channel='single'
file_name_end1='_%s_trig%s_erf_2jet.root'%(channel,trigger)
mc_names=['QCD_HT100to200','QCD_HT200to300','QCD_HT300to500','QCD_HT500to700','QCD_HT700to1000','QCD_HT1000to1500','QCD_HT1500to2000','QCD_HT2000toInf']

	



#hist_names = ["hJet1_pt_trigger","hJet2_pt_trigger","hJet3_pt_trigger","hJet4_pt_trigger"] 
#hist_names_notrigger = ["hJet1_pt","hJet2_pt","hJet3_pt","hJet4_pt"] 
#hist_names = ["hJet1_pt_trigger"] 
#hist_names_notrigger = ["hJet1_pt"] 
#hist_names = ["hJet2_pt_trigger"] 
#hist_names_notrigger = ["hJet2_pt"] 
hist_names = ["hJet3_pt_trigger"] 
hist_names_notrigger = ["hJet3_pt"] 
btag=0
presel_cuts = [92.,76.,64.,30.]


list_hist_mc=[]
list_hist_notrigger_mc=[]
list_ratio_mc = []
list_ratio_mc2 = []

new_bins = array.array('d',[0.,20,40,60,80,100,120,140,180,240,300,550])

for i in range(0,len(mc_names)):
  fmc0 = ROOT.TFile.Open(path+mc_names[i]+file_name_end0)
  fmc1 = ROOT.TFile.Open(path+mc_names[i]+file_name_end1)
  for j in range(0,len(hist_names)):
    hist0 = fmc0.Get(hist_names[j]) 
    hist_notrig0 = fmc0.Get(hist_names_notrigger[j])
    hist1 = fmc1.Get(hist_names[j]) 
    hist_notrig1 = fmc1.Get(hist_names_notrigger[j])
    hist0.Add(hist1)
   # hist00 = hist0.Rebin(11,"mc0",new_bins)
    hist00 = hist0
    hist_notrig0.Add(hist_notrig1)
  #  hist_notrig00 = hist_notrig0.Rebin(11,"mc1",new_bins)
    hist_notrig00 = hist_notrig0
    if i==0 : 
      list_hist_mc.append(hist00)
      list_hist_notrigger_mc.append(hist_notrig00)
    else :
      list_hist_mc[j].Add(hist00,1)
      list_hist_notrigger_mc[j].Add(hist_notrig00)
    
for i in range(0,len(hist_names)):	
  hist=list_hist_mc[i]
  hist_notrig=list_hist_notrigger_mc[i]
  hist.Divide(hist_notrig)
  list_ratio_mc.append(hist)
  list_ratio_mc[i].SetMarkerStyle(26)
  list_ratio_mc[i].SetLineColor(2)
  list_ratio_mc[i].SetMarkerColor(2)

list_hist = []
list_hist_notrigger = []
list_ratio = []
list_ratio2 = []

for i in range(0,len(hist_names)):	
  hist0 = f0.Get(hist_names[i]) 
  hist1 = f1.Get(hist_names[i]) 
  hist_notrig0 = f0.Get(hist_names_notrigger[i])
  hist_notrig1 = f1.Get(hist_names_notrigger[i])
  hist0.Add(hist1)
#  hist00 = hist0.Rebin(11,"data0",new_bins)
  hist00 = hist0
  hist_notrig0.Add(hist_notrig1)
#  hist_notrig00 = hist_notrig0.Rebin(11,"data1",new_bins)
  hist_notrig00 = hist_notrig0
  list_hist.append(hist00)
  list_hist_notrigger.append(hist_notrig00)
  hist00.Divide(hist_notrig00)
  list_ratio.append(hist00)
  print list_ratio[0].GetNbinsX()



list_ratio_data_mc = []
list_ratio_data_mc2 = []
for i in range(0,len(hist_names)):	
  hist_mc=list_ratio_mc[i]
  hist_data=list_ratio[i].Clone("New_data")
  hist_data.Divide(hist_mc)
  list_ratio_data_mc.append(hist_data)


for i in range(0,len(hist_names)):
	list_ratio2.append(list_ratio[i])
	list_ratio_mc2.append(list_ratio_mc[i])
	list_ratio_data_mc2.append(list_ratio_data_mc[i])

list_ratio_data_mcUp = []
list_ratio_data_mcDown = []
for i in range(0,len(hist_names)):
	hist_Up = list_ratio_data_mc2[i].Clone("Up"+str(i))
	hist_Down = list_ratio_data_mc2[i].Clone("Down"+str(i))
	for ibin in range(0,hist_Up.GetNbinsX()):
		ey=0.
		bin=0;
		bin = list_ratio_data_mc2[i].GetBinContent(ibin+1)
		ey = list_ratio_data_mc2[i].GetBinError(ibin+1)	
		hist_Up.SetBinContent(ibin+1,bin+ey)
		hist_Down.SetBinContent(ibin+1,bin-ey)
	list_ratio_data_mcUp.append(hist_Up)
	list_ratio_data_mcDown.append(hist_Down)



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


pCMS22 = ROOT.TPaveText(left,1.-top*3.5,0.4,1.-top*2.5,"NDC")
pCMS22.SetTextFont(42)
pCMS22.SetTextSize(top*0.75)
pCMS22.SetTextAlign(32)
pCMS22.SetFillStyle(-1)
pCMS22.SetBorderSize(0)
#pCMS22.AddText(channel_name)


pCMS2 = ROOT.TPaveText(0.5,1.-top,1.-right*0.5,1.,"NDC")
pCMS2.SetTextFont(42)
pCMS2.SetTextSize(top*0.75)
pCMS2.SetTextAlign(32)
pCMS2.SetFillStyle(-1)
pCMS2.SetBorderSize(0)
pCMS2.AddText("35.9 fb^{-1} (13 TeV)")

for num in range(0,len(hist_names)):
	
	func_erf_Up=TF1("erffuncUp","[0]/2.*(1.+TMath::Erf((x-[1])/[2]))",0.,600.)
	func_erf_Up.SetLineWidth(1)
	func_erf_Up.SetLineColor(ROOT.kRed-7)
	func_erf_Up.SetFillColor(ROOT.kRed-7)
	func_erf_Up.SetFillStyle(3004)
	func_erf_Up.SetParameters(1.,82,30.)
#	func_erf_Up.SetParameters(1.,76,30.)
#	func_erf_Up.SetParameters(1.,24,30.)
	list_ratio_data_mcUp[num].Fit(func_erf_Up,"R","N",0,600.)
	func_erf_Down=TF1("erffuncDown","[0]/2.*(1.+TMath::Erf((x-[1])/[2]))",0.,600.)
	func_erf_Down.SetLineWidth(1)
	func_erf_Down.SetLineColor(ROOT.kRed-7)
	func_erf_Down.SetFillColor(10)
	func_erf_Down.SetFillStyle(1001)
	func_erf_Down.SetParameters(1.,82,30.)
#	func_erf_Down.SetParameters(1.,76,30.)
#	func_erf_Down.SetParameters(1.,24,30.)
	list_ratio_data_mcDown[num].Fit(func_erf_Down,"R","N",0,200.)


	c = ROOT.TCanvas("c","c",900,900)
	c.cd()
	c.SetBottomMargin(0.3)
	xmin = list_hist[num].GetXaxis().GetXmin()*0.9
	xmax = list_hist[num].GetXaxis().GetXmax()*1.1
	frame = ROOT.TH1F("frame","",1,xmin,xmax)
	frame.SetStats(0)
	frame.GetYaxis().SetTitle("Efficiency")
	frame.GetYaxis().SetLabelSize(0.04)
	frame.GetXaxis().SetLabelSize(0)
	frame.GetXaxis().SetTitleOffset(0.91);
#	frame.GetXaxis().SetTitle(list_hist[num].GetXaxis().GetTitle())
	y_min= list_ratio2[num].GetMinimum()*0.9
	y_max = list_ratio2[num].GetMaximum()*1.8
	frame.GetYaxis().SetRangeUser(y_min,y_max)
	frame.Draw()
	list_ratio2[num].Draw("PEsame")
	list_ratio_mc2[num].Draw("PEsame")
	pCMS1.Draw()
	pCMS11.Draw()
	pCMS12.Draw()
	pCMS2.Draw()
#	pCMS22.Draw()
	leg = ROOT.TLegend(0.7,0.75,0.9,0.9)
	leg.AddEntry(list_ratio2[num],"JetHT" ,"PE")
	leg.AddEntry(list_ratio_mc2[num],"QCD" ,"PE")
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

	pad2 = ROOT.TPad("pad2", "pad2", 0., 0., 1., 1.)
	pad2.SetTopMargin(0.73)
#	pad2.SetBottomMargin(0.)
#	pad2.SetRightMargin(0.)
	pad2.SetFillColor(0)
	pad2.SetFillStyle(0)
	pad2.Draw()
	pad2.cd()
	frame2 = ROOT.TH1F("frame2","",1,xmin,xmax)
	frame2.SetMinimum(0.)	
	frame2.SetMaximum(2) 
	frame2.GetYaxis().SetLabelSize(0.02)
	frame2.GetXaxis().SetLabelSize(0.04)
	frame2.GetYaxis().SetTitleSize(0.04)
	frame2.GetXaxis().SetTitle(list_hist[num].GetXaxis().GetTitle())
	frame2.SetStats(0)
	frame2.GetYaxis().SetTitle("Data/MC")	
	frame2.Draw()

	list_ratio_data_mc2[num].Draw("PEsame")
		
	func_erf_Up.Draw("same")
	func_erf_Down.Draw("same")
	
	func_erf=TF1("erffunc","[0]/2.*(1.+TMath::Erf((x-[1])/[2]))",0.,600.)
#	func_erf.SetParameters(1.,82,30.)
#	func_erf.SetParameters(1.,76,30.)
	func_erf.SetParameters(1.,24,30.)
	if num==0 : 
		list_ratio_data_mc2[num].Fit(func_erf,"R","SAME")
		print func_erf.GetChisquare(), func_erf.GetNDF(), func_erf.GetChisquare()/func_erf.GetNDF()


	line2 = TLine(xmin,1,xmax,1)
	line2.SetLineStyle(2)
	line2.SetLineColor(1)
	line2.SetLineWidth(2)
	line2.Draw("same")

	
	ROOT.gPad.Update()
	ROOT.gPad.RedrawAxis()
	c.SaveAs("plots_combined_erf/Unc2/plot_%s_%s.png" %(hist_names[num],trigger_names[int(trigger)] ))

