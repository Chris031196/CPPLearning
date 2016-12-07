#pragma once
#include <Windows.h>

#include <iostream>
#include <conio.h>

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
	static LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
		WindowType *pThis = NULL;

		if (uMsg == WM_NCCREATE)
		{
			CREATESTRUCT* pCreate = (CREATESTRUCT*)lParam;
			pThis = (WindowType*)pCreate->lpCreateParams;
			SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)pThis);

			pThis->m_hwnd = hwnd;
		}
		else
		{
			pThis = (WindowType*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
		}

		if (pThis)
		{
			return pThis->HandleMessage(uMsg, wParam, lParam);
		}
		else
		{
			return DefWindowProc(hwnd, uMsg, wParam, lParam);
		}
	}

	BaseWindow() : m_hwnd(NULL) { }

	BOOL Init(
		LPCWSTR windowName,
		int nCmdShow,
		int width = CW_USEDEFAULT,
		int height = CW_USEDEFAULT
	) {
		m_show = nCmdShow;

		WNDCLASS wndClass = { };

		wndClass.lpfnWndProc = WindowType::WindowProc;
		wndClass.hInstance = GetModuleHandle(NULL);
		wndClass.lpszClassName = ClassName();

		RegisterClass(&wndClass);

		m_hwnd = CreateWindowEx(
			NULL,
			ClassName(),
			windowName,
			WS_OVERLAPPEDWINDOW,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			width,
			height,
			0,
			0,
			GetModuleHandle(NULL),
			reinterpret_cast<LPVOID>(this)
		);

		if (!m_hwnd) {
			return false;
		}

		return true;
	}

	BOOL Show()
	{
		BOOL result = false;

		if (m_hwnd) {
			ShowWindow(m_hwnd, m_show);
			result = true;
		}

		return result;
	}

	HWND Window() const { return m_hwnd; }

protected:

	virtual LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam) = 0;
	virtual LPCWSTR ClassName() const = 0;

	HWND m_hwnd;
	int m_show;
};
