##### if you want to generate toy, the label of alternative function should not have "Pol" word, otherwise it will generate pdf according to QCD POL model and you will get pdf error in toy generation. So you have to change "Pol" words for all the alternative function in generatePdf and pdf_param_cfi file also add the formula in generateFormula file#####

Nparam = {
########  exp
'expPol1' : 1,
'exp_pol2':2,
'expPol3':3,
'expPol4':4,
'expPol5':5,
'expPol6':6,
'expPol7':7,
'expPol8':8,

####### Poldijet
'Pol1_dijet' : 3,
'Pol2_dijet' : 4,
'pol3_dijet' : 5,
'Pol4_dijet' : 6,
'Pol5_dijet' : 7,
'Pol6_dijet' : 8,
'Pol7_dijet' : 9,
'Pol8_dijet' : 10,

####### Polinvdijet
'Pol1_invdijet':3,
'pol2_invdijet':4,
'Pol3_invdijet':5,
'Pol4_invdijet':6,
'Pol5_invdijet':7,
'Pol6_invdijet':8,
'Pol7_invdijet':9,

####### expPow
'expPow' : 3,
'expPow2' : 4,

#######  x^Pol
'x^Pol1' : 2,
'x^Pol2' : 3,
'x^pol3' : 4,
'x^Pol4' : 5,
'x^Pol5' : 6,

######## Pol*exp
'Pol1exp' : 1,
'Pol2exp' : 2,

###### sine
'sine' : 3,
'sine2' : 6,
'sine3' : 9,
'sine4' : 12,
'sine5' : 15,

###### sineErf
'sineErf' : 5,

####### modG
'modG' : 3,
'modG2': 4,
'modG3': 5,
'modG4': 6,
'modG5': 7,
'modG6': 8,
 
####### tanh
'tanh2' : 7,
'tanh' : 4,
'erfPol2' : 4,
'erfPol3' : 5,
'tanh3' : 10,
'tanh4' : 13,
'tanh5' : 16,
'tanh6' : 19,
'erfPol3' : 5,

######### POL
'Pol2' : 3,
'Pol3' : 4,
'Pol4' : 5,
'Pol5' : 6,
'Pol6' : 7,
'Pol7' : 8,
'Pol8' : 9
}

