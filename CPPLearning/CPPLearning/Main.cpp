#ifndef UNICODE
#define UNICODE
#endif

#ifndef _UNICODE
#define _UNICODE
#endif

#include <Windows.h>
#include <stdio.h>
#include "FileChooser.h"

void COMExample() {
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
}

void Direct2DExample() {

}

int WINAPI wWinMain(HINSTANCE instance, HINSTANCE, PWSTR pCmdLine, int nCmdShow) 
{
	//COMExample();

	Direct2DExample();

	return 0;
}
