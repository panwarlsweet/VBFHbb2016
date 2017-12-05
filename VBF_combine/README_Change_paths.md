# This readme explains how to change path to your files :

As you read in the README you need to create jsons with all bkg and signal samples name, ppath, cross sections and ect. This is done automatically, all you need to do is to run write_samples.py with the __CORRECT PATHS__ to the root fiels you copied from me. Since there are many root ntuples there, I explicitely specify which are signals and backgrounds below. You just need to put your actual path to the root files instead of 'path/' to the prepard command line below.

## Background

./write_samples.py -i path/FitVBF_DYJetsToQQ_analysis_single_trignone_v25_VBFbdt_transfer.root,path/FitVBF_WJetsToQQ_analysis_single_trignone_v25_VBFbdt_transfer.root,path/FitVBF_ST_tW_top_analysis_single_trignone_v25_VBFbdt_transfer.root,path/FitVBF_ST_s_inclusive_analysis_single_trignone_v25_VBFbdt_transfer.root,path/FitVBF_ST_tW_antitop_analysis_single_trignone_v25_VBFbdt_transfer.root,path/FitVBF_ST_s-channel_analysis_single_trignone_v25_VBFbdt_transfer.root,path/FitVBF_ST_t-channel_top_4f_inclusiveDecays_analysis_single_trignone_v25_VBFbdt_transfer.root,path/FitVBF_ST_t-channel_antitop_4f_inclusiveDecays_analysis_single_trignone_v25_VBFbdt_transfer.root,path/FitVBF_TT_analysis_single_trignone_v25_VBFbdt_transfer.root,path/FitVBF_DYJetsToQQ_analysis_double_trignone_v25_VBFbdt_transfer.root,path/FitVBF_WJetsToQQ_analysis_double_trignone_v25_VBFbdt_transfer.root,path/FitVBF_ST_tW_top_analysis_double_trignone_v25_VBFbdt_transfer.root,path/FitVBF_ST_s_inclusive_analysis_double_trignone_v25_VBFbdt_transfer.root,path/FitVBF_ST_tW_antitop_analysis_double_trignone_v25_VBFbdt_transfer.root,path/FitVBF_ST_s-channel_analysis_double_trignone_v25_VBFbdt_transfer.root,path/FitVBF_ST_t-channel_top_4f_inclusiveDecays_analysis_double_trignone_v25_VBFbdt_transfer.root,path/FitVBF_ST_t-channel_antitop_4f_inclusiveDecays_analysis_double_trignone_v25_VBFbdt_transfer.root,path/FitVBF_TT_analysis_double_trignone_v25_VBFbdt_transfer.root -b  vbfHbb_info_2016.json -o vbfHbb_samples_2016_bkg.json

## Signal 

./write_samples.py -i  path/FitVBF_VBFHToBB_M-125_analysis_single_trignone_v25_VBFbdt_transfer.root,path/FitVBF_GluGluHToBB_M-125_analysis_single_trignone_v25_VBFbdt_transfer.root,path/FitVBF_VBFHToBB_M-125_analysis_double_trignone_v25_VBFbdt_transfer.root,path/FitVBF_GluGluHToBB_M-125_analysis_double_trignone_v25_VBFbdt_transfer.root -b  vbfHbb_info_2016.json -o vbfHbb_samples_2016_sig.json

## Data 

For the data file BTagCSV we just put the path explicitely in mkDataTemplates_run2.py file, e.g. you would have to change it with your path. 

```
## Load tree
fin = TFile.Open("path/FitVBF_BTagCSV_analysis_%s_trignone_v25_VBF_newReg.root"%(str.lower(S.tag)),"read")

```
