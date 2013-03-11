extern "C" void * __stdcall GetWindowDC(void *);

struct dib_int
{
   int count;
   int *bits;
   int w, h;

   dib_int()
   {
      bits = 0;
   }

   dib_int(int W, int H)
   {
      bits = //(int*) malloc(W * H * 4);
      new int[W * H];
      w = W, h = H;
   }

   void virtual release()
   {
      if (bits) //free(bits);
      delete bits;
      bits = 0;
   }

   virtual ~ dib_int()
   {
      release();
   }
};

struct base_dib
{
int *data;
dib_int *p;

void virtual newref(int W, int H)
{
   release();
   p = new dib_int(W, H);
}

virtual void* sys_handle()
{
   return 0;
}

base_dib()
{
   p = 0;
}

~base_dib()
{
   release();
}

void assign(base_dib &V)
{
   release();
   p = V.p;
   if (p) p->count++;
}

base_dib(base_dib &V)
{
   p = 0;
   assign(V);
}

void operator = (base_dib &V)
{
   assign(V);
}

void release()
{
   if (p)
   {
      if (p->count > 1) p->count--; else
      {
         p->release();
         delete p;
      }
      p = 0;
   }
}

void makeown()
{
   if (p && p->count > 1)
   {
      p->count--;
      dib_int *p1 = p;
      p = 0;
      resize(p1->w, p1->h);
      move(p->bits, p1->bits, p->w * p->h * 4);
   }
}

void resize(int W, int H)
{
   if (p && W == p->w && H == p->h) return;
   release();
   newref(W, H);
   data = p->bits;
}

void seek(int X, int Y)
{
   Y = p->h - Y - 1;
   data = (int*) ((int)p->bits + Y * p->w * 4 + X * 4);
}

void clear(int color)
{
   fill32(color, (int *)p->bits, p->w * p->h);
}

int operator ~ ()
{
   if (!p) return 0;
   return p->w;
}

int operator ! ()
{
   if (!p) return 0;
   return p->h;
}

byte * operator * ()
{
   if (!p) return 0;
   return (byte*) p->bits;
}

int & pixel (int x, int y)
{
   seek(x, y);
   return * (int *) data;
}

void safe_pixel (int x, int y, int C)
{
   if (x < 0) return;
   if (y < 0) return;
   if (x >= p->w) return;
   if (y >= p->h) return;
   seek(x, y);
   * (int *) data = C;
}

void rect(int x1, int y1, int x2, int y2, int color)
{
   for (int y = y1; y < y2; y++)
   for (int x = x1; x < x2; x++)
     pixel(x, y) = color;
}

};

struct w32_dc{   HDC dc;};

struct dib_int_w32 : dib_int, w32_dc
{
   HBITMAP handle;
   HDC dc;
   void *bk;
   BITMAPINFO bi;

   dib_int_w32(int W, int H)
   {
      count = 1;
      w = W;
      h = H;
      dc = CreateCompatibleDC(0);
      BITMAPINFOHEADER & b = bi.bmiHeader;
      fillchar(& bi, sizeof(bi), 0);
      b.biSize = sizeof(b);
      b.biPlanes = 1;
      b.biBitCount = 32;
      b.biCompression = 0;//BI_RGB;
      b.biWidth = w;
      b.biHeight = h;
      handle = CreateDIBSection(dc, &bi, DIB_RGB_COLORS, &bits, 0, 0);
      bk = SelectObject(dc, handle);
   }

   void release()
   {
      SelectObject(dc, bk);
      DeleteObject(handle);
      DeleteDC(dc);
      bits = 0;
   }
};

struct inherit(dib_w32, base_dib)
{
   void virtual newref(int W, int H)
   {
      release();
      p = new dib_int_w32(W, H);
   }
   
   void* sys_handle()
   {
      return ((dib_int_w32*)p)->dc;
   }   
};

typedef dib_w32 dib;

int no_brush = 0xffffffff;

struct base_surface
{
   struct text_cache
   {
      int y;
      Str s;
      ints sw;
   } t;
   struct _point { int x, y; } CP;
   int bg_color;

   double system_font_multiplier;

