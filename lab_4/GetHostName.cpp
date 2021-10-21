#include "../lab_4/Header.h"

void GetHostName(char* hn, int hnlen)
{
	if (gethostname(hn, hnlen) == SOCKET_ERROR)
		throwError(GETHOSTNAME_MSG_TEXT);	
}
