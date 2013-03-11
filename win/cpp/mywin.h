// windows.h replacement for a much faster compilation
// by Yakov Sudeikin
//
# ifndef mywin_cpp
# define mywin_cpp

# ifdef WIN32

# ifdef GNU
# define __stdcall
# endif

# ifdef UNDER_CE
# define UNALIGNED __unaligned
# else
# define UNALIGNED
# endif

#define NULL 0
#ifndef API
# define API int __stdcall
# define APP void* __stdcall
#endif

#define PTR2 PTR, PTR
#define PTR3 PTR, PTR, PTR
#define PTR4 PTR, PTR, PTR, PTR
#define PTR5 PTR, PTR, PTR, PTR, PTR

#define INT int
#define INT2 int, int
#define INT3 int, int, int
#define INT4 int, int, int, int
#define INT5 int, int, int, int, int
#define INT6 int, int, int, int, int, int
#define INT7 int, int, int, int, int, int, int
#define INT8 int, int, int, int, int, int, int, int
unsigned char
  VK_DEL = 46,
  VK_INS = 45,
  VK_MINUS = 189,
  VK_EQ = 187,
  VK_PLUS = 187,
  VK_DOWN = 40,
  VK_UP = 38,
  VK_LEFT = 37,
  VK_RIGHT = 39,
  VK_HOME = 36,
  VK_END = 35,
  VK_PGDN = 34,
  VK_PGUP = 33,
  VK_LBUTTON = 1,
  VK_RBUTTON = 2,
  VK_CANCEL = 3,
  VK_BACK = 8,
  VK_TAB = 9,
  VK_SHIFT = 0x10,
  VK_CONTROL = 0x11,
  VK_CLEAR = 0x0c,
  VK_RETURN = 0x0d,
  VK_MENU = 0x12,
  VK_PAUSE = 0x13,
  VK_CAPITAL = 0x14,
  VK_ESC = 0x1b,
  VK_SPACE = 0x20,
  VK_PRIOR = 0x21,
  VK_NEXT = 0x22,
  VK_PRINT = 0x2a,
  VK_EXECUTE = 0x2b,
  VK_PRNSCRN = 0x2c,
  VK_HELP = 0x2f,
  VK_NUMPAD0 = 0x60,
  VK_MULTIPLY = 0x6A,
  VK_ADD = 0x6B,
  VK_SEPARATER = 0x6C,
  VK_SUBTRACT = 0x6D,
  VK_DECIMAL = 0x6E,
  VK_DIVIDE = 0x6F,
  VK_F = 0x70 - 1,
  VK_NUMLOCK = 0x90,
  VK_SCROLL = 0x91,
  VK_LSHIFT = 0xA0,
  VK_RSHIFT = 0xA1,
  VK_LCONTROL = 0xA2,
  VK_RCONTROL = 0xA3,
  VK_LMENU = 0xA4,
  VK_RMENU = 0xA5,
  VK_C_S = 19,
  VK_C_X = 24,
  VK_C_Y = 25,
  VK_C_RIGHT = 185,
  VK_C_LEFT = 186
  ;


typedef unsigned long DWORD;
typedef unsigned long ULONG; 
typedef unsigned int UINT;
typedef int BOOL;
typedef unsigned char BYTE;
typedef unsigned short WORD;
typedef void *HFONT;
typedef void *HICON;
typedef void *HMENU;
typedef void *HINSTANCE;
typedef void *HBITMAP;
typedef void *HRGN;
typedef void *HCURSOR;

typedef WORD ATOM;

#ifdef UNICODE
 #define TCHAR wchar_t
#else
 #define TCHAR char
#endif

typedef TCHAR *STR;
typedef char *LPSTR;
#define LPCSTR STR
#define LPCWSTR STR
typedef void* HANDLE;
#define PTR void*

typedef char *CSTR;
typedef wchar_t *WSTR;
typedef STR LPTSTR;
struct LARGE_INTEGER { int LowPart; int HighPart; };
typedef int WPARAM;
typedef int LPARAM;

#define OEM_FIXED_FONT 10
#define ANSI_FIXED_FONT 11
#define ANSI_VAR_FONT 12
#define SYSTEM_FONT 13
#define DEVICE_DEFAULT_FONT 14
#define DEFAULT_PALETTE 15
#define SYSTEM_FIXED_FONT 16

