#   ifndef winclass_cpp
#   define winclass_cpp

template <typename T> struct named {
   strings n;
   list <T> v;
   void clear() { n(0), v(0); }
   int operator ! () { return !n; }
   int operator () (str N) { return n.find(N); }
   str & operator () (int i) { return n[i]; }
   T & operator [] (int i) { return v[i]; }
   T & operator [] (str N) {
      int i = n.find(N);
      if (i >= 0) return v[i];
      n << N;
      v++;
      return v[-1];
   }
   void operator ()  (str N, T V) { n << N; v << V; }
   void del(int i, int c) { n.del(i, c); v.del(i, c);}
   void del(str N){del(self(N), 1);}
};

typedef named <str> vals;

struct cmd_obj;

arr <cmd_obj*> *cmd_objects1;

struct cmd_obj
{
	int __OBJ;
   cmd_obj *owner;
   str name;
   list <cmd_obj*> children;

   cmd_obj()
   {
   	__OBJ = 0xDA0B1EC7;
      cmd_objects1 = new arr <cmd_obj*> ;
      (*cmd_objects1) << this;
   }

  ~cmd_obj()
   {
      int j = (*cmd_objects1).find(this);
      if (j >= 0) (*cmd_objects1).del(j, 1);
   }

   virtual str cmd(str c)
   {
      return "";
   }
};

struct inherit(base_win, cmd_obj)
{
	vals data;
   surface *S;
   bool created, focused;
   int cmdid;

   struct _rect_ {word x, y, w, h; }  geom;

   base_win()
   {
      S = 0;
      created = false;
   }

   void virtual get_geom() {}

#  define  on_msg      int  msg(int M, int W, int L, bool &cont)
#  define  on_paint    void paint()
#  define  on_cursor   void cursor(int x, int y)
#  define  on_mouse    void mouse(bool down, int button, int x, int y)
#  define  on_created  void creating()
#  define  on_command  void command(int cmd, int data)
#  define  on_command2 int  command2(int cmd, int data)
#  define  on_char     void character(word ch)
#  define  on_key      void keyboard(bool down, int key)
#  define  on_size     void sizing(int w, int h)
#  define  on_timer    void timer(int id)
#  define  on_focus    void focus_change()
#  define  on_close    bool closing()
#  define  on_align    void do_align(int w, int h)
#  define  on_move     void do_move()
#  define  on_leave    void leave()
#  define  on_hover    void hover(int x, int y)
#  define  on_minimize void minimize(bool mini)
#  define  on_hotkey   bool hotkey(bool S, bool C, bool A, int key)


   virtual on_msg {return 0;}
   virtual on_paint
   {
       S->crect(0, 0, w() - 1, h() - 1, S->bg_color);
       S->CP.x = 0;
       S->CP.x = 0;
       flush();
   }
   virtual on_mouse    {}
   virtual on_cursor   {}
   virtual on_created  {}
   virtual on_command  {}
   virtual on_command2 { return 0; }
   virtual on_char     {}
   virtual on_key      {}
   virtual on_size     { if (created) align(); }
   virtual on_timer    {}
   virtual on_focus    {}
   virtual on_close    { return true; }
   virtual on_align    {}
   virtual on_move     {}
   virtual on_leave    {}
   virtual on_hover    {}
   virtual on_minimize {}
   virtual on_hotkey   { return false; }
   virtual void close() {}
   int virtual w() {return 0;}
   int virtual h() {return 0;}
   void align()
   {
      int w1 = w(), h1 = h();
      do_align(w1, h1);
   }

   void virtual insert(base_win &child) {}
   void virtual start_mouse_capture() {}
   void virtual end_mouse_capture() {}
   int  virtual add_timer(int T, int id = -1) {return 0;}
   void virtual del_timer(int id) {}
   void virtual flush() {}
   void virtual size(int x, int y) {}
   bool virtual visible() {return 0;}
   void virtual set_focus() {}
   void set_border(int width, bool title = true){}
   void move_to_top() {}
   virtual void change_cursor(int x) {}

};

struct inherit(win, base_win)
{
   HWND handle;
   WNDPROC BackUp;
   bool auto_delete, quit, in_command, enabled;
   void * ZCursor;
   tagMSG M;
   str *timers;
   int mouse_speed;
   struct _mrec { int x, y; } mrec;

