#pragma once
#include <d2d1.h>
#include <list>

class Line
{
public:
	Line(D2D1_COLOR_F pColor) : color(pColor) {}
	~Line();

	void Draw(ID2D1HwndRenderTarget* rTarget, ID2D1SolidColorBrush* brush);
	void AddPoint(D2D1_POINT_2F point);

private:
	std::list<D2D_POINT_2F> points;
	D2D1_COLOR_F color;

};