Parameters = {
'expPow' : {
	'b0_CAT0' : [0,2],
	'b1_CAT0' : [0,1],
	'b2_CAT0' : [0,2],
	'b0_CAT4' : [-0.7,0.7],
        'b1_CAT4' : [-0.006,0.006],
        'b2_CAT4' : [1.18,1.2]
},

'expPow2' : {
	'b0_CAT0' : [0,2],
        'b1_CAT0' : [0,1],
        'b2_CAT0' : [0,2],
	'b3_CAT0' : [0,0.000001],
        'b0_CAT4' : [-0.5,0.5],
        'b1_CAT4' : [-0.005,0.005],
        'b2_CAT4' : [1.1,1.2],
        'b3_CAT4' : [0,0.000001],
},

'expPol1' : {
	'b0_seldouble_CAT0' : [0,1],
        'b0_selsingle_CAT4' : [0,1],
},

'exp_pol2' : {
	'b0_seldouble_CAT0' : [-5,5],
	'b1_seldouble_CAT0' : [-5,5],
        'b0_selsingle_CAT4' : [-5,5],
	'b1_selsingle_CAT4' : [-5,5],
},

'expPol3' : {
	'b0_CAT0' : [-5,5],
        'b1_CAT0' : [-5,5],
	'b2_CAT0' : [-5,5],
        'b0_CAT4' : [-0.05,0.05],
        'b1_CAT4' : [-0.0005,0.0005],
	'b2_CAT4' : [-1e-05,1e-05]
},

'expPol4' : {
	'b0_seldouble_CAT0' : [-5,5],
        'b1_seldouble_CAT0' : [-5,5],
        'b2_seldouble_CAT0' : [-5,5],
	'b3_seldouble_CAT0' : [-5,5],
        'b0_selsingle_CAT4' : [-0.05,0.05],
        'b1_selsingle_CAT4' : [-0.0005,0.0005],
        'b2_selsingle_CAT4' : [-1e-05,1e-05],
	'b3_selsingle_CAT4' : [-1e-7,1e-7]
},

'expPol5' : {
	'b0_CAT0' : [-0.00926557,5],
        'b1_CAT0' : [0.000188252,1e-03],
        'b2_CAT0' : [-9.3537e-7,1e-5],
        'b3_CAT0' : [1.7654e-9,1e-7],
	'b4_CAT0' : [0,1e-09],
        'b0_CAT4' : [-0.05,.05],
        'b1_CAT4' : [-0.001,1e-03],
        'b2_CAT4' : [-1e-05,1e-05],
        'b3_CAT4' : [-3.46931e-09,1e-08],
	'b4_CAT4' : [-1e-10,1e-10],
},

'expPol6' : {
        'b0_CAT0' : [-0.00926557,5],
        'b1_CAT0' : [0.000188252,1e-03],
        'b2_CAT0' : [-9.3537e-7,1e-5],
        'b3_CAT0' : [1.7654e-9,1e-7],
        'b4_CAT0' : [1e-20,1e-09],
	'b5_CAT0' : [0,1e-11],
        'b0_CAT4' : [0.0229348,5],
        'b1_CAT4' : [-0.000275669,1e-03],
        'b2_CAT4' : [1.72816e-06,1e-05],
        'b3_CAT4' : [-3.46931e-09,1e-08],
        'b4_CAT4' : [1e-20,1e-10],
	'b5_CAT4' : [0,1e-11],
},


'expPol7' : {
        'b0_CAT0' : [-5,5],
        'b1_CAT0' : [7.24176e-08,1e-03],
        'b2_CAT0' : [4.98545e-10,1e-05],
        'b3_CAT0' : [2.2e-12,1e-07],
        'b4_CAT0' : [6.8e-14,1e-09],
	'b5_CAT0' : [0,1e-11],
        'b0_CAT4' : [-5,5],
        'b1_CAT4' : [4.83531e-07,1e-03],
        'b2_CAT4' : [1.6e-9,1e-05],
        'b3_CAT4' : [1.4e-12,1e-08],
        'b4_CAT4' : [6.9e-16,1e-10],
	'b5_CAT4' : [0.0,1e-13],
},

'expPol7' : {
	'b0_CAT0' : [-5,5],
        'b1_CAT0' : [7.24176e-08,1e-03],
        'b2_CAT0' : [4.98545e-10,1e-05],
        'b3_CAT0' : [2.2e-12,1e-07],
        'b4_CAT0' : [6.8e-14,1e-09],
        'b5_CAT0' : [8.3e-25,1e-11],
        'b6_CAT0' : [0.0,1e-13],
        'b0_CAT4' : [-5,5],
        'b1_CAT4' : [4.83531e-07,1e-03],
        'b2_CAT4' : [1.6e-9,1e-05],
        'b3_CAT4' : [1.4e-12,1e-08],
        'b4_CAT4' : [6.9e-16,1e-10],
        'b5_CAT4' : [4.7e-16,1e-13],
	'b6_CAT4' : [0.0,1e-16],
},

'expPol8' : {
	'b0_CAT0' : [0.00787389,1],
        'b1_CAT0' : [7.24176e-08,1e-03],
        'b2_CAT0' : [4.98545e-10,1e-05],
        'b3_CAT0' : [2.2e-12,1e-07],
        'b4_CAT0' : [6.8e-14,1e-09],
        'b5_CAT0' : [8.3e-25,1e-11],
        'b6_CAT0' : [1.6e-25,1e-13],
	'b7_CAT0' : [0,1e-15],
        'b0_CAT4' : [0.008533,1],
        'b1_CAT4' : [4.83531e-07,1e-03],
        'b2_CAT4' : [1.6e-9,1e-05],
        'b3_CAT4' : [1.4e-12,1e-08],
        'b4_CAT4' : [6.9e-16,1e-10],
        'b5_CAT4' : [4.7e-16,1e-13],
        'b6_CAT4' : [3.0e-19,1e-16],
	'b7_CAT4' : [0.0,1e-19]
},




'x^Pol1' : {
	'b0_CAT0' : [-5,5],
	'b1_CAT0' : [-5,5],
        'b0_CAT4' : [-5,5],
	'b1_CAT4' : [-5,5],
},

'x^Pol2' : {
	'b0_CAT0' : [-5,5],
        'b1_CAT0' : [-5,5],
	'b2_CAT0' : [-5,5],
        'b0_CAT4' : [0.824874,5],
        'b1_CAT4' : [-5,5],
	'b2_CAT4' : [-5,5],

},

'x^pol3' : {
	'b0_seldouble_CAT0' : [1,2],
        'b1_seldouble_CAT0' : [-2,0],
        'b2_seldouble_CAT0' : [-1e-04,1e-04],
	'b3_seldouble_CAT0' : [-1e-07,1e-07],
        'b0_selsingle_CAT4' : [-5,5],
        'b1_selsingle_CAT4' : [-5,5],
        'b2_selsingle_CAT4' : [-5,5],
	'b3_selsingle_CAT4' : [-5,5],
},

'x^Pol4' : {
	'b0_CAT0' : [-5,5],
        'b1_CAT0' : [-5,5],
        'b2_CAT0' : [-5,5],
        'b3_CAT0' : [-5,5],
	'b4_CAT0' : [-5,5],
        'b0_CAT4' : [-5,5],
        'b1_CAT4' : [-5,5],
        'b2_CAT4' : [-5,5],
        'b3_CAT4' : [-5,5],
	'b4_CAT4' : [-5,5],
},

'x^Pol5' : {
        'b0_CAT0' : [-5,5],
        'b1_CAT0' : [-5,5],
        'b2_CAT0' : [-5,5],
        'b3_CAT0' : [-5,5],
        'b4_CAT0' : [-5,5],
	'b5_CAT0' : [-5,5],
        'b0_CAT4' : [-5,5],
        'b1_CAT4' : [-5,5],
        'b2_CAT4' : [-5,5],
        'b3_CAT4' : [-5,5],
        'b4_CAT4' : [-5,5],
	'b5_CAT4' : [-5,5],
},

'Pol1exp' : {
	'b0_CAT0' : [-2,2],
        #'b1_CAT0' : [-5,5],
        #'b2_CAT0' : [-5,5],
        'b0_CAT4' : [-2,2],
        #'b1_CAT4' : [0,1],
        #'b2_CAT4' : [0,1]
},

'Pol2exp' : {
	'b0_CAT0' : [20,30],
        'b1_CAT0' : [-1e-03,1e-03],
        #'b2_CAT0' : [-5,5],
        'b0_CAT4' : [-0.958851,2],
        'b1_CAT4' : [-1e-03,1e-03],
        #'b2_CAT4' : [0,1]
},


'Pol1_dijet' : {
	'b0_CAT0' : [0,10],
        'b1_CAT0' : [-2,0],
        'b2_CAT0' : [-10,10],
	'b0_CAT4' : [0.0,10],
        'b1_CAT4' : [-2,0],
        'b2_CAT4' : [-10,10],
},

'Pol2_dijet' : {
	'b0_CAT0' : [5.15637,10],
	'b1_CAT0' : [ -0.74, 0],
        'b2_CAT0' : [0.0039,10],
	'b3_CAT0' : [0,10],
        'b0_CAT4' : [0,10],
        'b1_CAT4' : [-1,10],
        'b2_CAT4' : [-1,4],
	'b3_CAT4' : [-10,10],
},

'pol3_dijet' : {
        'b0_seldouble_CAT0' : [-1,2],
        'b1_seldouble_CAT0' : [-1,1],
        'b2_seldouble_CAT0' : [-1, 1],
        'b3_seldouble_CAT0' : [-1e-03, 1e-03],
        'b4_seldouble_CAT0' : [-1e-05,1e-05],
	'b0_selsingle_CAT4' : [-10,10],
        'b1_selsingle_CAT4' : [-1,10],
        'b2_selsingle_CAT4' : [-0.0027,4],
        'b3_selsingle_CAT4' : [-1e-03,10],
	'b4_selsingle_CAT4' : [-10,10],

},
'Pol4_dijet' : {
        'b0_CAT0' : [5.15641,10],
        'b1_CAT0' : [-0.739986, 0],
        'b2_CAT0' : [0.00582,5],
        'b3_CAT0' : [0.0001458,10],
        'b4_CAT0' : [-3.14864e-07,10],
	'b5_CAT0' : [-10,10],
	'b0_CAT4' : [-10,10],
        'b1_CAT4' : [-1,10],
        'b2_CAT4' : [-10,10],
        'b3_CAT4' : [-10.0,10],
        'b4_CAT4' : [-1e-03,1e-03],
	'b5_CAT4' : [-10,10],
},

'Pol5_dijet' : {
        'b0_CAT0' : [5.15772,10],
        'b1_CAT0' : [-0.739858, 0],
        'b2_CAT0' : [0.00582, 4],
        'b3_CAT0' : [0.0001460,10],
        'b4_CAT0' : [-3.14864e-07,10],
        'b5_CAT0' : [-1.45395e-11,10],
	'b6_CAT0' : [-10,10],
        'b0_CAT4' : [-10,10],
        'b1_CAT4' : [-1,20],
        'b2_CAT4' : [-20, 20],
        'b3_CAT4' : [-10,10],
        'b4_CAT4' : [-1e-3,1e-03],
        'b5_CAT4' : [-1e-5,1e-05],
	'b6_CAT4' : [-1e-7,1e-07],
},
'Pol6_dijet' : {
        'b0_CAT0' : [5.15798,10],
        'b1_CAT0' : [-0.739848, 0],
        'b2_CAT0' : [0.00582, 10],
        'b3_CAT0' : [0.0001460,10],
        'b4_CAT0' : [-3.14668e-07,10],
        'b5_CAT0' : [1.27334e-10,10],
        'b6_CAT0' : [-7.17648e-13,10],
	'b7_CAT0' : [-10,10],
        'b0_CAT4' : [-10,10],
        'b1_CAT4' : [-1,20],
        'b2_CAT4' : [-20, 20],
        'b3_CAT4' : [-10,10],
        'b4_CAT4' : [-1e-03,1e-03],
        'b5_CAT4' : [-1e-05,1e-05],
        'b6_CAT4' : [-1e-07,1e-07],
	'b7_CAT4' : [-1e-09,1e-09],
},

'Pol7_dijet' : {
        'b0_CAT0' : [5.15798,10],
        'b1_CAT0' : [-0.739848, 0],
        'b2_CAT0' : [0.00582, 10],
        'b3_CAT0' : [0.0001460,10],
        'b4_CAT0' : [-3.14668e-07,10],
        'b5_CAT0' : [1.27334e-10,10],
        'b6_CAT0' : [-10,10],
        'b7_CAT0' : [-10,10],
	'b8_CAT0' : [-10,10],
        'b0_CAT4' : [-10,10],
        'b1_CAT4' : [-1,20],
        'b2_CAT4' : [-20,20],
        'b3_CAT4' : [-10,10],
        'b4_CAT4' : [-1e-03,1e-03],
        'b5_CAT4' : [-1e-05,1e-05],
        'b6_CAT4' : [-1e-07,1e-07],
        'b7_CAT4' : [-1e-09,1e-09],
	'b8_CAT4' : [-1e-11,1e-11],
},

'Pol8_dijet' : {
        'b0_CAT0' : [5.15798,10],
        'b1_CAT0' : [-0.739848, 0],
        'b2_CAT0' : [0.00582, 10],
        'b3_CAT0' : [0.0001460,10],
        'b4_CAT0' : [-3.14668e-07,10],
        'b5_CAT0' : [1.27334e-10,10],
        'b6_CAT0' : [-10,10],
        'b7_CAT0' : [-10,10],
        'b8_CAT0' : [-10,10],
	'b9_CAT0' : [-10,10],
        'b0_CAT4' : [-10,10],
        'b1_CAT4' : [-1,20],
        'b2_CAT4' : [-20,20],
        'b3_CAT4' : [-30,30],
        'b4_CAT4' : [-1e-03,1e-03],
        'b5_CAT4' : [-1e-05,1e-05],
        'b6_CAT4' : [-1e-07,1e-07],
        'b7_CAT4' : [-1e-09,1e-09],
        'b8_CAT4' : [-1e-12,1e-12],
	'b9_CAT4' : [-1e-14,1e-14],
},

'Pol1_invdijet' : {
	'b0_CAT0' : [-10,10],
        'b1_CAT0' : [-10,10],
        'b2_CAT0' : [-10,10],
        'b0_CAT4' : [-10,10],
        'b1_CAT4' : [-10,10],
        'b2_CAT4' : [-100,100],
},

'pol2_invdijet' : {
        'b0_seldouble_CAT0' : [4.6037,10],
        'b1_seldouble_CAT0' : [-10,10],
        'b2_seldouble_CAT0' : [-100,100],
	'b3_seldouble_CAT0' : [-1000,1000],
        'b0_selsingle_CAT4' : [-10,10],
        'b1_selsingle_CAT4' : [-10,10],
        'b2_selsingle_CAT4' : [-100,100],
	'b3_selsingle_CAT4' : [-10000,10000],
},

'Pol3_invdijet' : {
        'b0_CAT0' : [4.61624,10],
        'b1_CAT0' : [-10,10],
        'b2_CAT0' : [-100,100],
        'b3_CAT0' : [-1000,1000],
	'b4_CAT0' : [-10000,10000],
        'b0_CAT4' : [9.138,10],
        'b1_CAT4' : [-10,10],
        'b2_CAT4' : [-100,100],
        'b3_CAT4' : [-10000,10000],
	'b4_CAT4' : [-100000,100000],
},

'Pol4_invdijet' : {
        'b0_CAT0' : [4.61716, 10],
        'b1_CAT0' : [-10,10],
        'b2_CAT0' : [-100,100],
        'b3_CAT0' : [-1000,1000],
        'b4_CAT0' : [-10000,10000],
	'b5_CAT0' : [-100000,100000],
        'b0_CAT4' : [9.13892,10],
        'b1_CAT4' : [-10,10],
        'b2_CAT4' : [-100,100],
        'b3_CAT4' : [-1000,1000],
        'b4_CAT4' : [-1e5,1e5],
	'b5_CAT4' : [-1e9,1e9],
},

'Pol5_invdijet' : {
        'b0_CAT0' : [4.61717, 10],
        'b1_CAT0' : [-10,10],
        'b2_CAT0' : [-100,100],
        'b3_CAT0' : [-1000,1000],
        'b4_CAT0' : [-1e4,1e4],
        'b5_CAT0' : [-1e5,1e5],
	'b6_CAT0' : [-1e6,1e6],
        'b0_CAT4' : [9.13925,10],
	'b1_CAT4' : [-10,10],
        'b2_CAT4' : [-100,100],
        'b3_CAT4' : [-10000,10000],
        'b4_CAT4' : [-1e5,1e5],
        'b5_CAT4' : [-1e7,1e7],
	'b6_CAT4' : [-1e12,1e12],
},

'Pol6_invdijet' : {
        'b0_CAT0' : [4.61717, 10],
        'b1_CAT0' : [-0.588718,10],
        'b2_CAT0' : [-7.80452,10],
        'b3_CAT0' : [19.2141,20],
        'b4_CAT0' : [13.1912,30],
        'b5_CAT0' : [9.9672,20],
        'b6_CAT0' : [-20,20],
	'b7_CAT0' : [-10,10],
        'b0_CAT4' : [9.13925,10],
	'b1_CAT4' : [-10,10],
        'b2_CAT4' : [-10,10],
        'b3_CAT4' : [-20,20],
        'b4_CAT4' : [-1e5,1e5],
        'b5_CAT4' : [-1e9,1e9],
        'b6_CAT4' : [-1e14,1e14],
	'b7_CAT4' : [-1e17,1e17],
},
'Pol7_invdijet' : {
        'b0_CAT0' : [4.61717, 10],
        'b1_CAT0' : [-0.588718,10],
        'b2_CAT0' : [-7.80452,10],
        'b3_CAT0' : [19.2141,20],
        'b4_CAT0' : [13.1912,30],
        'b5_CAT0' : [9.9672,20],
        'b6_CAT0' : [-20,20],
        'b7_CAT0' : [-10,10],
	'b8_CAT0' : [-10,10],
        'b0_CAT4' : [9.13925,10],
	'b1_CAT4' : [-10,10],
        'b2_CAT4' : [-10,10],
        'b3_CAT4' : [-20,20],
        'b4_CAT4' : [-1e5,1e5],
        'b5_CAT4' : [-1e9,1e9],
        'b6_CAT4' : [-1e15,1e15],
        'b7_CAT4' : [-1e18,1e18],
	'b8_CAT4' : [-1e20,1e20],
},

'modG' : {
	'b0_seldouble_CAT0' : [-5,5],
	'b1_seldouble_CAT0' : [-5,5],
	'b2_seldouble_CAT0' : [-0.005,0.1],
	'b0_selsingle_CAT4' : [-5,5],
        'b1_selsingle_CAT4' : [0.0,1],
        'b2_selsingle_CAT4' : [0.005,0.1],
},

'modG2' : {
        'b0_CAT0' : [-5,5],
        'b1_CAT0' : [-5,5],
        'b2_CAT0' : [-5,5],
	'b3_CAT0' : [-0.005,0.1],
        'b0_CAT4' : [-5,5],
        'b1_CAT4' : [-10,10],
        'b2_CAT4' : [-15,15],
	'b3_CAT4' : [0.005,0.1],
},

'modG3' : {
        'b0_CAT0' : [-5,5],
        'b1_CAT0' : [-5,5],
        'b2_CAT0' : [-5,5],
	'b3_CAT0' : [-5,5],
        'b4_CAT0' : [-0.005,0.1],
        'b0_CAT4' : [-5,5],
        'b1_CAT4' : [-10,10],
        'b2_CAT4' : [-15,15],
	'b3_CAT4' : [-15,15],
        'b4_CAT4' : [-0.5,0.5],
},

'modG4' : {
        'b0_seldouble_CAT0' : [-5,5],
        'b1_seldouble_CAT0' : [-5,5],
        'b2_seldouble_CAT0' : [-5,5],
        'b3_seldouble_CAT0' : [-5,5],
	'b4_seldouble_CAT0' : [-5,5],
        'b5_seldouble_CAT0' : [-0.005,0.1],
        'b0_selsingle_CAT4' : [-5,5],
        'b1_selsingle_CAT4' : [-10,10],
        'b2_selsingle_CAT4' : [-15,15],
        'b3_selsingle_CAT4' : [-15,15],
	'b4_selsingle_CAT4' : [-15,15],
        'b5_selsingle_CAT4' : [-0.5,0.5],
},

'modG5' : {
        'b0_CAT0' : [-5,5],
        'b1_CAT0' : [-5,5],
        'b2_CAT0' : [-5,5],
        'b3_CAT0' : [-5,5],
        'b4_CAT0' : [-5,5],
	'b5_CAT0' : [-5,5],
        'b6_CAT0' : [-0.005,0.1],
        'b0_CAT4' : [-5,5],
        'b1_CAT4' : [-10,10],
        'b2_CAT4' : [-15,15],
        'b3_CAT4' : [-15,15],
        'b4_CAT4' : [-15,15],
	'b5_CAT4' : [-15,15],
        'b6_CAT4' : [-0.5,0.5],
},

'modG6' : {
        'b0_CAT0' : [-5,5],
        'b1_CAT0' : [-5,5],
        'b2_CAT0' : [-5,5],
        'b3_CAT0' : [-5,5],
        'b4_CAT0' : [-5,5],
        'b5_CAT0' : [-5,5],
	'b6_CAT0' : [-5,5],
        'b7_CAT0' : [-0.005,0.1],
        'b0_CAT4' : [-5,5],
        'b1_CAT4' : [-10,10],
        'b2_CAT4' : [-15,15],
        'b3_CAT4' : [-15,15],
        'b4_CAT4' : [-15,15],
        'b5_CAT4' : [-15,15],
	'b6_CAT4' : [-15,15],
        'b7_CAT4' : [-0.5,0.5],
},


'sine' : {
	'b0_seldouble_CAT0' : [0.1,0.95],
	'b1_seldouble_CAT0' : [0.002,0.027],
	'b2_seldouble_CAT0' : [1.5,4.],
	'b0_selsingle_CAT4' : [0.1,0.95],
	'b1_selsingle_CAT4' : [0.0001,0.047],
	'b2_selsingle_CAT4' : [0.,2]
},
'sine2' : {
        'b0_CAT0' : [0.1,0.95],
        'b1_CAT0' : [0.002,0.027],
        'b2_CAT0' : [1.5,4.],
	'b3_CAT0' : [0.002,0.027],
	'b4_CAT0' : [0,0],
	'b5_CAT0' : [0,0],
        'b0_CAT4' : [0.1,0.95],
        'b1_CAT4' : [0.0001,0.047],
        'b2_CAT4' : [0.,2],
	'b3_CAT4' : [-5,5],
	'b4_CAT4' : [0,0],
	'b5_CAT4' : [0,0],
},

'sine3' : {
	'b0_CAT0' : [0.1,0.95],
        'b1_CAT0' : [0.002,0.027],
        'b2_CAT0' : [1.5,4.],
        'b3_CAT0' : [-5,5],
        'b4_CAT0' : [-5,5],
        'b5_CAT0' : [0,0],
	'b6_CAT0' : [0,0],
	'b7_CAT0' : [0,0],
	'b8_CAT0' : [0,0],
        'b0_CAT4' : [0.520617,0.95],
        'b1_CAT4' : [0.0135695,0.047],
        'b2_CAT4' : [ 1.58373,2],
        'b3_CAT4' : [-0.100083,0.0027],
        'b4_CAT4' : [0.00002,0.00027],
        'b5_CAT4' : [0,0],
	'b6_CAT4' : [0,0],
        'b7_CAT4' : [0,0],
        'b8_CAT4' : [0,0],
},
'sine4' : {
        'b0_CAT0' : [0.924155,0.95],
        'b1_CAT0' : [0.00874177,0.027],
        'b2_CAT0' : [1.74203,4.],
        'b3_CAT0' : [-5,5],
        'b4_CAT0' : [-5,5],
        'b5_CAT0' : [-5,5],
        'b6_CAT0' : [0,0],
        'b7_CAT0' : [0,0],
        'b8_CAT0' : [0,0],
	'b9_CAT0' : [0,0],
        'b10_CAT0' : [0,0],
        'b11_CAT0' : [0,0],
        'b0_CAT4' : [0.52062,0.95],
        'b1_CAT4' : [0.0135696,0.047],
        'b2_CAT4' : [1.58376,2],
        'b3_CAT4' : [-0.100082,0.0027],
        'b4_CAT4' : [2.00057e-05,0.0027],
        'b5_CAT4' : [0.0002,0.0027],
        'b6_CAT4' : [0,0],
        'b7_CAT4' : [0,0],
        'b8_CAT4' : [0,0],
	'b9_CAT4' : [0,0],
        'b10_CAT4' : [0,0],
        'b11_CAT4' : [0,0],
},
'sine5' : {
	'b0_CAT0' : [0.1,0.95],
        'b1_CAT0' : [0.002,0.027],
        'b2_CAT0' : [1.5,4.],
        'b3_CAT0' : [-5,5],
        'b4_CAT0' : [-5,5],
        'b5_CAT0' : [-5,5],
        'b6_CAT0' : [-5,5],
        'b7_CAT0' : [0,0],
        'b8_CAT0' : [0,0],
        'b9_CAT0' : [0,0],
        'b10_CAT0' : [0,0],
        'b11_CAT0' : [0,0],
	'b12_CAT0' : [0,0],
        'b13_CAT0' : [0,0],
        'b14_CAT0' : [0,0],
        'b0_CAT4' : [0.1,0.95],
        'b1_CAT4' : [0.0001,0.047],
        'b2_CAT4' : [0.,2],
        'b3_CAT4' : [0.002,0.027],
        'b4_CAT4' : [0.002,0.027],
        'b5_CAT4' : [0.0002,0.0027],
        'b6_CAT4' : [0.00002,0.00027],
        'b7_CAT4' : [0,0],
        'b8_CAT4' : [0,0],
        'b9_CAT4' : [0,0],
        'b10_CAT4' : [0,0],
	'b11_CAT4' : [0,0],
	'b12_CAT4' : [0,0],
        'b13_CAT4' : [0,0],
        'b14_CAT4' : [0,0],
},
'sineErf' : {
	'b0_CAT0' : [0.1,0.95],
	'b1_CAT0' : [0.002,0.027],
	'b2_CAT0' : [1.5,4],
	'b3_CAT0' : [0.5,30],
	'b4_CAT0' : [0.005,0.1],
	'b0_CAT4' : [0.1,0.95],
        'b1_CAT4' : [0.001,0.047],
        'b2_CAT4' : [0,2],
        'b3_CAT4' : [0.5,5],
        'b4_CAT4' : [0.01,0.1]
},
'tanh' :{
	'b0_seldouble_CAT0' : [0.005,2.],
	'b1_seldouble_CAT0' : [1,1],
	'b2_seldouble_CAT0' : [0.001,0.1],
	'b3_seldouble_CAT0' : [0.0,3],
	'b0_selsingle_CAT4' : [0.005,2.],
        'b1_selsingle_CAT4' : [1,1],
        'b2_selsingle_CAT4' : [0.001,0.1],
	'b3_selsingle_CAT4' : [0.0,3],
},
'tanh2' :{
	'b0_seldouble_CAT0' : [0.005,2.],
        'b1_seldouble_CAT0' : [1,1],
        'b2_seldouble_CAT0' : [0.001,0.1],
        'b3_seldouble_CAT0' : [-5,5],
	'b4_seldouble_CAT0' : [-10,10],
	'b5_seldouble_CAT0' : [0.0,0],
	'b6_seldouble_CAT0' : [0.0,0],
	'b7_seldouble_CAT0' : [0.0,0],
        'b0_selsingle_CAT4' : [0.005,2.],
        'b1_selsingle_CAT4' : [1,1],
        'b2_selsingle_CAT4' : [0.001,0.1],
        'b3_selsingle_CAT4' : [0,3],
	'b4_selsingle_CAT4' : [-5,5], 	
        'b5_selsingle_CAT4' : [0.0,0],
        'b6_selsingle_CAT4' : [0.0,0],
        'b7_selsingle_CAT4' : [0.0,0],
},

'tanh3' :{
	'b0_tanh3_CAT0' : [0.005,2.],
        'b1_tanh3_CAT0' : [1,1],
        'b2_tanh3_CAT0' : [0.001,0.1],
        'b3_tanh3_CAT0' : [-5,5],
        'b4_tanh3_CAT0' : [-10,10],
        'b5_tanh3_CAT0' : [-10.0,10],
        'b6_tanh3_CAT0' : [0.0,0],
        'b7_tanh3_CAT0' : [0.0,0],
	'b8_tanh3_CAT0' : [0.0,0],
        'b9_tanh3_CAT0' : [0.0,0],
        'b0_tanh3_CAT4' : [0.005,2.],
        'b1_tanh3_CAT4' : [1,1],
        'b2_tanh3_CAT4' : [0.001,0.1],
        'b3_tanh3_CAT4' : [0,3],
        'b4_tanh3_CAT4' : [-5,5],
        'b5_tanh3_CAT4' : [-10.0,10],
        'b6_tanh3_CAT4' : [0.0,0],
        'b7_tanh3_CAT4' : [0.0,0],
	'b8_tanh3_CAT4' : [0.0,0],
        'b9_tanh3_CAT4' : [0.0,0],
},

'tanh4' :{
        'b0_tanh4_CAT0' : [0.005,2.],
        'b1_tanh4_CAT0' : [1,1],
        'b2_tanh4_CAT0' : [0.001,0.1],
        'b3_tanh4_CAT0' : [-5,5],
        'b4_tanh4_CAT0' : [-10,10],
        'b5_tanh4_CAT0' : [-10.0,10],
        'b6_tanh4_CAT0' : [-10.0,10],
        'b7_tanh4_CAT0' : [0.0,0],
        'b8_tanh4_CAT0' : [0.0,0],
        'b9_tanh4_CAT0' : [0.0,0],
	'b10_tanh4_CAT0' : [0.0,0],
        'b11_tanh4_CAT0' : [0.0,0],
	'b12_tanh4_CAT0' : [0.0,0],
        'b0_tanh4_CAT4' : [0.005,2.],
        'b1_tanh4_CAT4' : [1,1],
        'b2_tanh4_CAT4' : [0.001,0.1],
        'b3_tanh4_CAT4' : [0,3],
        'b4_tanh4_CAT4' : [-5,5],
        'b5_tanh4_CAT4' : [-10.0,10],
        'b6_tanh4_CAT4' : [-10.0,10],
        'b7_tanh4_CAT4' : [0.0,0],
        'b8_tanh4_CAT4' : [0.0,0],
        'b9_tanh4_CAT4' : [0.0,0],
	'b10_tanh4_CAT4' : [0.0,0],
        'b11_tanh4_CAT4' : [0.0,0],
	'b12_tanh4_CAT4' : [0.0,0],
},

'tanh5' :{
	'b0_tanh5_CAT0' : [0.005,2.],
        'b1_tanh5_CAT0' : [1,1],
        'b2_tanh5_CAT0' : [0.001,0.1],
        'b3_tanh5_CAT0' : [-5,5],
        'b4_tanh5_CAT0' : [-10,10],
        'b5_tanh5_CAT0' : [-10.0,10],
        'b6_tanh5_CAT0' : [-10.0,10],
        'b7_tanh5_CAT0' : [-10.0,10],
        'b8_tanh5_CAT0' : [0.0,0],
        'b9_tanh5_CAT0' : [0.0,0],
        'b10_tanh5_CAT0' : [0.0,0],
        'b11_tanh5_CAT0' : [0.0,0],
        'b12_tanh5_CAT0' : [0.0,0],
	'b13_tanh5_CAT0' : [0.0,0],
        'b14_tanh5_CAT0' : [0.0,0],
        'b15_tanh5_CAT0' : [0.0,0],
        'b0_tanh5_CAT4' : [0.005,2.],
        'b1_tanh5_CAT4' : [1,1],
        'b2_tanh5_CAT4' : [0.001,0.1],
        'b3_tanh5_CAT4' : [0,3],
        'b4_tanh5_CAT4' : [-5,5],
        'b5_tanh5_CAT4' : [-10.0,10],
        'b6_tanh5_CAT4' : [-10.0,10],
        'b7_tanh5_CAT4' : [-10.0,10],
        'b8_tanh5_CAT4' : [0.0,0],
        'b9_tanh5_CAT4' : [0.0,0],
        'b10_tanh5_CAT4' : [0.0,0],
        'b11_tanh5_CAT4' : [0.0,0],
        'b12_tanh5_CAT4' : [0.0,0],
	'b13_tanh5_CAT4' : [0.0,0],
        'b14_tanh5_CAT4' : [0.0,0],
        'b15_tanh5_CAT4' : [0.0,0],
},

'tanh6' :{
        'b0_tanh6_CAT0' : [0.005,2.],
        'b1_tanh6_CAT0' : [1,1],
        'b2_tanh6_CAT0' : [0.001,0.1],
        'b3_tanh6_CAT0' : [-5,5],
        'b4_tanh6_CAT0' : [-10,10],
        'b5_tanh6_CAT0' : [-10.0,10],
	'b6_tanh6_CAT0' : [-10.0,10],
        'b7_tanh6_CAT0' : [-10.0,10],
        'b8_tanh6_CAT0' : [-10.0,10],
        'b9_tanh6_CAT0' : [0.0,0],
        'b10_tanh6_CAT0' : [0.0,0],
        'b11_tanh6_CAT0' : [0.0,0],
        'b12_tanh6_CAT0' : [0.0,0],
        'b13_tanh6_CAT0' : [0.0,0],
        'b14_tanh6_CAT0' : [0.0,0],
        'b15_tanh6_CAT0' : [0.0,0],
	'b16_tanh6_CAT0' : [0.0,0],
        'b17_tanh6_CAT0' : [0.0,0],
        'b18_tanh6_CAT0' : [0.0,0],
        'b0_tanh6_CAT4' : [0.005,2.],
        'b1_tanh6_CAT4' : [1,1],
        'b2_tanh6_CAT4' : [0.001,0.1],
        'b3_tanh6_CAT4' : [0,3],
        'b4_tanh6_CAT4' : [-5,5],
        'b5_tanh6_CAT4' : [-10.0,10],
        'b6_tanh6_CAT4' : [-10.0,10],
        'b7_tanh6_CAT4' : [-10.0,10],
        'b8_tanh6_CAT4' : [-10.0,10],
        'b9_tanh6_CAT4' : [0.0,0],
        'b10_tanh6_CAT4' : [0.0,0],
        'b11_tanh6_CAT4' : [0.0,0],
	'b12_tanh6_CAT4' : [0.0,0],
        'b13_tanh6_CAT4' : [0.0,0],
        'b14_tanh6_CAT4' : [0.0,0],
        'b15_tanh6_CAT4' : [0.0,0],
	'b16_tanh6_CAT4' : [0.0,0],
        'b17_tanh6_CAT4' : [0.0,0],
        'b18_tanh6_CAT4' : [0.0,0],
},

'erfPol2' : {
	'b0_erfPol2_CAT0' : [10,40],
	'b1_erfPol2_CAT0' : [5.,15.],
	'b2_erfPol2_CAT0' : [3.53e-07,15.53e-07],
	'b3_erfPol2_CAT0' : [-6.69e-03,-0.69e-03],
},
'erfPol3' : {
	'b0_erfPol3_CAT0' : [10,40],
	'b1_erfPol3_CAT0' : [5.,15.],
	'b2_erfPol3_CAT0' : [0.712e-07,4.71e-07],
	'b3_erfPol3_CAT0' : [ -11.3e-05, -7.3e-05],
	'b4_erfPol3_CAT0' : [3.48e-03,7.48e-03],
},

'Pol3' : {
'b0_Pol3_CAT0' : 1.17123, 
'b1_Pol3_CAT0' : 0.689743,  
'b2_Pol3_CAT0' : 0.453177, 
'b3_Pol3_CAT0' : 0.0,
'b0_Pol3_CAT4' : 1.44345, 
'b1_Pol3_CAT4' : 0.915609,  
'b2_Pol3_CAT4' : 0.486283,  
'b3_Pol3_CAT4' : 0.0,
},

'Pol4' :{
'b0_Pol4_CAT0' : 9.3, 
'b1_Pol4_CAT0' : 6.9,  
'b2_Pol4_CAT0' : 4.5 , 
'b3_Pol4_CAT0' : 3.9 ,
'b4_Pol4_CAT0' : 0.0,
'b0_Pol4_CAT4' : 9.9 ,                
'b1_Pol4_CAT4' : 8.4 ,                   
'b2_Pol4_CAT4' : 4.9,                   
'b3_Pol4_CAT4' : 3.6,                  
'b4_Pol4_CAT4' : 0.0,
},
'Pol5' : {
'b0_seldouble_CAT0' : 9.3,
'b1_seldouble_CAT0' : 7.97,
'b2_seldouble_CAT0' : 6.06,
'b3_seldouble_CAT0' : 5.03,
'b4_seldouble_CAT0' : 3.81,
'b5_seldouble_CAT0' : 0.0,
'b0_selsingle_CAT4' : 9.9,
'b1_selsingle_CAT4' : 8.75,
'b2_selsingle_CAT4' : 6.71,
'b3_selsingle_CAT4' : 4.55,
'b4_selsingle_CAT4' : 3.6,
'b5_selsingle_CAT4' : 0.0,
},

'Pol6' : {
'b0_Pol6_CAT0' : 9.3,
'b1_Pol6_CAT0' : 8.3,
'b2_Pol6_CAT0' : 6.3,
'b3_Pol6_CAT0' : 5.3,
'b4_Pol6_CAT0' : 4.8,
'b5_Pol6_CAT0' : 3.3,
'b6_Pol6_CAT0' : 0.0,
'b0_Pol6_CAT4' : 0,
'b1_Pol6_CAT4' : 8.75,
'b2_Pol6_CAT4' : 7.71,
'b3_Pol6_CAT4' : 5.55,
'b4_Pol6_CAT4' : 4.6,
'b5_Pol6_CAT4' : 3.3,
'b6_Pol6_CAT4' : 0.0,
},
'Pol7' : {
'b0_seldouble_CAT0' : 9.3,
'b1_seldouble_CAT0' : 8.4,
'b2_seldouble_CAT0' : 7.8,
'b3_seldouble_CAT0' : 5.3,
'b4_seldouble_CAT0' : 5.9,
'b5_seldouble_CAT0' : 4.3,
'b6_seldouble_CAT0' : 3.8,
'b7_seldouble_CAT0' : 0,
'b0_selsingle_CAT4' : 0,
'b1_selsingle_CAT4' : 0.0,
'b2_selsingle_CAT4' : 0.0,
'b3_selsingle_CAT4' : 0.0,
'b4_selsingle_CAT4' : 4.0,
'b5_selsingle_CAT4' : 5.5,
'b6_selsingle_CAT4' : 3.5,
'b7_selsingle_CAT4' : 0,
},
'Pol8' : {
'b0_Pol8_CAT0' : 9.3,
'b1_Pol8_CAT0' : 8.8,
'b2_Pol8_CAT0' : 7.8,
'b3_Pol8_CAT0' : 6.5,
'b4_Pol8_CAT0' : 6.15,
'b5_Pol8_CAT0' : 5.0,
'b6_Pol8_CAT0' : 4.5,
'b7_Pol8_CAT0' : 3.8,
'b8_Pol8_CAT0' : 0,
'b0_Pol8_CAT4' : 0.0,
'b1_Pol8_CAT4' : 0.0,
'b2_Pol8_CAT4' : 0.0,
'b3_Pol8_CAT4' : 0.0,
'b4_Pol8_CAT4' : 0.0,
'b5_Pol8_CAT4' : 5.5,
'b6_Pol8_CAT4' : 3.5,
'b7_Pol8_CAT4' : 3.61,
'b8_Pol8_CAT4' : 0,
},

}
