#include "Server.hpp"


using namespace TCP_Server_COM;

inline int Server::Connection() {
	
	if (WSAStartup(MAKEWORD(2, 2), &dat) != 0) {
		std::cerr << "There was an error on the startup!" << std::endl;
		std::cout << "Closing socket due to an error!" << std::endl;
		return -1;
	}
	this->sSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (sSocket == INVALID_SOCKET) {
		std::cerr << "There was an error on creating the socket: " << WSAGetLastError() << std::endl;
		std::cout << "Doing a cleanup due to an error!" << std::endl;
		WSACleanup();
		return -1;
	}

	sockaddr_in server_addr;
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = INADDR_ANY;
	server_addr.sin_port = htons(443);

	if (bind(sSocket, reinterpret_cast<sockaddr*>(&server_addr), sizeof(server_addr)) == SOCKET_ERROR) {
		std::cerr << "There was an error on binding the socket: " << WSAGetLastError() << std::endl;
		std::cout << "Closing socket and performing a cleanup due to an error!" << std::endl;
		closesocket(sSocket);
		WSACleanup();
		return -1;
	}

	if (listen(sSocket, SOMAXCONN) == SOCKET_ERROR) {
		std::cerr << "There was an error on the socket listener: " << WSAGetLastError() << std::endl;
		std::cout << "Closing socket and performing a cleanup due to an error!" << std::endl;
		closesocket(sSocket);
		WSACleanup();
		return -1;
	}

	std::cout << "Listening to 443" << std::endl;

	this->cSocket = accept(sSocket, nullptr, nullptr);
	if (cSocket == INVALID_SOCKET) {
		std::cerr << "There was an error on the connection with the client: " << WSAGetLastError() << std::endl;
		std::cout << "Closing socket and performing a cleanup due to an error!" << std::endl;
		closesocket(sSocket);
		WSACleanup();
		return -1;
	}

	std::cout << "Client has been connected" << std::endl;

	char buffer[1024];
	memset(buffer, 0, sizeof(buffer));
	int recMsg = recv(cSocket, buffer, sizeof(buffer), 0);
	if (recMsg == SOCKET_ERROR) {
		std::cout << "There was an error on receiving the message from the connected client: " << WSAGetLastError() << std::endl;
	}
	else {
		std::cout << "Received a message from the client: " << buffer << std::endl;
	}
	closesocket(cSocket);
	closesocket(sSocket);
	WSACleanup();

	return (recMsg == SOCKET_ERROR) ? -1 : 0;
	
}

int main() {
	Server serv;
	serv.Connection();
	return 0;
}