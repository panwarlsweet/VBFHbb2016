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

def parser(mp=None):
	if not mp: mp = OptionParser()
	mg1 = OptionGroup(mp,'Selection setup')
	mg1.add_option('--SELCATs',help=colours[5]+'Selection/Category setup.'+colours[0],default='double;DoubleB;0.0875#0.5775#0.7875#1.,single;SingleB;0.0775#0.5775#0.7775#0.8775#1.',type='str',action='callback',callback=SELsetup,dest='SC')# final
	mp.add_option_group(mg1)
	mg2 = OptionGroup(mp,'Sig template setup')
	mg2.add_option('--bounds',help=colours[5]+'Template boundaries: 80,200 (min,max)'+colours[0],default=[80.,200.],type='str',action='callback',callback=optsplitfloat,dest='X')
	mg2.add_option('--binwidth',help=colours[5]+'Binwidth: 0.1,0.1 (Single,Double)'+colours[0],default=[0.1,0.1],type='str',action='callback',callback=optsplitfloat,dest='dX')
	mg2.add_option('--lumi',help=colours[5]+'Luminosity: 35900 (Single,Double)'+colours[0],default=[35900.,35900.],type='str',action='callback',callback=optsplitfloat,dest='LUMI')
	mp.add_option_group(mg2)
	return mp


def style():
	gROOT.SetBatch(1)
	gROOT.ProcessLineSync(".x %s/styleCMSTDR.C"%basepath)
	gROOT.ForceStyle()
	gStyle.SetPadTopMargin(0.06)
	gStyle.SetPadRightMargin(0.04)
	gROOT.ProcessLineSync("gErrorIgnoreLevel = kWarning;")
	RooMsgService.instance().setSilentMode(kTRUE)
	for i in range(2): RooMsgService.instance().setStreamStatus(i,kFALSE)



####################################################################################################
def main():
# Parse options
	mp = parser()
	opts,args = mp.parse_args()

# Style
	style()

# Create directories if needed
	SC = opts.SC if not type(opts.SC)==str else SELsetup(opts.SC)
	LUMI = opts.LUMI
	NBINS = [int((opts.X[1]-opts.X[0])/x) for x in opts.dX] 

# Setup
	SC = opts.SC if not type(opts.SC)==str else SELsetup(opts.SC)
	fnames = json.loads(filecontent("%s/vbfHbb_samples_2016_sig.json"%basepath))

 ## File reading
	inf = {} 
	for f in [x['fname'] for x in fnames['files'].itervalues()]:
		mass=125
		styp = re.search('.*(single|double).*',f).group(1)
		ftyp = re.search('.*(VBF|GluGlu)HToBB.*',f).group(1)
		if not mass in inf: inf[mass] = {}
		if not styp in inf[mass]: inf[mass][styp] = {}
		inf[mass][styp][ftyp] = TFile.Open("/afs/cern.ch/work/n/nchernya/VBFHbb_2016/VBF_combine/inputs/root/"+f,'read')

 	hVBF = {}
 	hVBFGF = {}
	hGF  = {}
	hTOT = {}
# Selection loop
	for iS,S in enumerate(SC.selections):
		fVBF = inf[mass][S.tag]['VBF']
		fGF  = inf[mass][S.tag]['GluGlu']
		fin = TFile.Open("/afs/cern.ch/work/n/nchernya/VBFHbb_2016/VBF_combine/inputs/root/FitVBF_BTagCSV_analysis_%s_trignone_v25_VBF_newReg.root"%(str.lower(S.tag)),"read")
		sVBF = float(fnames['files'][os.path.split(fVBF.GetName())[1]]['scale'])
		sGF  = float(fnames['files'][os.path.split(fGF.GetName())[1]]['scale'])
		tVBF = fVBF.Get("VBF/events")
		tGF  = fGF.Get("VBF/events")
		T = fin.Get("VBF/events")
		hTOT = {}
		yVBF = {}
		yGF  = {}
		hData={}

### Category loop
		for C in range(S.ncat):
			Cp = C + sum([x for x in SC.ncats[0:iS]])
			cut = TCut("totalWeight*(bdt_VBF>%1.4f && bdt_VBF<=%1.4f)"%(S.boundaries[C],S.boundaries[C+1]))
			cutData    = TCut("(bdt_VBF>%1.4f && bdt_VBF<=%1.4f)"%(S.boundaries[C],S.boundaries[C+1]))
  			N = "mH%d_sel%s_CAT%d"%(mass,S.tag,Cp)
  			hVBF[N] = TH1F("MbbShape_VBF_mH%d_sel%s_CAT%d"%(mass,S.tag,Cp),"MbbShape_VBF_mH%d_sel%s_CAT%d"%(mass,S.tag,Cp),NBINS[iS],opts.X[0],opts.X[1])
  			hGF[N]  = TH1F("MbbShape_GF_mH%d_sel%s_CAT%d"%(mass,S.tag,Cp),"MbbShape_GF_mH%d_sel%s_CAT%d"%(mass,S.tag,Cp),NBINS[iS],opts.X[0],opts.X[1])
			hData[N]   = TH1F("hMbb_%s"%N,"hMbb_%s"%N,NBINS[iS],opts.X[0],opts.X[1])
			tVBF.Draw("mbbRegFSR>>%s"%(hVBF[N].GetName()),cut)
			tGF.Draw("mbbRegFSR>>%s"%(hGF[N].GetName()),cut)
			T.Draw("mbbRegFSR>>%s"%(hData[N].GetName()),cutData)
			hVBFGF[N]=hVBF[N].Clone("MbbShape_VBFGF_mH%d_sel%s_CAT%d"%(mass,S.tag,Cp))
			hVBF[N].Scale(LUMI[iS]/sVBF)
			hGF[N].Scale(LUMI[iS]/sGF)
			hTOT[N] = hVBF[N].Clone("mass_Total_%s"%N)
			hTOT[N].Add(hGF[N])
		#	print Cp, hGF[N].Integral(), hVBF[N].Integral()
			cat_name=''
			if Cp>2 : cat_name='\SB'
			if Cp<=2 : cat_name='\DB'
			print Cp, '&',cat_name ,'& $','%.3f' %S.boundaries[C],'-','%.3f'%S.boundaries[C+1],'$ &',"%.3f" %(hGF[N].Integral()/hTOT[N].Integral()),'&','%.4f'%(hTOT[N].Integral()/hData[N].Integral()),'%.4f'%(hTOT[N].Integral()/sqrt(hData[N].Integral())),'\\'



####################################################################################################
if __name__=='__main__':
	main()
