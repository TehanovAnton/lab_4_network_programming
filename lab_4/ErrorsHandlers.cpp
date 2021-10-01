#include "Header.h"

string GetErrorMsgText(int code)
{
	string msgText;
	switch (code)
	{
	case WSAEINTR: msgText = "Function interrupted";
		break;
	case WSAEACCES: msgText = "Permission denied";
		break;
	case WSAEFAULT: msgText = "Wrong address";
		break;
	case WSASYSCALLFAILURE: msgText = "System call abort";
		break;
	default: msgText = "***ERROR***";
		break;
	}

	return msgText;
}
string SetErrorMsgText(string msgText, int code)
{
	return msgText + GetErrorMsgText(code);
}