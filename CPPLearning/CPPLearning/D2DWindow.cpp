#include "D2DWindow.h"



D2DWindow::D2DWindow()
{
}


D2DWindow::~D2DWindow()
{
}

LRESULT D2DWindow::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	return DefWindowProc(m_hwnd, uMsg, wParam, lParam);
}
