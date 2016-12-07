call "C:\Program Files (x86)\Microsoft Visual Studio 14.0\VC\vcvarsall.bat"

REM for git.exe and bison.exe
set "PATH=E:\Git\bin;%PATH%"

cd mruby
ruby minirake clean
ruby minirake default
cd ..