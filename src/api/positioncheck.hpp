#ifndef __POSITIONCHECK_HPP_
#define __POSITIONCHECK_HPP_

#include "ThostFtdcTraderApi.h"
#include<iostream>
#include<cstring>
#include<fstream>
#include<vector>
#include<mysql/mysql.h>
#include<sstream>
#include<time.h>
#include<pthread.h>


#include "common/data_handler.hpp"
#include "common/conn_db.hpp"

using namespace std;

class PositionCheck:public CThostFtdcTraderSpi{
    public:
    PositionCheck(CThostFtdcTraderApi *pTraderApi):m_pTraderApi(pTraderApi){
		vector<string> ans(4);
		ans=get_config();
		BrokerID=ans[0];
		InvestorID=ans[1];
		UserID=ans[1];
		Password=ans[2];
		mysql=init_mysql("future");

	}
    ~PositionCheck(){}
    
	void OnFrontConnected(){
		ReqAuthenticate();
	}

	void OnRspAuthenticate(CThostFtdcRspAuthenticateField *pRspAuthenticateField, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast){
		login();
	}

	void OnRspUserLogin(CThostFtdcRspUserLoginField *pRspUserLogin,CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast){
		cout<<"Log In Finished!"<<endl;
		ReqSettlementInfoConfirm();
	}
	
	void OnRspSettlementInfoConfirm(CThostFtdcSettlementInfoConfirmField *pSettlementInfoConfirm, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast){
		checkposition();
	}
	
