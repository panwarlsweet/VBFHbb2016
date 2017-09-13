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

export MYBATCHDIR=/mnt/t3nfs01/data01/shome/nchernya/VBFHbb2016/plotter/
cd $MYBATCHDIR

root=.root

./plot $1 $2 $3 $4 $5 $6 $7 $8 $9 $TMPDIR
echo $8

xrdfs   t3dcachedb03.psi.ch   rm   /pnfs/psi.ch/cms/trivcat/store/user/nchernya/VBFHbb2016/plotterOutput/$8/$2_$4_$3_trig$7_$8_$9.root
xrdfs  t3dcachedb03.psi.ch    rm   /pnfs/psi.ch/cms/trivcat/store/user/nchernya/VBFHbb2016/plotterOutput/$8/$2_$4_$3_trig$7_$8_$9.txt
xrdfs   t3dcachedb03.psi.ch   rm   /pnfs/psi.ch/cms/trivcat/store/user/nchernya/VBFHbb2016/FitInputs/$8/FitZbb_$2_$4_$3_trig$7_$8_$9.root
xrdfs   t3dcachedb03.psi.ch   rm   /pnfs/psi.ch/cms/trivcat/store/user/nchernya/VBFHbb2016/FitInputs/$8/FitVBF_$2_$4_$3_trig$7_$8_$9.root

xrdcp -f $TMPDIR/$2_$4_$3_trig$7_$8_$9.root root://t3dcachedb.psi.ch:1094///pnfs/psi.ch/cms/trivcat//store/user/nchernya/VBFHbb2016/plotterOutput/$8
xrdcp -f $TMPDIR/$2_$4_$3_trig$7_$8_$9.txt root://t3dcachedb.psi.ch:1094///pnfs/psi.ch/cms/trivcat//store/user/nchernya/VBFHbb2016/plotterOutput/$8/
xrdcp -f $TMPDIR/FitZbb_$2_$4_$3_trig$7_$8_$9.root root://t3dcachedb.psi.ch:1094///pnfs/psi.ch/cms/trivcat//store/user/nchernya/VBFHbb2016/FitInputs/$8
xrdcp -f $TMPDIR/FitVBF_$2_$4_$3_trig$7_$8_$9.root root://t3dcachedb.psi.ch:1094///pnfs/psi.ch/cms/trivcat//store/user/nchernya/VBFHbb2016/FitInputs/$8

#$ -o /mnt/t3nfs01/data01/shome/nchernya/Hbb/skim_trees/batch_logs2/
#$ -e /mnt/t3nfs01/data01/shome/nchernya/Hbb/skim_trees/batch_logs2/
