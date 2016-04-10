@echo off
echo "start building ......"
echo "…æ≥˝build.log"
del build.log
echo "±‡“Î ./ZEncrypt/ZEncrypt.sln"
devenv.exe ./ZEncrypt/ZEncrypt.sln /Rebuild Release /out build.log
echo "±‡“Î ./minizlib/minizlib.sln"
devenv.exe ./minizlib/minizlib.sln /Rebuild Release /out build.log
echo "±‡“Î ./ZEncryptFile/ZEncryptFile.sln"
devenv.exe ./ZEncryptFile/ZEncryptFile.sln /Rebuild Release /out build.log
echo "±‡“Î ./ZShareMem/ZShareMem.sln"
devenv.exe ./ZShareMem/ZShareMem.sln /Rebuild Release /out build.log
echo "±‡“Î ./ZConvertFile/ZConvertFile.sln"
devenv.exe ./ZConvertFile/ZConvertFile.sln /Rebuild Release /out build.log
echo "±‡“Î ./ZEncrpt_GUI/ZEncrpt_GUI.sln"
devenv.exe ./ZEncrpt_GUI/ZEncrpt_GUI.sln /Rebuild Release /out build.log
echo "±‡“Î ./ZDencrpt_GUI/ZDencrpt_GUI.sln"
devenv.exe ./ZDencrpt_GUI/ZDencrpt_GUI.sln /Rebuild Release /out build.log
echo "finished"
pause