//// dllmain.cpp : 定义 DLL 应用程序的入口点。
//#pragma warning(disable:4996) 
//#include "framework.h"
//#include<stdio.h>
//#include<fstream>
//#include<iomanip>
//#include<string>
//#include <memory>
//#include <Windows.h>
//#include <iostream>
//#include <time.h>
//#include <map>
//using namespace std;
//string getTime()
//{
//	time_t timep;
//	time(&timep);
//	char tmp[64];
//	strftime(tmp, sizeof(tmp), "%Y-%m-%d %H:%M:%S", localtime(&timep));
//	return tmp;
//}
//string wstring2string(wstring wstr)
//{
//	string result;
//	//获取缓冲区大小，并申请空间，缓冲区大小事按字节计算的  
//	int len = WideCharToMultiByte(CP_ACP, 0, wstr.c_str(), wstr.size(), NULL, 0, NULL, NULL);
//	char* buffer = new char[len + 1];
//	//宽字节编码转换成多字节编码  
//	WideCharToMultiByte(CP_ACP, 0, wstr.c_str(), wstr.size(), buffer, len, NULL, NULL);
//	buffer[len] = '\0';
//	//删除缓冲区并返回值  
//	result.append(buffer);
//	delete[] buffer;
//	return result;
//}
//
//
//string GetStringByAddress(DWORD address)
//{
//	string sValue = "";
//
//	char cValue[500] = { 0 };
//	memcpy(cValue, (const void*)address, 10);
//	sValue = string(cValue);
//	return sValue;
//}
//
//// 模块基址
//DWORD dllBaseAddress = (DWORD)GetModuleHandle(L"WeChatWin.dll");
//
//// 接收消息hook位置偏移
//
////DWORD recievedHookOffset = 0x3CCB65;
////DWORD recievedHookOffset = 0x37DB7B;
////demo
//DWORD recievedHookOffset = 0x37E2C2;
//// 接收消息hook位置的内存地址
//DWORD recievedHookAddress = dllBaseAddress + recievedHookOffset;
//
//// 被覆盖的数据的偏移
////DWORD coeverDataOffset = 0x18A2BF0;
//DWORD coeverDataOffset = 0x80770;
//// 被覆盖的数据的内存地址
//DWORD coeverDataAddress = dllBaseAddress + coeverDataOffset;
//
//// Hook下一个指令的地址
//DWORD recievedHookRetAddress = recievedHookAddress + 5;
//CHAR originalRecieveCode[5] = { 0 };
//
//
//map<string, string> names{
//	{"25283462653@chatroom","微淼VplusI"},
//	{"24833878718@chatroom","test"},
//};
//ofstream ofile;
//
//
//void DealRecievedMessage(WCHAR* wid, WCHAR* msg)
//{
//
//	//sendTextmsg(wid,msg);
//	dispatch(wid, msg);
//	string wsMsg = "未定义";
//	if (msg!=0x0) {
//		wsMsg = wstring2string(msg);
//		//MessageBox(NULL, L"hello", L"收到消息", 0);
//	}
//	string wwid_str = wstring2string(wid);
//	string ShowMsg =" 消息： " + wsMsg;
//	map<string, string>::iterator iter = names.find(wwid_str);
//	string ret_wid = iter != names.end() ? iter->second : wwid_str;
//	string createtime = getTime();
//
//	ofile << ret_wid+"  "+ createtime +"："<< endl;
//	ofile << "\t" << wsMsg << endl;
//	ofile << "-----------------------------------------" << endl;
//
//
//	//MessageBox(NULL, L"hello", L"收到消息", 0);
//}
//
//void DealRecievedMessage2(WCHAR* wid, WCHAR* msg)
//{
//	wstring wsMsg = msg;
//	wstring wswid = wid;
//	wstring content = wswid + L" ; " + wsMsg;
//	MessageBox(NULL, content.c_str(), L"收到消息", 0);
//}
//
//
//void UnHookRecievedMessage()
//{
//	// 回复被覆盖的指令
//	WriteProcessMemory(GetCurrentProcess(), (LPVOID)recievedHookAddress, originalRecieveCode, 5, 0);
//}
//
//
//__declspec(naked) void ListenRecievedMessage()
//{
//	/*
//	__asm
//	{
//
//		pushad;
//		pushfd;
//		//content
//		push[ebp - 0x240];
//		//wid
//		push[ebp - 0x268];
//		call DealRecievedMessage;
//		add esp, 0x8;
//		popfd;
//		popad;
//
//		//push wechatwin.57DB6C48
//		push coeverDataAddress;
//		// 返回hook的下一条指令
//		jmp recievedHookRetAddress
//	}
//	*/
//	__asm
//	{
//		pushad;
//		pushfd;
//		//content
//		push[eax];
//		//wid
//		push[eax-0x28]
//		call DealRecievedMessage;
//		add esp,0x8;
//		popfd;
//		popad;
//		//push wechatwin.57DB6C48
//		//push coeverDataAddress;
//		//call wechatwin.63760770
//		call coeverDataAddress
//		// 返回hook的下一条指令
//		jmp recievedHookRetAddress
//	}
//
//}
//
//void HookRecievedMessage()
//{
//	// 跳转需要五个字节
//	BYTE jmpCode[5] = { 0 };
//	// 第一个字节填 E9，对应汇编的jmp
//	jmpCode[0] = 0xE9;
//	// 后面四个字节，填要跳转的位置，之所以减5，是因为当前的指令占五个字节
//	*(DWORD*)&jmpCode[1] = (DWORD)ListenRecievedMessage - recievedHookAddress - 5;
//	// 把老的指令读出来存好，方便恢复
//	ReadProcessMemory(GetCurrentProcess(), (LPVOID)recievedHookAddress, originalRecieveCode, 5, 0);
//	// 把新的执行写到hook的位置
//	WriteProcessMemory(GetCurrentProcess(), (LPVOID)recievedHookAddress, jmpCode, 5, 0);
//}
//
//
//
//BOOL APIENTRY DllMain(HMODULE hModule,
//	DWORD  ul_reason_for_call,
//	LPVOID lpReserved
//)
//{
//	switch (ul_reason_for_call)
//	{
//	case DLL_PROCESS_ATTACH:
//	{
//		ofile.open("d:\\myfile.txt", ios::app);
//		//ofile.open("C:\\programe\\record.rc", ios::app);//server version
//	
//		MessageBox(NULL, L"hello1", L"收到消息", 0);
//		HookRecievedMessage();
//	}
//	break;
//	case DLL_PROCESS_DETACH:
//	{
//		ofile.close();
//
//		UnHookRecievedMessage();
//	}
//	break;
//	case DLL_THREAD_ATTACH:
//	case DLL_THREAD_DETACH:
//		break;
//	}
//	return TRUE;
//}
//
//
//
//
////BOOL APIENTRY DllMain( HMODULE hModule,
////                       DWORD  ul_reason_for_call,
////                       LPVOID lpReserved
////                     )
////{
////    switch (ul_reason_for_call)
////    {
////        case DLL_PROCESS_ATTACH:
////		{
////			// 1、获取DLL模块基址
////			// 模块基址
////			DWORD dllBaseAddress = (DWORD)GetModuleHandle(L"WeChatWin.dll");
////			// 2、获取用户名
////			// 用户名偏移
////			DWORD wxNameOffset = 0x18A259C;
////			// 用户名内存地址
////			DWORD wxNameAddress = dllBaseAddress + wxNameOffset;
////			// 用户名
////			string sWxName = GetStringByAddress(wxNameAddress);
////			// 3、获取WXID
////			// WXID指针偏移
////			DWORD wxIDPointerOffset = 0x18A2524;
////			// WXID指针地址
////			DWORD wxIDPointerAddress = dllBaseAddress + wxIDPointerOffset;
////			// WXID内存地址
////			DWORD wxIDAddress = GetIntByAddress(wxIDPointerAddress);
////			// WXID
////			string sWxId = GetStringByAddress(wxIDAddress);
////
////			// 4、显示结果
////
////			// 用户信息
////			string csUserInfo = string("用户信息： 用户名：") + sWxName + " 用户ID: " + sWxId;
////			MessageBoxA(NULL, csUserInfo.c_str(), "用户信息", 0);
////			break;
////		}
////
////        case DLL_THREAD_ATTACH:
////        case DLL_THREAD_DETACH:
////        case DLL_PROCESS_DETACH:
////            break;
////    }
////    return TRUE;
////}
//
// dllmain.cpp : 定义 DLL 应用程序的入口点。