	void OnRspQryInvestorPosition(CThostFtdcInvestorPositionField *pIP, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast){
		cout<<"Rsp On Checking Position "<<bIsLast<<endl;
		if (pRspInfo!=NULL)
			cout<<pRspInfo->ErrorID<<endl;
		if (pIP!=NULL)
		{
			time_t now = time(0);
			char* dt = ctime(&now);
			now=now+8*3600;
			tm *gmtm = gmtime(&now);
			stringstream ss;
			ss<<gmtm->tm_year+1900;
			if (gmtm->tm_mon+1<10) ss<<"0";
			ss<<gmtm->tm_mon+1;
			if (gmtm->tm_mday<10) ss<<"0";
			ss<<gmtm->tm_mday<<"_";
			if (gmtm->tm_hour<10) ss<<"0";
			ss<<gmtm->tm_hour<<":";
			if (gmtm->tm_min<10) ss<<"0";
			ss<<gmtm->tm_min<<":";
			if (gmtm->tm_sec<10) ss<<"0";
			ss<<gmtm->tm_sec;
			
			
			stringstream values;
			values<<"'"<<ss.str()<<"','"<<pIP->InstrumentID <<"','"<<pIP->BrokerID <<"','"<<pIP->InvestorID <<"','"<<pIP->PosiDirection <<"','"<<pIP->HedgeFlag <<"','"<<pIP->PositionDate <<"','"<<pIP->YdPosition <<"','"<<pIP->Position <<"','"<<pIP->LongFrozen <<"','"<<pIP->ShortFrozen <<"','"<<pIP->LongFrozenAmount <<"','"<<pIP->ShortFrozenAmount <<"','"<<pIP->OpenVolume <<"','"<<pIP->CloseVolume <<"','"<<pIP->OpenAmount <<"','"<<pIP->CloseAmount <<"','"<<pIP->PositionCost <<"','"<<pIP->PreMargin <<"','"<<pIP->UseMargin <<"','"<<pIP->FrozenMargin <<"','"<<pIP->FrozenCash <<"','"<<pIP->FrozenCommission <<"','"<<pIP->CashIn <<"','"<<pIP->Commission <<"','"<<pIP->CloseProfit <<"','"<<pIP->PositionProfit <<"','"<<pIP->PreSettlementPrice <<"','"<<pIP->SettlementPrice <<"','"<<pIP->TradingDay <<"','"<<pIP->SettlementID <<"','"<<pIP->OpenCost <<"','"<<pIP->ExchangeMargin <<"','"<<pIP->CombPosition <<"','"<<pIP->CombLongFrozen <<"','"<<pIP->CombShortFrozen <<"','"<<pIP->CloseProfitByDate <<"','"<<pIP->CloseProfitByTrade <<"','"<<pIP->TodayPosition <<"','"<<pIP->MarginRateByMoney <<"','"<<pIP->MarginRateByVolume <<"','"<<pIP->StrikeFrozen <<"','"<<pIP->StrikeFrozenAmount <<"','"<<pIP->AbandonFrozen <<"','"<<pIP->ExchangeID <<"','"<<pIP->YdStrikeFrozen <<"','"<<pIP->InvestUnitID <<"','"<<pIP->PositionCostOffset <<"','"<<pIP->TasPosition <<"','"<<pIP->TasPositionCost <<"'";
			string s="INSERT INTO `position` (`Time`,`InstrumentID`,`BrokerID`,`InvestorID`,`PosiDirection`,`HedgeFlag`,`PositionDate`,`YdPosition`,`Position`,`LongFrozen`,`ShortFrozen`,`LongFrozenAmount`,`ShortFrozenAmount`,`OpenVolume`,`CloseVolume`,`OpenAmount`,`CloseAmount`,`PositionCost`,`PreMargin`,`UseMargin`,`FrozenMargin`,`FrozenCash`,`FrozenCommission`,`CashIn`,`Commission`,`CloseProfit`,`PositionProfit`,`PreSettlementPrice`,`SettlementPrice`,`TradingDay`,`SettlementID`,`OpenCost`,`ExchangeMargin`,`CombPosition`,`CombLongFrozen`,`CombShortFrozen`,`CloseProfitByDate`,`CloseProfitByTrade`,`TodayPosition`,`MarginRateByMoney`,`MarginRateByVolume`,`StrikeFrozen`,`StrikeFrozenAmount`,`AbandonFrozen`,`ExchangeID`,`YdStrikeFrozen`,`InvestUnitID`,`PositionCostOffset`,`TasPosition`,`TasPositionCost`) VALUES(";
			s=s+values.str()+");";
			//cout<<s<<endl;
			insert_data(s,mysql,"Nothing!");
			cout<<"after insert into mysql"<<endl;
			string positionDir="NULL";
			if (pIP->PosiDirection=='2')
				positionDir="long";
			else if(pIP->PosiDirection=='3')
				positionDir="short";

			cout<<pIP->InstrumentID<<" "<<pIP->Position<<" "<<positionDir<<endl;
			// cout<<"InstrumentID:" <<pInvestorPosition->InstrumentID <<","<<"BrokerID:" <<pInvestorPosition->BrokerID <<","<<"InvestorID:" <<pInvestorPosition->InvestorID <<","<<"PosiDirection:" <<pInvestorPosition->PosiDirection <<","<<"HedgeFlag:" <<pInvestorPosition->HedgeFlag <<","<<"PositionDate:" <<pInvestorPosition->PositionDate <<","<<"YdPosition:" <<pInvestorPosition->YdPosition <<","<<"Position:" <<pInvestorPosition->Position <<","<<"LongFrozen:" <<pInvestorPosition->LongFrozen <<","<<"ShortFrozen:" <<pInvestorPosition->ShortFrozen <<","<<"LongFrozenAmount:" <<pInvestorPosition->LongFrozenAmount <<","<<"ShortFrozenAmount:" <<pInvestorPosition->ShortFrozenAmount <<","<<"OpenVolume:" <<pInvestorPosition->OpenVolume <<","<<"CloseVolume:" <<pInvestorPosition->CloseVolume <<","<<"OpenAmount:" <<pInvestorPosition->OpenAmount <<","<<"CloseAmount:" <<pInvestorPosition->CloseAmount <<","<<"PositionCost:" <<pInvestorPosition->PositionCost <<","<<"PreMargin:" <<pInvestorPosition->PreMargin <<","<<"UseMargin:" <<pInvestorPosition->UseMargin <<","<<"FrozenMargin:" <<pInvestorPosition->FrozenMargin <<","<<"FrozenCash:" <<pInvestorPosition->FrozenCash <<","<<"FrozenCommission:" <<pInvestorPosition->FrozenCommission <<","<<"CashIn:" <<pInvestorPosition->CashIn <<","<<"Commission:" <<pInvestorPosition->Commission <<","<<"CloseProfit:" <<pInvestorPosition->CloseProfit <<","<<"PositionProfit:" <<pInvestorPosition->PositionProfit <<","<<"PreSettlementPrice:" <<pInvestorPosition->PreSettlementPrice <<","<<"SettlementPrice:" <<pInvestorPosition->SettlementPrice <<","<<"TradingDay:" <<pInvestorPosition->TradingDay <<","<<"SettlementID:" <<pInvestorPosition->SettlementID <<","<<"OpenCost:" <<pInvestorPosition->OpenCost <<","<<"ExchangeMargin:" <<pInvestorPosition->ExchangeMargin <<","<<"CombPosition:" <<pInvestorPosition->CombPosition <<","<<"CombLongFrozen:" <<pInvestorPosition->CombLongFrozen <<","<<"CombShortFrozen:" <<pInvestorPosition->CombShortFrozen <<","<<"CloseProfitByDate:" <<pInvestorPosition->CloseProfitByDate <<","<<"CloseProfitByTrade:" <<pInvestorPosition->CloseProfitByTrade <<","<<"TodayPosition:" <<pInvestorPosition->TodayPosition <<","<<"MarginRateByMoney:" <<pInvestorPosition->MarginRateByMoney <<","<<"MarginRateByVolume:" <<pInvestorPosition->MarginRateByVolume <<","<<"StrikeFrozen:" <<pInvestorPosition->StrikeFrozen <<","<<"StrikeFrozenAmount:" <<pInvestorPosition->StrikeFrozenAmount <<","<<"AbandonFrozen:" <<pInvestorPosition->AbandonFrozen <<","<<"ExchangeID:" <<pInvestorPosition->ExchangeID <<","<<"YdStrikeFrozen:" <<pInvestorPosition->YdStrikeFrozen <<","<<"InvestUnitID:" <<pInvestorPosition->InvestUnitID <<","<<"PositionCostOffset:" <<pInvestorPosition->PositionCostOffset <<","<<"TasPosition:" <<pInvestorPosition->TasPosition <<","<<"TasPositionCost:" <<pInvestorPosition->TasPositionCost<<endl;

		}
		else
			cout<<"pInvestorPosition null!"<<endl;
		
		//最后一条数据退出线程
		if (bIsLast==true)
		{
			pthread_exit(NULL);
		}
		// if (bIsLast==true)
			//exit(1);
		// if (bIsLast==1)
		// {
		// 	cout<<"log out!"<<endl;
		// 	CThostFtdcUserLogoutField req;
		// 	memset(&req,0,sizeof(req));
		// 	strcpy(req.BrokerID,BrokerID.c_str());
		// 	strcpy(req.UserID,UserID.c_str());
		// 	m_pTraderApi->ReqUserLogout(&req,++iRequestID);
		// }
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
	}
	
	void ReqSettlementInfoConfirm(){
		CThostFtdcSettlementInfoConfirmField req;
		memset(&req, 0, sizeof(req));
		strcpy(req.BrokerID, BrokerID.c_str());
		strcpy(req.InvestorID, InvestorID.c_str());
		int iResult = m_pTraderApi->ReqSettlementInfoConfirm(&req, ++iRequestID);
		cerr << "--->>> 投资者结算结果确认: " << ((iResult == 0) ? "成功" : "失败") << endl;
		
	}

	void checkposition(){
		CThostFtdcQryInvestorPositionField req;
		memset(&req,0,sizeof(req));
		strcpy(req.BrokerID,BrokerID.c_str());
		strcpy(req.InvestorID,InvestorID.c_str());

		int ret=m_pTraderApi->ReqQryInvestorPosition(&req,++iRequestID);
		if (ret!=0)
		  cerr<<"Check Position Failed"<<endl;
	}
    
	CThostFtdcTraderApi *m_pTraderApi;
    int iRequestID;
	vector<string> position;
	private:
		string BrokerID;
		string InvestorID;
		string UserID;
		string Password;

		MYSQL *mysql;
};

#endif