export WORKDIR=`pwd`
cd $WORKDIR

g++ run_create_main_tmva_all.C -g -o run_all `root-config --cflags --glibs` 

max_samples_num=2
path=dcap://t3se01.psi.ch:22125//pnfs/psi.ch/cms/trivcat/store/user/nchernya/VBFHbb2016/blike_reg_v25/
input_dir=( VBFHbb BTagCSV0 BTagCSV1 BTagCSV2 BTagCSV4 BTagCSV5 DYJetsToQQ)
data=(0 1 1 1 1 1 0 )

prefix='blike_reg_v25_'
postfix=First
v=v25
ROOT=.root



current_sample=1
while [ $current_sample -lt $max_samples_num ]
do	
#	f=$path$prefix${input_dir[ $current_sample ]}.root
	data_files=$path$prefix${input_dir[1]}.root,$path$prefix${input_dir[2]}.root,$path$prefix${input_dir[3]}.root,$path$prefix${input_dir[4]}.root,$path$prefix${input_dir[5]}.root
#	data_files=$path$prefix${input_dir[$current_sample]}.root
	echo $data_files
	./run_all ${input_dir[ $current_sample ]} ${data[ $current_sample ]} 0 $data_files
#	./run_all ${input_dir[ $current_sample ]} ${data[ $current_sample ]} 1 $data_files

	current_sample=$(( $current_sample + 1 ))
done