#pragma warning(disable:4996) 
#include "framework.h"
#include<stdio.h>
#include<fstream>
#include<iomanip>
#include<string>
#include <memory>
#include <Windows.h>
#include <iostream>
#include <time.h>
#include <map>
using namespace std;
string getTime()
{
	time_t timep;
	time(&timep);
	char tmp[64];
	strftime(tmp, sizeof(tmp), "%Y-%m-%d %H:%M:%S", localtime(&timep));
	return tmp;
}

string GetStringByAddress(DWORD address)
{
	string sValue = "";

	char cValue[500] = { 0 };
	memcpy(cValue, (const void*)address, 10);
	sValue = string(cValue);
	return sValue;
}

// 模块基址
DWORD dllBaseAddress = (DWORD)GetModuleHandle(L"WeChatWin.dll");

// 接收消息hook位置偏移

//DWORD recievedHookOffset = 0x3CCB65;
//DWORD recievedHookOffset = 0x37DB7B;
//demo
DWORD recievedHookOffset = 0x37D992;
// 接收消息hook位置的内存地址
DWORD recievedHookAddress = dllBaseAddress + recievedHookOffset;

// 被覆盖的数据的偏移
//DWORD coeverDataOffset = 0x18A2BF0;
DWORD coeverDataOffset = 0x80770;
// 被覆盖的数据的内存地址
DWORD coeverDataAddress = dllBaseAddress + coeverDataOffset;

