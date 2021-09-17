#include "ThostFtdcTraderApi.h"
#include<iostream>
#include<cstring>
#include "api/orderinsert.hpp"
#include "api/positioncheck.hpp"

using namespace std;


int main(){
    createtable_position("future","position");

	CThostFtdcTraderApi *myapi=CThostFtdcTraderApi::CreateFtdcTraderApi();
	PositionCheck mypositioncheck(myapi);
	myapi->RegisterSpi(&mypositioncheck);
	char add_char[]="tcp://218.202.237.33:10203";//tradingfront
	myapi->RegisterFront(add_char);
	myapi->Init();
	myapi->Join();
    cout<<"main end"<<endl;
}
