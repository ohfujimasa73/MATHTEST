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

echo [3/4] Compiling sample_cpp.cpp and linking ...
%CXX% -Wall -Wextra -o sample_cpp.exe sample_cpp.cpp arithmetic.lib
if errorlevel 1 goto :error

echo [4/4] Compiling calc_cli.c and linking ...
%CC% -Wall -Wextra -o calc_cli.exe calc_cli.c arithmetic.lib
if errorlevel 1 goto :error

echo [5/5] Compiling and running test_Ctest.c ...
%CC% -Wall -Wextra -o test_Ctest.exe test_Ctest.c arithmetic.c
if errorlevel 1 goto :error
test_Ctest.exe
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
