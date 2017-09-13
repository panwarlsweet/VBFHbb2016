#!/usr/bin/env python

import os,sys,re,json,datetime
from glob import glob
from array import array
from optparse import OptionParser,OptionGroup
import warnings
warnings.filterwarnings( action='ignore', category=RuntimeWarning, message='.*class stack<RooAbsArg\*,deque<RooAbsArg\*> >' )

basepath=os.path.split(os.path.abspath(__file__))[0]+"/../"
sys.path.append(basepath+"common/")

tempargv = sys.argv[:]
sys.argv = []
import ROOT
from ROOT import *
sys.argv = tempargv

from toolkit import *

colours = ["\033[m"] + ["\033[%d;%dm"%(x,y) for (x,y) in [(0,z) for z in range(31,37)]+[(1,z) for z in range(31,37)]]

####################################################################################################
def parser(mp=None):
	if not mp: mp = OptionParser()
#	mp.add_option('','',help=colours[5]+''+colours[0],default='',type='',dest='')
#
#	mg1 = OptionGroup(mp,'GroupTitle')
#	mg1.add_option('','',help=colours[5]+''+colours[0],default='',type='',dest='')
#	mp.add_option_group(mg1)
#
	mp.add_option('--workdir',help=colours[5]+'Case workdir.'+colours[0],default='case0',type='str')
	mp.add_option('--long',help=colours[5]+'Long filenames.'+colours[0],default=False,action='store_true')
	mp.add_option('-v','--verbosity',help=colours[5]+'Verbosity.'+colours[0],default=0,action='count')
	mp.add_option('-q','--quiet',help=colours[5]+'Quiet.'+colours[0],default=True,action='store_false')
#
	mg1 = OptionGroup(mp,'Selection setup')
#	mg1.add_option('--SELCATs',help=colours[5]+'Selection/Category setup: "Double;DoubleB;-1.,-0.0175,0.2925,1.".'+colours[0],default='Double;DoubleB;-1.#-0.0175#0.2925#1.',type='str',action='callback',callback=SELsetup,dest='SC')# final
	mg1.add_option('--SELCATs',help=colours[5]+'Selection/Category setup: "Double;DoubleB;-1.,-0.2275, 0.1125,0.3425,1.".'+colours[0],default='Double;DoubleB;-1.#-0.2275#0.1125#0.3425#1.',type='str',action='callback',callback=SELsetup,dest='SC')# final
	mp.add_option_group(mg1)
#
	mg2 = OptionGroup(mp,'Bkg template setup')
	mg2.add_option('--bounds',help=colours[5]+'Template boundaries: 60,170 (min,max)'+colours[0],default=[60.,170.],type='str',action='callback',callback=optsplitfloat,dest='X')
	mg2.add_option('--binsize',help=colours[5]+'Template NBINS: 20 (double)'+colours[0],default=[20],type='str',action='callback',callback=optsplitint,dest='NBINS')
	mg2.add_option('--lumi',help=colours[5]+'Luminosity: 35900.,35900. (double)'+colours[0],default=[35900.],type='str',action='callback',callback=optsplitfloat,dest='LUMI')
	mp.add_option_group(mg2)
#
	return mp

####################################################################################################
def style():
	gROOT.SetBatch(1)
	gROOT.ProcessLineSync(".x %s/styleCMSTDR.C"%basepath)
	gROOT.ForceStyle()
	gStyle.SetPadTopMargin(0.06)
	gStyle.SetPadRightMargin(0.04)
	gROOT.ProcessLineSync("gErrorIgnoreLevel = kWarning;")
	RooMsgService.instance().setSilentMode(kTRUE)
	for i in range(2): RooMsgService.instance().setStreamStatus(i,kFALSE)

def hStyle(h,i,sumw2=True):
	if sumw2: h.Sumw2()
	h.SetMarkerStyle([20,20,23,21][i])
	h.SetMarkerSize(1.2)
	h.SetMarkerColor([kBlack,kBlue,kRed,kGreen+2][i])
	h.SetLineColor([kBlack,kBlue,kRed,kGreen+2][i])

def gpStyle(g,i):
	g.SetFillColor([kBlack,kBlue,kRed,kGreen+2][i])
	g.SetFillStyle(3004)

def gaStyle(g,i):
	g.SetFillColor(kGray)
	g.SetFillStyle(1001)

