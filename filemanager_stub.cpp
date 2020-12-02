#include "filemanager_stub.h"

fileManager_stub::fileManager_stub() {
	socket = initClient("127.0.0.1", 8081);
}

vector<string*>* fileManager_stub::listFiles() {
	int opType = OP_LIST;
	char* buffer = nullptr;
	int bufferLength = 0;

	//Creo una listade copia
	std::vector<string*>* fileList = new vector<string*>();
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
		recvMSG(socket, (void**)&buffer, bufferLength);
		fileList->push_back(new string(buffer));
		delete[] buffer;
	}

	return fileList;
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