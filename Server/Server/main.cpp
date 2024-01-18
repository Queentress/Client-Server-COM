#include "Server.hpp"
using namespace TCP_Server_COM;

inline int Server::Connection(int port = 8080) {
	
	if (WSAStartup(MAKEWORD(2, 2), &dat) != 0) {
		std::cerr << "There was an error on the startup!" << std::endl;
		return -1;
	}
	this->sSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (sSocket == INVALID_SOCKET) {
		std::cerr << "There was an error on creating the socket: " << WSAGetLastError() << std::endl;
		WSACleanup();
		return -1;
	}

}

int main() {
	int port;
	std::cout << "Choose a port for the connection to open [8080 on default]: " << std::endl;
	std::cin >> port;
	return 0;
}