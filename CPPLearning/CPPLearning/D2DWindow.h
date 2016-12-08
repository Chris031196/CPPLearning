#pragma once
#include "BaseWindow.h"
#include <d2d1.h>
#pragma comment(lib, "d2d1")

class D2DWindow : public BaseWindow<D2DWindow>
{
public:
	D2DWindow() : BaseWindow<D2DWindow>(), m_Factory(NULL), m_rTarget(NULL), m_BrushBG(NULL) {};
	~D2DWindow();

	LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);
	LPCWSTR ClassName() const{ return L"D2DWindow"; }

private:
	void DiscardGraphics();
	void InitPixelScale();
	void Resize();
	void CalculateEllipse(D2D1_SIZE_U size);
	void DrawPointer(float length, float width, float angle);
	void DrawClock();

	float PixelDIPX(float pixel);
	float PixelDIPY(float pixel);

	BOOL OnCreate();
	BOOL OnPaint();

	ID2D1Factory* m_Factory;
	ID2D1HwndRenderTarget* m_rTarget;
	ID2D1SolidColorBrush* m_BrushBG;
	ID2D1SolidColorBrush* m_BrushFG;
	float scaleX = 1.0f;
	float scaleY = 1.0f;
	D2D1_ELLIPSE ellipse;
};

