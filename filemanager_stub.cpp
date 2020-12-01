#include "filemanager_stub.h"

fileManager_stub::fileManager_stub() {
	socket = initClient("127.0.0.1", 8081);
}

vector<string*>* fileManager_stub::listFiles() {
	
}

void fileManager_stub::readFile(char* fileName, char* &data, unsigned long int & dataLength) {
	int opType = OP_READ;

	//Se env�a el tipo de operaci�n que se realiza y despu�s se env�a el nombre del fichero a leer
	sendMSG(socket, &opType, sizeof(int));
	sendMSG(socket, fileName, strlen(fileName) + 1);

	//Se reciben los datos del fichero
	recvMSG(socket, (void**)&data, &dataLength);
}

void fileManager_stub::writeFile(char* fileName, char* data, unsigned long int dataLength) {
	int opType = OP_WRITE;

	//Se env�a el tipo de operaci�n nombre de fichero y contenido a escribir
	sendMSG(socket, &opType, sizeof(int));
	sendMSG(socket, fileName, strlen(fileName) + 1);
	sendMSG(socket, data, dataLength);
}

fileManager_stub::~fileManager_stub() {
	int opType = OP_END;

	//Se env�a el tipo de operaci�n que es
	sendMSG(socket, &opType, sizeof(int));
}