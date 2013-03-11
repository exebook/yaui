#ifndef WIN_H
#define WIN_H
#define WIN32

#define WINMAIN extern "C" int __stdcall WinMain(void*, void*, void*, int)
#    ifdef _MSC_VER
#       define type64 __int64
#    else
#       define type64 long long
#    endif
# define  self (*this)
# define  loop while(true)
# define  each(a, b) for (int a = 0, each_counter = !b; a < each_counter; a++)
# define dllex(a) extern "C" a __declspec(dllexport)
#define inherit(b, a) \
  child_##b##_##p : a { typedef a inherited; };\
  struct b : child_##b##_##p
  
typedef unsigned short word;
typedef char i8;
typedef short i16;
typedef int i32;
typedef unsigned char byte;
typedef unsigned char u8;
typedef unsigned int u32;
typedef unsigned short u16;
typedef float f32;
typedef double f64;

typedef type64 i64;
typedef unsigned type64 u64;
#include "basic.h"
#include "strings.h"
#include "list.h"
#include "arr.h"
#include "mywin.h"
#include "surface.h"
#include "winclass.h"

#endif //WIN_H

