#include "framework.h"
#include<windows.h>
#include <iostream>
#include <string>
#include <io.h>
using namespace std;

int getFiles(wstring search_str, string path, string& info)
{
	string str = w2s(search_str);
	//�ļ����
	long  hFile = 0;
	//�ļ���Ϣ
	struct _finddata_t fileinfo;
	int files = 0;
	string p;
	string ret = "";
	string first_one = "";
	if ((hFile = _findfirst(p.assign(path).append("\\*").c_str(), &fileinfo)) != -1)
	{
		do
		{
			//�Ƿ�ΪĿ¼
			if ((fileinfo.attrib & _A_SUBDIR)) { ; }
			else
			{
				string name = fileinfo.name;
				if (name.find(str) != name.npos) {
					string fpath = p.assign(path).append("\\").append(fileinfo.name);
					if (files == 0) first_one = fpath;
					ret += "[" + to_string(files) + "] " + fileinfo.name + "\n";
					files++;
				}
			}
		} while (_findnext(hFile, &fileinfo) == 0);
		_findclose(hFile);
	}
	if (files == 0) {
		info = "#δ�ҵ��ļ�,��鿴�Ƿ������ʽ�д���!";
	}
	else if (files == 1) {
		info = first_one;
	}
	else {
		info = "�ҵ���#" + str + "��ص��ļ�:\n" + ret;
	}
	return files;
}

void dispatch(wstring wid, wstring msg) {

	wstring wwid = wid;
	wstring a = msg.substr(0, ROBOT_LEN);
	if (a != ROBOT) {
		//wstring ss = L"������ʦ���ɣ��Ҳ������Ҫ��ʲô:https://www.yuque.com/hongseshitou-n4dia/lqi07d";
		//sendTextmsg(wid, msg.substr(0,6));
	}
	else {
		int pos = msg.find(L"#");
		int last = msg.find_last_not_of(L" ");
		wstring ky = msg.substr(pos + 1, last);
		ky.resize(last - pos);
		//MessageBox(NULL, ky.c_str(), L"�յ���Ϣ", 0);
		bool isnum = IsdigitAll(w2s(ky));
		if (isnum) {
			wstring ret_url = L"https://www.yuque.com/hongseshitou-n4dia/bcu1bk/" + ky;
			wstring ret_infoss = L"�鵽��Ʊ����Ϊ:" + ky + L"����(Ŀǰ��֧�ֱ������������֤ȯ�๫˾)�����������:" + ret_url;
			sendTextmsg(wid, ret_infoss);
		}
		else if (ky == L"�����ļ�") {
			wstring ret_url = L"https://docs.qq.com/desktop/mydoc/folder/aE33aoCXn0_100016";
			wstring ret_infoss = L"Ⱥ�����ļ�:���������:\n����Ѷ�ĵ���" + ret_url + L"\n��Books�⡿" + L"https://www.yuque.com/hongseshitou-n4dia/dy2fqv";
			sendTextmsg(wid, ret_infoss);

		}
		else {

			string info;
			//MessageBox(NULL, ky.c_str(), L"�յ���Ϣ", 0);
			int ret = getFiles(ky, SEARCH_DIRS, info);
			//MessageBox(NULL, (s2w(info)).c_str(), L"�յ���Ϣ", 0);
			if (ret == 0) {
				wstring ret_infoss = L"��ʽ����Ŀǰ��֧�ֹ�������:\n��1��Ⱥ�����ļ���ȡ:@robot #�����ļ������ĵ�����\n��2���Ʊ�23��:@robot #��Ʊ����";
				sendTextmsg(wid, ret_infoss);
			}
			else if (ret == 1) {
				SendFileMessage((wchar_t*)wid.c_str(), (wchar_t*)(s2w(info)).c_str());
			}
			else {
				sendTextmsg(wid, s2w(info));
			}
		}
	}

}