#define DEFAULT_GUI_FONT 17

#ifdef UNDER_CE
#define SYS_COLOR_INDEX_FLAG 0x40000000
#else
#define SYS_COLOR_INDEX_FLAG 0
#endif // UNDER_NT

#define BS_SOLID 0
#define BS_NULL 1
#define BS_HOLLOW BS_NULL
#define BS_HATCHED 2
#define BS_PATTERN 3
#define BS_INDEXED 4
#define BS_DIBPATTERN 5
#define BS_DIBPATTERNPT 6
#define BS_PATTERN8X8 7
#define BS_DIBPATTERN8X8 8
#define BS_MONOPATTERN 9

#define COLOR_BTNFACE (15 | SYS_COLOR_INDEX_FLAG)

#ifdef UNICODE
#define TEXT(s) L##s
#else
#define TEXT(s) s
#endif

#define LONG int
#define BYTE unsigned char
#define LPBYTE BYTE*
#define LF_FACESIZE 32
#define VOID void
#define CALLBACK __stdcall


/*
 CONSTANTS
*/
#define DIB_RGB_COLORS 0 /* color table in RGBs */
#define SB_BOTTOM 7
 /*
 * Window Styles
 */
 #define WS_OVERLAPPED 0x00000000L
 #define WS_POPUP 0x80000000L
 #define WS_CHILD 0x40000000L
 #define WS_MINIMIZE 0x20000000L
 #define WS_VISIBLE 0x10000000L
 #define WS_DISABLED 0x08000000L
 #define WS_CLIPSIBLINGS 0x04000000L
 #define WS_CLIPCHILDREN 0x02000000L
 #define WS_MAXIMIZE 0x01000000L
 #define WS_CAPTION 0x00C00000L /* WS_BORDER | WS_DLGFRAME */
 #define WS_BORDER 0x00800000L
 #define WS_DLGFRAME 0x00400000L
 #define WS_VSCROLL 0x00200000L
 #define WS_HSCROLL 0x00100000L
 #define WS_SYSMENU 0x00080000L
 #define WS_THICKFRAME 0x00040000L
 #define WS_GROUP 0x00020000L
 #define WS_TABSTOP 0x00010000L

 #define WS_MINIMIZEBOX 0x00020000L
 #define WS_MAXIMIZEBOX 0x00010000L


 #define WS_TILED WS_OVERLAPPED
 #define WS_ICONIC WS_MINIMIZE
 #define WS_SIZEBOX WS_THICKFRAME
 #define WS_TILEDWINDOW WS_OVERLAPPEDWINDOW

 /*
 * Common Window Styles
 */
 #define WS_OVERLAPPEDWINDOW (WS_OVERLAPPED | \
 WS_CAPTION | \
 WS_SYSMENU | \
 WS_THICKFRAME | \
 WS_MINIMIZEBOX | \
 WS_MAXIMIZEBOX)

 #define WS_POPUPWINDOW (WS_POPUP | \
 WS_BORDER | \
 WS_SYSMENU)

 #define WS_CHILDWINDOW (WS_CHILD)
 #define WS_EX_TOOLWINDOW 0x00000080L
 #define CS_VREDRAW 0x0001
 #define CS_HREDRAW 0x0002
 #define CS_DBLCLKS 0x0008
 #define CS_OWNDC 0x0020

 #define GWL_WNDPROC (-4)
 #define GWL_STYLE (-16)
 #define GWL_EXSTYLE (-20)
 #define GWL_USERDATA (-21)

 #define LOWORD(l) ((short)((DWORD)(l) & 0xffff))
 #define HIWORD(l) ((short)((DWORD)(l) >> 16))
 #define LOGPIXELSX 88
 #define LOGPIXELSY 90
 #define WM_SETFOCUS 0x0007
 #define WM_KILLFOCUS 0x0008

 #define WM_MOUSEWHEEL 0x020A
 #define WM_PAINT 0x000F
 #define WM_NCPAINT 0x0085
 #define WM_CLOSE 0x0010
 #define WM_QUIT 0x0012
 #define WM_ERASEBKGND 0x0014
 #define WM_SYSCOLORCHANGE 0x0015
 #define WM_SHOWWINDOW 0x0018
 #define WM_ACTIVATEAPP 0x001C
 #define WM_SETFONT 0x0030
 #define WM_GETFONT 0x0031
 #define WM_DESTROY 0x0002
 #define WM_MOVE 0x0003
 #define WM_SIZE 0x0005
 #define WM_ACTIVATE 0x0006
 #define WM_SETCURSOR 0x0020
 #define WM_NCDESTROY 0x0082
 #define WM_COMMAND 0x0111
 #define WM_SYSCOMMAND 0x0112
 #define WM_TIMER 0x0113
 #define WM_HSCROLL 0x0114
 #define WM_VSCROLL 0x0115
 #define WM_HOTKEY 0x0312
 #define WM_DISPLAYCHANGE 0x007E
 #define WM_NCACTIVATE 0x0086
 #define WM_SETTEXT 0x000C
 #define WM_GETTEXT 0x000D
 #define WM_GETTEXTLENGTH 0x000E

 #define SC_MINIMIZE 0xF020
 #define SC_RESTORE 0xF120
 #define SC_MAXIMIZE 0xF030
 
 #define WS_EX_CONTROLPARENT 0x00010000L

 #define BN_CLICKED 0

