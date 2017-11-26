import ROOT
from ROOT import RooFit,RooRealVar
import math
import sys
from  pdf_param_cfi import *

def generate_pdf(x=ROOT.RooRealVar(), pdf_name="expPow",x_name='mbbReg_CAT0', selection="double",gcs=[]):
	pdf = None
	coeff = ROOT.RooArgList()
	n_param = Nparam[pdf_name]
	cat_num=0
	if selection=="double" : cat_num=0
	if selection=="single" : cat_num=4
	if pdf_name=="expPow":            
		coeff.removeAll()
		brn = {}
		brn_names = []
		for p in xrange(n_param):   
		#	nb = "b%d_%s_CAT0"%(p,pdf_name)
			nb = "b%d_sel%s_CAT%d"%(p,selection,cat_num)
			brn_names.append(nb)
			brn[nb] = RooRealVar(nb,nb,0.5,0,10.)
		#	[pmin,pmax] = Parameters[pdf_name][nb] 
		#	brn[nb] = RooRealVar(nb,nb,pmin,pmax)
			coeff.add(brn[nb])
			gcs.append(brn[nb])
			const30 = '30'
		formula = "TMath::Power((%s-%s),%s)*TMath::Exp(-1*%s*TMath::Power(%s,%s))"%(x_name,const30,brn_names[0],brn_names[1],x_name,brn_names[2])
		coeff.add(x)
	#	name = "qcd_model_"+pdf_name+"_CAT0"
		name = "qcd_model_POL1POL1_CAT%d"%cat_num
		pdf = ROOT.RooGenericPdf(name,"",formula,coeff )
	elif pdf_name=="modG":            
		coeff.removeAll()
		brn = {}
		brn_names = []
		for p in xrange(n_param):   
		#	nb = "b%d_%s_CAT0"%(p,pdf_name)
			nb2 = "b%d_CAT0"%(p)
			nb = "b%d_sel%s_CAT%d"%(p,selection,cat_num)
			brn_names.append(nb)
		#	brn[nb] = RooRealVar(nb,nb,0.5,0,10.)
			[pmin,pmax] = Parameters[pdf_name][nb2] 
			brn[nb] = RooRealVar(nb,nb,pmin,pmax)
			coeff.add(brn[nb])
			gcs.append(brn[nb])
		formula = "TMath::Exp(-1.*%s*%s)*TMath::Erfc(%s-%s*%s)"%(x_name,brn_names[0],brn_names[1],brn_names[2],x_name)
		coeff.add(x)
	#	name = "qcd_model_"+pdf_name+"_CAT0"
		name = "qcd_model_POL1POL1_CAT%d"%cat_num
		pdf = ROOT.RooGenericPdf(name,"",formula,coeff )
	elif pdf_name=="tanhPol2":            
		coeff.removeAll()
		brn = {}
		brn_names = []
		for p in xrange(n_param):   
		#	nb = "b%d_%s_CAT0"%(p,pdf_name)
			nb2 = "b%d_CAT0"%(p)
			nb = "b%d_sel%s_CAT%d"%(p,selection,cat_num)
			brn_names.append(nb)
		#	brn[nb] = RooRealVar(nb,nb,0.5,0,10.)
			[pmin,pmax] = Parameters[pdf_name][nb2] 
			brn[nb] = RooRealVar(nb,nb,pmin,pmax)
			coeff.add(brn[nb])
			gcs.append(brn[nb])
		formula = "TMath::TanH(%s*(%s-%s))*(%s*TMath::Power(%s,2)+%s*%s+1.)"%(brn_names[0],x_name,brn_names[1],brn_names[2],x_name,brn_names[3],x_name)
		coeff.add(x)
	#	name = "qcd_model_"+pdf_name+"_CAT0"
		name = "qcd_model_POL1POL1_CAT%d"%cat_num
		pdf = ROOT.RooGenericPdf(name,"",formula,coeff )
	elif pdf_name=="tanh":            
		coeff.removeAll()
		brn = {}
		brn_names = []
		for p in xrange(n_param):   
		#	nb = "b%d_%s_CAT0"%(p,pdf_name)
			nb2 = "b%d_CAT0"%(p)
			nb = "b%d_sel%s_CAT%d"%(p,selection,cat_num)
			brn_names.append(nb)
		#	brn[nb] = RooRealVar(nb,nb,0.5,0,10.)
			[pmin,pmax] = Parameters[pdf_name][nb2] 
			brn[nb] = RooRealVar(nb,nb,pmin,pmax)
			coeff.add(brn[nb])
			gcs.append(brn[nb])
		formula = "%s-TMath::TanH(%s*%s-%s)"%(brn_names[0],brn_names[1],x_name,brn_names[2])
		coeff.add(x)
	#	name = "qcd_model_"+pdf_name+"_CAT0"
		name = "qcd_model_POL1POL1_CAT%d"%cat_num
		pdf = ROOT.RooGenericPdf(name,"",formula,coeff )
	elif pdf_name=="tanhPol3":            
		coeff.removeAll()
		brn = {}
		brn_names = []
		for p in xrange(n_param):   
		#	nb = "b%d_%s_CAT0"%(p,pdf_name)
			nb2 = "b%d_CAT0"%(p)
			nb = "b%d_sel%s_CAT%d"%(p,selection,cat_num)
			brn_names.append(nb)
		#	brn[nb] = RooRealVar(nb,nb,0.5,0,10.)
			[pmin,pmax] = Parameters[pdf_name][nb2] 
			brn[nb] = RooRealVar(nb,nb,pmin,pmax)
			coeff.add(brn[nb])
			gcs.append(brn[nb])
		formula = "TMath::TanH(%s*(%s-%s))*(%s*TMath::Power(%s,2)+%s*%s+1.)"%(brn_names[0],x_name,brn_names[1],brn_names[2],x_name,brn_names[3],x_name)
		coeff.add(x)
	#	name = "qcd_model_"+pdf_name+"_CAT0"
		name = "qcd_model_POL1POL1_CAT%d"%cat_num
		pdf = ROOT.RooGenericPdf(name,"",formula,coeff )
	elif pdf_name=="sine":            
		coeff.removeAll()
		brn = {}
		brn_names = []
		for p in xrange(n_param):   
		#	nb = "b%d_%s_CAT0"%(p,pdf_name)
			nb2 = "b%d_CAT0"%(p)
			nb = "b%d_sel%s_CAT%d"%(p,selection,cat_num)
			brn_names.append(nb)
		#	brn[nb] = RooRealVar(nb,nb,0.5,0,10.)
			[pmin,pmax] = Parameters[pdf_name][nb2] 
			brn[nb] = RooRealVar(nb,nb,pmin,pmax)
			coeff.add(brn[nb])
			gcs.append(brn[nb])
		formula = "(1+%s*TMath::Sin(%s*%s+%s))"%(brn_names[0],x_name,brn_names[1],brn_names[2])
		coeff.add(x)
	#	name = "qcd_model_"+pdf_name+"_CAT0"
		name = "qcd_model_POL1POL1_CAT%d"%cat_num
		pdf = ROOT.RooGenericPdf(name,"",formula,coeff )
	elif pdf_name=="sineErf":            
		coeff.removeAll()
		brn = {}
		brn_names = []
		for p in xrange(n_param):   
		#	nb = "b%d_%s_CAT0"%(p,pdf_name)
			nb2 = "b%d_CAT0"%(p)
			nb = "b%d_sel%s_CAT%d"%(p,selection,cat_num)
			brn_names.append(nb)
		#	brn[nb] = RooRealVar(nb,nb,0.5,0,10.)
			[pmin,pmax] = Parameters[pdf_name][nb2] 
			brn[nb] = RooRealVar(nb,nb,pmin,pmax)
			coeff.add(brn[nb])
			gcs.append(brn[nb])
		formula = "(1+%s*TMath::Sin(%s*%s+%s))*TMath::Erfc(%s-%s*%s)"%(brn_names[0],x_name,brn_names[1],brn_names[2],brn_names[3],brn_names[4],x_name)
		coeff.add(x)
	#	name = "qcd_model_"+pdf_name+"_CAT0"
		name = "qcd_model_POL1POL1_CAT%d"%cat_num
		pdf = ROOT.RooGenericPdf(name,"",formula,coeff )
	elif pdf_name=="erfPol2":            
		coeff.removeAll()
		brn = {}
		brn_names = []
		for p in xrange(n_param):   
		#	nb = "b%d_%s_CAT0"%(p,pdf_name)
			nb2 = "b%d_CAT0"%(p)
			nb = "b%d_sel%s_CAT%d"%(p,selection,cat_num)
			brn_names.append(nb)
		#	brn[nb] = RooRealVar(nb,nb,0.5,0,10.)
			[pmin,pmax] = Parameters[pdf_name][nb2] 
			brn[nb] = RooRealVar(nb,nb,pmin,pmax)
			coeff.add(brn[nb])
			gcs.append(brn[nb])
		formula = "TMath::Erf((%s-%s)/%s)*(%s*TMath::Power(%s,2)+%s*%s+1.)"%(x_name,brn_names[0],brn_names[1],brn_names[2],x_name,brn_names[3],x_name)
		coeff.add(x)
	#	name = "qcd_model_"+pdf_name+"_CAT0"
		name = "qcd_model_POL1POL1_CAT%d"%cat_num
		pdf = ROOT.RooGenericPdf(name,"",formula,coeff )
	elif pdf_name=="erfPol3":            
		coeff.removeAll()
		brn = {}
		brn_names = []
		for p in xrange(n_param):   
		#	nb = "b%d_%s_CAT0"%(p,pdf_name)
			nb2 = "b%d_CAT0"%(p)
			nb = "b%d_sel%s_CAT%d"%(p,selection,cat_num)
			brn_names.append(nb)
		#	brn[nb] = RooRealVar(nb,nb,0.5,0,10.)
			[pmin,pmax] = Parameters[pdf_name][nb2] 
			brn[nb] = RooRealVar(nb,nb,pmin,pmax)
			coeff.add(brn[nb])
			gcs.append(brn[nb])
		formula = "TMath::Erf((%s-%s)/%s)*(%s*TMath::Power(%s,3)+%s*TMath::Power(%s,2)+%s*%s+1.)"%(x_name,brn_names[0],brn_names[1],brn_names[2],x_name,brn_names[3],x_name,brn_names[4],x_name)
		coeff.add(x)
	#	name = "qcd_model_"+pdf_name+"_CAT0"
		name = "qcd_model_POL1POL1_CAT%d"%cat_num
		pdf = ROOT.RooGenericPdf(name,"",formula,coeff )
	if pdf_name=="Pol2":            
		coeff.removeAll()
		brn = {}
		brn_names = []
		for p in xrange(n_param):   
		#	nb = "b%d_%s_CAT0"%(p,pdf_name)
			nb = "b%d_sel%s_CAT%d"%(p,selection,cat_num)
			brn_names.append(nb)
			brn[nb] = RooRealVar(nb,nb,0.5,0,10.)
			coeff.add(brn[nb])
			gcs.append(brn[nb])
