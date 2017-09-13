export WORKDIR=`pwd`
echo "Working on a machine:" `uname -a`
cd $WORKDIR

num=0
max=100 #100
n_toys=2  #10


datacard=/mnt/t3nfs01/data01/shome/nchernya/VBFHbb2016/VBF_fit/toys_Fit/datacard_vbfHbb_2016_m125.txt

while [ $num -lt $max ]
do
	qsub -q all.q batch.sh  $datacard  $n_toys toys_${n_toys}_num_$num 
	echo $num
	num=$(( $num + 1 ))
done

