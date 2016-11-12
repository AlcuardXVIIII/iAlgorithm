#pragma once

#include <windows.h>

class _declspec(dllexport) CAES
{
public:
	CAES(VOID);
	~CAES(VOID);

public:
	enum AES_TYPE
	{
		AES_128_TYPE = 16,
		AES_192_TYPE = 24,
		AES_256_TYPE = 32,
	};

	enum AES_ENCRYPT_MODE
	{
		AES_EBC = 1,
		AES_CBC = 2,
		AES_FBC = 3,
	};

private:
	int Nk;
	int Nr;
	static const int Nb;
	ULONG key[8];
	BYTE Iv[16];
	ULONG RoundKey[60];
	int AesType;
	int EncryptType;

private:
	static const ULONG Rcon[11];
	static const BYTE SBox[256];
	static const BYTE InvSBox[256];

public:
	VOID AesSetIv(BYTE* pSetIv);
	BOOL AesInit(BYTE* pKey, int KeySize, int EncryptMode);
	BOOL Encrypt_EBC(BYTE* pBufferIn, int BufferInSize, BYTE* pBufferOut, int BufferOutSize);
	BOOL Decrypt_EBC(BYTE* pBufferIn, int BufferInSize, BYTE* pBufferOut, int BufferOutSize);

	BOOL Encrypt_CBC(BYTE* pBufferIn, int BufferInSize, BYTE* pBufferOut, int BufferOutSize);
	BOOL Decrypt_CBC(BYTE* pBufferIn, int BufferInSize, BYTE* pBufferOut, int BufferOutSize);

private:
	BOOL SetAESKey(BYTE* pKey, int KeySize);
	VOID AesRoundEncrypt(BYTE* pBlockIn, BYTE* pBlockOut);
	VOID AesRoundDecrypt(BYTE* pBlockIn, BYTE* pBlockOut);

private:
	//����Կ������չ����չΪ����Կ
	VOID AESKeyExpansion();
	//��״̬Ԫ��������Կ���м��������
	VOID AddRoundKey(BYTE* pState, BYTE* pRoundKey);
	//SubBytes  ��״̬������ÿ���ֽ�Ԫ�صĸ�4λ���б꣬��4λ���б꣬ȡ��ӦSBoxԪ��
	VOID SubBytes(BYTE* pState);
	//��״̬�������λ��
	VOID ShiftRows(BYTE* pState);
	//��״̬������о����������
	VOID MixColumns(BYTE* State);

	VOID InvSubBytes(BYTE* pState);
	VOID InvShiftRows(BYTE* pState);
	VOID InvMixColumns(BYTE* pState);

private:
	BYTE xtime(BYTE cByte);
	VOID SubWord(BYTE* dwTemp);
	VOID RotWord(BYTE* dwTemp);
};