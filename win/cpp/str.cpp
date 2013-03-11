#define malloc ERROR()()()
#define free ERROR()()()
struct me
{
  struct strptr { bit *p; int count, size, capacity; };
  strptr *p;
                                   
  me  ();
  me  (const me &s);
  me  (char *s);
  me  (char ch);
  me  (wchar_t *s);
  me  (wchar_t ch);
  me  (int i);
  me  (unsigned int i);
  me  (double i);
# ifndef onebyte
  me  (str);
# endif
 ~me  ();

# ifndef onebyte
  operator str() {  return self.compat();  };
# endif
  void operator  =  (const me&);

  me   operator  +  (me s);
  me   operator  +  (char *s);
  me   operator  +  (char ch);
  me   operator  +  (wchar_t *s);
  me   operator  +  (wchar_t ch);
  me   operator  +  (int i);
  me & operator  /  (me s);
# ifdef onebyte
  me & operator  << (me s);
  me & operator  << (word w);
  me & operator  << (byte b);
  me & operator  << (int i);
  me & operator  << (float f);
  me & operator  << (double w);
# endif
  bool  operator  == (me s);
  bool  operator  != (me s);

  int  cmp(me s);
  bool  operator  < (me s);
  bool  operator  > (me s);
  bool  operator  <= (me s);
  bool  operator  >= (me s);

  u64   operator  ~  ();
  int   operator  !  ();
  bit *operator  *  ();
  inline bit &operator  [] (int i);
  me  &operator  () (int i);
  me  &operator  () (char *s, int i);
  int   operator  += (int  i);

  void del(int x, int c);
  void ins(me sub, int x);
  void ins(bit *sub, int x);
  void ins(bit sub, int x);

  void init();
  void unref();
  void copy();
  void resize(int newsize);
  void alloc(int x);
  me   add(void *p, int i);

  int  pos(bit *c);
  int  pos(me s);
  int  pos(bit c);
  int  find(int start, bit *c, int subsize);
  int  strcount(me substring);
  int  replace(me old, me _new, int start = 0,
       void *callback = 0, int count = -1);
  int  high();
  void fill(bit c);
  int  charsize() { return bytesize(1); }
  void save(char *filename);
  void save(me filename);
  void append(str filename);
  me *ptr();
  str  compat();
  me  sub(int pos, int count);
  int  occu();
  void attach(bit *c, int size = -1);
  str  binary();
  void binary(str b);
  int& geti(int i);
  word& getw(int i);
  me  upper();
  me  lower();
};

/////////////  CONSTRUCTORS //////////

me :: me()
{
  init();
}

me :: me (const me &s)
{
  p = s.p;
  if (p != 0) p->count++;
}

# ifndef onebyte
me :: me(str s)
{
  init();
  self(!s);
  byte * ab = (byte*) *s;
  ab += !s;
  word * bb = (word*) *self; bb += !self;
  int L = UTF2W((byte*) *s, ab, (word*) *self, bb);
  self(L);
}
# endif


me :: me (char *s)
{
  init();
  resize(len(s));
# ifdef onebyte
  move(s, p->p, !self);
# else
  each (x, self) self[x] = to_ascii(*s++);
# endif
}

me :: me (char ch)
{
  init();
  resize(1);
  (self)[0] = ch;
}

me :: me (int i)
{
  init();
  str s = "           ";
  tostr(*s, i);
  s(len(*s));
  self = s;
}

me :: me (unsigned int i)
{
  init();
  str s = "           ";
  tostr(*s, i);
  s(len(*s));
  self = s;
}

me :: me (double i)
{
   init();
   str s = "                   \0";
   tostr(*s, i);
   s(len(*s));
   self = s;
}

me :: me (wchar_t *s)
{
   init();
   self(len(s));
 # ifdef onebyte
   each (x, self)
     self[x] = to_ascii(*s++);
 # else
   move(s, *self, bytesize(!self));
 # endif
}

