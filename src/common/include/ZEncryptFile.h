#ifndef __ZENCRYPTFILE__
#define __ZENCRYPTFILE__

#define ERROR_FILE_HASCHANGED 0xFFFF0001


typedef size_t (WINAPI * PZEncryptFileReadFile)(PVOID buf,UINT bufsize,PVOID handle);
typedef size_t (WINAPI * PZEncryptFileWriteFile)(PVOID buf,UINT bufsize,PVOID handle);

HRESULT WINAPI ZEncryptFile(
							__in LPSTR filePath,
							__in PZEncryptFileWriteFile PWriteFile,
							__in PVOID handlewrite,
							__in UINT encryptType,
							__in PVOID password,
							__in size_t passwordlen
							);

HRESULT WINAPI ZDecryptFile(
							__in LPSTR filePath,
							__in PZEncryptFileReadFile PReadFile,
							__in PVOID handleread,
							//__in UINT encryptType,
							__in PVOID password,
							__in size_t passwordlen
							);

#endif