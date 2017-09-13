export WORKDIR=`pwd`
cd $WORKDIR


declare -A file_names

path=root://t3dcachedb.psi.ch:1094///pnfs/psi.ch/cms/trivcat//store/user/nchernya/VBFHbb2016/plotterOutput/v25/
file_name=(
VBFHToBB_M-125_herwig
GluGluHToBB_M-125_herwig

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
DYJetstoLL_amc_0J
DYJetstoLL_amc_1J
DYJetstoLL_amc_2J

ST_tW_top
ST_tW_antitop
ST_s-channel
ST_t-channel_top_4f_inclusiveDecays
ST_t-channel_antitop_4f_inclusiveDecays
BTagCSV0
BTagCSV1
BTagCSV2
BTagCSV3

QCD_HT100to200
QCD_HT200to300
QCD_HT300to500
QCD_HT500to700
QCD_HT700to1000
QCD_HT1000to1500
QCD_HT1500to2000
QCD_HT2000toInf
VBFHToBB_M-125
GluGluHToBB_M-125
TT
WJetsToLNu
WJetsToQQ
)

prefix=''
postfix=v25_VBF_newReg
#postfix=v25_VBFbdt_transfer
v=v25
ROOT=.root
dataset_type=(double single)
region=(analysis)
output_dir=$TMPDIR
pathhome=/afs/cern.ch/work/n/nchernya/VBFHbb_2016/plotter/output_root/


current_region=0
current_datasettype=1
current_file=0
current_trigWeight=0
max_files=2 #28  #9+8 
while [ $current_file -lt $max_files  ]
do	 
	xrdcp $path${file_name[$current_file]}_${region[$current_region]}_${dataset_type[$current_datasettype]}_trignone_$postfix.txt /afs/cern.ch/work/n/nchernya/VBFHbb_2016/plotter/output_txt_paolo/



	current_file=$((current_file + 1))
done

