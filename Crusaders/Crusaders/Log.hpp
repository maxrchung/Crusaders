#pragma once

#include <string>

class Log {
public:
	Log();
	void WriteLine(const std::string& message);
	void Write(const std::string& message);

	std::string path;
};
