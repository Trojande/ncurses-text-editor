#include "EditorInterface.h"
#include "KeyHandler.h"
#include "Constants.h"
EditorInterface::EditorInterface(std::string _filename){
    transition = 0;
	setPosition(0, 0);
    filename = _filename;
    setStatus(filename);
    isActive = true;
    mode = true;
    command = "";
    realBuff = Buffer(filename);
    for(int i=0; i < realBuff.getSize() && i < LINES - 1 ; i++) {
        fakeBuff.appendLine(realBuff.getLine(i));
    }
}
EditorInterface::EditorInterface() {
    setPosition(0, 0);
    filename = "untitled";
    setStatus(filename);
    isActive = true;
    mode = true;
    command = "";
    realBuff = Buffer(true);
    fakeBuff = Buffer(true);
}
void EditorInterface::ExecuteCommand(std::string cmd) {
	std::transform(cmd.begin(), cmd.end(), cmd.begin(), ::tolower); //lowercase: save SAVE saVE will be works
	if (cmd == "save") {
		realBuff.saveToFile(filename);
		status.erase(status.begin());
	} else
	if (cmd == "exit") {
		appExit();
	}
}
void EditorInterface::insertChar(char c) {
	std::string newString = fakeBuff.getLine(y);
	newString.insert(x, 1, c);
	fakeBuff.removeLine(y);
    fakeBuff.writeLine(newString, y);
	realBuff.removeLine(transition + y);
	realBuff.writeLine(newString, transition + y);
}
std::string EditorInterface::getStatusLine() {
    return status + "/" + std::to_string(x + 1) + ":" + std::to_string(y + transition + 1);
}
void EditorInterface::setStatus(std::string _status) {
    status = _status;
}
bool EditorInterface::setPosition(int _x, int _y) {
    if (_x >= 0) { 
        x = _x;
        y = _y;
    }
}
void EditorInterface::appExit() {
    isActive = false;
}
void EditorInterface::changeMode() {
    mode = !mode;
}
void EditorInterface::scrollHandler(int direction) {
    switch (direction) {
        case SCROLL_DOWN:
            if ((fakeBuff.getSize() + transition) != realBuff.getSize()) { //if it's not end
                fakeBuff.removeLine(0); //hide first line
                int nextIndex = ++transition + fakeBuff.getSize(); ; //calculate current last line index
                fakeBuff.appendLine(realBuff.getLine(nextIndex)); //append to our visible buffer
            }
            break;
        case SCROLL_UP:
            if (transition != 0) { // if it's not begin
                int prevIndex = --transition; // calculate previous index and transition value
                fakeBuff.removeLine(fakeBuff.getSize() - 1); //hide last line
                fakeBuff.writeLine(realBuff.getLine(prevIndex), 0); //show previous line
            }
			break;
		case SCROLL_ENTER:
			fakeBuff.removeLine(0);
			fakeBuff.appendLine("\n");
			realBuff.writeLine("\n", fakeBuff.getSize() + ++transition);
			
            
    }
    
}
void EditorInterface::actionHandler(int action) {
    if (mode) {
        switch (action) {
            case ENTER:
				if (y+1 == LINES - 1)
					scrollHandler(SCROLL_ENTER);
				else {
						fakeBuff.writeLine("\n", y);
						realBuff.writeLine("\n", y);
						setPosition(x, y+1);
					}
				
				
				
                break;
            case UP:
                if (y == 0)
                    scrollHandler(SCROLL_UP);
                else
                    setPosition(x,y-1);
                break;
            case DOWN:
                if (y+1 == LINES - 1 ) 
                    scrollHandler(SCROLL_DOWN); //scroll outside
                else
					if (y+1 > realBuff.getSize()) break;
                    setPosition(x,y+1); //scroll inside
                break;
            case LEFT:
                setPosition(x-1,y);
                break;
            case RIGHT:
                setPosition(x+1,y);
                break;
            case TAB:
                setPosition(x+4,y);
                break;
            case BACKSPACE:
                setPosition(x-1,y);
				std::string newStr = fakeBuff.getLine(y);
				if newStr != "" {
					newStr.erase(str.begin()+x,1)
				}
                setStatus("*"+filename );
            case DELETE:
                setPosition(x+1,y);
                setStatus("*" + filename);
                break;
            case MODE:
                changeMode();
                setPosition(0, LINES - 1);
                break;
			case PDOWN:
				for (int i=0;i<4;i++) 
					actionHandler(DOWN);
                break;
			case PUP:
				for (int i=0;i<4;i++) 
					actionHandler(UP);
				break;
				
            default:
                setStatus("*" +filename);
				insertChar(char(action));
				setPosition(x+1,y);
                break;
        } 
    } 
    
    else { //execute command
        switch (action) {
            case MODE:
                changeMode();
                setPosition(0,0);
            case ENTER:
				ExecuteCommand(command);
				command="";
				changeMode();
                setPosition(0,0);
                break;
            case BACKSPACE:
                //set
                if (command.size() !=0) {
					command.erase(command.end() - 1);
					setPosition(x-1, y);
				}
                break;
            default:
                command+=char(action);
				setPosition(x+1,y);
                break;
                
        }
    }
    
}

void EditorInterface::handleInput(int c){
    int action = KeyHandler().getKey(c);
    actionHandler(action);
}

bool EditorInterface::refresh() {
    erase(); // clear screen
    for(int i=0; i < fakeBuff.getSize(); i++) {
        mvprintw(i, 0, fakeBuff.getLine(i).c_str());
    }
	if (!mode && command!="") {
		mvprintw(LINES - 1,0, command.c_str()) ;
	}
    std::string currentStatusLine = getStatusLine();
    mvprintw(LINES - 1,COLS - currentStatusLine.size(), currentStatusLine.c_str());
    move(y,x);
    
    return isActive;
}