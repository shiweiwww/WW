// upload.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include<windows.h>
#include<stdio.h>
#include<conio.h>
//void main()
//{
//	//监视C盘根目录下文件名改变的例子，其中while循环一直监控，知道程序关闭
//	const char* szStr = "D:/upload/";
//	WCHAR wszClassName[256];
//	memset(wszClassName, 0, sizeof(wszClassName));
//	MultiByteToWideChar(CP_ACP, 0, szStr, strlen(szStr) + 1, wszClassName,sizeof(wszClassName) / sizeof(wszClassName[0]));
//	HANDLE hChangeHandle = FindFirstChangeNotification(wszClassName, false, FILE_NOTIFY_CHANGE_FILE_NAME);
//	//判断是否设置成功
//	if (hChangeHandle == INVALID_HANDLE_VALUE)
//	{
//		printf("Find First Change Notification failed\n");
//		return;
//	}
//	//等待通知 
//	if (WaitForSingleObject(hChangeHandle, -1) == 0)
//	{
//		printf("These change a file name\n");
//	}
//	//循环等待
//	while (true)
//	{
//		if (FindNextChangeNotification(hChangeHandle))
//		{
//			if (WaitForSingleObject(hChangeHandle, -1) == 0)
//			{
//				printf("These change a file name\n");
//			}
//		}
//	}
//	//结束监视程序调用FindCloseChangeNotification关闭句柄
//	FindCloseChangeNotification(hChangeHandle);
//	//按键退出程序
//	_getch();
//}