#define FORMAT_MESSAGE_ALLOCATE_BUFFER 0x00000100
#define FORMAT_MESSAGE_FROM_SYSTEM 0x00001000
#define MAKELANGID(p, s) ((((WORD )(s)) << 10) | (WORD )(p))

#define MOD_ALT 0x0001
#define MOD_CONTROL 0x0002
#define MOD_SHIFT 0x0004
#define MOD_WIN 0x0008

#define WM_MOUSEFIRST 0x0200
#define WM_MOUSEMOVE 0x0200
#define WM_LBUTTONDOWN 0x0201
#define WM_LBUTTONUP 0x0202
#define WM_LBUTTONDBLCLK 0x0203
#define WM_RBUTTONDOWN 0x0204
#define WM_RBUTTONUP 0x0205
#define WM_RBUTTONDBLCLK 0x0206
#define WM_MBUTTONDOWN 0x0207
#define WM_MBUTTONUP 0x0208
#define WM_MBUTTONDBLCLK 0x0209
#define WM_MOUSEWHEEL 0x020A

#define WM_MOUSEHOVER 0x02A1
#define WM_MOUSELEAVE 0x02A3

#define WM_USER 0x0400

#define MAKEINTRESOURCE(i) (STR)((int)((word)(i)))
#define IDC_ARROW MAKEINTRESOURCE(32512)
#define IDC_IBEAM MAKEINTRESOURCE(32513)
#define IDC_SIZEWE MAKEINTRESOURCE(32644)
#define IDC_SIZENS MAKEINTRESOURCE(32645)
#define IDC_HAND MAKEINTRESOURCE(32649)

#define WM_KEYDOWN 0x0100
#define WM_KEYUP 0x0101
#define WM_CHAR 0x0102
#define WM_DEADCHAR 0x0103
#define WM_SYSKEYDOWN 0x0104
#define WM_SYSKEYUP 0x0105
#define WM_SYSCHAR 0x0106
#define WM_SYSDEADCHAR 0x0107

#define WS_EX_CLIENTEDGE 0x00000200L
#define ES_MULTILINE 0x0004L
#define ES_AUTOVSCROLL 0x0040L
#define ES_AUTOHSCROLL 0x0080L

#define SWP_NOSIZE 0x0001
#define SWP_NOMOVE 0x0002
#define SWP_NOZORDER 0x0004
#define SWP_NOREDRAW 0x0008
#define SWP_NOACTIVATE 0x0010
#define SWP_FRAMECHANGED 0x0020 /* The frame changed: send WM_NCCALCSIZE */
#define SWP_SHOWWINDOW 0x0040
#define SWP_HIDEWINDOW 0x0080
#define SWP_NOCOPYBITS 0x0100
#define SWP_NOOWNERZORDER 0x0200 /* Don't do owner Z ordering */
#define SWP_NOSENDCHANGING 0x0400 /* Don't send WM_WINDOWPOSCHANGING */

#define SW_HIDE 0
#define SW_SHOW 5
#define SW_MAXIMIZE 3
#define SW_SHOWNOACTIVATE 4
#define SW_MINIMIZE 6
#define SW_RESTORE 9

