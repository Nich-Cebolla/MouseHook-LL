#include "pch.h"
#include <windows.h>
#include <stdio.h>

HHOOK g_hHook = NULL;
HINSTANCE g_hInstance = NULL;

// Start the global hook with external function pointer
extern "C" __declspec(dllexport)
BOOL StartHook(HOOKPROC pfnHook) {
    if (!g_hHook) {
        g_hHook = SetWindowsHookExW(WH_MOUSE_LL, pfnHook, g_hInstance, 0);
    }
    return g_hHook != NULL;
}

// Remove the hook
extern "C" __declspec(dllexport)
void StopHook() {
    if (g_hHook) {
        UnhookWindowsHookEx(g_hHook);
        g_hHook = NULL;
    }
}

// DLL entry point
BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved) {
    if (ul_reason_for_call == DLL_PROCESS_ATTACH) {
        g_hInstance = hModule;
    }
    return TRUE;
}
