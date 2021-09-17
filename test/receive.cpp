
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include<iostream>
#include<fstream>
#include<mysql/mysql.h>


using namespace std;
#define DEST_PORT 8000
#define DSET_IP_ADDRESS  "127.0.0.1"

MYSQL* init_mysql(){
	MYSQL  *mysql;
	mysql=mysql_init(NULL);
	if (mysql==NULL){
		cout<<"Init Mysql Error!"<<endl;
		exit(1);
	}
	string host="localhost";
	string user="root";
	string password="mysql990903";
	string db_name="future";
	
	mysql=mysql_real_connect(mysql,host.c_str(),user.c_str(),password.c_str(),db_name.c_str(),0,NULL,0);
	if (mysql==NULL){
		cout<<"Connect Mysql Error!"<<endl;
		exit(1);
	}
	return mysql;
}

void insert_data(string s,MYSQL *mysql){
	 if (mysql_query(mysql,s.c_str())){
        cout<<"Query Error: "<<mysql_error(mysql);
    }
    else{
        MYSQL_RES * result = mysql_store_result(mysql);  //获取结果集
		cout<<"Successful!"<<endl;
	}
}

int main()
{

//"TradingDay","InstrumentID","ExchangeID","ExchangeInstID","LastPrice","PreSettlementPrice","PreClosePrice","PreOpenInterest","OpenPrice","HighestPrice","LowestPrice","Volume","Turn    over","OpenInterest","ClosePrice","SettlementPrice","UpperLimitPrice","LowerLimitPrice","PreDelta","CurrDelta","UpdateTime","UpdateMillisec","BidPrice1","BidVolume1","AskPrice1","AskVolume1","Bi    dPrice2","BidVolume2","AskPrice2","AskVolume2","BidPrice3","BidVolume3","AskPrice3","AskVolume3","BidPrice4","BidVolume4","AskPrice4","AskVolume4","BidPrice5","BidVolume5","AskPrice5","AskVolume5","AveragePrice","ActionDay"

	string s="CREATE TABLE IF NOT EXISTS `future1`(\
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
	MYSQL *mysql=init_mysql();
	insert_data(s,mysql);
	if(mysql!=NULL)  {
        mysql_close(mysql);
    }

/*
  int sock_fd;
  sock_fd = socket(AF_INET, SOCK_DGRAM, 0);
  if(sock_fd < 0)
  {
    perror("socket");
    exit(1);
  }

	struct sockaddr_in addr_serv;
	int len;
	memset(&addr_serv, 0, sizeof(addr_serv));
	addr_serv.sin_family = AF_INET;
	addr_serv.sin_addr.s_addr = inet_addr(DSET_IP_ADDRESS);
	addr_serv.sin_port = htons(DEST_PORT);
	len = sizeof(addr_serv);
	int send_num;
	int recv_num;
	char send_buf[20]="test";
	char recv_buf[400];
	cout<<"waiting for reply"<<endl;
	send_num = sendto(sock_fd, send_buf, strlen(send_buf), 0, (struct sockaddr *)&addr_serv, len);
	if(send_num < 0)
  	{
   		perror("sendto error:");
    	exit(1);
  	}
ofstream ofile;
while (1){
	recv_num = recvfrom(sock_fd, recv_buf, sizeof(recv_buf), 0, (struct sockaddr *)&addr_serv, (socklen_t *)&len);
	if(recv_num < 0)
	{
	perror("recvfrom error:");
	exit(1);
	}
	recv_buf[recv_num] = '\0';

	//输入到文件
	ofile.open("test.txt",ios::app|ios::out);
	ofile<<recv_buf<<endl;
	cout<<recv_buf<<endl;
	ofile.close();
}
  close(sock_fd);
*/


  return 0;
}