@ECHO OFF
:start
title С��VPS�ͻ�����ϵͳ��� by SmallBamboo
@echo.��ʼ����
"D:\AnacondaEnvs\PyFlask\python.exe" D:\����\������\04_IDE��ϰ��Ŀ\Python\BeijingSubway\app.py
@echo ���������10����Զ��������粻��Ҫ��������ֱ�ӹص�
choice /t 10 /d y /n >nul
goto start
pause