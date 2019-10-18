
if not exist "VSCode-win32-x64-1.39.2.zip" (
    bitsadmin /transfer "Download VSCode" /priority HIGH https://az764295.vo.msecnd.net/stable/6ab598523be7a800d7f3eb4d92d7ab9a66069390/VSCode-win32-x64-1.39.2.zip
)

powershell Expand-Archive VSCode-win32-x64-1.39.2.zip -DestinationPath vscode

pushd vscode\bin
call code --user-data-dir %~dp0/vscode-userdata --extensions-dir %~dp0/vscode-extensions --install-extension ms-vscode.cpptools
popd
