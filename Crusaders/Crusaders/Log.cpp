#include "Log.hpp"
#include <fstream>
#include <sstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <time.h>


Log::Log() {
	// Reading now time http://stackoverflow.com/questions/997946/how-to-get-current-time-and-date-in-c
	time_t t = time(0);
	struct tm* now = localtime(&t);
	std::stringstream stream;
	stream << "Logs\\"
		<< std::setfill('0') << std::setw(4) << now->tm_year + 1900
		<< std::setw(2) << now->tm_mon + 1
		<< std::setw(2) << now->tm_mday
		<< ".log";
	stream >> path;

	std::ofstream log(path, std::ios::out | std::ios::app);
	log << std::setw(2) << now->tm_hour << ":"
		<< std::setw(2) << now->tm_min << ":"
		<< std::setw(2) << now->tm_sec << ": "
		<< "Log created."
		<< std::endl;
}

void Log::WriteLine(const std::string& message) {
	std::ofstream log(path, std::ios::out | std::ios::app);
	log << message << std::endl;
}

void Log::Write(const std::string& message) {
	std::ofstream log(path, std::ios::out | std::ios::app);
	log << message;
}