#pragma once
#pragma warning(disable : 4996)
#include <iostream>
#include "connection.h"
#include <sstream>
#include <time.h>

class History {

private:
	int row_id;
	std::string call_from;
	std::string call_to;
	struct tm* start;
	struct tm* stop;
	int duration;

public:

	History(std::string = "777000000", std::string = "777000001");
	void history_add();
	void history_manual_add();
	void history_delete();


};