#include "Header.h"

bool PutAnswerToClient(SOCKET sS, char* name, sockaddr* to, int* lto)
{
	string msg = name;
	int sizeTo = sizeof(*((SOCKADDR_IN*)to));

	return sendto(sS, name, msg.size() + 1, 0, to, sizeTo) == INVALID_SOCKET;
}