   void virtual blit(base_dib &d, int x, int y){}
   void virtual capture(base_dib &d, int x, int y){}
   void virtual open(void *some_data){}
   base_surface() {}
  ~base_surface() {}
   virtual void flush_text(){}
   void virtual write_char(int width, word c){ }
   void virtual start_text(int x, int y){}
   void virtual int_crect(__rect &R, int color = -2) {}
   void virtual coval(__rect &R, int color = -2){}
   void virtual irect(__rect &a){}
   void virtual set_pixel(int x, int y, int c){}
   void virtual draw_line(int x, int y, int x1, int y1, int c){}
   void virtual polygon(ints &L){}
   void virtual brush(int color){}
   void virtual pen(int color, int width = 1){}
   void virtual ascent_descent(int & a, int & d){}
   int  virtual char_width(word n){return 0;}
   int  virtual str_width(Str s){return 0;}
   int  virtual char_height(word n) {return 0;}
   void virtual clip_set(__rect R) {}
   void virtual clip_remove() {}
   void virtual set_dc(void *adc) {}
   void virtual setorg(int x, int y) {}

   int  virtual apply_font(str name, float size = 12, int color = 0, bool bold = false, bool italic = false, bool underline = false){return 0;}
   void virtual font_color(int color){}
   void virtual font_trans(bool yes){}
   void virtual font_size(int size){}
   void virtual font_bold(bool yes){}
   void virtual font_italic(bool yes){}
   void virtual font_under(bool yes){}
   void virtual font_name(Str name){}
   void virtual font_reset(){}
   void virtual font_set(){}

   void virtual flush() {}
   void virtual text_out(Str s, int x, int y) {}

   void print(Str s, int x = -1, int y = -1)
   {
      if (!s == 0) return;
      if (x >= 0) CP.x = x;
      if (y >= 0) CP.y = y;
      int a, d;
      ascent_descent(a, d);
      //font_trans(true);
      text_out(s, CP.x, CP.y + a);
      CP.y += char_height(s[0]);
   }

   void frect(int x, int y, int x1, int y1, int back_color, int frame_color, int line_width = 1)
   {
      pen(0, 0);
      __rect R = { x, y, x1 - x + 1, y1 - y + 1 };
      int_crect(R, back_color);
      frame(R, frame_color);
   }

   void crect(int x, int y, int x1, int y1, int C)
   {
      pen(0, 0);
      __rect R = { x, y, x1 - x + 1, y1 - y + 1 };
      int_crect(R, C);
   }

   void frame(int x, int y, int x1, int y1, int C, int line_width = 1)
   {
      __rect R = { x, y, x1 - x + 1, y1 - y + 1 };
      frame(R, C, line_width);
   }

   void frame(__rect &R, int color, int line_width = 1)
   {
      __rect K;
      K = R; K.h = line_width; int_crect(K, color);
      K = R; K.y += K.h - line_width; K.h = line_width; int_crect(K, color);
      K = R; K.y += line_width; K.h -= line_width * 2; K.w = line_width; int_crect(K, color);
      K.x = R.x + R.w - line_width; int_crect(K, color);
   }
};

struct setfont_w32
{
  LOGFONT options;
  str name;
  int color;
  bool transparent;
  HFONT handle;
  setfont_w32() {  init();  }
  ~setfont_w32()
  {
    DeleteObject(handle);
  }

  void init (str Name = "")
  {
    DeleteObject(handle);
    fillchar(&options, sizeof options, 0);
    options.lfWeight = FW_NORMAL;
    options.lfWidth = 0;
    options.lfCharSet = DEFAULT_CHARSET;
    name = Name;
    if (!name > 32) name(32);
    transparent = true;
  }

  void create()
  {
    if (!name > 0)
    {
       Str s;
       if (!name > 32) name(32);
       s = name;
       move(s.p->p, &options.lfFaceName, s.occu());
    }
    DeleteObject(handle);
    handle = CreateFontIndirect(&options);
  }

  void set(HDC DC, bool del = true)
  {
    SetTextColor(DC, color);
    HFONT f, oldf;
    create();
    f = handle;
    oldf = SelectObject(DC, f);
    if (del) DeleteObject(oldf);
    if (transparent) SetBkMode(DC, TRANSPARENT);
    else SetBkMode(DC, OPAQUE);
  }

  void send(void * winhandle)
  {
     void * theDC = GetWindowDC(winhandle);
     if (transparent) SetBkMode(theDC, TRANSPARENT);
     else SetBkMode(theDC, OPAQUE);
     create();
     SendMessage(winhandle, WM_SETFONT, (int)handle, 0);
     SetTextColor(theDC, color);
  }

  void size(float i)
  {
    options.lfHeight = (int) -i;//(- i * 96 / 72);
  }

  void bold(bool b)
  {
     options.lfWeight = b ? FW_BOLD : FW_NORMAL;
  }

  void italic(bool i)
  {
     options.lfItalic = i;
  }

};

struct surface_w32 : base_surface, w32_dc
{
   setfont_w32 F;

//   using base_surface :: irect;
   bool del_font_handles;
   void *sys_brush;
   void *sys_pen;

