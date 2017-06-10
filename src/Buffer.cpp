#include "Buffer.h"

Buffer::Buffer(std::string fileName) {
	std::string line;
	std::ifstream file (fileName);
	if (file.is_open()) {
		while (getline (file,line)) {
			buff.push_back(line);
		}
		file.close();
	}
}
Buffer::Buffer(bool isBlank) {
	if (isBlank) buff.push_back("");
}
int Buffer::getSize() {
    return buff.size();
}
void Buffer::writeLine(std::string line, int position){
	buff.insert(buff.begin()+position, line);
}
void Buffer::removeLine(int position) {
    buff.erase(buff.begin()+position);
}
std::string Buffer::getLine(int position) {
    return buff[position];
}
void Buffer::appendLine(std::string line) {
    buff.push_back(line);
}
bool Buffer::saveToFile(std::string fileName) {
	std::ofstream file (fileName);
	if (file.is_open()) {
		try {
			for(auto it = buff.begin(); it != buff.end();it++) {
				file << *it + '\n';
			}
		} catch (...) {
			return false;
		}
	} else return false;
	return true;
} 