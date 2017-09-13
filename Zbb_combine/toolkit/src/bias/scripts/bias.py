import ROOT
from ROOT import *
from ROOT import gStyle
import sys


gROOT.SetBatch(True)
gROOT.ProcessLineSync(".x /afs/cern.ch/work/n/nchernya/Hbb/setTDRStyle.C")
gROOT.ForceStyle()
gStyle.SetPadTopMargin(0.06)
gStyle.SetPadRightMargin(0.04)
gStyle.SetPadLeftMargin(0.15)

#toy_func=sys.argv[1]
mu=sys.argv[1]
fit=sys.argv[2]
#fit_func=sys.argv[2]

toy_funcs=['expPow','modG','sineErf']
toy_funcs.append(fit)
fit_funcs=[]
for i in range(0,4):
 fit_funcs.append(fit)
#toy_funcs=['expPow','modG','Pol6']
#fit_funcs=['Pol6','Pol6','Pol6']
#toy_funcs=['expPow','modG','Pol5']
#fit_funcs=['Pol5','Pol5','Pol5']

#path='/mnt/t3nfs01/data01/shome/nchernya/VBFHbb2016/Zbb_fit/bias/'
path='/mnt/t3nfs01/data01/shome/nchernya/VBFHbb2016/Zbb_fit/bias/all_files/'
file_names=[]
list_hist=[]
archive=[]
for num in range(0,4):
 toy_func=toy_funcs[num]
 fit_func=fit_funcs[num]
 hist_all = ROOT.TH1F("hist_all%d"%num,"",30,-6,6)
# if (toy_func=='modG' and (fit_func=='Pol6'or fit_func=='Pol7') and mu=='0') : 
# if (toy_func=='modG' and (fit_func=='Pol6'or fit_func=='Pol7') and mu==0) or ((fit=="Pol8") and (toy_func!="sineErf")) : 
#  list_hist.append(hist_all)
#  continue

# inj_name=toy_funcs[num]+'_'+fit_funcs[num]+'_inj1'
# f = ROOT.TFile.Open(path+toy_funcs[num]+'/'+inj_name+'/mlfit'+inj_name+'.root')
 inj_name=toy_funcs[num]+'_'+fit_funcs[num]+'_inj'+mu
 f = ROOT.TFile.Open(path+'/mlfit'+inj_name+'.root')
 tree = f.Get("tree_fit_sb")
 hist_all = ROOT.TH1F("hist_all%d"%num,"",30,-6,6)
 tree.Draw("(mu-%s)/muErr>>hist_all%d"%(mu,num),"fit_status==0")
 list_hist.append(hist_all)


canv = ROOT.TCanvas("canv","canv",900,900)
canv.Divide(2,2)
for num in range(0,4):
 toy_func=toy_funcs[num]
 fit_func=fit_funcs[num]
 #if (toy_func=='modG' and (fit_func=='Pol6'or fit_func=='Pol7') and mu=='0') : continue
# if (toy_func=='modG' and (fit_func=='Pol6'or fit_func=='Pol7') and mu==0) or ((fit=="Pol8") and (toy_func!="sineErf")) : continue
 hist_all=list_hist[num]
 canv.cd(num+1)
 mean = hist_all.GetMean()
 rms =  hist_all.GetRMS()
 hist_all.SetStats(False)
 hist_all.SetLineColor(1)
 ymax=hist_all.GetMaximum()*1.1
 hist_all.GetYaxis().SetRangeUser(0.,ymax)
 hist_all.GetXaxis().SetTitle("(#mu-#mu_{inj})/#sigma")
 hist_all.GetYaxis().SetTitle("Toys")
 hist_all.Draw()
 #func = ROOT.TF1("func","gaus",-100,100)
 #func.SetParameters(7.98094e-02,1.00,2.5)
 #func.SetLineColor(ROOT.kRed)
 #func.SetLineWidth(3)
# hist_all.Fit(func)
 
 pave2 = ROOT.TPaveText(0.2,0.65,0.4,0.9,"NDC");
 pave2.AddText(toy_func);
 pave2.AddText("Fitted with %s"%fit_func);
 pave2.AddText("#mu_{inj}=%s"%mu);
 pave2.AddText("mean=%0.2f"%mean);
 pave2.AddText("rms=%0.2f"%rms);
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
#c.SaveAs("plot_inj1_%s_%s.pdf"%(toy_func,fit_func))
canv.SaveAs("plot_inj%s_%s.pdf"%(mu,fit_funcs[0]))
