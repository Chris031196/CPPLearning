#include "Line.h"


Line::~Line()
{
}

void Line::Draw(ID2D1HwndRenderTarget * rTarget, ID2D1SolidColorBrush * brush)
{
	brush->SetColor(color);
	D2D_POINT_2F p1 = points.front(), p2;

	int i;
	for (std::list<D2D_POINT_2F>::const_iterator iterator = points.begin(), end = points.end(); iterator != end; ++iterator) {
		p2 = *iterator;
		if (p1.x != p2.x & p1.y != p2.y) {
			rTarget->DrawLine(p1, p2, brush);
			p1 = p2;
		}
	}
}

void Line::AddPoint(D2D1_POINT_2F point)
{
	points.push_back(point);
}
