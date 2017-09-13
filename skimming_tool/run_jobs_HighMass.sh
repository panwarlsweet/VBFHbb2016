export WORKDIR=`pwd`
echo "Working on a machine:" `uname -a`
cd $WORKDIR
#g++ run_skim_trees_double_main.C -g -o run `root-config --cflags --glibs`
g++ run_skim_trees_single_main.C -g -o run `root-config --cflags --glibs`

#EOS=root://xrootd-cms.infn.it//store/user/arizzi/VHBBHeppyV21/
EOS=dcap://t3se01.psi.ch:22125//pnfs/psi.ch/cms/trivcat/store/user/nchernya/
TREE=tree_
ROOT=.root
WORKDIR2=/scratch/nchernya

output_dir=(
 VBFSpin0ToBBbar_W_1p0_M_750_TuneCUEP8M1_13TeV_pythia8
 VBFSpin0ToBBbar_W_1p0_M_300_TuneCUEP8M1_13TeV_pythia8
 VBFSpin0ToBBbar_W_1p0_M_450_TuneCUEP8M1_13TeV_pythia8
 VBFSpin0ToBBbar_W_1p0_M_600_TuneCUEP8M1_13TeV_pythia8
 VBFSpin0ToBBbar_W_1p0_M_900_TuneCUEP8M1_13TeV_pythia8
 VBFSpin0ToBBbar_W_1p0_M_1050_TuneCUEP8M1_13TeV_pythia8
 VBFSpin0ToBBbar_W_1p0_M_375_TuneCUEP8M1_13TeV_pythia8
 VBFSpin0ToBBbar_W_1p0_M_525_TuneCUEP8M1_13TeV_pythia8
 VBFSpin0ToBBbar_W_1p0_M_675_TuneCUEP8M1_13TeV_pythia8
 VBFSpin0ToBBbar_W_1p0_M_825_TuneCUEP8M1_13TeV_pythia8
 VBFSpin0ToBBbar_W_1p0_M_975_TuneCUEP8M1_13TeV_pythia8
#VBFHToBB_M-125_13TeV_powheg-ext
# VBFHToBB_M-125_13TeV_powheg 
##QCD_HT100to200
# QCD_HT200to300
# QCD_HT300to500
# QCD_HT500to700
## QCD_HT700to1000
# QCD_HT1000to1500
# QCD_HT1500to2000 
#QCD_HT2000toInf
# TTJets_TuneCUETP8M1_13TeV-madgraph
## TT_TuneCUETP8M1_13TeV-amcatnlo
## DYJetsToQQ WJetsToQQ_HT180_13TeV-madgraph
# DYJetsToLL_M-50_TuneCUETP8M1_13TeV-amcatnlo_ext_1
# DYJetsToLL_M-50_TuneCUETP8M1_13TeV-amcatnlo_ext_2
# DYJetsToLL_M-50_TuneCUETP8M1_13TeV-amcatnlo
# ST_tW_antitop_5f_inclusiveDecays_13TeV-powheg 
#ST_tW_top_5f_inclusiveDecays_13TeV-powheg
# ST_s-channel_4f_leptonDecays_13TeV-amcatnlo
# WJetsToLNu_TuneCUETP8M1_13TeV-amcatnlo
## GluGluHToBB_M125_13TeV_powheg-ext
# GluGluHToBB_M125_13TeV_powheg 
#ttHTobb_M125_13TeV_powheg
# ttHToNonbb_M125_13TeV_powheg
#TT_powheg_1 
#TT_powheg_2 
#TT_powheg_3 
#TT_powheg_4 
#TT_powheg_5 
#TT_powheg_6 
#TT_powheg_7
#ZH_HToBB
#WplusH_HToBB
#WminusH_HToBB
#ZZ
#WZ
#WW 
#SUSYGluGluToBBHToBB_M-120
#bbHToBB_M-125_4FS_yb2
#bbHToBB_M-125_4FS_ybyt
#VBFHToBB_M-125_13TeV_amc
#GluGluHToBB_M125_13TeV_amc
#ST_t-channel_top_4f_inclusiveDecays
#ST_t-channel_antitop_4f_inclusiveDecays
##VBFHToBB_M-125_13TeV_powheg_herwigpp_weightfix
#VBFHToBB_M-125_13TeV_powheg_pythia8_weightfix_CUETP8M1Down
#VBFHToBB_M-125_13TeV_powheg_pythia8_weightfix_CUETP8M1Up 
)
max_trees_number=(100 100 100 100 100 100 100 100 100 100 100) 
current_sample=0
while read sample
do
#	if [ $current_sample -lt 6 ] || [ $current_sample -gt 6 ]
#	if [ $current_sample -ne 43 ] && [ $current_sample -ne 44 ] 
#	then
#		current_sample=$((current_sample + 1))
#		continue
#	fi
	
	cd $WORKDIR
	FILES=$EOS$sample$TREE
	current_tree=1
	while [ $current_tree -le ${max_trees_number[current_sample]} ]
#	while [ $current_tree -le 1 ]
	do
		f=$FILES$current_tree$ROOT
		echo $f
	#	qsub -q short.q batch2.sh $f $current_tree ${output_dir[current_sample]}  # old
#		echo $f $current_tree $WORKDIR/v14${output_dir[current_sample]}$v14 #old
		qsub -q short.q batch21_HighMass.sh $f $current_tree ${output_dir[current_sample]} #old
		#echo $f $current_tree ${output_dir[current_sample]} #old
#		./run_single $f $current_tree $WORKDIR/v14${output_dir[current_sample]}$v14
#		break
#		qsub -q short.q batch2_single.sh $f $current_tree $scratch${output_dir[current_sample]}$v14 
#		if [ $current_sample -eq 12 ]
#			then  
#				qsub -q short.q batch2.sh $f $current_tree $WORKDIR${output_dir[current_sample]}$v14
#		fi
		#break
 		current_tree=$(( $current_tree + 1 ))
	done
#	break
	current_sample=$((current_sample + 1))
#	if [ $current_sample -eq 11 ]
#	then
#		break		
#	fi 
done < samples_paths_v21_HighMass.txt
