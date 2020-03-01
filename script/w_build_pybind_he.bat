@echo off
set LOGFILE=log.txt
call :LOG > %LOGFILE%
exit /B

:LOG
g++ -pthread -DNDEBUG -g -fwrapv -O2 -Wall -g ^
-m64 ^
-fstack-protector-strong -Wformat -Werror=format-security -Wdate-time ^
-D_FORTIFY_SOURCE=2 ^
-fPIC -I..\lib\pybind11 ^
-I..\lib\helib_pack\include ^
-IC:\Python36\include ^
-c ..\pybind_he\pybind_he.cpp ^ 
-o ..\build\pybind_he.o > log.txt
