#include "D2DWindow.h"

D2DWindow::~D2DWindow()
{
	DiscardGraphics();
	SafeRelease(&m_Factory);
}

LRESULT D2DWindow::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg) {
	case WM_CREATE:
		return OnCreate();
	case WM_PAINT:
		OnPaint();
		return 0;
	case WM_DESTROY:
		DiscardGraphics();
		SafeRelease(&m_Factory);
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(m_hwnd, uMsg, wParam, lParam);
}

void D2DWindow::DiscardGraphics()
{
	SafeRelease(&m_Brush);
	SafeRelease(&m_rTarget);
}

BOOL D2DWindow::OnCreate()
{
	HRESULT hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &m_Factory);

	if (FAILED(hr)) {
		return -1;
	}

	RECT rect;
	GetClientRect(m_hwnd, &rect);

	D2D1_SIZE_U size = D2D1::SizeU(rect.right, rect.bottom);

	hr = m_Factory->CreateHwndRenderTarget(D2D1::RenderTargetProperties(), D2D1::HwndRenderTargetProperties(m_hwnd, size), &m_rTarget);

	if (FAILED(hr)) {
		return -1;
	}

	D2D1_COLOR_F color = D2D1::ColorF(1.0f, 0.0f, 0.0f);

	hr = m_rTarget->CreateSolidColorBrush(color, &m_Brush);

	if (FAILED(hr)) {
		return -1;
	}

	return 0;
}

BOOL D2DWindow::OnPaint()
{

	return true;
}
