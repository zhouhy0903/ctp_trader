#ifndef __CONN_DB_HPP_
#define __CONN_DB_HPP_
#include<mysql/mysql.h>
#include<string>
#include<iostream>
#include<vector>

using namespace std;

MYSQL* init_mysql(string dbname="future"){
	MYSQL  *mysql;
	mysql=mysql_init(NULL);
	if (mysql==NULL){
		cout<<"Init Mysql Error!"<<endl;
		exit(1);
	}
	string host="localhost";
	string user="root";
	string password="mysql990903";
	string db_name=dbname;
	
	mysql=mysql_real_connect(mysql,host.c_str(),user.c_str(),password.c_str(),db_name.c_str(),0,NULL,0);
	if (mysql==NULL){
		cout<<"Connect Mysql Error!"<<endl;
		exit(1);
	}
	return mysql;
}

void insert_data(string s,MYSQL *mysql,string info=""){
	 if (mysql_query(mysql,s.c_str())){
        cout<<"Query Error: "<<mysql_error(mysql)<<" "<<info<<endl;
    }
    else {
        MYSQL_RES * result = mysql_store_result(mysql);  //获取结果集
		cout<<"Successful! "<<info<<endl;
	}
}

//要修改成返回string
void query_data(string s,MYSQL *mysql){
	 if (mysql_query(mysql,s.c_str())){
        cout<<"Query Error: "<<mysql_error(mysql)<<endl;
    }
    else {
		MYSQL_RES *result = mysql_use_result(mysql); // 获取结果集
        // mysql_field_count()返回connection查询的列数
        for(int i=0; i < mysql_field_count(mysql); ++i)
        {
            // 获取下一行
            MYSQL_ROW row = mysql_fetch_row(result);
            if(row <= 0)
            {
                break;
            }
            // mysql_num_fields()返回结果集中的字段数
            for(int j=0; j < mysql_num_fields(result); ++j)
            {
				std::cout << row[j] << " ";
            }
			std::cout << endl;
        }
		std::cout << endl;
        // 释放结果集的内存
        mysql_free_result(result);
	}
}

void createdatabase(string dbname){
	// string s="CREATE DATABASE "+dbname+";";
	string s="CREATE DATABASE IF NOT EXISTS `"+dbname+"`;";
	MYSQL *mysql=init_mysql();
	insert_data(s,mysql);
	if(mysql!=NULL)  {
        mysql_close(mysql);
    }
}

void createtable(string dbname,string tbname){
	string s="CREATE TABLE IF NOT EXISTS `"+tbname+"`(\
   `TradingDay` VARCHAR(8),\
   `InstrumentID` VARCHAR(13),\
   `ExchangeID` VARCHAR(10),\
   `ExchangeInstID` VARCHAR(10),\
   `LastPrice` FLOAT,\
   `PreSettlementPrice` FLOAT,\
   `PreClosePrice` FLOAT,\
   `PreOpenInterest` FLOAT,\
   `OpenPrice` FLOAT,\
   `HighestPrice` FLOAT,\
   `LowestPrice` FLOAT,\
   `Volume` FLOAT,\
   `Turnover` FLOAT,\
   `OpenInterest` FLOAT,\
   `ClosePrice` FLOAT,\
   `SettlementPrice` FLOAT,\
   `UpperLimitPrice` FLOAT,\
   `LowerLimitPrice` FLOAT,\
   `PreDelta` FLOAT,\
   `CurrDelta` FLOAT,\
   `UpdateTime` VARCHAR(9),\
   `UpdateMillisec` FLOAT,\
   `BidPrice1` FLOAT,\
   `BidVolume1` INT,\
   `AskPrice1` FLOAT,\
   `AskVolume1` INT,\
   `BidPrice2` FLOAT,\
   `BidVolume2` INT,\
   `AskPrice2` FLOAT,\
   `AskVolume2` INT,\
   `BidPrice3` FLOAT,\
   `BidVolume3` INT,\
   `AskPrice3` FLOAT,\
   `AskVolume3` INT,\
   `BidPrice4` FLOAT,\
   `BidVolume4` INT,\
   `AskPrice4` FLOAT,\
   `AskVolume4` INT,\
   `BidPrice5` FLOAT,\
   `BidVolume5` INT,\
   `AskPrice5` FLOAT,\
   `AskVolume5` INT,\
   `AveragePrice` FLOAT,\
   `ActionDay` VARCHAR(9),\
   PRIMARY KEY (`TradingDay`,`InstrumentID`,`UpdateTime`,`UpdateMillisec`)\
)""";	
	MYSQL *mysql=init_mysql(dbname);
	insert_data(s,mysql);
	if(mysql!=NULL)  {
        mysql_close(mysql);
    }
}

void createtable_position(string dbname,string tbname){
	string s="CREATE TABLE IF NOT EXISTS `"+tbname+"`(\
   `Time` VARCHAR(20),\
   `InstrumentID` VARCHAR(13),\
   `BrokerID` VARCHAR(13),\
   `InvestorID` VARCHAR(13),\
   `PosiDirection` VARCHAR(3),\
   `HedgeFlag` VARCHAR(3),\
   `PositionDate` VARCHAR(3),\
   `YdPosition` INT,\
   `Position` INT,\
   `LongFrozen` INT,\
   `ShortFrozen` INT,\
   `LongFrozenAmount` DOUBLE,\
   `ShortFrozenAmount` DOUBLE,\
   `OpenVolume` INT,\
   `CloseVolume` INT,\
   `OpenAmount` DOUBLE,\
   `CloseAmount` DOUBLE,\
   `PositionCost` DOUBLE,\
   `PreMargin` DOUBLE,\
   `UseMargin` DOUBLE,\
   `FrozenMargin` DOUBLE,\
   `FrozenCash` DOUBLE,\
   `FrozenCommission` DOUBLE,\
   `CashIn` DOUBLE,\
   `Commission` DOUBLE,\
   `CloseProfit` DOUBLE,\
   `PositionProfit` DOUBLE,\
   `PreSettlementPrice` DOUBLE,\
   `SettlementPrice` DOUBLE,\
   `TradingDay` VARCHAR(10),\
   `SettlementID` INT,\
   `OpenCost` DOUBLE,\
   `ExchangeMargin` DOUBLE,\
   `CombPosition` INT,\
   `CombLongFrozen` INT,\
   `CombShortFrozen` INT,\
   `CloseProfitByDate` DOUBLE,\
   `CloseProfitByTrade` DOUBLE,\
   `TodayPosition` INT,\
   `MarginRateByMoney` DOUBLE,\
   `MarginRateByVolume` DOUBLE,\
   `StrikeFrozen` INT,\
   `StrikeFrozenAmount` DOUBLE,\
   `AbandonFrozen` INT,\
   `ExchangeID` VARCHAR(10),\
   `YdStrikeFrozen` INT,\
   `InvestUnitID` VARCHAR(20),\
   `PositionCostOffset` DOUBLE,\
   `TasPosition` INT,\
   `TasPositionCost` DOUBLE,\
   PRIMARY KEY(`Time`,`InstrumentID`))""";	
//    PRIMARY KEY (`TradingDay`,`InstrumentID`,`UpdateTime`,`UpdateMillisec`)
	MYSQL *mysql=init_mysql(dbname);
	insert_data(s,mysql);
	if(mysql!=NULL)  {
        mysql_close(mysql);
    }
}

#endif