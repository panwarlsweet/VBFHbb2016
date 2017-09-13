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
	mp.add_option('--workdir',help=colours[5]+'Case workdir.'+colours[0],default='case0',type='str')
	mp.add_option('--long',help=colours[5]+'Long filenames.'+colours[0],default=False,action='store_true')
	mp.add_option('--bias',help=colours[5]+'Bias filenames.'+colours[0],default=False,action='store_true')
	mp.add_option('-v','--verbosity',help=colours[5]+'Verbosity.'+colours[0],default=0,action='count')
	mp.add_option('-q','--quiet',help=colours[5]+'Quiet.'+colours[0],default=True,action='store_false')

	mg1 = OptionGroup(mp,'Selection setup')
##	mg1.add_option('--SELCATs',help=colours[5]+'Selection/Category setup: "Double;DoubleB;-1.,-0.0175,0.2925,1.".'+colours[0],default='Double;DoubleB;-1.#-0.0175#0.2925#1.',type='str',action='callback',callback=SELsetup,dest='SC')# final
	mg1.add_option('--SELCATs',help=colours[5]+'Selection/Category setup: "Double;DoubleB;-1.,-0.2275, 0.1125,0.3425,1.".'+colours[0],default='Double;DoubleB;-1.#-0.2275#0.1125#0.3425#1.',type='str',action='callback',callback=SELsetup,dest='SC')# final
	mp.add_option_group(mg1)

	mg2 = OptionGroup(mp,'Datacard settings')
	mg2.add_option('--CATS',help=colours[5]+'CATMIN-CATMAX: 0,4'+colours[0],default=[0,3],type='str',action='callback',callback=optsplitint)
	mg2.add_option('--CATveto',help=colours[5]+'CATveto: (blank)'+colours[0],default=[],type='str',action='callback',callback=optsplitint)
	mg2.add_option('--bounds',help=colours[5]+'Template boundaries: 60,170 (min,max)'+colours[0],default=[60.,170.],type='str',action='callback',callback=optsplitfloat,dest='X')
	mg2.add_option('--lumi',help=colours[5]+'Luminosity: 35900. (double)'+colours[0],default=[35900.],type='str',action='callback',callback=optsplitfloat,dest='LUMI')
	mg2.add_option('--TF',help=colours[5]+'Transfer function label: POL1 (Double)'+colours[0],default=['POL1'],type='str',action='callback',callback=optsplit)
	mg2.add_option('--function',help=colours[5]+'Function for bias study :  expPow'+colours[0],default='expPow',type='str')
	mg2.add_option('--BRN',help=colours[5]+'Bernstein order: 8 (Double)'+colours[0],default=[8],type='str',action='callback',callback=optsplitint)
	mg2.add_option('--prefix',help=colours[5]+'Datacard prefix (folder): datacards/'+colours[0],default="datacards/",type='str')
	mp.add_option_group(mg2)
#	mg1.add_option('','',help=colours[5]+''+colours[0],default='',type='',dest='')
	mp.add_option_group(mg1)
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

####################################################################################################
def main():
	mp = parser()
	opts,args = mp.parse_args()
# Style
	style()

	NTOTAL=4

# Create directories if needed
	makeDirs('%s'%opts.workdir)
	makeDirs('%s/plot'%opts.workdir)
	makeDirs('%s/root'%opts.workdir)
	longtag1 = "_B%d-%d"%(opts.X[0],opts.X[1])
	longtag2 = "_B%d-%d_TF%s"%(opts.X[0],opts.X[1],opts.TF[0])
#	longtag3 = "_B%d-%d_BRN%d_TF%s"%(opts.X[0],opts.X[1],opts.BRN[0],opts.TF[0])
	longtag3 = "_BRN%d"%(opts.BRN[0])
	longtag3 = "_BRN%d"%(opts.BRN[0])
	
# Settings
	SC = opts.SC if not type(opts.SC)==str else SELsetup(opts.SC)
	TF = opts.TF
	ncats = sum(SC.ncats)
	prefix = (opts.prefix).strip('/')
	makeDirs('%s/%s'%(opts.workdir,prefix))
	CATS = list(set(range(opts.CATS[0],opts.CATS[1]+1)) - set(opts.CATveto))
	print len(CATS)

# Read files
	uncertainties = json.loads(filecontent("%s/vbfZbb_uncertainties_2016.json"%basepath))
