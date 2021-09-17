#include "ThostFtdcTraderApi.h"
#include<iostream>
#include<cstring>
#include<fstream>
#include<vector>
#include "common/data_handler.hpp"
using namespace std;

class ContractId:public CThostFtdcTraderSpi{
	public:
	ContractId(CThostFtdcTraderApi *pTraderApi,string path):m_pTraderApi(pTraderApi),path(path){
		iRequestID=0;
		vector<string> ans(4);
		ans=get_config();
		BrokerID=ans[0];
		UserID=ans[1];
		Password=ans[2];
	}
	~ContractId(){}

	void OnFrontConnected(){
		ReqAuthenticate();
	}

	void OnRspAuthenticate(CThostFtdcRspAuthenticateField *pRspAuthenticateField, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast){
		login();
	}

	void OnRspUserLogin(CThostFtdcRspUserLoginField *pRspUserLogin,CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast){
		cout<<"Log In Finished!"<<endl;
		cout<<pRspInfo->ErrorID<<endl;
		cout<<pRspInfo->ErrorMsg<<endl;
		ReqQryInstrument();
	}
	
	void OnRspQryInstrument(CThostFtdcInstrumentField *pInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID,bool bIsLast){
		ofstream ofile;
		// cout<<path+"contract.txt"<<endl;
		ofile.open(path+"contract.csv",ios::app|ios::out);
		char InstrumentName[20]={0};
		convert(pInstrument->InstrumentName,strlen(pInstrument->InstrumentName),InstrumentName,20);
		//ofile<<pInstrument->InstrumentID <<","<<pInstrument->ExchangeID <<","<<InstrumentName <<","<<pInstrument->ExchangeInstID <<","<<pInstrument->ProductID <<","<<pInstrument->ProductClass <<","<<pInstrument->DeliveryYear <<","<<pInstrument->DeliveryMonth <<","<<pInstrument->MaxMarketOrderVolume <<","<<pInstrument->MinMarketOrderVolume <<","<<pInstrument->MaxLimitOrderVolume <<","<<pInstrument->MinLimitOrderVolume <<","<<pInstrument->VolumeMultiple <<","<<pInstrument->PriceTick <<","<<pInstrument->CreateDate <<","<<pInstrument->OpenDate <<","<<pInstrument->ExpireDate <<","<<pInstrument->StartDelivDate <<","<<pInstrument->EndDelivDate <<","<<pInstrument->InstLifePhase <<","<<pInstrument->IsTrading <<","<<pInstrument->PositionType <<","<<pInstrument->PositionDateType <<","<<pInstrument->LongMarginRatio <<","<<pInstrument->ShortMarginRatio <<","<<pInstrument->MaxMarginSideAlgorithm <<","<<pInstrument->UnderlyingInstrID <<","<<pInstrument->StrikePrice <<","<<pInstrument->OptionsType <<","<<pInstrument->UnderlyingMultiple <<","<<pInstrument->CombinationType<<endl;
		//cout<<pInstrument->InstrumentID <<","<<pInstrument->ExchangeID <<","<<InstrumentName <<","<<pInstrument->ExchangeInstID <<","<<pInstrument->ProductID <<","<<pInstrument->ProductClass <<","<<pInstrument->DeliveryYear <<","<<pInstrument->DeliveryMonth <<","<<pInstrument->MaxMarketOrderVolume <<","<<pInstrument->MinMarketOrderVolume <<","<<pInstrument->MaxLimitOrderVolume <<","<<pInstrument->MinLimitOrderVolume <<","<<pInstrument->VolumeMultiple <<","<<pInstrument->PriceTick <<","<<pInstrument->CreateDate <<","<<pInstrument->OpenDate <<","<<pInstrument->ExpireDate <<","<<pInstrument->StartDelivDate <<","<<pInstrument->EndDelivDate <<","<<pInstrument->InstLifePhase <<","<<pInstrument->IsTrading <<","<<pInstrument->PositionType <<","<<pInstrument->PositionDateType <<","<<pInstrument->LongMarginRatio <<","<<pInstrument->ShortMarginRatio <<","<<pInstrument->MaxMarginSideAlgorithm <<","<<pInstrument->UnderlyingInstrID <<","<<pInstrument->StrikePrice <<","<<pInstrument->OptionsType <<","<<pInstrument->UnderlyingMultiple <<","<<pInstrument->CombinationType<<endl;
		ofile<<pInstrument->InstrumentID<<","<<InstrumentName<<","<<pInstrument->IsTrading<<endl;
		ofile.close();
	}
	void OnRspSettlementInfoConfirm(CThostFtdcSettlementInfoConfirmField *pSettlementInfoConfirm, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast){
		cout<<"RspSettlemnet"<<endl;
	}
	void ReqAuthenticate(){
		CThostFtdcReqAuthenticateField req;
		memset(&req,0,sizeof(req));
		strcpy(req.BrokerID,BrokerID.c_str());
		strcpy(req.UserID,UserID.c_str());
		strcpy(req.AppID,"simnow_client_test");
		strcpy(req.AuthCode,"0000000000000000");
		int ret=m_pTraderApi->ReqAuthenticate(&req,++iRequestID);
		cout<<"ReqAuenticate "<<ret<<endl;
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
		if (ret!=0)
			cerr<<"Login Failed!"<<endl;
		// ReqQryInstrument();
	}

	void ReqQryInstrument(){
		cout<<"ReqQryInstrument"<<endl;
		CThostFtdcQryInstrumentField req;
		memset(&req,0,sizeof(req));
		int ret=m_pTraderApi->ReqQryInstrument(&req,++iRequestID);
		cout<<"ret"<<ret<<endl;
		if (ret!=0)
			cerr<<"Request Instrument Failed!"<<endl;
	}


	CThostFtdcTraderApi *m_pTraderApi;
	string BrokerID;
	string UserID;
	string Password;
	string path;
	int iRequestID;
};


int main(){
	CThostFtdcTraderApi *myapi=CThostFtdcTraderApi::CreateFtdcTraderApi();
	ContractId contractid(myapi,"/media/zhou/3d3bcba8-4222-49a4-92ae-8d53e869e4ed/data/future/");
	myapi->RegisterSpi(&contractid);
	char add_char[]="tcp://180.168.146.187:10202";//实盘
	// char add_char[]="tcp://180.168.146.187:10130";//仿真
	myapi->RegisterFront(add_char);
	myapi->SubscribePrivateTopic(THOST_TERT_QUICK);
	myapi->SubscribePublicTopic(THOST_TERT_QUICK);
	myapi->Init();
	myapi->Join();
	while (1){

	}
}