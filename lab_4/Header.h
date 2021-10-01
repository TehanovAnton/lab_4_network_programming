#pragma once
#define _CRT_SECURE_NO_WARNINGS
#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include<WinSock2.h>
#include<WS2tcpip.h>
#pragma comment(lib, "WS2_32.lib")
#include <iostream>

#define STARTUP_MSG_TEXT "Startup: "
#define SOCKET_MSG_TEXT "Socket: "
#define CLOSESOCKET_MSG_TEXT "Closesocket: "
#define BIND_MSG_TEXT "Bind: "
#define RECVFROM_MSG_TEXT "Recvfrom: "
#define SENDTO_MSG_TEXT "Sendto: "
#define SERVER_IPV4 "127.0.0.1"
#define SERVER_PORT 3000
#define HELLO "123456789"

using namespace std;

string GetErrorMsgText(int code);
string SetErrorMsgText(string msgText, int code);

bool GetRequestFromClient(SOCKET sS, char* name, short port, sockaddr* from, int* flen);
bool PutAnswerToClient(SOCKET sS, char* name, sockaddr* to, int* lto);