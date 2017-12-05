# Run combine machinery for VBFHbb

Instructions how to make datacards, templates and extract limits using CombineLimit toolkit
https://twiki.cern.ch/twiki/bin/viewauth/CMS/SWGuideHiggsAnalysisCombinedLimit

## Prerequisites

All inputs can be found here : 
```
/afs/cern.ch/user/n/nchernya/public/VBFHbb2016/inputs/
```
Ready to use datacards can be found here : 
```
/afs/cern.ch/user/n/nchernya/public/VBFHbb2016/datacards
```
Ready to use templates can be found here :
```
/afs/cern.ch/user/n/nchernya/public/VBFHbb2016/root
```

All code needed to make final limits from the prepared inputs is here 
```
VBFHbb2016/VBF_combine/
```
__First you can simply go to the section  'Running limits' of this readme and just run the expected limits. Make sure that you get the same results as quoted in the AN/PAS__ 
When you run these make sure you open the datacard file first and change the path to the root template file to wherever you are going to copy it to.

Once this step is done, you can create datacards and templates yourself following the instructions below.


## Preparing templates and datacards
 
### Scripts for initial set up of bkg,sig names , cross sections and etc. (This step can be ommited since set up is already done)

In the VBFHbb2016/VBF_combine/common/ first info file vbfHbb_info_2016.json has to be prepared with short names of sig,bkg,data samples, cross sections.__This is already done, you dont have to touch it at all.__

Then using just created info file one runs scripts to get json with full sample paths, names, cross-sections, etc and obtain vbfHbb_samples_2016_sig/bkg.json 
__This you have to run yourself in order to set YOUR paths to the root files__
You have to create 2 json files vbfHbb_samples_2016_bkg.json and vbfHbb_samples_2016_sig.json   for background and signal. For the data file BTagCSV we just put the path explicitely in mkDataTemplates_run2.py file, e.g. you would have to change it with your path.
 
```
./write_samples.py -i path_to_sample/sample.root,path_to_sample2/sample2.root,... -b  vbfHbb_info_2016.json -o vbfHbb_samples_2016_bkg.json
```
Very explicit instuctions how to run this write_samples are given in another README "README_Change_paths.md"

All uncertainties are stores here:
```
vbfHbb_uncertainties_2016.json

````
Uncertainty band for Transfer function plots is defined here per category and for different TF that can be used:
```
vbfHbb_transfer_2016_run2_linear.json
```

Style file used for plots :
```
styleCMSTDR.C
```

### Preparing templates and datacards
First of all the framework is set up using 'toolkit' scipt that you can find in toolkit/common. All functions that you dont know where they aer coming from can be found there.
All templates are prepared using the following scripts. Bining, order of polynomials, category boundaries can be passed as an argument. If not specifically passed then default ones are used. 
__In all scripts that starts with 'mk' (make) you will see that there is a loop over Categories (SC.selections) and Tags(SingleB and DoubleB) S.tag__

1. Create Transfer functions prefit
```
./mkTransferFunctions_run2.py  --workdir name_of_workdir
```
2. Create signal templates
```
./mkSigTemplates_run2.py --workdir name_of_workdir
```
3. Create background templates
```
./mkBkgTemplates_run2.py --workdir name_of_workdir
```
4. Using the output files created using the above scripts create data templates
```
./mkDataTemplates_run2.py --workdir name_of_workdir
```
5. Create datacards. One can pass categories names if datacards are needed only for CAT0-CAT1, CAT0-CAT2_CAT1veto, CAT3-CAT4, etc. fits
```
./mkDatacards_run2.py --workdir name_of_workdir
./mkDatacards_run2.py --workdir name_of_workdir --CATS 0,2 --CATveto 1
```
## Running limits
in the name_of_workdir workdirectory there will be plots, datacards and root derectories. One can create 'run_from' dicrectory and run limits
```
combine ../datacards/datacard_m125.txt   -M MaxLikelihoodFit --X-rtd FITTER_NEVER_GIVE_UP --X-rtd FITTER_BOUND --X-rtd ADDNLL_RECURSIVE=0 --X-rtd FITTER_NEW_CROSSING_ALGO  -t -1 --expectSignal=1  --minimizerTolerance=0.01 --preFitValue=1.0 --robustFit=1
   --rMin=-20  --rMax=20 -n fit_number_1_nametag
   
