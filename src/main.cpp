#include <ncurses.h>
#include "EditorInterface.h"

void init(){
    initscr();
    noecho();
    cbreak();
    keypad(stdscr, true);  
}

int main(int argc, char const *argv[])
{
	
	EditorInterface ei;
	init();
	if (argv[1]) 
        ei = EditorInterface(argv[1]);
    else
        ei = EditorInterface();
    
    while (ei.refresh()) {
        int inputButton = getch();
        ei.handleInput(inputButton);
    }
	endwin();

	return 0;
}