####################################################################################################
def RooDraw(can,x,h,model,S,C,Cp,text,archive):
	can.cd(C+1)
	frame = x.frame()
	h.plotOn(frame)
	model.plotOn(frame,RooFit.LineWidth(2))
	frame.GetXaxis().SetTitle("M_{bb} (GeV)")
	frame.GetYaxis().SetRangeUser(0,frame.GetMaximum()*1.25)
	frame.Draw()
	right,top = gStyle.GetPadRightMargin(),gStyle.GetPadTopMargin()
	pave = TPaveText(0.67,0.75,1.-right-top*0.3333,1.-top*1.666,"NDC")
	pave.SetTextAlign(11)
	pave.SetFillStyle(-1)
	pave.SetBorderSize(0)
	pave.SetTextFont(62)
	pave.SetTextSize(top*0.80)
#	pave.AddText("%s selection"%(S.label))
	pave.AddText("CAT%d"%Cp)
	pave.AddText(text)
	pave.Draw()
	gPad.Update()
	pave.SetY1NDC(pave.GetY2NDC()-top*0.92*pave.GetListOfLines().GetSize())
	pave.Draw()
	archive += [pave]

####################################################################################################
def main():
# Parse options
	mp = parser()
	opts,args = mp.parse_args()

# Style
	style()

# Create directories if needed
	makeDirs('%s'%opts.workdir)
	makeDirs('%s/plot'%opts.workdir)
	makeDirs('%s/root'%opts.workdir)
	longtag = "_B%d-%d"%(opts.X[0],opts.X[1])

# Setup
	SC = opts.SC if not type(opts.SC)==str else SELsetup(opts.SC)
	fnames = json.loads(filecontent("%s/vbfZbb_samples_2016_bkg.json"%basepath))
	finfo  = json.loads(filecontent("%s/vbfZbb_info_2016.json"%basepath))

# New histograms, graphs, containers
	w = RooWorkspace("w","workspace")
	CN0 = TCanvas("c1","c1",900,750)
	kJES = [None]*(SC.nsel)
	kJER = [None]*(SC.nsel)
	archive = []

## CMS info
	left,right,top,bottom = gStyle.GetPadLeftMargin(),gStyle.GetPadRightMargin(),gStyle.GetPadTopMargin(),gStyle.GetPadBottomMargin()
	pCMS1 = TPaveText(left,1.-top,0.4,1.,"NDC")
	pCMS1.SetTextFont(62)
	pCMS1.SetTextSize(top*0.75)
	pCMS1.SetTextAlign(12)
	pCMS1.SetFillStyle(-1)
	pCMS1.SetBorderSize(0)
	pCMS1.AddText("CMS")
	pCMS2 = TPaveText(0.5,1.-top,1.-right*0.5,1.,"NDC")
	pCMS2.SetTextFont(42)
	pCMS2.SetTextSize(top*0.75)
	pCMS2.SetTextAlign(32)
	pCMS2.SetFillStyle(-1)
	pCMS2.SetBorderSize(0)
	pCMS2.AddText("L = 35.9 fb^{-1} (13 TeV)")

# Selection loop
	for iS,S in enumerate(SC.selections):
 ## Container ## Containers
 		hMbb = {}
 		hMbbYield = {}
 		rh_W = {}
 		rh_T = {}
 ## File reading
		inf = [None]*(len(fnames['files']))
		fi = 0
		for f in fnames['files'].itervalues():
			inf[fi] = TFile.Open("/afs/cern.ch/work/n/nchernya/VBFHbb_2016/Zbb_combine/inputs/root/"+f['fname'],'read')
			fi += 1
 ## Canvas definition
		canW = TCanvas("canW_sel%s"%S.tag,"canW_sel%s"%S.label,900,600)
		canT = TCanvas("canT_sel%s"%S.tag,"canT_sel%s"%S.label,900,600)
		canW.Divide(2,2)
		canT.Divide(2,2)
		can = TCanvas("c","c",900,600)
 ## Nuissance parameters
		print S.tag
 		nVar = "CMS_vbfbb_scale_mbb_13TeV"
		kJES[iS] = RooRealVar(nVar,nVar,1.0)
 		nVar = "CMS_vbfbb_res_mbb_13TeV"
		kJER[iS] = RooRealVar(nVar,nVar,1.0)
		kJES[iS].setConstant(kTRUE)
		kJER[iS].setConstant(kTRUE)
		
## Category loop
		for C in range(S.ncat):
			Cp = C + sum([x for x in SC.ncats[0:iS]])
			NBINS=opts.NBINS[iS]