combine -M Asymptotic --run expected -v 2 --X-rtd FITTER_NEVER_GIVE_UP --X-rtd FITTER_BOUND --X-rtd ADDNLL_RECURSIVE=0 --X-rtd FITTER_NEW_CROSSING_ALGO --rMin=-5 --rMax=5  ../datacards/datacard_m125.txt

combine -M ProfileLikelihood --X-rtd FITTER_NEVER_GIVE_UP --X-rtd FITTER_BOUND --X-rtd ADDNLL_RECURSIVE=0 --X-rtd FITTER_NEW_CROSSING_ALGO --significance -t -1 --expectSignal=1 ../datacards/datacard_m125.txt

```
To make impacts:
```
combineTool.py -M Impacts  -d ../datacards/datacard_vbfHbb_m125.root  -m 125 --doInitialFit --robustFit 1 --X-rtd FITTER_NEVER_GIVE_UP --X-rtd FITTER_BOUND --X-rtd ADDNLL_RECURSIVE=0  --minimizerAlgoForMinos Minuit2,Migrad  --preFitValue=1.0 --rMin=-10 --rMax=10 --setPhysicsModelParameterRanges r=-10,10 --expectSignal=1 -t -1
plotImpacts.py -i impacts.json -o impacts

```

For CombinedLimit tool in order to run VBF Hbb this flag is necessary --X-rtd ADDNLL_RECURSIVE=0 , and the others are recommended:
```
--X-rtd FITTER_NEVER_GIVE_UP --X-rtd FITTER_BOUND --X-rtd ADDNLL_RECURSIVE=0 --X-rtd FITTER_NEW_CROSSING_ALGO
```

Get pulls:
```
python /afs/cern.ch/user/n/nchernya/Hbb/newCombine/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/test/diffNuisances.py -a mlfitfit_number_1_nametag.root -g plots_fit_number_1_nametag.root

../mkNuisances.py -a -f text mlfitfit_number_1_nametag.root -g plots_fit_number_1_nametag.root  > Nuisances_fit_number_1_nametag.txt

../ptNuisances.py plots_fit_number_1_nametag 125
```

Goodness of the fit:
```
combine  -M GoodnessOfFit ../datacards/datacard_vbfHbb_2016_m125.txt --X-rtd ADDNLL_RECURSIVE=0  --minimizerTolerance=0.0001 --algo=saturated
```
Here are couple of scipts how the toys were submitted:
src/nolimit/
and in toys_Fit one can find new plotting scipts for toys/data agreements

# Bias studies
Bias studies were done on several functions. Several scipts are available to extract expected limits, make toys, etc with other functions:
```
mkBiasTemplates_run2.py
generateFormula.py
generatePdf.py
pdf_param_cfi.py
./mkBiasTemplates_run2.py --workdir name_of_workdir --function expPow
./mkDatacards_run2.py --workdir name_of_workdir --function expPow --bias true --CATS 0,2
```
Several scipts are availbale here how I ran the toys for bias studies:
```
VBF_combine/toolkit/src/bias
```
And to plot injected/fitted models in scipts:
```
bias.py
bias_plot.py
```



# Create datacards and templates with CAT-1 and CAT-2 
One can simply change the code of mkTranferFunctions_run2.py, mkSigTemplates_run2.py and so on. I did not want to create a separate branch for this, and I just simply added the copies of mkTF,Sig,Bkg,Data,Datacard scipts with little change of the code so you can run on CAT -1 and -2 and renamed it to "_cat.py" like mkDatacards_run2.py
 

# Make tables of yields for AN and PAS
```
mkTable_yields.py
mkTable_yieldsPAS.py
```

# Scipts to make different kinds of plots

plot the results of the fit, PAS/paper plots:
Be aware that root file name with the fitted result and the datacards/templates directories is hardcoded. Change it!
```
root -l ptBestFit.C'(5.,0,"125","","")'
```
plot loglikelihood 
```
loglikelihood_value.py
```
plot p_value
```
p_value.py
```
plot agreement of Asimov, toys and pre/post fit toys tossing (studies we did with Andre David)
```
plot_toys_data.py  
plot_toys_data_violin.py
```
plot for goodness of fit agreement between toys and observed
```
GoF_p_value.py
```
plot polynomial with fitted coefficiants to visualize:
```
brn.py
```