   surface_w32()
   {
       double a, b, c;
       void *TDC = GetDC(0);
       a = GetDeviceCaps(TDC, LOGPIXELSY);
       b = GetDeviceCaps(TDC, VERTRES);
       c = GetDeviceCaps(TDC, VERTSIZE);
       system_font_multiplier = a / 70.;
//       system_font_multiplier = c;
       DeleteDC(TDC);
       del_font_handles = true;
       sys_brush = 0;
       sys_pen = 0;
   }

  ~surface_w32()
   {
      DeleteObject(sys_brush);
      DeleteObject(sys_pen);
   }

   void brush(int color)
   {
      if (color == -1)
      {
    #  ifndef UNDER_CE
          LOGBRUSH B = { 1, 0, 0 };
          DeleteObject(SelectObject(dc, CreateBrushIndirect(&B)));
    #  endif
      }
      else
      {
         DeleteObject(sys_brush);
         sys_brush = CreateSolidBrush(color);
         SelectObject(dc, sys_brush);
      }

   }

   void open(void *some_data) { dc = some_data; }

   struct text_cache
   {
      int y;
      Str s;
      ints sw;
   } t;

   void text_out(Str s, int x, int y)
   {
      int a, d;
      ascent_descent(a, d);
      ExtTextOut(dc, x, y - a, 0, 0, *s, !s, 0);
   }

   void flush_text()
   {
      if (!t.s > 0)
      {
         each (i, t.s) if (t.s[i] == 9) t.s[i] = 0;//' ';//183; //0xB6;
      // each (i, t.s) if (t.s[i] == ' ') t.s[i] = 183;//183; //0xB6;
         int x;
         x = t.sw[0];
         for (int n = 0; n < !t.s - 1; n++)
            t.sw[n] = t.sw[n + 1] - t.sw[n];
         t.sw[-1] = char_width(t.s[-1]);
         int a, d;
         ascent_descent(a, d);
      // SetBkMode(dc, OPAQUE);
         font_trans(true);
         ExtTextOut(dc, x, t.y - a, 0, 0, *t.s, !t.s, &t.sw[0]);
      // GdiFlush();
         t.s(0);
         t.sw(0);
      }
   }

   void write_char(int addX, word c)
   {
   #  ifdef UNDER_CE
      // Devanagari fix
      if (c == 0x093F) c = 0x0940;
   #  endif
      t.s / (wchar_t)c;
      t.sw << addX;
   }

   void start_text(int x, int y)
   {
      t.y = y;
   }

   void int_crect(__rect &R, int color = -2)
   {
      if (color >= -1) brush(color);
      #ifdef UNDER_CE
      Rectangle(dc, R.x, R.y, R.x + R.w, R.y + R.h);
      #else
      pen(0, 0);
      Rectangle(dc, R.x, R.y, R.x + R.w + 1, R.y + R.h + 1);
      #endif
   }

   void coval(__rect &R, int color = -2)
   {
      if (color >= -1) brush(color);
      Ellipse(dc, R.x, R.y, R.x + R.w, R.y + R.h);
   }

   void irect(__rect &a)
   {
     if (a.h < 0) return;
     RECT R;
     R.left = a.x;
     R.top = a.y;
     R.right = a.x + a.w + 1;
     R.bottom = a.y + a.h + 1;

      int OLDROP = SetROP2(dc, R2_NOT);
    # ifdef UNDER_CE
      Rectangle(dc, R.left, R.top + 0, R.right, R.bottom - 0);
    # else
      Rectangle(dc, R.left, R.top, R.right, R.bottom);
    # endif
      SetROP2(dc, OLDROP);
   }

   void set_pixel(int x, int y, int c)
   {
      SetPixel(dc, x, y, c);
   }

   void draw_line(int x, int y, int x1, int y1, int c = -1)
   {
      if (c != -1) pen(c);
      POINT P[2] = {x, y, x1, y1};
      Polyline(dc, P, 2);
   }

   void pen(int color, int width = 1)
   {
      if (width == 0)
      DeleteObject(SelectObject(dc, CreatePen(PS_NULL, 0, 0)));
      else
      DeleteObject(SelectObject(dc, CreatePen(PS_SOLID, width, color)));
   }

    void ascent_descent(int & a, int & d)
    {
       TEXTMETRIC TM;
       GetTextMetrics(dc, &TM);
       a = TM.tmAscent;
       d = TM.tmDescent;
    }

    int char_width(word n)
    {
//       word s = n;
       POINT wh;
       GetTextExtentPoint32W(dc, &n, 1, (SIZE *) &wh);
       return wh.x;
    }

