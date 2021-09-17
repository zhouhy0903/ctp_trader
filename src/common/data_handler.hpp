#ifndef __DATA_HANDLER_HPP_
#define __DATA_HANDLER_HPP_
#include<fstream>
#include<cstring>
#include<vector>
#include<iconv.h>

size_t convert(char *inbuf, size_t inlen, char *outbuf, size_t outlen){
		char **pin = &inbuf; 
		char **pout = &outbuf; 
		memset(outbuf,0,outlen);
		iconv_t cd = iconv_open("utf-8", "gbk"); 
		return iconv(cd, pin, (size_t *)&inlen, pout, (size_t *)&outlen); 
}

std::vector<std::string> get_config(){
	std::ifstream ifile("../config/config.txt");
	std::string line;
	std::vector<std::string> ans(4);
	int i=0;  	
	while (getline(ifile,line)){
		ans[i]=line.data();
		i++;
	}
	ifile.close();
	return ans;
}


std::vector<std::string> read_contractid(std::string path){
    std::ifstream ifile(path);
    std::string line;
    std::vector<std::string> ans;
    while (getline(ifile,line)){
        ans.push_back(line);
    }
    ifile.close();
    return ans;
}

std::vector<std::string> parse_string(std::string tickstring){
	//将字符串转化为vector数组
}

#endif