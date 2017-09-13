#!/bin/bash

g++ btagWeight_unc.C -g -o btag `root-config --cflags --glibs`  -lMLP -lXMLIO -lTMVA

variables="
1
2
3
4
5
6
7
8
"

for arg in $variables
do
	./btag 1 0 $arg
	sleep 3
done

