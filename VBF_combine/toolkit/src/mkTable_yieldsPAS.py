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
#	NBINS = [int((opts.X[1]-opts.X[0])/x) for x in opts.dX] 
	NBINS=[1 for x in opts.dX]	

# Setup
	SC = opts.SC if not type(opts.SC)==str else SELsetup(opts.SC)
	fnames = json.loads(filecontent("%s/vbfHbb_samples_2016_sig.json"%basepath))
	fnames2 = json.loads(filecontent("%s/vbfHbb_samples_2016_yields.json"%basepath))
	finfo  = json.loads(filecontent("%s/vbfHbb_info_2016.json"%basepath))

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
	yVBFY=[]
	eyVBFY=[]
	yGFY=[]
	yDataY=[]
	eyGFY=[]
	yWY,yZY,ySTY,yTTY = [],[],[],[]
	eyWY,eyZY,eySTY,eyTTY = [],[],[],[]
	yVV, yVH, ybbH, yttH, yQCD = [], [] , [] , [] ,[]
	eyVV, eyVH,eybbH, eyttH, eyQCD = [], [] , [] , [] ,[]
# Selection loop
	for iS,S in enumerate(SC.selections):
 		hMbb = {}
 		hMbbYield = {}
		inf2 = [None]*(len(fnames2['files'])/2)
		fi = 0
		for f in fnames2['files'].itervalues():
			if '%s'%S.tag in f['fname']:
				inf2[fi] = TFile.Open("/afs/cern.ch/work/n/nchernya/VBFHbb_2016/VBF_combine/inputs/root/"+f['fname'],'read')
				fi += 1

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
	#	for C in range(2):
			Cp = C + sum([x for x in SC.ncats[0:iS]]) -1
			cut = TCut("totalWeight*(bdt_VBF>%1.4f && bdt_VBF<=%1.4f)"%(S.boundaries[C],S.boundaries[C+1]))
			cutData    = TCut("(bdt_VBF>%1.4f && bdt_VBF<=%1.4f)"%(S.boundaries[C],S.boundaries[C+1]))
  			N = "mH%d_sel%s_CAT%d"%(mass,S.tag,Cp)
  			hVBF[N] = TH1F("MbbShape_VBF_mH%d_sel%s_CAT%d"%(mass,S.tag,Cp),"MbbShape_VBF_mH%d_sel%s_CAT%d"%(mass,S.tag,Cp),NBINS[iS],opts.X[0],opts.X[1])
  			hGF[N]  = TH1F("MbbShape_GF_mH%d_sel%s_CAT%d"%(mass,S.tag,Cp),"MbbShape_GF_mH%d_sel%s_CAT%d"%(mass,S.tag,Cp),NBINS[iS],opts.X[0],opts.X[1])
			hData[N]   = TH1F("hMbb_%s"%N,"hMbb_%s"%N,NBINS[iS],opts.X[0],opts.X[1])
			hVBF[N].Sumw2()
			hGF[N].Sumw2()
			tVBF.Draw("mbbRegFSR>>%s"%(hVBF[N].GetName()),cut)
			tGF.Draw("mbbRegFSR>>%s"%(hGF[N].GetName()),cut)
			T.Draw("mbbRegFSR>>%s"%(hData[N].GetName()),cutData)
			hVBF[N].Scale(LUMI[iS]/sVBF)
			hGF[N].Scale(LUMI[iS]/sGF)
			hTOT[N] = hVBF[N].Clone("mass_Total_%s"%N)
			hTOT[N].Add(hGF[N])
			yVBFY.append(hVBF[N].Integral())
			eyVBFY.append(hVBF[N].GetBinError(1))
			yGFY.append(hGF[N].Integral())
			eyGFY.append(hGF[N].GetBinError(1))
			yDataY.append(hData[N].Integral())
		#	print Cp, hGF[N].Integral(), hVBF[N].Integral()
			cat_name=''
			if Cp>2 : cat_name='\SB'
			if Cp<=2 : cat_name='\DB'
#			print Cp, '&',cat_name ,'& $','%.3f' %S.boundaries[C],'-','%.3f'%S.boundaries[C+1],'$ &',"%.3f" %(hGF[N].Integral()/hTOT[N].Integral()),'&','%.4f'%(hTOT[N].Integral()/hData[N].Integral()),'%.4f'%(hTOT[N].Integral()/sqrt(hData[N].Integral())),'\\'
				


