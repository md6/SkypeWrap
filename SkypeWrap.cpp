/*
	SkypeWrap 0.3 by md6
	Release date: October 19, 2014
	This application hides the advertisements within the Windows version of Skype.
	-------------------------------------------------------------------------------
	Usage Information:
	
	If this is your first time running SkypeWrap:
	---------------------------------------------
	1) Run SkypeWrap.exe
	2) Put in the full path to your Skype.exe
	3) SkypeWrap will create config.cfg and launch Skype
	4) You will have 30 seconds to login to Skype and make sure that advertisements are showing
	5) SkypeWrap will then hide the ads and exit

	If you have created the config.cfg before:
	------------------------------------------
	1) Run SkypeWrap.exe
	2) You will have 30 seconds to login to Skype and make sure that advertisements are showing
	3) SkypeWrap will then hide the ads and exit

	If Skype is already running:
	----------------------------
	1) Run SkypeWrap to hide ads

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
		}
		if (ad2) {
			ShowWindow(ad2, 0);
		}
	}
}

// Check for the existence of the config file
bool does_exist(const char* file)
{
	std::ifstream infile(file);
	return infile.good();
}

int _tmain(int argc, _TCHAR* argv[])
{
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
		std::ifstream config_file2;
		std::string line;
		Sleep(1000);
		config_file2.open("config.cfg");
		if (config_file2.good()) {
			std::getline(config_file2, line);
			HINSTANCE c = ShellExecuteA(NULL, "open", line.c_str(), NULL, NULL, SW_SHOWNORMAL);
			if (c) {
				std::cout << "Skype has been loaded. Please make sure ads are in view." << std::endl;
				std::cout << "SkypeWrap will hide ads in 30 seconds and will exit." << std::endl;
			}
			Sleep(30000);
			while (!ads_hidden) {
				hide_skype();
				ads_hidden = true;
			}
			return 0;
		}
		config_file2.close();
	}
	else {
		HWND skype = FindWindow(L"tSkMainForm", 0);
		if (skype) {
			hide_skype();
		}
		else {
			std::ifstream config_file2;
			std::string line;
			config_file2.open("config.cfg");
			if (config_file2.good()) {
				std::getline(config_file2, line);
				HINSTANCE c = ShellExecuteA(NULL, "open", line.c_str(), NULL, NULL, SW_SHOWNORMAL);
				if (c) {
					std::cout << "Skype has been loaded. Please make sure ads are in view." << std::endl;
					std::cout << "SkypeWrap will hide ads in 30 seconds and will exit." << std::endl;
				}
				Sleep(30000);
				while (!ads_hidden) {
					hide_skype();
					ads_hidden = true;
				}
				return 0;
			}
			config_file2.close();
		}
	}
	return 0;
}