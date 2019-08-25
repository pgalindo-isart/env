call config.bat

:: Cygwin package list
:: This list can be used to update cygwin
set PACKAGES=tmux,vim,openssh,git,tig,mingw64-x86_64-gcc-g++,gdb,make,unzip,wget,bash-completion,ctags,tree
set PACKAGES=%PACKAGES%,mingw64-x86_64-SDL2,mingw64-x86_64-SDL2_image,mingw64-x86_64-SDL2_mixer,mingw64-x86_64-SDL2_ttf,mingw64-x86_64-SDL2_net

:: Download cygwin
if not exist "setup-x86_64.exe" (
	bitsadmin /transfer "Download Cygwin" /priority HIGH https://cygwin.com/setup-x86_64.exe %CD%\setup-x86_64.exe
)
:: Install cygwin
setup-x86_64.exe --no-admin --no-desktop --no-shortcuts --no-startmenu --quiet-mode --root %CD%\cygwin64 --local-package-dir %CD%\cygwin-packages --packages %PACKAGES% 

:: Add custom skeleton files (will be later copied to home folder)
xcopy /s /y skel cygwin64\etc\skel
