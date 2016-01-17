#ifndef __ZENCRYPTFILE__
#define __ZENCRYPTFILE__

typedef size_t (WINAPI * PZEncryptFileReadFile)(PVOID buf,UINT bufsize,PVOID handle);
typedef size_t (WINAPI * PZEncryptFileWriteFile)(PVOID buf,UINT bufsize,PVOID handle);

#endif