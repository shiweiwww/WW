#include "framework.h"
#include<windows.h>
#include <iostream>
#include <string>
#include <io.h>
using namespace std;

int getFiles(wstring search_str, string path, string& info)
{
	string str = w2s(search_str);
	//文件句柄
	long  hFile = 0;
	//文件信息
	struct _finddata_t fileinfo;
	int files = 0;
	string p;
	string ret = "";
	string first_one = "";
	if ((hFile = _findfirst(p.assign(path).append("\\*").c_str(), &fileinfo)) != -1)
	{
		do
		{
			//是否为目录
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
		info = "#未找到文件,请查看是否输入格式有错误!";
	}
	else if (files == 1) {
		info = first_one;
	}
	else {
		info = "找到与#" + str + "相关的文件:\n" + ret;
	}
	return files;
}

void dispatch(wstring wid, wstring msg) {

	wstring wwid = wid;
	wstring a = msg.substr(0, ROBOT_LEN);
	if (a != ROBOT) {
		//wstring ss = L"问下我师傅吧，我不清楚你要问什么:https://www.yuque.com/hongseshitou-n4dia/lqi07d";
		//sendTextmsg(wid, msg.substr(0,6));
	}
	else {
		int pos = msg.find(L"#");
		int last = msg.find_last_not_of(L" ");
		wstring ky = msg.substr(pos + 1, last);
		ky.resize(last - pos);
		//MessageBox(NULL, ky.c_str(), L"收到消息", 0);
		bool isnum = IsdigitAll(w2s(ky));
		if (isnum) {
			wstring ret_url = L"https://www.yuque.com/hongseshitou-n4dia/bcu1bk/" + ky;
			wstring ret_infoss = L"查到股票代码为:" + ky + L"报告(目前不支持保险类银行类和证券类公司)，请访问链接:" + ret_url;
			sendTextmsg(wid, ret_infoss);
		}
		else if (ky == L"聊天文件") {
			wstring ret_url = L"https://docs.qq.com/desktop/mydoc/folder/aE33aoCXn0_100016";
			wstring ret_infoss = L"群聊天文件:请访问链接:\n【腾讯文档】" + ret_url + L"\n【Books库】" + L"https://www.yuque.com/hongseshitou-n4dia/dy2fqv";
			sendTextmsg(wid, ret_infoss);

		}
		else {

			string info;
			//MessageBox(NULL, ky.c_str(), L"收到消息", 0);
			int ret = getFiles(ky, SEARCH_DIRS, info);
			//MessageBox(NULL, (s2w(info)).c_str(), L"收到消息", 0);
			if (ret == 0) {
				wstring ret_infoss = L"格式错误，目前仅支持功能如下:\n【1】群聊天文件获取:@robot #聊天文件或者文档名称\n【2】财报23步:@robot #股票代码";
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