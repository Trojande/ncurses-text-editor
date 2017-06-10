#ifndef EDITOR_INTERFACE_CLASS
#define EDITOR_INTERFACE_CLASS

#include <string>
#include <ncurses.h>
#include "Buffer.h"
#include <algorithm>
class EditorInterface
{
public:
    EditorInterface();
    EditorInterface(std::string); //load from file
	void handleInput(int); //handle keyboard input
	bool refresh(); //mainfunc
private:
	int x,y;
    void setStatus(std::string);
	void insertChar(char);
    std::string getStatusLine();
    void changeMode();
    void appExit();
	void ExecuteCommand(std::string);
    void scrollHandler(int);
    bool setPosition(int,int);
	void actionHandler(int);
    std::string status;
    std::string filename;
    std::string command;
	bool isActive; // exit if false
    bool mode; //true = edit mode, false = command execute mode
    int transition; // transition to real buffer
	Buffer realBuff, fakeBuff;

};

#endif