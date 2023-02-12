#ifndef LHAT_DEFINES_H
#define LHAT_DEFINES_H

#include <WinSock2.h>
#include <vector>
#include <string>
using namespace std;

struct User
{
	SOCKET socket;
	string address;
	string username;
	string rooms[32];
	int idNum;
	string permission;
};

struct Settings
{
	bool writeLogs;
	bool recordChats;
	bool forceAccount;
	bool allowRegister;
	bool lockServer;
};

#endif //LHAT_DEFINES_H