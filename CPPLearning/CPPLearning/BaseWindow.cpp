//#include "BaseWindow.h"
//
//BaseWindow<class DERIVED_TYPE>::BaseWindow()
//{
//}
//
//
//BaseWindow<class DERIVED_TYPE>::~BaseWindow()
//{
//}
//
//
//BOOL BaseWindow<class DERIVED_TYPE>::Init(
//	HINSTANCE instance, 
//	LPCSTR className, 
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
//	wndClass.hInstance = instance;
//	wndClass.lpszClassName = className;
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
//BOOL BaseWindow<class DERIVED_TYPE>::Show()
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
//
//LRESULT BaseWindow<DERIVED_TYPE>::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
//{
//	return 0;
//}
