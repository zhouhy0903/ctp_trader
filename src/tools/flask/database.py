import pymysql
import pandas as pd
import time
import matplotlib.pyplot as plt
from datetime import datetime
from flask.json import jsonify
import os

def get_dbname() -> str:
    print(time.localtime(time.time()))
    return "test"

# dbname=time.strftime('future_%Y_%-m_%-dnight',time.localtime(time.time()))
dbname=time.strftime('future_%Y_%-m_%-dday',time.localtime(time.time()))
# dbname="future_2021_9_3day"

def get_base_data(InstrumentID):
    print("database ",InstrumentID)
    # dbname=time.strftime('future_%Y_%-m_%-dday',time.localtime(time.time()))
    db=pymysql.connect(host="127.0.0.1",user="root",passwd="mysql990903",db=dbname)
    cursor=db.cursor()
    cursor.execute("select LastPrice,UpdateTime,UpdateMillisec,Volume from {} ORDER BY UpdateTime DESC,UpdateMillisec DESC LIMIT 120".format(InstrumentID))
    #cursor.execute("select LastPrice,UpdateTime from IF2109;")
    data=cursor.fetchall()
    # print(data)
    t=[int(time.mktime(datetime.strptime(d[1]+"."+str(int(d[2]/100)), "%H:%M:%S.%f").timetuple()) * 1000.0 + datetime.strptime(d[1]+"."+str(int(d[2]/100)), "%H:%M:%S.%f").microsecond / 1000.0) for d in data[::-1]]
    p=[d[0] for d in data[::-1]]
    v=[d[3] for d in data[::-1]]
    for i in range(len(v)-1,0,-1):
        v[i]=v[i]-v[i-1]
    v=v[1:]
    p=p[1:]
    t=t[1:]
    print(len(v),len(t),"*"*100)
    # t = time.strptime(t, "%H:%M:%S.%f")
    # t = time.mktime(t)
    return t,p,v

def get_update_data(InstrumentID:str):
    # dbname=time.strftime('future_%Y_%-m_%-dday',time.localtime(time.time()))
    db=pymysql.connect(host="127.0.0.1",user="root",passwd="mysql990903",db=dbname)
    cursor=db.cursor()
    #cursor.execute("select LastPrice,UpdateTime from IF2109 ORDER BY UpdateTime DESC LIMIT 10;")
    cursor.execute("select LastPrice,UpdateTime,UpdateMillisec,Volume from {} ORDER BY UpdateTime DESC,UpdateMillisec DESC LIMIT 2;".format(InstrumentID))
    data=cursor.fetchall()
    data=data[::-1]
    t=data[0][1]+"."+str(int(data[0][2]/100))
    print("original ",t)
    t = datetime.strptime(t, "%H:%M:%S.%f")
    t = int(time.mktime(t.timetuple()) * 1000.0 + t.microsecond / 1000.0)
    # t = time.mktime(t)
    p=data[0][0]
    v=data[1][3]-data[0][3]
    print(t,p)
    return t,p,v


    #print(price[:5])
    #plt.plot(time,price)
    #plt.xticks([])
    #plt.savefig("test.png")

def get_dbposition(InstrumentID:str):
    # dbname=time.strftime('future_%Y_%-m_%-dday',time.localtime(time.time()))
    db=pymysql.connect(host="127.0.0.1",user="root",passwd="mysql990903",db="future")
    cursor=db.cursor()
    cursor.execute("select Position from position where InstrumentID=\"{}\" ORDER BY Time DESC LIMIT 1;".format(InstrumentID))
    data=cursor.fetchall()
    if len(data)==0:
        return 0

    return data[0][0]

def get_profit(InstrumentID:str):
    # try:
    #     os.system("/home/zhou/Desktop/code/git/ctp_trader/build/position")
    # except Exception as e:
    #     pass

    # dbname=time.strftime('future_%Y_%-m_%-dday',time.localtime(time.time()))
    db=pymysql.connect(host="127.0.0.1",user="root",passwd="mysql990903",db="future")
    cursor=db.cursor()
    cursor.execute("select CloseProfit from position where InstrumentID=\"{}\" ORDER BY Time DESC LIMIT 1;".format(InstrumentID))
    data=cursor.fetchall()
    if len(data)==0:
        return 0
    
    return data[0][0]


if __name__=="__main__":
    # print(get_base_data("IF2109"))
    # get_update_data("IF2109")
    print(get_dbname)
