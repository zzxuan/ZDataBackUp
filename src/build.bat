@echo off
echo "start building ......"
echo "ɾ��build.log"
del build.log
echo "���� ./ZEncrypt/ZEncrypt.sln"
devenv.exe ./ZEncrypt/ZEncrypt.sln /Rebuild Release /out build.log
echo "���� ./minizlib/minizlib.sln"
devenv.exe ./minizlib/minizlib.sln /Rebuild Release /out build.log
echo "���� ./ZEncryptFile/ZEncryptFile.sln"
devenv.exe ./ZEncryptFile/ZEncryptFile.sln /Rebuild Release /out build.log
echo "���� ./ZShareMem/ZShareMem.sln"
devenv.exe ./ZShareMem/ZShareMem.sln /Rebuild Release /out build.log
echo "finished"
pause