   win()
   {
      handle = 0;
      BackUp = 0;
      auto_delete = false;
      quit = true;
      ZCursor = LoadCursor(0, IDC_ARROW);
      focused = false;
      cmdid = 0;
      in_command = false;
      created = false;
      enabled = true;
      timers = 0;
      S = new surface_w32;
      S->bg_color = GetSysColor(COLOR_BTNFACE);
   }

  ~win()
   {
     if (IsWindow(handle)) DestroyWindow(handle);
     handle = 0;
   }

   virtual on_msg;
   void create(win * parent = 0);
   void winapi_create(win * parent, Str class_name, int _style = 0, int style_ex = 0, bool not_child = false);
   void assign(HWND Handle);
   void virtual show();
   virtual bool can_close();
   void hide();
   void step();
   void check();
   void run();
   void close();
   void insert(base_win &);

   void both_handlers();
   void init_sysfont(bool via_message = false);
   void mouse1(bool down, int button, short x, short y);
//   void focusing(bool A);

   int  W();
   int  w();
   int  H();
   int  h();
   int  top();
   int  left();
   int  TOP();
   int  LEFT();
   void size(int, int);
   void SIZE(int, int);
   void move(int, int);
   bool visible();
   Str  caption();
   void caption(Str s);
//   void focus();

   int  style();
   void style(int value);
   void start_track();

   virtual int add_timer(int T, int id = -1);
   virtual void del_timer(int id);

   void set_border(int width, bool title)
   {
      if (title) style(WS_BORDER + WS_SYSMENU + WS_DLGFRAME);
      else style(WS_EX_TOOLWINDOW + WS_CLIPCHILDREN);
   }

   void start_mouse_capture()
   {
       SetCapture(handle);
   }

   void end_mouse_capture()
   {
       ReleaseCapture();
   }

   void set_focus()
   {
       SetFocus(handle);
   }

   void destroy()
   {
       DestroyWindow(handle);
       quit = true;
       delete this;
   }

   void enable(bool on)
   {
       int i = 0; if (on) i = 1;
       EnableWindow(handle, i);
       enabled = on;
   }

   void move_to_top()
   {
      SetWindowPos(handle, 0, 0, 0, 0, 0,
        SWP_NOMOVE | SWP_NOACTIVATE | SWP_NOSIZE );
   }
   
   void change_cursor(int x) //0-arrow 1-hand 2-finger 3-caret 4-size_h 5-size_v
   {
       if (x > 5) return;
       #ifdef WIN32
       void* cur_cursor = (void*) -1;//IDC_HAND;
       static void *curs[] = {0, 0, 0, 0, 0, 0, 0};
       if (curs[0] == 0)
       {
          curs[0] = LoadCursor(0, IDC_ARROW);
          curs[1] = LoadCursor(0, IDC_HAND);
          curs[2] = LoadCursor(0, IDC_HAND);
          curs[3] = LoadCursor(0, IDC_IBEAM);
          curs[4] = LoadCursor(0, IDC_SIZEWE);
          curs[5] = LoadCursor(0, IDC_SIZENS);
       }
       cur_cursor = curs[x];
       ZCursor = cur_cursor;
       SetCursor(cur_cursor);
       #endif
       #ifdef UNIX
       #endif
   }

   void do_minimize(bool min = true)
   {
      if (min) ShowWindow(handle, SW_MINIMIZE);
   }

   bool dispatch_hotkey(bool shift, bool control, bool alt, int key);
};

str win_error()
{
   static str s;
   char * e;
   # ifndef UNDER_CE
   FormatMessageA(
      FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
      0,
      GetLastError(),
      MAKELANGID(0, 1), // Default language
      (char*) & e,
      0,
      0
   );
   # endif // todo: support CE
   s = e;
   return s;
}


win * win_of(HWND handle)
{
   win *w = 0;
   if (IsWindow(handle))
   {
      w = (win*)GetWindowLong(handle, GWL_USERDATA);
      if (w && w->handle != handle) w = 0;
   }
   return w;
}

Str exe_dir(Str name)
{
   Str S;
   S(1024);
   S(GetModuleFileName(0, *S, !S));
   int slash = -1;
   each (i, S) if (S[i] == '\\') slash = i;
   if (slash >= 0) S(slash + 1);
   S / name;
   return S;
}

