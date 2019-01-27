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

	std::cout << "Podaj date i godzine rozpoczêcia rozmowy w formacie rrrr-mm-dd gg-mm-ss"; std::string start_date;
	std::cout << ""
	std::string stop_date;



}