#ifndef __MARKETDATA_HPP_
#define __MARKETDATA_HPP_

#include<cstring>
#include<iostream>
#include "ThostFtdcMdApi.h"
#include<vector>
#include<sstream>
#include<typeinfo>
#include<mysql/mysql.h>
#include "common/data_handler.hpp"
#include "common/conn_db.hpp"

using namespace std;



void change_maxnum(double &origin){
	if (origin>100000000){
		origin=NULL;
	}
}

string columns_name[]{"TradingDay","InstrumentID","ExchangeID","ExchangeInstID","LastPrice","PreSettlementPrice","PreClosePrice","PreOpenInterest","OpenPrice","HighestPrice","LowestPrice","Volume","Turnover","OpenInterest","ClosePrice","SettlementPrice","UpperLimitPrice","LowerLimitPrice","PreDelta","CurrDelta","UpdateTime","UpdateMillisec","BidPrice1","BidVolume1","AskPrice1","AskVolume1","BidPrice2","BidVolume2","AskPrice2","AskVolume2","BidPrice3","BidVolume3","AskPrice3","AskVolume3","BidPrice4","BidVolume4","AskPrice4","AskVolume4","BidPrice5","BidVolume5","AskPrice5","AskVolume5","AveragePrice","ActionDay"};


class MarketDataCollector:public CThostFtdcMdSpi{
	public:
	MarketDataCollector(CThostFtdcMdApi *pMdApi,char** contractid,int contract_num,string path,string dbname,int thnum,bool ifwrite):m_pMdApi(pMdApi),m_contractid(contractid),contract_num(contract_num),path(path),ifwrite(ifwrite){
		vector<string> ans(4);
		ans=get_config();
		BrokerID=ans[0];
		UserID=ans[1];
		Password=ans[2];
		cout<<dbname<<endl;
		mysql=init_mysql(dbname);
		databasename=dbname;
		threadnum=thnum;

	}
	~MarketDataCollector(){}

	void OnFrontConnected(){
		cout<<"Init Finished! Logging in!"<<endl;
		CThostFtdcReqUserLoginField req;
		memset(&req,0,sizeof(req));


		strcpy(req.BrokerID,BrokerID.c_str());
		strcpy(req.UserID,UserID.c_str());
		strcpy(req.Password,Password.c_str());
		int ret=m_pMdApi->ReqUserLogin(&req,1);
		cout<<ret<<endl;
		if (ret!=0)
			cerr<<"Login Failed!"<<endl;
	}

	void OnRspUserLogin(CThostFtdcRspUserLoginField *pRspUserLogin,CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast){
		cout<<"Log In Finished! Checking contracts!"<<endl;
		// char* contract[]{"IF2108","IC2108"};
		int ret=m_pMdApi->SubscribeMarketData(m_contractid,contract_num);
		cout<<ret<<endl;
	}

	void OnRspSubscribeMarketData(){

	}

