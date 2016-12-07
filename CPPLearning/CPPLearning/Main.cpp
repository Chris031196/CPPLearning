#ifndef UNICODE
#define UNICODE
#endif

#ifndef _UNICODE
#define _UNICODE
#endif

#include <Windows.h>
#include <stdio.h>
#include "FileChooser.h"
#include "D2DWindow.h"

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

void Direct2DExample(int nCmdShow) {
	D2DWindow* win = new D2DWindow();
	if (win->Init(L"Test Fenster", nCmdShow)) {
		if (win->Show()) {
			MSG msg = {};
			while (GetMessage(&msg, NULL, 0, 0)) {
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
	}
	
	delete win;
}

int WINAPI wWinMain(HINSTANCE instance, HINSTANCE, PWSTR pCmdLine, int nCmdShow) 
{
	//COMExample();

	Direct2DExample(nCmdShow);

	return 0;
}
