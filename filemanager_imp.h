#ifndef FILEMANAGER_IMP_H
#define FILEMANAGER_IMP_H
#include "filemanager.h"
#include "filemanager_stub.h"

class fileManager_imp {

	int client_fd = 0;
	FileManager* op;
public:
	bool salir = false;
	fileManager_imp(int socket_fd);
	void recvOp();
	~fileManager_imp();

};

#endif //FILEMANAGER_IMP_H