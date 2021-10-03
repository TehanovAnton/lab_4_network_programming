#include "Header.h"

bool PutAnswerToClient(char* name, sockaddr* to, int* lto)
{

	SOCKET sS;
	if ((sS = socket(AF_INET, SOCK_DGRAM, NULL)) == INVALID_SOCKET)
		throw SetErrorMsgText(SOCKET_MSG_TEXT, WSAGetLastError());

	string msg = name;
	bool res_sentto = sendto(sS, name, msg.size() + 1, 0, to, *lto) != INVALID_SOCKET;

	if (closesocket(sS))
		throw SetErrorMsgText(CLOSESOCKET_MSG_TEXT, WSAGetLastError());

	return res_sentto;
}