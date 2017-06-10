#ifndef BUFFER_CLASS
#define BUFFER_CLASS

#include <fstream>
#include <vector>
#include <string>
#include <ncurses.h>


class Buffer
{
public:
    Buffer(bool = false);
	Buffer(std::string);
	// void destroy();
	// void save(std::string file);
    int getSize();
    std::string getLine(int);
	void writeLine(std::string, int);
    void removeLine(int);
    void appendLine(std::string);
	bool saveToFile(std::string);
private:
	std::vector<std::string> buff;
};

#endif 