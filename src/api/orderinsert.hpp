#ifndef __ORDERINSERT_HPP_
#define __ORDERINSERT_HPP_

#include "ThostFtdcTraderApi.h"
#include "common/data_handler.hpp"

#include<iostream>
#include<cstring>
#include<fstream>
#include <unistd.h>
#include<vector>
#include<pthread.h>
// #include<chrono>
// #include<thread>

using namespace std;

class OrderInsert:public CThostFtdcTraderSpi{
    public:
    OrderInsert(CThostFtdcTraderApi *pTraderApi,string InsID,bool buysell,bool openclose,int punit,double munit):m_pTraderApi(pTraderApi){
		vector<string> ans(4);
		ans=get_config();
		BrokerID=ans[0];
		InvestorID=ans[1];
		UserID=ans[1];
		Password=ans[2];
		InstrumentID=InsID;
		slippage=atof(ans[3].c_str());
		iRequestID=0;
		flag=0;
		BuySell=buysell;
		OpenClose=openclose;
		minimumunit=munit;

		if (punit==-1)
			unit=1;
		else
			unit=punit;

	}
    ~OrderInsert(){}
    
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
		// CheckPrice();
		if (minimumunit==-1)
			ReqMinimumUnit();
		else
			CheckPrice();
		// cout<<"Current Price: "<<price<<endl;
		// InsertOrder();
		// InsertOrder();
    }
	
	void OnRspOrderInsert(CThostFtdcInputOrderField *pInputOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast){
		cout<<"RspOrderInsert"<<endl;
		char ErrorMsg[20]={0};
		convert(pRspInfo->ErrorMsg,strlen(pRspInfo->ErrorMsg),ErrorMsg,20);
		cout<<pRspInfo->ErrorID<<" "<<ErrorMsg<<endl;
	}


	void OnRspQryInstrument(CThostFtdcInstrumentField *pInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
		cout<<"RspQryInstrument"<<endl;
		minimumunit=pInstrument->MinLimitOrderVolume;
		cout<<minimumunit<<endl;
		if (pRspInfo!=nullptr)
		{
		cout<<"ERROR is "<<pRspInfo->ErrorMsg<<endl;
		} else
		cout<<"nullptr"<<endl;
		CheckPrice();
	};

	void OnRspQryDepthMarketData(CThostFtdcDepthMarketDataField *pDepthMarketData, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
		cout<<"RspQryDepthMarket"<<endl;
		price=pDepthMarketData->LastPrice;
		cout<<price<<endl;

		for (int i=0;i<unit;i++)
			InsertOrder();
			
	};	

	void OnRtnTrade(CThostFtdcTradeField *pTrade) {
		cout<<"Traded!"<<endl;
		if (flag==1)
			pthread_exit(NULL);
	};
	
	// void OnErrRtnOrderInsert(CThostFtdcInputOrderField *pInputOrder, CThostFtdcRspInfoField *pRspInfo) {
	// 	cout<<"error"<<endl;
	// };
	// void OnRtnOrder(CThostFtdcOrderField *pOrder) {
	// 	cout<<"OnRtnOrder"<<endl;
	// 	char OrderStatusMsg[20]={0};
	// 	convert(pOrder->StatusMsg,strlen(pOrder->StatusMsg),OrderStatusMsg,20);
	// 	cout<<OrderStatusMsg<<endl;
	// };

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
	
	void ReqMinimumUnit(){
		cout<<"Requesting MinimiumUnit "<<InstrumentID.c_str()<<endl;
		CThostFtdcQryInstrumentField req;
		memset(&req,0,sizeof(req));
		strcpy(req.InstrumentID,InstrumentID.c_str());
		int ret=m_pTraderApi->ReqQryInstrument(&req,++iRequestID);
		// if (ret!=0)
			// cerr<<"Get Minimum Unit Failed!"<<endl;
	}

	void CheckPrice(){
		sleep(1);
		cout<<"Checking Price "<<InstrumentID.c_str()<<endl;
		CThostFtdcQryDepthMarketDataField req;
		memset(&req,0,sizeof(req));
		strcpy(req.InstrumentID,InstrumentID.c_str());
		int ret=m_pTraderApi->ReqQryDepthMarketData(&req,++iRequestID);
		cout<<ret<<endl;
		if (ret!=0)
			cerr<<"QryInstrument Failed!"<<endl;
	}


	void InsertOrder(){
		sleep(2);
		// cout<<"Inserting Order"<<endl;
		CThostFtdcInputOrderField ord;
		// cout<<"BrokerID"<<BrokerID<<"InvestorID"<<InvestorID<<"InstrumentID"<<InstrumentID<<endl;
		memset(&ord,0,sizeof(ord));
		strcpy(ord.BrokerID,BrokerID.c_str());
		strcpy(ord.InvestorID,InvestorID.c_str());
		strcpy(ord.InstrumentID,InstrumentID.c_str());
		strcpy(ord.OrderRef,"");
		if (BuySell==true)
			ord.Direction = THOST_FTDC_D_Buy; 
		else
			ord.Direction = THOST_FTDC_D_Sell;

		if (OpenClose==true){
			// cout<<"open"<<endl;
			ord.CombOffsetFlag[0] = THOST_FTDC_OF_Open;
		}
		else
		{
			// cout<<"close"<<endl;
			ord.CombOffsetFlag[0] = THOST_FTDC_OF_CloseToday;

		}
		ord.CombHedgeFlag[0] = THOST_FTDC_HF_Speculation;
		ord.VolumeTotalOriginal = 1;
		ord.ContingentCondition = THOST_FTDC_CC_Immediately;
		ord.VolumeCondition = THOST_FTDC_VC_AV;
		ord.MinVolume = 1;
		ord.ForceCloseReason = THOST_FTDC_FCC_NotForceClose;
		ord.IsAutoSuspend = 0;
		ord.UserForceClose = 0;

		ord.OrderPriceType = THOST_FTDC_OPT_LimitPrice;
		if (BuySell==true)
			ord.LimitPrice = price+slippage*minimumunit;
		else
			ord.LimitPrice = price-slippage*minimumunit;
		cout<<"price is "<<ord.LimitPrice<<" "<<price<<" "<<slippage*minimumunit<<endl;
		
		ord.TimeCondition = THOST_FTDC_TC_GFD; //当日有效hbg

		int ret=m_pTraderApi->ReqOrderInsert(&ord,++iRequestID);
		if (ret!=0)
			cerr<<"OrderInsert Failed"<<endl;
		cout<<"insertorder func end"<<endl;	
		flag=1;
		// this_thread::sleep_for(chrono::milliseconds(3000));
		// pthread_exit(NULL);
	}
    CThostFtdcTraderApi *m_pTraderApi;
    int iRequestID;
	public:
		string BrokerID;
		string InvestorID;
		string UserID;
		string InstrumentID;
		string Password;
		bool BuySell;//Buy is True,Sell is False
		bool OpenClose;//Open is True,Close is False
		double price;
		double slippage;
		double minimumunit;

		int flag;
		int unit;
};

#endif