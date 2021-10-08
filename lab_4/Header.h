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
#define WSACLEANUP_MSG_TEXT "Wsacleanup: "
#define BIND_MSG_TEXT "Bind: "
#define SOCKOPT_MSG_TEXT "Sockopt: "
#define RECVFROM_MSG_TEXT "Recvfrom: "
#define SENDTO_MSG_TEXT "Sendto: "
#define SERVER_IPV4 "192.168.43.31"
#define SERVER_PORT 3000
#define HELLO "Hello"

using namespace std;

string GetErrorMsgText(int code);
string SetErrorMsgText(string msgText, int code);
void throwError(const char* msg);

bool CheckServers(char* call, short port, sockaddr* from, int* lenFrom);
bool GetRequestFromClient(char* name, short port, sockaddr* from, int* flen);
bool PutAnswerToClient(char* name, sockaddr* to, int* lto);