if exist userconfig.bat call userconfig.bat

set WIN32_PATH=C:\Windows\System32
if not defined CYGWIN_PATH set CYGWIN_PATH=%~dp0cygwin64

:: Clean PATH variable
set PATH=
set PATH=%PATH%;%WIN32_PATH%

