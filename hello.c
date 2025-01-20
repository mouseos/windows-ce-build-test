#include <windows.h>
#include <stdio.h>

// DLLエクスポート用マクロ
#define DLL_EXPORT __declspec(dllexport)

// 指定パスのexeを起動する関数
extern "C" DLL_EXPORT void run_exe(const char* path) {
    if (path == NULL) {
        return;
    }

    // CreateProcessを使用してEXEを起動
    STARTUPINFO si;
    PROCESS_INFORMATION pi;

    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    ZeroMemory(&pi, sizeof(pi));

    if (!CreateProcess(
            path,      // 実行するEXEのパス
            NULL,      // コマンドライン引数
            NULL,      // セキュリティ属性
            NULL,      // スレッドセキュリティ属性
            FALSE,     // 子プロセスが親のハンドルを継承するかどうか
            0,         // 作成フラグ
            NULL,      // 環境変数
            NULL,      // カレントディレクトリ
            &si,       // STARTUPINFO構造体
            &pi        // PROCESS_INFORMATION構造体
        )) {
        // エラー処理
        DWORD error = GetLastError();
        printf("Failed to start process. Error: %lu\n", error);
        return;
    }

    // プロセスとスレッドハンドルを閉じる
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);
}

// A:\run.txtを読み取り、そのパスでrun_exeを実行する関数
extern "C" DLL_EXPORT void run_txt() {
    const char* filePath = "A:\\run.txt";
    char exePath[MAX_PATH];

    // ファイルを開く
    FILE* file = fopen(filePath, "r");
    if (file == NULL) {
        printf("Failed to open %s\n", filePath);
        return;
    }

    // ファイルから1行読み込む
    if (fgets(exePath, sizeof(exePath), file) != NULL) {
        // 改行を削除
        size_t len = strlen(exePath);
        if (len > 0 && exePath[len - 1] == '\n') {
            exePath[len - 1] = '\0';
        }

        // 読み取ったパスでrun_exeを呼び出し
        run_exe(exePath);
    } else {
        printf("Failed to read from %s\n", filePath);
    }

    // ファイルを閉じる
    fclose(file);
}

// DLLエントリポイント
BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpReserved) {
    switch (fdwReason) {
        case DLL_PROCESS_ATTACH:
            // DLLがプロセスにロードされたときの初期化
            break;
        case DLL_THREAD_ATTACH:
        case DLL_THREAD_DETACH:
            // スレッドが作成/終了したときの処理
            break;
        case DLL_PROCESS_DETACH:
            // DLLがプロセスからアンロードされたときのクリーンアップ
            break;
    }
    return TRUE;
}
