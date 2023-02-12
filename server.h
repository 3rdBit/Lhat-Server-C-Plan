#ifndef LHAT_SERVER_H
#define LHAT_SERVER_H

#include "json/json.h"
#include "md5/md5.h"
#include "defines.h"
#include <cstdio>
#include <string>
#include <ctime>
#include <thread>
#include <map>
#include <vector>
#include "sqlite3/sqlite3.h"

#pragma comment(lib, "jsoncpp.lib")

//跨平台操作
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
#include <WinSock2.h>
#include <Windows.h>
#pragma comment(lib, "ws2_32.lib")
#elif __linux__
#include <sys/socket.h>
#include <unistd.h>
#else
printf("Error: Unknown Operating System Type.");
printf("Only Microsoft Windows and Linux is supported.");
#endif //跨平台操作结束

class LhatServer
{
private:
	const string VERSION; //服务器版本号
	string networkIP; //服务器绑定地址
	int networkPort; //服务器绑定端口
	string defaultRoomName; //默认聊天室名
	SOCKET serverSocket; //服务器主套接字
	map<string, User> userConnections; //用户连接列表，键为用户名，值为用户结构体
	vector<string> registeredUsers; //在SQL数据库中存在的用户
	string handlingMessages[64]; //待处理的消息列表
	string chattingRooms[256]; //聊天室列表
	Settings serverSettings; //服务器设置结构体
public:
	LhatServer();
	void run();
	int createConnection(SOCKET newSocket);
	int serveClient(int selectorKey, bool socketMask);
	int processMessage(string messageString, SOCKET clientSocket, sockaddr_in clientAddress);
	void processNewLogin(SOCKET newSocket, sockaddr_in newAddress, string userInfo);
	string* getOnlineUsers(); //记住，要返回的数组必须声明为static，然后返回它的指针
	string* getManagers(); //同理
	int closeConnection(SOCKET closedSocket, sockaddr_in closedAddress);
	int log(string logContent, string contentEnd = "\n", bool showTime = true);
	int record(string chatContent);
};

#endif //LHAT_SERVER_H