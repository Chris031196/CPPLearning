#pragma once
#include "BaseWindow.h"
class D2DWindow :
	public BaseWindow<D2DWindow>
{
public:
	D2DWindow();
	~D2DWindow();

protected:
	LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);
};

