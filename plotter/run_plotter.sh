export WORKDIR=`pwd`
cd $WORKDIR

g++ plotter_VBFHbb2016.C -g -o plot `root-config --cflags --glibs`  -lMLP -lXMLIO -lTMVA  

declare -A file_names

cp plot /mnt/t3nfs01/data01/shome/nchernya/VBFHbb2016/plotter/ 
cp  batch.sh	/mnt/t3nfs01/data01/shome/nchernya/VBFHbb2016/plotter/

 
#path=dcap://t3se01.psi.ch:22125//pnfs/psi.ch/cms/trivcat/store/user/nchernya/VBFHbb2016/blike_reg_v25/
#path=dcap://t3se01.psi.ch:22125//pnfs/psi.ch/cms/trivcat/store/user/nchernya/VBFHbb2016/v25_Zbb_mva/
path=dcap://t3se01.psi.ch:22125//pnfs/psi.ch/cms/trivcat/store/user/nchernya/VBFHbb2016/v25_VBF_mva_JESR_full/
file_names=(
#["BTagCSV0"]=BTagCSV0
#["BTagCSV1"]=BTagCSV1
#["BTagCSV2"]=BTagCSV2
################["BTagCSV3"]=BTagCSV3
#["BTagCSV4"]=BTagCSV4
#["BTagCSV5"]=BTagCSV5
#["VBFHToBB_M-125"]=VBFHbb
#["GluGluHToBB_M-125"]=ggHbb
#["QCD_HT100to200"]=QCD_HT100to200
#["QCD_HT200to300"]=QCD_HT200to300
#["QCD_HT300to500"]=QCD_HT300to500 
#["QCD_HT500to700"]=QCD_HT500to700
#["QCD_HT700to1000"]=QCD_HT700to1000
#["QCD_HT1000to1500"]=QCD_HT1000to1500
#["QCD_HT1500to2000"]=QCD_HT1500to2000
#["QCD_HT2000toInf"]=QCD_HT2000toInf 
#["ST_tW_top"]=ST_tW_top
#["ST_tW_antitop"]=ST_tW_antitop
#["ST_s-channel"]=ST_s
#["ST_t-channel_top_4f_inclusiveDecays"]=ST_t_top
#["ST_t-channel_antitop_4f_inclusiveDecays"]=ST_t_antitop
#["ST_s_inclusive"]=ST_s_inclusive
#["WJetsToQQ"]=WJetsToQQ
#["DYJetsToQQ"]=DYJetsToQQ
#["TT"]=TT
##["DYJetstoLL_amc_0J"]=DYJetstoLL_amc_0J
##["DYJetstoLL_amc_1J"]=DYJetstoLL_amc_1J
#["DYJetstoLL_amc_2J"]=DYJetstoLL_amc_2J
##["WJetsToLNu"]=WJetsToLnu_madgraph

["VBFHToBB_M-125_herwig"]=VBFHbb_herwig
#["VBFHToBB_M-125_ueps_down"]=VBFHbb_CUEDown
#["VBFHToBB_M-125_ueps_up"]=VBFHbb_CUEUp
#["VBFHToBB_M-125_amc"]=VBFHbb_amc
##["WminusH_HToBB"]=WminusHbb_powheg
#["WplusH_HToBB"]=WplusHbb_powheg
#["ZH_HToBB"]=ZHbb_powheg
["GluGluHToBB_M-125_herwig"]=ggHbb_herwig
#["GluGluHToBB_M-125_amc"]=ggHbb_amc
#["bbHToBB_yb2"]=bbH_yb2
#["bbHToBB_ybyt"]=bbH_ybyt
#["WW"]=WW
#["ZZ"]=ZZ
#["WZ"]=WZ
#["ttHTobb_M125"]=ttHbb
#["ttHToNonbb_M125"]=ttHnonbb

#["DYJetsToLL"]=DYJetsToLL_M-50_TuneCUETP8M1_13TeV-amcatnlo_ext_1
#["WJetsToLNu"]=WJetsToLNu_TuneCUETP8M1_13TeV-amcatnlo
#["WW"]=WW
#["ZZ"]=ZZ
#["WZ"]=WZ
#["bbHSusy120"]=SUSYGluGluToBBHToBB_M-120
#["bbHToBB_yb2"]=bbHToBB_M-125_4FS_yb2
#["bbHToBB_ybyt"]=bbHToBB_M-125_4FS_ybyt
#["VBFHToBB_M-125_amc"]=VBFHToBB_M-125_13TeV_amc
#["GluGluHToBB_M-125_amc"]=GluGluHToBB_M125_13TeV_amc
#["GluGluHToBB_M-125_ueps_up"]=gf_ueps_pythia_up
#["GluGluHToBB_M-125_ueps_down"]=gf_ueps_pythia_down
#["VBFHToBB_M-125_ueps_down"]=VBFHToBB_M-125_13TeV_powheg_pythia8_weightfix_CUETP8M1Down
#["VBFHToBB_M-125_herwig"]=VBFHToBB_M-125_13TeV_powheg_herwigpp_weightfix
#["VBFHToBB_M-125_ueps_up"]=VBFHToBB_M-125_13TeV_powheg_pythia8_weightfix_CUETP8M1Up
#["GluGluHToBB_M-125_herwig"]=gf_herwig
#["ttHTobb_M125"]=ttHTobb_M125_13TeV_powheg
#["ttHToNonbb_M125"]=ttHToNonbb_M125_13TeV_powheg
#["WplusH_HToBB"]=WplusH_HToBB
#["WminusH_HToBB"]=WminusH_HToBB
#["ZH_HToBB"]=ZH_HToBB

)
#prefix='blike_v25_'
#prefix='blike_reg_v25_'
#prefix='ZbbMva_v25_'
prefix='VBFMvaJESR_v25_'
prefix2=(double single)
file_end=(_double _single)
#postfix=trigWeightNewRegBtagCut_ZbbBdtInclFitWeight
#postfix=VBFbdt_transfer
#postfix=notriggercorr
postfix=VBF_herwig_noqgl
#postfix=JECup2
#postfix=JECdown2
#postfix=JERup2
#postfix=JERdown2
#postfix=JECnom2
v=v25
ROOT=.root
dataset_type=(double single)
region=(analysis controlTop controlDY)
applyTrigWeight=0
trigWeightNom=(nom up down)
output_dir=$TMPDIR


