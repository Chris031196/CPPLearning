#pragma once

#include <Windows.h>
#include <ShObjIdl.h>
#include <atlbase.h>

class FileChooser
{
public:
	FileChooser();
	~FileChooser();

	HRESULT Init();
	HRESULT Show();
	HRESULT Get_Result(PWSTR* result);
	template<class T> void SafeRelease(T** ptr);

private:
	CComPtr<IFileOpenDialog> ptrFileOpen;
	CComPtr<IShellItem> ptrItem;


};

