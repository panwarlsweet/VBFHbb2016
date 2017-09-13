export WORKDIR=`pwd`
echo "Working on a machine:" `uname -a`
cd $WORKDIR

num=0
max=100
n_toys=10
name=Pol3
inj=_inj
mu=1
cat0=0
cat1=2
datacard=/mnt/t3nfs01/data01/shome/nchernya/VBFHbb2016/VBF_fit/bias/datacards/datacard_bias${name}_m125_CAT${cat0}-CAT${cat1}_CATveto.txt
while [ $num -lt $max ]
do
	qsub -q short.q batch.sh  $n_toys $mu $name$num$inj${mu}_cat${cat0}-cat${cat1}  $datacard $name
	echo $num
	num=$(( $num + 1 ))
done

