export WORKDIR=`pwd`
cd $WORKDIR
g++ tmva.C -g -o run_Nm1_tmva   -lMLP -lXMLIO -lTMVA `root-config --cflags --glibs`
cp run_Nm1_tmva /mnt/t3nfs01/data01/shome/nchernya/VBFHbb2016/main_mva  
cp TMVAClassification_main.C /mnt/t3nfs01/data01/shome/nchernya/VBFHbb2016/main_mva
cp tmva.C /mnt/t3nfs01/data01/shome/nchernya/VBFHbb2016//main_mva
cp TMVAGui.C /mnt/t3nfs01/data01/shome/nchernya/VBFHbb2016//main_mva 
cp tmvaglob.C  /mnt/t3nfs01/data01/shome/nchernya/VBFHbb2016//main_mva
cp  efficiencies.C  /mnt/t3nfs01/data01/shome/nchernya/VBFHbb2016//main_mva 


end=PreapptovalFinalMbb
max=1 #10 #12 #13 
#####variables_names=(Mqq DeltaEtaQQ DeltaPhiQQ SoftN5 CMVAV2_1 CMVAV2_2 Jet5_pt qgl1 qgl2 DeltaEtaQB qqbb_pt qqbb_pz all)
#variables_names=(Mqq DeltaEtaQQ DeltaPhiQQ SoftN5 CMVAV2_1 CMVAV2_2 qgl1 qgl2 DeltaEtaQB  qqbb_pz all)
variables_names=(all)
dir=/mnt/t3nfs01/data01/shome/nchernya/VBFHbb2016/main_mva/
counter=0
while  [ $counter -lt $max ]
do
	nTrees=120
	MinNodeSize=8 # it is in % already
	maxDepth=3
	echo $nTrees  $MinNodeSize $maxDepth
#	qsub -q short.q batch2.sh ${variables_names[counter]} double $nTrees $MinNodeSize $maxDepth
#	qsub -q short.q batch2.sh ${variables_names[counter]} single $nTrees $MinNodeSize $maxDepth 
	qsub -q short.q batch2.sh ${variables_names[counter]} double $end $dir $nTrees $MinNodeSize $maxDepth 
	nTrees=200
	MinNodeSize=5 # it is in % already
	maxDepth=3
	echo $nTrees  $MinNodeSize $maxDepth
	qsub -q short.q batch2.sh ${variables_names[counter]} single $end  $dir $nTrees $MinNodeSize $maxDepth 
	counter=$(( $counter + 1 ))	
done