int __stdcall win_proc(HWND H, int M, int W, int L)
{
   win *w = (win*)GetWindowLong(H, GWL_USERDATA);
   if (w != 0)
   {
      bool cont = true;
      int R;
      R = w->msg(M, W, L, cont);
      if (!cont) return R;
      if (w->BackUp)
      {
        return w->BackUp(H, M, W, L);
      }
   }
   return DefWindowProc(H, M, W, L);
}

/*
             ACTUAL FUNCTIONS
*/

HICON winclass_def_icon;

void RegisterNonameClass()
{
   WNDCLASS c = { 0 };
   c.style = CS_OWNDC | CS_DBLCLKS | CS_HREDRAW | CS_VREDRAW;
   c.lpfnWndProc = (WNDPROC)win_proc;
   c.hInstance = GetModuleHandle(0);
   HICON &h = winclass_def_icon;
   if (h == 0) h = LoadIcon(GetModuleHandle(0), (void*)TEXT("MAINICON"));
   c.hIcon = h;
   c.lpszClassName = TEXT("MYCLASSNONAME");
   RegisterClass(&c);
}

void win :: assign(HWND Handle)
{
   //after assign call both_handlers() if needed
   handle = Handle;
   SetWindowLong(handle, GWL_USERDATA, (int)this);
   ((surface_w32*)S)->dc = GetDC(handle);
   S->font_trans(true);
   S->pen(0, 0);
   init_sysfont();
   creating();
   sizing(w(), h());
   created = true;
}

void win :: create(win *parent)
{
   winapi_create(parent, "MYCLASSNONAME");
}

void win :: winapi_create(win *parent, Str class_name, int _style, int style_ex, bool not_child)
{
   owner = parent;
   int style_extra = 0;
   HWND Parent = 0;
   int ws_ex_style = 0;
   RECT *Rk = 0;
   int s1 = _style;
   int s2 = style_ex;
   if (!class_name == 0) class_name = TEXT("MYCLASSNONAME");
   RegisterNonameClass();
   if (parent)
      style_extra |= WS_CHILD,
      Parent = parent->handle;
   if (_style == -1) style_extra = 0;
   style_extra |= WS_CLIPCHILDREN;
   RECT R = { CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT };
   if (Rk) R.left = Rk->left, R.top = Rk->top, R.right = Rk->right, R.bottom = Rk->bottom;
   if (s1 == -1) style_extra = 0; else style_extra |= s1;
   if (s2 == -1) ws_ex_style = 0; else ws_ex_style |= s2;
   if (not_child && (style_extra & WS_CHILD)) style_extra -= WS_CHILD;
   handle = CreateWindowEx(ws_ex_style,
     *class_name,
     TEXT("NO TITLE"),
     style_extra,
     R.left, R.top, R.right, R.bottom,
     Parent, 0, GetModuleHandle(0), 0);
   assign(handle);
//   win_error();
   start_track();
}
void win :: start_track()
{
   int TME_HOVER = 1;
   int TME_LEAVE = 2;
#define HOVER_DEFAULT   0xFFFFFFFF
   TRACKMOUSEEVENT TR = { 0 };
   TR.cbSize = sizeof(TR);
   TR.dwFlags = TME_LEAVE | TME_HOVER;
   TR.hwndTrack = handle;
   TR.dwHoverTime = HOVER_DEFAULT;
#ifndef UNDER_CE
   TrackMouseEvent(&TR);
#endif   
}

void win :: both_handlers()
{
    // if the windows has a system class (like 'EDIT')
    // hook it up and add our WNDPROC handler to the system one.
    BackUp = (WNDPROC) GetWindowLong(handle, GWL_WNDPROC);
    SetWindowLong(handle, GWL_WNDPROC, (int) win_proc);
}

void win::init_sysfont(bool via_message)
{
   HFONT f;
   #ifdef UNDER_CE
   f = (HFONT)GetStockObject(SYSTEM_FONT);
   #else
   f = (HFONT)GetStockObject(DEFAULT_GUI_FONT);
   #endif
   if (via_message)
         SendMessage(handle, WM_SETFONT, (int)f, 0);
   else  DeleteObject(SelectObject(((surface_w32*)S)->dc, f));
}

void win :: show()
{
   ShowWindow(handle, SW_SHOW);
//   SetForegroundWindow(handle);
//   UpdateWindow(handle);
}

void win :: hide()
{
   ShowWindow(handle, SW_HIDE);
   UpdateWindow(handle);
}

