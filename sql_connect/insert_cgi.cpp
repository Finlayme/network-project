#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<unistd.h>
#include<fcntl.h>
#include"comm.h"
#include <string>
#include <fstream>
int main()
{
	char arg[1024];
	if(getenv("METHOD")){
		if(strcasecmp(getenv("METHOD"), "GET") == 0){
			strcpy(arg, getenv("QUERY_STRING"));
		}else{
			char c;
			int i = 0;
			int len = atoi(getenv("CONTENT_LENGTH"));
			for(; i < len; i++ ){
				read(0, &c, 1);
				arg[i] = c;
			}
			arg[i] = 0;
		}
	}
	MYSQL *myfd = connectMysql();
	strtok(arg, "=&");
	std::string name = strtok(NULL, "=&");
	strtok(NULL, "=&");
	std::string keyword = strtok(NULL, "=&");
	strtok(NULL, "=&");
	std::string author = strtok(NULL, "=&");
	insertMysql(myfd, name,keyword, author);
	closeMysql(myfd);
}











