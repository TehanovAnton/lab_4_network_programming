#include "Header.h"

int main()
{
	try
	{
		cout << "Client start\n\n";

		//wsastartup
		WSADATA wsadata;
		if (WSAStartup(MAKEWORD(2, 0), &wsadata) != 0)
			throwError(STARTUP_MSG_TEXT);

		//getserver
		SOCKADDR_IN from;
		int lenFrom;
		char call[10] = HELLO;
		if (GetServer(call, PORT, (sockaddr*)&from, &lenFrom))
			cout << "Client recived msg from: "
				<< inet_ntoa(from.sin_addr) << ":" << htons(from.sin_port) << "\n\n";


		if (WSACleanup() != 0)
			throwError(WSACLEANUP_MSG_TEXT);

	}
	catch (string errorMsg)
	{
		cout << '\n' + errorMsg;
	}

	system("pause");

	return 0;
}