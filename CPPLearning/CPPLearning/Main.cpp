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
	switch (uMsg) {
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hwnd, &ps);

		FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW + 1));

		EndPaint(hwnd, &ps);
	}
		return 0;

	case WM_CLOSE:
		if (MessageBox(hwnd, "Wirklich schlieﬂen?", "LEL", MB_OKCANCEL) == IDOK) {
			DestroyWindow(hwnd);
		}
		return 0; //kek

	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}
	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}