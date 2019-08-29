
if not exist "VSCode-win32-x64.zip" (
    bitsadmin /transfer "Download VSCode" /priority HIGH https://az764295.vo.msecnd.net/stable/f06011ac164ae4dc8e753a3fe7f9549844d15e35/VSCode-win32-x64-1.37.1.zip %CD%\VSCode-win32-x64.zip
)

powershell Expand-Archive VSCode-win32-x64.zip -DestinationPath vscode

pushd vscode\bin
call code --user-data-dir %~dp0/vscode-userdata --extensions-dir %~dp0/vscode-extensions --install-extension ms-vscode.cpptools
popd
