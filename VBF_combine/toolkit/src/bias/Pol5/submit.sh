export WORKDIR=`pwd`
echo "Working on a machine:" `uname -a`
cd $WORKDIR

num=0
max=50 #100
n_toys=20  #10
inj=_inj
name=sine
fit=Pol5	
mu=0
#cat0=0
#cat1=2
cat0=0
cat1=3

datacard=/afs/cern.ch/work/l/lata/VBF_Analysis/CMSSW_7_4_7/src/VBFHbb2016/VBF_combine/toolkit/src/set_DBT3P5_SBT2P7/datacards/datacard_vbfHbb_bias${name}_m125_CAT${cat0}-CAT${cat1}_CATveto.txt
while [ $num -lt $max ]
do
#	toys_file=$(find /mnt/t3nfs01/data01/shome/nchernya/VBFHbb2016/VBF_fit/bias/toys/${name}/ -name higgsCombine${name}${num}_inj1_cat${cat0}-cat${cat1}.GenerateOnly.mH120.*.root)
	toys_file=/afs/cern.ch/work/l/lata/VBF_Analysis/CMSSW_7_4_7/src/VBFHbb2016/VBF_combine/toolkit/src/bias/makeToys/${name}/higgsCombine${name}${num}_inj${mu}_cat${cat0}-cat${cat1}.GenerateOnly.mH120.*.root
	bsub -q 1nd batch.sh  $datacard  $toys_file  ${name}_fit${fit}$inj${mu}_cat${cat0}${cat1}_ $num $name $mu
#	qsub -q all.q batch2.sh  $datacard  $toys_file  ${name}_fit${fit}$inj${mu}_cat${cat0}${cat1}_ $num $name $mu
	echo $num
        echo $toys_file
	num=$(( $num + 1 ))
done

