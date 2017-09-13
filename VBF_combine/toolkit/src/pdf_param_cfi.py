Nparam = {
'expPow' : 3,
'sine' : 3,
'sineErf' : 5,
'modG' : 3,
'tanhPol2' : 4,
'tanh' : 3,
'erfPol2' : 4,
'erfPol3' : 5,
'tanhPol3' : 5,
'erfPol3' : 5,
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
	'b0_CAT0' : [0.,5],
	'b1_CAT0' : [0.,5],
	'b2_CAT0' : [0.,5]
},
'modG' : {
	'b0_CAT0' : [0,0.02],
	'b1_CAT0' : [0.5,5],
	'b2_CAT0' : [0.005,0.1],
},
'sine' : {
	'b0_CAT0' : [0.1,0.95],
	'b1_CAT0' : [0.002,0.027],
	'b2_CAT0' : [1.5,4.]
	#'b0_CAT0' : [0.1,0.95],
	#'b1_CAT0' : [0.0001,0.047],
	#'b2_CAT0' : [0.,1]
},
'sineErf' : {
	'b0_CAT0' : [0.1,0.95],
	'b1_CAT0' : [0.002,0.027],
	'b2_CAT0' : [0.1,4],
	'b3_CAT0' : [0.5,30],
	'b4_CAT0' : [0.005,0.1]
},
'tanhPol2' :{
	'b0_tanhPol2_CAT0' : [0.005,0.4],
	'b1_tanhPol2_CAT0' : [20,30],
	'b2_tanhPol2_CAT0' : [3.53e-07,13.53e-07],
	'b3_tanhPol2_CAT0' : [-8.69e-03,-1e-03],
},
'tanh' :{
	'b0_CAT0' : [0.005,2.],
	'b1_CAT0' : [0.001,0.1],
	'b2_CAT0' : [0.0,5],
},
'tanhPol3' :{
	'b0_tanhPol3_CAT0' : [0.005,0.4],
	'b1_tanhPol3_CAT0' : [20,30],
	'b2_tanhPol3_CAT0' : [0.712e-07,4.71e-07],
	'b3_tanhPol3_CAT0' : [ -11.3e-05, -7.3e-05],
	'b4_tanhPol3_CAT0' : [3.48e-03,7.48e-03],
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
}
}

