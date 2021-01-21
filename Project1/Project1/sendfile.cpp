// dllmain.cpp : 定义 DLL 应用程序的入口点。
#include "framework.h"
#include<windows.h>
#include <iostream>
#include <string>
#include <io.h>
using namespace std;

#define WxFileMessageParam 0x161B4C8
#define WxFileMessage1 0x5740C0				//发送文件消息

#define WxFileMessage2 0x574100								//发送文件消息
#define WxFileMessage3 0x66CB0								//发送文件消息
#define WxFileMessage4 0x2B7600								//发送文件消息


//用于调用微信发送消息call的结构体
//微信ID的结构体
struct Wxid
{
	wchar_t* str;//4
	int strLen;//4
	int maxLen;//4
	char file[0x8] = { 0 };
};
//文件路径的结构体
struct filePath
{

	wchar_t* str;//4
	int strLen;//4
	int maxLen;//4
	char file[0x1C] = { 0 };
};

void SendFileMessage(wchar_t* wxid, wchar_t* filepath)
{
	//构造需要的地址
	DWORD dllBaseAddress = (DWORD)GetModuleHandle(L"WeChatWin.dll");
	DWORD dwcall0 = dllBaseAddress + 0x5734C0;
	DWORD dwCall1 = dllBaseAddress + 0x573480;
	DWORD dwCall2 = dllBaseAddress + 0x5734C0;
	DWORD dwCall3 = dllBaseAddress + 0x66CB0;//组合参数
	DWORD dwCall4 = dllBaseAddress + 0x2B70C0;	//发送消息
	DWORD dwParams = dllBaseAddress + 0x161B4C8;
	char buff1[0x20] = { 0 };
	char buff[0x350] = { 0 };

	//构造需要的数据
	Wxid wxidStruct = { 0 };
	wxidStruct.str = wxid;
	wxidStruct.strLen = wcslen(wxid);
	wxidStruct.maxLen = wcslen(wxid) * 2;

	filePath filePathStruct = { 0 };
	filePathStruct.str = filepath;
	filePathStruct.strLen = wcslen(filepath);
	filePathStruct.maxLen = wcslen(filepath) * 2;

	//取出需要的数据的地址
	char* pFilePath = (char*)&filePathStruct.str;
	char* pWxid = (char*)&wxidStruct.str;
	__asm {


		pushad;

		mov ecx, 0x0;
		mov eax, 0x1;
		cmovne ecx, eax;
		sub esp, 0x14;
		lea eax, buff1;
		mov ecx, esp;
		push eax;
		call dwcall0;

		push 0x0;
		sub esp, 0x14;
		mov ecx, esp;
		push - 0x1;
		push dwParams;
		call dwCall1;

		sub esp, 0x14;
		mov ecx, esp;
		mov ebx, pFilePath;
		push ebx;
		call dwCall2;

		sub esp, 0x14;
		mov ecx, esp;
		push pWxid;
		call dwCall2;

		lea eax, buff;
		push eax;
		call dwCall3;
		mov ecx, eax;
		call dwCall4;

		mov edi, eax;
		popad;

	}
}

