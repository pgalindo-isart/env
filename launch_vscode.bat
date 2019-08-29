call config.bat

set HOME=
set PATH=%PATH%;%CYGWIN_PATH%/bin/;%CYGWIN_PATH%/usr/x86_64-w64-mingw32/sys-root/mingw/bin
set SHELL=/bin/bash

pushd vscode\bin
call code --user-data-dir %~dp0/vscode-userdata --extensions-dir %~dp0/vscode-extensions
popd
