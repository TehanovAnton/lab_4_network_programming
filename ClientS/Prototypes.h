#pragma once
#include "../ClientS/Libs.h"

string GetErrorMsgText(int code);
string SetErrorMsgText(string msgText, int code);
void throwError(const char* msg);

bool GetServer(char* call, short port, sockaddr* from, int* lenFrom);
bool GetServerByName(char* name, char* call, sockaddr* from, int* flen);
