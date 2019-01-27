#pragma once
#pragma warning(disable : 4996)
#include <iostream>
#include <ctime>
#include <vector>
#include <sstream>
#include <time.h>

#include "Number.h"
#include "connection.h"


class User {

private:

	int user_id;
	std::string first_name;
	std::string second_name;
	std::string login;
	std::string password;
	char sex[1];
	struct tm* birth_date;
	int access;

public:

	User(int = 0);

	void add_user();
	void drop_user();
	void show_user();
	void show_all();

	bool valid(std::string dane);

};
