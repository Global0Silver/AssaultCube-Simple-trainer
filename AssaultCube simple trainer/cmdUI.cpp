#include "includes.h"
#include "cmdUI.h"


void cmdUI(bool bHealth, bool bAmmo, bool bRecoil, bool bDualpistols,bool OnTop){
	const std::string RED = "\033[1;91m";
	const std::string GREEN = "\033[1;32m";
	const std::string RESET = "\033[0m";
	std::cout << "\033[2J\033[1;1H";//clears console
	std::cout << "        Made by Global0Silver         " <<"\n";
	std::cout << "   Simple AssaultCube 1.3.0.2 trainer" << "\n";

	std::string bools[2] = { RED + "[OFF]" + RESET, GREEN + "[ON]" + RESET };
	std::cout << "[Numpad1]Health hack       - " << bools[bHealth] << "\n";
	std::cout << "[Numpad2]Ammo hack         - " << bools[bAmmo] << "\n";
	std::cout << "[Numpad3]Recoil hack       - " << bools[bRecoil] << "\n";
	std::cout << "[Numpad4]Dualpistol hack   - " << bools[bDualpistols] << "\n";
	std::cout << "[Numpad5]CMD always on top - " << bools[OnTop] << "\n";
	std::cout << "[Insert ]Exit";
}