#ls -v /pnfs/psi.ch/cms/trivcat/store/user/nchernya/VBFZll/workflow/v25b/SingleElectron  > el_done.txt

import string

input = open("el_done_2.txt","rt")
output = open("el_output_3.txt","wt")
lines = input.readlines()
max_num = 1007
for i in range(0,max_num+1) : 
	found = 0
	num = str(i)
	search_line = "skimmed_tree_"+ num +".root\n"
	if search_line not in lines:
		output.write('%i\n'%i)
