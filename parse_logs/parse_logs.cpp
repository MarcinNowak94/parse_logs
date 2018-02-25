// parse_logs.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <fstream>

struct downtime
{
	std::string timestamp = "";
	int errcount=0;
};

int parselogs(const std::string & logfilename)
{
	std::ifstream logfile;
	try	{logfile.open(logfilename);} catch (std::system_error& e) 
	{std::cerr << e.code().message() << '\n'; return EXIT_FAILURE;};

	downtime tempdown = {"Timestamp", 0};
	std::vector<downtime> down(1);
	down.at(0)=tempdown;
	std::string temp;
	
	int iter = 0;
	//getting & storing data
	do
	{
		std::getline(logfile, temp);
		std::cout << iter++ << '\t' << temp << '\n';
		if (temp.substr(0, 4) == "----") continue;
		tempdown = { temp.substr(0, 10), 1 };
		if (temp.substr(0, 10) != down.back().timestamp) { down.emplace_back(tempdown); }
		else { down.back().errcount++; };
	}while (!logfile.eof());
	std::cout << "Reading data finished. Dates stored:\t" << down.size() << "\a\n\n";
	//displaying processed data
	for (auto i = 0; i < down.size(); i++)
	{
		std::cout << "Date:\t" << down.at(i).timestamp << "\tErrors:\t" << down.at(i).errcount << "\n";
	};
	logfile.close();
	return EXIT_SUCCESS;
};

int main()
{
	parselogs("Przerwy_polaczenia.log");
	std::cout << "\nPress any key to continue...";
	_getch();
    return 0;
}

//date of creation:  25.02.18
