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
echo "���� ./ZConvertFile/ZConvertFile.sln"
devenv.exe ./ZConvertFile/ZConvertFile.sln /Rebuild Release /out build.log
echo "���� ./ZEncrpt_GUI/ZEncrpt_GUI.sln"
devenv.exe ./ZEncrpt_GUI/ZEncrpt_GUI.sln /Rebuild Release /out build.log
echo "finished"
pause