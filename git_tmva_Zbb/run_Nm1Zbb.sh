export WORKDIR=`pwd`
cd $WORKDIR
g++ tmvaZbb.C -g -o run_Nm1_tmvaZbb   -lMLP -lXMLIO -lTMVA `root-config --cflags --glibs`
cp run_Nm1_tmvaZbb /mnt/t3nfs01/data01/shome/nchernya/VBFHbb2016/Zbb_mva  
cp TMVAClassification_mainZbb.C /mnt/t3nfs01/data01/shome/nchernya/VBFHbb2016/Zbb_mva
cp tmvaZbb.C /mnt/t3nfs01/data01/shome/nchernya/VBFHbb2016//Zbb_mva
cp TMVAGui.C /mnt/t3nfs01/data01/shome/nchernya/VBFHbb2016//Zbb_mva 
cp tmvaglob.C  /mnt/t3nfs01/data01/shome/nchernya/VBFHbb2016//Zbb_mva
cp  efficiencies.C  /mnt/t3nfs01/data01/shome/nchernya/VBFHbb2016//Zbb_mva 


end=BDTIncl_try6
max=6 #10 #12 #13 
#variables_names=( DeltaEtaQQ  CMVAV2_2  qgl1 qgl2 DeltaEtaQB  EtaBB all)
#variables_names=( qgl2)
#variables_names=(  qgl1  EtaBB )
variables_names=( DeltaEtaQQ qgl1 qgl2 DeltaEtaQB  EtaBB all )
dir=/mnt/t3nfs01/data01/shome/nchernya/VBFHbb2016/Zbb_mva/
counter=0
while  [ $counter -lt $max ]
do
	nTrees=150
	MinNodeSize=5 # it is in % already
	maxDepth=3
	echo $nTrees  $MinNodeSize $maxDepth
#	qsub -q short.q batch2.sh ${variables_names[counter]} double $nTrees $MinNodeSize $maxDepth
#	qsub -q short.q batch2.sh ${variables_names[counter]} single $nTrees $MinNodeSize $maxDepth 
	qsub -q short.q batch2.sh ${variables_names[counter]} double $end $dir $nTrees $MinNodeSize $maxDepth
	nTrees=120
	MinNodeSize=10 # it is in % already
	maxDepth=4
#	qsub -q short.q batch2.sh ${variables_names[counter]} single $end  $dir 
	counter=$(( $counter + 1 ))	
done
