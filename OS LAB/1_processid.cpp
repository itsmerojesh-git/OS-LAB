// CREATING A PROCESS AND DISPLAYING IT'S PROCESS ID
#include <windows.h>
#include <stdio.h>

int main() {
    STARTUPINFO si;
    PROCESS_INFORMATION pi;

    
    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    ZeroMemory(&pi, sizeof(pi));

    
    if (!CreateProcess(
            NULL,               
            "C:\\Windows\\System32\\notepad.exe", 
            NULL,               
            NULL,               
            FALSE,              
            0,                  
            NULL,               
            NULL,                
            &si,                
            &pi)                
        ) {
        printf("CreateProcess failed (%d).\n", GetLastError());
        return 1;
    }

  
    printf("Process ID: %lu\n", pi.dwProcessId);

    
    WaitForSingleObject(pi.hProcess, INFINITE);

    
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);

    return 0;
}
