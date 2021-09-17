import os
import pandas as pd

def dropRep(list1):
    list2=[]
    for i in list1:
        if i not in list2:
            list2.append(i)
    return list2

rpath="/media/zhou/3d3bcba8-4222-49a4-92ae-8d53e869e4ed/data/future/"
path=os.path.join(rpath,"contract.csv")

data=pd.read_csv(path,header=None)
print(data)
with open(os.path.join(rpath,"contractid.csv"),"w") as f:
    print(data[0].tolist())
    unique=dropRep(data[0].tolist())
    print(len(unique))
    
    for d in unique:
        print(d)
        f.write(d+"\n")



