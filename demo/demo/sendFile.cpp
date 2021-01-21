#include "pch.h"
#include <string>
using namespace std;

#define WxFileMessage1 0x60B140C0-0x605A0000				//�����ļ���Ϣ
#define WxFileMessage2 0x60B14100-0x605A0000								//�����ļ���Ϣ
#define WxFileMessage3 0x60606CB0-0x605A0000								//�����ļ���Ϣ
#define WxFileMessage4 0x60857600-0x605A0000								//�����ļ���Ϣ
#define WxFileMessageParam 0x61AF0368-0x605A0000							//�����ļ���Ϣ

//���ڵ���΢�ŷ�����Ϣcall�Ľṹ��
struct wxMsg
{
	wchar_t* pMsg;		//΢��ID
	int msgLen;			//ID����
	int buffLen;		//����������
	int fill1 = 0;
	int fill2 = 0;
};

//΢��ID�Ľṹ��
struct Wxid
{
	wchar_t* str;
	int strLen = 0;
	int maxLen = 0;
	char file[0x8] = { 0 };
};
//�ļ�·���Ľṹ��
struct filePath
{
	wchar_t* str;
	int strLen = 0;
	int maxLen = 0;
	char file[0x18] = { 0 };
};

void SendFileMessage(wchar_t* wxid, wchar_t* filepath)
{
	//������Ҫ�ĵ�ַ
	DWORD dwBase = (DWORD)GetModuleHandle(TEXT("WeChatWin.dll"));
	DWORD dwCall1 = dwBase + WxFileMessage1;
	DWORD dwCall2 = dwBase + WxFileMessage2;
	DWORD dwCall3 = dwBase + WxFileMessage3;	//�������
	DWORD dwCall4 = dwBase + WxFileMessage4;	//������Ϣ
	DWORD dwParams = dwBase + WxFileMessageParam;

	char buff[0x350] = { 0 };

	//������Ҫ������
	Wxid wxidStruct = { 0 };
	wxidStruct.str = wxid;
	wxidStruct.strLen = wcslen(wxid);
	wxidStruct.maxLen = wcslen(wxid) * 2;

	filePath filePathStruct = { 0 };
	filePathStruct.str = filepath;
	filePathStruct.strLen = wcslen(filepath);
	filePathStruct.maxLen = wcslen(filepath) * 2;

	//ȡ����Ҫ�����ݵĵ�ַ
	char* pFilePath = (char*)&filePathStruct.str;
	char* pWxid = (char*)&wxidStruct.str;
	__asm {

		pushad;
		
		push 0x1;
		sub esp, 0x14;
		mov ecx, esp;

		push 0xFFFFFFFF;
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

		popad;
	}
}