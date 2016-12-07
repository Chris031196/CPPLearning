#include "BaseWindow.h"

//template<class WindowType>
//static LRESULT CALLBACK BaseWindow<WindowType>::WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) 
//{
//	WindowType *pThis = NULL;
//
//	if (uMsg == WM_NCCREATE)
//	{
//		CREATESTRUCT* pCreate = (CREATESTRUCT*)lParam;
//		pThis = (WindowType*)pCreate->lpCreateParams;
//		SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)pThis);
//
//		pThis->m_hwnd = hwnd;
//	}
//	else
//	{
//		pThis = (WindowType*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
//	}
//	if (pThis)
//	{
//		return pThis->HandleMessage(uMsg, wParam, lParam);
//	}
//	else
//	{
//		return DefWindowProc(hwnd, uMsg, wParam, lParam);
//	}
//}


//template<class WindowType>
//BOOL BaseWindow<WindowType>::Init(
//	LPCSTR windowName, 
//	int nCmdShow, 
//	int width, 
//	int height) 
//{
//	m_show = nCmdShow;
//
//	WNDCLASS wndClass = {0};
//
//	wndClass.lpfnWndProc = WindowProc;
//	wndClass.hInstance = GetModuleHandle(NULL);
//	wndClass.lpszClassName = ClassName();
//
//	RegisterClass(&wndClass);
//
//	m_hwnd = CreateWindowEx(
//		NULL, 
//		className, 
//		windowName, 
//		WS_OVERLAPPEDWINDOW, 
//		CW_USEDEFAULT, 
//		CW_USEDEFAULT, 
//		width, 
//		height, 
//		NULL, 
//		NULL, 
//		instance, 
//		this
//	);
//
//	if (!m_hwnd) {
//		return false;
//	}
//
//	return true;
//}
//
//template<class WindowType>
//BOOL BaseWindow<WindowType>::Show()
//{
//	BOOL result = false;
//
//	if (m_hwnd) {
//		ShowWindow(m_hwnd, m_show);
//		result = true;
//	}
//
//	return result;
//}