me :: me (wchar_t c)
{
   init();
   self(1);
   self[0] = c;
}

me :: ~me()
{
  unref();
}

////////////     INTERNALS    ////////////////

void me :: alloc(int x)
{
   if (x > !self)
   {
      int o = !self;
      self(x);
      p->size = o;
      p->p[p->size] = 0;
   }
}

void me :: resize(int newsize)
{
   copy();
   if (newsize > 0)
   {
      if (p == 0) init();
      if (p->capacity < newsize + 1)
      {
         p->capacity = newsize * 2 + 1;
         bit * p_old = p->p;
         bit * P = new bit[p->capacity];
         p->p = P;
         if (p_old)
         {
            move(p_old, p->p, bytesize(p->size));
            delete p_old;
         }
      }
      p->size = newsize;
      p->p[p->size] = 0;
   }
   else if (!self > 0)
   {
      delete p->p;
      p->p = 0;
      p->size = 0;
      unref();
   }
}

void me :: init()
{
   p = new strptr;
   p->p = 0;
   p->count = 1;
   p->size = 0;
   p->capacity = 0;
}

void me :: copy()
{
   if (p && p->count > 1)
   {
      p->count--; // line must be first due to multitask
      strptr *old;
      old = p;
      init();
      resize(old->size);
      int B = (bytesize(old->size));
      move(old->p, p->p, B);
   }
}

void me :: unref()
{
   if (p && --p->count == 0)
   {
       if (p->p)
       {
          delete p->p;
          p->p = 0;
       }
       delete p;
       p = 0;
   }
   else p = 0;
}

/////////////////   OPERATORS   ///////////////

void me :: operator = (const me &s)
{
  if (p == s.p) return;
  unref();
  if (s.p)
  {
     p = s.p;
     s.p->count++;
  } else
    self(0);
}  

me &me :: operator / (me s)
{
  if (!self == 0) self = s;
  else  self.ins(s, !self);
  return self;
}

me me :: operator + (me s)
{
  me r = self;
  r.ins(s, !r);
  return r;
}

me me :: operator + (char *s)
{
  me r = self;
  r.ins(s, !r);
  return r;
}

me me :: operator + (char ch)
{
  me r = self;
  r.ins(ch, !r);
  return r;
}

me me :: operator + (int i)
{
  me r = i;
  r.ins(self, 0);
  return r;
}

bool me :: operator == (me s)
{
//   return self.cmp(s) == 0;//== must me case sensitive
  if (!s != !self) return false;
  if (!s == !self && !s == 0) return true;
  if (!s == 0) return false;
  int i = -1;
  bit *a = *self, *b = *s;
  while (i++ < p->size)
  {
    if (*a++ != *b++) return false;
  }
  return true;
}

bool me :: operator != (me s)
{
   return !(self == s);
}

int me :: cmp (me s)
{
   if (!self == 0 && !s == 0) return 0;
   if (!self == 0) return -1;
   if (!s == 0) return 1;
   bit *a, *b, *ea, *eb;
   a = *self; b = *s;
   ea = a + !self;
   eb = b + !s;
   loop
   {
      bit A = *a, B = *b;
    # ifdef onebyte
      A = up_char(A);
      B = up_char(B);
    # else
      A = up_char(A);
      B = up_char(B);
    # endif
      if (A != B)
      {
         if (A < B) return -1;
         return 1;
      }
      if (a == ea) break;
      if (b == eb) break;
      a++;
      b++;
   }
   if (!self < !s) return -1;
   if (!self > !s) return 1;
   return 0;
}

bool me :: operator  < (me s)
{
   return self.cmp(s) == -1;
}

bool me :: operator  > (me s)
{
   return self.cmp(s) == 1;
}

bool me :: operator  <= (me s)
{
   return self.cmp(s) <= 0;
}

bool me :: operator  >= (me s)
{
   return self.cmp(s) >= 0;
}

