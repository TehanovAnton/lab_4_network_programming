#include "Header.h"

int main()
{
	try
	{
		WSADATA wsadata;
		if (WSAStartup(MAKEWORD(2, 0), &wsadata) != 0)
			throw SetErrorMsgText(STARTUP_MSG_TEXT, WSAGetLastError());

		SOCKADDR_IN from; 
		int fromLen;	
		char name[10] = HELLO;
		if (GetRequestFromClient(name, SERVER_PORT, (SOCKADDR*)&from, &fromLen))
		{
			cout << "Recived msg from: "
				<< inet_ntoa(from.sin_addr) << ":" << htons(from.sin_port) << "\n\n";			

			if (PutAnswerToClient(name, (SOCKADDR*)&from, &fromLen))
				cout << "Sent " << inet_ntoa(from.sin_addr) << ":" << htons(from.sin_port)
					<< "/ " << name;
		}

		if (WSACleanup() != 0)
			throw SetErrorMsgText(WSACLEANUP_MSG_TEXT, WSAGetLastError());

	}
	catch (string errorMsg)
	{
		cout << '\n' + errorMsg;
	}

	system("pause");
	return 0;
}