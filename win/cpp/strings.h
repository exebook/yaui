const char *str_no_null = "\0\0\0\0";

char up_char(char c)
{
   if (c >= 'a' && c <= 'z')
     c -= 'a' - 'A';
   return c;
}

wchar_t up_char(wchar_t c)
{
   if (c >= 'a' && c <= 'z')
     c -= 'a' - 'A';
   return c;
}

word UTF = 0xFEFF;

int utf_offsets[6] = { 0x0UL, 0x3080UL, 0xE2080UL, 0x3C82080UL, 0xFA082080UL, 0x82082080UL };

byte utf_trail(int i)
{
   if (i < 192) return 0;
   if (i < 224) return 1;
   if (i < 240) return 2;
   if (i < 248) return 3;
   if (i < 252) return 4;
   return 5;
}

int UTF2W (byte* src, byte* SB, word* dst, word* TB)
{
    byte* S = src;
    word* T = dst;
    while (S < SB)
    {
	int ch = 0;
	word X = utf_trail(*S);
	if (S + X >= SB) break;
        int x = X;
        while (x-- > 0) ch += *S++, ch <<= 6;
        ch += *S++;
	ch -= utf_offsets[X];
	if (T >= TB) { S -= (X+1); break; }
	if (ch <= 0xFFFF)
        {
	    if (ch >= 0xD800 && ch <= 0xDFFF) *T++ = 0xFFFD;
            else *T++ = (word)ch;
	}
        else if (ch > 0x0010FFFF) *T++ = 0xFFFD;
	else
        {
	    if (T + 1 >= TB) { S -= (X+1); break; }
	    ch -= 0x0010000UL;
	    *T++ = (word)((ch >> 10) + 0xD800);
	    *T++ = (word)((ch & 0x3FFUL) + 0xDC00);
	}
    }
    return T - dst;
}

int wutf(char *D, int DD, wchar_t *S, int SS)
{
  int i = 0, n = 0, c;
  if (S == 0) return 0;
  if (D != 0)
  {
    while ((i < SS) && (n < DD))
    {
      c = S[i++];
      if (c <= 0x7F) D[n++] = c;
      else if (c > 0x7FF)
      {
        if (n + 3 > DD) break;
        D[n] = 0xE0 | (c >> 12);
        D[n + 1] = 0x80 | ((c >> 6) & 0x3F);
        D[n + 2] = 0x80 | (c & 0x3F);
        n += 3;
      }
      else
      {
        if (n + 2 > DD) break;
        D[n] = 0xC0 | (c >> 6);
        D[n + 1] = 0x80 | (c & 0x3F);
        n += 2;
      }
    }
    //if (n > DD) n = DD - 1;
    D[n] = 0;
  }
  else
  {
    while (i < SS)
    {
      c = S[i++];
      if (c > 0x7F) { if (c > 0x7FF) n++; n++; }
      n++;
    }
  }
  return n;
}

char to_ascii(wchar_t w)
{
   char c;
   char a = 0xE0; // rusA
   if (w >= 0x0410)
   c = (char) w - (0x0410 - a);
   else if (w == 0x0451) c = 184;
   else if (w == 0x2014) c = 0x97;
   else c = w & 0xff;
   return c;
}


struct str;
# define onebyte
# define me str
# define bit char
# define bytesize(a) a
#   include "str.cpp"
# undef me
# undef bit
# undef onebyte
# undef bytesize

# define me wstr
# define bit wchar_t
# define bytesize(a) (a * 2)
#   include "str.cpp"
# undef me
# undef bit

  typedef wstr Str;
  typedef wchar_t Char;

str load(str name)
{
   str R;
   R(filesize(*name));
   if (!R > 0)
     load(*name, *R, !R);
   return R;
}

str bhex(byte b)
{
    str s; char c;
    byte B;
    B = (b >> 4) & 0xF;
    if (B <= 9) c = B + '0'; else c = B - 10 + 'A'; s / c;
    B = b & 0xF;
    if (B <= 9) c = B + '0'; else c = B - 10 + 'A'; s / c;
    return s;
}

str hex_to_str(u32 c)
{
   str s;
   byte *b = (byte*)&c;
   s.ins(bhex(*b++), 0);
   s.ins(bhex(*b++), 0);
   s.ins(bhex(*b++), 0);
   s.ins(bhex(*b++), 0);
   return s;
}


u32 str_to_hex(str s)
{
  u32 R = 0;
  for (int i = 0; i < !s; i++)
  {
     R <<= 4;
     byte c = 0;
     if (s[i] >= '0' && s[i] <= '9') c = s[i] - '0';
     else if (s[i] >= 'a' && s[i] <= 'f') c = s[i] - 'a' + 10;
     else if (s[i] >= 'A' && s[i] <= 'F') c = s[i] - 'A' + 10;
     R |= c;
  }
  return R;
}

template <typename T>
T bite_t(T &s, T separator){
   T R;
   int i = s.pos(separator);
   if (i < 0)   {      R = s;      s(0);   }
   else
   {
      R(i);
      if (!R > 0) { move(*s, *R, !R * R.charsize()); }
      s.del(0, i + !separator);
   }
   return R;
}

str bite(str &s, str separator)
{
   return bite_t(s, separator);
}

#ifndef NO_WSTR
wstr bite(wstr &s, wstr separator)
{
   return bite_t(s, separator);
}

wstr wbite(wstr &s, wstr separator)
{
   return bite_t(s, separator);
}
#endif // NO_WSTR

int wutf_size(wstr S, bool prefix = false)
{
   int n = 0;
   int c;
   each (i, S)
   {
      c = S[i];
      if (c > 0x7F) { if (c > 0x7FF) n++; n++; }
      n++;
   }
   if (prefix) n += 2;
   return n;
}

str w2utf(wstr w, bool prefix = false)
{
  str R;
  if (!w == 0) return R;
  R(wutf_size(w, prefix));
  char * e = *R;
  if (prefix) e += 2;
  wutf(e, !R, *w, !w);
  if (prefix) move(& UTF, *R, 2);
  return R;
}

wstr utf2w(str s)
{
   if (!s >= 3 && (byte)s[0] == 0xef && (byte)s[1] == 0xbb && (byte)s[2] == 0xbf)
     s.del(0, 3);
   wstr R;
   R(!s);
   byte * ab = (byte*) *s;
   ab += !s;
   word * bb = (word*) *R; bb += !R;
   int L = UTF2W((byte*) *s, ab, (word*) *R, bb);
   R(L);
   return R;
}