#define FW_NORMAL 400
#define FW_MEDIUM 500
#define FW_SEMIBOLD 600
#define FW_BOLD 700
#define DEFAULT_CHARSET 1
#define MB_OK 0x00000000L
typedef DWORD COLORREF;

struct FILETIME {
 int dwLowDateTime;
 int dwHighDateTime;
};

#define MAX_PATH 260

struct WIN32_FIND_DATA {
 DWORD dwFileAttributes;
 FILETIME ftCreationTime;
 FILETIME ftLastAccessTime;
 FILETIME ftLastWriteTime;
 DWORD nFileSizeHigh;
 DWORD nFileSizeLow;
 DWORD dwReserved0;
 DWORD dwReserved1;
 TCHAR cFileName[ MAX_PATH ];
 TCHAR cAlternateFileName[ 14 ];
};

#define FILE_ATTRIBUTE_READONLY 0x00000001
#define FILE_ATTRIBUTE_HIDDEN 0x00000002
#define FILE_ATTRIBUTE_SYSTEM 0x00000004
#define FILE_ATTRIBUTE_DIRECTORY 0x00000010
#define FILE_ATTRIBUTE_ARCHIVE 0x00000020
#define FILE_ATTRIBUTE_DEVICE 0x00000040
#define FILE_ATTRIBUTE_NORMAL 0x00000080
#define FILE_ATTRIBUTE_TEMPORARY 0x00000100
#define FILE_ATTRIBUTE_SPARSE_FILE 0x00000200
#define FILE_ATTRIBUTE_REPARSE_POINT 0x00000400
#define FILE_ATTRIBUTE_COMPRESSED 0x00000800
#define FILE_ATTRIBUTE_OFFLINE 0x00001000
#define FILE_ATTRIBUTE_NOT_CONTENT_INDEXED 0x00002000
#define FILE_ATTRIBUTE_ENCRYPTED 0x00004000


typedef PTR HWND;
#define HDC PTR

typedef int (CALLBACK* WNDPROC)(HWND, UINT, WPARAM, LPARAM);

#define CW_USEDEFAULT ((int)0x80000000)

struct POINT { int x, y; };
struct RECT { int left, top, right, bottom; };

struct tagMSG {
 PTR hwnd;
 int message;
 int wParam;
 int lParam;
 int time;
 POINT pt;
};

struct WNDCLASS {
 int style;
 //PTR
 WNDPROC lpfnWndProc;
 int cbClsExtra;
 int cbWndExtra;
 PTR hInstance;
 PTR hIcon;
 PTR hCursor;
 PTR hbrBackground;
 STR lpszMenuName;
 STR lpszClassName;
};

struct LOGFONT
{
 LONG lfHeight;
 LONG lfWidth;
 LONG lfEscapement;
 LONG lfOrientation;
 LONG lfWeight;
 BYTE lfItalic;
 BYTE lfUnderline;
 BYTE lfStrikeOut;
 BYTE lfCharSet;
 BYTE lfOutPrecision;
 BYTE lfClipPrecision;
 BYTE lfQuality;
 BYTE lfPitchAndFamily;
 TCHAR lfFaceName[LF_FACESIZE];
}; 

typedef LOGFONT *LPLOGFONT;

struct TEXTMETRIC
{
 LONG tmHeight;
 LONG tmAscent;
 LONG tmDescent;
 LONG tmInternalLeading;
 LONG tmExternalLeading;
 LONG tmAveCharWidth;
 LONG tmMaxCharWidth;
 LONG tmWeight;
 LONG tmOverhang;
 LONG tmDigitizedAspectX;
 LONG tmDigitizedAspectY;
 TCHAR tmFirstChar;
 TCHAR tmLastChar;
 TCHAR tmDefaultChar;
 TCHAR tmBreakChar;
 BYTE tmItalic;
 BYTE tmUnderlined;
 BYTE tmStruckOut;
 BYTE tmPitchAndFamily;
 BYTE tmCharSet;
};

struct NEWTEXTMETRIC : TEXTMETRIC
{
 DWORD ntmFlags;
 UINT ntmSizeEM;
 UINT ntmCellHeight;
 UINT ntmAvgWidth;
};

