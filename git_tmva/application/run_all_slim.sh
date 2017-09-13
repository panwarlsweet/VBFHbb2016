export WORKDIR=`pwd`
cd $WORKDIR

#g++ run_create_Zbb.C -g -o run_all_0 `root-config --cflags --glibs`  -lMLP -lXMLIO -lTMVA  
g++ run_create_Zbb.C -g -o run_all_1 `root-config --cflags --glibs`  -lMLP -lXMLIO -lTMVA  

cp run_all_* /mnt/t3nfs01/data01/shome/nchernya/VBFHbb2016/main_mva/

input_dir=(
QCD_HT1000to1500  QCD_HT500to700
 QCD_HT100to200    QCD_HT700to1000  TT
 QCD_HT1500to2000   
 QCD_HT2000toInf
 QCD_HT200to300  
 QCD_HT300to500 
DYJetsToQQ 
WJetsToQQ
ST_s_inclusive



ggHbb 
VBFHbb   

bbH_yb2
bbH_ybyt
ttHbb   
ttHnonbb
WminusHbb_powheg
WplusHbb_powheg
ZHbb_powheg
WW
ZZ
WZ

VBFHbb_herwig
VBFHbb_CUEDown
VBFHbb_CUEUp
VBFHbb_amc
ggHbb_herwig
ggHbb_amc





BTagCSV4 BTagCSV5
BTagCSV0 BTagCSV1 BTagCSV2

 ST_s
               ST_tW_top                WJetsToLnu_HT2500toInf  DYJetstoLL_amc_0J                      WJetsToLnu_HT400to600
DYJetstoLL_amc_1J                              WJetsToLnu_HT600to800
DYJetstoLL_amc_2J    ST_t_antitop     WJetsToLnu_HT100to200    WJetsToLnu_HT70to100
         ST_t_top         WJetsToLnu_HT1200to2500  WJetsToLnu_HT800to1200
               ST_tW_antitop    WJetsToLnu_HT200to400    WJetsToLnu_madgraph



)
max_samples_num=12 #30  #31 #35 #35 #35 #35 #34 #26 

path=dcap://t3se01.psi.ch:22125///pnfs/psi.ch/cms/trivcat/store/user/nchernya/VBFHbb2016/blike_reg_v25/
ROOT=.root
file_end=""
mva=VBFMvaJESR_v25_weights_new
blike="blike_reg_v25_"

current_sample=0
while [ $current_sample -lt $max_samples_num ]
do
#############################Double and Single SHOULD BE RUN one at a time!!!!! because you need to change preselection!!!!!!!!	
	str_type=double
#	qsub -q all.q batch2_2.sh $path$blike${input_dir[ $current_sample ]}$file_end$ROOT $str_type$mva${input_dir[ $current_sample ]} 0
#	echo $path$blike${input_dir[ $current_sample ]}$file_end$ROOT $mva${input_dir[ $current_sample ]}
	str_type=single
	qsub -q all.q batch2_single.sh $path$blike${input_dir[ $current_sample ]}$file_end$ROOT $str_type$mva${input_dir[ $current_sample ]} 1
	current_sample=$(( $current_sample + 1 ))
done

