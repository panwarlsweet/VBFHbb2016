cd /afs/cern.ch/work/l/lata/VBF_Analysis/CMSSW_7_4_7/src/VBFHbb2016/VBF_combine/toolkit/src/bias/makeToys
num=0
max=50
n_toys=20
name_list="
pol2_invdijet
exp_pol2
"
name2=_sine
inj=_inj
mu=0
## DB cats.
cat0=0
cat1=3
## SB cats.

name_list2="
modG4
"
cat2=4
cat3=8


for arg in $name_list:
do
  	name=$arg
        datacard=/afs/cern.ch/work/l/lata/VBF_Analysis/CMSSW_7_4_7/src/VBFHbb2016/VBF_combine/toolkit/src/set_DBT3P5_SBT2P7/datacards/datacard_vbfHbb_bias${name}_m125_CAT${cat0}-CAT${cat1}_CATveto.txt
        echo datacard
        num=0
        while [ $num -lt $max ]
        do
        bsub -q 1nh batch.sh  $n_toys $mu $name$num$inj${mu}_cat${cat0}-cat${cat1}  $datacard $name
        echo $num $arg CAT${cat0} CAT${cat1} inj${mu}

        num=$(( $num + 1 ))
	done
done


#for arg in $name_list2:
#do
#        name=$arg
#        datacard=/afs/cern.ch/work/l/lata/VBF_Analysis/CMSSW_7_4_7/src/VBFHbb2016/VBF_combine/toolkit/src/set_DBT3P5_SBT2P7/datacards/datacard_vbfHbb_bias${name}_m125_CAT${cat2}-CAT${cat3}_CATveto.txt
#        num=0
#        while [ $num -lt $max ]
#        do
#        bsub -q 1nd batch.sh  $n_toys $mu $name$num$inj${mu}_cat${cat2}-cat${cat3}  $datacard $name
#        echo $num $arg CAT${cat2} CAT${cat3} inj${mu}

#        num=$(( $num + 1 ))
#        done
#done

