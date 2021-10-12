#include "Header.h"


bool GetServer(char* call, short port, sockaddr* from, int* lenFrom)
{
	//socket
	SOCKET cS;
	if ((cS = socket(AF_INET, SOCK_DGRAM, NULL)) == INVALID_SOCKET)
		throwError(SOCKET_MSG_TEXT);

	//setsockopt
	int optval = 1;
	if (setsockopt(cS, SOL_SOCKET, SO_BROADCAST, (char*)&optval, sizeof(int)) == SOCKET_ERROR)
		throwError(SOCKOPT_MSG_TEXT);

	//sendto
	SOCKADDR_IN all;
	all.sin_family = AF_INET;
	all.sin_addr.S_un.S_addr = INADDR_BROADCAST;
	all.sin_port = htons(port);
					 
	string call_msg = call;
	if (sendto(cS, call, call_msg.size() + 1, 0, (SOCKADDR*)&all, sizeof(all)) == SOCKET_ERROR)
		throwError(SENDTO_MSG_TEXT);

	cout << "Sent message: " << call << "; "
		<< inet_ntoa(all.sin_addr) << ":" << htons(all.sin_port) << "\n\n";

	//recvfrom	 
	SOCKADDR_IN sSAddrIn;
	int sizeSSAddrIn = sizeof(sSAddrIn);
	char buf[10];
	bool res_recvfrom;
	bool isCS = true;
	while (res_recvfrom = strcmp(buf, call) != 0 || isCS)
	{
		if (recvfrom(cS, buf, sizeof(buf), 0, (SOCKADDR*)&sSAddrIn, &sizeSSAddrIn) == SOCKET_ERROR)
			throwError(RECVFROM_MSG_TEXT);

		isCS = strcmp(inet_ntoa(sSAddrIn.sin_addr), WIRELESS_IPV4) == 0;
	}

	if (res_recvfrom = strcmp(buf, call) == 0)
	{
		*from = *((SOCKADDR*)&sSAddrIn);
		*lenFrom = sizeSSAddrIn;
	}

	if (closesocket(cS) != 0)
		throwError(CLOSESOCKET_MSG_TEXT);

	return res_recvfrom;
}