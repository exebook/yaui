#include <windows.h>
#include <objidl.h>
#include <gdiplus.h>
#include <GdiPlusGraphics.h>
using namespace Gdiplus;

#pragma comment (lib,"Gdiplus.lib")

ULONG_PTR           gdiplusToken;
GdiplusStartupInput gdiplusStartupInput;

extern "C" void gdiplus_startup() {
	GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);
}

extern "C" void* load_image(wchar_t * name, int &w, int &h) {
	Image *i = new Image(name);
	w = i->GetWidth();
	h = i->GetHeight();
	return (void*) i;
}

extern "C" void draw_image_on_dc(HDC hdc, void* i, int w, int h) {
   Graphics graphics(hdc);
	graphics.DrawImage((Image *)i, 0, 0, w, h);
}

