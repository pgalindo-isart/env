set URL=https://az764295.vo.msecnd.net/stable/e790b931385d72cf5669fcefc51cdf65990efa5d/VSCode-win32-x64-1.49.0.zip
set ZIP_FILE=VSCode-win32-x64-1.49.0.zip

if not exist %ZIP_FILE% (
    bitsadmin /transfer "Download VSCode" /priority HIGH %URL% %CD%\%ZIP_FILE%
)

powershell Expand-Archive %ZIP_FILE% -DestinationPath vscode

pushd vscode\bin
call code --user-data-dir %~dp0/vscode-userdata --extensions-dir %~dp0/vscode-extensions --install-extension ms-vscode.cpptools
popd
