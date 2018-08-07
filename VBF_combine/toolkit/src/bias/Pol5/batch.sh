#source $VO_CMS_SW_DIR/cmsset_default.sh
# shopt -s expand_aliases is needed if you want to use the alias 'cmsenv' created by $VO_CMS_SW_DIR/cmsset_default.sh instead of the less mnemonic eval `scramv1 runtime -sh`

#source $VO_CMS_SW_DIR/cmsset_default.sh
#source /swshare/psit3/etc/profile.d/cms_ui_env.sh  # for bash

export MYCMSENVDIR=/afs/cern.ch/work/l/lata/VBF_Analysis/CMSSW_7_4_7/src/VBFHbb2016/VBF_combine/toolkit/src
cd $MYCMSENVDIR
eval `scramv1 runtime -sh`
#shopt -s expand_aliases
#cmsenv
#export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/usr/lib64/dcap



export MYBATCHDIR=/afs/cern.ch/work/l/lata/VBF_Analysis/CMSSW_7_4_7/src/VBFHbb2016/VBF_combine/toolkit/src/bias/makeToys/$5
cd $MYBATCHDIR

pwd
#echo combine -M MaxLikelihoodFit --X-rtd FITTER_NEVER_GIVE_UP --X-rtd FITTER_BOUND --X-rtd ADDNLL_RECURSIVE=0 --X-rtd FITTER_NEW_CROSSING_ALGO  -t 1 --expectSignal=1 --preFitValue=1 --minimizerTolerance=0.01  --robustFit=1  --rMin=-4 --rMax=4  --toysFile $2  -n $3$4   $1

combine -M MaxLikelihoodFit --X-rtd FITTER_NEVER_GIVE_UP --X-rtd FITTER_BOUND --X-rtd ADDNLL_RECURSIVE=0 --X-rtd FITTER_NEW_CROSSING_ALGO  -t 20 --expectSignal=$6 --preFitValue=2 --minimizerTolerance=0.01  --robustFit=1  --rMin=-20 --rMax=20  --toysFile $2  -n $3$4_mu$6   $1

#$ -o /mnt/t3nfs01/data01/shome/nchernya/Hbb/skim_trees/batch_logs2/
#$ -e /mnt/t3nfs01/data01/shome/nchernya/Hbb/skim_trees/batch_logs2/