// Hook下一个指令的地址
DWORD recievedHookRetAddress = recievedHookAddress + 5;
CHAR originalRecieveCode[5] = { 0 };


map<string, string> names{
	{"25283462653@chatroom","微淼VplusI"},
	{"24833878718@chatroom","test"},
};
ofstream ofile;


void DealRecievedMessage(WCHAR* wid, WCHAR* msg)
{

	dispatch(wid, msg);
	string wsMsg = "未定义";
	if (msg != 0x0) {
		wsMsg = w2s(msg);
		//MessageBox(NULL, L"hello", L"收到消息", 0);
	}
	string wwid_str = w2s(wid);
	string ShowMsg = " 消息： " + wsMsg;
	map<string, string>::iterator iter = names.find(wwid_str);
	string ret_wid = iter != names.end() ? iter->second : wwid_str;
	string createtime = getTime();

	ofile << ret_wid + "  " + createtime + "：" << endl;
	ofile << "\t" << wsMsg << endl;
	ofile << "-----------------------------------------" << endl;


	//MessageBox(NULL, L"hello", L"收到消息", 0);
}

void DealRecievedMessage2(WCHAR* wid, WCHAR* msg)
{
	wstring wsMsg = msg;
	wstring wswid = wid;
	wstring content = wswid + L" ; " + wsMsg;
	MessageBox(NULL, content.c_str(), L"收到消息", 0);
}


void UnHookRecievedMessage()
{
	// 回复被覆盖的指令
	WriteProcessMemory(GetCurrentProcess(), (LPVOID)recievedHookAddress, originalRecieveCode, 5, 0);
}


