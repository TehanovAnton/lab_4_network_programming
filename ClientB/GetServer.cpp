#include "Header.h"


bool GetServer(SOCKET cS, char* call, short port, sockaddr* from, int* lenFrom)
{
	//sendto
	SOCKADDR_IN all;
	all.sin_family = AF_INET;
	all.sin_addr.S_un.S_addr = INADDR_BROADCAST;
	all.sin_port = htons(port);
					 
	if (sendto(cS, call, sizeof(call), 0, (SOCKADDR*)&all, sizeof(all)) == SOCKET_ERROR)
		throwError(SENDTO_MSG_TEXT);

	//recvfrom
	char buf[10];
	if (recvfrom(cS, buf, sizeof(buf), 0, from, lenFrom) == SOCKET_ERROR)
		throwError(RECVFROM_MSG_TEXT);

	return strcmp(buf, call) == 0;
}