#pragma once
#include <iostream>
#include "connection.h"
#include <sstream>

class Number {

private:

	std::string phone_number;
	int user_id;

public:

	Number(int user_id = 0, std::string phone_number = "777000000");
	bool check_number();
	void add_number();
	void drop_number();
	void show_number();

};