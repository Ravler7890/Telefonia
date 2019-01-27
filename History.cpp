#include "History.h"


History::History(std::string call_from, std::string call_to) {


	this->call_from = call_from;
	this->call_to = call_to;

}

void History::history_add(){
	
	std::stringstream start_date;
	std::stringstream stop_date;

	std::cout << "Trwa polaczenie, nacisnij dowolny klawisz aby przerwac" << std::endl;

	time_t start = time(0);
	this->start = localtime(&start);

	start_date << this->start->tm_year + 1900 << "-" << this->start->tm_mon + 1 << "-" << this->start->tm_mday << " " << this->start->tm_hour << ":"
		<< this->start->tm_min << ":" << this->start->tm_sec;

	std::cin.ignore();
	getchar();
			
	time_t stop = time(0);
	this->stop = localtime(&stop);

	stop_date << this->stop->tm_year + 1900 << "-" << this->stop->tm_mon + 1 << "-" << this->stop->tm_mday << " " << this->stop->tm_hour << ":" 
		<< this->stop->tm_min << ":" << this->stop->tm_sec;

	duration = stop - start;
	std::cout << duration << std::endl;

	std::stringstream ss;
	ss << "insert into history(call_from, call_to, call_begin, call_end, duration) values ('"
		<< this->call_from << "','" << this->call_to << "','" << start_date.str() <<"','" << stop_date.str() << "','" << (int)this->duration / 3600 << ":"
		<< (int)(this->duration % 3600) / 60 << ":" << (int)(this->duration%60) << "')";

	simple_request(ss.str());

}

void History::history_manual_add() {

	std::string stop_date;
	std::string start_date;
	int duration;

	std::cout << "Podaj numer z ktorego zostalo wykonane polaczenie: "; std::cin >> this->call_from;
	std::cout << "Podaj numer na ktore zostalo wykonane polaczenie: "; std::cin >> this->call_to;
	std::cin.ignore();
	std::cout << "Podaj date i godzine rozpoczêcia rozmowy w formacie rrrr-mm-dd gg-mm-ss: "; getline(std::cin, start_date);
	std::cin.ignore();
	std::cout << "Podaj date i godzine zakonczenia rozmowy w formacie rrrr-mm-dd gg-mm-ss: "; getline(std::cin, stop_date);
	std::cout << "Podaj czas polaczenia w sekundach: "; std::cin >> duration;

	std::stringstream ss;
	ss << "insert into history(call_from, call_to, call_begin, call_end, duration) values ('"
		<< this->call_from << "','" << this->call_to << "','" << start_date << "','" << stop_date << "','" << (int)duration / 3600 << ":"
		<< (int)(duration % 3600) / 60 << ":" << (int)duration % 60 << "')";

	if (simple_request(ss.str()))
		std::cout << "Pomyslnie dodano wpis do historii" << std::endl;


}

void History::history_show(int user_id) {

	MYSQL_ROW row;
	MYSQL_RES* res;
	int i = 1;

	std::stringstream ss;
	ss << "select call_from, call_to, call_begin, call_end, duration from history h "
		<< "inner join phone_number p on h.call_from = p.phone_number or h.call_to = p.phone_number "
		<< "where user_id = " << user_id << " order by call_begin DESC";
	
	std::cout << "Wyswietlam historie uzytkownika o ID nr " << user_id << std::endl << std::endl;

	std::cout << std::left << std::setw(5) << "ID";
	std::cout << std::left << std::setw(15) << "Z numeru:";
	std::cout << std::left << std::setw(15) << "Na numer";
	std::cout << std::left << std::setw(25) << "Data rozp.";
	std::cout << std::left << std::setw(25) << "Data zak";
	std::cout << std::left << std::setw(15) << "Czas trwania";
	std::cout << std::endl;

	res = request(ss.str());

	while (row = mysql_fetch_row(res)) {

		
		std::cout << std::left << std::setw(5) << i;
		std::cout << std::left << std::setw(15) << row[0];
		std::cout << std::left << std::setw(15) << row[1];
		std::cout << std::left << std::setw(25) << row[2];
		std::cout << std::left << std::setw(25) << row[3];
		std::cout << std::left << std::setw(15) << row[4];
		std::cout << std::endl;
		i++;
	}

}

void History::history_show() {

	MYSQL_ROW row;
	MYSQL_RES* res;
	int i = 1;

	std::stringstream ss;
	ss << "select call_from, call_to, call_begin, call_end, duration from history order by call_begin DESC";
		

	std::cout << std::left << std::setw(5) << "ID";
	std::cout << std::left << std::setw(15) << "Z numeru:";
	std::cout << std::left << std::setw(15) << "Na numer";
	std::cout << std::left << std::setw(25) << "Data rozp.";
	std::cout << std::left << std::setw(25) << "Data zak";
	std::cout << std::left << std::setw(15) << "Czas trwania";
	std::cout << std::endl;

	res = request(ss.str());

	while (row = mysql_fetch_row(res)) {

		std::cout << std::left << std::setw(5) << i;
		std::cout << std::left << std::setw(15) << row[0];
		std::cout << std::left << std::setw(15) << row[1];
		std::cout << std::left << std::setw(25) << row[2];
		std::cout << std::left << std::setw(25) << row[3];
		std::cout << std::left << std::setw(15) << row[4];
		std::cout << std::endl;
		i++;
	}

}