#include "FileChooser.h"

FileChooser::FileChooser()
{
	ptrFileOpen = NULL;
}


FileChooser::~FileChooser()
{

}

template<class T> void FileChooser::SafeRelease(T** ptr) 
{
	if (*ptr) {
		(*ptr)->Release();
		(*ptr) = NULL;
	}
}

HRESULT FileChooser::Init() {
	HRESULT hr = CoInitializeEx(NULL, COINIT_APARTMENTTHREADED | COINIT_DISABLE_OLE1DDE);

	if (FAILED(hr)) return hr;

	hr = ptrFileOpen.CoCreateInstance(__uuidof(FileOpenDialog));

	return hr;
}

HRESULT FileChooser::Show() 
{
	HRESULT hr = ptrFileOpen->Show(NULL);
	return hr;
}

HRESULT FileChooser::Get_Result(PWSTR* result) 
{
	HRESULT hr = ptrFileOpen->GetResult(&ptrItem);

	if (FAILED(hr)) return hr;

	hr = ptrItem->GetDisplayName(SIGDN_FILESYSPATH, result);

	return hr;
}