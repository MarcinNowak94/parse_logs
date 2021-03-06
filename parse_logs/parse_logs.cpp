// parse_logs.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <fstream>

struct downtime
{
	std::string timestamp = "";
	int errcount=0;
};

int main(int argc, char* argv[])
{
	if (!argv[1]) { std::cout << "Please specify log file to parse.\a\n"; return EXIT_FAILURE; };
	std::ifstream logfile;
	try	{logfile.open(argv[1]+'\0');} catch (std::system_error& e) 
	{std::cerr << e.code().message() << '\n'; return EXIT_FAILURE;};
	
	//getting & storing data
	if (logfile.is_open())
	{
		downtime tempdown = { "Timestamp", 0 };
		std::vector<downtime> down(1);
		down.at(0) = tempdown;
		std::string temp;
		int iter = 0;
		do
		{
			std::getline(logfile, temp);
			if (temp.substr(0, 4) == "----") continue;
			tempdown = { temp.substr(0, 10), 1 };
			if (temp.substr(0, 10) != down.back().timestamp) { down.emplace_back(tempdown); }
			else { down.back().errcount++; };
		} while (!logfile.eof());
		std::cout << "Reading data finished. Dates stored:\t" << down.size() << "\a\n\n";
		//displaying processed data
		for (auto i = 0; i < down.size(); i++)
		{
			std::cout << "Date:\t" << down.at(i).timestamp << "\tErrors:\t" << down.at(i).errcount << "\n";
		};
		logfile.close();
	};
	return EXIT_SUCCESS;
};

//date of creation:  25.02.18
