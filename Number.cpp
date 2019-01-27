#include "Number.h"

Number::Number(int user_id, std::string phone_number) {

	this->user_id = user_id;
	this->phone_number = phone_number;

}

void Number::add_number() {

	std::stringstream ss;

	ss.str("");
	ss << "Insert into phone_number(user_id) values (" << this->user_id << ")";
	if (simple_request(ss.str()))
		std::cout << "Numer dodany pomyslnie" << std::endl;

}

bool Number::check_number() {

	std::stringstream ss;

	ss.str("");
	ss << "select * from phone_number where phone_number = '" << phone_number << "'";
	if (request(ss.str())->row_count >= 1)
		return true;
	else
		return false;

	
}