### File loop
			for fi,F in enumerate(inf2):
				ni = F.GetName()
				niShort = os.path.split(F.GetName())[1]
			#	print os.path.split(F.GetName())[1]
			#	niShort = re.search('FitVBF_(.*)_analysis',ni).group(1)
			#	group = niShort
				group = finfo['groups'][fnames2['files'][niShort]['tag']]
				N  = "MbbShape_sel%s_CAT%d_%d_%s"%(S.label,Cp,fi,group)
				NYield  = "MbbYield_sel%s_CAT%d_%d_%s"%(S.label,Cp,fi,group)
				T2 = F.Get("VBF/events")
				cut2 = TCut("totalWeight*(bdt_VBF>%1.4f && bdt_VBF<=%1.4f)"%(S.boundaries[C],S.boundaries[C+1]))
  				hMbb[N] = TH1F(N,N,NBINS[iS],opts.X[0],opts.X[1])
				hMbb[N].Sumw2()
				T2.Draw("mbbRegFSR>>%s"%(hMbb[N].GetName()),cut)
				xsec,npass = float(fnames2['files'][niShort]['xsec']),float(fnames2['files'][niShort]['npassed'])
				hMbb[N].Scale(LUMI[iS]*xsec)
				hMbb[N].Scale(1./npass)
				hMbbYield[NYield] = hMbb[N].Clone(NYield)
				hY = hMbbYield[NYield]
#
#--- end of FILE loop
#
 ### Group yields
			hWY,hZY,hSTY,hTTY = None,None,None,None
			hVV,hbbH, hVH,httH, hQCD = None,None,None,None,None
			for hi,hY in enumerate(hMbbYield.itervalues()):
				nh = hY.GetName()
				if not "CAT%d"%Cp in nh: continue
				if 'ZJets' in nh: 
					hZY = hY.Clone("ZYield")
					yZY.append(hZY.Integral())
					eyZY.append(hZY.GetBinError(1))
				elif 'WJets' in nh: 
					hWY = hY.Clone("WYield")
					yWY.append(hWY.Integral())
					eyWY.append(hWY.GetBinError(1))
			#		print hWY.Integral(), hWY.GetBinContent(1)
				elif 'TTJets' in nh: 
					hTTY = hY.Clone("TTYield")
					yTTY.append(hTTY.Integral())
					eyTTY.append(hTTY.GetBinError(1))
				elif 'singleT' in nh: 
					if not hSTY: 
						hSTY = hY.Clone("STYield")
						ySTY.append(hSTY.Integral())
						eySTY.append(hSTY.GetBinError(1))
					else: 
						hSTY.Add(hY)
						ySTY[-1] = hSTY.Integral()
						eySTY[-1] = hSTY.GetBinError(1)
				elif 'VV' in nh: 
					if not hVV: 
						hVV = hY.Clone("VVield")
						yVV.append(hVV.Integral())
						eyVV.append(hVV.GetBinError(1))
					else: 
						hVV.Add(hY)
						yVV[-1] = hVV.Integral()
						eyVV[-1] = hVV.GetBinError(1)
				elif 'VH' in nh: 
					if not hVH: 
						hVH = hY.Clone("VHield")
						yVH.append(hVH.Integral())
						eyVH.append(hVH.GetBinError(1))
					else: 
						hVH.Add(hY)
						yVH[-1] = hVH.Integral()
						eyVH[-1] = hVH.GetBinError(1)
				elif 'ttH' in nh: 
					if not httH: 
						httH = hY.Clone("ttHield")
						yttH.append(httH.Integral())
						eyttH.append(httH.GetBinError(1))
					else: 
						httH.Add(hY)
						yttH[-1] = httH.Integral()
						eyttH[-1] = httH.GetBinError(1)
				elif 'bbH' in nh: 
					if not hbbH: 
						hbbH = hY.Clone("bbHield")
						ybbH.append(hbbH.Integral())
						eybbH.append(hbbH.GetBinError(1))
					else: 
						hbbH.Add(hY)
						ybbH[-1] = hbbH.Integral()
						eybbH[-1] = hbbH.GetBinError(1)
				elif 'QCD' in nh: 
					if not hQCD: 
						hQCD = hY.Clone("QCDield")
						yQCD.append(hQCD.Integral())
						eyQCD.append(hQCD.GetBinError(1))
					else: 
						hQCD.Add(hY)
						yQCD[-1] = hQCD.Integral()
						eyQCD[-1] = hQCD.GetBinError(1)
	

	
	for i in range(0,7):
 		print yDataY[i],' &	 ',
	print ''

	for i in range(0,7):
 		print '%.2f'%yZY[i],'$\pm$','%.2f'%eyZY[i],' &	 ',
	print ''
	for i in range(0,7):
 		print '%.2f'%yWY[i],'$\pm$','%.2f'%eyWY[i],' &	 ',
	print ''
	for i in range(0,7):
 		print '%.2f'%yTTY[i],'$\pm$','%.2f'%eyTTY[i],' &	 ',
	print ''
	for i in range(0,7):
 		print '%.2f'%ySTY[i],'$\pm$','%.2f'%eySTY[i],' &	 ',
	print ''

	
	for i in range(0,7):
 		print '%.2f'%yVBFY[i],'$\pm$','%.2f'%eyVBFY[i],' &	 ',
	print ''
	for i in range(0,7):
 		print '%.2f'%yGFY[i],'$\pm$','%.2f'%eyGFY[i],' &	 ',
	print ''
	for i in range(0,7):
 		print '%.2f'%yttH[i],'$\pm$','%.2f'%eyttH[i],' &	 ',
	print ''


	print ''
	print ''
	print ''



####################################################################################################


####################################################################################################
if __name__=='__main__':
	main()
