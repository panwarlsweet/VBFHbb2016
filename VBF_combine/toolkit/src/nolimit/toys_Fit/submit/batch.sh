#source $VO_CMS_SW_DIR/cmsset_default.sh
# shopt -s expand_aliases is needed if you want to use the alias 'cmsenv' created by $VO_CMS_SW_DIR/cmsset_default.sh instead of the less mnemonic eval `scramv1 runtime -sh`

source $VO_CMS_SW_DIR/cmsset_default.sh
source /swshare/psit3/etc/profile.d/cms_ui_env.sh  # for bash

export MYCMSENVDIR=/mnt/t3nfs01/data01/shome/nchernya/CMSSW_7_4_7/src/HiggsAnalysis/
cd $MYCMSENVDIR
eval `scramv1 runtime -sh`
shopt -s expand_aliases
cmsenv
#export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/usr/lib64/dcap



export MYBATCHDIR=//mnt/t3nfs01/data01/shome/nchernya/VBFHbb2016/VBF_fit/toys_Fit_nolimit/toys/
cd $MYBATCHDIR

pwd

combine  -M MaxLikelihoodFit --X-rtd ADDNLL_RECURSIVE=0 --minimizerAlgoForMinos Minuit2,Migrad --minimizerTolerance=0.0001 --preFitValue=1.0 --robustFit=1 --rMin=-20  --rMax=20  --toysFrequentist -t $2 --saveShapes  -n $3 $1 -s -1

 
#combine  -M MaxLikelihoodFit --X-rtd ADDNLL_RECURSIVE=0 --minimizerAlgoForMinos Minuit2,Migrad --minimizerTolerance=0.0001 --preFitValue=1.0 --robustFit=1 --rMin=-20  --rMax=20  --toysFrequentist --noErrors --minos none -t $2 --saveShapes  -n $3 $1 -s -1 --freezeNuisances CMS_vbfbb_qcd_norm_CAT0_13TeV,CMS_vbfbb_qcd_norm_CAT1_13TeV,CMS_vbfbb_qcd_norm_CAT2_13TeV,CMS_vbfbb_qcd_norm_CAT3_13TeV,CMS_vbfbb_qcd_norm_CAT4_13TeV,CMS_vbfbb_qcd_norm_CAT5_13TeV,CMS_vbfbb_qcd_norm_CAT6_13TeV

#combine  -M MaxLikelihoodFit --X-rtd ADDNLL_RECURSIVE=0 --minimizerAlgoForMinos Minuit2,Migrad --minimizerTolerance=0.0001 --preFitValue=1.0 --robustFit=1 --rMin=-20  --rMax=20  --toysFrequentist --noErrors --minos none -t $2 --saveShapes  -n $3 $1 -s -1 

#combine  -M MaxLikelihoodFit --X-rtd ADDNLL_RECURSIVE=0 --minimizerAlgoForMinos Minuit2,Migrad --minimizerTolerance=0.0001 --preFitValue=1.0 --robustFit=1 --rMin=-20  --rMax=20  --noErrors --minos none -t $2 --saveShapes  -n $3 $1 -s -1    #wo Frequentist, throw toys from prefit


#$ -o /mnt/t3nfs01/data01/shome/nchernya/Hbb/skim_trees/batch_logs2/
#$ -e /mnt/t3nfs01/data01/shome/nchernya/Hbb/skim_trees/batch_logs2/

