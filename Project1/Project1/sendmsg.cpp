//#include "framework.h"
//#include "myurl.h"
//#include <stdio.h>
//#include <string>
//using namespace std;
//struct WxString
//{
//	// ���ַ���
//	wchar_t* buffer;
//	// ���ַ�������
//	int size;
//	// ���ַ����ռ�
//	int capacity;
//	// 8�������0
//	char fill[8];
//};
//
//void sendTextmsg(wstring wsWxId, wstring wsTextMsg)
//{
//
//	WxString wxWxid = { 0 };
//	wxWxid.buffer = (wchar_t*)wsWxId.c_str();
//	wxWxid.size = wsWxId.size();
//	wxWxid.capacity = wsWxId.size() * 2;
//	//// ������Ϣ�ṹ
//	WxString wxTextMsg = { 0 };
//	wxTextMsg.buffer = (wchar_t*)wsTextMsg.c_str();
//	wxTextMsg.size = wsTextMsg.size();
//	wxTextMsg.capacity = wsTextMsg.size() * 2;
//	//// �����buffer
//	char buff[0x5A8] = { 0 };
//	char* pWxid = (char*)&wxWxid.buffer;
//	char* pWxmsg = (char*)&wxTextMsg.buffer;
//
//
//	/*char buff[0x5A8] = { 0 };
//	char* pWxid = (char*)wsWxId.c_str();
//	char* pWxmsg = (char*)wsTextMsg.c_str();
//
//	int pwid_size = wsWxId.size();
//	int pwmsg_size = wsTextMsg.size();*/
//
//	// ģ���ַ
//	DWORD dllBaseAddress = (DWORD)GetModuleHandle(L"WeChatWin.dll");
//	DWORD callOffset = 0x3A0C20;
//	DWORD callAddress = dllBaseAddress + callOffset;
//
//	/*
//		����Դ��
//		push	1
//		push	edi
//		push	ebx
//		lea		edx,dword ptr ss:[ebp-88]
//		lea		ecx,dword ptr ss:[ebp-5A8]
//		call	wechatwin.61770250
//	*/
//	__asm {
//
//		push 1;
//		mov edi, 0;
//		push edi;
//
//		mov ebx, pWxmsg;
//		push ebx;
//
//		mov edx, pWxid;
//
//		lea ecx, buff;
//		call callAddress;
//		add esp, 0xC;
//	}
//}
//
//string wstring2string2(wstring wstr)
//{
//	string result;
//	//��ȡ��������С��������ռ䣬��������С�°��ֽڼ����  
//	int len = WideCharToMultiByte(CP_ACP, 0, wstr.c_str(), wstr.size(), NULL, 0, NULL, NULL);
//	char* buffer = new char[len + 1];
//	//���ֽڱ���ת���ɶ��ֽڱ���  
//	WideCharToMultiByte(CP_ACP, 0, wstr.c_str(), wstr.size(), buffer, len, NULL, NULL);
//	buffer[len] = '\0';
//	//ɾ��������������ֵ  
//	result.append(buffer);
//	delete[] buffer;
//	return result;
//}
//
//
//wstring string2wstring(string str)
//{
//	wstring result;
//	//��ȡ��������С��������ռ䣬��������С���ַ�����  
//	int len = MultiByteToWideChar(CP_ACP, 0, str.c_str(), str.size(), NULL, 0);
//	TCHAR* buffer = new TCHAR[len + 1];
//	//���ֽڱ���ת���ɿ��ֽڱ���  
//	MultiByteToWideChar(CP_ACP, 0, str.c_str(), str.size(), buffer, len);
//	buffer[len] = '\0';             //����ַ�����β  
//	//ɾ��������������ֵ  
//	result.append(buffer);
//	delete[] buffer;
//	return result;
//}
//
//std::string& trim(std::string& s)
//
//{
//	if (s.empty())
//	{
//		return s;
//	}
//	s.erase(0, s.find_first_not_of(" "));
//	s.erase(s.find_last_not_of(" ") + 1);
//	return s;
//}
//
//void dispatch(wstring wid, wstring msg) {
//
//	wstring wwid = wid;
//	wchar_t* buffer = (wchar_t*)msg.c_str();
//	string wmsg = (char*)&buffer;
//	wstring a = msg.substr(0, 6);
//	if (a != L"@robot"){
//		//wstring ss = L"������ʦ���ɣ��Ҳ������Ҫ��ʲô:https://www.yuque.com/hongseshitou-n4dia/lqi07d";
//		//sendTextmsg(wid, msg.substr(0,6));
//	}
//	else {
//		int pos = msg.find(L"#");
//		int last = msg.find_last_not_of(L" ");
//		wstring ky = msg.substr(pos + 1, last);
//
//		map<wstring, wstring>::iterator iter = url_map.find(ky);
//		wstring ret_url = iter != url_map.end() ? iter->second : L"";
//		wstring ret_infoss = ret_url==L""? L"#δ�鵽���Ʊ����"+ky+L"��صı���(Ŀǰ��֧�ֱ������������֤ȯ�๫˾)" : L"�鵽��Ʊ����Ϊ:"+ky+L"���棬���������:"+ ret_url;
//		sendTextmsg(wid, ret_infoss);
//	}
//
//}
#include "framework.h"
#include "myurl.h"
#include <stdio.h>
#include <string>
using namespace std;
struct WxString
{
	// ���ַ���
	wchar_t* buffer;
	// ���ַ�������
	int size;
	// ���ַ����ռ�
	int capacity;
	// 8�������0
	char fill[8];
};

void sendTextmsg(wstring wsWxId, wstring wsTextMsg)
{

	WxString wxWxid = { 0 };
	wxWxid.buffer = (wchar_t*)wsWxId.c_str();
	wxWxid.size = wsWxId.size();
	wxWxid.capacity = wsWxId.size() * 2;
	//// ������Ϣ�ṹ
	WxString wxTextMsg = { 0 };
	wxTextMsg.buffer = (wchar_t*)wsTextMsg.c_str();
	wxTextMsg.size = wsTextMsg.size();
	wxTextMsg.capacity = wsTextMsg.size() * 2;
	//// �����buffer
	char buff[0x5A8] = { 0 };
	char* pWxid = (char*)&wxWxid.buffer;
	char* pWxmsg = (char*)&wxTextMsg.buffer;


	/*char buff[0x5A8] = { 0 };
	char* pWxid = (char*)wsWxId.c_str();
	char* pWxmsg = (char*)wsTextMsg.c_str();

	int pwid_size = wsWxId.size();
	int pwmsg_size = wsTextMsg.size();*/

	// ģ���ַ
	DWORD dllBaseAddress = (DWORD)GetModuleHandle(L"WeChatWin.dll");
	DWORD callOffset = 0x3A0250;
	DWORD callAddress = dllBaseAddress + callOffset;

	/*
		����Դ��
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

