@echo off
echo "start building ......"
echo "…æ≥˝build.log"
del build.log
echo "±‡“Î ./ZEncrypt/ZEncrypt.sln"
devenv.exe ./ZEncrypt/ZEncrypt.sln /Rebuild Release /out build.log
echo "±‡“Î ./minizlib/minizlib.sln"
devenv.exe ./minizlib/minizlib.sln /Rebuild Release /out build.log
echo "finished"
pause