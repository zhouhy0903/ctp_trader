#include "ThostFtdcMdApi.h"

#include<iostream>
#include<cstring>
#include<fstream>
#include<vector>
#include<cstring>
#include<time.h>
#include<sstream>
#include<thread>

#include "api/marketdata.hpp"
#include "tools/subscribe.cpp"
#include "common/data_handler.hpp"
#include "common/conn_db.hpp"


using namespace std;
void savemarketdata(){
    time_t now = time(0);
   	char* dt = ctime(&now);
    now=now+8*3600;
	tm *gmtm = gmtime(&now);
	stringstream ss;
    if (gmtm->tm_hour>17)
    {
        cout<<"Night"<<endl;
	    ss<<"future_"<<gmtm->tm_year+1900<<"_"<<gmtm->tm_mon+1<<"_"<<gmtm->tm_mday<<"night";
    } else{
        cout<<"Day"<<endl;
	    ss<<"future_"<<gmtm->tm_year+1900<<"_"<<gmtm->tm_mon+1<<"_"<<gmtm->tm_mday<<"day";
    }

	createdatabase(ss.str());
    string p="";
    if (gmtm->tm_hour>17){
        cout<<"night"<<endl;
	    p="/media/zhou/3d3bcba8-4222-49a4-92ae-8d53e869e4ed/data/future/contractid_test_night.csv";       
    } else{
        p="/media/zhou/3d3bcba8-4222-49a4-92ae-8d53e869e4ed/data/future/contractid_test.csv";
    }
	vector<string> contractid=read_contractid(p);
    
    cout<<"Create Table or not?"<<endl;
    string ifcreatetable;
    cin>>ifcreatetable;
    if (ifcreatetable=="y")
    {
        for (auto i:contractid){
            createtable(ss.str(),i);
            cout<<i<<endl;
        }
        cout<<"Create Table Finished! Receiving data or not?"<<endl;
    }
    string ifreceive;
    cin>>ifreceive;
    if (ifreceive!="y") return;

    //int thread_num=150;
    int thread_num=5;
    for (int i=0;i<thread_num;i++){
        vector<string>::const_iterator start = contractid.cbegin()+i*contractid.size()/thread_num;
        vector<string>::const_iterator end  = contractid.cbegin()+(i+1)*contractid.size()/thread_num;
        if (i==thread_num-1){
            end  = contractid.cend();
        }
        vector<string> cur_contract(start,end);
        for (int j=0;j<cur_contract.size();j++)
            cout<<cur_contract[j]<<" ";
        cout<<endl;
        thread* task=new thread(subscribe,cur_contract,i,true);
    }

}


int main(){
	savemarketdata();
    cout<<"end save marketdata"<<endl;
    while(1){

    }
    /*
	CThostFtdcMdApi *myapi=CThostFtdcMdApi::CreateFtdcMdApi();
	subscribe(myapi,contractid,true);
	while (1)
	{
	}
    */
}
