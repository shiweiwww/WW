// dllmain.cpp : 定义 DLL 应用程序的入口点。
#include "pch.h"
#include <string>
#include<thread>
#include <iostream>
using namespace std;

struct WxString
{
	// 存字符串
	wchar_t* buffer;
	// 存字符串长度
	int size;
	// 存字符串空间
	int capacity;
	// 8个空余的0
	char fill[8];
};

void sendTextmsg(wstring wsWxId, wstring wsTextMsg)
{

	WxString wxWxid = { 0 };
	wxWxid.buffer = (wchar_t*)wsWxId.c_str();
	wxWxid.size = wsWxId.size();
	wxWxid.capacity = wsWxId.size() * 2;
	//// 构造消息结构
	WxString wxTextMsg = { 0 };
	wxTextMsg.buffer = (wchar_t*)wsTextMsg.c_str();
	wxTextMsg.size = wsTextMsg.size();
	wxTextMsg.capacity = wsTextMsg.size() * 2;
	//// 构造空buffer
	char buff[0x5A8] = { 0 };
	char* pWxid = (char*)&wxWxid.buffer;
	char* pWxmsg = (char*)&wxTextMsg.buffer;


	/*char buff[0x5A8] = { 0 };
	char* pWxid = (char*)wsWxId.c_str();
	char* pWxmsg = (char*)wsTextMsg.c_str();

	int pwid_size = wsWxId.size();
	int pwmsg_size = wsTextMsg.size();*/

	// 模块基址
	DWORD dllBaseAddress = (DWORD)GetModuleHandle(L"WeChatWin.dll");
	DWORD callOffset = 0x3A0C20;
	DWORD callAddress = dllBaseAddress + callOffset;

	/*
		参照源码
		push	1
		push	edi
		push	ebx
		lea		edx,dword ptr ss:[ebp-88]
		lea		ecx,dword ptr ss:[ebp-5A8]
		call	wechatwin.61770250
	*/
	__asm {

		push 1;
		mov edi, 0;
		push edi;

		mov ebx, pWxmsg;
		push ebx;

		mov edx, pWxid;

		lea ecx, buff;
		call callAddress;
		add esp, 0xC;
	}
}

void thread01()
{
		wstring wsWxId = L"wxid_ne4akdf9whd822";
		wstring wsTextMsg = L"这是一条测试消息！！！境外输入确诊病例：某男，24岁，中国籍，在巴基斯坦工作。从巴基斯坦乘坐国航CA946航班，于2020年12月18日到达北京首都机场，海关进行健康筛查并做核酸检测，结果为阴性，经闭环管理送至集中隔离酒店。2021年1月1日核酸检测结果为阳性，由120负压救护车转至地坛医院，综合流行病学史、临床表现、实验室检测和影像学检查等结果，1月2日诊断为确诊病例，临床分型为轻型。患者抵京后一直集中隔离，无密切接触者。按要求落实管控措施";
		sendTextmsg(wsWxId, wsTextMsg);
		std::cout << "thread t1 running  ID:" << std::this_thread::get_id() << std::endl;

}



BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
	case DLL_PROCESS_ATTACH:
		{
			MessageBox(NULL, L"hello1", L"收到消息", 0);

			wstring wsWxId = L"wxid_ne4akdf9whd822";
			wstring wsTextMsg = L"这是一条测试消息！！！境外输入确诊病例：某男，24岁，中国籍，在巴基斯坦工作。从巴基斯坦乘坐国航CA946航班，于2020年12月18日到达北京首都机场，海关进行健康筛查并做核酸检测，结果为阴性，经闭环管理送至集中隔离酒店。2021年1月1日核酸检测结果为阳性，由120负压救护车转至地坛医院，综合流行病学史、临床表现、实验室检测和影像学检查等结果，1月2日诊断为确诊病例，临床分型为轻型。患者抵京后一直集中隔离，无密切接触者。按要求落实管控措施";
			sendTextmsg(wsWxId, wsTextMsg);

	}
		break;
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

