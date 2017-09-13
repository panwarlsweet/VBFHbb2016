import ROOT
from ROOT import *


x = RooRealVar("mbbReg","mbbReg",80,200)
brn_params   = RooArgList()
brn          = {}
for ib in range(6):
	nb = "b%d"%(ib)	
	brn[nb] = RooRealVar(nb,nb,0.5,0,1000.)
	nbp = "sel"
#	if not nbp in brn_params: brn_params["a"] = RooArgList()
	brn_params.add(brn[nb])
	brn[nb].setConstant(kTRUE)
  ## x
brn["b0"].setVal(1.0444e+02)
brn["b1"].setVal(8.2299e+01)
brn["b2"].setVal(6.1091e+01)
brn["b3"].setVal(6.0909e+01)
brn["b4"].setVal(4.7898e+01)
brn["b5"].setVal(3.9749e+01)

#brn["b0"].setVal(8.7637e-01)
#brn["b1"].setVal(6.6746e-01)
#brn["b2"].setVal(6.4630e-01)
#brn["b3"].setVal(3.6274e-01)
#brn["b4"].setVal( 3.5066e-01)
#brn["b5"].setVal(2.5860e-01 )
qcd_pdf_aux = RooBernstein("qcd_model","qcd_model",x,brn_params)
fracInt = qcd_pdf_aux.createIntegral(x,ROOT.NormSet(x),Range("cut"))
print fracInt.getVal()
can = TCanvas("can","can",900,900)
can.cd()
frame=x.frame()
qcd_pdf_aux.plotOn(frame)
frame.Draw()
can.SaveAs("brn_double.png")
