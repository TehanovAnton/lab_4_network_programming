#pragma once
#include "Libs.h"


string GetErrorMsgText(int code);
string SetErrorMsgText(string msgText, int code);
void throwError(const char* msg);

void GetHostName(char* hn, int hnlen);
bool CheckServers(char* call, short port, sockaddr* from, int* lenFrom);
bool GetRequestFromClient(char* name, short port, sockaddr* from, int* flen);
bool PutAnswerToClient(char* name, sockaddr* to, int* lto);
