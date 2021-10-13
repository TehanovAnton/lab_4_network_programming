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
		while (true)
		{
			if (GetRequestFromClient(name, SERVER_PORT, (SOCKADDR*)&from, &fromLen))
			{
				char* fromInetAddr = (char*)&(from.sin_addr);
				hostent* fromHostent;
				if ((fromHostent = gethostbyaddr(fromInetAddr, sizeof(fromInetAddr), AF_INET)) == NULL)
					throwError(GETHOSTBYADDR_MSG_TEXT);

				cout << "Server recived msg from: "
					<< inet_ntoa(from.sin_addr) << ":" << htons(from.sin_port)
					<< "; hostname: " << fromHostent->h_name << '\n';

				if (PutAnswerToClient(name, (SOCKADDR*)&from, &fromLen))
					cout << "Sent " << inet_ntoa(from.sin_addr) << ":" << htons(from.sin_port)
					<< "/ " << name << "\n\n";
			}
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