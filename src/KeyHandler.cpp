#include "KeyHandler.h"
#include "Constants.h"
KeyHandler::KeyHandler() {};
int KeyHandler::getKey(int c) {
    switch (c) {
        case KEY_UP:
            return UP;
        case KEY_DOWN:
            return DOWN;
        case KEY_LEFT:
            return LEFT;
        case KEY_RIGHT:
            return RIGHT;
        case KEY_BACKSPACE:
        case 127:
            return BACKSPACE;
        case KEY_DC:
            return DELETE;
        case KEY_ENTER:
        case 10:
            return ENTER;
        case 9:
        case KEY_BTAB:
        case KEY_CTAB:
        case KEY_STAB:
        case KEY_CATAB:
            return TAB;
        case KEY_F2:
            return MODE;
		case KEY_NPAGE:
			return PDOWN;
		case KEY_PPAGE:
			return PUP;
		default:
			return c;

   }

}  
