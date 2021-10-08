#include "Header.h"

bool GetRequestFromClient(char* name, short port, sockaddr* from, int* flen)
{
	SOCKADDR_IN oSAdrIn;
	int sizeOSAdrIn = sizeof(oSAdrIn);
	char call[10] = HELLO;
	if (CheckServers(call, SERVER_PORT, (SOCKADDR*)&oSAdrIn, &sizeOSAdrIn))
	{
		cout << "!!!Warning!!! There is another server with the same call: "
			<< inet_ntoa(oSAdrIn.sin_addr) << ":" << htons(oSAdrIn.sin_port) << "\n\n";
	}

	SOCKET sS = socket(AF_INET, SOCK_DGRAM, NULL);
	if (sS == INVALID_SOCKET)
		throw SetErrorMsgText(SOCKET_MSG_TEXT, WSAGetLastError());

	SOCKADDR_IN sSAddrIn;
	sSAddrIn.sin_family = AF_INET;
	sSAddrIn.sin_addr.S_un.S_addr = inet_addr(SERVER_IPV4);
	sSAddrIn.sin_port = htons(port);
	if (bind(sS, (SOCKADDR*)&sSAddrIn, sizeof(SOCKADDR_IN)) != 0)
		throw SetErrorMsgText(BIND_MSG_TEXT, WSAGetLastError());

	cout << "Server running => " << inet_ntoa(sSAddrIn.sin_addr) << ":" << htons(sSAddrIn.sin_port) << "\n\n";

	SOCKADDR_IN fSAddrIn;
	int sizeFSAddrIn = sizeof(sSAddrIn);
	bool getServName = false;
	char buf[10] = "";
	while (true)
	{

		if (recvfrom(sS, buf, sizeof(buf), 0, (SOCKADDR*)&fSAddrIn, &sizeFSAddrIn) == SOCKET_ERROR)
			throw SetErrorMsgText(RECVFROM_MSG_TEXT, WSAGetLastError());		

		if (getServName = strcmp(buf, name) == 0)
		{
			*from = *((SOCKADDR*)&fSAddrIn);
			*flen = sizeFSAddrIn;
			break;
		}
	}

	if (closesocket(sS) != 0)
		throw SetErrorMsgText(CLOSESOCKET_MSG_TEXT, WSAGetLastError());

	return getServName;
}
