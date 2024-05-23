@ECHO OFF
:start
title 小竹VPS客户管理系统后端 by SmallBamboo
@echo.开始启动
"D:\AnacondaEnvs\PyFlask\python.exe" D:\桌面\编程相关\04_IDE练习项目\Python\BeijingSubway\app.py
@echo 服务器后端10秒后自动重启，如不需要重启，请直接关掉
choice /t 10 /d y /n >nul
goto start
pause