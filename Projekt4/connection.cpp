#include "connection.h"


MYSQL* connect() {

	MYSQL* conn;

	conn = mysql_init(0);
	conn = mysql_real_connect(conn, ADDRES, USER, PASSWD, DATA_BASE, 0, NULL, 0);

	if (conn) {
		std::cout << "Polaczono z baza danych" << std::endl;
		return conn;
	}
	else {

		std::cout << "BLAD POLACZENIA" << std::endl;
		return NULL;
	}


}


bool simple_request(std::string request) {

	MYSQL* conn;

	conn = mysql_init(0);
	conn = mysql_real_connect(conn, ADDRES, USER, PASSWD, DATA_BASE, 0, NULL, 0);

	const char*q = request.c_str();
	int qstate = mysql_query(conn, q);


	if (!qstate) {

		return true;

	}
	else {

		std::cout << "BLAD" << std::endl;
		std::cout << mysql_error(conn) << std::endl;
		return false;
	}


}

MYSQL_RES* request(std::string request) {

	MYSQL* conn;
	MYSQL_RES* res;

	conn = mysql_init(0);
	conn = mysql_real_connect(conn, ADDRES, USER, PASSWD, DATA_BASE, 0, NULL, 0);

	const char*q = request.c_str();
	int qstate = mysql_query(conn, q);

	

	if (!qstate) {

		res = mysql_store_result(conn);
		return res;

	}
	else {

		std::cout << "BLAD POLACZENIA" << std::endl;
		std::cout << mysql_error(conn) << std::endl;
		return NULL;
	}


}