#include "../ClientS/Header.h"

int main()
{
	try
	{
		cout << "ClientS start\n";

		//wsastartup
		WSADATA wsadata;
		if (WSAStartup(MAKEWORD(2, 0), &wsadata) != 0)
			throwError(STARTUP_MSG_TEXT);

		//getserver
		SOCKADDR_IN from;
		int fLen;
		char call[10] = HELLO,
			hostname[50];
		int hnLen = sizeof(hostname);
		if (gethostname(hostname, hnLen) == SOCKET_ERROR)
			throwError(SOCKET_MSG_TEXT);

		if (GetServerByName(hostname, call, (sockaddr*)&from, &fLen))
		{
			cout << "ClientS gets server: "
				<< inet_ntoa(from.sin_addr) << ":" << htons(from.sin_port) << '\n';
		}


		if (WSACleanup() != 0)
			throwError(WSACLEANUP_MSG_TEXT);

	}
	catch (string errorMsg)
	{
		cout << '\n' + errorMsg + '\n';
	}

	system("pause");

	return 0;
}