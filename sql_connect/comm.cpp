#include "comm.h"
#include <iostream>
#include <locale>
#include <cstdlib>
#include<string.h>
using namespace std;
MYSQL* connectMysql()
{
	MYSQL *myfd = mysql_init(NULL);
	if(mysql_real_connect(myfd,"127.0.0.1","root","","34_class",\
				3306,NULL,0) == NULL)
	{
		std::cerr<<"connect error"<<std::endl;
	}
	else{
		mysql_query(myfd, "SET NAMES UTF8");
		std::cout<<"<h2>"<<"Mysql connect success"<<"<h2>"<<std::endl;
	}
	return myfd;
}



int insertMysql(MYSQL *myfd, const std::string &name, \
		const std::string &keyword, const std::string &author)
{
	std::cout<<author<<std::endl;
	//VALUES ("zhangsan", "man", "conding")
	std::string sql="INSERT INTO st_table (name,keyword,author) VALUES (\"";
	sql += name;
	sql += "\",\"";
	sql += keyword;
	sql += "\",\"";
	sql += author;
	sql += "\")";
	std::cout << sql << std::endl;
	std::cout << "</table>" << std::endl;
	free(result);
}


void selectMysql(MYSQL *myfd)
{
	std::string sql = "SELECT * FROM st_table";
	mysql_query(myfd, sql.c_str());
	MYSQL_RES * result = mysql_store_result(myfd);
	int lines = mysql_num_rows(result);
	int cols = mysql_num_fields(result);
	std::cout << "<table border=\"1\"> " << std::endl;
	MYSQL_FIELD *field = mysql_fetch_fields(result);
	int i = 0;
	std::cout << "<tr>" << std::endl;
	for(; i < cols; i++){
		std::cout << "<th>" << field[i].name << "</th>";
	}
	std::cout << "</tr>" << std::endl;

	for(i=0; i < lines; i++){
		std::cout << "<tr>" << std::endl;
		MYSQL_ROW line = mysql_fetch_row(result);
		int j = 0;
		for(; j < cols; j++){
			std::cout << "<td>" << line[j] << "</td>";
		}
		std::cout << "</tr>" << std::endl;
	}
	std::cout << "</table>" << std::endl;
	free(result);
}

void closeMysql(MYSQL *myfd)
{
	mysql_close(myfd);
}
