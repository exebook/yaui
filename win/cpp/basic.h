  byte ticks_bits[3] = { 0x0F, 0x31, 0xC3};
  u64 ( * ticks ) () = (u64 (*) ()) & ticks_bits;
#define APP void * __stdcall
#define API int __stdcall

extern "C"
{
#ifndef _INC_STDIO
   void printf(char *, ...);
#endif
   API GetFileSize(void *, int *);
   API ReadFile(void *, void *, int, void *, int);
   API WriteFile(void *, void *, int, void *, void *);
   API CloseHandle(void *);
   API SetFilePointer(void *, int, int*, int);
   API SetConsoleTextAttribute(void*, word);
   APP CreateFileW(wchar_t *, int, int, void *, int, int, void *);
   API DeleteFileW(wchar_t *);
   APP CreateFileA(char *, int, int, void *, int, int, void *);
   API DeleteFileA(char *);
   API WriteConsoleA(void *, void *, int, void *, void *);
   API ExitProcess(int);
   APP GetStdHandle(int);
}
bool fileexists(wchar_t *n)
{
   bool B;
   void * F = CreateFileW(n, 1<<31, 1, 0, 3, 0, 0);
   B = ((int) F != -1);
   CloseHandle(F);
   return B;
}

bool fileexists(char *n)
{
   bool B;
   void * F = CreateFileA(n, 1<<31, 1, 0, 3, 0, 0);
   B = ((int) F != -1);
   CloseHandle(F);
   return B;
}

# ifdef _MSC_VER
#ifdef CONSOLE
void mainCRTStartup(){  main(0, 0);}
#endif
extern "C" {   int _fltused() { return 0;};}
# endif // _MSC_VER

float _sqrt (float number)
{
   long i;
   float f = 1.5, x = number/2, y = number;
   i  = * ( unsigned long * ) &y;
   i   = 0x5f3759df - ( i >> 1 );
   y = * ( float * ) &i;
   y = y * (f - x*y*y);
   return number * y;
}

void load(char *n, void* data, int size, int from_pos = 0)
{
   void * F = CreateFileA(n, 1<<31, 1, 0, 3, 0, 0);
   int rd;
   rd = GetFileSize(F, 0);
   SetFilePointer(F, from_pos, 0, 0);
   ReadFile(F, data, size, &rd, 0);
   CloseHandle(F);
}

int filesize(char * n)
{
   void * F = CreateFileA(n, 1<<31, 1, 0, 3, 0, 0);
   int R = GetFileSize(F, 0);
   CloseHandle(F);
   return R;
}

void appendfile(char *n, void *data, int size)
{
   void * F = CreateFileA(n, 1<<30, 1, 0, 4, 0, 0);
   SetFilePointer(F, 0, 0, 2);
   int w;
   WriteFile(F, data, size, & w, 0);
   CloseHandle(F);
}

void deletefile(char *n)
{
   DeleteFileA(n);
}

void fill32(int value, int *dest, int count)
{
  int *b = dest;
  while (count--) *b++ = value;
}

struct __rect
{
    int x, y, w, h;
};

void fillchar(void *dest, int count, char ch)
{
  if (count <= 0) return;
  char *b = (char *)dest;
  while (count--) *b++ = ch;
}

void move(void *src, void *dest, int count)
{
  if (count <= 0) return;
  char *a = (char *)src; char *b = (char *)dest;
  while (count--) *b++ = *a++;
}

void tostr(char *s, unsigned int i) {
   char *c = s;
   while (true)
   {
      unsigned int i10 = i / 10;
      *s = (i - (i10 * 10)) + '0';
      i = i10;
      s++;
      if (i == 0) { *s-- = 0; break; }
   }
   char *b = s;
   while (b > c)
   {
      char tmp = *b;
      *b-- = *c;
      *c++ = tmp;
   }
}

int len(char *c) {
   int R = 0;
   while (*c++) R++;
   return R;
}

int len(wchar_t *c) {
  int l = 0;
  if (c == 0) return 0;
  while (*c++) l++;
  return l;
}
