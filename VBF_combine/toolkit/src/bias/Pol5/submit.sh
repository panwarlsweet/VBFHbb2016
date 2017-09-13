export WORKDIR=`pwd`
echo "Working on a machine:" `uname -a`
cd $WORKDIR

num=0
max=50 #100
n_toys=20  #10
inj=_inj
name=Pol5
fit=Pol5
mu=2
#cat0=0
#cat1=2
cat0=3
cat1=6

datacard=/mnt/t3nfs01/data01/shome/nchernya/VBFHbb2016/VBF_fit/bias/datacards/datacard_bias${fit}_m125_CAT${cat0}-CAT${cat1}_CATveto.txt
while [ $num -lt $max ]
do
#	toys_file=$(find /mnt/t3nfs01/data01/shome/nchernya/VBFHbb2016/VBF_fit/bias/toys/${name}/ -name higgsCombine${name}${num}_inj1_cat${cat0}-cat${cat1}.GenerateOnly.mH120.*.root)
	toys_file=$(find /mnt/t3nfs01/data01/shome/nchernya/VBFHbb2016/VBF_fit/bias/toys/new_inj2/ -name higgsCombine${name}${num}_inj2_cat${cat0}-cat${cat1}.GenerateOnly.mH120.*.root)
#	echo $toys_file  
	qsub -q all.q batch.sh  $datacard  $toys_file  ${name}_fit${fit}$inj${mu}_cat${cat0}${cat1}_ $num $name $mu
#	qsub -q all.q batch2.sh  $datacard  $toys_file  ${name}_fit${fit}$inj${mu}_cat${cat0}${cat1}_ $num $name $mu
	echo $num
	num=$(( $num + 1 ))
done

