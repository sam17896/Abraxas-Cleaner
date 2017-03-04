#ifndef GUI_H
#define GUI_H
#include "Header.h"
class GUI
{
	public:
		virtual HWND CreateChildWindow(HWND hwnd,LPCSTR type,int x,int y,int width,int height,int Wparam)=0;
};
class Button:public GUI
{
	public:
		HWND CreateChildWindow(HWND hwnd,LPCSTR type,int x,int y,int width,int height,int Wparam);
};
class TextField:public GUI
{
	public:
		HWND CreateChildWindow(HWND hwnd,LPCSTR type,int x,int y,int width,int height,int Wparam);
};
class TextBox:public GUI
{
	public:
		HWND CreateChildWindow(HWND hwnd,LPCSTR type,int x,int y,int width,int height,int Wparam);
};
class Bitmap
{
	public:
		bool LoadBitmap(LPCSTR FileName, HDC hWinDC,int x,int y);
};
#endif
