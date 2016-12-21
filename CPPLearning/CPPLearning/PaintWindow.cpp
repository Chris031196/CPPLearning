#include "PaintWindow.h"



PaintWindow::PaintWindow()
{
}


PaintWindow::~PaintWindow()
{
	DiscardGraphics();
	SafeRelease(&m_Factory);
}

LRESULT PaintWindow::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg) {
	case WM_CREATE:
		return Initialize();
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	case WM_PAINT:
		return OnPaint();
	case WM_LBUTTONDOWN:
		OnLButtonDown(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam), (DWORD)lParam);
		return 0;
	case WM_MOUSEMOVE:
		OnMouseMove(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam), (DWORD)wParam);
		return 0;
	}
	return DefWindowProc(m_hwnd, uMsg, wParam, lParam);
}

BOOL PaintWindow::Initialize()
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

	hr = m_rTarget->CreateSolidColorBrush(D2D1::ColorF(0.0f, 0.0f, 0.0f), &m_Brush);
	if (FAILED(hr)) {
		return -1;
	}
	
	InitPixelScale();
	return 0;
}

void PaintWindow::InitPixelScale()
{
	m_Factory->GetDesktopDpi(&scaleX, &scaleY);

	scaleX /= 96;
	scaleY /= 96;
}

void PaintWindow::DiscardGraphics()
{
	SafeRelease(&m_rTarget);
	SafeRelease(&m_Brush);
}

BOOL PaintWindow::OnPaint()
{
	PAINTSTRUCT ps;
	BeginPaint(m_hwnd, &ps);
	m_rTarget->BeginDraw();

	m_rTarget->Clear(D2D1::ColorF(1.0f, 1.0f, 1.0f));

	for (std::list<Line*>::const_iterator iterator = lines.begin(), end = lines.end(); iterator != end; ++iterator) {
		Line* line = *iterator;
		line->Draw(m_rTarget, m_Brush);
	}

	m_rTarget->EndDraw();
	EndPaint(m_hwnd, &ps);

	return 0;
}

BOOL PaintWindow::OnCreate()
{
	return Initialize();
}

void PaintWindow::OnLButtonDown(int pX, int pY, DWORD flags)
{
	Line* line = new Line(D2D1::ColorF(1.0f, 0.0f, 0.0f));
	line->AddPoint(D2D1::Point2F(pX, pY));
	lines.push_back(line);
}

void PaintWindow::OnMouseMove(int pX, int pY, DWORD flags)
{
	if (flags & MK_LBUTTON) {
		lines.back()->AddPoint(D2D1::Point2F(pX, pY));
	}
}

float PaintWindow::PixelToDIPx(float pixel)
{
	return pixel / scaleX;
}

float PaintWindow::PixelToDIPy(float pixel)
{
	return pixel / scaleY;
}
