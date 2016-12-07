call "C:\Program Files (x86)\Microsoft Visual Studio\2017\Community\VC\Auxiliary\Build\vcvarsall.bat" x86_x64

REM for git.exe and bison.exe
set "PATH=E:\Git\bin;%PATH%"

cd mruby
del vc140.pdb
ruby minirake clean
ruby minirake default
cd ..
pause