#		name = "qcd_model_"+pdf_name+"_CAT0"
		name = "qcd_model_POL1POL1_CAT%d"%cat_num
		pdf = ROOT.RooBernstein(name,"",x,coeff )
	if pdf_name=="Pol3":            
		coeff.removeAll()
		brn = {}
		brn_names = []
		for p in xrange(n_param):   
		#	nb = "b%d_%s_CAT0"%(p,pdf_name)
			nb = "b%d_sel%s_CAT%d"%(p,selection,cat_num)
			brn_names.append(nb)
			brn[nb] = RooRealVar(nb,nb,0.5,0,10.)
			coeff.add(brn[nb])
			gcs.append(brn[nb])
#		name = "qcd_model_"+pdf_name+"_CAT0"
		name = "qcd_model_POL1POL1_CAT%d"%cat_num
		pdf = ROOT.RooBernstein(name,"",x,coeff )
	if pdf_name=="Pol4":            
		coeff.removeAll()
		brn = {}
		brn_names = []
		for p in xrange(n_param):   
		#	nb = "b%d_%s_CAT0"%(p,pdf_name)
			nb = "b%d_sel%s_CAT%d"%(p,selection,cat_num)
			brn_names.append(nb)
			brn[nb] = RooRealVar(nb,nb,0.5,0,10.)
			coeff.add(brn[nb])
			gcs.append(brn[nb])
