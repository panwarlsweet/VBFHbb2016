export WORKDIR=`pwd`
echo "Working on a machine:" `uname -a`
cd $WORKDIR

num=0
max=50
n_toys=20
name=expPow
inj=_inj
mu=2
datacard=/mnt/t3nfs01/data01/shome/nchernya/VBFHbb2016/Zbb_fit/bias/datacards/datacard_biasexpPow_zbb.txt
while [ $num -lt $max ]
do
	qsub -q short.q batch.sh  $n_toys $mu $name$num$inj$mu  $datacard
	echo $num
	num=$(( $num + 1 ))
done

