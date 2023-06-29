@echo off
:A
Cls
echo Messenger
set /p n=User:
set /p m=Message:
net send %N% %M%
Pause
Goto A