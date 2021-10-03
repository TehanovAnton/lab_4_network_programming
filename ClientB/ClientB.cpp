#include "Header.h"

int main()
{
	try
	{
		cout << "Client start";

		//wsastartup
		WSADATA wsadata;
		if (WSAStartup(MAKEWORD(2, 0), &wsadata) != 0)
			throwError(STARTUP_MSG_TEXT);

		//socket
		SOCKET cS;
		if ((cS = socket(AF_INET, SOCK_DGRAM, NULL)) == INVALID_SOCKET)
			throwError(SOCKET_MSG_TEXT);

		//bind
		SOCKADDR_IN cSAddrIn;
		cSAddrIn.sin_family = AF_INET;
		cSAddrIn.sin_addr.S_un.S_addr = inet_addr(WIRELESS_IPV4);
		cSAddrIn.sin_port = htons(PORT);

		if (bind(cS, (SOCKADDR*)&cSAddrIn, sizeof(SOCKADDR_IN)) != 0)
			throw SetErrorMsgText("Bind: ", WSAGetLastError());

		int optval = 1;
		if (setsockopt(cS, SOL_SOCKET, SO_BROADCAST, (char*)&optval, sizeof(int)) == SOCKET_ERROR)
			throwError(SOCKOPT_MSG_TEXT);

		//getserver
		SOCKADDR_IN from;
		int lenFrom = sizeof(from);
		char call[10] = HELLO;
		GetServer(cS, call, PORT, (sockaddr*)&from, &lenFrom);
		
		if (closesocket(cS) != 0)
			throwError(CLOSESOCKET_MSG_TEXT);

		if (WSACleanup() != 0)
			throwError(WSACLEANUP_MSG_TEXT);

	}
	catch (string errorMsg)
	{
		cout << '\n' + errorMsg;
	}
}