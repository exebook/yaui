typedef unsigned short word;
typedef unsigned char byte;
typedef unsigned int u32;
           typedef unsigned long long u64;
namespace unixstuff
{
typedef signed char __int8_t;
typedef unsigned char __uint8_t;
typedef short __int16_t;
typedef unsigned short __uint16_t;
typedef int __int32_t;
typedef unsigned int __uint32_t;
typedef long long __int64_t;
typedef unsigned long long __uint64_t;
typedef long __darwin_intptr_t;
typedef unsigned int __darwin_natural_t;
typedef int __darwin_ct_rune_t;
typedef union {
 char __mbstate8[128];
 long long _mbstateL;
} __mbstate_t;
typedef __mbstate_t __darwin_mbstate_t;
typedef long int __darwin_ptrdiff_t;
typedef long unsigned int __darwin_size_t;
typedef __builtin_va_list __darwin_va_list;
typedef int __darwin_wchar_t;
typedef __darwin_wchar_t __darwin_rune_t;
typedef int __darwin_wint_t;
typedef unsigned long __darwin_clock_t;
typedef __uint32_t __darwin_socklen_t;
typedef long __darwin_ssize_t;
typedef long __darwin_time_t;
struct __darwin_pthread_handler_rec
{
 void (*__routine)(void *);
 void *__arg;
 struct __darwin_pthread_handler_rec *__next;
};
struct _opaque_pthread_attr_t { long __sig; char __opaque[56]; };
struct _opaque_pthread_cond_t { long __sig; char __opaque[40]; };
struct _opaque_pthread_condattr_t { long __sig; char __opaque[8]; };
struct _opaque_pthread_mutex_t { long __sig; char __opaque[56]; };
struct _opaque_pthread_mutexattr_t { long __sig; char __opaque[8]; };
struct _opaque_pthread_once_t { long __sig; char __opaque[8]; };
struct _opaque_pthread_rwlock_t { long __sig; char __opaque[192]; };
struct _opaque_pthread_rwlockattr_t { long __sig; char __opaque[16]; };
struct _opaque_pthread_t { long __sig; struct __darwin_pthread_handler_rec *__cleanup_stack; char __opaque[1168]; };
typedef __int64_t __darwin_blkcnt_t;
typedef __int32_t __darwin_blksize_t;
typedef __int32_t __darwin_dev_t;
typedef unsigned int __darwin_fsblkcnt_t;
typedef unsigned int __darwin_fsfilcnt_t;
typedef __uint32_t __darwin_gid_t;
typedef __uint32_t __darwin_id_t;
typedef __uint64_t __darwin_ino64_t;
typedef __darwin_ino64_t __darwin_ino_t;
typedef __darwin_natural_t __darwin_mach_port_name_t;
typedef __darwin_mach_port_name_t __darwin_mach_port_t;
typedef __uint16_t __darwin_mode_t;
typedef __int64_t __darwin_off_t;
typedef __int32_t __darwin_pid_t;
typedef struct _opaque_pthread_attr_t
   __darwin_pthread_attr_t;
typedef struct _opaque_pthread_cond_t
   __darwin_pthread_cond_t;
typedef struct _opaque_pthread_condattr_t
   __darwin_pthread_condattr_t;
typedef unsigned long __darwin_pthread_key_t;
typedef struct _opaque_pthread_mutex_t
   __darwin_pthread_mutex_t;
typedef struct _opaque_pthread_mutexattr_t
   __darwin_pthread_mutexattr_t;
typedef struct _opaque_pthread_once_t
   __darwin_pthread_once_t;
typedef struct _opaque_pthread_rwlock_t
   __darwin_pthread_rwlock_t;
typedef struct _opaque_pthread_rwlockattr_t
   __darwin_pthread_rwlockattr_t;
typedef struct _opaque_pthread_t
   *__darwin_pthread_t;
typedef __uint32_t __darwin_sigset_t;
typedef __int32_t __darwin_suseconds_t;
typedef __uint32_t __darwin_uid_t;
typedef __uint32_t __darwin_useconds_t;
typedef unsigned char __darwin_uuid_t[16];
typedef char __darwin_uuid_string_t[37];



struct timespec
{
 __darwin_time_t tv_sec;
 long tv_nsec;
};







struct timeval
{
 __darwin_time_t tv_sec;
 __darwin_suseconds_t tv_usec;
};
extern "C" {
typedef struct fd_set {
 __int32_t fds_bits[((((1024) % ((sizeof(__int32_t) * 8))) == 0) ? ((1024) / ((sizeof(__int32_t) * 8))) : (((1024) / ((sizeof(__int32_t) * 8))) + 1))];
} fd_set;
}
static inline int
__darwin_fd_isset(int _n, const struct fd_set *_p)
{
 return (_p->fds_bits[_n/(sizeof(__int32_t) * 8)] & (1<<(_n % (sizeof(__int32_t) * 8))));
}
typedef __darwin_time_t time_t;
typedef __darwin_suseconds_t suseconds_t;
struct itimerval {
 struct timeval it_interval;
 struct timeval it_value;
};
struct timezone {
 int tz_minuteswest;
 int tz_dsttime;
};
struct clockinfo {
 int hz;
 int tick;
 int tickadj;
 int stathz;
 int profhz;
};
typedef int __darwin_nl_item;
typedef int __darwin_wctrans_t;
typedef __uint32_t __darwin_wctype_t;
typedef __darwin_clock_t clock_t;
typedef __darwin_size_t size_t;
struct tm {
 int tm_sec;
 int tm_min;
 int tm_hour;
 int tm_mday;
 int tm_mon;
 int tm_year;
 int tm_wday;
 int tm_yday;
 int tm_isdst;
 long tm_gmtoff;
 char *tm_zone;
};
extern char *tzname[];
extern int getdate_err;
extern long timezone __asm("_" "timezone" );
extern int daylight;
extern "C" {
char *asctime(const struct tm *);
clock_t clock(void) __asm("_" "clock" );
char *ctime(const time_t *);
double difftime(time_t, time_t);
struct tm *getdate(const char *);
struct tm *gmtime(const time_t *);
struct tm *localtime(const time_t *);
time_t mktime(struct tm *) __asm("_" "mktime" );
size_t strftime(char * , size_t, const char * , const struct tm * ) __asm("_" "strftime" );
char *strptime(const char * , const char * , struct tm * ) __asm("_" "strptime" );
time_t time(time_t *);
void tzset(void);
char *asctime_r(const struct tm * , char * );
char *ctime_r(const time_t *, char *);
struct tm *gmtime_r(const time_t * , struct tm * );
struct tm *localtime_r(const time_t * , struct tm * );
time_t posix2time(time_t);
void tzsetwall(void);
time_t time2posix(time_t);
time_t timelocal(struct tm * const);
time_t timegm(struct tm * const);
int nanosleep(const struct timespec *, struct timespec *) __asm("_" "nanosleep" );
}
extern "C" {
int adjtime(const struct timeval *, struct timeval *);
int futimes(int, const struct timeval *);
int lutimes(const char *, const struct timeval *) __attribute__((visibility("default")));
int settimeofday(const struct timeval *, const struct timezone *);
int getitimer(int, struct itimerval *);
int gettimeofday(struct timeval * , void * );
int select(int, fd_set * , fd_set * ,
  fd_set * , struct timeval * )
  __asm("_" "select" "$1050")
  ;
int setitimer(int, const struct itimerval * ,
  struct itimerval * );
int utimes(const char *, const struct timeval *);
}
extern "C" {
extern int * __error(void);
}
typedef __darwin_va_list va_list;
typedef __darwin_off_t fpos_t;
struct __sbuf {
 unsigned char *_base;
 int _size;
};
struct __sFILEX;
typedef struct __sFILE {
 unsigned char *_p;
 int _r;
 int _w;
 short _flags;
 short _file;
 struct __sbuf _bf;
 int _lbfsize;
 void *_cookie;
 int (*_close)(void *);
 int (*_read) (void *, char *, int);
 fpos_t (*_seek) (void *, fpos_t, int);
 int (*_write)(void *, const char *, int);
 struct __sbuf _ub;
 struct __sFILEX *_extra;
 int _ur;
 unsigned char _ubuf[3];
 unsigned char _nbuf[1];
 struct __sbuf _lb;
 int _blksize;
 fpos_t _offset;
} FILE;
extern "C" {
extern FILE *__stdinp;
extern FILE *__stdoutp;
extern FILE *__stderrp;
}
extern "C" {
void clearerr(FILE *);
int fclose(FILE *);
int feof(FILE *);
int ferror(FILE *);
int fflush(FILE *);
int fgetc(FILE *);
int fgetpos(FILE * , fpos_t *);
char *fgets(char * , int, FILE *);
FILE *fopen(const char * , const char * ) __asm("_" "fopen" );
int fprintf(FILE * , const char * , ...) __attribute__((__format__ (__printf__, 2, 3)));
int fputc(int, FILE *);
int fputs(const char * , FILE * ) __asm("_" "fputs" );
size_t fread(void * , size_t, size_t, FILE * );
FILE *freopen(const char * , const char * ,
                 FILE * ) __asm("_" "freopen" );
int fscanf(FILE * , const char * , ...) __attribute__((__format__ (__scanf__, 2, 3)));
int fseek(FILE *, long, int);
int fsetpos(FILE *, const fpos_t *);
long ftell(FILE *);
size_t fwrite(const void * , size_t, size_t, FILE * ) __asm("_" "fwrite" );
int getc(FILE *);
int getchar(void);
char *gets(char *);
void perror(const char *);
int printf(const char * , ...) __attribute__((__format__ (__printf__, 1, 2)));
int putc(int, FILE *);
int putchar(int);
int puts(const char *);
int remove(const char *);
int rename (const char *, const char *);
void rewind(FILE *);
int scanf(const char * , ...) __attribute__((__format__ (__scanf__, 1, 2)));
void setbuf(FILE * , char * );
int setvbuf(FILE * , char * , int, size_t);
int sprintf(char * , const char * , ...) __attribute__((__format__ (__printf__, 2, 3)));
int sscanf(const char * , const char * , ...) __attribute__((__format__ (__scanf__, 2, 3)));
FILE *tmpfile(void);
char *tmpnam(char *);
int ungetc(int, FILE *);
int vfprintf(FILE * , const char * , va_list) __attribute__((__format__ (__printf__, 2, 0)));
int vprintf(const char * , va_list) __attribute__((__format__ (__printf__, 1, 0)));
int vsprintf(char * , const char * , va_list) __attribute__((__format__ (__printf__, 2, 0)));
}
extern "C" {
char *ctermid(char *);
FILE *fdopen(int, const char *) __asm("_" "fdopen" );
int fileno(FILE *);
}
extern "C" {
int pclose(FILE *);
FILE *popen(const char *, const char *) __asm("_" "popen" );
}
extern "C" {
int __srget(FILE *);
int __svfscanf(FILE *, const char *, va_list) __attribute__((__format__ (__scanf__, 2, 0)));
int __swbuf(int, FILE *);
}
static inline int __sputc(int _c, FILE *_p) {
 if (--_p->_w >= 0 || (_p->_w >= _p->_lbfsize && (char)_c != '\n'))
  return (*_p->_p++ = _c);
 else
  return (__swbuf(_c, _p));
}
extern "C" {
void flockfile(FILE *);
int ftrylockfile(FILE *);
void funlockfile(FILE *);
int getc_unlocked(FILE *);
int getchar_unlocked(void);
int putc_unlocked(int, FILE *);
int putchar_unlocked(int);
int getw(FILE *);
int putw(int, FILE *);
char *tempnam(const char *, const char *) __asm("_" "tempnam" );
}
typedef __darwin_off_t off_t;
extern "C" {
int fseeko(FILE *, off_t, int);
off_t ftello(FILE *);
}
extern "C" {
int snprintf(char * , size_t, const char * , ...) __attribute__((__format__ (__printf__, 3, 4)));
int vfscanf(FILE * , const char * , va_list) __attribute__((__format__ (__scanf__, 2, 0)));
int vscanf(const char * , va_list) __attribute__((__format__ (__scanf__, 1, 0)));
int vsnprintf(char * , size_t, const char * , va_list) __attribute__((__format__ (__printf__, 3, 0)));
int vsscanf(const char * , const char * , va_list) __attribute__((__format__ (__scanf__, 2, 0)));
}
typedef __darwin_ssize_t ssize_t;
extern "C" {
int dprintf(int, const char * , ...) __attribute__((__format__ (__printf__, 2, 3))) __attribute__((visibility("default")));
int vdprintf(int, const char * , va_list) __attribute__((__format__ (__printf__, 2, 0))) __attribute__((visibility("default")));
ssize_t getdelim(char ** , size_t * , int, FILE * ) __attribute__((visibility("default")));
ssize_t getline(char ** , size_t * , FILE * ) __attribute__((visibility("default")));
}
extern "C" {
extern const int sys_nerr;
extern const char *const sys_errlist[];
int asprintf(char **, const char *, ...) __attribute__((__format__ (__printf__, 2, 3)));
char *ctermid_r(char *);
char *fgetln(FILE *, size_t *);
const char *fmtcheck(const char *, const char *);
int fpurge(FILE *);
void setbuffer(FILE *, char *, int);
int setlinebuf(FILE *);
int vasprintf(char **, const char *, va_list) __attribute__((__format__ (__printf__, 2, 0)));
FILE *zopen(const char *, const char *, int);
FILE *funopen(const void *,
                 int (*)(void *, char *, int),
                 int (*)(void *, const char *, int),
                 fpos_t (*)(void *, fpos_t, int),
                 int (*)(void *));
}
struct accessx_descriptor {
 unsigned int ad_name_offset;
 int ad_flags;
 int ad_pad[2];
};
typedef signed char int8_t;
typedef unsigned char u_int8_t;
typedef short int16_t;
typedef unsigned short u_int16_t;
typedef int int32_t;
typedef unsigned int u_int32_t;
typedef long long int64_t;
typedef unsigned long long u_int64_t;
typedef int64_t register_t;
typedef __darwin_intptr_t intptr_t;
typedef unsigned long uintptr_t;
typedef u_int64_t user_addr_t;
typedef u_int64_t user_size_t;
typedef int64_t user_ssize_t;
typedef int64_t user_long_t;
typedef u_int64_t user_ulong_t;
typedef int64_t user_time_t;
typedef int64_t user_off_t;
typedef u_int64_t syscall_arg_t;
static inline
__uint16_t
_OSSwapInt16(
    __uint16_t _data
)
{
    return ((_data << 8) | (_data >> 8));
}
static inline
__uint32_t
_OSSwapInt32(
    __uint32_t _data
)
{
    return __builtin_bswap32(_data);
}
static inline
__uint64_t
_OSSwapInt64(
    __uint64_t _data
)
{
    return __builtin_bswap64(_data);
}
typedef unsigned char u_char;
typedef unsigned short u_short;
typedef unsigned int u_int;
typedef unsigned long u_long;
typedef unsigned short ushort;
typedef unsigned int uint;
typedef u_int64_t u_quad_t;
typedef int64_t quad_t;
typedef quad_t * qaddr_t;
typedef char * caddr_t;
typedef int32_t daddr_t;
typedef __darwin_dev_t dev_t;
typedef u_int32_t fixpt_t;
typedef __darwin_blkcnt_t blkcnt_t;
typedef __darwin_blksize_t blksize_t;
typedef __darwin_gid_t gid_t;
typedef __uint32_t in_addr_t;
typedef __uint16_t in_port_t;
typedef __darwin_ino_t ino_t;
typedef __darwin_ino64_t ino64_t;
typedef __int32_t key_t;
typedef __darwin_mode_t mode_t;
typedef __uint16_t nlink_t;
typedef __darwin_id_t id_t;
typedef __darwin_pid_t pid_t;
typedef int32_t segsz_t;
typedef int32_t swblk_t;
typedef __darwin_uid_t uid_t;
static inline __int32_t major(__uint32_t _x)
{
 return (__int32_t)(((__uint32_t)_x >> 24) & 0xff);
}
static inline __int32_t minor(__uint32_t _x)
{
 return (__int32_t)((_x) & 0xffffff);
}
static inline dev_t makedev(__uint32_t _major, __uint32_t _minor)
{
 return (dev_t)(((_major) << 24) | (_minor));
}
typedef __darwin_useconds_t useconds_t;
typedef __int32_t fd_mask;
typedef __darwin_pthread_attr_t pthread_attr_t;
typedef __darwin_pthread_cond_t pthread_cond_t;
typedef __darwin_pthread_condattr_t pthread_condattr_t;
typedef __darwin_pthread_mutex_t pthread_mutex_t;
typedef __darwin_pthread_mutexattr_t pthread_mutexattr_t;
typedef __darwin_pthread_once_t pthread_once_t;
typedef __darwin_pthread_rwlock_t pthread_rwlock_t;
typedef __darwin_pthread_rwlockattr_t pthread_rwlockattr_t;
typedef __darwin_pthread_t pthread_t;
typedef __darwin_pthread_key_t pthread_key_t;
typedef __darwin_fsblkcnt_t fsblkcnt_t;
typedef __darwin_fsfilcnt_t fsfilcnt_t;
typedef __uint8_t sa_family_t;
typedef __darwin_socklen_t socklen_t;
struct iovec {
 void * iov_base;
 size_t iov_len;
};
struct linger {
 int l_onoff;
 int l_linger;
};
struct so_np_extensions {
 u_int32_t npx_flags;
 u_int32_t npx_mask;
};
struct sockaddr {
 __uint8_t sa_len;
 sa_family_t sa_family;
 char sa_data[14];
};
struct sockproto {
 __uint16_t sp_family;
 __uint16_t sp_protocol;
};
struct sockaddr_storage {
 __uint8_t ss_len;
 sa_family_t ss_family;
 char __ss_pad1[((sizeof(__int64_t)) - sizeof(__uint8_t) - sizeof(sa_family_t))];
 __int64_t __ss_align;
 char __ss_pad2[(128 - sizeof(__uint8_t) - sizeof(sa_family_t) - ((sizeof(__int64_t)) - sizeof(__uint8_t) - sizeof(sa_family_t)) - (sizeof(__int64_t)))];
};
struct msghdr {
 void *msg_name;
 socklen_t msg_namelen;
 struct iovec *msg_iov;
 int msg_iovlen;
 void *msg_control;
 socklen_t msg_controllen;
 int msg_flags;
};
struct cmsghdr {
 socklen_t cmsg_len;
 int cmsg_level;
 int cmsg_type;
};
struct sf_hdtr {
 struct iovec *headers;
 int hdr_cnt;
 struct iovec *trailers;
 int trl_cnt;
};
extern "C" {
int accept(int, struct sockaddr * , socklen_t * )
  __asm("_" "accept" );
int bind(int, const struct sockaddr *, socklen_t) __asm("_" "bind" );
int connect(int, const struct sockaddr *, socklen_t) __asm("_" "connect" );
int getpeername(int, struct sockaddr * , socklen_t * )
  __asm("_" "getpeername" );
int getsockname(int, struct sockaddr * , socklen_t * )
  __asm("_" "getsockname" );
int getsockopt(int, int, int, void * , socklen_t * );
int listen(int, int) __asm("_" "listen" );
ssize_t recv(int, void *, size_t, int) __asm("_" "recv" );
ssize_t recvfrom(int, void *, size_t, int, struct sockaddr * ,
  socklen_t * ) __asm("_" "recvfrom" );
ssize_t recvmsg(int, struct msghdr *, int) __asm("_" "recvmsg" );
ssize_t send(int, const void *, size_t, int) __asm("_" "send" );
ssize_t sendmsg(int, const struct msghdr *, int) __asm("_" "sendmsg" );
ssize_t sendto(int, const void *, size_t,
  int, const struct sockaddr *, socklen_t) __asm("_" "sendto" );
int setsockopt(int, int, int, const void *, socklen_t);
int shutdown(int, int);
int sockatmark(int) __attribute__((visibility("default")));
int socket(int, int, int);
int socketpair(int, int, int, int *) __asm("_" "socketpair" );
int sendfile(int, int, off_t, off_t *, struct sf_hdtr *, int);
void pfctlinput(int, struct sockaddr *);
}
typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
typedef unsigned int uint32_t;
typedef unsigned long long uint64_t;
typedef int8_t int_least8_t;
typedef int16_t int_least16_t;
typedef int32_t int_least32_t;
typedef int64_t int_least64_t;
typedef uint8_t uint_least8_t;
typedef uint16_t uint_least16_t;
typedef uint32_t uint_least32_t;
typedef uint64_t uint_least64_t;
typedef int8_t int_fast8_t;
typedef int16_t int_fast16_t;
typedef int32_t int_fast32_t;
typedef int64_t int_fast64_t;
typedef uint8_t uint_fast8_t;
typedef uint16_t uint_fast16_t;
typedef uint32_t uint_fast32_t;
typedef uint64_t uint_fast64_t;
typedef long int intmax_t;
typedef long unsigned int uintmax_t;
struct in_addr {
 in_addr_t s_addr;
};
struct sockaddr_in {
 __uint8_t sin_len;
 sa_family_t sin_family;
 in_port_t sin_port;
 struct in_addr sin_addr;
 char sin_zero[8];
};
struct ip_opts {
 struct in_addr ip_dst;
 char ip_opts[40];
};
struct ip_mreq {
 struct in_addr imr_multiaddr;
 struct in_addr imr_interface;
};
struct ip_mreqn {
 struct in_addr imr_multiaddr;
 struct in_addr imr_address;
 int imr_ifindex;
};
#pragma pack(4)
struct ip_mreq_source {
 struct in_addr imr_multiaddr;
 struct in_addr imr_sourceaddr;
 struct in_addr imr_interface;
};
struct group_req {
 uint32_t gr_interface;
 struct sockaddr_storage gr_group;
};
struct group_source_req {
 uint32_t gsr_interface;
 struct sockaddr_storage gsr_group;
 struct sockaddr_storage gsr_source;
};
struct __msfilterreq {
 uint32_t msfr_ifindex;
 uint32_t msfr_fmode;
 uint32_t msfr_nsrcs;
 uint32_t __msfr_align;
 struct sockaddr_storage msfr_group;
 struct sockaddr_storage *msfr_srcs;
};
#pragma pack()
struct sockaddr;
int setipv4sourcefilter(int, struct in_addr, struct in_addr, uint32_t,
     uint32_t, struct in_addr *) __attribute__((visibility("default")));
int getipv4sourcefilter(int, struct in_addr, struct in_addr, uint32_t *,
     uint32_t *, struct in_addr *) __attribute__((visibility("default")));
int setsourcefilter(int, uint32_t, struct sockaddr *, socklen_t,
     uint32_t, uint32_t, struct sockaddr_storage *) __attribute__((visibility("default")));
int getsourcefilter(int, uint32_t, struct sockaddr *, socklen_t,
     uint32_t *, uint32_t *, struct sockaddr_storage *) __attribute__((visibility("default")));
struct in_pktinfo {
 unsigned int ipi_ifindex;
 struct in_addr ipi_spec_dst;
 struct in_addr ipi_addr;
};
struct in6_addr {
 union {
  __uint8_t __u6_addr8[16];
  __uint16_t __u6_addr16[8];
  __uint32_t __u6_addr32[4];
 } __u6_addr;
};
struct sockaddr_in6 {
 __uint8_t sin6_len;
 sa_family_t sin6_family;
 in_port_t sin6_port;
 __uint32_t sin6_flowinfo;
 struct in6_addr sin6_addr;
 __uint32_t sin6_scope_id;
};
extern const struct in6_addr in6addr_any;
extern const struct in6_addr in6addr_loopback;
extern const struct in6_addr in6addr_nodelocal_allnodes;
extern const struct in6_addr in6addr_linklocal_allnodes;
extern const struct in6_addr in6addr_linklocal_allrouters;
extern const struct in6_addr in6addr_linklocal_allv2routers;
struct ipv6_mreq {
 struct in6_addr ipv6mr_multiaddr;
 unsigned int ipv6mr_interface;
};
struct in6_pktinfo {
 struct in6_addr ipi6_addr;
 unsigned int ipi6_ifindex;
};
struct ip6_mtuinfo {
 struct sockaddr_in6 ip6m_addr;
 uint32_t ip6m_mtu;
};
extern "C" {
struct cmsghdr;
extern int inet6_option_space(int);
extern int inet6_option_init(void *, struct cmsghdr **, int);
extern int inet6_option_append(struct cmsghdr *, const __uint8_t *,
 int, int);
extern __uint8_t *inet6_option_alloc(struct cmsghdr *, int, int, int);
extern int inet6_option_next(const struct cmsghdr *, __uint8_t **);
extern int inet6_option_find(const struct cmsghdr *, __uint8_t **, int);
extern size_t inet6_rthdr_space(int, int);
extern struct cmsghdr *inet6_rthdr_init(void *, int);
extern int inet6_rthdr_add(struct cmsghdr *, const struct in6_addr *,
  unsigned int);
extern int inet6_rthdr_lasthop(struct cmsghdr *, unsigned int);
extern int inet6_rthdr_segments(const struct cmsghdr *);
extern struct in6_addr *inet6_rthdr_getaddr(struct cmsghdr *, int);
extern int inet6_rthdr_getflags(const struct cmsghdr *, int);
extern int inet6_opt_init(void *, socklen_t);
extern int inet6_opt_append(void *, socklen_t, int, __uint8_t,
     socklen_t, __uint8_t, void **);
extern int inet6_opt_finish(void *, socklen_t, int);
extern int inet6_opt_set_val(void *, int, void *, socklen_t);
extern int inet6_opt_next(void *, socklen_t, int, __uint8_t *,
          socklen_t *, void **);
extern int inet6_opt_find(void *, socklen_t, int, __uint8_t,
     socklen_t *, void **);
extern int inet6_opt_get_val(void *, int, void *, socklen_t);
extern socklen_t inet6_rth_space(int, int);
extern void *inet6_rth_init(void *, socklen_t, int, int);
extern int inet6_rth_add(void *, const struct in6_addr *);
extern int inet6_rth_reverse(const void *, void *);
extern int inet6_rth_segments(const void *);
extern struct in6_addr *inet6_rth_getaddr(const void *, int);
extern void addrsel_policy_init(void);
}
extern "C" {
int bindresvport(int, struct sockaddr_in *);
struct sockaddr;
int bindresvport_sa(int, struct sockaddr *);
}
extern int h_errno;
struct hostent {
 char *h_name;
 char **h_aliases;
 int h_addrtype;
 int h_length;
 char **h_addr_list;
};
struct netent {
 char *n_name;
 char **n_aliases;
 int n_addrtype;
 uint32_t n_net;
};
struct servent {
 char *s_name;
 char **s_aliases;
 int s_port;
 char *s_proto;
};
struct protoent {
 char *p_name;
 char **p_aliases;
 int p_proto;
};
struct addrinfo {
 int ai_flags;
 int ai_family;
 int ai_socktype;
 int ai_protocol;
 socklen_t ai_addrlen;
 char *ai_canonname;
 struct sockaddr *ai_addr;
 struct addrinfo *ai_next;
};
struct rpcent {
        char *r_name;
        char **r_aliases;
        int r_number;
};
extern "C" {
void endhostent(void);
void endnetent(void);
void endprotoent(void);
void endservent(void);
void freeaddrinfo(struct addrinfo *);
const char *gai_strerror(int);
int getaddrinfo(const char * , const char * ,
       const struct addrinfo * ,
       struct addrinfo ** );
struct hostent *gethostbyaddr(const void *, socklen_t, int);
struct hostent *gethostbyname(const char *);
struct hostent *gethostent(void);
int getnameinfo(const struct sockaddr * , socklen_t,
         char * , socklen_t, char * ,
         socklen_t, int);
struct netent *getnetbyaddr(uint32_t, int);
struct netent *getnetbyname(const char *);
struct netent *getnetent(void);
struct protoent *getprotobyname(const char *);
struct protoent *getprotobynumber(int);
struct protoent *getprotoent(void);
struct servent *getservbyname(const char *, const char *);
struct servent *getservbyport(int, const char *);
struct servent *getservent(void);
void sethostent(int);
void setnetent(int);
void setprotoent(int);
void setservent(int);
void freehostent(struct hostent *);
struct hostent *gethostbyname2(const char *, int);
struct hostent *getipnodebyaddr(const void *, size_t, int, int *);
struct hostent *getipnodebyname(const char *, int, int, int *);
struct rpcent *getrpcbyname(const char *name);
struct rpcent *getrpcbynumber(int number);
struct rpcent *getrpcent(void);
void setrpcent(int stayopen);
void endrpcent(void);
void herror(const char *);
const char *hstrerror(int);
int innetgr(const char *, const char *, const char *, const char *);
int getnetgrent(char **, char **, char **);
void endnetgrent(void);
void setnetgrent(const char *);
}
struct sockaddr_un {
 unsigned char sun_len;
 sa_family_t sun_family;
 char sun_path[104];
};
extern "C" {
in_addr_t inet_addr(const char *);
char *inet_ntoa(struct in_addr);
const char *inet_ntop(int, const void *, char *, socklen_t);
int inet_pton(int, const char *, void *);
int ascii2addr(int, const char *, void *);
char *addr2ascii(int, const void *, int, char *);
int inet_aton(const char *, struct in_addr *);
in_addr_t inet_lnaof(struct in_addr);
struct in_addr inet_makeaddr(in_addr_t, in_addr_t);
in_addr_t inet_netof(struct in_addr);
in_addr_t inet_network(const char *);
char *inet_net_ntop(int, const void *, int, char *, __darwin_size_t);
int inet_net_pton(int, const char *, void *, __darwin_size_t);
char *inet_neta(in_addr_t, char *, __darwin_size_t);
unsigned int inet_nsap_addr(const char *, unsigned char *, int maxlen);
char *inet_nsap_ntoa(int, const unsigned char *, char *ascii);
}
struct passwd {
 char *pw_name;
 char *pw_passwd;
 uid_t pw_uid;
 gid_t pw_gid;
 __darwin_time_t pw_change;
 char *pw_class;
 char *pw_gecos;
 char *pw_dir;
 char *pw_shell;
 __darwin_time_t pw_expire;
};
extern "C" {
struct passwd *getpwuid(uid_t);
struct passwd *getpwnam(const char *);
int getpwuid_r(uid_t, struct passwd *, char *, size_t, struct passwd **);
int getpwnam_r(const char *, struct passwd *, char *, size_t, struct passwd **);
struct passwd *getpwent(void);
void setpwent(void);
void endpwent(void);
}
typedef __darwin_uuid_t uuid_t;
typedef __darwin_uuid_string_t uuid_string_t;
extern "C" {
void uuid_clear(uuid_t uu);
int uuid_compare(const uuid_t uu1, const uuid_t uu2);
void uuid_copy(uuid_t dst, const uuid_t src);
void uuid_generate(uuid_t out);
void uuid_generate_random(uuid_t out);
void uuid_generate_time(uuid_t out);
int uuid_is_null(const uuid_t uu);
int uuid_parse(const uuid_string_t in, uuid_t uu);
void uuid_unparse(const uuid_t uu, uuid_string_t out);
void uuid_unparse_lower(const uuid_t uu, uuid_string_t out);
void uuid_unparse_upper(const uuid_t uu, uuid_string_t out);
}
extern "C" {
int setpassent(int);
char *user_from_uid(uid_t, int);
struct passwd *getpwuuid(uuid_t);
int getpwuuid_r(uuid_t, struct passwd *, char *, size_t, struct passwd **);
}
}
void move(void *src, void *dest, int count)
{
  if (count <= 0) return;
  char *a = (char *)src; char *b = (char *)dest;
  while (count--) *b++ = *a++;
}
void movew(void *src, void *dest, int count)
{
   wchar_t *b = (wchar_t *)src, *a = (wchar_t *)dest;
   if (count > 0) while (count--) *a++ = *b++;
}
void move2(void* from1, void *to1, int count)
{
  if (count <= 0) return;
  char *from = (char*)from1, *to = (char*)to1;
  switch (count % 8)
  {
    case 0: do { *to++ = *from++;
    case 7: *to++ = *from++;
    case 6: *to++ = *from++;
    case 5: *to++ = *from++;
    case 4: *to++ = *from++;
    case 3: *to++ = *from++;
    case 2: *to++ = *from++;
    case 1: *to++ = *from++;
                      } while ((count -= 8) > 0);
  }
}
void move3(void* from1, void *to1, int count)
{
  if (count <= 0) return;
  char *from = (char*)from1, *to = (char*)to1;
  switch (count % 8)
  {
    case 0: do { *to++ = *from++;
    case 7: *to++ = *from++;
    case 6: *to++ = *from++;
    case 5: *to++ = *from++;
    case 4: *to++ = *from++;
    case 3: *to++ = *from++;
    case 2: *to++ = *from++;
    case 1: *to++ = *from++;
                      } while ((count -= 8) > 0);
  }
}
template <typename T> void swap(T &a, T &b) { T t = a; a = b; b = t; }
bool same(void *a, void *b, int size)
{
   if (size == 0) return true;
   if (size < 0) return false;
   char *A = (char *)a, *B = (char *)b;
   while (size--)
   {
      if (*A++ != *B++ ) return false;
   }
   return true;
}
int min(int a, int b)
{
  if (a > b) return b;
  return a;
}
int max(int a, int b)
{
  if (a < b) return b;
  return a;
}
template <typename T> T ABS(T a)
{
  return ((a) >= 0 ? (a) : -(a));
}
template <typename T> T abs(T a)
{
  return ((a) >= 0 ? (a) : -(a));
}
void move32(void *src, void *dest, int count)
{
  int *a = (int*)src; int *b = (int*)dest;
  while (count--) *b++ = *a++;
}
void fill32(int value, int *dest, int count)
{
  int *b = dest;
  while (count--) *b++ = value;
}
void invert32(int *dest, int count)
{
  int *b = dest;
  while (count--)
  {
    *b = !*b;
    b++;
  }
}
void * my_cast(...)
{
   int *n;
   return (int*)(&n)[3];
}
void xchg(void *a, void *b, int size)
{
  char ch;
  char *A = (char *)a, *B = (char *)b;
  while (size-- > 0)
  {
     ch = *A; *A++ = *B; *B++ = ch;
  }
}
void __limit(int &i, int min, int max)
{
 if (min < max)
  {
   if (i < min) i = min;
   else if (i > max) i = max;
  }
 else
  {
   if (i < max) i = max;
   else if (i > min) i = min;
  }
}
void fillchar(void *dest, int count, char ch)
{
  if (count <= 0) return;
  char *b = (char *)dest;
  while (count--) *b++ = ch;
}
void memset(void *dest, char ch, int count)
{
   fillchar(dest, count, ch);
}
template <typename T>
struct mb
{
   T *a;
   mb& operator () (T &A) { a = &A; return *this; }
   mb& operator > (T b) { if (*a <= b) *a = b + 1; return *this; }
   mb& operator < (T b) { if (*a >= b) *a = b - 1; return *this; }
   mb& operator >= (T b) { if (*a < b) *a = b; return *this; }
   mb& operator <= (T b) { if (*a > b) *a = b; return *this; }
};
mb <int> mustbe;
mb <double> dmustbe;
template <typename T>
struct typish
{
   struct N
   {
      char *x;
      T & operator [] (int i)
      {
         return *(T *) & x[i];
      }
   };
   N operator [] (void *c)
   {
      N R;
      R.x = (char *) c;
      return R;
   }
};
typish <char> charish;
typish <word> wordish;
typish <int> intish;
typish <float> floatish;
typish <double> doublish;
struct rgb
{
   byte r, g, b, k;
   rgb()
   {
       *(int*)(&r) = 0;
   }
   void operator = (rgb &x)
   {
      intish[&r][0] = intish[&x.r][0];
   }
   rgb(int c)
   {
       * (int *)(& r) = c;
   }
   void operator = (int i)
   {
       *(int *)(& r) = i;
   }
   operator int()
   {
       return * (int *)(& r);
   }
};
struct timeval1 {
   int tv_sec;
   int tv_usec;
};
int time1000()
{
  using namespace unixstuff;
  timeval val;
  gettimeofday(&val, 0);
  return val.tv_sec * 1000 + val.tv_usec / 1000;
}
int daysec = 60 * 60 * 24;
extern "C" int usleep(int);
void delay(int seconds, int miliseconds)
{
  int total, current, left, stop;
  total = seconds * 1000 + miliseconds;
  stop = time1000() + total;
  current = time1000();
  while (true) {
   left = stop - current;
   usleep(left * 1000);
   current = time1000();
   if (current > stop) break;
  }
}
struct rect
{
    int x, y, w, h;
};
int blend(int C1, int C2, int frame, int frame_count)
{
   rgb a = C1, b = C2;
   a.r += ((double)(b.r - a.r) / frame_count) * frame; a.g += ((double)(b.g - a.g) / frame_count) * frame; a.b += ((double)(b.b - a.b) / frame_count) * frame;
   return a;
}
int brightness(int c, int x)
{
   int r = c & 0xff, g = (c >> 8) & 0xff, b = (c >> 16) & 0xff;
   r += x; g += x; b += x;
   if (r < 0) r = 0;
   if (g < 0) g = 0;
   if (b < 0) b = 0;
   if (r > 255) r = 255;
   if (g > 255) g = 255;
   if (b > 255) b = 255;
   int R = 0;
   R += r;
   R |= g << 8;
   R |= b << 16;
   return R;
}
int cmp(char *a, char *b)
{
 if (!a) return a == b;
 if (!b) return 1;
 while (*a == *b && *a && *b) { a++; b++; };
 if (*a == *b && *a == 0) return 1;
 return 0;
}
int len(char *c)
{
   int R = 0;
   while (*c++) R++;
   return R;
}
int len(wchar_t *c)
{
  int l = 0;
  if (c == 0) return 0;
  while (*c++)
     l++;
  return l;
}
int toint(char* digit)
{
   int result = 0;
   if (digit == 0) return 0;
   while (*digit >= '0' && *digit <= '9')
   {
      result = (result * 10) + (*digit - '0');
      digit++;
   }
   if (*digit != 0) { return 0; }
   return result;
}
u64 toint64(char* digit)
{
   u64 result = 0;
   if (digit == 0) return 0;
   while (*digit >= '0' && *digit <= '9')
   {
      result = (result * 10) + (*digit - '0');
      digit++;
   }
   if (*digit != 0) { return 0; }
   return result;
}
double dbl(char *S, int c)
{
   if (c == 0) return 0;
   double T = 1, P = 1;
   bool dot = false;
   char N[12], X[12];
   int n = 0, x = 0;
   for (int p = 0; p < c; p++)
   {
      if (S[p] == '-') P = -P;
      else if (S[p] == '.') dot = true;
      else if (S[p] >= '0' && S[p] <= '9')
      {
         if (dot) X[x++] = S[p]; else N[n++] = S[p];
      }
   }
   N[n++] = 0; X[x++] = 0;
   for (int i = 1; i < x; i++) T /= 10;
   return (toint(N) + (T * toint(X))) * P;
}
void tostr(char *s, unsigned int i)
{
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
void tostr(char *s, u64 i)
{
   char *c = s;
   while (true)
   {
      u64 i10 = i / 10;
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
void tostr(char *s, int i)
{
   if (i < 0)
   {
      *s++ = '-';
      tostr(s, (unsigned int)-i);
   }
   else
     tostr(s, (unsigned int)i);
}
void tostr(char *s, double d)
{
   if (d < 0)
   {
      *s++ = '-';
      if ((int) (d * 100) != 0)
      tostr(s, -d);
      else *s++ = '0', *s++ = 0;
   }
   else
   {
      char z = ' ';
      tostr(s, (int)d);
      s += len(s);
      *s++ = '.';
      int N = 2;
      unsigned int Q = 1;
      while (N-- > 0) Q *= 10;
      double D = (d - (int)d) * Q;
      unsigned int n = ((D - (int)D) >= 0.5) ? (unsigned)D + 1 : (unsigned)D;
      if (n == Q) n--;
      if (n < 10) *s++ = '0';
      tostr(s, n);
      if (z != ' ')
      {
         while (*s != 0) s++;
         *s++ = z;
         *s++ = 0;
      }
   }
}
void tostr2(char *s, double d)
{
   if (d < 0)
   {
      *s++ = '-';
      if ((int) (d * 100) != 0)
      tostr(s, -d);
      else *s++ = '0', *s++ = 0;
   }
   else
   {
      char z = ' ';
      if (d > 1000000)
      {
         d /= 1000000, z = 'M';
         if (d > 1000) d /= 1000, z = 'G';
         if (d > 1000) d /= 1000, z = 'T';
         if (d > 1000) d /= 1000, z = 'P';
         if (d > 1000) d /= 1000, z = 'E';
         if (d > 1000) d /= 1000, z = 'Z';
         if (d > 1000) d /= 1000, z = 'Y';
         if (d > 1000) d /= 1000, z = 'Q';
      }
      tostr(s, (int)d);
      s += len(s);
      *s++ = '.';
      int N = 2;
      unsigned int Q = 1;
      while (N-- > 0) Q *= 10;
      double D = (d - (int)d) * Q;
      unsigned int n = ((D - (int)D) >= 0.5) ? (unsigned)D + 1 : (unsigned)D;
      if (n == Q) n--;
      if (n < 10) *s++ = '0';
      tostr(s, n);
      if (z != ' ')
      {
         while (*s != 0) s++;
         *s++ = z;
         *s++ = 0;
      }
   }
}
int length(char *s){ return len(s);};
template <typename T> void lowercase(T *p)
{
  while (*p)
  {
     if (*p >= 'A' && *p <= 'Z') *p += ('a' - 'A');
     p++;
  }
}
void uppercase(char *p)
{
  while (*p)
  {
    if (*p >= 'a' && *p <= 'z') *p -= ('a' - 'A');
    p++;
  }
}
void lowerrus(unsigned char *p)
{
  while (*p)
  {
     if (*p >= 'A' && *p <= 'Z') *p += ('a' - 'A');
     if (*p >= 192 && *p <= 223) *p += (224 - 192);
     p++;
  }
}
  byte ticks_bits[3] = { 0x0F, 0x31, 0xC3};
  u64 ( * ticks ) () = (u64 (*) ()) & ticks_bits;
extern "C" {
//  void * malloc(int);
//  int printf(char*, ...);
  void free(void *ptr);
  void exit(int status);
}
typedef unsigned char byte;
float _sqrt (float number)
{
   long i;
   float f = 1.5, x = number/2, y = number;
   i = * ( unsigned long * ) &y;
   i = 0x5f3759df - ( i >> 1 );
   y = * ( float * ) &i;
   y = y * (f - x*y*y);
   return number * y;
}
void deletefile(char *n)
{
 using namespace unixstuff;
 FILE *f;
 f = fopen(n, "wb");
 fclose(f);
}
bool fileexists(char *name)
{
 using namespace unixstuff;
 FILE *f = fopen(name, "rb");
 bool b = f != 0;
 if (b) fclose(f);
 return b;
}
void appendfile(char *filename, void *data, int size)
{
 using namespace unixstuff;
   FILE *f;
   if (fileexists(filename))
   {
     f = fopen(filename, "r+b");
   }
   else
   {
     f = fopen(filename, "wb");
   }
   fseek(f, 0, 2);
   fwrite(data, 1, size, f);
   fclose(f);
}
int filesize(char *n)
{
 using namespace unixstuff;
 FILE *f;
 f = fopen(n, "rb");
 if (f)
 {
 fseek(f, 0, 2);
 int t;
 t = ftell(f);
 fseek(f, 0, 0);
 fclose(f);
 return t;
 } else return 0;
}
int load(char *filename, char *s, int size)
{
 using namespace unixstuff;
  FILE *f;
  f = fopen(filename, "r");
  if (f != 0)
  {
    int l = fread(s, 1, size, f);
    fclose(f);
    return l;
  }
  else
  {
     size = 0;
     *s = 0;
     return 0;
  }
}
struct wc
{
  word code;
  word c;
wc()
{
  c = 0;
}
wc(word w)
{
  c = 0; code = w;
}
wchar_t * operator * ()
{
  return (wchar_t *) this;
}
};
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
wchar_t to_unicode(char c)
{
   int q = c & 0xff;
   word w = 0;
   w += c;
   char A = 0xC0;
   char a = 0xE0;
   char YA = 0xDF;
   char ya = 0xFF;
   if (c >= A && c <= YA) w += 0x0410 - A;
   if (c >= a && c <= ya) w += 0x0410 - A;
   if (q == 184) w = 0x0451;
   else if (q == 0x97) w = 0x2014;
   else if (q == 0xAB) w = 0xAB;
   else if (q == 0xBB) w = 0xBB;
   else if (q == 0x91) w = 0x5C;
   else if (q == 0x92) w = 0x5C;
   else if (q == 0x84) w = '"';
   else if (q == 0x93) w = '"';
   else if (q == 0x85) w = 0x2026;
   return w;
}
char to_ascii(wchar_t w)
{
   char c;
   char a = 0xE0;
   if (w >= 0x0410)
   c = (char) w - (0x0410 - a);
   else if (w == 0x0451) c = 184;
   else if (w == 0x2014) c = 0x97;
   else c = w & 0xff;
   return c;
}
struct str;
struct str
{
  struct strptr { char *p; int count, size, capacity; };
  strptr *p;
  str ();
  str (const str &s);
  str (const char *s);
  str (char ch);
  str (wchar_t *s);
  str (wchar_t ch);
  str (int i);
  str (unsigned int i);
  str (double i);
 ~str ();
  void operator = (const str&);
  str operator + (str s);
  str operator + (char *s);
  str operator + (char ch);
  str operator + (wchar_t *s);
  str operator + (wchar_t ch);
  str operator + (int i);
  str & operator / (str s);
  str & operator << (str s);
  str & operator << (word w);
  str & operator << (byte b);
  str & operator << (int i);
  str & operator << (float f);
  str & operator << (double w);
  bool operator == (str s);
  bool operator != (str s);
  int cmp(str s);
  bool operator < (str s);
  bool operator > (str s);
  bool operator <= (str s);
  bool operator >= (str s);
  u64 operator ~ ();
  int operator ! ();
  char *operator * ();
  inline char &operator [] (int i);
  str &operator () (int i);
  str &operator () (char *s, int i);
  int operator += (int i);
  void del(int x, int c);
  void ins(str sub, int x);
  void ins(char *sub, int x);
  void ins(char sub, int x);
  void init();
  void unref();
  void copy();
  void resize(int newsize);
  void alloc(int x);
  str add(void *p, int i);
  int pos(char *c);
  int pos(str s);
  int pos(char c);
  int find(int start, char *c, int subsize);
  int strcount(str substring);
  int replace(str old, str _new, int start = 0,
       void *callback = 0, int count = -1);
  int high();
  void fill(char c);
  int charsize() { return 1; }
  void save(char *filename);
  void save(str filename);
  void append(str filename);
  str *ptr();
  str compat();
  str sub(int pos, int count);
  int occu();
  void attach(char *c, int size = -1);
  str binary();
  void binary(str b);
  int& geti(int i);
  word& getw(int i);
  str upper();
  str lower();
};
str :: str()
{
  init();
}
str :: str (const str &s)
{
  p = s.p;
  if (p != 0) p->count++;
}
str :: str (const char *s)
{
  init();
  resize(len((char*)s));
  move((char*)s, p->p, !(*this));
}
str :: str (char ch)
{
  init();
  resize(1);
  ((*this))[0] = ch;
}
str :: str (int i)
{
  init();
  str s = "           ";
  tostr(*s, i);
  s(len(*s));
  (*this) = s;
}
str :: str (unsigned int i)
{
  init();
  str s = "           ";
  tostr(*s, i);
  s(len(*s));
  (*this) = s;
}
str :: str (double i)
{
   init();
   str s = "                   \0";
   tostr(*s, i);
   s(len(*s));
   (*this) = s;
}
str :: str (wchar_t *s)
{
   init();
   (*this)(len(s));
   for (int x = 0; x < !(*this); x++)
     (*this)[x] = to_ascii(*s++);
}
str :: str (wchar_t c)
{
   init();
   (*this)(1);
   (*this)[0] = c;
}
str :: ~str()
{
  unref();
}
void str :: alloc(int x)
{
   if (x > !(*this))
   {
      int o = !(*this);
      (*this)(x);
      p->size = o;
      p->p[p->size] = 0;
   }
}
void str :: resize(int newsize)
{
   copy();
   if (newsize > 0)
   {
      if (p == 0) init();
      if (p->capacity < newsize + 1)
      {
         p->capacity = newsize * 2 + 1;
         char * p_old = p->p;
         char * P = new char[p->capacity];
         p->p = P;
         if (p_old)
         {
            move(p_old, p->p, p->size);
            delete p_old;
         }
      }
      p->size = newsize;
      p->p[p->size] = 0;
   }
   else if (!(*this) > 0)
   {
      delete p->p;
      p->p = 0;
      p->size = 0;
      unref();
   }
}
void str :: init()
{
   p = new strptr;
   p->p = 0;
   p->count = 1;
   p->size = 0;
   p->capacity = 0;
}
void str :: copy()
{
   if (p && p->count > 1)
   {
      p->count--;
      strptr *old;
      old = p;
      init();
      resize(old->size);
      int B = (old->size);
      move(old->p, p->p, B);
   }
}
void str :: unref()
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
void str :: operator = (const str &s)
{
  if (p == s.p) return;
  unref();
  if (s.p)
  {
     p = s.p;
     s.p->count++;
  } else
    (*this)(0);
}
str &str :: operator / (str s)
{
  if (!(*this) == 0) (*this) = s;
  else (*this).ins(s, !(*this));
  return (*this);
}
str str :: operator + (str s)
{
  str r = (*this);
  r.ins(s, !r);
  return r;
}
str str :: operator + (char *s)
{
  str r = (*this);
  r.ins(s, !r);
  return r;
}
str str :: operator + (char ch)
{
  str r = (*this);
  r.ins(ch, !r);
  return r;
}
str str :: operator + (int i)
{
  str r = i;
  r.ins((*this), 0);
  return r;
}
bool str :: operator == (str s)
{
  if (!s != !(*this)) return false;
  if (!s == !(*this) && !s == 0) return true;
  if (!s == 0) return false;
  int i = -1;
  char *a = *(*this), *b = *s;
  while (i++ < p->size)
  {
    if (*a++ != *b++) return false;
  }
  return true;
}
bool str :: operator != (str s)
{
   return !((*this) == s);
}
int str :: cmp (str s)
{
   if (!(*this) == 0 && !s == 0) return 0;
   if (!(*this) == 0) return -1;
   if (!s == 0) return 1;
   char *a, *b, *ea, *eb;
   a = *(*this); b = *s;
   ea = a + !(*this);
   eb = b + !s;
   while(true)
   {
      char A = *a, B = *b;
      A = up_char(A);
      B = up_char(B);
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
   if (!(*this) < !s) return -1;
   if (!(*this) > !s) return 1;
   return 0;
}
bool str :: operator < (str s)
{
   return (*this).cmp(s) == -1;
}
bool str :: operator > (str s)
{
   return (*this).cmp(s) == 1;
}
bool str :: operator <= (str s)
{
   return (*this).cmp(s) <= 0;
}
bool str :: operator >= (str s)
{
   return (*this).cmp(s) >= 0;
}
u64 str :: operator ~ ()
{
   str &s = (*this);
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
void str :: ins (str sub, int x)
{
  if (!sub == 0) return;
  copy();
  int oldsize;
  if (p != 0) oldsize = p->size; else oldsize = 0;
  (*this)(!(*this) + !sub);
  int c = (oldsize - x);
  if (c > 0)
  {
     char *a, *b;
     a = &p->p[p->size - 1];
     b = &p->p[oldsize - 1];
     while (c--)
     {
       *a-- = *b;
       if (c) b--;
     }
  }
  move(*sub, p->p + x, !sub);
}
str &str :: operator ()(int i)
{
  resize(i);
  return (*this);
}
str &str :: operator () (char *s, int i)
{
   (*this)(i);
   move(s, *(*this), i);
   return (*this);
}
int str :: operator += (int i)
{
  int r = !(*this);
  if (i < 0) { i = -i; }
  else r += i;
  (*this)(!(*this) + i);
  return r;
}
int str :: operator ! ()
{
  if (p == 0) return 0;
  return p->size;
}
char * str :: operator * ()
{
   if (p == 0 || p->p == 0)
     return (char*) str_no_null;
   return p->p;
}
char& str :: operator [](int i)
{
   copy();
   if (i < 0) i = !(*this) + i;
   if (p == 0) { (*this)(i); }
   return p->p[i];
}
void str :: del(int x, int c)
{
   if (x >= !(*this)) return;
   if (c > !(*this) - x) c = !(*this) - x;
   copy();
   int newsize = !(*this) - c;
   char *a, *b;
   a = &p->p[x];
   b = &p->p[x + c];
   c = (!(*this) - x) - c;
   while (c--){ *a++ = *b++; }
   resize(newsize);
}
void str :: ins (char *sub, int x)
{
  str tmp(sub);
  ins(tmp, x);
}
void str :: ins (char sub, int x)
{
  str tmp(sub);
  ins(tmp, x);
}
int str :: pos (char *c)
{
 return find(0, c, len(c));
}
int str :: pos (str s)
{
 return find(0, *s, !s);
}
int str :: pos (char c)
{
 return find(0, &c, 1);
}
int str :: find (int start, char *c, int subsize)
{
  if (subsize == 0) return -1;
  int e = subsize;
  int l = start + e;
  int i = l - 1;
  while (i < !(*this))
    if (p->p[i] != c[e - 1]) i++;
    else {
      int x = e;
      char *a = &p->p[i], *b = &c[e - 1];
      while (x--)
      {
        if (*a != *b) { i++; break; }
        if (x > 0) { a--; b--; }
      }
      if (x < 0) return i - e + 1;
    }
  return -1;
}
int str :: strcount(str substring)
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
int str :: replace(
  str old, str _new, int start,
  void *callback, int count
  )
{
 int subcount, len, si, di, x;
 str dest;
 if ((!old == 0) || (!(*this) == 0)) return 0;
 int result = 0;
 if (!_new == 0)
  {
  }
 subcount = strcount(old);
 dest(!(*this) + subcount * (!_new - !old));
 if (!dest <= 0) dest(!(*this));
 si = start;
 di = si;
 move(&((*this))[0], &dest[0], si);
 while (true)
 {
  x = (*this).find(si, *old, !old);
  if ((x < 0) || ((count != -1) && (result == count)))
  {
    len = !(*this) - si;
    if (len > 0) move(&(((*this))[si]), &(dest[di]), len);
    dest(di + len);
    (*this) = dest;
    return result;
  }
  else len = x - si;
  if (len > 0) move(&(((*this))[si]), &(dest[di]), len);
  di = di + len;
  if (!_new > 0) move(&(*_new)[0], &(*dest)[di], !_new);
  si = x + !old;
  di = di + !_new;
  result ++;
 }
}
int str :: high() { return !(*this) - 1; }
void str :: fill(char c)
{
   copy();
   if (!(*this)) fillchar(this->p->p, !(*this), c);
}
void str :: save(char *filename)
{
   deletefile(filename);
   appendfile(filename, *(*this), !(*this));
}
void str :: save(str filename)
{
  save(*filename);
}
str str :: sub(int pos, int count = 1)
{
   str s;
   if (count > !(*this) - pos) count = !(*this) - pos;
   s(count);
   if (count > 0)
     move(&( ((*this))[pos] ), *s, count);
   return s;
}
str * str :: ptr()
{
   return this;
}
int str :: occu()
{
   return (!(*this) + 1) * charsize();
}
str str :: compat()
{
    return (*this);
}
void str :: append(str filename)
{
  appendfile(*filename, *(*this), !(*this));
}
str &str :: operator << (str s)
{
   int u = !(*this);
   (*this)(u + 4 + !s);
   int i = !s;
   move(&i, & (*this)[u], 4);
   move(*s, & (*this)[u + 4], !s);
   return (*this);
}
str &str :: operator << (byte b)
{
   int u = !(*this);
   (*this)(u + 1);
   * (word * )(& (*this)[u]) = b;
   return (*this);
}
str &str :: operator << (word w)
{
   int u = !(*this);
   (*this)(u + 2);
   * (word * )(& (*this)[u]) = w;
   return (*this);
}
str &str :: operator << (int i)
{
   int u = !(*this);
   (*this)(u + 4);
   * (int * )(& (*this)[u]) = i;
   return (*this);
}
str &str :: operator << (double w)
{
   int u = !(*this);
   (*this)(u + sizeof w);
   * (double * )(& (*this)[u]) = w;
   return (*this);
}
str &str :: operator << (float f)
{
   int u = !(*this);
   (*this)(u + sizeof f);
   * (float * )(& (*this)[u]) = f;
   return (*this);
}
str str :: add(void *p, int i)
{
   int u = !(*this);
   (*this)(u + 4 + i);
   move(&i, & (*this)[u], 4);
   move(p, & (*this)[u + 4], i);
   return (*this);
}
void str::attach(char *c, int size)
{
   (*this)(0);
   p->p = c;
   if (size >= 0)
     p->size = size;
   else
     p->size = len(c);
   p->capacity = p->size;
}
str str :: binary()
{
   return (*this);
}
void str :: binary(str b)
{
   (*this) = b;
}
int& str :: geti(int i)
{
   return *(int*)&p->p[i];
}
word& str :: getw(int i)
{
   return *(word*)&p->p[i];
}
str str :: upper()
{
   str s = (*this);
   for (int x = 0; x < !s; x++)
      if (s[x] >= 'a' && s[x] <= 'z')
         s[x] -= 'a' - 'A';
   return s;
}
str str :: lower()
{
   str s = (*this);
   for (int x = 0; x < !s; x++)
      if (s[x] >= 'A' && s[x] <= 'Z')
         s[x] += 'a' - 'A';
   return s;
}
struct wstr
{
  struct strptr { wchar_t *p; int count, size, capacity; };
  strptr *p;
  wstr ();
  wstr (const wstr &s);
  wstr (char *s);
  wstr (char ch);
  wstr (wchar_t *s);
  wstr (wchar_t ch);
  wstr (int i);
  wstr (unsigned int i);
  wstr (double i);
  wstr (str);
 ~wstr ();
  operator str() { return (*this).compat(); };
  void operator = (const wstr&);
  wstr operator + (wstr s);
  wstr operator + (char *s);
  wstr operator + (char ch);
  wstr operator + (wchar_t *s);
  wstr operator + (wchar_t ch);
  wstr operator + (int i);
  wstr & operator / (wstr s);
  bool operator == (wstr s);
  bool operator != (wstr s);
  int cmp(wstr s);
  bool operator < (wstr s);
  bool operator > (wstr s);
  bool operator <= (wstr s);
  bool operator >= (wstr s);
  u64 operator ~ ();
  int operator ! ();
  wchar_t *operator * ();
  inline wchar_t &operator [] (int i);
  wstr &operator () (int i);
  wstr &operator () (char *s, int i);
  int operator += (int i);
  void del(int x, int c);
  void ins(wstr sub, int x);
  void ins(wchar_t *sub, int x);
  void ins(wchar_t sub, int x);
  void init();
  void unref();
  void copy();
  void resize(int newsize);
  void alloc(int x);
  wstr add(void *p, int i);
  int pos(wchar_t *c);
  int pos(wstr s);
  int pos(wchar_t c);
  int find(int start, wchar_t *c, int subsize);
  int strcount(wstr substring);
  int replace(wstr old, wstr _new, int start = 0,
       void *callback = 0, int count = -1);
  int high();
  void fill(wchar_t c);
  int charsize() { return (1 * 2); }
  void save(char *filename);
  void save(wstr filename);
  void append(str filename);
  wstr *ptr();
  str compat();
  wstr sub(int pos, int count);
  int occu();
  void attach(wchar_t *c, int size = -1);
  str binary();
  void binary(str b);
  int& geti(int i);
  word& getw(int i);
  wstr upper();
  wstr lower();
};
wstr :: wstr()
{
  init();
}
wstr :: wstr (const wstr &s)
{
  p = s.p;
  if (p != 0) p->count++;
}
wstr :: wstr(str s)
{
  init();
  (*this)(!s);
  for (int i = 0; i < !s; i++)
  {
     wchar_t c = s[i];
     c = to_unicode(c);
     p->p[i] = c;
  }
}
wstr :: wstr (char *s)
{
  init();
  resize(len(s));
  for (int x = 0; x < !(*this); x++) (*this)[x] = to_ascii(*s++);
}
wstr :: wstr (char ch)
{
  init();
  resize(1);
  ((*this))[0] = ch;
}
wstr :: wstr (int i)
{
  init();
  str s = "           ";
  tostr(*s, i);
  s(len(*s));
  (*this) = s;
}
wstr :: wstr (unsigned int i)
{
  init();
  str s = "           ";
  tostr(*s, i);
  s(len(*s));
  (*this) = s;
}
wstr :: wstr (double i)
{
   init();
   str s = "                   \0";
   tostr(*s, i);
   s(len(*s));
   (*this) = s;
}
wstr :: wstr (wchar_t *s)
{
   init();
   (*this)(len(s));
   move(s, *(*this), (!(*this) * 2));
}
wstr :: wstr (wchar_t c)
{
   init();
   (*this)(1);
   (*this)[0] = c;
}
wstr :: ~wstr()
{
  unref();
}
void wstr :: alloc(int x)
{
   if (x > !(*this))
   {
      int o = !(*this);
      (*this)(x);
      p->size = o;
      p->p[p->size] = 0;
   }
}
void wstr :: resize(int newsize)
{
   copy();
   if (newsize > 0)
   {
      if (p == 0) init();
      if (p->capacity < newsize + 1)
      {
         p->capacity = newsize * 2 + 1;
         wchar_t * p_old = p->p;
         wchar_t * P = new wchar_t[p->capacity];
         p->p = P;
         if (p_old)
         {
            move(p_old, p->p, (p->size * 2));
            delete p_old;
         }
      }
      p->size = newsize;
      p->p[p->size] = 0;
   }
   else if (!(*this) > 0)
   {
      delete p->p;
      p->p = 0;
      p->size = 0;
      unref();
   }
}
void wstr :: init()
{
   p = new strptr;
   p->p = 0;
   p->count = 1;
   p->size = 0;
   p->capacity = 0;
}
void wstr :: copy()
{
   if (p && p->count > 1)
   {
      p->count--;
      strptr *old;
      old = p;
      init();
      resize(old->size);
      int B = ((old->size * 2));
      move(old->p, p->p, B);
   }
}
void wstr :: unref()
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
void wstr :: operator = (const wstr &s)
{
  if (p == s.p) return;
  unref();
  if (s.p)
  {
     p = s.p;
     s.p->count++;
  } else
    (*this)(0);
}
wstr &wstr :: operator / (wstr s)
{
  if (!(*this) == 0) (*this) = s;
  else (*this).ins(s, !(*this));
  return (*this);
}
wstr wstr :: operator + (wstr s)
{
  wstr r = (*this);
  r.ins(s, !r);
  return r;
}
wstr wstr :: operator + (char *s)
{
  wstr r = (*this);
  r.ins(s, !r);
  return r;
}
wstr wstr :: operator + (char ch)
{
  wstr r = (*this);
  r.ins(ch, !r);
  return r;
}
wstr wstr :: operator + (int i)
{
  wstr r = i;
  r.ins((*this), 0);
  return r;
}
bool wstr :: operator == (wstr s)
{
  if (!s != !(*this)) return false;
  if (!s == !(*this) && !s == 0) return true;
  if (!s == 0) return false;
  int i = -1;
  wchar_t *a = *(*this), *b = *s;
  while (i++ < p->size)
  {
    if (*a++ != *b++) return false;
  }
  return true;
}
bool wstr :: operator != (wstr s)
{
   return !((*this) == s);
}
int wstr :: cmp (wstr s)
{
   if (!(*this) == 0 && !s == 0) return 0;
   if (!(*this) == 0) return -1;
   if (!s == 0) return 1;
   wchar_t *a, *b, *ea, *eb;
   a = *(*this); b = *s;
   ea = a + !(*this);
   eb = b + !s;
   while(true)
   {
      wchar_t A = *a, B = *b;
      A = up_char(A);
      B = up_char(B);
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
   if (!(*this) < !s) return -1;
   if (!(*this) > !s) return 1;
   return 0;
}
bool wstr :: operator < (wstr s)
{
   return (*this).cmp(s) == -1;
}
bool wstr :: operator > (wstr s)
{
   return (*this).cmp(s) == 1;
}
bool wstr :: operator <= (wstr s)
{
   return (*this).cmp(s) <= 0;
}
bool wstr :: operator >= (wstr s)
{
   return (*this).cmp(s) >= 0;
}
u64 wstr :: operator ~ ()
{
   str s = (*this).compat();
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
void wstr :: ins (wstr sub, int x)
{
  if (!sub == 0) return;
  copy();
  int oldsize;
  if (p != 0) oldsize = p->size; else oldsize = 0;
  (*this)(!(*this) + !sub);
  int c = (oldsize - x);
  if (c > 0)
  {
     wchar_t *a, *b;
     a = &p->p[p->size - 1];
     b = &p->p[oldsize - 1];
     while (c--)
     {
       *a-- = *b;
       if (c) b--;
     }
  }
  move(*sub, p->p + x, (!sub * 2));
}
wstr &wstr :: operator ()(int i)
{
  resize(i);
  return (*this);
}
wstr &wstr :: operator () (char *s, int i)
{
   (*this)(i);
   move(s, *(*this), i);
   return (*this);
}
int wstr :: operator += (int i)
{
  int r = !(*this);
  if (i < 0) { i = -i; }
  else r += i;
  (*this)(!(*this) + i);
  return r;
}
int wstr :: operator ! ()
{
  if (p == 0) return 0;
  return p->size;
}
wchar_t * wstr :: operator * ()
{
   if (p == 0 || p->p == 0)
     return (wchar_t*) str_no_null;
   return p->p;
}
wchar_t& wstr :: operator [](int i)
{
   copy();
   if (i < 0) i = !(*this) + i;
   if (p == 0) { (*this)(i); }
   return p->p[i];
}
void wstr :: del(int x, int c)
{
   if (x >= !(*this)) return;
   if (c > !(*this) - x) c = !(*this) - x;
   copy();
   int newsize = !(*this) - c;
   wchar_t *a, *b;
   a = &p->p[x];
   b = &p->p[x + c];
   c = (!(*this) - x) - c;
   while (c--){ *a++ = *b++; }
   resize(newsize);
}
void wstr :: ins (wchar_t *sub, int x)
{
  wstr tmp(sub);
  ins(tmp, x);
}
void wstr :: ins (wchar_t sub, int x)
{
  wstr tmp(sub);
  ins(tmp, x);
}
int wstr :: pos (wchar_t *c)
{
 return find(0, c, len(c));
}
int wstr :: pos (wstr s)
{
 return find(0, *s, !s);
}
int wstr :: pos (wchar_t c)
{
 return find(0, &c, 1);
}
int wstr :: find (int start, wchar_t *c, int subsize)
{
  if (subsize == 0) return -1;
  int e = subsize;
  int l = start + e;
  int i = l - 1;
  while (i < !(*this))
    if (p->p[i] != c[e - 1]) i++;
    else {
      int x = e;
      wchar_t *a = &p->p[i], *b = &c[e - 1];
      while (x--)
      {
        if (*a != *b) { i++; break; }
        if (x > 0) { a--; b--; }
      }
      if (x < 0) return i - e + 1;
    }
  return -1;
}
int wstr :: strcount(wstr substring)
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
int wstr :: replace(
  wstr old, wstr _new, int start,
  void *callback, int count
  )
{
 int subcount, len, si, di, x;
 wstr dest;
 if ((!old == 0) || (!(*this) == 0)) return 0;
 int result = 0;
 if (!_new == 0)
  {
  }
 subcount = strcount(old);
 dest(!(*this) + subcount * (!_new - !old));
 if (!dest <= 0) dest(!(*this));
 si = start;
 di = si;
 move(&((*this))[0], &dest[0], (si * 2));
 while (true)
 {
  x = (*this).find(si, *old, !old);
  if ((x < 0) || ((count != -1) && (result == count)))
  {
    len = !(*this) - si;
    if (len > 0) move(&(((*this))[si]), &(dest[di]), (len * 2));
    dest(di + len);
    (*this) = dest;
    return result;
  }
  else len = x - si;
  if (len > 0) move(&(((*this))[si]), &(dest[di]), (len * 2));
  di = di + len;
  if (!_new > 0) move(&(*_new)[0], &(*dest)[di], (!_new * 2));
  si = x + !old;
  di = di + !_new;
  result ++;
 }
}
int wstr :: high() { return !(*this) - 1; }
void wstr :: fill(wchar_t c)
{
   copy();
   for (int i = 0; i < !(*this); i++) (*this)[i] = c;
}
void wstr :: save(char *filename)
{
   deletefile(filename);
   appendfile(filename, *(*this), !(*this));
}
void wstr :: save(wstr filename)
{
  save(*filename);
}
wstr wstr :: sub(int pos, int count = 1)
{
   wstr s;
   if (count > !(*this) - pos) count = !(*this) - pos;
   s(count);
   if (count > 0)
     move(&( ((*this))[pos] ), *s, (count * 2));
   return s;
}
wstr * wstr :: ptr()
{
   return this;
}
int wstr :: occu()
{
   return (!(*this) + 1) * charsize();
}
str wstr :: compat()
{
   str R;
   R(!(*this));
   for (int i = 0; i < !R; i++)
     R[i] = to_ascii((*this)[i]);
   return R;
}
void wstr :: append(str filename)
{
  appendfile(*filename, *(*this), (!(*this) * 2));
}
wstr wstr :: add(void *p, int i)
{
   int u = !(*this);
   (*this)(u + 4 + i);
   move(&i, & (*this)[u], 4);
   move(p, & (*this)[u + 4], i);
   return (*this);
}
void wstr::attach(wchar_t *c, int size)
{
   (*this)(0);
   p->p = c;
   if (size >= 0)
     p->size = size;
   else
     p->size = len(c);
   p->capacity = p->size;
}
str wstr :: binary()
{
   str r;
   r((!(*this) * 2));
   move(*(*this), *r, !r);
   return r;
}
void wstr :: binary(str b)
{
   (*this)(!b / 2);
   move(*b, *(*this), !(*this) * 2);
}
int& wstr :: geti(int i)
{
   return *(int*)&p->p[i];
}
word& wstr :: getw(int i)
{
   return *(word*)&p->p[i];
}
wstr wstr :: upper()
{
   wstr s = (*this);
   for (int x = 0; x < !s; x++)
      if (s[x] >= 'a' && s[x] <= 'z')
         s[x] -= 'a' - 'A';
   return s;
}
wstr wstr :: lower()
{
   wstr s = (*this);
   for (int x = 0; x < !s; x++)
      if (s[x] >= 'A' && s[x] <= 'Z')
         s[x] += 'a' - 'A';
   return s;
}
  typedef str Str;
  typedef char Char;
str load(str name)
{
   str R;
   R(filesize(*name));
   if (!R > 0)
     load(*name, *R, !R);
   return R;
}
wstr wload(str name)
{
   str s = load(name);
   wstr R;
   R.binary(s);
   if (!R > 2)
   if (R[0] == 0xfeff) R.del(0, 1);
   return R;
}
void wtrim(wstr &w)
{
   int a = 0, b = 0;
   for (int x = 0; x < !w; x++) if (w[x] == ' ') a++; else break;
   for (int x1 = !w - 1; x1 > a; x1--)
     if (w[x1] == ' ') b++; else break;
   int l = !w - a - b;
   move(& w[a], *w, l * 2);
   w(l);
}
int wstr_cmp(wstr &A, wstr &B)
{
   if (!A == 0) return 2;
   if (!B == 0) return 3;
   wchar_t *a = *A, *b = *B, *alast = &A.p->p[!A - 1], *blast = &B.p->p[!B - 1];
   while (true)
   {
      if (a > alast)
      {
         if (b > blast) return 0;
         return 1;
      }
      if (b > blast) return -1;
      if (*a < *b) return 1;
      if (*a > *b) return -1;
      a++; b++;
   }
}
template <typename T>void trim(T &s)
{
   if (!s == 0) return;
   int a = 0, b = 0;
   for (int x = 0; x < !s; x++)
     if (s[x] == ' ' && s[x] > 5) a++; else break;
   if (a == !s)
   {
      s(0);
      return;
   }
   for (int x1 = !s - 1; x1 > a; x1--)
     if (s[x1] <= ' ' && s[x1] > 5)
       b++;
         else break;
   s.del(0, a);
   s(!s - b);
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
void quick_hex(byte b, char *&dest)
{
    char c;
    byte B;
    B = (b >> 4) & 0xF;
    if (B <= 9) c = B + '0'; else c = B - 10 + 'A'; *dest++ = c;
    B = b & 0xF;
    if (B <= 9) c = B + '0'; else c = B - 10 + 'A'; *dest++ = c;
}
str hex_dump(str src)
{
   str d;
   d(!src * 2);
   char *w = *d, *a = *src, *e = a + !src;
   while (a < e)
     quick_hex(*a++, w);
   return d;
}
str hex_undump(str src)
{
   str d;
   static str hash;
   if (!hash == 0)
   {
      hash(256);
      hash.fill(100);
      for (int a = '0'; a <= '9'; a++) hash[a] = a - '0';
      for (int b = 'a'; b <= 'f'; b++) hash[b] = b - 'a' + 10;
      for (int c = 'A'; c <= 'F'; c++) hash[c] = c - 'A' + 10;
   }
   d(!src / 2);
   char *w = *d, *a = *src, *e = a + !src;
   char* p = hash.p->p;
   while (a < e)
   {
      byte A, B;
      while(true) { A = p[*a++]; if (A != 100 || a >= e) break; }
      while(true) { B = p[*a++]; if (B != 100 || a >= e) break; }
      if (a > e) break;
      *w++ = (A << 4) + B;
   }
   d(w - *d);
   return d;
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
byte hexhalf(char *s)
{
   byte c = 0;
   if (*s >= '0' && *s <= '9') c = *s - '0';
   else if (*s >= 'a' && *s <= 'f') c = *s - 'a' + 10;
   else if (*s >= 'A' && *s <= 'F') c = *s - 'A' + 10;
   return c;
}
byte hex1(char *s)
{
  byte R = 0;
  byte c;
  c = hexhalf(s);
  R |= c;
  R <<= 4;
  s++;
  c = hexhalf(s);
  R |= c;
  return R;
}
word hex2(char *s)
{
   return (hex1(& s[0]) << 4) | hex1(& s[1]);
}
int backpos(str s, char sub)
{
   for (int i = !s - 1; i >= 0; i--)
   {
     if (s[i] == sub) return i;
   }
   return -1;
}
str fileext(str s)
{
   int i = backpos(s, '.');
   if (i > 0)
   {
      s.del(0, i + 1);
   }
   else s = "";
   for (i = 0; i < !s; i++)
     if (s[i] >= 'A' && s[i] <= 'Z') s[i] += 'a' - 'A';
   return s;
}
int ord(char c)
{
   return c & 0xff;
}
template <typename T>
T bite_t(T &s, T separator)
{
   T R;
   int i = s.pos(separator);
   if (i < 0)
   {
      R = s;
      s(0);
   }
   else
   {
      R(i);
      if (!R > 0)
      {
         move(*s, *R, !R * R.charsize());
      }
      s.del(0, i + !separator);
   }
   return R;
}
str bite(str &s, str separator)
{
   return bite_t(s, separator);
}
wstr bite(wstr &s, wstr separator)
{
   return bite_t(s, separator);
}
wstr wbite(wstr &s, wstr separator)
{
   return bite_t(s, separator);
}
int earlier(str s, str a, str b)
{
   int A = s.pos(a), B = s.pos(b);
   if (A < 0)
   {
      if (B < 0) return -1;
      return 1;
   }
   if (B < 0 || A < B) return 0;
   return 1;
}
str tostr(int i4)
{
   str s = i4;
   return s;
}
double dbl(str s)
{
   if (!s == 0) return 0;
   double T = 1, P = 1;
   bool dot = false;
   str N, X; int n = 0, x = 0; N(!s); X(!s);
   for (int p = 0; p < !s; p++)
   {
      if (s[p] == '-') P = -P;
      else if (s[p] == '.') dot = true;
      else if (s[p] >= '0' && s[p] <= '9')
      {
         if (dot) X[x++] = s[p]; else N[n++] = s[p];
      }
   }
   N(n); X(x);
   for (int i = 0; i < !X; i++) T /= 10;
   return (~N + (T * ~X)) * P;
}
int toint(str digit)
{
   return toint(*digit);
}
template <typename T>
void invert(T &s)
{
  int a = 0, b = !s - 1, e = !s;
  s(!s + 1);
  while (a <= b)
  {
     s[e] = s[a];
     s[a] = s[b];
     s[b] = s[e];
     a++; b--;
  }
  s(!s - 1);
}
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
void operator = (const list &n)
{
   assign(n);
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
   return (*this)[0];
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
  if (p) move32(p, n, min(size, newsize) * sizeof(T*)/4);
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
int operator ! ()
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
int operator~()
{
   return size - 1;
}
T& operator [](int i)
{
  if (i < 0) i = size + i;
  if (p[i] == 0) p[i] = new T();
  return (*p[i]);
}
list<T>& operator << (T item)
{
  resize(size + 1);
  (*this)[size - 1] = item;
  return (*this);
}
list<T>& operator >> (T &item)
{
   resize(size - 1);
   if (size > 0) item = (*this)[-1];
   return (*this);
}
list<T> & operator < (T item)
{
   ins(0, item);
   return (*this);
}
list<T> & operator > (T & item)
{
   item = (*this)[0];
   del(0, 1);
}
T operator --(int)
{
   T t = (*this)[-1];
   resize(size - 1);
   return t;
}
T operator --()
{
   T t = (*this)[0];
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
   for (int i = 0; i < n.size; i++) (*this)[i] = * n.p[i];
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
str dump()
{
  str r;
  for (int i = 0; i < !(*this); i++) r = r + (*this)[i] + ",";
  return r;
}
int find(T &what)
{
   for (int i = 0; i < size; i++)
     if (what == *p[i]) return i;
   return -1;
}
};
typedef list<str> strings;
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
inline int operator ! ()
{
   return size;
}
inline int operator ~ ()
{
   return size - 1;
}
inline void operator () (int i)
{
   resize(i);
}
inline void operator = (arr &n)
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
   (*this)++;
   (*this)[-1] = item;
   return (*this);
}
arr<T> & operator << (arr & S)
{
   int n = !(*this);
   (*this)(n + !S);
   for (int i = 0; i < !S; i++) (*this)[n + i] = S[i];
   return (*this);
}
arr<T> & operator >> (T item)
{
  if (size > 0) item = (*this)[-1];
  (*this)--;
  return (*this);
}
arr<T> & operator < (T item)
{
   ins(0, item);
   return (*this);
}
arr<T> & operator > (T item)
{
   item = (*this)[0];
   del(0, 1);
   return (*this);
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
    result[i] = (*this)[pos + i];
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
   return (*this)[-1];
}
T & operator ++()
{
   T t;
   ins(0, t);
   return (*this)[0];
}
T operator --(int)
{
   T t = (*this)[-1];
   resize(size - 1);
   return t;
}
T operator --()
{
   T t = (*this)[0];
   del(0, 1);
   return t;
}
void operator = (T item)
{
   (*this)[-1] = item;
}
inline T & operator [] (int i)
{
   if (i < 0) i = size + i;
   return p[i];
}
};
typedef arr<int> ints;
ints ints_hidden_variable;
void assign(strings &L, str V, str D)
{
    str s, q;
    int start, stop, i;
    L(V.strcount(D) + 1);
    if (!V == 0) L(0);
    i = 0;
    start = 0;
    while (i < !L)
    {
      stop = V.find(start, *D, !D);
      if (stop < 0) stop = !V;
      s = "";
      s(stop - start);
      if (!s > 0) move(&V[start], *s, !s * s.charsize());
      L[i++] = s;
      start = stop + !D;
    }
}
str join(strings &L, str D)
{
   str r;
   if (!L == 0) return r;
   int m = 0, u, W = L[0].charsize();
   for (int i = 0; i < !L; i++)
     m += !L[i];
   m += (!L - 1) * !D;
   r.resize(m);
   u = 0;
   for (int j = 0; j < !L; j++)
   {
      if (!L[j] > 0) move(&L[j][0], &r[u], !L[j] * W);
      u += !L[j];
      if (j < !L - 1)
      {
         if (!D > 0) move(&D[0], &r[u], !D* W);
         u += !D * W;
      }
   }
   return r;
}
void assign_text(strings &l, str s)
{
   str crlf;
   int a = -1;
   for (int i = 0; i < !s; i++)
   {
       if (s[i] == '\r' || s[i] == '\n') { crlf / s[i]; }
       if (a >= 0) break;
       if (!crlf == 2) break;
       if (!crlf > 0) a = i;
   }
   if (!crlf > 0)
     assign(l, s, crlf); else { l(0); l << s; }
}
void assign(list<wstr> &L, wstr V, wstr D)
{
    wstr s, q;
    int start, stop, i;
    L(V.strcount(D) + 1);
    if (!V == 0) L(0);
    i = 0;
    start = 0;
    while (i < !L)
    {
      stop = V.find(start, *D, !D);
      if (stop < 0) stop = !V;
      s = (char*)"";
      s(stop - start);
      if (!s > 0) move(&V[start], &s[0], !s * s.charsize());
      L[i++] = s;
      start = stop + !D;
    }
}
wstr join(list<wstr> &L, wstr D)
{
   wstr r;
   if (!L == 0) return r;
   int m = 0, u, W = L[0].charsize();
   for (int i = 0; i < !L; i++) m += !L[i];
   m += (!L - 1) * !D;
   r.resize(m);
   u = 0;
   for (int j = 0; j < !L; j++)
   {
      int x = !L[j] * W;
      if (x) move(& L[j][0], & r[u], x);
      u += !L[j];
      if (j < !L - 1)
      {
         move(&D[0], &r[u], !D * W);
         u += !D;
      }
   }
   return r;
}
void assign_text(list<wstr> &L, wstr w)
{
    L(0);
    if (!w == 0) return;
    wchar_t *e = &w[-1], *a = *w, *b = a;
    while(true)
    {
       if (a > e)
       {
           wstr t;
           t(a - b);
           move(b, *t, !t * 2);
           L << t;
           break;
       }
       if (*a == 10 || *a == 13)
       {
          wstr t;
          t(a - b);
          move(b, *t, !t * 2);
          L << t;
          if (a < e && (a[0] == 13 && a[1] == 10)) a++;
          a++;
          b = a;
          continue;
       }
       a++;
    }
}
void assign_text_old(list<wstr> &l, wstr w)
{
   wstr crlf;
   int a = -1;
   for (int i = 0; i < !w; i++)
   {
       if (w[i] == L'\n' && !crlf == 1 && crlf[0] == L'\n') break;
       if (w[i] == L'\r' || w[i] == L'\n')
       {
          crlf / w[i];
       }
       if (a >= 0) break;
       if (!crlf == 2) break;
       if (!crlf > 0) a = i;
   }
   if (!crlf > 0)
     assign(l, w, crlf); else { l(0); l << w; }
}
void destring(str &s, char str_char, bool direction)
{
   static strings L;
   if (direction)
   {
      L(0);
      int a = 0;
      str t;
      bool q = false;
      for (int i = 0; i < !s; i++)
      {
         if (s[i] == str_char)
         {
            q = !q;
            if (q)
            {
                t / s.sub(a, i - a) / (char) 1;
                a = i;
            }
            else
            {
                L << s.sub(a, i - a + 1);
                a = i + 1;
            }
            continue;
         }
      }
      t / s.sub(a, !s - a);
      s = t;
   }
   else
   {
	for (int l = 0; l < !L; l++)
      s.replace((char)1, L[l], 0, 0, 1);
   }
}

