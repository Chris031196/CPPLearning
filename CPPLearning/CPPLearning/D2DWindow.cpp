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
		return OnPaint();
		return 0;
	case WM_SIZE:
		Resize();
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
	SafeRelease(&m_BrushBG);
	SafeRelease(&m_rTarget);
}

void D2DWindow::InitPixelScale()
{
	m_Factory->GetDesktopDpi(&scaleX, &scaleY);

	scaleX /= 96.0f;
	scaleY /= 96.0f;
}

void D2DWindow::Resize()
{
	RECT rect;
	GetClientRect(m_hwnd, &rect);

	D2D1_SIZE_U size = D2D1::SizeU(rect.right, rect.bottom);

	m_rTarget->Resize(size);

	CalculateEllipse(size);

	InvalidateRect(m_hwnd, &rect, FALSE);
}

void D2DWindow::CalculateEllipse(D2D1_SIZE_U size)
{
	ellipse = D2D1::Ellipse(D2D1::Point2F(size.width / 2.0f, size.height / 2.0f), size.width / 2.0f, size.height / 2.0f);
}

void D2DWindow::DrawPointer(float length, float width, float angle)
{
	m_rTarget->SetTransform(D2D1::Matrix3x2F::Rotation(angle, ellipse.point));

	m_rTarget->DrawLine(ellipse.point, D2D1::Point2F(ellipse.point.x, ellipse.point.y - ellipse.radiusY*length), m_BrushFG, width);
}

void D2DWindow::DrawClock()
{
	SYSTEMTIME time;
	GetLocalTime(&time);

	float angleS = (360.0f / 60.0f) * time.wSecond;
	DrawPointer(1.0f, 2.0f, angleS);
	
	float angleH = (360.0f / 12.0f) * time.wHour + (time.wMinute * 0.5f);
	DrawPointer(0.5f, 6.0f, angleH);

	float angleM = (360.0f / 60.0f) * time.wMinute;
	DrawPointer(1.0f, 4.0f, angleM);

	m_rTarget->SetTransform(D2D1::Matrix3x2F::Identity());
}

float D2DWindow::PixelDIPX(float pixel)
{
	return pixel/scaleX;
}

float D2DWindow::PixelDIPY(float pixel)
{
	return pixel/scaleY;
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
	hr = m_rTarget->CreateSolidColorBrush(color, &m_BrushBG);
	if (FAILED(hr)) {
		return -1;
	}

	color = D2D1::ColorF(.0f, .0f, .0f);
	hr = m_rTarget->CreateSolidColorBrush(color, &m_BrushFG);
	if (FAILED(hr)) {
		return -1;
	}

	CalculateEllipse(size);

	return 0;
}

BOOL D2DWindow::OnPaint()
{
	if (m_rTarget != NULL) {
		PAINTSTRUCT ps;
		BeginPaint(m_hwnd, &ps);
		m_rTarget->BeginDraw();

		m_rTarget->Clear(D2D1::ColorF(0.0f, 1.0f, 0.0f));
		m_rTarget->FillEllipse(ellipse, m_BrushBG);
		m_rTarget->DrawEllipse(ellipse, m_BrushFG);

		DrawClock();

		HRESULT hr = m_rTarget->EndDraw();
		EndPaint(m_hwnd, &ps);
		if (SUCCEEDED(hr)) {
			return true;
		}
	}
	DiscardGraphics();
	return -1;
}
