//�����ļ�
#pragma once

class CDecryptFile
{
public:
	CDecryptFile(void);
	~CDecryptFile(void);

	HRESULT WINAPI ZCDecryptFile(
		__in LPSTR filePath,
		__in PZEncryptFileReadFile PReadFile,
		__in PVOID handleread,
		//__in UINT encryptType,
		__in PVOID password,
		__in size_t passwordlen
		);

private:
	LPSTR m_filePath;
	PZEncryptFileReadFile m_PReadFile;
	PVOID m_handleread;
	UINT m_encryptType;
	PVOID m_password;
	size_t m_passwordlen;

	WIN32_FIND_DATAA m_fileData;



	HRESULT GetHeaderAndCheckPassword();
	//HRESULT ReadAndTransferOneBulk();

	PVOID GetOneBulk(UINT &bulksize,UINT &orgSize);//�����ͷ��ڴ�

	HRESULT UnCompressOneBuffer(PVOID * comdata,size_t *comdatalen,PVOID data,size_t datasize);

	void SetFileMsg();
};
