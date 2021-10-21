#include "..\ClientS\Libs.h"
#include "..\ClientS\Defines.h"
#include "..\ClientS\Prototypes.h"

bool GetServerByName(char* name, char* call, sockaddr* from, int* flen)
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
	all.sin_port = htons(PORT);

	string call_msg = call;
	if (sendto(cS, call, call_msg.size() + 1, 0, (SOCKADDR*)&all, sizeof(all)) == SOCKET_ERROR)
		throwError(SENDTO_MSG_TEXT);

	cout << "Sent message: " << call << "; "
		<< inet_ntoa(all.sin_addr) << ":" << htons(all.sin_port) << '\n';

	//recvfrom	 
	SOCKADDR_IN sSAddrIn;
	int sizeSSAddrIn = sizeof(sSAddrIn);
	char buf[10];
	bool res_recvfrom;
	bool isCS = true;
	while (res_recvfrom = strcmp(buf, call) != 0)
	{
		if (recvfrom(cS, buf, sizeof(buf), 0, (SOCKADDR*)&sSAddrIn, &sizeSSAddrIn) == SOCKET_ERROR)
			throwError(RECVFROM_MSG_TEXT);
	}

	//check call
	if (res_recvfrom = strcmp(buf, call) == 0)
	{
		hostent* hostByAddr;
		char* addr = inet_ntoa(sSAddrIn.sin_addr);
		cout << "Someine answer, addr: " << inet_ntoa(sSAddrIn.sin_addr) << '\n';

		char* serverInetAddr = (char*)&(sSAddrIn.sin_addr);
		if ((hostByAddr = gethostbyaddr(serverInetAddr, sizeof(serverInetAddr), AF_INET)) == NULL)
			throwError(GETHOSTBYNAME_MSG_TEXT);

		//check hostname		
		string strname = name;
		if (res_recvfrom &= strncmp(name, hostByAddr->h_name, strname.length()) == 0)
		{
			*from = *((SOCKADDR*)&sSAddrIn);
			*flen = sizeSSAddrIn;
		}
	}

	if (closesocket(cS) != 0)
		throwError(CLOSESOCKET_MSG_TEXT);

	return res_recvfrom;


	//char hostname[30];
	//int hnLen = sizeof(hostname);
	//if (gethostname(hostname, hnLen) == SOCKET_ERROR)
	//	throwError(SOCKET_MSG_TEXT);

	//hostent* hostByName;
	//if ((hostByName = gethostbyname(hostname)) == NULL)
	//	throwError(GETHOSTBYNAME_MSG_TEXT);
	//cout << hostByName->h_name;

	//char** addrListByName = hostByName->h_addr_list;
	//char str[] = "192.168.1371";

	//hostent* hostByAddr = gethostbyaddr(str, sizeof(str), AF_INET);
	//cout << hostByAddr->h_name;

	//return false;
}