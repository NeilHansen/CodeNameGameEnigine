#include "windows.h"
#include "stdio.h"
#include "direct.h"
#include <iostream>
#include <atlstr.h>

using namespace std;

//check if only instance base on gameTitle
bool IsOnlyInstance(LPCTSTR gameTitle) {
	HANDLE handle = CreateMutex(NULL, TRUE, gameTitle);
	if (GetLastError() != ERROR_SUCCESS)
	{
		//HWND hWnd = FindWindow(gameTitle, NULL);
		//if (hWnd) {
			// An instance of your game is already running. 
			//ShowWindow(hWnd, SW_SHOWNORMAL);
			//SetFocus(hWnd);
			//SetForegroundWindow(hWnd);
			//SetActiveWindow(hWnd);
			return false;
		//}
	}
	return true;
}

//Read CPU speed
DWORD ReadCPUSpeed() {
	DWORD BufSize = sizeof(DWORD);
	DWORD dwMHz = 0;
	DWORD type = REG_DWORD;
	HKEY hKey;
	// open the key where the proc speed is hidden: 
	long lError = RegOpenKeyEx(HKEY_LOCAL_MACHINE, "HARDWARE\\DESCRIPTION\\System\\CentralProcessor\\0", 0, KEY_READ, &hKey);
	if (lError == ERROR_SUCCESS) {
		// query the key:  
		RegQueryValueEx(hKey, "~MHz", NULL, &type, (LPBYTE)&dwMHz, &BufSize);
	}
	return dwMHz;
}

//Look for RAM and virtual memory
bool CheckMemory()
{
	char virtualMemoryNeeded = NULL;
	MEMORYSTATUSEX status;
	status.dwLength = sizeof(status);
	GlobalMemoryStatusEx(&status);

	cout << "Physical Space: " <<endl;
	cout << status.ullAvailPhys << endl;
	cout << endl;
	cout << "Virtual Space: " << endl;
	cout << status.ullAvailVirtual << endl;	
	return 0;
}

//Check free disc space
void CheckFreeDiscSpace()
{
	ULARGE_INTEGER bytes_available, total_bytes, total_free_bytes;
	GetDiskFreeSpaceEx("c:\\", &bytes_available, &total_bytes, &total_free_bytes);

	double free_kilobytes = (double)(__int64)total_free_bytes.QuadPart / 1024.0;
	double free_megabytes = free_kilobytes / 1024.0;
	double free_gigabytes = free_megabytes / 1024.0;

	cout << "Free Space: " << endl;
	cout << " Free Kb's : " << endl;
	cout << free_kilobytes << endl;
	cout << endl;
	cout << " Free Mb's: " << endl;
	cout << free_megabytes << endl;
	cout << endl;
	cout << " Free Gb's :" << endl;
	cout << free_gigabytes << endl;
	cout << endl;
}

//check system architecture
DWORD Architecture()
{
	HKEY AKey;
	DWORD Atype = REG_SZ;
	DWORD BufSize = sizeof(DWORD);
	char dwMHz[256] = "";

	long lError = RegOpenKeyEx(HKEY_LOCAL_MACHINE, "HARDWARE\\DESCRIPTION\\System\\CentralProcessor\\0", 0, KEY_READ, &AKey);
	if (lError == ERROR_SUCCESS) {
		// query the key:  
		lError = RegQueryValueEx(AKey, "ProcessorNameString", NULL, &Atype, (LPBYTE)&dwMHz, &BufSize);
		//cout << "here" << endl;
		while (lError == ERROR_MORE_DATA)
{
			BufSize++;
			lError = RegQueryValueEx(AKey, "ProcessorNameString", NULL, &Atype, (LPBYTE)&dwMHz, &BufSize);
			}
	}
	cout << dwMHz;
	return 0;
	//return dwMHz;
}



int main() 
{	
	//set Game Name to check if its the only instance
	LPCTSTR gameTitle = "CodeName";
	if (IsOnlyInstance(gameTitle) != 0)
		cout << "ONLY INSTANCE" << endl;
	else
		cout << "Not Only Instance" << endl;
	cout << endl;

	//Check RAM
	CheckMemory();
	cout << endl;
	
	//Check Free Disc Space
	CheckFreeDiscSpace();
	
	// Read cpu speed
	cout << "CPU Speed:" << endl;
	cout << ReadCPUSpeed() << endl;
	cout << endl;

	//System Architecture
	cout << "System Architecture :" << endl;
	cout << Architecture() << endl;
	cout << endl;
	system("pause");
}





