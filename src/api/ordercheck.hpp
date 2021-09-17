
#ifndef __ORDERCHECK_HPP_
#define __ORDERCHECK_HPP_

#include "ThostFtdcTraderApi.h"
#include "common/data_handler.hpp"

#include<iostream>
#include<cstring>
#include<fstream>
#include <unistd.h>
#include<vector>
#include<iconv.h>
#define Log(...) {printf(__VA_ARGS__);printf("\n");}

using namespace std;

class OrderCheck:public CThostFtdcTraderSpi{
    public:
    OrderCheck(CThostFtdcTraderApi *pTraderApi):m_pTraderApi(pTraderApi){
		vector<string> ans(4);
		ans=get_config();
		BrokerID=ans[0];
		InvestorID=ans[1];
		UserID=ans[1];
		Password=ans[2];
		slippage=atof(ans[3].c_str());
		iRequestID=0;
	}
    ~OrderCheck(){}
    
	void OnFrontConnected(){
		ReqAuthenticate();
	}

	void OnRspAuthenticate(CThostFtdcRspAuthenticateField *pRspAuthenticateField, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast){
		cout<<"RspAuthenticate!"<<endl;
		cout<<pRspInfo->ErrorID<<endl;
		login();
	}

	void OnRspUserLogin(CThostFtdcRspUserLoginField *pRspUserLogin,CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast){
		cout<<"Log In Finished!"<<endl;
		cout<<pRspInfo->ErrorID<<endl;
		cout<<pRspInfo->ErrorMsg<<endl;
    }
	

	void ReqAuthenticate(){
		CThostFtdcReqAuthenticateField req;
		memset(&req,0,sizeof(req));
		strcpy(req.BrokerID,BrokerID.c_str());
		strcpy(req.UserID,UserID.c_str());
		// strcpy(req.UserProductInfo,"zhy");
		strcpy(req.AppID,"simnow_client_test");
		strcpy(req.AuthCode,"0000000000000000");
		int ret=m_pTraderApi->ReqAuthenticate(&req,++iRequestID);
		cout<<"ReqAuenticate "<<ret<<endl;
		// cout<<"BrokerID"<<BrokerID<<"InvestorID"<<InvestorID<<"InstrumentID"<<InstrumentID<<endl;
		if (ret!=0)
			cerr<<"Authenticate Failed!"<<endl;
	}

	size_t convert(char *inbuf, size_t inlen, char *outbuf, size_t outlen){
		char **pin = &inbuf; 
		char **pout = &outbuf; 
		memset(outbuf,0,outlen);
		iconv_t cd = iconv_open("utf-8", "gbk"); 
		return iconv(cd, pin, (size_t *)&inlen, pout, (size_t *)&outlen); 
	}

	void OnRtnOrder(CThostFtdcOrderField *pOrder) {
		cout<<"OnRtnOrder"<<endl;
		char outString[200]={0};
		convert(pOrder->StatusMsg,strlen(pOrder->StatusMsg),outString,200);
		printf("%s",outString);
		printf("\n");
	};

	void login(){
		cout<<"Logging in!"<<endl;
		CThostFtdcReqUserLoginField req;
		memset(&req,0,sizeof(req));
		strcpy(req.BrokerID,BrokerID.c_str());
		strcpy(req.UserID,UserID.c_str());
		strcpy(req.Password,Password.c_str());
		int ret=m_pTraderApi->ReqUserLogin(&req,++iRequestID);
		// cout<<"BrokerID"<<BrokerID<<"InvestorID"<<InvestorID<<"InstrumentID"<<InstrumentID<<endl;
		if (ret!=0)
			cerr<<"Login Failed!"<<endl;
	}

	
    CThostFtdcTraderApi *m_pTraderApi;
    int iRequestID;
	public:
		string BrokerID;
		string InvestorID;
		string UserID;
		string InstrumentID;
		string Password;
		double slippage;
};

#endif