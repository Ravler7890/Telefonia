#include "User.h"



User::User(int taccess) {

	this->access = taccess;

}

//lols

void User::add_user() {


	int choose = 0;
	bool result = false;
	MYSQL_ROW row;
	

	std::stringstream ss;
	//std::string date;

	int bDay, bMonth, bYear;
	time_t current = time(NULL); // pobieram obecn¹ datê
	birth_date = localtime(&current); // Uzupelniam strukture dat¹ obecn¹


	std::cout << "*** Procedura dodawania nowego uzytkownika ***" << std::endl;

	while (1) {

		std::cout << "Login (max 15 znakow): "; std::cin >> this->login;
		if (this->login.length() > 15) {
			std::cout << "Login jest za dlugi (max 15 znakow)" << std::endl;
			continue;
		}

		ss.str("");
		ss << "Select * from user where login = '" << this->login << "'";

		if (mysql_fetch_row(request(ss.str()))) {
			std::cout << "Podany login istnieje w bazie" << std::endl;
			continue;
		}
		else break;

	}

	while (1) {

		std::cout << "Haslo (max 15 znakow): "; std::cin >> this->password;
		if (this->password.length() > 15) {
			std::cout << "Haslo jest zbyt dlugie" << std::endl;
			continue;
		}
		else break;

	}

	while (1) {
		std::cout << "Imie: "; std::cin >> this->second_name;
		if (!this->valid(this->second_name))
			continue;
		else break;
	}

	while (1) {
		std::cout << "Nazwisko: "; std::cin >> this->first_name;
		if (!this->valid(this->first_name))
			continue;
		else break;
	}

	while (1) {

		std::cout << "Podaj dzien urodzenia: "; std::cin >> bDay;
		if (bDay > 31 || bDay <= 0)
			continue;
		else break;

	}

	while (1) {

		std::cout << "Podaj miesiac urodzenia: "; std::cin >> bMonth;
		if (bMonth > 12 || bMonth <= 0)
			continue;
		else break;

	}

	while (1) {

		std::cout << "Podaj rok urodzenia: "; std::cin >> bYear;
		if (birth_date->tm_year + 1900 - bYear < 18) {
			std::cout << "Osoba niepelnoletnia nie moze posiadac konta." << std::endl;
			continue;
		}
		else break;

	}

	this->birth_date->tm_year = bYear;
	this->birth_date->tm_mon = bMonth;
	this->birth_date->tm_mday = bDay;


	while (!result) {

		std::cout << "Plec: " << std::endl;
		std::cout << "1. Kobieta" << std::endl;
		std::cout << "2. Mezczyzna" << std::endl;

		std::cin >> choose;

		switch (choose) {

		case 1:
			sex[0] = 'K';
			result = true;
			break;
		case 2:
			sex[0] = 'M';
			result = true;
			break;
		default:
			std::cout << "Wybierz plec" << std::endl;
			result = false;
			break;
		}
	}


	std::cout << "Czy chcesz uzytkownik mial dostep do bazy?" << std::endl;
	std::cout << "Tak - wybierz 1 i zatwierdz enter; Nie - wybierz inna cyfre i zatwierdz enter" << std::endl;

	std::cin >> choose;

	if (choose == 1) {
		this->access = 1;
	}


	ss.str("");
	ss << "INSERT INTO user(first_name, second_name, birth_date, acces, sex, login, password) values ('"
		<< this->first_name << "','" << this->second_name << "','" << this->birth_date->tm_year << "-"
		<< this->birth_date->tm_mon << "-" << this->birth_date->tm_mday << "'," << this->access << ", '" << sex << "','"
		<< this->login << "','" << this->password << "');";

	if (simple_request(ss.str()))
		std::cout << "Uzytkownik zostal dodany pomyslnie" << std::endl;

	std::cout << "Czy chcesz teraz dodac numer telefonu uzytkownika?" << std::endl;
	std::cout << "Tak - wybierz 1 i zatwierdz enterem; Nie - wybierz dowolna cyfre" << std::endl;

	std::cin >> choose;

	if (choose == 1) {

		ss.str("");
		ss << "select user_id from user where login = '" << this->login << "'";
		row = mysql_fetch_row(request(ss.str()));

		this->user_id = atoi(row[0]);

		Number n1(this->user_id);
		n1.add_number();

		if (simple_request(ss.str())) {

			ss.str("");
			ss << "select phone_number from phone_number p inner join user u on p.user_id = u.user_id where u.login = '" << this->login << "'";
			row = mysql_fetch_row(request(ss.str()));
			std::cout << "Nowy numer uzytkownika " << this->second_name <<" to: " << row[0] << std::endl;

		}
	}


}

bool User::valid(std::string dane) {

	int size = 0;


	for (int i = 0; i < sizeof dane; i++) {
		if (dane[i] == NULL) {
			return true;
			break;
		}
		if (dane[i] < 65 || dane[i] > 90 && dane[i] < 96 || dane[i] > 122 || dane.length() > 30) {
			std::cout << "Niedozwolone znaki lub dlugosc" << std::endl;
			return false;
			break;
		}
	}

	return true;

}


void User::drop_user() {

	MYSQL_ROW row;

	std::stringstream ss;
	ss << "select * from user where user_id =" << this->user_id;
	if (request(ss.str())->row_count >= 1) {

		ss.str("");
		ss << "delete from phone_number where user_id = " << this->user_id;
		if (simple_request(ss.str()))
			std::cout << "Numery uzytkownika zostana usuniete..." << std::endl;

		ss.str("");
		ss << "delete from user where user_id = " << this->user_id;
		if (simple_request(ss.str()))
			std::cout << "Uzytkownik zostal usuniety z bazy danych..." << std::endl;


	}
	else {
		std::cout << "Uzytkownik o podanym id nie istnieje w bazie danych" << std::endl;
	}


}
