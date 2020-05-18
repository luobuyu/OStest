@echo off
setlocal EnableDelayedExpansion
set chZodiac[0]=0
set chZodiac[1]=��
set chZodiac[2]=ţ
set chZodiac[3]=��
set chZodiac[4]=��
set chZodiac[5]=��
set chZodiac[6]=��
set chZodiac[7]=��
set chZodiac[8]=��
set chZodiac[9]=��
set chZodiac[10]=��
set chZodiac[11]=��
set chZodiac[12]=��
set /A Month[0]=0, Month[1]=31, Month[2]=28, Month[3]=31, Month[4]=30, Month[5]=31, Month[6]=30
set /A Month[7]=31, Month[8]=31, Month[9]=30, Month[10]=31, Month[11]=30, Month[12]=31


set begin[0]=0
set begin[1]=0120
set begin[2]=0219
set begin[3]=0321
set begin[4]=0420
set begin[5]=0521
set begin[6]=0622
set begin[7]=0723
set begin[8]=0823
set begin[9]=0923
set begin[10]=1024
set begin[11]=1123
set begin[12]=1222
set end[1]=0219
set end[2]=0321
set end[3]=0420
set end[4]=0521
set end[5]=0622
set end[6]=0723
set end[7]=0823
set end[8]=0923
set end[9]=1024
set end[10]=1123
set end[11]=1222
set end[12]=0
set Cons[0]=0
set Cons[1]=ˮƿ��
set Cons[2]=˫����
set Cons[3]=������
set Cons[4]=��ţ��
set Cons[5]=˫����
set Cons[6]=��з��
set Cons[7]=ʨ����
set Cons[8]=��Ů��
set Cons[9]=�����
set Cons[10]=��Ы��
set Cons[11]=������
set Cons[12]=Ħ����

:input
echo please input your birthday(eg:2000-07-31)
set /p in=(input q or Q exit):
if %in% equ q exit
if %in% equ Q exit

::��ȡ������ʱ��
set /A year=%in:~0,4%
set /A month=%in:~5,2%
set /A day=%in:~8,2%
set strMonth=%in:~5,2%
set strDay=%in:~8,2%
::��ȡ����ǰʱ��
set /A curYear=%date:~0,4%
set /A curMonth=%date:~5,2%
set /A curDay=%date:~8,2%
::�ж�����
if %year% gtr %curYear% goto error
set /A lim=%curYear%-120
if %year% lss %lim% goto error

if %month% gtr 12 goto error
if %month% lss 1 goto error

if %day% gtr 31 goto error
if %day% lss 1 goto error
if %month% neq 2 if %day% gtr !Month[%month%]! goto error
::�ж�����
set /A leapFlag1=%year% %% 400
set /A leapFlag2=%year% %% 4
set /A leapFlag3=%year% %% 100
set /A flag=0
if %leapFlag1% equ 0 set /A flag=1
if %leapFlag2% equ 0 ( 
	if %leapFlag3% neq 0 ( 
		set /A flag=1 
	)
)
if %flag% equ 1 (
	if %month% equ 2 (
		if %day% gtr 29 (
			goto error 
		)
	)
) else (
	if %month% equ 2 (
		if %day% gtr 28 (
			goto error
		)
	)
)
set /A mod=((%year%+8) %% 12) + 1
echo ��������ǣ�!chZodiac[%mod%]!
for /L %%i in (1,1,12) do (
	set s=%strMonth%%strDay%
	if !s! gtr %begin[12]% (
		echo ���������Ħ����
		goto input
	)
	if !s! lss %begin[1]% (
		echo ���������Ħ����
		goto input
	)
	if !s! geq !begin[%%i]! if !s! lss !end[%%i]! ( 
		echo ��������ǣ�!Cons[%%i]! 
		goto input
	)
)

:error
echo your input is invilid. please enter again
goto input
pause