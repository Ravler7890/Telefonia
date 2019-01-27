#pragma once
#include <iostream>
#include <string>
#include <sstream>
#include <mysql.h>


#define ADDRES "localhost"
#define USER "root"
#define PASSWD ""
#define DATA_BASE "telefonia"


MYSQL* connect();
bool simple_request(std::string request);
MYSQL_RES* request(std::string request);