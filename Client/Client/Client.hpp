#include <iostream>
#include <WinSock2.h>
#pragma comment(lib, "ws2_32.lib")

namespace TCP_Client_COM {
	class Client {
	private: 
		SOCKET cSocket;
		SOCKET sSocket;
		WSADATA dat;
		sockaddr_in server_addr;
	public:
		Client();
		inline int ConnectToServer(const char* msg);
	};

	Client::Client() { };
}