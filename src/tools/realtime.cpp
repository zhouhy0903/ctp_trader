#include "ThostFtdcMdApi.h"

#include<iostream>
#include<cstring>
#include<fstream>
#include "api/marketdata.hpp"
#include "subscribe.cpp"
#include<vector>
#include<cstring>

using namespace std;

int main(){
	//string p="/media/zhou/3d3bcba8-4222-49a4-92ae-8d53e869e4ed/data/future/contractid.csv";
	string p="/media/zhou/3d3bcba8-4222-49a4-92ae-8d53e869e4ed/data/future/contract_id_select.csv";
	vector<string> contractid;
	int n;
	cin>>n;
	for (int i=0;i<n;i++){
		string s;
		cin>>s;
		contractid.push_back(s);
	}

	for (int i=0;i<n;i++){
		cout<<contractid[i]<<endl;
	}

	subscribe(contractid,0,false);
	while (1)
	{
	}
}
