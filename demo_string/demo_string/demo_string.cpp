// demo_string.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
#include<windows.h>
#include <iostream>
#include <string>
#include <io.h>
#include<stdlib.h>
#include<vector>
using namespace std;

#ifdef _DEBUG
    #define SEARCH_DIRS "C:\\Users\\swxxx\\Desktop\\temp\\2021-01"
#else
    #define SEARCH_DIRS "C:\\vplus\\"
#endif


bool IsdigitAll(wstring str)
{
    wstring::iterator ptr1 = str.begin();
    while (ptr1 != str.end()) {
        wchar_t chr = *(ptr1++);
        char ss = static_cast<char>(chr);
        if (!isdigit(ss)) {
            return false;
        }
        printf("%c", ss);
    }
    return true;
}

std::string w2s(const std::wstring& wstr)
{
    LPCWSTR pwszSrc = wstr.c_str();
    int nLen = WideCharToMultiByte(CP_ACP, 0, pwszSrc, -1, NULL, 0, NULL, NULL);
    if (nLen == 0)
        return std::string("");
    char* pszDst = new char[nLen];
    if (!pszDst)
        return std::string("");
    WideCharToMultiByte(CP_ACP, 0, pwszSrc, -1, pszDst, nLen, NULL, NULL);
    std::string str(pszDst);
    delete[] pszDst;
    pszDst = NULL;
    return str;
}

wstring s2w(string str)
{
    wstring result;
    //获取缓冲区大小，并申请空间，缓冲区大小按字符计算  
    int len = MultiByteToWideChar(CP_ACP, 0, str.c_str(), str.size(), NULL, 0);
    TCHAR* buffer = new TCHAR[len + 1];
    //多字节编码转换成宽字节编码  
    MultiByteToWideChar(CP_ACP, 0, str.c_str(), str.size(), buffer, len);
    buffer[len] = '\0';             //添加字符串结尾  
    //删除缓冲区并返回值  
    result.append(buffer);
    delete[] buffer;
    return result;
}

int getFiles(wstring search_str,string path,string &info)
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
                    ret += "["+ to_string(files)+"] "+ fileinfo.name +"\n";
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
        info = "找到与#"+ str +"相关的文件:\n"+ret;
    }
    return files;
}
int main()
{

    cout << SEARCH_DIRS << endl;

    /*
    wstring str = L"#4视频课笔记-A股详细版  ";
    int pos = str.find(L"#");
    int last = str.find_last_not_of(L" ");
    wstring search_str = str.substr(pos + 1, last);
    string filepath = "C:\\Users\\swxxx\\Desktop\\temp\\2021-01";
    string info;
    int ret = getFiles(search_str,filepath,info);
    cout << ret << w2s(s2w(info)) << endl;
    */
    

    //wstring a = L"@robot    #chatfile   ";
    //int pos = a.find(L"#");
    //int last = a.find_last_not_of(L" ");
    //wstring b = a.substr(pos + 1, last);
    //b.resize(last-pos);
    //bool isnum = IsdigitAll(b);
    //cout << endl;
    //if (isnum) {
    //    cout<<"is all number"<<endl;
    //}
    //else {
    //    cout << "is error" << endl;
    //}

   

    //struct filePath
    //{
    //    wchar_t* str;//4
    //    int strLen = 0;//4
    //    int maxLen = 0;//4
    //    char file[0x1C] = { 0 };
    //};

    //cout << sizeof(filePath) << endl;

    //wstring b = buf;

    
    //printf("%c ", buf[0]);
    //printf("%c ", buf[1]);
    //printf("%c ", buf[2]);
    //printf("%c ", buf[3]);
    //printf("%c ", buf[4]);
    //printf("%c ", buf[5]);
    //printf("%s", a.c_str());
    //std::cout << a.data()<<endl;
}
