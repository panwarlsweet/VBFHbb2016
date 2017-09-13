export WORKDIR=`pwd`
cd $WORKDIR


declare -A file_names

path=root://t3dcachedb.psi.ch:1094///pnfs/psi.ch/cms/trivcat//store/user/nchernya/VBFHbb2016/FitInputs/v25/
path2=root://t3dcachedb.psi.ch:1094///pnfs/psi.ch/cms/trivcat//store/user/nchernya/VBFHbb2016/plotterOutput/v25/
file_name=(
QCD_HT100to200
QCD_HT200to300
QCD_HT300to500
QCD_HT500to700
QCD_HT700to1000
QCD_HT1000to1500
QCD_HT1500to2000
QCD_HT2000toInf
ttHTobb_M125
ttHToNonbb_M125
WplusH_HToBB
WminusH_HToBB
ZH_HToBB
bbHToBB_yb2
bbHToBB_ybyt
WW
ZZ
WZ



DYJetsToQQ
WJetsToQQ
ST_tW_top
ST_s_inclusive
ST_tW_antitop
ST_s-channel
ST_t-channel_top_4f_inclusiveDecays
ST_t-channel_antitop_4f_inclusiveDecays
VBFHToBB_M-125
GluGluHToBB_M-125
TT
BTagCSV0
BTagCSV1
BTagCSV2
BTagCSV4
BTagCSV5
)

prefix=''
postfix=v25_VBF_newReg
#postfix=v25_trigWeightNewRegBtagCut_ZbbBdtInclFit
v=v25
ROOT=.root
dataset_type=(double single)
region=(analysis)
output_dir=$TMPDIR
pathhome=/afs/cern.ch/work/n/nchernya/VBFHbb_2016/plotter/output_root/


current_region=0
current_datasettype=0
current_file=0
current_trigWeight=0
max_files=18 #15 #15 #28  #9+8 
pre=FitVBF_
while [ $current_file -lt $max_files  ]
do	 
	xrdcp $path$pre${file_name[$current_file]}_${region[$current_region]}_${dataset_type[$current_datasettype]}_trignone_$postfix.root  /afs/cern.ch/work/n/nchernya/VBFHbb_2016/VBF_combine/inputs/root/
#	xrdcp $path2${file_name[$current_file]}_${region[$current_region]}_${dataset_type[$current_datasettype]}_trignone_$postfix.txt  /afs/cern.ch/work/n/nchernya/VBFHbb_2016/Zbb_combine/inputs/txt/



	current_file=$((current_file + 1))
done