__declspec(naked) void ListenRecievedMessage()
{
	/*
	__asm
	{

		pushad;
		pushfd;
		//content
		push[ebp - 0x240];
		//wid
		push[ebp - 0x268];
		call DealRecievedMessage;
		add esp, 0x8;
		popfd;
		popad;

		//push wechatwin.57DB6C48
		push coeverDataAddress;
		// 返回hook的下一条指令
		jmp recievedHookRetAddress
	}
	*/
	__asm
	{
		pushad;
		pushfd;
		//content
		push[eax];
		//wid
		push[eax - 0x28]
			call DealRecievedMessage;
		add esp, 0x8;
		popfd;
		popad;
		//push wechatwin.57DB6C48
		//push coeverDataAddress;
		//call wechatwin.63760770
		call coeverDataAddress
			// 返回hook的下一条指令
			jmp recievedHookRetAddress
	}

}

void HookRecievedMessage()
{
	// 跳转需要五个字节
	BYTE jmpCode[5] = { 0 };
	// 第一个字节填 E9，对应汇编的jmp
	jmpCode[0] = 0xE9;
	// 后面四个字节，填要跳转的位置，之所以减5，是因为当前的指令占五个字节
	*(DWORD*)&jmpCode[1] = (DWORD)ListenRecievedMessage - recievedHookAddress - 5;
	// 把老的指令读出来存好，方便恢复
	ReadProcessMemory(GetCurrentProcess(), (LPVOID)recievedHookAddress, originalRecieveCode, 5, 0);
	// 把新的执行写到hook的位置
	WriteProcessMemory(GetCurrentProcess(), (LPVOID)recievedHookAddress, jmpCode, 5, 0);
}



BOOL APIENTRY DllMain(HMODULE hModule,
	DWORD  ul_reason_for_call,
	LPVOID lpReserved
)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
	{
		
		ofile.open(RECOR_DPATH, ios::app);
		#ifdef _DEBUG
			MessageBox(NULL, L"hello1", L"收到消息", 0);
		//#else
		//printf("loading wechathelper.dll....\n");
		#endif

		HookRecievedMessage();
	}
	break;
	case DLL_PROCESS_DETACH:
	{
		ofile.close();
		UnHookRecievedMessage();
	}
	break;
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
		break;
	}
	return TRUE;
}




//BOOL APIENTRY DllMain( HMODULE hModule,
//                       DWORD  ul_reason_for_call,
//                       LPVOID lpReserved
//                     )
//{
//    switch (ul_reason_for_call)
//    {
//        case DLL_PROCESS_ATTACH:
//		{
//			// 1、获取DLL模块基址
//			// 模块基址
//			DWORD dllBaseAddress = (DWORD)GetModuleHandle(L"WeChatWin.dll");
//			// 2、获取用户名
//			// 用户名偏移
//			DWORD wxNameOffset = 0x18A259C;
//			// 用户名内存地址
//			DWORD wxNameAddress = dllBaseAddress + wxNameOffset;
//			// 用户名
//			string sWxName = GetStringByAddress(wxNameAddress);
//			// 3、获取WXID
//			// WXID指针偏移
//			DWORD wxIDPointerOffset = 0x18A2524;
//			// WXID指针地址
//			DWORD wxIDPointerAddress = dllBaseAddress + wxIDPointerOffset;
//			// WXID内存地址
//			DWORD wxIDAddress = GetIntByAddress(wxIDPointerAddress);
//			// WXID
//			string sWxId = GetStringByAddress(wxIDAddress);
//
//			// 4、显示结果
//
//			// 用户信息
//			string csUserInfo = string("用户信息： 用户名：") + sWxName + " 用户ID: " + sWxId;
//			MessageBoxA(NULL, csUserInfo.c_str(), "用户信息", 0);
//			break;
//		}
//
//        case DLL_THREAD_ATTACH:
//        case DLL_THREAD_DETACH:
//        case DLL_PROCESS_DETACH:
//            break;
//    }
//    return TRUE;
//}