#	fBKG = TFile.Open("%s/root/shapes_workspace%s.root"%(opts.workdir,"" if not opts.long else longtag1),"read")
#	fSIG = TFile.Open("%s/root/shapes_workspace%s.root"%(opts.workdir,"" if not opts.long else longtag1),"read")
#	fDAT = TFile.Open("%s/root/data_shapes_workspace%s.root"%(opts.workdir,"" if not opts.long else longtag1),"read")
#	fTRF = TFile.Open("%s/root/TransferFunctions%s.root"%(opts.workdir,"" if not opts.long else longtag2),"read")
	fBKG = TFile.Open("%s/root/shapes_workspace%s.root"%(opts.workdir,"" ),"read")
	fSIG = TFile.Open("%s/root/shapes_workspace%s.root"%(opts.workdir,"" ),"read")
	fDAT = TFile.Open("%s/root/data_shapes_workspace%s.root"%(opts.workdir,"" if not opts.long else longtag3),"read")
	fTRF = TFile.Open("%s/root/TransferFunctions%s.root"%(opts.workdir,"" ),"read")
	wBKG = fBKG.Get("w")
	wSIG = fSIG.Get("w")
	wDAT = fDAT.Get("w")

# Load yields
	yD,yW,yZ,yT = [],[],[],[]
	for i in range(sum(SC.ncats)):
		yD += [wDAT.var("yield_data_CAT%d"%i).getValV()]
		yW += [wDAT.var("yield_WJets_CAT%d"%i).getValV()]
		yT += [wDAT.var("yield_Top_CAT%d"%i).getValV()]
		yZ += [wSIG.var("yield_ZJets_CAT%d"%i).getValV()]
	print len(yW),len(yZ)
