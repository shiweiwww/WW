// header.h: 标准系统包含文件的包含文件，
// 或特定于项目的包含文件
//

//#pragma once
//
//#define WIN32_LEAN_AND_MEAN             // 从 Windows 头文件中排除极少使用的内容
//// Windows 头文件
//#include <windows.h>
//#include<string>
//using namespace std;
//void sendTextmsg(wstring wsWxId,wstring wsTextMsg);
//void dispatch(wstring wid, wstring msg);

// header.h: 标准系统包含文件的包含文件，
// 或特定于项目的包含文件
//

#pragma once

#define WIN32_LEAN_AND_MEAN             // 从 Windows 头文件中排除极少使用的内容
// Windows 头文件
#include <windows.h>
#include<string>
using namespace std;

#ifdef _DEBUG
	#define RECOR_DPATH "D:\\myfile.txt"
	#define SEARCH_DIRS "C:\\Users\\swxxx\\Desktop\\temp\\2021-01"
	#define ROBOT L"@robot_demox"
	#define ROBOT_LEN 12
#else
	#define RECOR_DPATH "C:\\vplus\\msg.rc"
	#define SEARCH_DIRS "C:\\vplus\\files"
	#define ROBOT L"@robot"
	#define ROBOT_LEN 6
#endif

void sendTextmsg(wstring wsWxId, wstring wsTextMsg);
void dispatch(wstring wid, wstring msg);
void SendFileMessage(wchar_t* wxid, wchar_t* filepath);
int getFiles(wstring search_str, string path, string& info);
string w2s(const std::wstring& wstr);
wstring s2w(string str);
bool IsdigitAll(string str);