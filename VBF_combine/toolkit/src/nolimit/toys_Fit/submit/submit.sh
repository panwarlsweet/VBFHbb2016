export WORKDIR=`pwd`
echo "Working on a machine:" `uname -a`
cd $WORKDIR

num=0
max=100 #100
n_toys=2  #10


#datacard=/mnt/t3nfs01/data01/shome/nchernya/VBFHbb2016/VBF_fit/toys_Fit_nolimit/datacard_vbfHbb_names_m125.txt
datacard=/mnt/t3nfs01/data01/shome/nchernya/VBFHbb2016/VBF_fit/toys_Fit_nolimit/datacard_vbfHbb_names_m125_CAT0-CAT0_CATveto.txt

while [ $num -lt $max ]
do
	qsub -q all.q batch.sh  $datacard  $n_toys CAT0_${n_toys}_num_$num 
	echo $num
	num=$(( $num + 1 ))
done

