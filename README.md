# MouseHook-LL
A C++ Dll that calls `SetWindowsHookExW` with an input LowLevelMouseProc function. For use with AutoHotkey (AHK) to install a global low-level mouse hook.

To compile, load MouseHook-LL.sln in Visual Studio and build the project. You can then call `StartHook` and `StopHook` from AHK like any other dll function.

Here is a working demo script:

```
; https://github.com/Nich-Cebolla/AutoHotkey-LibV2/blob/main/Win32/MsLlHookStruct.ahk
#include <MsLlHookStruct>

; Set the path to the dll file on your machine. See file
; "https://github.com/Nich-Cebolla/AutoHotkey-LibV2/blob/main/Win32/MsLlHookStruct.ahk" for an explanation.
DllPath := ""

test()


class test {
    static Call() {
        g := this.Gui := Gui()
        g.SetFont('s11 q5', 'Segoe Ui')
        g.Add('Text', , 'Press start then move your mouse around.')
        g.Add('Edit', 'w300 r1 vEdt')
        g.Add('Button', 'Section vBtnStart', 'Start').OnEvent('Click', HClickButtonStart)
        g.Add('Button', 'ys vBtnStop', 'Stop').OnEvent('Click', HClickButtonStop)
        g.Add('Button', 'ys vBtnExit', 'Exit').OnEvent('Click', (*) => ExitApp())
        g.Show()
        this.hDll := DllCall('LoadLibrary', 'str', DllPath, 'ptr')
        this.start := DllCall('GetProcAddress', 'ptr', this.hDll, 'AStr', 'StartHook', 'ptr')
        this.stop := DllCall('GetProcAddress', 'ptr', this.hDll, 'AStr', 'StopHook', 'ptr')
        this.MouseHookProcPtr := CallbackCreate(LowLevelMouseProc)
        this.OnExitCallback := ObjBindMethod(this, 'Unhook')

        HClickButtonStart(*) {
            DllCall(this.start, 'ptr', this.MouseHookProcPtr, 'int')
            OnExit(this.OnExitCallback, 1)
        }
        HClickButtonStop(*) {
            this.Unhook()
        }
    }
    static Unhook(*) {
        DllCall(this.stop, 'int')
        OnExit(this.OnExitCallback, 0)
    }
}


LowLevelMouseProc(code, wParam, lParam) {
    if code == 0 {
        _mouseHookStruct := MsLlHookStruct(lParam, wParam)
        test.Gui['Edt'].Text := ('The mouse moved to ( ' _mouseHookStruct.X ', ' _mouseHookStruct.Y ' )`n')
    }
    return DllCall(
        'CallNextHookEx'
      , 'ptr', 0
      , 'int', code
      , 'uptr', wParam
      , 'ptr', lParam
      , 'ptr'
    )
}
```
