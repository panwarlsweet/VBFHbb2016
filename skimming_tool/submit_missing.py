import string
import subprocess
import shlex

input = open("BtagCSV_output.txt","rt")
input2 = open("submit_all_easter.txt","rt")
output = open("btagCSV_submit.txt","wt")
lines = input.readlines()
lines2 = input2.readlines()
for i in range(0,len(lines)) : 
	num = str(lines[i].strip())
	num_int = int(lines[i].strip())
#	if ( num_int!=17 and num_int!=76 and num_int!=100 and num_int!=130 and num_int!=214 and num_int!=229):
#		continue
	print num
	search_line = num + " BTagCSV root://stormgf1.pi.infn.it:1094/"
#	if num_int>409 :
#		search_line = num + " SingleElectron root://stormgf1.pi.infn.it:1094/"
	matching = [s.strip() for s in lines2 if s.find(search_line)==0]
#	print matching	
	if len(matching) > 0 :
		for item in matching:
			returnList = item[item.find('root://storm'):]
			output.write('%s\n'%item)
			pass_arg=[]
			pass_arg.append("sh")
		#	pass_arg.append("run_python_skim.sh")
			pass_arg.append("run_python_skim_vbfhbb.sh")
			pass_arg.append(num)
			pass_arg.append('BTagCSV')
			pass_arg.append(returnList)
	#		print pass_arg
			subprocess.check_call(pass_arg)
