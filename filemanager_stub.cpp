#include "filemanager_stub.h"

fileManager_stub::fileManager_stub() {
	socket = initClient("127.0.0.1", 8081);
}

vector<string*>* fileManager_stub::listFiles() {
	
}

void fileManager_stub::readFile(char* fileName, char* &data, unsigned long int & dataLength) {
	int opType = OP_READ;

	//Se envía el tipo de operación que se realiza y después se envía el nombre del fichero a leer
	sendMSG(socket, &opType, sizeof(int));
	sendMSG(socket, fileName, strlen(fileName) + 1);

	//Se reciben los datos del fichero
	recvMSG(socket, (void**)&data, &dataLength);
}

void fileManager_stub::writeFile(char* fileName, char* data, unsigned long int dataLength) {
	int opType = OP_WRITE;

	//Se envía el tipo de operación nombre de fichero y contenido a escribir
	sendMSG(socket, &opType, sizeof(int));
	sendMSG(socket, fileName, strlen(fileName) + 1);
	sendMSG(socket, data, dataLength);
}

fileManager_stub::~fileManager_stub() {
	int opType = OP_END;

	//Se envía el tipo de operación que es
	sendMSG(socket, &opType, sizeof(int));
}