export WORKDIR=`pwd`
cd $WORKDIR

g++ run_create_matching.C -g -o r `root-config --cflags --glibs` 

max_samples_num=1 
path=dcap://t3se01.psi.ch:22125//pnfs/psi.ch/cms/trivcat///store/user/nchernya/VBFHbb2016/v25_skim/
#path=/afs/cern.ch/work/n/nchernya/tmva/TMVA-v4.2.0/test/VBFHbb2016_blikelihood/application/
path=dcap://t3se01.psi.ch:22125//pnfs/psi.ch/cms/trivcat//store/user/nchernya/VBFHbb2016/workflow/v25/BTagCSV/
input_dir=(  skimmed_tree_142)
ROOT=.root
v=_v25


current_sample=0
while [ $current_sample -lt $max_samples_num ]
do
	file=$path${input_dir[ $current_sample ]}$ROOT
	./r $file 

	current_sample=$(( $current_sample + 1 ))
done
