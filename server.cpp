#include "utils.h"
#include "filemanager_imp.h"

void clientHandler(int clientID) {
	fileManager_imp* op = new fileManager_imp(clientID);
	while (!op->salir) {
		op->recvOp();
	}
	delete op;
}

int main(int argc, char**argv) {
	int server_fd = initServer(8081);
	while (true) {
		if (checkNewConnections()) {
			int newID = getNewConnection();
			std::thread* client = new std::thread(clientHandler, newID);
		}
		usleep(1000);
	}
	return 0;
}