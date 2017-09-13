#source $VO_CMS_SW_DIR/cmsset_default.sh
# shopt -s expand_aliases is needed if you want to use the alias 'cmsenv' created by $VO_CMS_SW_DIR/cmsset_default.sh instead of the less mnemonic eval `scramv1 runtime -sh`

source $VO_CMS_SW_DIR/cmsset_default.sh
source /swshare/psit3/etc/profile.d/cms_ui_env.sh  # for bash

export MYCMSENVDIR=/mnt/t3nfs01/data01/shome/nchernya/CMSSW_8_0_19/src
cd $MYCMSENVDIR
eval `scramv1 runtime -sh`
shopt -s expand_aliases 
cmsenv
#export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/usr/lib64/dcap 

export MYBATCHDIR=/mnt/t3nfs01/data01/shome/nchernya/VBFHbb2016//main_mva/
cd $MYBATCHDIR

#mkdir $TMPDIR/output/ 
#mkdir $TMPDIR/output/v25/
#mkdir $TMPDIR/output/txt/
#mkdir $TMPDIR/weights/

#./run_Nm1_tmva $1 $2 $3 $TMPDIR
./run_Nm1_tmva $1 $2 $3 $4 $5 $6 $7

#xrdcp -f $TMPDIR/output/v25/TMVA_main_v25_Nm1_$1$2$3.root  root://t3dcachedb.psi.ch:1094///pnfs/psi.ch/cms/trivcat//store/user/nchernya/VBFHbb2016/tmva_output/output/v25/
#
#xrdcp -f $TMPDIR/output/v25/TMVA_main_v25_Nm1_$1$2$3.txt root://t3dcachedb.psi.ch:1094///pnfs/psi.ch/cms/trivcat//store/user/nchernya/VBFHbb2016/tmva_output/output/v25/txt/
#
#xrdfs t3dcachedb.psi.ch  mkdir /pnfs/psi.ch/cms/trivcat//store/user/nchernya/VBFHbb2016/tmva_output/weights/TMVAClassification_BDTG_$1$2$3_v25
#
#xrdcp -f $TMPDIR/weights/TMVAClassification_BDTG_$1$2$3_v25/Classification_BDTG.weights.xml root://t3dcachedb.psi.ch:1094///pnfs/psi.ch/cms/trivcat//store/user/nchernya/VBFHbb2016/tmva_output/weights/TMVAClassification_BDTG_$1$2$3_v25/
#xrdcp  -f $TMPDIR/weights/TMVAClassification_BDTG_$1$2$3_v25/Classification_BDTG.class.C root://t3dcachedb.psi.ch:1094///pnfs/psi.ch/cms/trivcat//store/user/nchernya/VBFHbb2016/tmva_output/weights/TMVAClassification_BDTG_$1$2$3_v25/
 

#$ -o /mnt/t3nfs01/data01/shome/nchernya/Hbb/skim_trees/batch_logs2/
#$ -e /mnt/t3nfs01/data01/shome/nchernya/Hbb/skim_trees/batch_logs2/
