g++ run_skim_macro.C -g -o run `root-config --cflags --glibs`
qsub -q all.q batch_python_Zll.sh $1 $2 $3
echo $1 $2 $3
