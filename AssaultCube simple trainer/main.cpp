#include "includes.h"


//this is my first ever cheat so it may not be that clean

int main() {
    system("MODE 40,10"); //resizes the console window
    
    HANDLE hProcess = 0;
    uintptr_t moduleBase = 0, localPlayerPtr = 0, healthAddr = 0, dualPistoladdr = 0, dualPistolAmmoaddr = 0;
    bool bHealth = false, bAmmo = false, bRecoil = false, bDualpistols = false, OnTop = false;
   
    const int off = 0, on = 1; 
    const int newValue = 80085 ,origValue = 100;
    const int magAmmo = 20;
    
    DWORD procId = GetProcessID(L"ac_client.exe");
    
    if (procId) {
        hProcess = OpenProcess(PROCESS_ALL_ACCESS, NULL, procId);

        moduleBase =  GetModuleBaseAdresss(procId, L"ac_client.exe");
        localPlayerPtr = moduleBase + 0x0017E0A8;

        healthAddr = FindDMAAddy(hProcess, localPlayerPtr, {0xEC});
        dualPistoladdr = FindDMAAddy(hProcess, localPlayerPtr, { 0x100 });
        dualPistolAmmoaddr = FindDMAAddy(hProcess, localPlayerPtr, { 0x148 });

        cmdUI(bHealth, bAmmo, bRecoil, bDualpistols, OnTop);
    }
    else {
        std::cout << "Process Id wasnt found make sure you have opened the game"<<"\n";
        getchar();
        return 0;
    }

    DWORD dwExit = 0;
        while (GetExitCodeProcess(hProcess, &dwExit) && dwExit == STILL_ACTIVE) {
            
            if (GetAsyncKeyState(VK_NUMPAD1) & 1) {
                
                bHealth = !bHealth; //sometimes in a bot lobby it just stops workinng keep that in mind5
                cmdUI(bHealth, bAmmo, bRecoil, bDualpistols, OnTop);//not very happy that i have to call it every time but its simple 
                
                if (!bHealth); {
                    
                    mem::PatchEx((BYTE*)healthAddr, (BYTE*)&origValue, sizeof(newValue), hProcess);
                }

            }
            if (GetAsyncKeyState(VK_NUMPAD2) & 1) {
                bAmmo = !bAmmo;
                cmdUI(bHealth, bAmmo, bRecoil, bDualpistols, OnTop);
                
                if (bAmmo) {

                    mem::PatchEx((BYTE*) (moduleBase + 0xC73EF), (BYTE*)"\xFF\x00",2,hProcess);//ammo
                    mem::PatchEx((BYTE*)(moduleBase + 0xC7E5D), (BYTE*)"\xFF\x00", 2, hProcess);//grenade
                }
                else {

                    mem::PatchEx((BYTE*)(moduleBase + 0xC73EF), (BYTE*)"\xFF\x08", 2, hProcess);//ammo
                    mem::PatchEx((BYTE*)(moduleBase + 0xC7E5D), (BYTE*)"\xFF\x08", 2, hProcess);//grenade
                }
            }
            if (GetAsyncKeyState(VK_NUMPAD3) & 1) {
                
                bRecoil = !bRecoil;
                cmdUI(bHealth, bAmmo, bRecoil, bDualpistols, OnTop);
                if (bRecoil) {
                    
                    mem::NopEx((BYTE*)(moduleBase + 0xC2EC3), 5, hProcess);
                }
                else {
                    mem::PatchEx((BYTE*)(moduleBase + 0xC2EC3), (BYTE*)"\xF3\x0F\x11\x56\x38",5, hProcess);//change it back to how it was
                }

            }
            if (GetAsyncKeyState(VK_NUMPAD4) & 1) {
                
                bDualpistols = !bDualpistols;
                cmdUI(bHealth, bAmmo, bRecoil, bDualpistols, OnTop);
                if (bDualpistols) {
                   
                    mem::PatchEx((BYTE*)dualPistoladdr, (BYTE*)&on, sizeof(on), hProcess);
                    mem::PatchEx((BYTE*)dualPistolAmmoaddr, (BYTE*)&magAmmo, sizeof(magAmmo), hProcess);//adds 20 ammo as you spawn with 0
                }
                else {
                    
                    mem::PatchEx((BYTE*)dualPistoladdr, (BYTE*)&off, sizeof(off), hProcess);
                    
                }

            }
            if (GetAsyncKeyState(VK_INSERT) & 1) {
                
                return 0;

            }
            if (GetAsyncKeyState(VK_NUMPAD5) & 1) {
                OnTop = !OnTop;
                cmdUI(bHealth, bAmmo, bRecoil, bDualpistols, OnTop);
                if (OnTop) {  
                    ::SetWindowPos(GetConsoleWindow(), HWND_TOPMOST, 0, 0, 0, 0, SWP_DRAWFRAME | SWP_NOMOVE | SWP_NOSIZE | SWP_SHOWWINDOW);//makes the console window always on top 
                    ::ShowWindow(GetConsoleWindow(), SW_NORMAL);
                }
                else {
                    ::SetWindowPos(GetConsoleWindow(), HWND_NOTOPMOST, 0, 0, 0, 0, SWP_DRAWFRAME | SWP_NOMOVE | SWP_NOSIZE | SWP_SHOWWINDOW);
                    ::ShowWindow(GetConsoleWindow(), SW_SHOWMINIMIZED);
                }


            }
            //continous write
            if (bHealth) {
 
                mem::PatchEx((BYTE*)healthAddr, (BYTE*)&newValue, sizeof(newValue), hProcess);
            }
            Sleep(15); //for performance
    }
}   


