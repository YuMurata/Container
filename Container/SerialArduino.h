#pragma once

#include"Handle.h"
#include<tchar.h>
class SerialArduino
	:public HandleClass
{
private:
	SerialArduino(const LPCTSTR &port_num)
		:HandleClass(port_num, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL){}

public:
	SerialArduino(const int &com_num)
	{
		TCHAR com[10];
		_stprintf_s(com, 10, TEXT("COM%d"), com_num);
		*this = SerialArduino(com);
	}

	void Init(const unsigned long &speed)
	{
		DCB dcb; // シリアルポートの構成情報が入る構造体
		GetCommState(this->handle, &dcb); // 現在の設定値を読み込み

		dcb.BaudRate = speed; // 速度
		dcb.ByteSize = 8; // データ長
		dcb.Parity = NOPARITY; // パリティ
		dcb.StopBits = ONESTOPBIT; // ストップビット長
		dcb.fOutxCtsFlow = FALSE; // 送信時CTSフロー
		dcb.fRtsControl = RTS_CONTROL_ENABLE; // RTSフロー

											  // 変更した設定値を書き込み
		SetCommState(this->handle, &dcb);
	}

	size_t Write(const char &word)
	{
		return this->Write(&word, 1);
	}

	size_t Write(const char *buf,const int &len)
	{
		DWORD lengthOfSent = len; // 送信するbyte数
		DWORD numberOfPut; // 実際に送信したbyte数

						   // ポートへ送信
		WriteFile(this->handle, buf, lengthOfSent, &numberOfPut, NULL);

		return numberOfPut;
	}

	int Available()
	{
		//受信データ数を調べる
		DWORD errors;
		COMSTAT comStat;
		ClearCommError(this->handle, &errors, &comStat);

		int lengthOfRecieved = comStat.cbInQue; // 受信したメッセージ長を取得する

		return lengthOfRecieved;
	}

	int Read()
	{
		//受信データがない場合は読み込まない
		if (this->Available() < 1)
		{
			return -1;
		}

		char buf[1]; // 受信データ格納用
		DWORD numberOfRead; // 実際に受信したバイト数

							//データ受信
		bool result = ReadFile(this->handle, buf, 1, &numberOfRead, NULL);

		if (result == FALSE)
		{
			return -1;
		}
		else
		{
			return buf[0];
		}
	}
};