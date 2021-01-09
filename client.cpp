#include "utils.h"
#include <string>
#include <vector>
#include "filemanager_stub.h"

int main(int argc, char** argv) {
	fileManager_stub* op = new fileManager_stub();
	std::vector <std::string*>* filesList = nullptr;
	char* data = nullptr;
	std::string fileName;
	std::string fileData;
	int filePos = -1;
	int dataLength = 0;
	bool bucle = false;
	char opType;

	while (!bucle) {
		std::cout << "l->listar ficheros" << std::endl;
		std::cout << "u->escribe en el fichero" << std::endl;
		std::cout << "d->leer fichero" << std::endl;
		std::cout << "s->salir del programa" << std::endl;
		std::cout << "Introduce operacion:" << std::endl;
		std::cin >> opType;
		switch (opType) {
			case 'l': {
				std::cout << "Listando ficheros:" << std::endl;
				filesList = op->listFiles();
				for (unsigned int i = 0; i < filesList->size(); ++i) {
					std::cout << "Fichero: " << filesList->at(i)->c_str() << std::endl;
				}
			}
			break;
			case 'u': {
				std::cout << "Nombre del fichero:" << std::endl;
				std::cin >> fileName;
				std::cout << "Contenido a escribir en el fichero:" << std::endl;
				std::cin >> fileData;
				dataLength = fileData.length() + 1;
				op->writeFile(const_cast<char*>(fileName.c_str()), const_cast<char*>(fileData.c_str()), dataLength);
				delete[] data;
				dataLength = 0;
			}
			break;
			case 'd': {
				std::cout << "Numero del fichero de la lista:" << std::endl;
				std::cin >> filePos;
				if (filePos >= filesList->size() + 1 || filePos < 1) {
					std::cout << "No existe el fichero prueba a recargar la lista" << std::endl;
				}
				else {
					std::cout << "Descargando fichero" << std::endl;
					op->readFile(&(*(filesList->at(filePos - 1)))[0], data, dataLength);
					FILE* f = fopen(&(*(filesList->at(filePos - 1)))[0], "w");
					fwrite(data, dataLength, 1, f);
					fclose(f);
				}
			}
			break;
			case 's': {
				std::cout << "Cerrando conexión" << std::endl;
				bucle = true;
				op->terminar();
			}
			default: {
				std::cout << "Error en el tipo de operacion";
			}
		}
	}
}