////////////////  METHODS  /////////

u64 me :: operator ~ ()
{
#ifndef onebyte
   str s = self.compat();
#else
   str &s = self;
#endif
   int R = 0;
   if (!s == 0) return R;
   bool minus = false;
   int i = 0;
   if (s[0] == '-') { minus = true; i++; }
   for (; i < !s; i++)
   {
      if (s[i] == '.') break;
      if (s[i] < '0' || s[i] > '9') return 0;
      R = (R * 10) + (s[i] - '0');
   }
   if (minus) return -R;
   return R;
}

void me :: ins (me sub, int x)
{
  if (!sub == 0) return;
  copy();
  int oldsize;
  if (p != 0) oldsize = p->size; else oldsize = 0;
  self(!self + !sub);
  int c = (oldsize - x);
  if (c > 0)
  {
     bit *a, *b;
     a = &p->p[p->size - 1];
     b = &p->p[oldsize - 1];
     while (c--)
     {
       *a-- = *b;
       if (c) b--;
     }
  }
  move(*sub, p->p + x, bytesize(!sub));
}

me &me :: operator ()(int i)
{
  resize(i);
  return self;
}

me &me :: operator  () (char *s, int i)
{
   self(i);
   move(s, *self, i);
   return self;
}

int  me :: operator  += (int i)
{
  int r = !self;
  if (i < 0) { i = -i; }
  else r += i;
  self(!self + i);
  return r;
}

int me :: operator ! ()
{
  if (p == 0) return 0;
  return p->size;
}

bit * me :: operator * ()
{
   if (p == 0 || p->p == 0) 
     return (bit*) str_no_null;
///   copy();
   return p->p;
}

bit& me :: operator [](int i)
{
   copy();
   if (i < 0) i = !self + i;
   if (p == 0) { self(i); }
   return p->p[i];
}

void me :: del(int x, int c)
{
   if (x >= !self) return;
   if (c > !self - x) c = !self - x;
   copy();
   int newsize = !self - c;
   bit *a, *b;
   a = &p->p[x];
   b = &p->p[x + c];
   c = (!self - x) - c;
   while (c--){ *a++ = *b++; }
   resize(newsize);
}

void me :: ins (bit *sub, int x)
{
  me tmp(sub);
  ins(tmp, x);
}

void me :: ins (bit sub, int x)
{
  me tmp(sub);
  ins(tmp, x);
}

int me :: pos (bit *c)
{
 return find(0, c, len(c));
}

int me :: pos (me s)
{
 return find(0, *s, !s);
}

int me :: pos (bit c)
{
 return find(0, &c, 1);
}

int me :: find (int start, bit *c, int subsize)
{
  if (subsize == 0) return -1;
  int e = subsize;
  int l = start + e;
  int i = l - 1;
  while (i < !self)
    if (p->p[i] != c[e - 1]) i++;
    else {
      int x = e;
      bit    *a = &p->p[i], *b = &c[e - 1];
      while (x--)
      {
        if (*a != *b) { i++; break; }
        if (x > 0) { a--; b--; }
      }
      if (x < 0) return i - e + 1;
    }
  return -1;
}

int me :: strcount(me substring)
{
 int i = 0;
 int result = 0;
 while (true)
 {
  i = find(i, *substring, !substring);
  if (i < 0) return result;
  result ++;
  i += !substring;
 }
}

