export WORKDIR=`pwd`
cd $WORKDIR


declare -A file_names

path=root://t3se01.psi.ch///store/user/nchernya/VBFHbb2016/plotterOutput/v25/
file_name=(
#ST_tW_top
#ST_tW_antitop
#ST_s-channel
#ST_t-channel_top_4f_inclusiveDecays
#ST_t-channel_antitop_4f_inclusiveDecays
#QCD_HT100to200
#QCD_HT200to300
#QCD_HT300to500
#QCD_HT500to700
#QCD_HT700to1000
#QCD_HT1000to1500
#QCD_HT1500to2000
#QCD_HT2000toInf
#DYJetstoLL_amc_0J
#DYJetstoLL_amc_1J
#DYJetstoLL_amc_2J
#VBFHToBB_M-125
#GluGluHToBB_M-125
#WJetsToQQ
#DYJetsToQQ
#TT
#WJetsToLNu
VBFHToBB_M-125_herwig
GluGluHToBB_M-125_herwig





)
qgl_single=(
0.969027362
0.966305594
0.969012219
0.981936118
0.980760064
1
0.972104286
0.986218526
0.98425371
0.976825118
0.964332988
0.943468494
0.931756232
0.978234492
0.985054953
0.971988179
0.975317594
0.984415933
)


qgl_double=(
0.958732717
0.955997449
0.970870396
0.963252452
0.959430186
1.008803524
1.006402971
0.995691058
0.993618415
0.982397299
0.962535992
0.940583926
0.919402112
0.957131979
0.995103933
0.961346624
0.961970054
0.972793373
)

#postfix=v25_VBF_herwig_noqgl
postfix=v25_VBF_herwig_qglnonorm
v=v25
region=(analysis controlTop controlDY)
dataset_type=(double single)


current_region=0
current_datasettype=0
current_file=0
current_trigWeight=0
max_files=2 #35
a='"'
while [ $current_file -lt $max_files  ]
do	
#		xrdcp $path${file_name[$current_file]}_${region[$current_region]}_${dataset_type[$current_datasettype]}_trignone_$postfix.txt /afs/cern.ch/work/n/nchernya/VBFHbb_2016/plotter/output_txt_qgl2/
#	echo qgl_norm[$a${file_name[$current_file]}$a]'='${qgl_single[$current_file]}';'
#	echo ${file_name[$current_file]}
	tail -n+11	/afs/cern.ch/work/n/nchernya/VBFHbb_2016/plotter/output_txt_qgl2/${file_name[$current_file]}_${region[$current_region]}_${dataset_type[$current_datasettype]}_trignone_$postfix.txt | head -n 1 | sed s/:/\\n/g


#	echo
#	echo


	current_file=$((current_file + 1))
done

