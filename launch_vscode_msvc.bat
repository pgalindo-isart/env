call config.bat

call "C:\Program Files (x86)\Microsoft Visual Studio\2019\Enterprise\Common7\Tools\VsDevCmd.bat" -arch=x64

set HOME=
set PATH=%PATH%;%CYGWIN_PATH%/bin/;%CYGWIN_PATH%/usr/x86_64-w64-mingw32/sys-root/mingw/bin
set SHELL=/bin/bash

pushd vscode
set VSCODE_DEV=
set ELECTRON_RUN_AS_NODE=1
start Code.exe "%~dp0vscode\resources\app\out\cli.js" --user-data-dir %~dp0/vscode-userdata --extensions-dir %~dp0/vscode-extensions
popd
