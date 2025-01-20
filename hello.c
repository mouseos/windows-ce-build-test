#include <windows.h>
#include <stdio.h>

#define DLL_EXPORT __declspec(dllexport)

// 指定パスのexeを起動する関数
DLL_EXPORT void run_exe(const char* path) {
    if (path == NULL) {
        return;
    }

    STARTUPINFO si;
    PROCESS_INFORMATION pi;

    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    ZeroMemory(&pi, sizeof(pi));

    if (!CreateProcess(
            path,
            NULL,
            NULL,
            NULL,
            FALSE,
            0,
            NULL,
            NULL,
            &si,
            &pi)) {
        DWORD error = GetLastError();
        printf("Failed to start process. Error: %lu\\n", error);
        return;
    }

    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);
}

DLL_EXPORT void run_txt() {
    const char* filePath = "A:\\\\run.txt";
    char exePath[MAX_PATH];

    FILE* file = fopen(filePath, "r");
    if (file == NULL) {
        printf("Failed to open %s\\n", filePath);
        return;
    }

    if (fgets(exePath, sizeof(exePath), file) != NULL) {
        size_t len = strlen(exePath);
        if (len > 0 && exePath[len - 1] == '\\n') {
            exePath[len - 1] = '\\0';
        }
        run_exe(exePath);
    } else {
        printf("Failed to read from %s\\n", filePath);
    }

    fclose(file);
}

BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpReserved) {
    return TRUE;
}
