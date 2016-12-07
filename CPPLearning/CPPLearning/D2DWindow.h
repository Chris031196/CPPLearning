#pragma once
#include "BaseWindow.h"
#include <d2d1.h>

class D2DWindow : public BaseWindow<D2DWindow>
{
public:
	D2DWindow();
	~D2DWindow();

protected:
	LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);

private:
	void DiscardGraphics();

	BOOL OnCreate();
	BOOL OnPaint();

	ID2D1Factory* m_Factory;
	ID2D1HwndRenderTarget* m_rTarget;
	ID2D1SolidColorBrush* m_Brush;
};

