#pragma once
#include<Windows.h>

class HandleClass
{
private:
	HANDLE handle;

public:
	HandleClass
	(
		const LPCTSTR &lpFileName,                         // ファイル名
		const DWORD &dwDesiredAccess,                      // アクセスモード
		const DWORD dwShareMode,                          // 共有モード
		const LPSECURITY_ATTRIBUTES lpSecurityAttributes, // セキュリティ記述子
		const DWORD dwCreationDisposition,                // 作成方法
		const DWORD dwFlagsAndAttributes,                 // ファイル属性
		const HANDLE hTemplateFile
	)
		:handle(CreateFile(lpFileName, dwDesiredAccess, dwShareMode, lpSecurityAttributes, dwCreationDisposition, dwFlagsAndAttributes, hTemplateFile)) {}

	HandleClass()
		:handle(nullptr) {}

	~HandleClass()
	{
		if (this->handle)
		{
			CloseHandle(this->handle);
		}
	}

	HANDLE Get()const
	{
		return this->handle;
	}
};