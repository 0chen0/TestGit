#SingleInstance, Force
SendMode Input
SetWorkingDir, %A_ScriptDir%

#NoEnv
#WinActivateForce

; -------------------  窗口跳转
~LButton & XButton2::
		WinGetActiveTitle, Title
		WinGet, pName, ProcessName, %Title%
		If (!pName)
		{
			return
		}
		WinGet, MarkWin_Default_1, ID, A
		return
XButton2::
		WinGet, MarkWin_Cur, ID, A
		if (MarkWin_Cur != MarkWin_Default_1)
		{
			if (MarkWin_Cur != MarkWin_Default_2) {
				WinGetClass, pName , A
				if (pName != "WorkerW") {
					MarkWin_Tmp_1 = %MarkWin_Cur%
				}
			}
			WinActivate, ahk_id %MarkWin_Default_1%
		} Else {
			WinActivate, ahk_id %MarkWin_Tmp_1%
		}
		return

CapsLock & S::
		WinGetActiveTitle, Title
		WinGet, pName, ProcessName, %Title%
		If (!pName)
		{
			return
		}
		WinGet, MarkWin_Default_2, ID, A
		return
CapsLock & A::
		WinGet, MarkWin_Cur, ID, A
		if (MarkWin_Cur != MarkWin_Default_2)
		{
			if (MarkWin_Cur != MarkWin_Default_1) {
				WinGetClass, pName , A
				if (pName != "WorkerW") {
					MarkWin_Tmp_2 = %MarkWin_Cur%
				}
			}
			WinActivate, ahk_id %MarkWin_Default_2%
		} Else {
			WinActivate, ahk_id %MarkWin_Tmp_2%
		}
		return

; -------------------  剪切板
CapsLock & V::
	filename := "C:\Users\57148\Desktop\tmp.txt"
	wfd := FileOpen(filename, "w")
	string := clipboard
	wfd.Write(string)
	wfd.Close()
	
	InputBox, OutputVar, |  文本替换  |, , , 320, 97, 700, 500
	commands=
	(join&
		python "F:\0\script\py-test\test.py" "%OutputVar%"`n
	)
	RunWait, cmd /c %commands%  
	
	rfd := FileOpen(filename, "r")
	OutputVar := rfd.Read()
	rfd.Close()
	clipboard := OutputVar
	return

; -------------------  测试用, 打印当前活跃窗口信息
CapsLock & Tab::
		WinGet, win_id, ID, A
		WinGet, win_name, ProcessName, A
		WinGetClass, win_class , A
		MsgBox, %win_id%, %win_name%, %win_class%
		return

; -------------------  临时记录窗口
<^<#<!Numpad0::
	WinGetClass, pName , A
	if (pName == "WorkerW") {
		return 
	}
	WinGet, MarkWin_Cur, ID, A
	WinShow, ahk_id %MarkWin_0%
	MarkWin_0 = %MarkWin_Cur%
	return
<^RButton::
	IfWinActive, ahk_id %MarkWin_0% 
	{
		WinHide, ahk_id %MarkWin_0%
		WinActivate, ahk_id %MarkWin_Tmp_0%
	} Else {
		WinGetClass, pName , A
		if (pName != "WorkerW") {
			WinGet, MarkWin_Tmp_0, ID, A
		}
		WinShow, ahk_id %MarkWin_0%
		WinActivate, ahk_id %MarkWin_0%
	}
	return

OnExit, ExitScript
return
ExitScript:
WinShow, ahk_id %MarkWin_0%
ExitApp  ; Do a true exit.
