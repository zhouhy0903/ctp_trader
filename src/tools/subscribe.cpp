#include "ThostFtdcMdApi.h"
#include<iostream>
#include<cstring>
#include<time.h>
#include<vector>
#include "api/marketdata.hpp"

using namespace std;
void subscribe(vector<string> contractid,int threadnum,bool ifwrite=true){
	
	CThostFtdcMdApi *myapi=CThostFtdcMdApi::CreateFtdcMdApi();
	char **conid=new char*[contractid.size()];

	for (int i=0;i<contractid.size();i++){
		conid[i]=new char[11];
		strcpy(conid[i], contractid[i].c_str());
	}
	time_t now = time(0);
   	char* dt = ctime(&now);
    now=now+8*3600;
	tm *gmtm = gmtime(&now);
	stringstream ss;
    
	if (gmtm->tm_hour>17)
    {
	    ss<<"future_"<<gmtm->tm_year+1900<<"_"<<gmtm->tm_mon+1<<"_"<<gmtm->tm_mday<<"night";
    } else{
	    ss<<"future_"<<gmtm->tm_year+1900<<"_"<<gmtm->tm_mon+1<<"_"<<gmtm->tm_mday<<"day";
    }
	
	cout<<ss.str()<<endl;
	MarketDataCollector mdCollector(myapi,conid,contractid.size(),"/media/zhou/3d3bcba8-4222-49a4-92ae-8d53e869e4ed/data/future/20210806/",ss.str(),threadnum,ifwrite);
	myapi->RegisterSpi(&mdCollector);
	char add_char[]="tcp://218.202.237.33:10213";
	myapi->RegisterFront(add_char);
	myapi->Init();
	myapi->Join();
	}