    int str_width(Str s)
    {
       POINT wh;
       GetTextExtentPoint32W(dc, *s, !s, (SIZE *) &wh);
       return wh.x;
    }

    int char_height(word n)
    {
//       wc s = n;
       POINT wh;
       GetTextExtentPoint32W(dc, &n, 1, (SIZE *) &wh);
       return wh.y;
    }

    void clip_set(__rect R)//int x, int y, int w, int h)
    {
    #  ifndef UNDER_CE
       HRGN G;
       //got strange leak here
       G = CreateRectRgn(R.x, R.y, R.w, R.h);
       DeleteObject(G);
     //ExtSelectClipRgn(DC, G, RGN_AND);
       SelectClipRgn(dc, G);
       DeleteObject(G);
    #  endif
    }

    void clip_remove()
    {
    #  ifndef UNDER_CE
       SelectClipRgn(dc, 0);
    #  endif
    }

    void set_dc(void *adc)
    {
        dc = adc;
        pen(0, 0);
    #  ifndef UNDER_CE
//        SetTextAlign(dc, TA_BASELINE);
    #  endif
        SetBkMode(dc, TRANSPARENT);
    }

    void setorg(int x, int y)
    {
        SetViewportOrgEx(dc, x, y, 0);
        //SetWindowOrgEx(dc, -x, -y, 0);
    }

    int apply_font(str name = "arial", float size = 10, int color = 0, bool bold = false, bool italic = false, bool underline = false)
    {
        F.init(name);
        F.color = color;
        F.size(system_font_multiplier * size);
        if (bold) F.options.lfWeight = FW_BOLD;
        F.options.lfItalic = italic;
        F.options.lfUnderline = underline;
        F.options.lfQuality = 5;//anti_alias_fonts?5:3;
        F.set(dc, del_font_handles);
        int R = (int) F.handle;
        //F.handle = 0;
        return R;
    }

   void font_color(int color)
   {
      SetTextColor(dc, color);
   }

   void font_trans(bool yes)
   {
      if (yes) SetBkMode(dc, TRANSPARENT);
      else SetBkMode(dc, OPAQUE);
   }

   void font_size(int size){ F.size(size); }
   void font_bold(bool yes){ F.bold(yes); }
   void font_italic(bool yes){ F.italic(yes); }
   void font_under(bool yes) { F.options.lfUnderline = yes; }
   void font_name(Str name)
   {
       if (!name > 32) name(32);
       F.name = name;
   }

   void font_reset()
   {
      F.init("Arial");
   } //control_font.name); }

   void font_set() { F.set(dc); }

   void text_out11(Str s, int x, int y)
   {
      ExtTextOut(dc, x, y, 0, 0, *s, !s, 0);
   }

   void blit(base_dib &d, int x, int y)
   {
      void *dest = dc;
      BitBlt(dest, x, y, ~d, !d, ((dib_int_w32*)d.p)->dc, 0, 0, SRCCOPY);
   }

   void capture(base_dib &d, int x, int y)
   {
      BitBlt(((dib_int_w32*)d.p)->dc, x, y, ~d, !d, dc, 0, 0, SRCCOPY);
   }

   void polygon(ints &L)
   {
      #ifndef UNDER_CE
      POINT *P = (POINT* ) & L [0];
      SetPolyFillMode(dc, 2);
      Polygon(dc, P, !L / 2);
      #endif
   }
};

typedef surface_w32 surface;

struct dib_surface : surface, dib
{
   void virtual newref(int W, int H) {
       dib::newref(W, H);
       dc = ((dib_int_w32*)p)->dc;
   }

   void int_crect(__rect &R, int color = -2)
   {
      if (R.y < 0) R.h += R.y, R.y = 0;
      if (p->h == 0 || p->w == 0) return;
      int x2 = R.x + R.w, y2 = R.y + R.h;
      if (x2 > p->w) x2 = p->w;
      if (y2 > p->h) y2 = p->h;
      for (int y = R.y; y < y2; y++)
      for (int x = R.x; x < x2; x++) {
         pixel(x, y) = color;
      }
   }

   void line(double x, double y, double x1, double y1, int c)
   {
      double lx = x1 - x, ly = y1 - y;
      double L = _sqrt(lx*lx + ly*ly);
      double dx = lx / L, dy = ly / L;
      for (double l = 0; l <= L; l ++)
      {
         safe_pixel(x, y, c);
         x += dx; y += dy;
      }
   }

   void polygon(ints &L)
   {
      int c = 0;
      for (int n = 0; n < !L - 2; n += 2)
      {
         line (L[n], L[n + 1], L[n + 2], L[n + 3], c);
      }
      line (L[0], L[1], L[-2], L[-1], c);
   }
};