#		name = "qcd_model_"+pdf_name+"_CAT0"
		name = "qcd_model_POL1POL1_CAT%d"%cat_num
		pdf = ROOT.RooBernstein(name,"",x,coeff )
	if pdf_name=="Pol5":            
		coeff.removeAll()
		brn = {}
		brn_names = []
		for p in xrange(n_param):   
		#	nb = "b%d_%s_CAT0"%(p,pdf_name)
			nb = "b%d_sel%s_CAT%d"%(p,selection,cat_num)
			brn_names.append(nb)
			brn[nb] = RooRealVar(nb,nb,0.5,0,10.)
			coeff.add(brn[nb])
			gcs.append(brn[nb])
#		name = "qcd_model_"+pdf_name+"_CAT0"
		name = "qcd_model_POL2POL2_CAT%d"%cat_num
		pdf = ROOT.RooBernstein(name,"",x,coeff )
	if pdf_name=="Pol6":            
		coeff.removeAll()
		brn = {}
		brn_names = []
		for p in xrange(n_param):   
		#	nb = "b%d_%s_CAT0"%(p,pdf_name)
			nb = "b%d_sel%s_CAT%d"%(p,selection,cat_num)
			brn_names.append(nb)
			brn[nb] = RooRealVar(nb,nb,0.5,0,10.)
			coeff.add(brn[nb])
			gcs.append(brn[nb])
	#	name = "qcd_model_"+pdf_name+"_CAT0"
		name = "qcd_model_POL2POL2_CAT%d"%cat_num
		pdf = ROOT.RooBernstein(name,"",x,coeff )
	if pdf_name=="Pol7":            
		coeff.removeAll()
		brn = {}
		brn_names = []
		for p in xrange(n_param):   
		#	nb = "b%d_%s_CAT0"%(p,pdf_name)
			nb = "b%d_sel%s_CAT%d"%(p,selection,cat_num)
			brn_names.append(nb)
			brn[nb] = RooRealVar(nb,nb,0.5,0,10.)
			coeff.add(brn[nb])
			gcs.append(brn[nb])
	#	name = "qcd_model_"+pdf_name+"_CAT0"
		name = "qcd_model_POL2POL2_CAT%d"%cat_num
		pdf = ROOT.RooBernstein(name,"",x,coeff )
	if pdf_name=="Pol8":            
		coeff.removeAll()
		brn = {}
		brn_names = []
		for p in xrange(n_param):   
		#	nb = "b%d_%s_CAT0"%(p,pdf_name)
			nb = "b%d_sel%s_CAT%d"%(p,selection,cat_num)
			brn_names.append(nb)
			brn[nb] = RooRealVar(nb,nb,0.5,0,10.)
			coeff.add(brn[nb])
			gcs.append(brn[nb])
	#	name = "qcd_model_"+pdf_name+"_CAT0"
		name = "qcd_model_POL1POL1_CAT%d"%cat_num
		pdf = ROOT.RooBernstein(name,"",x,coeff )


	pdf.Print()
	coeff.Print()
	return [pdf, coeff]