void win :: check()
{
   if (PeekMessage(&M, handle, 0, 0, PM_REMOVE))
   {
      TranslateMessage(&M);
      DispatchMessage(&M);
   }
}

void win :: step()
{
   if (GetMessage(&M, 0, 0, 0))
   {
      TranslateMessage(&M);
      DispatchMessage(&M);
   }
}

void win :: run()
{
   quit = false;
   while (!quit) step();
   closing();
}

void win :: close()
{
   quit = true;
}

bool win :: can_close()
{
   return true;
}

void win :: insert(base_win &Child)
{
   win *child = (win*) child;
   SetParent(child->handle, handle);
}

///// DEFAULT /////////////////////////////////////////

void win :: mouse1(bool down, int button, short x, short y)
{ 
   if (down && button == 0)
     set_focus();
   mouse(down, button, x, y);
}

////  SIZE  ///////////////////////////////////////////

int win :: LEFT()  {  RECT R; GetWindowRect(handle, &R); return R.left; }
int win :: TOP()   {  RECT R; GetWindowRect(handle, &R); return R.top; }

int win :: left()
{
   RECT R;
   GetWindowRect(handle, &R);
   POINT P = { R.left, R.top};
   ScreenToClient(GetParent(handle), & P);
   return P.x;
}

int win :: top()
{
   RECT R;
   GetWindowRect(handle, &R);
   POINT P = { R.left, R.top};
   ScreenToClient(GetParent(handle), & P);
   return P.y;
}

int win :: W()  {  RECT R; GetWindowRect(handle, &R); return R.right - R.left; }
int win :: w()  {  RECT R; GetClientRect(handle, &R); return R.right - R.left; }
int win :: H()  {  RECT R; GetWindowRect(handle, &R); return R.bottom - R.top; }
int win :: h()  {  RECT R; GetClientRect(handle, &R); return R.bottom - R.top; }
void win :: size(int _w, int _h)  {  SIZE(_w + W() - w(), _h + H() - h()); }
void win :: SIZE(int _w, int _h)
{
  SetWindowPos(handle, 0, 0, 0, _w, _h,
    SWP_FRAMECHANGED | SWP_NOMOVE |
    SWP_NOOWNERZORDER | SWP_NOACTIVATE);
  sizing(_w, _h);
}
void win :: move(int x, int y)
{
//  MoveWindow(handle, x, y, W(), H(), true);
   SetWindowPos(handle, 0, x, y, 0, 0,
      SWP_NOSIZE | SWP_NOOWNERZORDER | SWP_NOACTIVATE);
}

/////  PROPERTIES   ////////////////////////////////////////

int win :: style()
{
  return GetWindowLong(handle, GWL_STYLE);
}

void win :: style(int value)
{
  SetWindowLong(handle, GWL_STYLE, value);
  SIZE(W(), H()); // to make changes effective
}

bool win :: visible()
{
   return IsWindowVisible(handle);
}

Str  win :: caption()
{
   Str s;
   int i = GetWindowTextLength(handle);
   if (i <= 0) return "";
   s(i);
   GetWindowText(handle, *s, !s + 1);
   return s;
}

void win :: caption(Str s)
{
   SetWindowText(handle, *s);
}

int win :: add_timer(int T, int id)
{
   if (!timers) timers = new str;
   if (id < 0)
   {
      each (j, timers) if (timers[j] == '0') { id = j; break; }
   }
   if (id < 0) id = !*timers, *timers << '1';
   SetTimer(handle, id, T, 0);
   return id;
}

void win :: del_timer(int id)
{
   KillTimer(handle, id);
}

bool win :: dispatch_hotkey(bool shift, bool control, bool alt, int key)
{
   if (hotkey(shift, control, alt, key)) return true;
   void *W = GetParent(handle);
   if (W)
   {
      win *par = win_of(W);
      if (par)
      {
        if (par->dispatch_hotkey(shift, control, alt, key))
           return true;
      }
   }
   return false;
}

