#include "Header.h"

bool GetRequestFromClient(SOCKET sS, char* name, short port, sockaddr* from, int* flen)
{
	char buf[10] = "";

	bool getServName = false;
	while (true)
	{
		if (recvfrom(sS, buf, sizeof(buf), 0, from, flen) == SOCKET_ERROR)
			throw SetErrorMsgText(RECVFROM_MSG_TEXT, WSAGetLastError());		


		if (getServName = strcmp(buf, name) == 0)
			return getServName;
	}

	return getServName;
}
