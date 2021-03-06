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
OrderInsert openlong(CThostFtdcTraderApi *myapi,string InstrumentID,int punit,double munit){
	OrderInsert myorderinsert(myapi,InstrumentID,true,true,punit,munit);
	return myorderinsert;
}

OrderInsert openshort(CThostFtdcTraderApi *myapi,string InstrumentID,int punit,double munit){
	OrderInsert myorderinsert(myapi,InstrumentID,false,true,punit,munit);
	return myorderinsert;
	
}

OrderInsert closelong(CThostFtdcTraderApi *myapi,string InstrumentID,int punit,double munit){
	OrderInsert myorderinsert(myapi,InstrumentID,true,false,punit,munit);
	return myorderinsert;
}

OrderInsert closeshort(CThostFtdcTraderApi *myapi,string InstrumentID,int punit,double munit){
	OrderInsert myorderinsert(myapi,InstrumentID,false,false,punit,munit);
	return myorderinsert;
}

void makeorder(string instrumentid,string direction,double minimiumunit=-1){
	CThostFtdcTraderApi *myapi=CThostFtdcTraderApi::CreateFtdcTraderApi();
	OrderInsert myorderinsert=closeshort(myapi,instrumentid,1,minimiumunit);//need to fix
	if (direction=="openlong"){
		myorderinsert=openlong(myapi,instrumentid,1,minimiumunit);
	} else
	if (direction=="openshort"){
		myorderinsert=openshort(myapi,instrumentid,1,minimiumunit);
	} else
	if (direction=="closelong"){
		myorderinsert=closeshort(myapi,instrumentid,1,minimiumunit);
	} else
	if (direction=="closeshort"){
		myorderinsert=closelong(myapi,instrumentid,1,minimiumunit);
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

	thread mo(makeorder,instrumentid,direction,miniumunit);
	mo.join();
	cout<<endl;
	cout<<endl;
	thread cp(check_position);
	cp.join();
	cout<<"main end"<<endl;
	/*
	pid_t pid=fork();
	if (pid<0){
		cerr<<"create pid error"<<endl;
	}
	if (pid==0){
		// make order


		cout<<"start making order"<<endl;
		makeorder(instrumentid,direction,miniumunit);

		cout<<"finished making order"<<endl;
	} else{
		// check position
		cout<<"start checking position"<<endl;
		int count=0;
		this_thread::sleep_for(chrono::milliseconds(4000));
		check_position();
		while (1){
			check_position();
			cout<<"checkposition finished"<<endl;
			count++;
			if (count>30){
				break;
			}
		}
	}
	*/

}
