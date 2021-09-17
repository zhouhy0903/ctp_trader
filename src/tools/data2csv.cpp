#include<iostream>
#include<string>
#include<mysql/mysql.h>
#include<time.h>
#include<sstream>
#include "common/conn_db.hpp"

using namespace std;
string get_table_name(){   
	time_t now = time(0);
   	char* dt = ctime(&now);
    now=now+8*3600;
	tm *gmtm = gmtime(&now);
	stringstream ss;
	ss<<"future"<<gmtm->tm_year+1900<<"_"<<gmtm->tm_mon+1<<"_"<<gmtm->tm_mday;
    return ss.str();
}

void get_data(string tablename){
	MYSQL *mysql=init_mysql();
    string s="SELECT * FROM "+tablename+" WHERE InstrumentID=\"IH2109\";";
    cout<<s<<endl;
	query_data(s,mysql);
	if(mysql!=NULL)  {
        mysql_close(mysql);
    }
}

int main(){
    string tablename=get_table_name();
    cout<<tablename<<endl;
    tablename="future2021_8_26_test1";
    get_data(tablename);

}