typedef struct tagLOGBRUSH { // lb 
 UINT lbStyle; 
 COLORREF lbColor; 
 LONG lbHatch; 
} LOGBRUSH;

struct RGBQUAD {
 BYTE rgbBlue;
 BYTE rgbGreen;
 BYTE rgbRed;
 BYTE rgbReserved;
};

struct BITMAPINFOHEADER{
 DWORD biSize;
 LONG biWidth;
 LONG biHeight;
 WORD biPlanes;
 WORD biBitCount;
 DWORD biCompression;
 DWORD biSizeImage;
 LONG biXPelsPerMeter;
 LONG biYPelsPerMeter;
 DWORD biClrUsed;
 DWORD biClrImportant;
};

struct BITMAPINFO {
 BITMAPINFOHEADER bmiHeader;
 RGBQUAD bmiColors[1];
};

struct SIZE
{
 LONG cx;
 LONG cy;
};

struct TRACKMOUSEEVENT {
 DWORD cbSize;
 DWORD dwFlags;
 HWND hwndTrack;
 DWORD dwHoverTime;
};

#define PM_REMOVE 0x0001
#define SRCCOPY (DWORD)0x00CC0020
#define RASTERCAPS 38 
#define HORZSIZE 4 
#define VERTSIZE 6 
#define HORZRES 8 
#define VERTRES 10 
#define BITSPIXEL 12 

#define RC_BITBLT 1 
#define PS_NULL 5
#define PS_SOLID 0
#define R2_NOT 6 
#define TRANSPARENT 1
#define OPAQUE 2

#define GENERIC_READ (0x80000000L)
#define GENERIC_WRITE (0x40000000L)
#define FILE_SHARE_READ 0x00000001
#define CREATE_NEW 1
#define CREATE_ALWAYS 2
#define OPEN_EXISTING 3
#define OPEN_ALWAYS 4
#define TRUNCATE_EXISTING 5

#define FILE_SHARE_READ 0x00000001 
#define FILE_SHARE_WRITE 0x00000002

#define IMAGE_BITMAP 0
#define IMAGE_ICON 1
#define IMAGE_CURSOR 2

#define LR_LOADFROMFILE 0x0010
#define LR_CREATEDIBSECTION 0x2000

#define FILE_MAP_WRITE 2
#define FILE_MAP_READ 4
#define PAGE_READONLY 0x02 
#define PAGE_READWRITE 0x04 

struct SYSTEMTIME
{
 WORD wYear;
 WORD wMonth;
 WORD wDayOfWeek;
 WORD wDay;
 WORD wHour;
 WORD wMinute;
 WORD wSecond;
 WORD wMilliseconds;
}; 

