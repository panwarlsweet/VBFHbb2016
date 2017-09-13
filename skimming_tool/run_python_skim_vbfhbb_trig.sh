g++ run_skim_macro_vbfhbb_trig.C -g -o run_vbfhbb_trig `root-config --cflags --glibs`
qsub -q all.q batch_python_VBFhbb_trig.sh $1 $2 $3
echo $1 $2 $3
