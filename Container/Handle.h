#pragma once
#include<Windows.h>

class HandleClass
{
private:
	HANDLE handle;

public:
	HandleClass
	(
		const LPCTSTR &lpFileName,                         // �t�@�C����
		const DWORD &dwDesiredAccess,                      // �A�N�Z�X���[�h
		const DWORD dwShareMode,                          // ���L���[�h
		const LPSECURITY_ATTRIBUTES lpSecurityAttributes, // �Z�L�����e�B�L�q�q
		const DWORD dwCreationDisposition,                // �쐬���@
		const DWORD dwFlagsAndAttributes,                 // �t�@�C������
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