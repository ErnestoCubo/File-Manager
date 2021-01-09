#ifndef FILEMANAGER_STUB_H
#define FILEMANAGER_STUB_H

#include "utils.h"

#define OP_END 0
#define OP_LIST 1
#define OP_READ 2
#define OP_WRITE 3
#define OP_FREE 4

class fileManager_stub {
	int socket = 0;
public:
	fileManager_stub();
	std::vector<std::string*>* listFiles();
	void readFile(char* fileName, char* &data, int &dataLength);
	void writeFile(char* fileName, char* data, unsigned long int dataLength);
	void freeListedFiles(std::vector<std::string*>* fileList);
	void terminar();
};

#endif //FILEMANAGER_STUB_H