#pragma once

#include <Windows.h>

class EasyWindow
{
public:
	EasyWindow( ) : m_hwnd(NULL) {}
	virtual ~EasyWindow();

	static LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {

		if (uMsg == WM_NCCREATE) {
			CREATESTRUCT cs = 
		}
	}

	HWND GetWindow() const { return m_hwnd; }

	virtual BOOL Create(
		HINSTANCE instance,
		LPCSTR class_name,
		LPCSTR window_name,
		int x = CW_USEDEFAULT,
		int y = CW_USEDEFAULT,
		int width = CW_USEDEFAULT,
		int height = CW_USEDEFAULT,
		HBRUSH background = (HBRUSH)(COLOR_WINDOW)
	);

	virtual LRESULT HandleMessage(
		UINT uMsg, 
		WPARAM wParam, 
		LPARAM lParam
	);

protected:
	HWND m_hwnd;
	HBRUSH m_background;
};