extern "C" {

// APP LoadCursorA(PTR, CSTR);
 APP LoadCursorW(PTR, WSTR);
 APP LoadLibraryA(CSTR);
 APP LoadIconW(PTR2);
 APP CreateFontIndirectW(PTR);
 APP CreateWindowExW(int, PTR, WSTR, INT5, PTR, PTR, PTR, PTR);
 APP CreateSolidBrush(int);
 API CloseHandle(PTR);
 APP CreateCompatibleDC(PTR);
 APP CreateDIBSection(PTR, PTR, int, PTR, int, int);
 APP CreatePen(INT3);
 APP CreateRectRgn(INT4);
 API CreateDirectoryA(PTR2);
 API CreateDirectoryW(PTR2);
 API CloseClipboard();
 APP ChildWindowFromPoint(PTR, POINT);
 APP CreateProcessA(PTR4, INT2, PTR4);
#ifndef UNDERCE
 APP CreateBrushIndirect(PTR); //wince does not support this
#endif
 APP CreateFileMappingA(PTR2, INT3, PTR);
 APP CreateFileMappingW(PTR2, INT3, PTR);
 APP CreateIconFromResource(char *, INT, bool, INT);
 APP CreateNamedPipeA(PTR, INT6, PTR);

 API DefWindowProcA(PTR, int, int, int);
 API DefWindowProcW(PTR, int, int, int);
 APP DispatchMessageA(PTR);
 APP DispatchMessageW(PTR);
 API DestroyWindow(PTR);
 API DeleteObject(PTR);
 API DeleteDC(PTR);
 API DrawTextExA(PTR2, INT, PTR, INT, PTR);
 API DrawTextExW(PTR2, INT, PTR, INT, PTR);
 APP FindFirstFileA(PTR2);
 APP FindFirstFileW(PTR2);
 API FindNextFileA(PTR2);
 API FindNextFileW(PTR2);
 API FindClose(HANDLE);
 API FormatMessageA(INT, PTR, INT2, PTR, INT, PTR);
 API FormatMessageW(INT, PTR, INT2, PTR, INT, PTR);
 API FreeLibrary(PTR);

 API SetWindowLongA(PTR, int, int);
 API SetWindowLongW(PTR, int, int);
 API SetWindowTextA(PTR, CSTR);
 API SetWindowTextW(PTR, WSTR);
 API SendMessageA(PTR, int, int, int);
 API SendMessageW(PTR, int, int, int);
 API PostMessageA(PTR, int, int, int);
 API PostMessageW(PTR, int, int, int);
 APP SelectObject(PTR, PTR);
 APP SetCursor(PTR);
 API SetTextColor(PTR, int);
 API Sleep(int);
 API SleepEx(int, bool);
 API SetWindowPos(PTR, int, int, int, int, int, int);
 API ShowWindow(PTR, int);
 API SetForegroundWindow(PTR);
 API SetMenu(PTR, PTR);
 API StretchBlt(PTR, INT4, PTR, INT5);
 API SetDIBitsToDevice(PTR, INT8, PTR, PTR, int);
 API SelectClipRgn(PTR, PTR);
 API SetROP2(PTR, int);
 API SetTimer(PTR handle, int id, int timeout, int callback);
 API SetBkMode(PTR, int);
 API SetScrollInfo(PTR, int, PTR, int);
 API SetScrollPos(PTR, INT3);
 API SetBkColor(PTR, int);
 API SetClipboardData(int, PTR);
 API SetCapture(PTR);
 API SetParent(PTR2);
 API SetFocus(PTR);
 API ScrollWindow(PTR, INT2, PTR2);
 API SetTextAlign(PTR, INT);
 API SetViewportOrgEx(PTR, INT2, PTR);
 API SetWindowOrgEx(PTR, INT2, PTR);
 APP SetActiveWindow(PTR);
 API SetPixel(PTR, INT3);
 API SetThreadPriority(PTR, INT);
 API ScreenToClient(PTR2);
 API ClientToScreen(PTR2);
 API ShowCursor(INT);

 APP GetForegroundWindow();
 APP GetModuleHandleA(PTR);
 APP GetModuleHandleW(PTR);
 API GetWindowLongA(PTR, int);
 API GetWindowLongW(PTR, int);
 API GetMessageA(PTR, int, int, int);
 API GetMessageW(PTR, int, int, int);
 API GetWindowTextA(PTR, CSTR, int);
 API GetWindowTextW(PTR, WSTR, int);
 API GetTextMetricsA(PTR, PTR);
 API GetTextMetricsW(PTR, PTR);
 API GetPixel(PTR, INT2);
 API GetTempPathA(INT, PTR);
 API GetTempPathW(INT, PTR);
 API GetTextExtentPoint32A(PTR, PTR, int, PTR);
 API GetTextExtentPoint32W(PTR, PTR, int, PTR);
 APP GlobalAlloc(INT2);
 API GlobalFree(PTR);
 APP GlobalLock(PTR);
 API GlobalUnlock(PTR);
 API GlobalSize(PTR);
 API GetWindowTextLengthA(PTR);
 API GetWindowTextLengthW(PTR);
 API GetVersionExA(PTR);
 API GetVersionExW(PTR);
 APP GetProcAddress(PTR, CSTR);
 API GetModuleFileNameA(PTR2, INT);
 API GetModuleFileNameW(PTR2, INT); //not A/W only Name?
 API GetLastError();
 APP GetDC(PTR);
 API GetWindowRect(PTR, PTR);
 API GetClientRect(PTR, PTR);
 APP GetStockObject(int);
 API GdiFlush();
 API GetDeviceCaps(PTR, int);
 APP GetClipboardData(int);
 API GetUpdateRect(PTR2, int);
 API GetTextColor(PTR);
 short __stdcall GetKeyState(int);
 short __stdcall GetAsyncKeyState(int);
 API GetDoubleClickTime();
 API GetSysColor(INT);
 APP GetParent(PTR);
 API GetCursorPos(PTR);
 API GetWindowPlacement(PTR2);
 APP GetDesktopWindow();
 APP GetWindow(PTR, INT);
 APP GetActiveWindow();
 APP GetFocus();
 API GetObjectA(PTR, INT, PTR);
 API GetObjectW(PTR, INT, PTR);
// API GetFileSize(PTR2);
 APP GetTopWindow(PTR);
 API GetSystemInfo(PTR);
 API GetCurrentDirectoryA(INT, PTR);
 API GetCurrentDirectoryW(INT, PTR);
 API RegisterClassA(PTR);
 API RegisterClassW(PTR);
 API ReleaseDC(PTR, PTR);
 API Rectangle(PTR, int, int, int, int);
 API RegisterClipboardFormatA(CSTR);
 API RegisterClipboardFormatW(WSTR);
 API ReleaseCapture();
 API RegisterHotKey(PTR, INT3);
 API ReadFileEx(PTR2, INT, PTR2);
 APP GetCapture();
 
 API PeekMessageA(PTR, PTR, int, int, int);
 API PeekMessageW(PTR, PTR, int, int, int);
 API PostQuitMessage(int);
 API Polyline(PTR2, INT);
 API Polygon(PTR2, INT);
#ifndef UNDER_CE
 API SetPolyFillMode(PTR, INT);
#endif 

 API MessageBoxA(PTR, CSTR, CSTR, int);
 API MessageBoxW(PTR, WSTR, WSTR, int);
 API MoveToEx(PTR, INT2, PTR);
 API ExtTextOutA(PTR, INT4, CSTR, int, PTR);
 API ExtTextOutW(PTR, INT4, WSTR, int, PTR);
 API EnumFontsA(PTR3, INT);
 API EnumFontsW(PTR3, INT);
 API EnumFontFamiliesA(PTR3, INT);
 API EnumFontFamiliesW(PTR3, INT);
 API EnumFontFamiliesExA(PTR4, INT);
 API EnumFontFamiliesExW(PTR4, INT);
 API EnumChildWindows(PTR2, INT);
 API EnableWindow(PTR, INT);
 API Ellipse(PTR, INT4);

 APP WindowFromPoint(POINT);
 API AppendMenuA(PTR, INT2, CSTR);
 API AppendMenuW(PTR, INT2, WSTR);
 API DeleteMenu(PTR, INT2);
 API GetMenuItemCount(PTR);
 API GetMenuItemID(PTR, INT);
 API GetMenuItemInfoA(PTR, INT2, PTR);
 API GetMenuItemInfoW(PTR, INT2, PTR);
 APP TranslateMessage(PTR);
 API IsWindow(PTR);
 API MoveWindow(PTR, int, int, int, int, int);
 APP MapViewOfFile(PTR, INT4);
 API UnmapViewOfFile(PTR);
// APP MapViewOfFileW(PTR, INT4);
 API UpdateWindow(PTR);
 API BitBlt(PTR, INT4, PTR, INT3);
 API BringWindowToTop(PTR);
 API KillTimer(PTR, int);
 API OpenClipboard(PTR);
 API EmptyClipboard();
 API IsClipboardFormatAvailable(int);
 API ValidateRect(PTR2);
 API InvalidateRect(PTR2, INT);
 API IsWindowVisible(PTR);

// API QueryPerformanceCounter(PTR);
 API QueueUserAPC(PTR2, INT);
 API RegisterWindowMessageA(char *);
 API RegisterWindowMessageW(wchar_t *);
 API EnumWindows(PTR2);
 API IsIconic(PTR);
 API PostMessageA(PTR, INT3);
 API SystemParametersInfoA(INT2, PTR, INT);
 API GetSystemTime(PTR);
 API GetLocalTime(PTR);
 API GetSystemMetrics(INT);
 APP GetDesktopWindow();
 APP GetWindowThreadProcessId(PTR2);
 APP OpenProcess(INT3);
 API Shell_NotifyIcon(INT, PTR);
 API GetFileInformationByHandle(PTR2);
 API FileTimeToSystemTime(PTR2);
 API FileTimeToLocalFileTime(PTR2);
 APP FindWindowA(PTR2);
 word __stdcall GlobalFindAtomA(char*);
 word __stdcall GlobalAddAtomA(char*);
 
 API PolyBezier(PTR2, INT);
 API PolyBezierTo(PTR2, INT);
 API PolylineTo(PTR2, INT);
 API BeginPath(PTR);
 API EndPath(PTR);
 API FillPath(PTR);
 API MoveToEx(PTR, INT2, PTR);
 API LineTo(PTR, INT2);
 API ShellExecuteA(PTR5, int);
 API ShellExecuteW(PTR5, int);
 API SystemTimeToFileTime(PTR2);
 API FileTimeToSystemTime(PTR2);
 API MoveFileA(PTR2);
 API MoveFileW(PTR2);
 API IsCharAlphaNumericA(char);
 API IsCharAlphaNumericW(wchar_t);
#ifndef _INC_STDIO
 void wprintf(wchar_t*, ...);
#endif
#ifndef UNDER_CE
 API TrackMouseEvent(PTR);
#endif 
 API InitCommonControls();
}
#define TEXT(quote) L##quote
# define LoadCursor LoadCursorW
# define CreateFontIndirect CreateFontIndirectW
# define SetWindowLong SetWindowLongW
# define GetWindowLong GetWindowLongW
# define DefWindowProc DefWindowProcW
# define GetModuleHandle GetModuleHandleW
# define RegisterClass RegisterClassW
# define CreateWindow CreateWindowW
# define SetWindowText SetWindowTextW
# define GetMessage GetMessageW
# define DispatchMessage DispatchMessageW
# define FindFirstFile FindFirstFileW
# define FindNextFile FindNextFileW
# define GetWindowText GetWindowTextW
# define MessageBox MessageBoxW
# define CreateWindowEx CreateWindowExW
# define RegisterClipboardFormat RegisterClipboardFormatW
# define GetTextMetrics GetTextMetricsW
# define GetTextExtentPoint32 GetTextExtentPoint32W
# define ExtTextOut ExtTextOutW
# define PeekMessage PeekMessageW
# define GetSaveFileName GetSaveFileNameW
# define GetOpenFileName GetOpenFileNameW
# define GetWindowTextLength GetWindowTextLengthW
# define SendMessage SendMessageW
# define PostMessage PostMessageW
# define EnumFonts EnumFontsW
# define AppendMenu AppendMenuW
# define GetVersionEx GetVersionExW
# define ChooseFont ChooseFontW
# define FindResource FindResourceW
# define LoadLibrary LoadLibraryW
# define GetModuleFileName GetModuleFileNameW
# define CallWindowProc CallWindowProcW
# define CreateProcess CreateProcessW
# define CreateDirectory CreateDirectoryW
# define LoadIcon LoadIconW
# define GetObject GetObjectW
# define LoadImage LoadImageW
# define CreateFileMapping CreateFileMappingW
# define CreateFile CreateFileW
# define DeleteFile DeleteFileW
# define SetCurrentDirectory SetCurrentDirectoryW
# define EnumFontFamilies EnumFontFamiliesW
# define EnumFontFamiliesEx EnumFontFamiliesExW
# define DrawTextEx DrawTextExW
# define ShellExecute ShellExecuteW
# define GetCurrentDirectory GetCurrentDirectoryW
# define MoveFile MoveFileW
# define GetTempPath GetTempPathW
# define IsCharAlphaNumeric IsCharAlphaNumericW
# define GetMenuItemInfo GetMenuItemInfoW

#define CreateWindowA(a, s, d, x, y,f, g, h, j, k, l)\
 CreateWindowExA(0L, a, s, d, x, y,f, g, h, j, k, l)

#define CreateWindowW(a, s, d, x, y,f, g, h, j, k, l)\
 CreateWindowExW(0L, a, s, d, x, y,f, g, h, j, k, l)

#define CP_UTF8 65001 // UTF-8 translation
extern "C"{
API WideCharToMultiByte(INT2, PTR, INT, CSTR, INT, PTR2);
API MultiByteToWideChar(INT2, CSTR, INT, WSTR, INT);
API lstrlenA(CSTR);
API lstrlenW(WSTR);
API lstrcpy(CSTR, CSTR);
API wsprintf(CSTR, CSTR, ...);
char * __stdcall GetCommandLineA();
char * __stdcall GetCommandLineW();
}

# endif // WIN32
# endif // mywin_cpp

