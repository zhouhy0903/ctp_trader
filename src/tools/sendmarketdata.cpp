#include<iostream>
#include<fstream>
#include<unistd.h>
#include<thread>
#include<chrono>
#include<regex>
#include<cassert>
#include<unordered_map>
#include<string>

#include<queue>
#include<sys/socket.h>
#include<netinet/in.h>
#include<sys/types.h>
using namespace std;

#define SERV_PORT 8000

vector<int> get_time(string line){
	regex time_reg("(.{2}):(.{2}):(.{2}),(.*?),");
	smatch mResult;
	vector<int> time;
	if (regex_search(line,mResult,time_reg)){
		assert(mResult.size()==5);
		int hour,minute,second,millis;
		time.push_back(atoi(mResult[1].str().c_str()));
		time.push_back(atoi(mResult[2].str().c_str()));
		time.push_back(atoi(mResult[3].str().c_str()));
		time.push_back(atoi(mResult[4].str().c_str()));
		// cout<<hour<<":"<<minute<<":"<<second<<":"<<millis<<endl;	
	}
	return time;
}


void read_data(string path){
	ifstream infile(path,ios::in);
	if (!infile){
		cout<<"Reading File Error!"<<endl;
		exit(1);
	}
	string line;
	string field;
	int count=0;
	unordered_map<string,string> umap;
	queue<string> myqueue;
	//init socket
	int sock_fd=socket(AF_INET,SOCK_DGRAM,0);
	if(sock_fd < 0)
  	{
    	perror("socket");
    	exit(1);
  	}
	struct sockaddr_in addr_serv;
	memset(&addr_serv,0,sizeof(struct sockaddr_in));
	addr_serv.sin_family=AF_INET;
	addr_serv.sin_port=htons(SERV_PORT);
	addr_serv.sin_addr.s_addr=htonl(INADDR_ANY);
  	int len = sizeof(addr_serv);
	bind(sock_fd,(struct sockaddr *)&addr_serv,sizeof(addr_serv));

	struct sockaddr_in addr_client;
	int recv_num;
  	char recv_buf[20];
	recv_num = recvfrom(sock_fd, recv_buf, sizeof(recv_buf), 0, (struct sockaddr *)&addr_client, (socklen_t *)&len);
    if(recv_num < 0)
    {
      perror("recvfrom error:");
      exit(1);
    }
	int curtime=0;
	int lastcurtime=0;

	while (getline(infile,line)){
			
		
		vector<int> time=get_time(line);
		int times=(time[0]*3600+time[1]*60+time[2])*2+time[3]/500;

		regex instrumentid("\\d*,(.*?),");
		string nameid;
		smatch mResult;
		vector<int> lasttime;
		int flag=0;

		if (regex_search(line,mResult,instrumentid)){
			assert(mResult.size()==2);
			nameid=mResult[1].str();
		}
		
			
		if (umap.find(nameid) == umap.end()){
			if (nameid=="IH2112" || nameid=="IF2112")
				myqueue.push(line);
				if (times>curtime){
					curtime=times;
				}
		} else{
				if (nameid=="IH2112" || nameid=="IF2112"){		
					if (times-lastcurtime<=1){
						myqueue.push(line);
					} else{
						//已经出现下一时刻的数据
						this_thread::sleep_for(std::chrono::milliseconds(500));	
						while (myqueue.size()>0){
							char send_buf[400];
							strcpy(send_buf,myqueue.front().c_str());
							myqueue.pop();
							int send_num=sendto(sock_fd,send_buf,sizeof(send_buf),0,(struct sockaddr *)&addr_client,len);
								cout<<send_buf<<endl;
								if(send_num < 0)
								{
									perror("sendto error:");
									exit(1);
								}
						}
						lastcurtime=curtime;
						myqueue.push(line);
					}
					if (times>curtime){
						curtime=times;
				}
			}
		}


		
		umap[nameid]=line;
		/*
		for (auto iter=umap.begin();iter!=umap.end();++iter){
			cout<<iter->first<<" "<<iter->second<<endl;
		}
		*/
	
		// count++;
		// cout<<"count is "<<count<<endl;

	}

	infile.close();
}

int main(){
	string path="/media/zhou/3d3bcba8-4222-49a4-92ae-8d53e869e4ed/data/future/commondata/marketdata.csv";
	read_data(path);

}
