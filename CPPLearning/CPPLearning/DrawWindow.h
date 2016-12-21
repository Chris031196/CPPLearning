#pragma once

#include "BaseWindow.h"
#include <d2d1.h>
#include <windowsx.h>
#pragma comment(lib, "d2d1")

class DrawWindow : public BaseWindow<DrawWindow>
{
public:
	DrawWindow() : m_Factory(NULL), m_rTarget(NULL), m_Brush(NULL), ellipse(D2D1::Ellipse(D2D1::Point2F(), 0, 0)), mouse(D2D1::Point2F()) {}
	~DrawWindow();

	LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);
	LPCWSTR ClassName() const { return L"DrawWindow"; }

private:
	BOOL Initialize();
	void InitPixelScale();
	void DiscardGraphics();

	BOOL OnPaint();
	BOOL OnCreate();
	void OnLButtonDown(int pX, int pY, DWORD flags);
	void OnLButtonUp();
	void OnMouseMove(int pX, int pY, DWORD flags);

	float PixelToDIPx(float pixel);
	float PixelToDIPy(float pixel);

	ID2D1Factory* m_Factory;
	ID2D1HwndRenderTarget* m_rTarget;
	ID2D1SolidColorBrush* m_Brush;
	float scaleX = 1.0f;
	float scaleY = 1.0f;
	D2D1_ELLIPSE ellipse;
	D2D1_POINT_2F mouse;
};