int win :: msg(int M, int W, int L, bool &cont)
{
    static bool shift = false, control = false, alt = false;

    if (M == WM_LBUTTONDOWN)
     cursor((short)LOWORD(L), (short)HIWORD(L));
         if (M == WM_PAINT)          { if (BackUp) cont = true; else paint(); }
    else if (M == WM_DESTROY)
    {
       quit = true;
       //delete this;
       delete S;
       //if (*App != this) delete this;
    }
    else if (M == WM_CLOSE)
    {
       cont = false;
       if (can_close())
       {
          DestroyWindow(handle);
       }
       return 0;
    }
    else if (M == WM_SETCURSOR)
    {
       return true; //most stupid message
    }
    else if (M == WM_LBUTTONDOWN)    mouse1(true,  0, LOWORD(L), HIWORD(L));
    else if (M == WM_LBUTTONUP)      mouse1(false, 0, LOWORD(L), HIWORD(L));
    else if (M == WM_LBUTTONDBLCLK)  mouse1(true, 10, LOWORD(L), HIWORD(L));
    else if (M == WM_RBUTTONDOWN)    mouse1(true,  1, LOWORD(L), HIWORD(L));
    else if (M == WM_RBUTTONUP)      mouse1(false, 1, LOWORD(L), HIWORD(L));
    else if (M == WM_RBUTTONDBLCLK)  mouse1(true, 11, LOWORD(L), HIWORD(L));
    else if (M == WM_MBUTTONDOWN)    mouse1(true,  2, LOWORD(L), HIWORD(L));
    else if (M == WM_MBUTTONUP)      mouse1(false, 2, LOWORD(L), HIWORD(L));
    else if (M == WM_MBUTTONDBLCLK)  mouse1(true, 12, LOWORD(L), HIWORD(L));
    else if (M == WM_MOUSELEAVE)
    {
       leave();
    }

    else if (M == WM_MOUSEHOVER)
    {
       POINT P = { LOWORD(L), HIWORD(L) };
       hover(P.x, P.y);
    }

    else if (M == WM_MOUSEWHEEL)
    {
       POINT P = { LOWORD(L), HIWORD(L) };
       ScreenToClient(handle, &P);
       mouse1((short) HIWORD(W) <= 0,  3, P.x, P.y);
    }
    else if (M == WM_MOUSEMOVE)
    {
       POINT P = { LOWORD(L), HIWORD(L) };
       SetCursor((HCURSOR)ZCursor);
       cursor(P.x, P.y);
       start_track();
    }
    else if (M == WM_COMMAND)
    {
       if (!in_command)
       {
          in_command = true;
          command(W, L);
          int R = command2(W, L);
          in_command = false;
          cont = false;
          return R;
       }
    }
    else if (M == WM_CHAR)
    {
        if (W == VK_SHIFT) shift = true;
        if (W == VK_CONTROL) control = true;
        if (W == VK_MENU) alt = true;
        if (!dispatch_hotkey(shift, control, alt, W))
        character(W);
    }
    else if (M == WM_KEYDOWN || M == WM_SYSKEYDOWN)
    {
        if (W == VK_SHIFT) shift = true;
        if (W == VK_CONTROL) control = true;
        if (W == VK_MENU) alt = true;
        if (!dispatch_hotkey(shift, control, alt, W))
          keyboard(true, W);
    }
    else if (M == WM_KEYUP || M == WM_SYSKEYUP)
    {
        if (W == VK_SHIFT) shift = false;
        if (W == VK_CONTROL) control = false;
        if (W == VK_MENU) alt = false;
        keyboard(false, W);
    }
    else if (M == WM_MOVE)     do_move();
    else if (M == WM_SYSCOMMAND)
    {
       if (W == SC_MINIMIZE) minimize(true);
       if (W == SC_RESTORE) minimize(false);
    }
    else if (M == WM_SIZE)
    {
      if (created)// && visible())
        sizing(LOWORD(L), HIWORD(L));
    }
    else if (M == WM_TIMER)          timer (W);
    else if (M == WM_SETFOCUS)       focused = true, focus_change();
    else if (M == WM_KILLFOCUS)
      focused = false, focus_change();
    return 0;
}



/// APP ////////////////////////////////////////

void *AppPtr = 0;

struct inherit(app, win)
{
   app() { S->bg_color = 0xccffff; };
   void create();
} ;
       
# define App (* (app *) AppPtr)

void app :: create()
{
    if (AppPtr == 0) AppPtr = this;
   # ifdef UNDER_CE
    win :: create();
    SetWindowLong(handle, GWL_STYLE, WS_CLIPCHILDREN);
   # else
    win :: create();
    SetWindowLong(handle, GWL_STYLE, WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN);
   # endif
}

# endif // winclass_cpp


