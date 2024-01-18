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
		inline int Connection();
	private:
		WSADATA dat;
		SOCKET sSocket;
		SOCKET cSocket;
	};
}