#pragma once
#include <iostream>
#include <cstring>
#define _WIN32_WINNT 0x501
#include <WinSock2.h>

namespace TCP_Server_COM {
	class Server
	{
	public:
		Server();
		~Server();
		void Connection();
	private:
		WSADATA dat;
		SOCKET sSocket;
		const char buffer[1024];
	};
}