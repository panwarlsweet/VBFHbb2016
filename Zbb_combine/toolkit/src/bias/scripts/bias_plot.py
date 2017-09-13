import ROOT
from ROOT import *
from ROOT import gStyle
import math
from math import sqrt
import sys


gROOT.SetBatch(True)
gROOT.ProcessLineSync(".x /afs/cern.ch/work/n/nchernya/Hbb/setTDRStyle.C")
gROOT.ForceStyle()
gStyle.SetPadTopMargin(0.06)
gStyle.SetPadRightMargin(0.04)
gStyle.SetPadLeftMargin(0.15)

#toy_func=sys.argv[1]
fit=sys.argv[1]
#fit_func=sys.argv[2]

list_graph=[]
graph0  = TGraphErrors(3)
graph1  = TGraphErrors(3)
graph2  = TGraphErrors(3)
graph3  = TGraphErrors(3)
list_graph.append(graph0)
list_graph.append(graph1)
list_graph.append(graph2)
list_graph.append(graph3)

toy_funcs=['expPow','modG','sineErf']
toy_funcs.append(fit)
fit_funcs=[]
for i in range(0,4):
 fit_funcs.append(fit)

path='/mnt/t3nfs01/data01/shome/nchernya/VBFHbb2016/Zbb_fit/bias/all_files/'
file_names=[]
for mu in range(0,3):
 list_hist=[]
 list_mean=[]
 list_rms=[]
 archive=[]
 for num in range(0,4):
  toy_func=toy_funcs[num]
  fit_func=fit_funcs[num]
  hist_all = ROOT.TH1F("hist_all%d"%num,"",30,-6,6)
#  if (toy_func=='modG' and (fit_func=='Pol6'or fit_func=='Pol7') and mu==0) or ((fit=="Pol8") and (toy_func!="sineErf")) : 
 #  list_hist.append(hist_all)
#   list_mean.append(0.)
 #  list_rms.append(0.)
 #  list_graph[num].SetPoint(mu,mu,0)
 #  list_graph[num].SetPointError(mu,0,0)
 #  continue
 
  inj_name=toy_funcs[num]+'_'+fit_funcs[num]+'_inj'+str(mu)
  f = ROOT.TFile.Open(path+'/mlfit'+inj_name+'.root')
  tree = f.Get("tree_fit_sb")
  hist_all = ROOT.TH1F("hist_all%d"%num,"",30,-6,6)
  tree.Draw("(mu-%d)/muErr>>hist_all%d"%(mu,num),"fit_status==0")
  n_toys = tree.GetEntries("fit_status==0")
  list_hist.append(hist_all)
#  list_mean.append(hist_all.GetMean())
 # list_rms.append(hist_all.GetRMS())
  list_graph[num].SetPoint(mu,mu,abs(hist_all.GetMean()))
#  list_graph[num].SetPoint(mu,mu,hist_all.GetMean())
  list_graph[num].SetPointError(mu,0,hist_all.GetRMS()/sqrt(n_toys))
 

colors=[kRed,kBlue,kGreen,kBlack]

for i in range(0,4):
 list_graph[i].SetLineColor(colors[i])
 list_graph[i].SetMarkerColor(colors[i])
 list_graph[i].SetMarkerStyle(21)

ymax=1.
ymin=0.
if fit=="Pol5" : 
	ymax=3.
	ymin=-3.
if fit=="Pol6" : 
	ymax=1.
	ymin=-1.
if fit=="Pol7" : 
	ymax=.7
	ymin=-.7
if fit=="Pol8" : 
	ymax=.4
	ymin=-.4

canv = ROOT.TCanvas("canv","canv",900,900)
list_graph[0].GetYaxis().SetTitle("bias")
list_graph[0].GetXaxis().SetTitle("#sigma/#sigma_{SM}")
list_graph[0].GetYaxis().SetRangeUser(0.,ymax)
#list_graph[0].GetYaxis().SetRangeUser(ymin,ymax)
list_graph[0].GetXaxis().SetLimits(-.5,2.5)
list_graph[0].GetXaxis().SetNdivisions(504)

leg = ROOT.TLegend(0.7,0.75,0.9,0.9)
leg.SetFillStyle(-1)
leg.SetBorderSize(0)
leg.SetTextFont(42)
leg.SetTextSize(0.03)
 
for num in range(0,4):
 if num==0 : list_graph[0].Draw("AP")
 else : list_graph[num].Draw("Psame")
 leg.AddEntry(list_graph[num],toy_funcs[num],"LP")
leg.Draw()

pave2 = ROOT.TPaveText(0.2,0.65,0.4,0.9,"NDC");
pave2.AddText("Fitted with %s"%fit_func);
pave2.SetFillColor(0)
pave2.SetTextFont(42)
pave2.SetTextColor(ROOT.kBlue)
pave2.SetTextSize(0.04)
pave2.SetBorderSize(0)
pave2.Draw();
gPad.Update()
right,top   = gStyle.GetPadRightMargin(),gStyle.GetPadTopMargin()
pave2.SetY1NDC(pave2.GetY2NDC()-top*0.9*pave2.GetListOfLines().GetSize())
pave2.Draw();
archive+=[pave2]

line = ROOT.TLine(-0.5,0.2,2.5,0.2)
line.SetLineStyle(3)
line.Draw("same")
line2 = ROOT.TLine(-0.5,-0.2,2.5,-0.2)
line2.SetLineStyle(3)
#line2.Draw("same")

#canv.SaveAs("plot_bias_sign_%s.pdf"%(fit_funcs[0]))
canv.SaveAs("plot_bias_%s.pdf"%(fit_funcs[0]))
