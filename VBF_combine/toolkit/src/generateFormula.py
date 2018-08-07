import ROOT
from ROOT import RooFit,RooRealVar
import math
import sys
from  pdf_param_cfi import *

def generate_formula(pdf_name="POL8",x_name='mbbReg_CAT0',selection="double"):
	brn_names = []
	n_param = Nparam[pdf_name]
	for p in xrange(n_param):   
		cat_num=0
		if selection=="double" : cat_num=0
		if selection=="single" : cat_num=4
		nb = "b%d_sel%s_CAT%d"%(p,selection,cat_num)
		brn_names.append(nb)
	if pdf_name=="expPow":            
		const30 = '30'
		formula = "TMath::Power((%s-%s),%s)*TMath::Exp(-1*%s*TMath::Power(%s,%s))"%(x_name,const30,brn_names[0],brn_names[1],x_name,brn_names[2])
	elif pdf_name=="modG":            
		formula = "TMath::Exp(-1.*%s*%s)*TMath::Erfc(%s-%s*%s)"%(x_name,brn_names[0],brn_names[1],brn_names[2],x_name)
        elif pdf_name=="modG4":
		formula = "TMath::Exp(-1.*%s*%s-%s*TMath::Power(%s,2)-%s*TMath::Power(%s,3)-%s*TMath::Power(%s,4))*TMath::Erfc(%s-%s*%s)"%(x_name,brn_names[0],brn_names[1],x_name,brn_names[2],x_name,brn_names[3],x_name,brn_names[4],brn_names[5],x_name)
	elif pdf_name=="tanhPol2":            
		formula = "TMath::TanH(%s*(%s-%s))*(%s*TMath::Power(%s,2)+%s*%s+1.)"%(brn_names[0],x_name,brn_names[1],brn_names[2],x_name,brn_names[3],x_name)
	elif pdf_name=="tanh":            
		formula = "%s-TMath::TanH(%s*%s-%s)"%(brn_names[0],brn_names[1],x_name,brn_names[2])
	elif pdf_name=="tanh2":
		formula = "%s-%s*TMath::TanH(%s*%s-%s)-%s*TMath::Power(TMath::TanH(%s*%s-%s),2)"%(brn_names[0],brn_names[1],x_name,brn_names[2],brn_names[3],brn_names[4],x_name,brn_names[2],brn_names[3])
	elif pdf_name=="tanhPol3":            
		formula = "TMath::TanH(%s*(%s-%s))*(%s*TMath::Power(%s,3)+%s*TMath::Power(%s,2)+%s*%s+1.)"%(brn_names[0],x_name,brn_names[1],brn_names[2],x_name,brn_names[3],x_name,brn_names[4],x_name)
	elif pdf_name=="erfPol2":            
		formula = "TMath::Erf((%s-%s)/%s)*(%s*TMath::Power(%s,2)+%s*%s+1.)"%(x_name,brn_names[0],brn_names[1],brn_names[2],x_name,brn_names[3],x_name)
	elif pdf_name=="erfPol3":            
		formula = "TMath::Erf((%s-%s)/%s)*(%s*TMath::Power(%s,3)+%s*TMath::Power(%s,2)+%s*%s+1.)"%(x_name,brn_names[0],brn_names[1],brn_names[2],x_name,brn_names[3],x_name,brn_names[4],x_name)
	elif pdf_name=="sine":            
		formula = "(1+%s*TMath::Sin(%s*%s+%s))"%(brn_names[0],x_name,brn_names[1],brn_names[2])
	elif pdf_name=="sine2":
		formula = "(1+%s*TMath::Sin(%s*%s+%s)+%s*TMath::Power(TMath::Sin(%s*%s+%s),2))"%(brn_names[0],x_name,brn_names[1],brn_names[2],brn_names[3],x_name,brn_names[1],brn_names[2])
	elif pdf_name=="sineErf":            
		formula = "(1+%s*TMath::Sin(%s*%s+%s))*TMath::Erfc(%s-%s*%s)"%(brn_names[0],x_name,brn_names[1],brn_names[2],brn_names[3],brn_names[4],x_name)
	elif pdf_name=="pol3_dijet":
		formula = "%s^(%s+%s*TMath::Log(%s))*(1+%s*TMath::Power(%s,1)+%s*TMath::Power(%s,2)+%s*TMath::Power(%s,3))"%(x_name,brn_names[0],brn_names[1],x_name,brn_names[2],x_name,brn_names[3],x_name,brn_names[4],x_name)
	elif pdf_name=="x^pol3":
                formula	= "TMath::Power(%s,%s+%s*TMath::Power(%s,1)+%s*TMath::Power(%s,2)+%s*TMath::Power(%s,3))"%(x_name,brn_names[0],brn_names[1],x_name,brn_names[2],x_name,brn_names[3],x_name)
        elif pdf_name=="exp_pol2":
		formula = "TMath::Exp(-1*%s*TMath::Power(%s,1)-1*%s*TMath::Power(%s,2))"%(brn_names[0],x_name,brn_names[1],x_name)
	elif pdf_name=="pol2_invdijet":
		formula = "(%s^(%s+%s*TMath::Log(%s)))*(1+%s*TMath::Power(1/%s,1)+%s*TMath::Power(1/%s,2))"%(x_name,brn_names[0],brn_names[1],x_name,brn_names[2],x_name,brn_names[3],x_name)
	print formula
	return formula
