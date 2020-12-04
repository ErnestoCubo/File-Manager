#include "utils.h"
#include "fileManager_stub.h"

int main(int argc, char** argv) {
	fileManager_stub* op = new fileManager_stub();
	std::vector <string*>* filesList = nullptr;
	char* data = nullptr;
	char* fileName = nullptr;
	unsigned long int dataLength = 0;
	bool bucle = false;
	std::string opType = nullptr;

	while (!bucle) {
		std::cout << "ls->listar ficheros" << std::endl;
		std::cout << "upload->nuevo fichero" << std::endl;
		std::cout << "download->leer fichero" << std::endl;
		std::cout << "Introduce operacion:" << std::endl;
		std::cin >> opType;
		switch (std::stoi(opType)) {
		case std::stoi("ls"): {
			std::cout << "Listando ficheros:" << std::endl;
			filesList = op->listFiles();
			for (std::vector<string*>::iterator it = fileList->begin(); it != fileList->end(); it++) {
				std::cout<<it<<std::endl
			}
		}
		break;
		case std::stoi("upload"): {
			std::cout << "Nombre del fichero:" << std::endl;
			std::cin >> fileName;
			std::cout << "Contenido a escribir en el fichero:" << std::endl;
			std::cin >> data;
			dataLength = std::strlen(data) + 1;
			op->writeFile(fileName, data, dataLength);
			delete[] data;
			delete[] fileName;
			dataLength = 0;
		}
		break;
		case std::stoi("download"): {
			std::cout << "Nombre del fichero:" << std::endl;
			std::cin >> fileName;
			for (std::vector<string*>::iterator it = fileList->begin(); it != fileList->end(); it++) {
				if (std::strcmp(fileName, it) == 0) {
					op->readFile(fileName, data, dataLength);
				}
				else {
					std::cout << "No se encontro el fichero" << std::endl;
				}
			}
			delete[] fileName;
		}
		default: {
			std::cout<<"Error en el tipo de operacion"
		}
		}
	}
}