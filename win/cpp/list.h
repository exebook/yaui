#ifndef list_h
#define list_h

template <typename T> struct list
{

typedef T** P;
P p;
int size, capacity, delta;

list()
{
   basic();
}

~list()
{
   resize(0);
}


//list& operator = (list &n)
void operator = (const list &n)
{
   assign(n);
//   return self;
}

list (const list &n)
{
  basic();
  assign(n);
}

void basic()
{
   p = 0;
   size = 0;
   delta = 0;
   capacity = 0;
}

T& operator ++()
{
   T t;
   ins(0, t);
   return self[0];
}

void real_resize(int newsize)
{
  P n;
  int i;
  if (newsize == size) return;
  for (i = newsize; i < size; i++)
  {
     if (p[i])
     {
       int ku = i;
       delete p[ku];
     }
  }
  if (newsize <= 0) { delete[] p; basic(); return; };
  n = new T*[newsize];
  for (i = size; i < newsize; n[i++] = 0);
  int minimal = newsize; if (minimal > size) minimal = size;
  if (p) for (int i = 0; i < minimal; i++) n[i] = p[i];
  delete[] p;
  size = newsize;
  p = n;
}

void resize(int newsize)
{
   if (newsize < 0) newsize = 0;
   int oldcap = capacity;
   if (newsize > capacity)
   {
      if (delta != 0)
      {
        capacity = size + delta;
        if (capacity < newsize) capacity = newsize;
      }  
      else capacity = newsize * 2;
   }
   if (newsize < size) capacity = newsize;
   if (oldcap != capacity)
   {
     size = oldcap;
     real_resize(capacity);
   }
   size = newsize;
}

int operator !  ()
{
   return size;
}

void operator ++ (int)
{
   resize(size + 1);
}

void operator () (int i)
{
   resize(i);
}

int  operator~()
{
   return size - 1;
}

T& operator [](int i)
{
  if (i < 0) i = size + i;
  if (p[i] == 0) p[i] = new T();
  return (*p[i]);
}

//list<T> & operator << (list<T> & S)
//{
//   int n = !self;
//   self(n + !S);
//   each(i, S) self[n + i] = S[i];
//   return self;
//}

list<T>& operator << (T item)
{
  resize(size + 1);
  self[size - 1] = item;
  return self;
}

list<T>& operator >> (T &item)
{
   resize(size - 1);
   if (size > 0) item = self[-1];
   return self;
}

list<T> & operator < (T item)
{
   ins(0, item);
   return self;
}

list<T> & operator > (T & item)
{
   item = self[0];
   del(0, 1);
}

T operator --(int)
{
   T t = self[-1];
   resize(size - 1);
   return t;
}

T operator --()
{
   T t = self[0];
   del(0, 1);
   return t;
}

void shmasign(list &n)
{
   size = n.size;
   capacity = n.capacity;
   delta = n.delta;
   p = n.p;
   n.p = 0;
   n.size = 0;
   n.capacity = 0;
}

void assign (const list &n)
{
   resize(0);
   resize(n.size);
   for (int i = 0; i < n.size; i++) self[i] = * n.p[i];
}

void del(int x, int count)
{
   if (count == 0) return;
   int c = size - x - count;
   P a = &p[x], b = &p[x + count];
   while (c--)
   {
     if (*a) delete *a; *a++ = *b; *b++ = 0;
   };
   resize(size - count);
}

void ins_from(int x, list <T> &src, int src_x, int count = -1)
{
   if (count < 0) count = !src;
   if (count == 0) return;
   if (x == -1) x = size;
   int c = size - x;
   resize(size + count);
   int a = size - 1, b = size - 1 - count;
   while (c--)
   {
      p[a--] = p[b--];
   };
   T **P = &src.p[src_x];
   for (int i = 0; i < count; i++)
   {
      T *tmp = new T;
      *tmp = **P;
      p[x + i] = tmp;
      P++;
   }  
}
                
void ins(int x, T item)
{
   resize(size + 1);
   int c = size - x;
   P a = &p[size - 1], b = &p[size - 2];
   while (--c) { *a-- = *b; *b = 0; b--; };
   *a = new T;
   **a = item;
}

void addptr(T *item)
{
   resize(size + 1);
   p[size - 1] = item;
}

# ifdef strings_cpp
str dump()
{
  str r;
  for (int i = 0; i < !self; i++) r = r + self[i] + ",";
  return r;
}
# endif

int find(T &what)
{
   for (int i = 0; i < size; i++)
     if (what == *p[i]) return i;
   return -1;
}

};

template <typename T>
struct slist : list<T> {
};

typedef list<str> strings;
# define wstrings slist<wstr>
# define Strings slist<Str>

#endif //#ifdef list_h
