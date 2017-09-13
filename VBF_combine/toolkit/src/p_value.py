import ROOT
from ROOT import gROOT
from ROOT import gStyle

gROOT.SetBatch(True)
gROOT.ProcessLineSync(".x /afs/cern.ch/work/n/nchernya/Hbb/setTDRStyle.C")
gROOT.ForceStyle()
gStyle.SetPadTopMargin(0.06)
gStyle.SetPadRightMargin(0.04)
gStyle.SetPadLeftMargin(0.15)

f = ROOT.TFile.Open("/afs/cern.ch/work/n/nchernya/VBFHbb_2016/VBF_combine/toolkit/src/combination/GoF/toys/higgsCombinesaturated_toys_50_num_all.GoodnessOfFit.root")
tree = f.Get("limit")
#hist = ROOT.TH1F("hist","",90,0.,0.03) #KS 
#hist_all = ROOT.TH1F("hist_all","",1000,-0.1,0.1) #KS
hist = ROOT.TH1F("hist","",100,7500,9500)  #sat
hist_all = ROOT.TH1F("hist_all","",1000,3000,15000) #sat
#hist = ROOT.TH1F("hist","",110,0,11)  #AD
#hist_all = ROOT.TH1F("hist_all","",1000,0,30) #AD

tree.Draw("limit>>hist")
tree.Draw("limit>>hist_all")
hist.Scale(1./hist.Integral())
hist_all.Scale(1./hist_all.Integral())
print hist.GetMean()
print hist.GetRMS()
hist.SetStats(False)
hist.SetLineColor(1)
hist.GetYaxis().SetTitle("Probability")
ymax=hist.GetMaximum()*1.1
hist.GetYaxis().SetRangeUser(0.,ymax)
hist.GetXaxis().SetNdivisions(505)
hist.GetXaxis().SetTitle("#chi^{2}_{saturated}")
c = ROOT.TCanvas("c","c",900,900)
hist.Draw("H")
#func = ROOT.TF1("func","gaus",0.,1.) #KS
func = ROOT.TF1("func","gaus",5000,12000) #sat
#func = ROOT.TF1("func","gaus",0,100) #AD
#func.SetParameters(7.98094e-02,0.015,0.002)
func.SetLineColor(ROOT.kBlue)
func.SetLineWidth(3)
hist.Fit(func,"R")
func.FixParameter(0,func.GetParameter(0))
func.FixParameter(1,func.GetParameter(1))
func.FixParameter(2,func.GetParameter(2))




print func.GetChisquare(), func.GetNDF() 
#mu=0.0226 #KS
mu=8044.38 #saturated
#mu=9.96161 #AD
hist2 = hist.Clone("hist2")
hist2.SetLineColor(2)
hist2.SetLineWidth(3)
hist2.SetFillColor(ROOT.kRed-9)
hist2.SetFillStyle(1001)
#hist2.GetXaxis().SetRangeUser(mu,1)
hist2.Draw("Hsame")
#print "p_value = ", func.Integral(-100.,mu)
#p_value=hist_all.Integral(hist_all.FindBin(mu),hist_all.FindBin(0.1))
#p_value=func.Integral(mu,1.)/func.Integral(0.,1.)
#p_value=func.Integral(1000,mu)/func.Integral(5000,12000)
#p_value=func.Integral(mu,100)/func.Integral(0,100)
#print "p_value = ", p_value
line  = ROOT.TLine(1.,0.,1.,ymax)
line.SetLineColor(1)
line.SetLineStyle(2)
line.SetLineWidth(2)
#line.Draw()
#func2 = ROOT.TF1("func","gaus",mu,0.1)
#func2.FixParameter(0,func.GetParameter(0))
#func2.FixParameter(1,func.GetParameter(1))
#func2.FixParameter(2,func.GetParameter(2))
#func2.SetLineColor(2)
#func2.SetLineWidth(3)
#func2.SetFillColor(ROOT.kRed-9)
#func2.SetFillStyle(1001)
#func2.Draw("LFsame")
line2  = ROOT.TLine(mu,0.,mu,ymax)
line2.SetLineColor(ROOT.kRed)
line2.SetLineStyle(7)
line2.SetLineWidth(3)
line2.Draw()
pave = ROOT.TPaveText(0.7,0.8,0.9,0.9,"NDC");
#pave.AddText("data_{obs} = %.3f" % mu)
#pave.AddText("p-value = %.6f" % p_value);
pave.SetFillColor(0)
pave.SetTextFont(62)
pave.SetTextColor(2)
pave.SetTextSize(0.04)
pave.SetBorderSize(0)
#pave.Draw();
pave2 = ROOT.TPaveText(0.25,0.85,0.4,0.9,"NDC");
#pave2.AddText("Combined");
#pave2.AddText("Dielectron");
pave2.AddText("GoF, saturated algo");
pave2.SetFillColor(0)
pave2.SetTextFont(42)
pave2.SetTextColor(ROOT.kBlue)
pave2.SetTextSize(0.04)
pave2.SetBorderSize(0)
pave2.Draw();
c.SaveAs("plot_pvalue_saturated.pdf")
c.SaveAs("plot_pvalue_saturated.png")
