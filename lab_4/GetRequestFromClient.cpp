#include "Header.h"

bool GetRequestFromClient(SOCKET sS, char* name, short port, sockaddr* from, int* flen)
{
	char buf[10] = "";
	int sizeBuf = sizeof(buf);	
	int sizeFromAddrIn = sizeof( *( (SOCKADDR_IN*)from ) );

	bool getServName = false;
	int resRcvfrom;
	while (true)
	{
		if ((resRcvfrom = recvfrom(sS, buf, sizeBuf, 0, from, &sizeFromAddrIn)) == SOCKET_ERROR)
			throw SetErrorMsgText(RECVFROM_MSG_TEXT, WSAGetLastError());		


		if (getServName = strcmp(buf, name) == 0)
		{			
			*flen = resRcvfrom;			
			break;
		}
	}

	return getServName;
}
