#include "Client.hpp"
#include <exception>
using namespace TCP_Client_COM;

inline int Client::ConnectToServer(const char* msg) {
	if (WSAStartup(MAKEWORD(2, 2), &dat) != 0) {
		std::cerr << "WSA Startup failed!" << std::endl;
		return -1;
	}
	this->cSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (cSocket == INVALID_SOCKET) {
		std::cerr << "There was an error creating the client socket: " << WSAGetLastError() << " ... cleaning up " << std::endl;
		WSACleanup();
		return -1;
	}
	this->server_addr.sin_family = AF_INET;
	this->server_addr.sin_port = htons(443);
	this->server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

	if (connect(cSocket, reinterpret_cast<sockaddr*>(&server_addr), sizeof(server_addr)) == SOCKET_ERROR) {
		std::cerr << "There was an error while connecting to the server: " << WSAGetLastError() << std::endl;
		std::cout << "Closing socket and performing a cleanup due to an error!" << std::endl;
		closesocket(cSocket);
		WSACleanup();
		return -1;
	}
	std::cout << "Successfully connected to the server!" << std::endl;
	
	int sRes = send(cSocket, msg, strlen(msg), 0);
	if (sRes == SOCKET_ERROR) {
		std::cout << "Error sending message: " << WSAGetLastError() << std::endl;
	}
	closesocket(cSocket);
	WSACleanup();

	return (sRes == SOCKET_ERROR) ? -1 : 0;
}


int main() {
	Client c;
	std::string msg;
	std::cout << "Type a message, that the server will be receiving: " << std::endl;
	std::cin >> msg;
	const char* cmsg = msg.c_str();
	c.ConnectToServer(cmsg);
	return 0;
}