#include "DrawWindow.h"


DrawWindow::~DrawWindow()
{
	SafeRelease(&m_Factory);
	DiscardGraphics();
}

LRESULT DrawWindow::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg) {
	case WM_CREATE:
		return OnCreate();
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	case WM_PAINT:
		return OnPaint();
	case WM_LBUTTONDOWN:
		OnLButtonDown(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam), (DWORD) wParam);
		return 0;
	case WM_LBUTTONUP:
		OnLButtonUp();
	case WM_MOUSEMOVE:
		OnMouseMove(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam), (DWORD)wParam);
		return 0;
	}
	return DefWindowProc(m_hwnd, uMsg, wParam, lParam);
}

BOOL DrawWindow::Initialize()
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

	hr = m_rTarget->CreateSolidColorBrush(D2D1::ColorF(1.0f, 0.0f, 0.0f), &m_Brush);

	InitPixelScale();

	return 0;
}

void DrawWindow::InitPixelScale()
{
	m_Factory->GetDesktopDpi(&scaleX, &scaleY);

	scaleX /= 96.0f;
	scaleY /= 96.0f;
}

void DrawWindow::DiscardGraphics()
{
	SafeRelease(&m_rTarget);
	SafeRelease(&m_Brush);
}

BOOL DrawWindow::OnPaint()
{
	PAINTSTRUCT ps;
	BeginPaint(m_hwnd, &ps);
	m_rTarget->BeginDraw();

	m_rTarget->Clear(D2D1::ColorF(0.0f, 1.0f, 0.0f));

	m_rTarget->FillEllipse(&ellipse, m_Brush);

	m_rTarget->EndDraw();

	EndPaint(m_hwnd, &ps);
	return 0;
}

BOOL DrawWindow::OnCreate()
{
	return Initialize();
}

void DrawWindow::OnLButtonDown(int pX, int pY, DWORD flags)
{
	SetCapture(m_hwnd);
	ellipse.point = mouse = D2D1::Point2F(PixelToDIPx((float) pX), PixelToDIPy((float) pY));
	ellipse.radiusX = ellipse.radiusY = 1.0f;

	RECT rc;
	POINT pt = { pX - 100, pY -100};
	POINT pt2 = { pX + 100, pY + 100};
	ClientToScreen(m_hwnd, &pt);
	ClientToScreen(m_hwnd, &pt2);
	SetRect(&rc, pt.x, pt.y, pt2.x, pt2.y);
	ClipCursor(&rc);

	InvalidateRect(m_hwnd, NULL, FALSE);
}

void DrawWindow::OnLButtonUp()
{
	ReleaseCapture();
	ClipCursor(NULL);
}

void DrawWindow::OnMouseMove(int pX, int pY, DWORD flags)
{
	if (flags & MK_LBUTTON) {
		D2D_POINT_2F p = D2D1::Point2F(PixelToDIPx((float) pX), PixelToDIPy((float) pY));

		float radX = (p.x - mouse.x) / 2;
		float radY = (p.y - mouse.y) / 2;
		float pX = mouse.x + radX;
		float pY = mouse.y + radY;

		ellipse.point = D2D1::Point2F(pX, pY);
		ellipse.radiusX = radX;
		ellipse.radiusY = radY;

		InvalidateRect(m_hwnd, NULL, FALSE);
	}
}

float DrawWindow::PixelToDIPx(float pixel)
{
	return pixel/scaleX;
}

float DrawWindow::PixelToDIPy(float pixel)
{
	return pixel / scaleY;
}