int me :: replace(
  me old, me _new, int start,
  void *callback,  int count
  )
{
 int subcount, len, si, di, x;
 me dest;
 if ((!old == 0) || (!self == 0)) return 0;
 int result = 0;
 if (!_new == 0)
  {
 //  return 0; // TODO: removestr(old, src, count);
  }
 subcount = strcount(old);
 dest(!self + subcount * (!_new - !old));
 if (!dest <= 0) dest(!self);
 si = start;
 di = si;
 move(&(self)[0], &dest[0], bytesize(si));
 while (true)
 {
  x = self.find(si, *old, !old);
  if ((x < 0) || ((count != -1) && (result == count)))
  {
    len = !self - si;
    if (len > 0) move(&((self)[si]), &(dest[di]), bytesize(len));
    dest(di + len);
    self = dest;
    return result;
  }
  else len = x - si;
  if (len > 0) move(&((self)[si]), &(dest[di]), bytesize(len));
  di = di + len;
  if (!_new > 0) move(&(*_new)[0], &(*dest)[di], bytesize(!_new));
  si = x + !old;
  di = di + !_new;
  //if (callback != 0) callback(si);
  result ++;
 }
}

int me :: high() { return !self - 1; }

void me :: fill(bit c)
{
   copy();
   each(i, self) self[i] = c;
}

void me :: save(char *filename)
{
   deletefile(filename);
   appendfile(filename, *self, !self);
}

void me :: save(me filename)
{
  save(*(str)filename);
}

me me :: sub(int pos, int count = 1)
{
   me s;
   if (count > !self - pos) count = !self - pos;
   s(count);
   if (count > 0)
     move(&( (self)[pos] ), *s, bytesize(count));
   return s;
}

me * me :: ptr()
{
   return this;
}

int  me :: occu()
{
   return (!self + 1) * charsize();
}

str me :: compat()
{
 # ifdef onebyte
    return self;
 # else
   str R;
   R(!self);
   each (i, R)
     R[i] = to_ascii(self[i]);
   return R;
 # endif
}

void me :: append(str filename)
{
  appendfile(*filename, *self, bytesize(!self));
}

# ifdef onebyte

me  &me :: operator  << (me s)
{
   int u = !self;
   self(u + 4 + !s);
   int i = !s;
   move(&i, & self[u], 4);
   move(*s, & self[u + 4], !s);
   return self;
}

me  &me :: operator  << (byte b)
{
   int u = !self;
   self(u + 1);
   * (word * )(& self[u]) = b;
   return self;
}

me  &me :: operator  << (word w)
{
   int u = !self;
   self(u + 2);
   * (word * )(& self[u]) = w;
   return self;
}

me  &me :: operator  << (int i)
{
   int u = !self;
   self(u + 4);
   * (int * )(& self[u]) = i;
   return self;
}

me  &me :: operator  << (double w)
{
   int u = !self;
   self(u + sizeof w);
   * (double * )(& self[u]) = w;
   return self;
}

me  &me :: operator  << (float f)
{
   int u = !self;
   self(u + sizeof f);
   * (float * )(& self[u]) = f;
   return self;
}

# endif

me  me :: add(void *p, int i)
{
   int u = !self;
   self(u + 4 + i);
   move(&i, & self[u], 4);
   move(p, & self[u + 4], i);
   return self;
}

void me::attach(bit *c, int size)
{
   self(0);
   p->p = c;
   if (size >= 0)
     p->size = size;
   else
     p->size = len(c);
   p->capacity = p->size;
}

str me :: binary()
{
 # ifdef onebyte
   return self;
 # else
   str r;
   r(bytesize(!self));
   move(*self, *r, !r);
   return r;
 # endif
}

void me :: binary(str b)
{
 # ifdef onebyte
   self = b;
 # else
   self(!b / 2);
   move(*b, *self, !self * 2);
 # endif
}

int& me :: geti(int i)
{
   return *(int*)&p->p[i];
}

word& me :: getw(int i)
{
   return *(word*)&p->p[i];
}

me me :: upper()
{
   me s = self;
   each (x, s)
      if (s[x] >= 'a' && s[x] <= 'z')
         s[x] -= 'a' - 'A';
   return s;
}

me me :: lower()
{
   me s = self;
   each (x, s) {
      if (s[x] >= 'A' && s[x] <= 'Z') s[x] += 'a' - 'A';
      }
   return s;
}

