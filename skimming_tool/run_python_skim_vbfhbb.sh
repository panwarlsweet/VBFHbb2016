g++ run_skim_macro_vbfhbb.C -g -o run_vbfhbb `root-config --cflags --glibs`
qsub -q all.q batch_python_VBFhbb.sh $1 $2 $3
echo $1 $2 $3
