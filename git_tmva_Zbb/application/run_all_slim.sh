export WORKDIR=`pwd`
cd $WORKDIR

g++ run_create_Zbb.C -g -o run_all `root-config --cflags --glibs`  -lMLP -lXMLIO -lTMVA  

cp run_all /mnt/t3nfs01/data01/shome/nchernya/VBFHbb2016/Zbb_mva/

input_dir=(
ggHbb 
VBFHbb   
BTagCSV4 BTagCSV5
 ST_s
BTagCSV0 BTagCSV1 BTagCSV2            QCD_HT1000to1500  QCD_HT500to700   ST_tW_top                WJetsToLnu_HT2500toInf  WJetsToQQ
DYJetstoLL_amc_0J  QCD_HT100to200    QCD_HT700to1000  TT                       WJetsToLnu_HT400to600
DYJetstoLL_amc_1J  QCD_HT1500to2000                              WJetsToLnu_HT600to800
DYJetstoLL_amc_2J  QCD_HT2000toInf   ST_t_antitop     WJetsToLnu_HT100to200    WJetsToLnu_HT70to100
DYJetsToQQ         QCD_HT200to300    ST_t_top         WJetsToLnu_HT1200to2500  WJetsToLnu_HT800to1200
             QCD_HT300to500    ST_tW_antitop    WJetsToLnu_HT200to400    WJetsToLnu_madgraph


)
max_samples_num=35 #35 #35 #35 #34 #26 

path=dcap://t3se01.psi.ch:22125///pnfs/psi.ch/cms/trivcat/store/user/nchernya/VBFHbb2016/blike_reg_v25/
ROOT=.root
file_end=""
mva=ZbbMvaJESR_v25_
blike="blike_reg_v25_"

current_sample=0
while [ $current_sample -lt $max_samples_num ]
do	
#	echo $path$blike${input_dir[ $current_sample ]}$file_end$ROOT $mva${input_dir[ $current_sample ]}
	qsub -q all.q batch2_2.sh $path$blike${input_dir[ $current_sample ]}$file_end$ROOT $mva${input_dir[ $current_sample ]}
	echo $path$blike${input_dir[ $current_sample ]}$file_end$ROOT $mva${input_dir[ $current_sample ]}
	current_sample=$(( $current_sample + 1 ))
done

