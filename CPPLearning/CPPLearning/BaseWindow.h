#pragma once
#pragma comment(lib, "d2d1")

#include <Windows.h>

template<class T>
void SafeRelease(T** ptr) {
	if (*ptr) {
		(*ptr)->Release();
		*ptr = NULL;
	}
}

template <class WindowType>
class BaseWindow
{
public:
	static LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

	BaseWindow() : m_hwnd(NULL) { }

	BOOL Init(
		HINSTANCE instance,
		LPCSTR className,
		LPCSTR windowName,
		int nCmdShow,
		int width,
		int height
	);

	BOOL Show();

	HWND Window() const { return m_hwnd; }

protected:

	virtual LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam) = 0;

	HWND m_hwnd;
	int m_show;
};
