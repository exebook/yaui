#ifndef arr_h
#define arr_h

/*
    Array template class
*/

// # define array arr
// # define strings arr<str>
template <class T>

struct arr {

public:

typedef T *P;
int size, capacity, delta;
P p;

void basic()
{
   p = 0;
   size = 0;
   delta = 0;
   capacity = 0;
}

arr()
{
  basic();
}

~arr()
{
  resize(0);
}

arr (arr &n)
{
   basic();
   assign(n);
}
//#define operator inline operator
inline int operator !  ()
{
   return size;
}

inline int operator ~  ()
{
   return size - 1;
}

inline void  operator () (int i)
{
   resize(i);
}

inline void  operator = (arr &n)
{
   assign(n);
}

void assign (arr &n)
{
   resize(0);
   resize(n.size);
   for (int i = 0; i < size; i++) p[i] = n.p[i];
}

inline arr<T> & operator << (T item)
{
   self++;
   self[-1] = item;
   return self;
}

arr<T> & operator << (arr & S)
{
   int n = !self;
   self(n + !S);
   each(i, S) self[n + i] = S[i];
   return self;
}

arr<T> & operator >> (T item)
{
  if (size > 0) item = self[-1];
  self--;
  return self;
}

arr<T> & operator < (T item)
{
   ins(0, item);
   return self;
}

arr<T> & operator > (T item)
{
   item = self[0];
   del(0, 1);
   return self;
}

void del(int x, int count)
{
   if (count == 0) return;
   int c = size - x - count;
   int a = x, b = x + count;
   while (c--)
   {
     move((void *)&p[b], (void *)&p[a++], sizeof(T));
     fillchar((void *)&p[b++], sizeof(T), 0);
   }
   resize(size - count);
}
void real_resize(int newsize)
{
   P n;
   if (newsize == size) return;
   if (newsize <= 0)
   {
      delete[] p;
      p = 0;
      size = 0;
      return;
   }
   n = new T[newsize];
   int minimal = newsize; if (minimal > size) minimal = size;
   for (int i = 0; i < minimal; i++) n[i] = p[i];
   delete[] p;
   p = n;
   size = newsize;
}

void alloc(int new_capacity)
{
   int x = size;
   real_resize(new_capacity);
   size = x;
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
    if (newsize < (size / 2)) capacity = newsize;
    if (oldcap != capacity)
    {
      size = oldcap;
      real_resize(capacity);
    }
    size = newsize;
}

void sub(arr &result, int pos, int count)
{
  result(count);
  for (int i = 0; i < count; i++)
    result[i] = self[pos + i];
}

void ins(int x, T &item, int count = 1)
{
   if (count == 0) return;
   int c = size - x;
   resize(size + count);
   int a = size - 1, b = size - 1 - count;
   while (c--)
   {
      p[a--] = p[b--];
   }
   T *P = &item;
   for (int i = 0; i < count; i++)
     p[x + i] = *P++;
}

int find(T what)
{
   for (int i = 0; i < size; i++)
     if (what == p[i]) return i;
   return -1;
}

T & operator ++(int)
{
   resize(size + 1);
   return self[-1];
}

T & operator ++()
{
   T t;
   ins(0, t);
   return self[0];
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

void operator = (T item)
{
   self[-1] = item;               
}

inline T &  operator [] (int i)
{
   if (i < 0) i = size + i;
#ifdef ARR_CHECK
   if (i > !self)
   
#endif
   return p[i];
}

};

typedef arr<int> ints;
ints ints_hidden_variable;
                                     
#endif // arr_h