### File loop
			for fi,F in enumerate(inf):
				ni = F.GetName()
				niShort = os.path.split(F.GetName())[1]
			#	if 'WJets' in ni: group = 'WJets'
			#	else: group = finfo['groups'][fnames['files'][niShort]['tag']]
				group = finfo['groups'][fnames['files'][niShort]['tag']]
				#print group
				N  = "MbbShape_sel%s_CAT%d_%d_%s"%(S.label,Cp,fi,group)
				NYield  = "MbbYield_sel%s_CAT%d_%d_%s"%(S.label,Cp,fi,group)
  #### Load tree
				T = F.Get("Zbb/events")
  #### Define cut
				cut = TCut("totalWeight*(bdt_Zbb>%1.4f && bdt_Zbb<=%1.4f)"%(S.boundaries[C],S.boundaries[C+1]))
  #### Draw mass
				if (group=='WJets'):	
					NBINS=11
			#	elif (group=='TTJets') or (group=='singleT'): 
			#		if Cp==2: NBINS=4
				else : NBINS=20
  				hMbb[N] = TH1F(N,N,NBINS,opts.X[0],opts.X[1])
				h = hMbb[N]
				h.Sumw2()
				can.cd()
				T.Draw("mbbRegFSR>>%s"%(h.GetName()),cut)
				hMbbYield[NYield] = h.Clone(NYield)
				hY = hMbbYield[NYield]
				xsec,npass = float(fnames['files'][niShort]['xsec']),float(fnames['files'][niShort]['npassed'])
				hY.Scale(opts.LUMI[iS]*xsec/npass)

#
#--- end of FILE loop
#
  ### Group histograms
			hW,hST,hTT,hT = None,None,None,None
			for hi,h in enumerate(hMbb.itervalues()):
				nh = h.GetName()
				if not "CAT%d"%Cp in nh: continue
				if 'WJets' in nh: hW = h.Clone("W")
				elif 'TTJets' in nh: hTT = h.Clone("TT")
				elif 'singleT' in nh: 
					if not hST: hST = h.Clone("ST")
					else: hST.Add(h)
			hT = hTT.Clone("Top")
			hT.Add(hST)
 ### Group yields
			hWY,hSTY,hTTY,hTY = None,None,None,None
			for hi,hY in enumerate(hMbbYield.itervalues()):
				nh = hY.GetName()
				if not "CAT%d"%Cp in nh: continue
				if 'WJets' in nh: hWY = hY.Clone("WYield")
				elif 'TTJets' in nh: hTTY = hY.Clone("TTYield")
				elif 'singleT' in nh: 
					if not hSTY: hSTY = hY.Clone("STYield")
					else: hSTY.Add(hY)
			hTY = hTTY.Clone("TopYield")
			hTY.Add(hSTY)
			for o in hW,hST,hTT,hT,hWY,hSTY,hTTY,hTY: archive += [o]


