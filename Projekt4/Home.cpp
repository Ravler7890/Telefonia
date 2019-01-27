#include <iostream>
#include "User.h"
#include "connection.h"
#include "number.h"
#include <sstream>
#include <vector>
#include "History.h"

void user_menu(int user_id);
void admin_menu(int user_id);

int main(void) {

	while (1) {
		if (getchar())
			break;
	}

	std::stringstream ss;
	std::string login, password;
	MYSQL_ROW row;
	int access;

	while (1) {

		std::cout << "TELEFONIA" << std::endl;
		std::cout << "Podaj login: "; std::cin >> login;
		std::cout << "Podaj haslo: "; std::cin >> password;

		ss.str("");
		ss << "select user_id, access from user where login = '" << login << "' and password = '" << password << "'";

		if (row = mysql_fetch_row(request(ss.str()))) {
			if (atoi(row[1]) == 1)
				admin_menu(atoi(row[0]));
			else
				user_menu(atoi(row[0]));
		}
		else {
			std::cout << "Bledny login lub haslo" << std::endl;
			continue;
		}
			
		
	}


	return 0;
}

void user_menu(int user_id) {

	std::stringstream ss;
	int choose = 0;
	MYSQL_ROW row;
	MYSQL_RES *res;
	std::string phone_number;
	std::string phone_number2;
	std::vector <std::string> user_phone_numbers;
	bool result;
	int i = 1 ;

	std::cout << "Zalogowano jako uzytkownik" << std::endl;
	std::cout << "1. Wykonaj polaczenie" << std::endl;
	std::cout << "2. Sprawdz historie" << std::endl;

	std::cin >> choose;

	switch (choose) {
	case 1:

		ss.str("");
		ss << "select phone_number, second_name from phone_number p inner join user u on p.user_id = u.user_id where p.user_id =" << user_id;
		res = request(ss.str());

		if (res->row_count == 0)
			std::cout << "Nie posiadasz numeru z ktorego moglbys zadzwonic" << std::endl;

		else {

			row = mysql_fetch_row(res);
			std::cout << "Dostepne numery uzytkownika " << row[1] << " to: " << std::endl;
			std::cout << row[0] << std::endl;
			user_phone_numbers.push_back(row[0]);
			while (row = mysql_fetch_row(res)) {
				std::cout << row[0] << std::endl;
				user_phone_numbers.push_back(row[0]);
			}

			while (1) {

				std::cout << "Numer z ktorego chcesz zadzwonic: "; std::cin >> phone_number;
			
				for (auto it = user_phone_numbers.begin(); it != user_phone_numbers.end(); it++) {
					if ((it->compare(phone_number)) == 0) {
						result = true;
						break;
					}
					else
						result = false;
				}

				if (result)
					break;
				else
					std::cout << "Wybierz numer z listy" << std::endl;
			}

			while (1) {
				std::cout << "Podaj numer na ktory chcesz zadzwonic: "; std::cin >> phone_number2;
				Number n1(user_id,phone_number2);
				if (n1.check_number()) {
					History h1(phone_number, phone_number2);
					h1.history_add();
					break;
				}
				else
					std::cout << "Numer na ktory chcesz zadzwonic nie istnieje, podaj inny numer" << std::endl;
				
			}

		}

		break;

		

	case 2:
		break;

	default:
		std::cout << "cos" << std::endl;
	}

}

void admin_menu(int user_id) {
	std::cout << "Zalogowano jako admin" << std::endl;
}