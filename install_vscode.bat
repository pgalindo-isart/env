URL=https://az764295.vo.msecnd.net/stable/5763d909d5f12fe19f215cbfdd29a91c0fa9208a/VSCode-win32-x64-1.45.1.zip
ZIP_FILE=VSCode-win32-x64-1.45.1.zip

if not exist "VSCode-win32-x64-1.45.1.zip" (
    bitsadmin /transfer "Download VSCode" /priority HIGH %URL% %CD%\%ZIP_FILE%
)

powershell Expand-Archive %ZIP_FILE% -DestinationPath vscode

pushd vscode\bin
call code --user-data-dir %~dp0/vscode-userdata --extensions-dir %~dp0/vscode-extensions --install-extension ms-vscode.cpptools
popd
