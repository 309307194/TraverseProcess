//进程查看器
////write by niwodiy.com

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <Windows.h>
#include <stdlib.h>
#include <TlHelp32.h>

BOOL CloseProcess(DWORD dwId)
{
	BOOL bRet;
	HANDLE hHandle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, dwId);
	if (hHandle != NULL)
	{
		bRet = TerminateProcess(hHandle, 0);
	}
	CloseHandle(hHandle);

	return bRet;
}

int main(int argc, char* argv[])
{
	PROCESSENTRY32 pc;
	pc.dwSize = sizeof(pc);
	HANDLE hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (INVALID_HANDLE_VALUE == hProcessSnap)
	{
		printf("get snapshop failed!\n");
		
		return 0;
	}
	BOOL bMore = Process32First(hProcessSnap, &pc);
	while (bMore)
	{
		printf("\n--------------------------------------\n");
		printf("id:%d\n", pc.th32ProcessID);
		wprintf(L"name:%s\n", pc.szExeFile);
		bMore = Process32Next(hProcessSnap, &pc);
	}
	CloseHandle(hProcessSnap);

	int pid = 0;
	printf("请输入要关闭的进程id\n");
	scanf("%d", &pid);
	CloseProcess(pid);

	return 0;
}