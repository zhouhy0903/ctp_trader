#include "api/orderinsert.hpp"
#include "ThostFtdcTraderApi.h"
#include "api/ordercheck.hpp"
#include<iostream>
#include<cstring>

using namespace std;

int main(){
	CThostFtdcTraderApi *myapi=CThostFtdcTraderApi::CreateFtdcTraderApi();
	OrderCheck myorderinsert=OrderCheck(myapi);

	myapi->RegisterSpi(&myorderinsert);
	char add_char[]="tcp://218.202.237.33:10203";//tradingfront
	myapi->RegisterFront(add_char);
	myapi->Init();
	myapi->Join();
	cout<<"finished"<<endl;
}
