from ROOT import *

func_r = TF1("erffunc","[0]/2.*(1.+TMath::Erf((x-[1])/[2]))",0.,1000.)
func_r_up = TF1("erffunc_up","[0]/2.*(1.+TMath::Erf((x-[1])/[2]))",0.,1000.)
func_r_down = TF1("erffunc_down","[0]/2.*(1.+TMath::Erf((x-[1])/[2]))",0.,1000.)

func_erf_btag= TF1("func_erf_btag","1.+ [3] + [0]/2.*(1.-TMath::Erf((x-[1])/[2]))",-10.,600.)
func_erf_btag_up= TF1("func_erf_btag_up","1.+ [3] + [0]/2.*(1.-TMath::Erf((x-[1])/[2]))",-10.,600.)
func_erf_btag_down= TF1("func_erf_btag_down","1.+ [3] + [0]/2.*(1.-TMath::Erf((x-[1])/[2]))",-10.,600.)



trigWeight_up = 1.;
trigWeight_down = 1.;
trigCor1_nom = [8.27936e+01 , 6.14282e+01,4.82877e+01]
trigCor2_nom = [2.30286e+01,  3.08334e+01,2.03703e+01]
trigCor1_up = [  6.98042e+01, 5.73656e+01,  4.61869e+01   ]
trigCor2_up = [  4.32075e+01, 3.95342e+01,  2.47467e+01 ]
trigCor1_down = [ 8.73145e+01,6.46045e+01,  4.98213e+01 ]
trigCor2_down = [1.98761e+01 , 2.59148e+01 ,  1.66816e+01 ]
trigCor_1btag_single = [  2.13366e-01,  2.43250e-01 ,  4.53758e-01 , -3.63544e-03 ]
trigCor_1btag_single_up = [   2.45483e-01,  2.17494e-02 , 6.02979e-01 ]
trigCor_1btag_single_down = [ 2.40780e-01,  4.01189e-01, 4.70670e-01   ]
trigCor_1btag_double = [ 5.65460e-01, -3.76206e-01 ,   9.45785e-01]
trigCor_1btag_double_up = [7.81024e-01, -6.22089e-01, 1.00052e+00]
trigCor_1btag_double_down = [4.77663e-01 ,  -1.66043e-01,1.00580e+00 ]
trigCor_2btag_double = [ 1.54834e-01,  -3.25802e-01,  3.62393e-01, -4.95807e-02  ]
trigCor_2btag_double_up = [1.27846e-01,-3.18694e-01,1.61907e-01,-4.82113e-03  ]
trigCor_2btag_double_down = [  3.27936e+01 , -7.55034e+00 ,3.85816e+00, -1.35285e-01   ]



func_r.FixParameter(0,1.)
func_r.FixParameter(1,trigCor1_nom[2] )
func_r.FixParameter(2,trigCor2_nom[2] )
func_r_up.FixParameter(0,1.)
func_r_up.SetLineColor(kBlue)
func_r_up.FixParameter(1,trigCor1_up[2] )
func_r_up.FixParameter(2,trigCor2_up[2] )
func_r_down.FixParameter(0,1.)
func_r_down.SetLineColor(kGreen)
func_r_down.FixParameter(1,trigCor1_down[2] )
func_r_down.FixParameter(2,trigCor2_down[2] )


func_erf_btag.FixParameter(0,trigCor_2btag_double[0])
func_erf_btag.FixParameter(1,trigCor_2btag_double[1])
func_erf_btag.FixParameter(2,trigCor_2btag_double[2])
func_erf_btag.FixParameter(3,0)
func_erf_btag.FixParameter(3,trigCor_2btag_double[3])

func_erf_btag_up.FixParameter(0,trigCor_2btag_double_up[0])
func_erf_btag_up.SetLineColor(kBlue)
func_erf_btag_up.FixParameter(1,trigCor_2btag_double_up[1])
func_erf_btag_up.FixParameter(2,trigCor_2btag_double_up[2])
func_erf_btag_up.FixParameter(3,0.)
func_erf_btag_up.FixParameter(3,trigCor_2btag_double_up[3])

func_erf_btag_down.FixParameter(0,trigCor_2btag_double_down[0])
func_erf_btag_down.SetLineColor(kGreen)
func_erf_btag_down.FixParameter(1,trigCor_2btag_double_down[1])
func_erf_btag_down.FixParameter(2,trigCor_2btag_double_down[2])
func_erf_btag_down.FixParameter(3,0.)
func_erf_btag_down.FixParameter(3,trigCor_2btag_double_down[3])


c = TCanvas("canv")
frame = TH1F("frame","",1,-2,10)
frame.SetStats(0)
frame.GetYaxis().SetRangeUser(0.7,1.6)
frame.Draw()
#func_r.Draw()
#func_r_up.Draw("same")
#func_r_down.Draw("same")
func_erf_btag_up.Draw("same")
func_erf_btag.Draw("same")
func_erf_btag_down.Draw("same")
c.SaveAs("c_btag1.png")
