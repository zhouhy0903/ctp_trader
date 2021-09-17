import os
import re
with open("struct.txt") as f:
	lines=f.readlines()
	for l in lines:
		l=l.strip("\n")
		if l.endswith(";") and l[0]!='}':
			name=re.findall(r"\t(.*)\t(.*);",l)[0][1]
			key=re.findall(r"\t(.*)\t(.*);",l)[0][0]
			#print("`{}`,".format(name),end="")
			print("pIP->{}".format(name),"<<\"\',\'\"<<",end="")
