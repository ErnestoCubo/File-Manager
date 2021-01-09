#include "filemanager_stub.h"

fileManager_stub::fileManager_stub() {
	socket = initClient("10.0.5.4", 8081);
}

std::vector<std::string*>* fileManager_stub::listFiles() {
	int opType = OP_LIST;
	char* buffer = 0x00;
	int bufferLength = 0;

	//Creo una listade copia
	std::vector<std::string*>* fileList = new std::vector<std::string*>();
	int listSize;

	/*Se env�a primero el tipo de operaci�n luego se recibe el tama�o de la lista se guarda el 
	tama�o y se libera el buffer*/
	sendMSG(socket, &opType, sizeof(int));
	recvMSG(socket, (void**)&buffer, &bufferLength);
	listSize = ((int*)buffer)[0];
	delete[] buffer;

	/*Una vez recibido el tama�o se va recibiendo fichero por fichero que se ir�n  metiendo en la 
	copia de la lista original*/
	for(int i = 0; i < listSize; i++) {
		recvMSG(socket, (void**)&buffer, &bufferLength);
		fileList->push_back(new std::string(buffer));
		delete[] buffer;
	}

	return fileList;
}

void fileManager_stub::readFile(char* fileName, char* &data, int &dataLength) {
	int opType = OP_READ;
	int length = 0;
	//Se env�a el tipo de operaci�n que se realiza y despu�s se env�a el nombre del fichero a leer
	sendMSG(socket, &opType, sizeof(int));
	sendMSG(socket, fileName, strlen(fileName) + 1);

	//Se reciben los datos del fichero
	recvMSG(socket, (void**)&data, &length);
	dataLength = length;
}

void fileManager_stub::writeFile(char* fileName, char* data, unsigned long int dataLength) {
	int opType = OP_WRITE;

	//Se env�a el tipo de operaci�n nombre de fichero y contenido a escribir
	sendMSG(socket, &opType, sizeof(int));
	sendMSG(socket, fileName, strlen(fileName) + 1);
	sendMSG(socket, data, dataLength);
}

void fileManager_stub::freeListedFiles(std::vector<std::string*>* fileList) {
	for (std::vector<std::string*>::iterator i = fileList->begin(); i != fileList->end(); ++i) {
		delete *i;
	}
	delete fileList;
}



void fileManager_stub::terminar() {
	int opType = OP_END;

	//Se env�a el tipo de operaci�n que es
	sendMSG(socket, &opType, sizeof(int));
}