####################################################################################################
#### Start of RooFit part 
  ## Yields
			x   = RooRealVar("mbbReg_CAT%d"%Cp,"mbbReg_CAT%d"%Cp,opts.X[0],opts.X[1])
			YW  = RooRealVar("yield_WJets_CAT%d"%Cp,"yield_WJets_CAT%d"%Cp,hWY.Integral())
			YTT = RooRealVar("yield_TTJets_CAT%d"%Cp,"yield_TTJets_CAT%d"%Cp,hTTY.Integral())
			YST = RooRealVar("yield_singleT_CAT%d"%Cp,"yield_singleT_CAT%d"%Cp,hSTY.Integral())
			YT  = RooRealVar("yield_Top_CAT%d"%Cp,"yield_Top_CAT%d"%Cp,hTY.Integral())
  ## W Fit
			rh_W["CAT%d"%Cp] = RooDataHist("roohist_W_CAT%d"%Cp,"roothist_W_CAT%d"%Cp,RooArgList(x),hW)
			mW              = RooRealVar("W_mean_CAT%d_13TeV"%Cp,"W_mean_CAT%d_13TeV"%Cp,95,80,110)
			sW              = RooRealVar("W_sigma_CAT%d_13TeV"%Cp,"W_sigma_CAT%d_13TeV"%Cp,12,9,20)
			mWShift         = RooFormulaVar("W_mean_shifted_CAT%d"%Cp,"@0*@1",RooArgList(mW,kJES[iS]))
			sWShift         = RooFormulaVar("W_sigma_shifted_CAT%d"%Cp,"@0*@1",RooArgList(sW,kJER[iS]))
			aW              = RooRealVar("W_a_CAT%d"%Cp,"W_a_CAT%d"%Cp,-1,-10,10)
			nW              = RooRealVar("W_n_CAT%d"%Cp,"W_n_CAT%d"%Cp,1,0,10)
			Wb0,Wb1,Wb2     = [RooRealVar("W_b%d_CAT%d"%(i,Cp),"W_b%d_CAT%d"%(i,Cp),0.5,0,1) for i in range(3)]
  ### Bkg part: Bernstein
  			Wbkg            = RooBernstein("W_bkg_CAT%d"%Cp,"W_bkg_CAT%d"%Cp,x,RooArgList(Wb0,Wb1,Wb2))
  ### Sig part: Crystal Ball
  			Wcore           = RooCBShape("Wcore_CAT%d"%Cp,"Wcore_CAT%d"%Cp,x,mWShift,sWShift,aW,nW)
			fWsig           = RooRealVar("fWsig_CAT%d"%Cp,"fWsig_CAT%d"%Cp,0.7,0,1)
  ### Combined model
  			modelW          = RooAddPdf("W_model_CAT%d"%Cp,"W_model_CAT%d"%Cp,RooArgList(Wcore,Wbkg),RooArgList(fWsig))
  ### Fit W
  			resW            = modelW.fitTo(rh_W["CAT%d"%Cp],RooFit.Save())
			resW.Print()
  ### Draw Z
  			RooDraw(canW,x,rh_W["CAT%d"%Cp],modelW,S,C,Cp,"W template",archive)
			canW.cd(C+1)
			pCMS1.Draw()
			pCMS2.Draw()

  ## T Fit
  			rh_T["CAT%d"%Cp] = RooDataHist("roohist_Top_CAT%d"%Cp,"roohist_Top_CAT%d"%Cp,RooArgList(x),hTY) # if C<3 else hSTY)
			mT              = RooRealVar("Top_mean_CAT%d_13TeV"%Cp,"Top_mean_CAT%d_13TeV"%Cp,130,0,200)
			sT              = RooRealVar("Top_sigma_CAT%d_13TeV"%Cp,"Top_sigma_CAT%d_13TeV"%Cp,50,0,200)
			mTShift         = RooFormulaVar("Top_mean_shifted_CAT%d"%Cp,"@0*@1",RooArgList(mT,kJES[iS]))
			sTShift         = RooFormulaVar("Top_sigma_shifted_CAT%d"%Cp,"@0*@1",RooArgList(sT,kJER[iS]))
  ### Full model: Gaussian
			modelT          = RooGaussian("Top_model_CAT%d"%Cp,"Top_model_CAT%d"%Cp,x,mTShift,sTShift)
  ### Fit T
			resT            = modelT.fitTo(rh_T["CAT%d"%Cp],RooFit.Save(),RooFit.SumW2Error(kTRUE))#,"q")
  ### Draw T
			RooDraw(canT,x,rh_T["CAT%d"%Cp],modelT,S,C,Cp,"Top template",archive)
			canT.cd(C+1)
			pCMS1.Draw()
			pCMS2.Draw()

#### Set Constants
			for o in [mW,sW,aW,nW,Wb0,Wb1,Wb2,fWsig,mT,sT]: 
				o.setConstant(kTRUE)
#### Import objects
			for o in [modelW,modelT,YW,YT,YTT,YST]:
				getattr(w,'import')(o,ROOT.RooCmdArg())
				if opts.verbosity>0 and not opts.quiet: o.Print()

#
#--- end of CAT loop
#

		makeDirs("%s/plot/bkgTemplates/"%opts.workdir)
		canW.SaveAs("%s/plot/bkgTemplates/%s.pdf"%(opts.workdir,canW.GetName()))
		canW.SaveAs("%s/plot/bkgTemplates/%s.png"%(opts.workdir,canW.GetName()))
		canT.SaveAs("%s/plot/bkgTemplates/%s.pdf"%(opts.workdir,canT.GetName()))
		canT.SaveAs("%s/plot/bkgTemplates/%s.png"%(opts.workdir,canT.GetName()))
	
		canW.Close()
		canT.Close()
		can.Close()
#
#--- end of SEL loop
#

	makeDirs("%s/root/"%opts.workdir)
	w.writeToFile("%s/root/bkg_shapes_workspace%s.root"%(opts.workdir,"" if not opts.long else longtag))

####################################################################################################
if __name__=='__main__':
	main()