//void sendfile(wstring wid,wstring ky) {
//	wstring str = L"#4视频课笔记-A股详细版  ";
//	//int pos = str.find(L"#");
//	//int last = str.find_last_not_of(L" ");
//	//wstring search_str = str.substr(pos + 1, last);
//	string filepath = "C:\\Users\\swxxx\\Desktop\\temp\\2021-01";
//	string info;
//	int ret = getFiles(ky, filepath, info);
//	MessageBox(NULL, (s2w(info)).c_str(), L"收到消息", 0);
//	SendFileMessage((wchar_t*)wid.c_str(), (wchar_t*)(s2w(info)).c_str());
//
//}
//BOOL APIENTRY DllMain(HMODULE hModule,
//	DWORD  ul_reason_for_call,
//	LPVOID lpReserved
//)
//{
//	switch (ul_reason_for_call)
//	{
//	case DLL_PROCESS_ATTACH:
//	{
//		wchar_t buffertest[100] = {0};
//		//swprintf_s(buffertest, L"%p", SendFileMessage);
//		//MessageBox(NULL, buffertest, L"收到消息", 0);
//		wchar_t wid[] = { L"filehelper" };
//		//wchar_t filepath[] = { L"C:\\Users\\swxxx\\Desktop\\f7600a1eb03be0ce181c1055edeab1f.jpg" };
//
//		wstring str = L"#4视频课笔记-A股详细版  ";
//		int pos = str.find(L"#");
//		int last = str.find_last_not_of(L" ");
//		wstring search_str = str.substr(pos + 1, last);
//		string filepath = "C:\\Users\\swxxx\\Desktop\\temp\\2021-01";
//		string info;
//		int ret = getFiles(search_str, filepath, info);
//		MessageBox(NULL, (s2w(info)).c_str(), L"收到消息", 0);
//
//		SendFileMessage(wid, (wchar_t*)(s2w(info)).c_str());
//	}
//	break;
//	case DLL_THREAD_ATTACH:
//	case DLL_THREAD_DETACH:
//	case DLL_PROCESS_DETACH:
//		break;
//	}
//	return TRUE;
//}
/*
606AA405 | B8 01000000	| mov eax, 1							| eax:&"`P卄pH卄w"
606AA40A | 0F45C8		| cmovne ecx, eax						| ecx : &"`P卄pH卄w", eax : &"`P卄pH卄w"
606AA40D | 83EC 14		| sub esp, 14							|
606AA410 | 884D 94		| mov byte ptr ss : [ebp - 6C] , cl		|
606AA413 | 8D47 E0		| lea eax, dword ptr ds : [edi - 20]	| eax : &"`P卄pH卄w"
606AA416 | 8BCC			| mov ecx, esp							|
606AA418 | 8965 BC		| mov dword ptr ss : [ebp - 44] , esp	|
606AA41B | 50			| push eax								| eax : &"`P卄pH卄w"
606AA41C | E8 DF9C4600	| call wechatwin.60B14100				|
60B14100-605A0000=0x574100

606AA421 | FF75 94		| push dword ptr ss : [ebp - 6C]		|
606AA424 | 83EC 14		| sub esp, 14							|
606AA427 | 8BCC			| mov ecx, esp							|
606AA429 | 8965 90		| mov dword ptr ss : [ebp - 70] , esp	|
606AA42C | 6A FF		| push FFFFFFFF							|
606AA42E | 68 6803AF61	| push wechatwin.61AF0368				|
606AA433 | E8 889C4600	| call wechatwin.60B140C0				|
61AF0368-605A0000 = 0x1550368
60B140C0-605A0000 = 0x5740C0

606AA438 | 83EC 14			| sub esp, 14							|
606AA43B | 8BCC				| mov ecx, esp							|
606AA43D | 8965 8C			| mov dword ptr ss : [ebp - 74] , esp	| [ebp - 74] : &L"C:\\Users\\swxxx\\Desktop\\现金流折现法计算公司内在价值.docx"
606AA440 | 53				| push ebx								| ebx : &L"C:\\Users\\swxxx\\Desktop\\现金流折现法计算公司内在价值.docx"
606AA441 | E8 BA9C4600		| call wechatwin.60B14100				| 组装函数1
60B14100-605A0000=0x574100


606AA446 | 83EC 14			| sub esp, 14							|
606AA449 | 8D85 78FFFFFF	| lea eax, dword ptr ss : [ebp - 88]	| [ebp - 88] : L"wxid_ne4akdf9whd822"
606AA44F | 8BCC				| mov ecx, esp							|
606AA451 | 8965 B0			| mov dword ptr ss : [ebp - 50] , esp	| [ebp - 50] : &L"wxid_ne4akdf9whd822"
606AA454 | 50				| push eax								| eax : &"`P卄pH卄w"
606AA455 | E8 A69C4600		| call wechatwin.60B14100				| 组装函数2
60B14100-605A0000=0x574100


606AA45A | 8D85 B0FCFFFF	| lea eax, dword ptr ss : [ebp - 350]	|
606AA460 | C645 FC 10		| mov byte ptr ss : [ebp - 4] , 10		|
606AA464 | 50				| push eax								| eax : &"`P卄pH卄w"
606AA465 | E8 46C8F5FF		| call wechatwin.60606CB0				| 组装函数3
60606CB0-605A0000=0x66CB0


606AA46A | 8BC8				| mov ecx, eax							| ecx : &"`P卄pH卄w", eax : &"`P卄pH卄w"
606AA46C | C645 FC 0C		| mov byte ptr ss : [ebp - 4] , C		| C : '\f'
606AA470 | E8 8BD11A00		| call wechatwin.60857600				| 发送文件一定会执行的call函数
60857600-605A0000=0x2B7600

base地址:
基址=605A0000
模块=wechatwin.dll
所属方=用户
路径=C:\Program Files (x86)\Tencent\WeChat\WeChatWin.dll
状态=Unloaded
00EFC954
*/