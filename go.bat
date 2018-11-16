@echo off
if %1==run start .\x64\Release\rain.exe
if %1==ide start .\rain.sln
if %1==test call scons -j 8 && .\x64\Release\rain.exe
if %1==build call scons -j 8

