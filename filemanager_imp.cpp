#include "filemanager_imp.h"

fileManager_imp::fileManager_imp(int socket_fd) {
	client_fd = socket_fd;
	op = new FileManager("./dirprueba/");
}

void fileManager_imp::recvOp() {
	char* buffer = 0x00;
	int bufferLen = 0;
	int opType = 0;

	//Se recibe el tipo de operación de la que se trata y se libera el buffer
	recvMSG(client_fd, (void**)&buffer, &bufferLen);
	opType = ((int*)buffer)[0];
	delete[] buffer;

	switch (opType) {
	case OP_END:{
		cout << "tarea terminada" << endl;
		this->salir = true;
	}
	break;
	case OP_LIST: {
		//Se crean una copia de la lista, otra del tamaño y otra del elemento
		int listSize = 0;
		string* copia = nullptr;
		vector<string*>* fileList = op->listFiles();

		//Se envía el tamaño
		listSize = fileList->size();
		sendMSG(client_fd, &listSize, sizeof(int));

		//Se envía el dato del principio de la lista y se elimina para coger el siguiente con erase se libera la memoria
		for (std::vector<string*>::iterator it = fileList->begin(); it != fileList->end();it++){
			copia = *it;
			sendMSG(client_fd, copia->c_str(), copia->length() + 1);
		}
	}
	break;
	case OP_READ: {
		char* fileName = 0x00;
		char *data = 0x00;
		unsigned long int dataLength = 0;

		//Se recibe el dato del nombre dle fichero se copia y se libera el buffer
		recvMSG(client_fd, (void**)&fileName, &bufferLen);

		//Se realiza la operación de leer el fichero
		op->readFile(fileName, data, dataLength);

		//Se devuelven los datos leidos del fichero
		sendMSG(client_fd, data, dataLength);
	}
	break;
	case OP_WRITE: {
		char* fileName = 0x00;
		char *data = 0x00;
		unsigned long int dataLength = 0;

		//Se recibe el nombre del fichero, se copia y se libera el fichero
		recvMSG(client_fd, (void**)&fileName, &bufferLen);

		/*Se  recibe el siguiente dato que es el contenido que se quiere escribir
		se copian su tamaño y su contenido y se libera el buffer*/
		recvMSG(client_fd, (void**)&buffer, &bufferLen);
		data = (char*)buffer;
		delete[] buffer;
		dataLength = bufferLen;

		//Se realiza la operación con los datos obenidos
		op->writeFile(fileName, data, dataLength);
		delete[] data;
	}
	break;
	default: {
		std::cout << "Error operacion no existente" << std::endl;
		exit(0);
	}
	break;
	}
}

fileManager_imp::~fileManager_imp(){
	closeConnection(client_fd);
	delete op;
}
