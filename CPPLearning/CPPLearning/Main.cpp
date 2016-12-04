#ifndef UNICODE
#define UNICODE
#endif

#ifndef _UNICODE
#define _UNICODE
#endif

#include <Windows.h>
#include <stdio.h>
#include "FileChooser.h"

int WINAPI wWinMain(HINSTANCE instance, HINSTANCE, PWSTR pCmdLine, int nCmdShow) 
{
	HRESULT hr = NULL;
	LPWSTR path = NULL;
	FileChooser* f = new FileChooser();

	hr = f->Init();

	if (SUCCEEDED(hr)) {
		hr = f->Show();

		if (SUCCEEDED(hr)) {
			hr = f->Get_Result(&path);
			MessageBoxW(NULL, path, L"Pfad", MB_OK);
			CoTaskMemFree(path);
		}
		else {
			MessageBox(NULL, L"Show failed!", L"ERROR!", MB_OK | MB_ICONERROR);
		}
	}
	else {
		MessageBox(NULL, L"Initialization failed!", L"ERROR!", MB_OK);
	}

	delete f;

	return 0;
}
