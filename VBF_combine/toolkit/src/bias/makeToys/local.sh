export WORKDIR=`pwd`
echo "Working on a machine:" `uname -a`
cd $WORKDIR

num=0
max=50
n_toys=20
name=Pol5
name_list="
Pol3
expPow
tanh
modG
sine
Pol4
Pol5
"
inj=_inj
mu=2
cat0=0
cat1=2

for arg in $name_list:
do
	name=$arg
	datacard=/mnt/t3nfs01/data01/shome/nchernya/VBFHbb2016/VBF_fit/bias/datacards/datacard_bias${name}_m125_CAT${cat0}-CAT${cat1}_CATveto.txt
	num=0
	while [ $num -lt $max ]
	do
		combine -M GenerateOnly --X-rtd FITTER_NEVER_GIVE_UP --X-rtd FITTER_BOUND --X-rtd ADDNLL_RECURSIVE=0 --X-rtd FITTER_NEW_CROSSING_ALGO --toysFrequentist -t $n_toys --expectSignal 2 --saveToys  --rMin=-8 --rMax=8 -n $name$num$inj${mu}_cat${cat0}-cat${cat1} -s -1  $datacard
		echo $num
		num=$(( $num + 1 ))
	done
done

