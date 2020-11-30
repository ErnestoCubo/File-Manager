#include "filemanager_stub.h"

fileManager_stub::fileManager_stub() {
	socket = initClient("127.0.0.1", 8081);
}

vector<string*>* fileManager_stub::listFiles() {
	
}

void fileManager_stub::readFile(char* fileName, char* &data, unsigned long int & dataLength) {
	int opType = OP_READ;
	sendMSG(socket, &opType, sizeof(int));
	sendMSG(socket, fileName, strlen(fileName) + 1);
}

void fileManager_stub::writeFile(char* fileName, char* data, unsigned long int dataLength) {

}

fileManager_stub::~fileManager_stub() {
	int opType = OP_END;
	sendMSG(socket, &opType, sizeof(int));
}