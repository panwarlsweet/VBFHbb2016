export WORKDIR=`pwd`
echo "Working on a machine:" `uname -a`
cd $WORKDIR

g++ turnOnN_1.C -g -o turnOn `root-config --cflags --glibs`


cp turnOn /mnt/t3nfs01/data01/shome/nchernya/VBFHbb2016/triggers/ 
cp  batch2.sh	/mnt/t3nfs01/data01/shome/nchernya/VBFHbb2016/triggers/

declare -A file_names

path=dcap://t3se01.psi.ch:22125//pnfs/psi.ch/cms/trivcat/store/user/nchernya/VBFHbb2016/v25_triggers/

file_names=(
["QCD_HT100to200"]=QCD_HT100to200
["QCD_HT200to300"]=QCD_HT200to300
["QCD_HT300to500"]=QCD_HT300to500 
["QCD_HT500to700"]=QCD_HT500to700
["QCD_HT700to1000"]=QCD_HT700to1000
["QCD_HT1000to1500"]=QCD_HT1000to1500
["QCD_HT1500to2000"]=QCD_HT1500to2000
["QCD_HT2000toInf"]=QCD_HT2000toInf 
#["JetHT"]=JetHT
)

dataset_type=(double single)
output_dir=$TMPDIR
trigger=6
ending=_after1btag

for key in ${!file_names[@]}; do
	data=0
	f=$path${file_names[${key}]}_triggers_QuadVBF_v25.root
	if [ $key == JetHT ]
	then 
		data=1
		f=$path${file_names[${key}]}_triggers_v25.root
	fi
#	f=$path${file_names[${key}]}_triggers_v25.root
	qsub -q all.q batch2.sh $f ${key} ${dataset_type[0]} $data $trigger $ending  
	qsub -q all.q batch2.sh $f ${key} ${dataset_type[1]} $data $trigger $ending
#	echo $key
done
