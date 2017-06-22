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
		DCB dcb; // �V���A���|�[�g�̍\����񂪓���\����
		GetCommState(this->handle, &dcb); // ���݂̐ݒ�l��ǂݍ���

		dcb.BaudRate = speed; // ���x
		dcb.ByteSize = 8; // �f�[�^��
		dcb.Parity = NOPARITY; // �p���e�B
		dcb.StopBits = ONESTOPBIT; // �X�g�b�v�r�b�g��
		dcb.fOutxCtsFlow = FALSE; // ���M��CTS�t���[
		dcb.fRtsControl = RTS_CONTROL_ENABLE; // RTS�t���[

											  // �ύX�����ݒ�l����������
		SetCommState(this->handle, &dcb);
	}

	size_t Write(const char &word)
	{
		return this->Write(&word, 1);
	}

	size_t Write(const char *buf,const int &len)
	{
		DWORD lengthOfSent = len; // ���M����byte��
		DWORD numberOfPut; // ���ۂɑ��M����byte��

						   // �|�[�g�֑��M
		WriteFile(this->handle, buf, lengthOfSent, &numberOfPut, NULL);

		return numberOfPut;
	}

	int Available()
	{
		//��M�f�[�^���𒲂ׂ�
		DWORD errors;
		COMSTAT comStat;
		ClearCommError(this->handle, &errors, &comStat);

		int lengthOfRecieved = comStat.cbInQue; // ��M�������b�Z�[�W�����擾����

		return lengthOfRecieved;
	}

	int Read()
	{
		//��M�f�[�^���Ȃ��ꍇ�͓ǂݍ��܂Ȃ�
		if (this->Available() < 1)
		{
			return -1;
		}

		char buf[1]; // ��M�f�[�^�i�[�p
		DWORD numberOfRead; // ���ۂɎ�M�����o�C�g��

							//�f�[�^��M
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