@echo off
echo "start building ......"
echo "ɾ��build.log"
del build.log
echo "���� ./ZEncrypt/ZEncrypt.sln"
devenv.exe ./ZEncrypt/ZEncrypt.sln /Rebuild Release /out build.log
echo "���� ./minizlib/minizlib.sln"
devenv.exe ./minizlib/minizlib.sln /Rebuild Release /out build.log
echo "finished"
pause