#pragma once
#include "BaseWindow.h"
#include <d2d1.h>
#pragma comment(lib, "d2d1")

class D2DWindow : public BaseWindow<D2DWindow>
{
public:
	D2DWindow() : BaseWindow<D2DWindow>(), m_Factory(NULL), m_rTarget(NULL), m_Brush(NULL) {};
	~D2DWindow();

	LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);
	LPCWSTR ClassName() const{ return L"D2DWindow"; }

private:
	void DiscardGraphics();

	BOOL OnCreate();
	BOOL OnPaint();

	ID2D1Factory* m_Factory;
	ID2D1HwndRenderTarget* m_rTarget;
	ID2D1SolidColorBrush* m_Brush;
};

