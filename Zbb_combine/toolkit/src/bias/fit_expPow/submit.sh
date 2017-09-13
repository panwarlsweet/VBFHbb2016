export WORKDIR=`pwd`
echo "Working on a machine:" `uname -a`
cd $WORKDIR

num=0
max=50 #50
n_toys=20
name=expPow_Pol8_
inj=_inj
mu=2

datacard=/mnt/t3nfs01/data01/shome/nchernya/VBFHbb2016/Zbb_fit/bias/datacards/datacard_biasPol8_zbb.txt
while [ $num -lt $max ]
do
	toys_file=$(find /mnt/t3nfs01/data01/shome/nchernya/VBFHbb2016/Zbb_fit/bias/expPow/root_$mu/ -name higgsCombineexpPow$num$inj$mu.GenerateOnly.mH120.*.root)
#	toys_file=$(find /mnt/t3nfs01/data01/shome/nchernya/VBFHbb2016/Zbb_fit/bias/expPow/root/ -name higgsCombineexpPow$num.GenerateOnly.mH120.*.root)
	#echo $toys_file
	qsub -q all.q batch.sh  $datacard  $toys_file  $name$inj$mu $num
	echo $num
	num=$(( $num + 1 ))
done

