#include "GUI.h"
#include "Header.h"
using namespace std;
HWND Button::CreateChildWindow(HWND hwnd,LPCSTR text,int x,int y,int width,int height,int Wparam) //function declaration (create button on hwnd main window, uske uoar ka text, uske co ordinates, uski hxw, wparam ko value assigned hai jo case mein chalegi aur usko pata chalega ke kia karna hai)
{
	CreateWindow(TEXT("BUTTON"),TEXT(text),WS_VISIBLE|WS_CHILD,x,y,width,height,hwnd,(HMENU) Wparam,NULL,NULL);
}
HWND TextField::CreateChildWindow(HWND hwnd,LPCSTR text,int x,int y,int width,int height,int Wparam)
{
	CreateWindow(TEXT("STATIC"),text,WS_VISIBLE|WS_CHILD,x,y,width,height,hwnd,(HMENU) Wparam,NULL,NULL);// (ismein akhhri do parameters null rakhte hain)
}
HWND TextBox::CreateChildWindow(HWND hwnd,LPCSTR text,int x,int y,int width,int height,int Wparam)
{
	CreateWindow(TEXT("EDIT"),text,WS_VISIBLE|WS_CHILD,x,y,width,height,hwnd,(HMENU) Wparam,NULL,NULL);// red mein jo hai woh batayega ke function call hone pe kia banega
}
bool Bitmap::LoadBitmap(LPCSTR FileName, HDC hWinDC,int x,int y)
{
	// Load the bitmap image file
	HBITMAP hBitmap;
	hBitmap = (HBITMAP)::LoadImage(NULL, FileName, IMAGE_BITMAP, 0, 0,
		LR_LOADFROMFILE);
	// Verify that the image was loaded
	if (hBitmap == NULL) {
		::MessageBox(NULL, "LoadImage Failed","Error", MB_OK);
		return false;
	}

	// Create a device context that is compatible with the window
	HDC hLocalDC;
	hLocalDC = ::CreateCompatibleDC(hWinDC);
	// Verify that the device context was created
	if (hLocalDC == NULL) {
		::MessageBox(NULL, "CreateCompatibleDC Failed", "Error", MB_OK);
		return false;
	}

	// Get the bitmap's parameters and verify the get
	BITMAP qBitmap;
	int iReturn = GetObject(reinterpret_cast<HGDIOBJ>(hBitmap), sizeof(BITMAP),
		reinterpret_cast<LPVOID>(&qBitmap));
	if (!iReturn) {
		::MessageBox(NULL, "GetObject Failed","Error", MB_OK);
		return false;
	}

	// Select the loaded bitmap into the device context
	HBITMAP hOldBmp = (HBITMAP)::SelectObject(hLocalDC, hBitmap);
	if (hOldBmp == NULL) {
		::MessageBox(NULL,"SelectObject Failed", "Error", MB_OK);
		return false;
	}

	// Blit the dc which holds the bitmap onto the window's dc
	BOOL qRetBlit = ::BitBlt(hWinDC, x, y, qBitmap.bmWidth, qBitmap.bmHeight,
		hLocalDC, 0, 0, SRCCOPY);
	if (!qRetBlit) {
		::MessageBox(NULL,"Blit Failed","Error", MB_OK);
		return false;
	}

	// Unitialize and deallocate resources
	::SelectObject(hLocalDC, hOldBmp);
	::DeleteDC(hLocalDC);
	::DeleteObject(hBitmap);
	return true;
}