	void OnRtnDepthMarketData(CThostFtdcDepthMarketDataField* pDepthMarketData){
		auto pD=pDepthMarketData;
		if (ifwrite==true){
		// ofstream ofile;
		// ofile.open(path+"ctp2.csv",ios::app|ios::out);
		// ofile<<pD->TradingDay <<","<<pD->InstrumentID <<","<<pD->ExchangeID <<","<<pD->ExchangeInstID <<","<<pD->LastPrice <<","<<pD->PreSettlementPrice <<","<<pD->PreClosePrice <<","<<pD->PreOpenInterest <<","<<pD->OpenPrice <<","<<pD->HighestPrice <<","<<pD->LowestPrice <<","<<pD->Volume <<","<<pD->Turnover <<","<<pD->OpenInterest <<","<<pD->ClosePrice <<","<<pD->SettlementPrice <<","<<pD->UpperLimitPrice <<","<<pD->LowerLimitPrice <<","<<pD->PreDelta <<","<<pD->CurrDelta <<","<<pD->UpdateTime <<","<<pD->UpdateMillisec <<","<<pD->BidPrice1 <<","<<pD->BidVolume1 <<","<<pD->AskPrice1 <<","<<pD->AskVolume1 <<","<<pD->BidPrice2 <<","<<pD->BidVolume2 <<","<<pD->AskPrice2 <<","<<pD->AskVolume2 <<","<<pD->BidPrice3 <<","<<pD->BidVolume3 <<","<<pD->AskPrice3 <<","<<pD->AskVolume3 <<","<<pD->BidPrice4 <<","<<pD->BidVolume4 <<","<<pD->AskPrice4 <<","<<pD->AskVolume4 <<","<<pD->BidPrice5 <<","<<pD->BidVolume5 <<","<<pD->AskPrice5 <<","<<pD->AskVolume5 <<","<<pD->AveragePrice <<","<<pD->ActionDay <<endl;
		stringstream values;
		change_maxnum(pD->ClosePrice);
		change_maxnum(pD->HighestPrice);
		change_maxnum(pD->LowestPrice);
		change_maxnum(pD->BidPrice1);
		change_maxnum(pD->AskPrice1);
		change_maxnum(pD->PreClosePrice);
		change_maxnum(pD->SettlementPrice);
		change_maxnum(pD->PreSettlementPrice);
		change_maxnum(pD->UpperLimitPrice);
		change_maxnum(pD->LowerLimitPrice);
		change_maxnum(pD->LastPrice);
		change_maxnum(pD->OpenPrice);
		change_maxnum(pD->Turnover);
		change_maxnum(pD->CurrDelta);
		change_maxnum(pD->PreDelta);
		change_maxnum(pD->BidPrice2);
		change_maxnum(pD->BidPrice3);
		change_maxnum(pD->BidPrice4);
		change_maxnum(pD->BidPrice5);
		change_maxnum(pD->AskPrice2);
		change_maxnum(pD->AskPrice3);
		change_maxnum(pD->AskPrice4);
		change_maxnum(pD->AskPrice5);
		change_maxnum(pD->AveragePrice);
		values<<"'"<<pD->TradingDay <<"','"<<pD->InstrumentID <<"','"<<pD->ExchangeID <<"','"<<pD->ExchangeInstID <<"','"<<pD->LastPrice <<"','"<<pD->PreSettlementPrice <<"','"<<pD->PreClosePrice <<"','"<<pD->PreOpenInterest <<"','"<<pD->OpenPrice <<"','"<<pD->HighestPrice <<"','"<<pD->LowestPrice <<"','"<<pD->Volume <<"','"<<pD->Turnover <<"','"<<pD->OpenInterest <<"','"<<pD->ClosePrice <<"','"<<pD->SettlementPrice <<"','"<<pD->UpperLimitPrice <<"','"<<pD->LowerLimitPrice <<"','"<<pD->PreDelta <<"','"<<pD->CurrDelta <<"','"<<pD->UpdateTime <<"','"<<pD->UpdateMillisec <<"','"<<pD->BidPrice1 <<"','"<<pD->BidVolume1 <<"','"<<pD->AskPrice1 <<"','"<<pD->AskVolume1 <<"','"<<pD->BidPrice2 <<"','"<<pD->BidVolume2 <<"','"<<pD->AskPrice2 <<"','"<<pD->AskVolume2 <<"','"<<pD->BidPrice3 <<"','"<<pD->BidVolume3 <<"','"<<pD->AskPrice3 <<"','"<<pD->AskVolume3 <<"','"<<pD->BidPrice4 <<"','"<<pD->BidVolume4 <<"','"<<pD->AskPrice4 <<"','"<<pD->AskVolume4 <<"','"<<pD->BidPrice5 <<"','"<<pD->BidVolume5 <<"','"<<pD->AskPrice5 <<"','"<<pD->AskVolume5 <<"','"<<pD->AveragePrice <<"','"<<pD->ActionDay <<"'";
		// ofile.close();
		stringstream InstrumentID;
		InstrumentID<<pD->InstrumentID;
		string s="INSERT INTO `"+InstrumentID.str()+"` (`TradingDay`,`InstrumentID`,`ExchangeID`,`ExchangeInstID`,`LastPrice`,`PreSettlementPrice`,`PreClosePrice`,`PreOpenInterest`,`OpenPrice`,`HighestPrice`,`LowestPrice`,`Volume`,`Turnover`,`OpenInterest`,`ClosePrice`,`SettlementPrice`,`UpperLimitPrice`,`LowerLimitPrice`,`PreDelta`,`CurrDelta`,`UpdateTime`,`UpdateMillisec`,`BidPrice1`,`BidVolume1`,`AskPrice1`,`AskVolume1`,`BidPrice2`,`BidVolume2`,`AskPrice2`,`AskVolume2`,`BidPrice3`,`BidVolume3`,`AskPrice3`,`AskVolume3`,`BidPrice4`,`BidVolume4`,`AskPrice4`,`AskVolume4`,`BidPrice5`,`BidVolume5`,`AskPrice5`,`AskVolume5`,`AveragePrice`,`ActionDay`) VALUES(";
		s=s+values.str()+");";
		// cout<<s<<endl;
		stringstream threadnum_str;
		threadnum_str<<threadnum;

		insert_data(s,mysql,"Thread: "+threadnum_str.str());
		}
		else
			cout<<pD->TradingDay <<","<<pD->InstrumentID <<","<<pD->ExchangeID <<","<<pD->ExchangeInstID <<","<<pD->LastPrice <<","<<pD->PreSettlementPrice <<","<<pD->PreClosePrice <<","<<pD->PreOpenInterest <<","<<pD->OpenPrice <<","<<pD->HighestPrice <<","<<pD->LowestPrice <<","<<pD->Volume <<","<<pD->Turnover <<","<<pD->OpenInterest <<","<<pD->ClosePrice <<","<<pD->SettlementPrice <<","<<pD->UpperLimitPrice <<","<<pD->LowerLimitPrice <<","<<pD->PreDelta <<","<<pD->CurrDelta <<","<<pD->UpdateTime <<","<<pD->UpdateMillisec <<","<<pD->BidPrice1 <<","<<pD->BidVolume1 <<","<<pD->AskPrice1 <<","<<pD->AskVolume1 <<","<<pD->BidPrice2 <<","<<pD->BidVolume2 <<","<<pD->AskPrice2 <<","<<pD->AskVolume2 <<","<<pD->BidPrice3 <<","<<pD->BidVolume3 <<","<<pD->AskPrice3 <<","<<pD->AskVolume3 <<","<<pD->BidPrice4 <<","<<pD->BidVolume4 <<","<<pD->AskPrice4 <<","<<pD->AskVolume4 <<","<<pD->BidPrice5 <<","<<pD->BidVolume5 <<","<<pD->AskPrice5 <<","<<pD->AskVolume5 <<","<<pD->AveragePrice <<","<<pD->ActionDay <<endl;
	
	}		


	CThostFtdcMdApi *m_pMdApi;
	string path;
	string BrokerID;
	string UserID;
	string Password;
	string databasename;
	MYSQL *mysql;

	char** m_contractid;
	int contract_num;
	int threadnum;
	bool ifwrite;


};

#endif
