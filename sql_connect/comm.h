#pragma once
#include <iostream>
#include <string>
#include <mysql.h>
#include<stdlib.h>
#include<stdio.h>
#include <string>
using namespace std;
MYSQL* connectMysql();
int insertMysql(MYSQL *myfd, const std::string &name, \
		const std::string &keyword, const std::string &author);
void selectMysql(MYSQL *myfd);
void closeMysql(MYSQL *myfd);
