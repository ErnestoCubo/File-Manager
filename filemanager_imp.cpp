#include "filemanager_imp.h"

filemanager_imp::filemanager_imp(int socket_fd) {
	client_fd = socket_fd;
	op = new FileManager();
}

void recvOp() {
	char buffer = nullptr;
	int buferLen = 0;
	int opType = 0;

	//Se recibe el tipo de poeració de la que se trata y se libera el buffer
	recvMSG(client_fd, (void**)&buffer, &bufferLen);
	opType = ((int*)buffer)[0];
	delete[] buffer;

	switch (opType) {
	case OP_END:{
		this->salir = true;
	}
		break;
	case OP_LIST: {
		
	}
	case OP_READ: {
		char* fileName = nullptr;
		char *data = nullptr;
		unsigned long int *dataLenght = 0;

		//Se recibe el dato del nombre dle fichero se copia y se libera el buffer
		recvMSG(client_fd, (void**)&buffer, &bufferLen);
		fileName = buffer;
		delete[] buffer;

		//Se realiza la operación de leer el fichero
		op->readFile(fileName, data, dataLength);

		//Se devuelven los datos leidos del fichero
		sendMSG(client_fd, data, dataLength);
	}
	case OP_WRITE: {
		char* fileName = nullptr;
		char *data = nullptr;
		unsigned long int *dataLenght = 0;

		//Se recibe el nombre del fichero, se copia y se libera el fichero
		recvMSG(socket, (void**)&buffer, &buferLen);
		filename = (char*)buffer;
		delete[] buffer;

		/*Se  recibe el siguiente dato que es el contenido que se quiere escribir
		se copian su tamaño y su contenido y se libera el buffer*/
		recvMSG(socket, (void**)&buffer, &buferLen);
		data = (char*)buffer;
		delete[] buffer;
		dataLength = buferLen;

		//Se realiza la operación con los datos obenidos
		op->writeFile(fileName, data, dataLength);
	}
	default: {
		std::cout << "Error operacíon no existente" << std::endl;
		exit(0);
		break;
	}

	}
}