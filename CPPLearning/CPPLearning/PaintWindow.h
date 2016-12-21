#pragma once
#include "BaseWindow.h"
#include <d2d1.h>
#include <windowsx.h>
#include "Line.h"

class PaintWindow :
	public BaseWindow<PaintWindow>
{
public:
	PaintWindow();
	~PaintWindow();

	LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);
	LPCWSTR ClassName() const { return L"DrawWindow"; }

private:
	BOOL Initialize();
	void InitPixelScale();
	void DiscardGraphics();

	BOOL OnPaint();
	BOOL OnCreate();
	void OnLButtonDown(int pX, int pY, DWORD flags);
	void OnMouseMove(int pX, int pY, DWORD flags);

	float PixelToDIPx(float pixel);
	float PixelToDIPy(float pixel);

	float scaleX = 1.0f;
	float scaleY = 1.0f;
	ID2D1Factory* m_Factory;
	ID2D1HwndRenderTarget* m_rTarget;
	ID2D1SolidColorBrush* m_Brush;

	std::list<Line*> lines;

};