for key in ${!file_names[@]}; do
	current_region=0
	while [ $current_region -lt  1 ] 
#	while [ $current_region -lt  3 ] 
	do
		data=0
		if [ $key == BTagCSV ] || [ $key == BTagCSV0 ] || [ $key == BTagCSV1 ] || [ $key == BTagCSV2 ] || [ $key == BTagCSV3 ] || [ $key == BTagCSV4 ] || [ $key == BTagCSV5 ]

		then 
	 		data=1
		fi
		if [ $key == BTagCSV ] || [ $key == BTagCSV0 ] || [ $key == BTagCSV1 ] || [ $key == BTagCSV2 ] || [ $key == BTagCSV3 ]  || [ $key == BTagCSV4 ] || [ $key == BTagCSV5 ] || [ $applyTrigWeight -eq 0 ]
		then
			f=$path${prefix2[0]}$prefix${file_names[${key}]}.root
		#	qsub -q all.q batch.sh  $f ${key} ${dataset_type[0]} ${region[$current_region]} $data  0 none $v $postfix
		#	echo  $f ${key} ${dataset_type[0]} ${region[$current_region]} $data  0 none $v $postfix
			f=$path${prefix2[1]}$prefix${file_names[${key}]}.root
			echo  $f ${key} ${dataset_type[0]} ${region[$current_region]} $data  0 none $v $postfix
		#	qsub -q all.q batch.sh  $f ${key} ${dataset_type[1]} ${region[$current_region ]} $data 0 none $v $postfix
		fi 
		if [ $key != BTagCSV ] && [ $key != BTagCSV0 ] && [ $key != BTagCSV1 ] && [ $key != BTagCSV2 ] && [ $key != BTagCSV3 ]  && [ $key != BTagCSV4 ] && [ $key != BTagCSV5 ] && [ $applyTrigWeight -eq 1 ]
		then
			current_trigWeight=0
			while [ $current_trigWeight -lt  1 ] 
#			while [ $current_trigWeight -lt  3 ] 
			do
				f=$path${prefix2[0]}$prefix${file_names[${key}]}.root
			#	echo  $f ${key} ${dataset_type[0]} ${region[$current_region]} $data  $applyTrigWeight ${trigWeightNom[$current_trigWeight]} $v $postfix
			#	qsub -q all.q batch.sh  $f ${key} ${dataset_type[0]} ${region[$current_region]} $data  $applyTrigWeight ${trigWeightNom[$current_trigWeight]} $v $postfix
				f=$path${prefix2[1]}$prefix${file_names[${key}]}.root
	#			qsub -q all.q batch.sh  $f ${key} ${dataset_type[1]} ${region[$current_region ]} $data $applyTrigWeight ${trigWeightNom[$current_trigWeight]} $v $postfix
				current_trigWeight=$(( $current_trigWeight + 1 ))
			done
		fi
		current_region=$(( $current_region + 1 ))
#		break
	done
#	break
done
