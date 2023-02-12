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

//��ƽ̨����
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
#endif //��ƽ̨��������

class LhatServer
{
private:
	const string VERSION; //�������汾��
	string networkIP; //�������󶨵�ַ
	int networkPort; //�������󶨶˿�
	string defaultRoomName; //Ĭ����������
	SOCKET serverSocket; //���������׽���
	map<string, User> userConnections; //�û������б���Ϊ�û�����ֵΪ�û��ṹ��
	vector<string> registeredUsers; //��SQL���ݿ��д��ڵ��û�
	string handlingMessages[64]; //���������Ϣ�б�
	string chattingRooms[256]; //�������б�
	Settings serverSettings; //���������ýṹ��
public:
	LhatServer();
	void run();
	int createConnection(SOCKET newSocket);
	int serveClient(int selectorKey, bool socketMask);
	int processMessage(string messageString, SOCKET clientSocket, sockaddr_in clientAddress);
	void processNewLogin(SOCKET newSocket, sockaddr_in newAddress, string userInfo);
	string* getOnlineUsers(); //��ס��Ҫ���ص������������Ϊstatic��Ȼ�󷵻�����ָ��
	string* getManagers(); //ͬ��
	int closeConnection(SOCKET closedSocket, sockaddr_in closedAddress);
	int log(string logContent, string contentEnd = "\n", bool showTime = true);
	int record(string chatContent);
};

#endif //LHAT_SERVER_H