@Echo off

set build_path=build
if exist %build_path% (echo y| echo %build_path% exist) else (echo create %build_path%
 mkdir %build_path%)

@Echo on
cd %build_path%
cmake -G "MSYS Makefiles" ..
make install

pause
cmd.exe
