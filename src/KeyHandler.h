#ifndef KEYHANDLER_CLASS
#define KEYHANDLER_CLASS
#include <string>
#include <ncurses.h>
class KeyHandler 
{
public:
    KeyHandler();
    int getKey(int);
};

#endif