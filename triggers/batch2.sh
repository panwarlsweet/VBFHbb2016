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

export MYBATCHDIR=/mnt/t3nfs01/data01/shome/nchernya/VBFHbb2016/triggers/
cd $MYBATCHDIR

./turnOn $1 $2 $3 $4 $5 $6 $TMPDIR

xrdfs t3dcachedb.psi.ch rm root://t3dcachedb.psi.ch:1094///pnfs/psi.ch/cms/trivcat//store/user/nchernya/VBFHbb2016/triggerOutput/v25/$2_$3_trig$5$6.root
xrdfs t3dcachedb.psi.ch rm root://t3dcachedb.psi.ch:1094///pnfs/psi.ch/cms/trivcat//store/user/nchernya/VBFHbb2016/triggerOutput/v25/$2_$3_trig$5$6.txt

xrdcp -f $TMPDIR/$2_$3_trig$5$6.root root://t3dcachedb.psi.ch:1094///pnfs/psi.ch/cms/trivcat//store/user/nchernya/VBFHbb2016/triggerOutput/v25/
xrdcp -f $TMPDIR/$2_$3_trig$5$6.txt root://t3dcachedb.psi.ch:1094///pnfs/psi.ch/cms/trivcat//store/user/nchernya/VBFHbb2016/triggerOutput/v25/

#$ -o /mnt/t3nfs01/data01/shome/nchernya/Hbb/skim_trees/batch_logs/
#$ -e /mnt/t3nfs01/data01/shome/nchernya/Hbb/skim_trees/batch_logs/
