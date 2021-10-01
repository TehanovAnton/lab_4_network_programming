#include "Header.h"

int main()
{
	try
	{
		WSADATA wsadata;
		if (WSAStartup(MAKEWORD(2, 0), &wsadata) != 0)
			throw SetErrorMsgText(STARTUP_MSG_TEXT, WSAGetLastError());

		SOCKET sS = socket(AF_INET, SOCK_DGRAM, NULL);
		if (sS == INVALID_SOCKET)
			throw SetErrorMsgText(SOCKET_MSG_TEXT, WSAGetLastError());

		SOCKADDR_IN sSAddrIn;
		sSAddrIn.sin_family = AF_INET;
		sSAddrIn.sin_addr.S_un.S_addr = inet_addr(SERVER_IPV4);
		sSAddrIn.sin_port = htons(SERVER_PORT);
		if (bind(sS, (SOCKADDR*)&sSAddrIn, sizeof(SOCKADDR_IN)) != 0)
			throw SetErrorMsgText(BIND_MSG_TEXT, WSAGetLastError());

		cout << "Server running => " << inet_ntoa(sSAddrIn.sin_addr) << ":" << htons(sSAddrIn.sin_port) << "\n\n";


		char name[10] = HELLO;
		SOCKADDR_IN from; 
		int fromLen;		
		if (GetRequestFromClient(sS, name, SERVER_PORT, (SOCKADDR*)&from, &fromLen))
		{
			cout << "Recived msg from: "
				<< inet_ntoa(from.sin_addr) << ":" << htons(from.sin_port) << "\n\n";			

			if (PutAnswerToClient(sS, name, (SOCKADDR*)&from, &fromLen))
				cout << "Sent " << inet_ntoa(from.sin_addr) << ":" << htons(from.sin_port) << "/ "
					<< name;
		}


		if (closesocket(sS) != 0)
			throw SetErrorMsgText(CLOSESOCKET_MSG_TEXT, WSAGetLastError());

		if (WSACleanup() != 0)
			throw SetErrorMsgText(CLOSESOCKET_MSG_TEXT, WSAGetLastError());

	}
	catch (string errorMsg)
	{
		cout << '\n' + errorMsg;
	}
}