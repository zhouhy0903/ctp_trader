#include "ThostFtdcTraderApi.h"
#include<iostream>
#include<cstring>
#include<stdio.h>
#include<unistd.h>

#include<chrono>
#include<thread>

#include "api/orderinsert.hpp"
#include "api/positioncheck.hpp"

using namespace std;
OrderInsert openlong(CThostFtdcTraderApi *myapi,string InstrumentID,double munit){
	OrderInsert myorderinsert(myapi,InstrumentID,true,true,munit);
	return myorderinsert;
}

OrderInsert openshort(CThostFtdcTraderApi *myapi,string InstrumentID,double munit){
	OrderInsert myorderinsert(myapi,InstrumentID,false,true,munit);
	return myorderinsert;
	
}

OrderInsert closelong(CThostFtdcTraderApi *myapi,string InstrumentID,double munit){
	OrderInsert myorderinsert(myapi,InstrumentID,true,false,munit);
	return myorderinsert;
}

OrderInsert closeshort(CThostFtdcTraderApi *myapi,string InstrumentID,double munit){
	OrderInsert myorderinsert(myapi,InstrumentID,false,false,munit);
	return myorderinsert;
}

void makeorder(string instrumentid,string direction,double minimiumunit=-1){
	CThostFtdcTraderApi *myapi=CThostFtdcTraderApi::CreateFtdcTraderApi();
	OrderInsert myorderinsert=closeshort(myapi,instrumentid,minimiumunit);//need to fix
	if (direction=="openlong"){
		myorderinsert=openlong(myapi,instrumentid,minimiumunit);
	} else
	if (direction=="openshort"){
		myorderinsert=openshort(myapi,instrumentid,minimiumunit);
	} else
	if (direction=="closelong"){
		myorderinsert=closeshort(myapi,instrumentid,minimiumunit);
	} else
	if (direction=="closeshort"){
		myorderinsert=closelong(myapi,instrumentid,minimiumunit);
	}
	myapi->RegisterSpi(&myorderinsert);
	char add_char[]="tcp://218.202.237.33:10203";//tradingfront
	myapi->RegisterFront(add_char);
	myapi->Init();
	myapi->Join();
}

void check_position(){
	CThostFtdcTraderApi *myapi=CThostFtdcTraderApi::CreateFtdcTraderApi();
	PositionCheck mypositioncheck(myapi);
	myapi->RegisterSpi(&mypositioncheck);
	char add_char[]="tcp://218.202.237.33:10203";//tradingfront
	myapi->RegisterFront(add_char);
	myapi->Init();
	myapi->Join();
}

int main(){
	cout<<"main"<<endl;
	string instrumentid,direction;
	double miniumunit;
	cin>>instrumentid>>direction>>miniumunit;

	makeorder(instrumentid,direction,miniumunit);

	/*
	pid_t pid=fork();
	if (pid<0){
		cerr<<"create pid error"<<endl;
	} else if (pid==0){
		// make order


		cout<<"start making order"<<endl;
		makeorder(instrumentid,direction,miniumunit);
		cout<<"finished making order"<<endl;
		// for (int i=0;i<5;i++){
			// cout<<"test "<<i<<endl;
		// }
	} else{
		// check position
		cout<<"start checking position"<<endl;
		int count=0;
		this_thread::sleep_for(chrono::milliseconds(8000));
		check_position();
		while (1){
			// check_position();
			
			cout<<"checkposition finished"<<endl;
			count++;
			if (count>30){
				break;
			}
		}
		while (1){

		}
		// for (int i=0;i<5;i++){
			// cout<<"test son"<<i<<endl;
		// }
	}
*/


	// makeorder();
	// check_position();


	

}
