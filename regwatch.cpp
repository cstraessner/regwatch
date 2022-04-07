// regwatch.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <windows.h>
#pragma comment (lib,"Advapi32")

int main()
{
    HKEY key;
    HKEY result;
    LSTATUS status = -1;
    DWORD lasterrror = 0;
    HANDLE hEvent = INVALID_HANDLE_VALUE;
        
    hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);



    status = RegOpenKeyEx(HKEY_LOCAL_MACHINE, L"SYSTEM\\CurrentControlSet\\Services\\HTTP\\Parameters", 0, KEY_ALL_ACCESS, &result);

    if (status != ERROR_SUCCESS)
    {
        DWORD lasterrror = GetLastError();
        std::cout << "error opening key" << std::hex << lasterrror << std::endl;
        exit(lasterrror);
    }
     status = RegNotifyChangeKeyValue(result, true, REG_NOTIFY_CHANGE_LAST_SET,hEvent,TRUE);
     if (status != ERROR_SUCCESS)
     {
         DWORD lasterrror = GetLastError();
         std::cout << "RegNotifyChangeKeyValue" << std::hex << lasterrror << std::endl;
         exit(lasterrror);
     }

    std::cout << "waiting for change  to happen....\n";
    if (WaitForSingleObject(hEvent, INFINITE) == WAIT_FAILED)
    {
        std::cout << "Error in WaitForSingleObject" << std::hex << GetLastError();
        return lasterrror ;
    }
    std::cout << "a change  to the monitored  key  happend" << std::endl;
    return lasterrror;
}

