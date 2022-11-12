@echo off
echo CA - Compile Assemble
echo.

set produce = 0
set producetest = 0
set test = 0

if %1 == produce (goto produceG)
if %1 == test (goto testG)
if %1 == producetest (goto ptG)
goto e

:produceG
echo - CA: producing %2
if %2 == devenv (goto devenvG)
if %2 == os (goto osG)
goto e

:devenvG
python tools/readCAFile.py "%CD%" devenv
call temp.bat
del temp.bat
goto e

:osG
python tools/readCAFile.py "%CD%" os
call temp.bat
del temp.bat
goto e

:ptG
python tools/readCAFile.py "%CD%" os
call temp.bat
del temp.bat
goto testG

:testG
%qemuPath% -soundhw pcspk -drive file=OS.bin,format=raw -boot c
goto e

:e