# Print card
#	for j,jmass in enumerate(range(115,140,5)):
	if (1>0):
		if opts.bias :
			fout = open("%s/%s/datacard_bias%s_zbb%s%s.txt"%(opts.workdir,prefix,opts.function,"" if CATS==range(NTOTAL) else "_CAT%d-CAT%d_CATveto%s"%(opts.CATS[0],opts.CATS[1],"".join(["%d"%x for x in opts.CATveto])),"" if not opts.long else longtag3),"w+")
			fout_table = open("%s/%s/table_bias%s_zbb.txt"%(opts.workdir,prefix,opts.function),"w+")
		if not opts.bias :
			fout_table = open("%s/%s/table_zbb%s.txt"%(opts.workdir,prefix,"" if not opts.long else longtag3),"w+")
			fout = open("%s/%s/datacard_zbb%s%s.txt"%(opts.workdir,prefix,"" if CATS==range(NTOTAL) else "_CAT%d-CAT%d_CATveto%s"%(opts.CATS[0],opts.CATS[1],"".join(["%d"%x for x in opts.CATveto])),"" if not opts.long else longtag3),"w+")
 ## numbers
		fout.write("imax %d\n"%len(CATS))
		fout.write("jmax *\nkmax *\n")
		fout.write("-"*100+"\n")
		fname = os.path.split(fDAT.GetName())[1]
		fname_bias = "biasCATS_shapes_workspace_%s.root"%opts.function;
		sfname = os.path.split(fSIG.GetName())[1]
 ## files
		fout.write("%-15s %-15s *   %s/%-30s %-30s\n"%("shapes","data_obs","../root",fname,"w:data_hist_$CHANNEL"))
		if not opts.bias : fout.write("%-15s %-15s *   %s/%-30s %-30s\n"%("shapes","qcd     ","../root",fname,"w:qcd_model_%s_$CHANNEL"%(''.join(opts.TF))))
		if opts.bias : fout.write("%-15s %-15s *   %s/%-30s %-30s\n"%("shapes","qcd     ","../root",fname_bias,"w:qcd_model_%s_$CHANNEL"%(''.join(opts.TF))))
		fout.write("%-15s %-15s *   %s/%-30s %-30s\n"%("shapes","top     ","../root",fname,"w:Top_model_$CHANNEL"))
		fout.write("%-15s %-15s *   %s/%-30s %-30s\n"%("shapes","wjets   ","../root",fname,"w:W_model_$CHANNEL"))
		fout.write("%-15s %-15s *   %s/%-30s %-30s\n"%("shapes","Zbb   ","../root",sfname,"w:Z_model_$CHANNEL"))
 ## top info
		fout.write("-"*100+"\n")
		fout.write("%-15s"%"bin")
		for i in CATS:
			fout.write("%-10s"%("CAT%d"%i))
		fout.write("\n")
		fout.write("%-15s"%"observation")
		for i in CATS: 
			fout.write("%-10d"%(-1))
		fout.write("\n"+"-"*100+"\n")
		fout.write("%-15s"%"bin")
		labels = ["Zbb","qcd","top","wjets"]
		for i in CATS: 
			for l in labels:
				fout.write("%-15s"%("CAT%d"%i))
		fout.write("\n")
		fout.write("%-15s"%"process")
		for i in CATS: 
			for l in labels:
				fout.write("%-15s"%l)
		fout.write("\n")
		fout.write("%-15s"%"process")
		for i in CATS: 
			fout.write("%-15d"%(0))
			fout.write("%-15d"%(1))
			fout.write("%-15d"%(1))
			fout.write("%-15d"%(1))
		fout.write("\n")
		fout.write("%-15s"%"rate")
		for i in CATS:
			fout.write("%-15s"%("%.2f"%yZ[i]))
			fout.write("%-15d"%(yD[i]))
			fout.write("%-15s"%("%.2f"%yT[i]))
			fout.write("%-15s"%("%.2f"%yW[i]))
			fout_table.write("CAT%d"%i)
			fout_table.write("\n")
			fout_table.write("%s\t%.2f"%("Zbb",yZ[i]))
			fout_table.write("\n")
			fout_table.write("%s\t%.2f"%("QCD",yD[i]))
			fout_table.write("\n")
			fout_table.write("%s\t%.2f"%("Top",yT[i]))
			fout_table.write("\n")
			fout_table.write("%s\t%.2f"%("W + jets",yW[i]))
			fout_table.write("\n")
			fout_table.write("\n")
		fout_table.close()
		fout.write("\n"+"-"*100+"\n")
  ## fixed parts
 # 		labels = ["lumi_13TeV"]
  		labels = []
		for l in labels:
			fout.write("%-25s %-15s"%(l,"lnN"))
			for i in CATS: 
				print len(uncertainties[l])
		#		k = j if len(uncertainties[l][0])==5 else i if len(uncertainties[l][0])==ncats else 0
		#		if len(uncertainties[l])==2: 
		#			fout.write("%-10s %-10s %-10s %-10s %-10s"%("%g"%uncertainties[l][0][k],"%g"%uncertainties[l][1][k],"-","-","-"))
		#		elif len(uncertainties[l])==1:
				fout.write("%-10s %-10s %-10s %-10s"%("%g"%uncertainties[l][0],"-","-","-"))
			fout.write("\n")
	#	fout.write("-"*100+"\n")
  ## QCD part
		for i in CATS: 
  			fout.write("%-25s %-8s"%("CMS_vbfbb_qcd_norm_CAT%d_13TeV"%i,"lnU"))
			for j in CATS: 
				if i==j: fout.write("%-10s %-10s %-10s %-10s"%("-","%g"%uncertainties['qcd_norm'],"-","-"))
				else:    fout.write("%-10s %-10s %-10s %-10s"%("-","-","-","-"))
			fout.write("\n")
		fout.write("-"*100+"\n")
  ## Z part
		for i in CATS: 
  			fout.write("%-25s %-8s"%("CMS_vbfbb_wjets_norm_CAT%d_13TeV"%i,"lnN"))
			for j in CATS: 
				if i==j: fout.write("%-10s %-10s %-10s %-10s"%("-","-","-","%g"%uncertainties['wjets_norm']))
				else:    fout.write("%-10s %-10s %-10s %-10s"%("-","-","-","-"))
			fout.write("\n")
  ## T part
		for i in CATS: 
  			fout.write("%-25s %-8s"%("CMS_vbfbb_top_norm_CAT%d_13TeV"%i,"lnN"))
			for j in CATS: 
				if i==j: fout.write("%-10s %-10s %-10s %-10s"%("-","-","%g"%uncertainties['top_norm'],"-"))
				else:    fout.write("%-10s %-10s %-10s %-10s"%("-","-","-","-"))
			fout.write("\n")
		fout.write("-"*100+"\n")
  ## scale/res part
  		labels = ["CMS_vbfbb_scale_mbb_13TeV","CMS_vbfbb_res_mbb_13TeV"]
		for l in labels:
			fout.write("%-30s %-10s %9s %9s\n"%(l,"param","%.1f"%uncertainties[l][0],"%g"%uncertainties[l][1]))
		fout.write("\n"+"-"*100+"\n")
  ## mean/sigma part
  		labels = ["Z_mean","Z_sigma"]
		for l in labels:
			for i in CATS: 
				n = "%s_CAT%d_13TeV"%(l,i)
				v = wSIG.var(n)
				fout.write("%-30s %-10s %9s %9s\n"%(n,"param","%g"%v.getValV(),"%g"%v.getError()))
		labels = ["Top_mean","Top_sigma","W_mean","W_sigma"]
		for l in labels:
			for i in CATS: 
				n = "%s_CAT%d_13TeV"%(l,i)
				v = wDAT.var(n)
				fout.write("%-30s %-10s %9s %9s\n"%(n,"param","%g"%v.getValV(),"%g"%(v.getError() if not 'Top' in l else v.getValV()*(0.01 if 'mean' in l else 0.05))))
  ## transfer functions
  		for iS,S in enumerate(SC.selections):
			start = sum(SC.ncats[:iS])
			end   = start + S.ncat
			if 'Fix' in opts.TF[iS]:
				for i in CATS: 
					if not (i>start and i<end): continue
					o = int(re.search('.*([0-9]{1})',opts.TF[iS]).group(1))
					for j in range(o+1):
						v = wDAT.var("trans_%s_CAT%d_p%d"%(opts.TF[iS],i,j))
						fout.write("%-30s %-10s %9.2e %9.2e\n"%(v.GetName(),"param",v.getValV(),v.getError()))
		
# Close
		fout.close()
		fDAT.Close()
		fSIG.Close()
		fBKG.Close()

if __name__=='__main__':
	main()
