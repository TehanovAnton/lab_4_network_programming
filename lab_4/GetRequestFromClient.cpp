#include "Header.h"

bool GetRequestFromClient(char* name, short port, sockaddr* from, int* flen)
{
	SOCKET sS = socket(AF_INET, SOCK_DGRAM, NULL);
	if (sS == INVALID_SOCKET)
		throw SetErrorMsgText(SOCKET_MSG_TEXT, WSAGetLastError());

	SOCKADDR_IN sSAddrIn;
	sSAddrIn.sin_family = AF_INET;
	sSAddrIn.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
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
