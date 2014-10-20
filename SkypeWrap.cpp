/*
	SkypeWrap 0.5 by md6
	Release date: October 19, 2014
	This application hides the advertisements within the Windows version of Skype.
	-------------------------------------------------------------------------------
	Usage Information:
	
	If this is your first time running SkypeWrap:
	---------------------------------------------
	1) Run SkypeWrap.exe
	2) Put in the full path to your Skype.exe
	3) SkypeWrap will create config.cfg and launch Skype
	4) SkypeWrap will load Skype and sit in the background while hiding ads until closed
	
	If you have created the config.cfg before:
	------------------------------------------
	1) Run SkypeWrap.exe
	2) SkypeWrap will load Skype and sit in the background while hiding ads until closed

	-------------------------------------------------------------------------------
	This program is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "stdafx.h"
#include <iostream>
#include <Windows.h>
#include <fstream>
#include <string>

// Hide the Skype ads
void hide_skype()
{
	HWND skype = FindWindow(L"tSkMainForm", 0);
	HWND child1 = FindWindowEx(skype, 0, L"TChatBanner", 0);
	HWND child2 = FindWindowEx(child1, 0, L"Shell Embedding", 0);
	HWND child3 = FindWindowEx(child2, 0, L"Shell DocObject View", 0);
	HWND ad1 = FindWindowEx(skype, 0, L"TDCEmbedBanner", 0);
	HWND ad2 = FindWindowEx(child3, 0, L"Internet Explorer_Server", 0);
	if (skype) {
		if (ad1) {
			ShowWindow(ad1, 0);
			Sleep(1000);
			if (ad2) {
				ShowWindow(ad2, 0);
				Sleep(1000);
			}
		}
	}
}

// Check for the existence of the config file
bool does_exist(const char* file)
{
	std::ifstream infile(file);
	return infile.good();
}

// Is Skype already open?
bool skype_open() 
{
	HWND skype = FindWindow(L"tSkMainForm", 0);
	if (skype) {
		return true;
	}
	return false;
}

// Load the Skype application
HINSTANCE load_skype() 
{
	std::ifstream config_file;
	std::string line;
	config_file.open("config.cfg");
	if (config_file.good()) {
		std::getline(config_file, line);
		config_file.close();
		return ShellExecuteA(NULL, "open", line.c_str(), NULL, NULL, SW_SHOWNORMAL);
	}
}

int _tmain(int argc, _TCHAR* argv[])
{
	if (skype_open()) {
		std::cout << "Please exit Skype before running SkypeWrap." << std::endl;
		std::cout << "Press enter to exit..." << std::endl;
		std::getchar();
		return 1;
	}

	std::string skype_path;
	std::ofstream config_file;
	bool ads_hidden = false;

	if (!does_exist("config.cfg")) {
		std::cout << "=> This appears to be your first time running SkypeWrap. Please input the full path to your Skype application." << std::endl;
		std::getline(std::cin, skype_path);
		config_file.open("config.cfg");
		if (config_file.good()) {
			config_file << "\"" + skype_path + "\"";
		}
		config_file.close();

		HINSTANCE c = load_skype();
		if (c) {
			std::cout << "Skype has been loaded. I will sit in the background and hide ads." << std::endl;
			while (1) {
				hide_skype();
				Sleep(500);
			}
		}
	}
	else {
		HINSTANCE c = load_skype();
		if (c) {
			std::cout << "Skype has been loaded. I will sit in the background and hide ads." << std::endl;
			while (1) {
				hide_skype();
				Sleep(500);
			}
		}
	}
	return 0;
}
