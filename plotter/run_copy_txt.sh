export WORKDIR=`pwd`
cd $WORKDIR


declare -A file_names

path=root://t3dcachedb.psi.ch:1094///pnfs/psi.ch/cms/trivcat//store/user/nchernya/VBFHbb2016/plotterOutput/v25/
file_name=(
#DYJetstoLL_amc_0J
#DYJetstoLL_amc_1J
#DYJetstoLL_amc_2J

ST_tW_top
ST_tW_antitop
ST_s-channel
ST_t-channel_top_4f_inclusiveDecays
ST_t-channel_antitop_4f_inclusiveDecays

BTagCSV0
BTagCSV1
BTagCSV2
BTagCSV4
BTagCSV5

QCD_HT100to200
QCD_HT200to300
QCD_HT300to500
QCD_HT500to700
QCD_HT700to1000
QCD_HT1000to1500
QCD_HT1500to2000
QCD_HT2000toInf

)

prefix=''
#postfix=v25_trigWeightNewRegBtagCut_ZbbBdtIncl2
#postfix=v25_VBFbdt
postfix=v25_VBF_newReg_turnOn_notrig
v=v25
ROOT=.root
dataset_type=(double single)
region=(analysis controlTop controlDY)
max_region=1
max_datasettype=2
output_dir=$TMPDIR
pathhome=/afs/cern.ch/work/n/nchernya/VBFHbb_2016/plotter/output_root/


current_file=0
current_trigWeight=0
max_files=19 #20 #17+3 #3  #9+8 
while [ $current_file -lt $max_files  ]
do	 
	current_region=0
	while [ $current_region -lt $max_region  ]
	do	 
	current_datasettype=0
		while [ $current_datasettype -lt $max_datasettype  ]
		do	 
			xrdcp $path${file_name[$current_file]}_${region[$current_region]}_${dataset_type[$current_datasettype]}_trignone_$postfix.root /afs/cern.ch/work/n/nchernya/VBFHbb_2016/plotter/output_root/

			current_datasettype=$((current_datasettype + 1))
		done
		current_region=$((current_region + 1))
	done
	current_file=$((current_file + 1))
done




list="
BTagCSV
QCD
ST
"
#DYJetstoLL_amc

for arg in $list
do
	current_region=0
	while [ $current_region -lt $max_region  ]
	do	 
		current_datasettype=0
		while [ $current_datasettype -lt $max_datasettype  ]
		do	 

			hadd ${pathhome}${arg}_${region[$current_region]}_${dataset_type[$current_datasettype]}_trignone_$postfix.root ${pathhome}$arg*_${region[$current_region]}_${dataset_type[$current_datasettype]}_trignone_$postfix.root

			xrdfs t3dcachedb03.psi.ch rm /pnfs/psi.ch/cms/trivcat/store/user//nchernya/VBFHbb2016/plotterOutput/v25/${arg}_${region[$current_region]}_${dataset_type[$current_datasettype]}_trignone_$postfix.root


			path2=root://t3dcachedb.psi.ch:1094///pnfs/psi.ch/cms/trivcat/

			xrdcp -f ${pathhome}${arg}_${region[$current_region]}_${dataset_type[$current_datasettype]}_trignone_$postfix.root $path2/store/user/nchernya/VBFHbb2016/plotterOutput/v25/

			current_datasettype=$((current_datasettype + 1))
		done
		current_region=$((current_region + 1))
	done
done
