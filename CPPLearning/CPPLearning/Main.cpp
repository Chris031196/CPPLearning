#include <Windows.h>
#include <stdio.h>

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

int WINAPI wWinMain(HINSTANCE instance, HINSTANCE, PWSTR pCmdLine, int nCmdShow) {
	WNDCLASS wc = {};
	LPCSTR class_name = "Fenster";

	wc.lpfnWndProc = WindowProc;
	wc.hInstance = instance;
	wc.lpszClassName = class_name;

	RegisterClass(&wc);

	HWND hwnd = CreateWindow(
		class_name, 
		"Test Fenster", 
		WS_OVERLAPPEDWINDOW, 
		CW_USEDEFAULT, 
		CW_USEDEFAULT, 
		CW_USEDEFAULT, 
		CW_USEDEFAULT, 
		NULL, 
		NULL, 
		instance, 
		NULL);

	if (!hwnd) return 0;

	ShowWindow(hwnd, nCmdShow);

	MSG msg;
	BOOL rslt = GetMessage(&msg, NULL, 0, 0);
	while (rslt) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
		rslt = GetMessage(&msg, NULL, 0, 0);
	}
	return 0;

}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}