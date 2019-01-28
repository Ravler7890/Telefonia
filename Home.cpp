#include <iostream>
#include "User.h"
#include "connection.h"
#include "Number.h"
#include <sstream>
#include <vector>
#include "History.h"

void user_menu(int user_id);
void admin_menu(int user_id);
void statistics();

int main(void) {


	std::stringstream ss;
	std::string login, password;
	MYSQL_ROW row;
	int access;

	std::cout << "TELEFONIA" << std::endl;

	while (1) {

		std::cout << std::endl;
		std::cout << "Zaloguj sie" << std::endl;
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
	int i = 1;
	bool end = false;

	std::cout << "Zalogowano jako uzytkownik" << std::endl;

	while (!end) {

		std::cout << std::endl;
		std::cout << "1. Wykonaj polaczenie" << std::endl;
		std::cout << "2. Sprawdz historie" << std::endl;
		std::cout << "3. Wyloguj" << std::endl;

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
					Number n1(user_id, phone_number2);
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
			if (1) {

				History h1("s", "s");
				h1.history_show(user_id);
			}
			break;

		case 3:

			end = true;
		}
	}
}

void admin_menu(int user_id) {

	bool end = false;
	int choose;
	std::stringstream ss;
	MYSQL_RES * res;
	MYSQL_ROW row;
	std::string phone_number;
	std::string phone_number2;
	std::vector <std::string> user_phone_numbers;
	bool result;
	int user_id2;


	std::cout << "Zalogowano jako admin" << std::endl;

	while (!end) {

		std::cout << std::endl;
		std::cout << "1. Wykonaj polaczenie" << std::endl;
		std::cout << "2. Sprawdz swoja historie" << std::endl;
		std::cout << "3. Sprawdz historie uzytkownika" << std::endl;
		std::cout << "4. Wyswietl cala historie" << std::endl;
		std::cout << "5. Dodaj uzytkownika" << std::endl;
		std::cout << "6. Usun uzytkownika" << std::endl;
		std::cout << "7. Dodaj numer" << std::endl;
		std::cout << "8. Dodaj historie polaczenia" << std::endl;
		std::cout << "9. Wyswietl statystki" << std::endl;
		std::cout << "10. Wyswietl wszystkich uzytkownikow" << std::endl;
		std::cout << "11. Wyloguj" << std::endl;

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
					Number n1(user_id, phone_number2);
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
			if (1) {

				History h1("s", "s");
				h1.history_show(user_id);
			}
			break;

		case 3:

			
			std::cout << "Podaj ID uzytkownika, ktorego historie chcesz sprawdzic: "; std::cin >> user_id2;
			ss.str("");
			ss << "Select second_name from user where user_id = " << user_id2;
			if (row = mysql_fetch_row(request(ss.str()))) {
				History h1("s", "s");
				h1.history_show(user_id2);
			}
			else
				std::cout << "Uzytkownik o podanym id nie istnieje" << std::endl;

			break;

		case 4:

			if (1) {
				History h1("s", "s");
				h1.history_show();
			}
			break;

		case 5:

			if (1) {

				User u1;
				u1.add_user();
			}
			break;

		case 6:


			std::cout << "Podaj ID uzytkownika, ktoremu chcesz dodac numer: "; std::cin >> user_id2;

			if (1) {
				ss.str("");
				ss << "select * from user where user_id =" << user_id2;
				if (request(ss.str())->row_count >= 1) {
						User u1(0,user_id2);
						u1.drop_user();
					}

				}
				else
					std::cout << "Uztkownik o podanym ID nie istnieje" << std::endl;	
			break;

		
		case 7:

			std::cout << "Podaj ID uzytkownika, ktoremu chcesz dodac numer: "; std::cin >> user_id2;
			if (1) {
				ss.str("");
				ss << "select * from user where user_id =" << user_id2;
				if (request(ss.str())->row_count >= 1) {
					Number n1(user_id2, "default");
					n1.add_number();

				}
				else
					std::cout << "Uztkownik o podanym ID nie istnieje" << std::endl;

			}
			break;

		case 8:

			if (1) {
				History h1("s", "s");
				h1.history_manual_add();
			}
			break;

		case 9:
			
			statistics();
			getchar();
			break;

		case 10:
			if (1) {

				User u1;
				u1.show_all_user();
			}
			getchar();
			break;

		case 11:
			end = true;
		}
	}

}


void statistics() {

	float variable1, variable2, variable3;

	std::stringstream ss;
	MYSQL_ROW row;

	std::cout << std::endl;


	ss << "select count(*) from user";
	row = mysql_fetch_row(request(ss.str()));
	variable1 = atoi(row[0]);

	ss.str("");
	ss << "SELECT COUNT(*) FROM user where sex = 'K'";
	row = mysql_fetch_row(request(ss.str()));
	variable2 = atoi(row[0]);

	variable3 = variable2 / variable1;

		std::cout.precision(2);
		std::cout << variable3 * 100 << " % uzytkownikow to kobiety" << std::endl;
		std::cout << (1 - variable3) * 100 << " % uzytkownikow to mezczyzni" << std::endl;

	ss.str("");
	ss << "select AVG(duration) from history";
	row = mysql_fetch_row(request(ss.str()));
	variable1 = atoi(row[0]);
	std::cout <<"Sredni czas polaczenia " << (int)variable1/360 <<":" << ((int)variable1 % 3600) / 60 <<":" << (int)variable1 % 60 << std::endl;

	ss.str("");
	ss << "SELECT AVG(TIMESTAMPDIFF(YEAR, birth_date, CURDATE())) AS age from user";
	row = mysql_fetch_row(request(ss.str()));
	variable1 = atoi(row[0]);
	std::cout << "Srednia wieku uzytkownikow " << (float)variable1 << std::endl;

}