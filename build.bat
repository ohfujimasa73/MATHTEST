@echo off
setlocal
set CC=clang
set CXX=clang++
set AR=llvm-ar

echo [1/3] Compiling arithmetic.c ...
%CC% -c arithmetic.c -o arithmetic.obj
if errorlevel 1 goto :error

echo [2/3] Creating static library arithmetic.lib ...
%AR% rcs arithmetic.lib arithmetic.obj
if errorlevel 1 goto :error

echo [3/3] Compiling sample_cpp.cpp and linking ...
%CXX% -Wall -Wextra -o sample_cpp.exe sample_cpp.cpp arithmetic.lib
if errorlevel 1 goto :error

echo.
echo Build succeeded. Running sample_cpp.exe ...
echo ----------------------------------------
sample_cpp.exe
goto :end

:error
echo.
echo Build FAILED.
exit /b 1

:end
endlocal
