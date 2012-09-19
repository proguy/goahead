/*
    goahead.h -- GoAhead Web Server Header
  
    Copyright (c) All Rights Reserved. See details at the end of the file.
 */

#ifndef _h_GOAHEAD
#define _h_GOAHEAD 1

/************************************ Defaults ********************************/

#include    "bit.h"

#ifndef BIT_DEBUG
    #define BIT_DEBUG 0
#endif
#ifndef BIT_ASSERT
    #if BIT_DEBUG
        #define BIT_ASSERT 1
    #else
        #define BIT_ASSERT 0
    #endif
#endif
#ifndef BIT_FLOAT
    #define BIT_FLOAT 1
#endif
#ifndef BIT_ROM
    #define BIT_ROM 0
#endif

/********************************* CPU Families *******************************/
/*
    CPU Architectures
 */
#define BIT_CPU_UNKNOWN     0
#define BIT_CPU_ARM         1           /* Arm */
#define BIT_CPU_ITANIUM     2           /* Intel Itanium */
#define BIT_CPU_X86         3           /* X86 */
#define BIT_CPU_X64         4           /* AMD64 or EMT64 */
#define BIT_CPU_MIPS        5           /* Mips */
#define BIT_CPU_PPC         6           /* Power PC */
#define BIT_CPU_SPARC       7           /* Sparc */

/*
    Use compiler definitions to determine the CPU
 */
#if defined(__alpha__)
    #define BIT_CPU "ALPHA"
    #define BIT_CPU_ARCH BIT_CPU_ALPHA
#elif defined(__arm__)
    #define BIT_CPU "ARM"
    #define BIT_CPU_ARCH BIT_CPU_ARM
#elif defined(__x86_64__) || defined(_M_AMD64)
    #define BIT_CPU "x64"
    #define BIT_CPU_ARCH BIT_CPU_X64
#elif defined(__i386__) || defined(__i486__) || defined(__i585__) || defined(__i686__) || defined(_M_IX86)
    #define BIT_CPU "x86"
    #define BIT_CPU_ARCH BIT_CPU_X86
#elif defined(_M_IA64)
    #define BIT_CPU "IA64"
    #define BIT_CPU_ARCH BIT_CPU_ITANIUM
#elif defined(__mips__)
    #define BIT_CPU "MIPS"
    #define BIT_CPU_ARCH BIT_CPU_SPARC
#elif defined(__ppc__) || defined(__powerpc__) || defined(__ppc64__)
    #define BIT_CPU "PPC"
    #define BIT_CPU_ARCH BIT_CPU_PPC
#elif defined(__sparc__)
    #define BIT_CPU "SPARC"
    #define BIT_CPU_ARCH BIT_CPU_SPARC
#endif

/*
    Operating system defines. Use compiler standard defintions to sleuth.  Works for all except VxWorks which does not
    define any special symbol.  NOTE: Support for SCOV Unix, LynxOS and UnixWare is deprecated. 
 */
#if defined(__APPLE__)
    #define BIT_OS "macosx"
    #define MACOSX 1
    #define BIT_UNIX_LIKE 1
    #define BIT_WIN_LIKE 0
#elif defined(__linux__)
    #define BIT_OS "linux"
    #define LINUX 1
    #define BIT_UNIX_LIKE 1
    #define BIT_WIN_LIKE 0
#elif defined(__FreeBSD__)
    #define BIT_OS "freebsd"
    #define FREEBSD 1
    #define BIT_UNIX_LIKE 1
    #define BIT_WIN_LIKE 0
#elif defined(_WIN32)
    #define BIT_OS "windows"
    #define WINDOWS 1
    #define BIT_UNIX_LIKE 0
    #define BIT_WIN_LIKE 1
#elif defined(__OS2__)
    #define BIT_OS "os2"
    #define OS2 0
    #define BIT_UNIX_LIKE 0
    #define BIT_WIN_LIKE 0
#elif defined(MSDOS) || defined(__DOS__)
    #define BIT_OS "msdos"
    #define WINDOWS 0
    #define BIT_UNIX_LIKE 0
    #define BIT_WIN_LIKE 0
#elif defined(__NETWARE_386__)
    #define BIT_OS "netware"
    #define NETWARE 0
    #define BIT_UNIX_LIKE 0
    #define BIT_WIN_LIKE 0
#elif defined(__bsdi__)
    #define BIT_OS "bsdi"
    #define BSDI 1
    #define BIT_UNIX_LIKE 1
    #define BIT_WIN_LIKE 0
#elif defined(__NetBSD__)
    #define BIT_OS "netbsd"
    #define NETBSD 1
    #define BIT_UNIX_LIKE 1
    #define BIT_WIN_LIKE 0
#elif defined(__QNX__)
    #define BIT_OS "qnx"
    #define QNX 1
    #define BIT_UNIX_LIKE 0
    #define BIT_WIN_LIKE 0
#elif defined(__hpux)
    #define BIT_OS "hpux"
    #define HPUX 1
    #define BIT_UNIX_LIKE 1
    #define BIT_WIN_LIKE 0
#elif defined(_AIX)
    #define BIT_OS "aix"
    #define AIX 1
    #define BIT_UNIX_LIKE 1
    #define BIT_WIN_LIKE 0
#elif defined(__CYGWIN__)
    #define BIT_OS "cygwin"
    #define CYGWIN 1
    #define BIT_UNIX_LIKE 1
    #define BIT_WIN_LIKE 0
#elif defined(__VMS)
    #define BIT_OS "vms"
    #define VMS 1
    #define BIT_UNIX_LIKE 0
    #define BIT_WIN_LIKE 0
#elif defined(VXWORKS)
    /* VxWorks does not have a pre-defined symbol */
    #define BIT_OS "vxworks"
    #define BIT_UNIX_LIKE 0
    #define BIT_WIN_LIKE 0
#elif defined(ECOS)
    /* ECOS may not have a pre-defined symbol */
    #define BIT_OS "ecos"
    #define BIT_UNIX_LIKE 0
    #define BIT_WIN_LIKE 0
#endif

#if __WORDSIZE == 64 || __amd64 || __x86_64 || __x86_64__ || _WIN64
    #define BIT_64 1
    #define BIT_WORDSIZE 64
#else
    #define BIT_WORDSIZE 32
#endif

/*
    Foundational types
 */
#ifndef BIT_CHAR_LEN
    #define BIT_CHAR_LEN 1
    #define UNICODE 0
    typedef short wchar;
#elif BIT_CHAR_LEN == 4
    typedef int32 wchar;
    #define T(s) L ## s
    #define UNICODE 1
#elif BIT_CHAR_LEN == 2
    typedef short wchar;
    #define T(s) L ## s
    #define UNICODE 1
#else
    typedef char wchar;
    #define T(s) s
    #define UNICODE 0
#endif

/********************************* O/S Includes *******************************/
/*
    Out-of-order definitions and includes. Order really matters in this section
 */
#if WINDOWS
    #undef      _CRT_SECURE_NO_DEPRECATE
    #define     _CRT_SECURE_NO_DEPRECATE 1
    #undef      _CRT_SECURE_NO_WARNINGS
    #define     _CRT_SECURE_NO_WARNINGS 1
    #ifndef     _WIN32_WINNT
        #define _WIN32_WINNT 0x501
    #endif
#endif

#if WINDOWS
    #include    <direct.h>
    #include    <io.h>
    #include    <sys/stat.h>
    #include    <limits.h>
    #include    <tchar.h>
    #include    <winsock2.h>
    #include    <windows.h>
    #include    <winnls.h>
    #include    <ws2tcpip.h>
    #include    <time.h>
    #include    <sys/types.h>
    #include    <stdio.h>
    #include    <stdlib.h>
    #include    <fcntl.h>
    #include    <errno.h>
    #include    <share.h>
#endif /* WINDOWS */

#if CE
    /*#include  <errno.h>*/
    #include    <limits.h>
    #include    <tchar.h>
    #include    <windows.h>
    #include    <winsock.h>
    #include    <winnls.h>
    #include    "CE/wincompat.h"
#endif /* CE */

#if NETWARE
    #include    <direct.h>
    #include    <io.h>
    #include    <sys/stat.h>
    #include    <time.h>
    #include    <sys/types.h>
    #include    <stdio.h>
    #include    <stdlib.h>
    #include    <fcntl.h>
    #include    <errno.h>
    #include    <niterror.h>
    #include    <limits.h>
    #include    <netdb.h>
    #include    <process.h>
    #include    <tiuser.h>
    #include    <sys/time.h>
    #include    <arpa/inet.h>
    #include    <sys/types.h>
    #include    <sys/socket.h>
    #include    <sys/filio.h>
    #include    <netinet/in.h>
#endif /* NETWARE */

#if SCOV5 || AIX || HPUX
    #include    <sys/types.h>
    #include    <dirent.h>
    #include    <stdio.h>
    #include    <signal.h>
    #include    <unistd.h>
    #include    "sys/socket.h"
    #include    "sys/select.h"
    #include    "netinet/in.h"
    #include    "arpa/inet.h"
    #include    "netdb.h"
    #include    <syslog.h>
#endif /* SCOV5 || AIX || HUPX */

#if LINUX
    #include    <sys/types.h>
    #include    <sys/stat.h>
    #include    <sys/param.h>
    #include    <dirent.h>
    #include    <limits.h>
    #include    <signal.h>
    #include    <stdio.h>
    #include    <stdlib.h>
    #include    <unistd.h>
    #include    <sys/socket.h>
    #include    <sys/select.h>
    #include    <netinet/in.h>
    #include    <arpa/inet.h>
    #include    <netdb.h>
    #include    <time.h>
    #include    <fcntl.h>
    #include    <grp.h>
    #include    <errno.h>
    #include    <sys/wait.h>
    #include    <syslog.h>
#endif /* LINUX */

#if LYNX
    #include    <dirent.h>
    #include    <limits.h>
    #include    <signal.h>
    #include    <stdarg.h>
    #include    <stdio.h>
    #include    <stdlib.h>
    #include    <unistd.h>
    #include    <socket.h>
    #include    <netinet/in.h>
    #include    <arpa/inet.h>
    #include    <netdb.h>
    #include    <time.h>
    #include    <fcntl.h>
    #include    <errno.h>
    #include    <syslog.h>
#endif /* LYNX */

#if MACOSX
    #include    <dirent.h>
    #include    <limits.h>
    #include    <sys/select.h>
    #include    <sys/types.h>
    #include    <sys/stat.h>
    #include    <stdio.h>
    #include    <stdlib.h>
    #include    <unistd.h>
    #include    <sys/socket.h>
    #include    <netinet/in.h>
    #include    <arpa/inet.h>
    #include    <netdb.h>
    #include    <fcntl.h>
    #include    <errno.h>
    #include    <grp.h>
    #include    <time.h>
    #include    <stdbool.h>
    #include    <sys/wait.h>
    #include    <syslog.h>
#endif /* MACOSX */

#if UW
    #include    <stdio.h>
    #include    <syslog.h>
#endif /* UW */

#if VXWORKS
    #ifndef _VSB_CONFIG_FILE                                                                               
        #define _VSB_CONFIG_FILE "vsbConfig.h"                                                             
    #endif
    #include    <vxWorks.h>
    #include    <iosLib.h>
    #include    <sockLib.h>
    #include    <selectLib.h>
    #include    <inetLib.h>
    #include    <ioLib.h>
    #include    <stdio.h>
    #include    <stat.h>
    #include    <time.h>
    #include    <usrLib.h>
    #include    <fcntl.h>
    #include    <errno.h>
    #include    <hostLib.h>
    #include    <dirent.h>
    #include    <sysSymTbl.h>
    #include    <loadLib.h>
    #include    <unldLib.h>
    #include    <envLib.h>
#endif /* VXWORKS */

#if SOLARIS
    #include    <sys/types.h>
    #include    <limits.h>
    #include    <stdio.h>
    #include    <stdlib.h>
    #include    <unistd.h>
    #include    <socket.h>
    #include    <sys/select.h>
    #include    <netinet/in.h>
    #include    <arpa/inet.h>
    #include    <netdb.h>
    #include    <time.h>
    #include    <fcntl.h>
    #include    <errno.h>
    #include    <dirent.h>
    #include    <syslog.h>
#endif /* SOLARIS */

#if QNX
    #include    <sys/types.h>
    #include    <stdio.h>
    #include    <sys/socket.h>
    #include    <sys/select.h>
    #include    <netinet/in.h>
    #include    <arpa/inet.h>
    #include    <netdb.h>
    #include    <stdlib.h>
    #include    <unistd.h>
    #include    <sys/uio.h>
    #include    <sys/wait.h>
    #include    <dirent.h>
#endif /* QNX */

#if ECOS
    #include    <limits.h>
    #include    <cyg/infra/cyg_type.h>
    #include    <cyg/kernel/kapi.h>
    #include    <time.h>
    #include    <network.h>
    #include    <errno.h>
#endif /* ECOS */

/*
    Included by all
 */
#include    <ctype.h>
#include    <stdarg.h>
#include    <string.h>
#include    <stdlib.h>

#if BIT_PACK_OPENSSL
/* Clashes with WinCrypt.h */
#undef OCSP_RESPONSE
#include    <openssl/ssl.h>
#include    <openssl/evp.h>
#include    <openssl/rand.h>
#include    <openssl/err.h>
#include    <openssl/dh.h>

#elif BIT_PACK_MATRIXSSL
/*
    Matrixssl defines int32, uint32, int64 and uint64, but does not provide HAS_XXX to disable.
   So must include matrixsslApi.h first and then workaround.
*/
#if WIN32
    #include   <winsock2.h>
    #include   <windows.h>
#endif
    #include    "matrixsslApi.h"

    #define     HAS_INT32 1
    #define     HAS_UINT32 1
    #define     HAS_INT64 1
    #define     HAS_UINT64 1
#endif /* BIT_PACK_MATRIXSSL */

/************************************** Defines *******************************/
#ifdef __cplusplus
extern "C" {
#endif

/*
    Standard types
 */
#ifndef HAS_BOOL
    #ifndef __cplusplus
        #if !MACOSX
            #define HAS_BOOL 1
            /**
                Boolean data type.
             */
            typedef char bool;
        #endif
    #endif
#endif

#ifndef HAS_UCHAR
    #define HAS_UCHAR 1
    /**
        Unsigned char data type.
     */
    typedef unsigned char uchar;
#endif

#ifndef HAS_SCHAR
    #define HAS_SCHAR 1
    /**
        Signed char data type.
     */
    typedef signed char schar;
#endif

#ifndef HAS_CCHAR
    #define HAS_CCHAR 1
    /**
        Constant char data type.
     */
    typedef const char cchar;
#endif

#ifndef HAS_CUCHAR
    #define HAS_CUCHAR 1
    /**
        Unsigned char data type.
     */
    typedef const unsigned char cuchar;
#endif

#ifndef HAS_USHORT
    #define HAS_USHORT 1
    /**
        Unsigned short data type.
     */
    typedef unsigned short ushort;
#endif

#ifndef HAS_CUSHORT
    #define HAS_CUSHORT 1
    /**
        Constant unsigned short data type.
     */
    typedef const unsigned short cushort;
#endif

#ifndef HAS_CVOID
    #define HAS_CVOID 1
    /**
        Constant void data type.
     */
    typedef const void cvoid;
#endif

#ifndef HAS_INT32
    #define HAS_INT32 1
    /**
        Integer 32 bits data type.
     */
    typedef int int32;
#endif

#ifndef HAS_UINT32
    #define HAS_UINT32 1
    /**
        Unsigned integer 32 bits data type.
     */
    typedef unsigned int uint32;
#endif

#ifndef HAS_UINT
    #define HAS_UINT 1
    /**
        Unsigned integer (machine dependent bit size) data type.
     */
    typedef unsigned int uint;
#endif

#ifndef HAS_ULONG
    #define HAS_ULONG 1
    /**
        Unsigned long (machine dependent bit size) data type.
     */
    typedef unsigned long ulong;
#endif

#ifndef HAS_SSIZE
    #define HAS_SSIZE 1
    #if BIT_UNIX_LIKE || VXWORKS || DOXYGEN
        /**
            Signed integer size field large enough to hold a pointer offset.
         */
        typedef ssize_t ssize;
    #else
        typedef SSIZE_T ssize;
    #endif
#endif

#ifdef __USE_FILE_OFFSET64
    #define BIT_HAS_OFF64 1
#else
    #define BIT_HAS_OFF64 0
#endif

#if BIT_UNIX_LIKE
    #define BIT_HAS_FCNTL 1
#endif

/*
    Windows uses uint for write/read counts (Ugh!)
 */
#if BIT_WIN_LIKE
    typedef uint wsize;
#else
    typedef ssize wsize;
#endif

#ifndef HAS_INT64
    #if BIT_UNIX_LIKE
        __extension__ typedef long long int int64;
    #elif VXWORKS || DOXYGEN
        /**
            Integer 64 bit data type.
         */
        typedef long long int int64;
    #elif BIT_WIN_LIKE
        typedef __int64 int64;
    #else
        typedef long long int int64;
    #endif
#endif

#ifndef HAS_UINT64
    #if BIT_UNIX_LIKE
        __extension__ typedef unsigned long long int uint64;
    #elif VXWORKS || DOXYGEN
        typedef unsigned long long int uint64;
    #elif BIT_WIN_LIKE
        typedef unsigned __int64 uint64;
    #else
        typedef unsigned long long int uint64;
    #endif
#endif

#ifndef BITSPERBYTE
    #define BITSPERBYTE (8 * sizeof(char))
#endif

#ifndef BITS
    #define BITS(type)  (BITSPERBYTE * (int) sizeof(type))
#endif

#if BIT_FLOAT
    #ifndef MAXFLOAT
        #if BIT_WIN_LIKE
            #define MAXFLOAT  DBL_MAX
        #else
            #define MAXFLOAT  FLT_MAX
        #endif
    #endif
    #if VXWORKS
        #define isnan(n)  ((n) != (n))
        #define isnanf(n) ((n) != (n))
        #define isinf(n)  ((n) == (1.0 / 0.0) || (n) == (-1.0 / 0.0))
        #define isinff(n) ((n) == (1.0 / 0.0) || (n) == (-1.0 / 0.0))
    #endif
    #if BIT_WIN_LIKE
        #define isNan(f) (_isnan(f))
    #elif VXWORKS || MACOSX || LINUX
        #define isNan(f) (isnan(f))
    #else
        #define isNan(f) (fpclassify(f) == FP_NAN)
    #endif
#endif

#ifndef MAXINT
#if INT_MAX
    #define MAXINT      INT_MAX
#else
    #define MAXINT      0x7fffffff
#endif
#endif

#ifndef MAXINT64
    #define MAXINT64    INT64(0x7fffffffffffffff)
#endif

#if SIZE_T_MAX
    #define MAXSIZE     SIZE_T_MAX
#elif BIT_64
    #define MAXSIZE     INT64(0xffffffffffffffff)
#else
    #define MAXSIZE     MAXINT
#endif

#if SSIZE_T_MAX
    #define MAXSSIZE     SSIZE_T_MAX
#elif BIT_64
    #define MAXSSIZE     INT64(0x7fffffffffffffff)
#else
    #define MAXSSIZE     MAXINT
#endif

#if OFF_T_MAX
    #define MAXOFF       OFF_T_MAX
#else
    #define MAXOFF       INT64(0x7fffffffffffffff)
#endif

/*
    Word size and conversions between integer and pointer.
 */
#if BIT_64
    #define ITOP(i)     ((void*) ((int64) i))
    #define PTOI(i)     ((int) ((int64) i))
    #define LTOP(i)     ((void*) ((int64) i))
    #define PTOL(i)     ((int64) i)
#else
    #define ITOP(i)     ((void*) ((int) i))
    #define PTOI(i)     ((int) i)
    #define LTOP(i)     ((void*) ((int) i))
    #define PTOL(i)     ((int64) (int) i)
#endif

#if BIT_WIN_LIKE
    #define INT64(x)    (x##i64)
    #define UINT64(x)   (x##Ui64)
    #define BIT_EXPORT  __declspec(dllexport)
#else
    #define INT64(x)    (x##LL)
    #define UINT64(x)   (x##ULL)
    #define BIT_EXPORT 
#endif

#ifndef max
    #define max(a,b)  (((a) > (b)) ? (a) : (b))
#endif
#ifndef min
    #define min(a,b)  (((a) < (b)) ? (a) : (b))
#endif

#ifndef PRINTF_ATTRIBUTE
    #if (__GNUC__ >= 3) && !DOXYGEN && BIT_DEBUG && UNUSED && KEEP
        /** 
            Use gcc attribute to check printf fns.  a1 is the 1-based index of the parameter containing the format, 
            and a2 the index of the first argument. Note that some gcc 2.x versions don't handle this properly 
         */     
        #define PRINTF_ATTRIBUTE(a1, a2) __attribute__ ((format (__printf__, a1, a2)))
    #else
        #define PRINTF_ATTRIBUTE(a1, a2)
    #endif
#endif

/*
    Optimize expression evaluation code depending if the value is likely or not
 */
#undef likely
#undef unlikely
#if (__GNUC__ >= 3)
    #define likely(x)   __builtin_expect(!!(x), 1)
    #define unlikely(x) __builtin_expect(!!(x), 0)
#else
    #define likely(x)   (x)
    #define unlikely(x) (x)
#endif

#if !__UCLIBC__ && !CYGWIN && __USE_XOPEN2K
    #define BIT_HAS_SPINLOCK    1
#endif

#if BIT_HAS_DOUBLE_BRACES || MACOSX || LINUX
    #define  NULL_INIT    {{0}}
#else
    #define  NULL_INIT    {0}
#endif

/*********************************** Fixups ***********************************/

#ifndef R_OK
    #define R_OK    4
    #define W_OK    2
#if BIT_WIN_LIKE
    #define X_OK    R_OK
#else
    #define X_OK    1
#endif
    #define F_OK    0
#endif

#ifndef O_RDONLY
    #if ECOS
        #define     O_RDONLY  1
    #else
        #define     O_RDONLY  1
    #endif
#endif

#ifndef O_BINARY
    #if ECOS 
        #define O_BINARY 2
    #else
        #define O_BINARY 0
    #endif
#endif

#if BIT_UNIX_LIKE || VXWORKS
    #define closesocket(x) close(x)
#endif

#ifndef SOCKET_ERROR
    #define SOCKET_ERROR -1
#endif

#if MACSOX
    #define LD_LIBRARY_PATH "DYLD_LIBRARY_PATH"
#else
    #define LD_LIBRARY_PATH "LD_LIBRARY_PATH"
#endif

#if VXWORKS
    /* Old VxWorks can't do array[] */
    #define BIT_FLEX 0
#else
    #define BIT_FLEX
#endif

#if WINDOWS
    #define getcwd  _getcwd
    #define tempnam _tempnam
    #define open    _open
    #define close   _close
    #define read    _read
    #define write   _write
    #define chdir   _chdir
    #define lseek   _lseek
    #define unlink  _unlink
    #define stat    _stat
    extern void sleep(int secs);
#endif

/**
    Signed file offset data type. Supports large files greater than 4GB in size on all systems.
 */
typedef int64 WebsFilePos;
typedef int64 WebsDateTime;

#if VXWORKS
    typedef int WebsSockLenArg;
#else
    typedef socklen_t WebsSockLenArg;
#endif

#if DOXYGEN || WINDOWS
    typedef int socklen_t;
#endif

#if VXWORKS
    #define fcntl(a, b, c)
    #if _WRS_VXWORKS_MAJOR < 6
        #define NI_MAXHOST 128
        extern STATUS access(char *path, int mode);
        struct sockaddr_storage { char pad[1024]; };
    #endif
#endif /* VXWORKS */

#if ECOS
    #define     LIBKERN_INLINE          /* to avoid kernel inline functions */
    #if BIT_CGI
        #error "Ecos does not support CGI. Disable BIT_CGI"
    #endif
#endif /* ECOS */

#if BIT_WIN_LIKE
    #ifndef EWOULDBLOCK
        #define EWOULDBLOCK WSAEWOULDBLOCK
    #endif
    #ifndef ENETDOWN
        #define ENETDOWN    WSAENETDOWN
    #endif
    #ifndef ECONNRESET
        #define ECONNRESET  WSAECONNRESET
    #endif
#endif

#if LINUX && !defined(_STRUCT_TIMEVAL)
    struct timeval
    {
        time_t  tv_sec;     /* Seconds.  */
        time_t  tv_usec;    /* Microseconds.  */
    };
    #define _STRUCT_TIMEVAL 1
#endif

#if QNX
    typedef long fd_mask;
    #define NFDBITS (sizeof (fd_mask) * NBBY)   /* bits per mask */
#endif

#if MACOSX
    typedef int32_t fd_mask;
#endif
#if WINDOWS
    typedef fd_set fd_mask;
#endif

/*
    Copyright. The software license requires that this not be modified or removed.
 */
#define EMBEDTHIS_GOAHEAD_COPYRIGHT T(\
    "Copyright (c) Embedthis Software Inc., 1993-2012. All Rights Reserved." \
    "Copyright (c) GoAhead Software Inc., 2012. All Rights Reserved." \
    )

/************************************ Unicode *********************************/
#if UNICODE
    #if !BIT_WIN_LIKE
        #error "Unicode only supported on Windows or Windows CE"
    #endif
    typedef ushort char_t;
    typedef ushort uchar_t;

#if UNUSED
    /*
        To convert strings to UNICODE. We have a level of indirection so things like T(__FILE__) will expand properly.
     */
    #define T(x)      __TXT(x)
    #define __TXT(s)  L ## s
#endif

    /*
        Size of a buffer in characters
     */
    #define TSZ(x) (sizeof(x) / sizeof(wchar))

    #define gaccess     _waccess
    #define gasctime    _wasctime
    #define gatoi(s)    wcstol(s, NULL, 10)
    #define gchdir      _wchdir
    #define gchmod      _wchmod
    #define gclose      close
    #define gcreat      _wcreat
    #define gctime      _wctime
    #define gexecvp     _wexecvp
    #define gfgets      fgetws
    #define gfindclose  _findclose
    #define gfinddata_t _wfinddata_t
    #define gfindfirst  _wfindfirst
    #define gfindnext   _wfindnext
    #define gfopen      _wfopen
    #define gfprintf    fwprintf
    #define gfputs      fputws
    #define gfscanf     fwscanf
    #define ggetcwd     _wgetcwd
    #define ggetenv     _wgetenv
    #define ggets       _getws
    #define gisalnum    iswalnum
    #define gisalpha    iswalpha
    #define glseek      lseek
    #define gmkdir      _wmkdir
    #define gprintf     wprintf
    #define gread       read
    #define grename     _wrename
    #define grmdir      _wrmdir
    #define gsprintf    swprintf
    #define gsscanf     swscanf
    #define gstat       _wstat
    #define gstrcat     wcscat
    #define gstrchr     wcschr
    #define gstrcmp     wcscmp
    #define gstrcpy     wcscpy
    #define gstrcspn    wcscspn
    #define gstricmp    wcsicmp
    #define gstrlen     wcslen
    #define gstrncat    wcsncat
    #define gstrncmp    wcsncmp
    #define gstrncpy    wcsncpy
    #define gstrnset    wcsnset
    #define gstrrchr    wcsrchr
    #define gstrspn     wcsspn
    #define gstrstr     wcsstr
    #define gstrtok     wcstok
    #define gstrtol     wcstol
    #define gtempnam    _wtempnam
    #define gtmpnam     _wtmpnam
    #define gtolower    towlower
    #define gtoupper    towupper
    #define gunlink     _wunlink
    #define gvsprintf   vswprintf
    #define gwrite      write

    #if CE
        #define gisspace    isspace
        #define gisdigit    isdigit
        #define gisxdigit   isxdigit
        #define gisupper    isupper
        #define gislower    islower
        #define gisprint    isprint
    #else
        #define gremove     _wremove
        #define gisspace    iswspace
        #define gisdigit    iswdigit
        #define gisxdigit   iswxdigit
        #define gisupper    iswupper
        #define gislower    iswlower
    #endif  /* CE */
    
    typedef struct _stat WebsStat;
    
#else /* !UNICODE */

    //  MOB REVIEW
    #define T(s)        s
    #define TSZ(x)      (sizeof(x))
    typedef char        char_t;
    #if WINDOWS
        typedef uchar   uchar_t;
    #endif
    #if VXWORKS
        #define gchdir      vxchdir
        #define gmkdir      vxmkdir
        #define grmdir      vxrmdir
    #elif BIT_UNIX_LIKE
        #define gchdir      chdir
        #define gmkdir(s)   mkdir(s,0755)
        #define grmdir      rmdir
    #else
        #define gchdir      chdir
        #define gmkdir      mkdir
        #define grmdir      rmdir
    #endif
    #define gaccess     access
    #define gasctime    asctime
    #define gatoi       atoi
    #define gchmod      chmod
    #define gclose      close
    #define gclosedir   closedir
    #define gcreat      creat
    #define gctime      ctime
    #define gexecvp     execvp
    #define gfgets      fgets
    #define gfindclose  _findclose
    #define gfinddata_t _finddata_t
    #define gfindfirst  _findfirst
    #define gfindnext   _findnext
    #define gfopen      fopen
    #define gfprintf    fprintf
    #define gfputs      fputs
    #define gfscanf     fscanf
    #define ggetcwd     getcwd
    #define ggetenv     getenv
    #define ggets       gets
    #define gisalnum    isalnum
    #define gisalpha    isalpha
    #define gisdigit    isdigit
    #define gislower    islower
    #define gisspace    isspace
    #define gisupper    isupper
    #define gisxdigit   isxdigit
    #define gloadModule loadModule
    #define glseek      lseek
    #define gopendir    opendir
    #define gprintf     printf
    #define gread       read
    #define greaddir    readdir
    #define gremove     remove
    #define grename     rename
    #define gsprintf    sprintf
    #define gsscanf     sscanf
    #define gstat       stat
    #define gstrcat     strcat
    #define gstrchr     strchr
    #define gstrcmp     strcmp
    #define gstrcpy     strcpy
    #define gstrcspn    strcspn
    #define gstricmp    strcmpci
    #define gstrlen     strlen
    #define gstrncat    strncat
    #define gstrncmp    strncmp
    #define gstrncpy    strncpy
    #define gstrnset    strnset
    #define gstrrchr    strrchr
    #define gstrspn     strspn
    #define gstrstr     strstr
    #define gstrtok     strtok
    #define gstrtol     strtol
    #define gtempnam    tempnam
    #define gtmpnam     tmpnam
    #define gtolower    tolower
    #define gtoupper    toupper
    #define gunlink     unlink
    #define gvsprintf   vsprintf
    #define gwrite      write
    typedef struct stat WebsStat;
#endif /* !UNICODE */

extern char_t *guni(char_t *ubuf, char *str, ssize nBytes);
extern char *gasc(char *buf, char_t *ustr, ssize nBytes);

#if CE
extern int gwriteUniToAsc(int fid, void *buf, ssize len);
extern int greadAscToUni(int fid, void **buf, ssize len);
#endif

#if !LINUX
    extern char_t *basename(char_t *name);
#endif

#if VXWORKS
    extern int vxchdir(char_t *dirname);
#endif

/************************************* Main ***********************************/

#define BIT_MAX_ARGC 32
#if VXWORKS
    #define MAIN(name, _argc, _argv, _envp)  \
        static int innerMain(int argc, char **argv, char **envp); \
        int name(char *arg0, ...) { \
            va_list args; \
            char *argp, *largv[BIT_MAX_ARGC]; \
            int largc = 0; \
            va_start(args, arg0); \
            largv[largc++] = #name; \
            if (arg0) { \
                largv[largc++] = arg0; \
            } \
            for (argp = va_arg(args, char*); argp && largc < BIT_MAX_ARGC; argp = va_arg(args, char*)) { \
                largv[largc++] = argp; \
            } \
            return innerMain(largc, largv, NULL); \
        } \
        static int innerMain(_argc, _argv, _envp)
#elif BIT_WIN_LIKE && UNICODE
    #define MAIN(name, _argc, _argv, _envp)  \
        APIENTRY WinMain(HINSTANCE inst, HINSTANCE junk, LPWSTR command, int junk2) { \
            char *largv[BIT_MAX_ARGC]; \
            extern int main(); \
            char *mcommand[BIT_LIMIT_STRING]; \
            int largc; \
            wtom(mcommand, sizeof(dest), command, -1);
            largc = gparseArgs(mcommand, &largv[1], BIT_MAX_ARGC - 1); \
            largv[0] = #name; \
            gsetAppInstance(inst); \
            main(largc, largv, NULL); \
        } \
        int main(argc, argv, _envp)
#elif BIT_WIN_LIKE
    #define MAIN(name, _argc, _argv, _envp)  \
        APIENTRY WinMain(HINSTANCE inst, HINSTANCE junk, char *command, int junk2) { \
            extern int main(); \
            char *largv[BIT_MAX_ARGC]; \
            int largc; \
            largc = gparseArgs(command, &largv[1], BIT_MAX_ARGC - 1); \
            largv[0] = #name; \
            main(largc, largv, NULL); \
        } \
        int main(_argc, _argv, _envp)
#else
    #define MAIN(name, _argc, _argv, _envp) int main(_argc, _argv, _envp)
#endif

extern int gparseArgs(char *args, char **argv, int maxArgc);

#if WINDOWS
    extern void websSetInst(HINSTANCE inst);
    extern HINSTANCE websGetInst();
#endif

/************************************ Tunables ********************************/

#define WEBS_MAX_LISTEN     8           /**< Maximum number of listen endpoints */
#define WEBS_SMALL_HASH     31          /**< General small hash size */

/************************************* Error **********************************/

#define WEBS_L                 T(__FILE__), __LINE__
#define WEBS_ARGS_DEC          char_t *file, int line
#define WEBS_ARGS              file, line

/*
    Log level flags
 */
#define WEBS_LOG_RAW        0x1000
#define WEBS_LOG_NEWLINE    0x2000
#define WEBS_LOG_MASK       0xF

#if BIT_DEBUG
    #define gassert(C)     if (C) ; else gassertError(WEBS_L, T("%s"), T(#C))
    extern void gassertError(WEBS_ARGS_DEC, char_t *fmt, ...);
#else
    #define gassert(C)     if (1) ; else
#endif

#define LOG trace
#if UNUSED
extern void traceRaw(char_t *buf);
#endif
extern int traceOpen();
extern void traceClose();
typedef void (*WebsTraceHandler)(int level, char_t *msg);
extern WebsTraceHandler traceSetHandler(WebsTraceHandler handler);
extern void traceSetPath(char_t *path);

extern void error(char_t *fmt, ...);
extern void trace(int lev, char_t *fmt, ...);

/*********************************** HTTP Codes *******************************/
/*
    Standard HTTP/1.1 status codes
 */
#define HTTP_CODE_CONTINUE                  100     /**< Continue with request, only partial content transmitted */
#define HTTP_CODE_OK                        200     /**< The request completed successfully */
#define HTTP_CODE_CREATED                   201     /**< The request has completed and a new resource was created */
#define HTTP_CODE_ACCEPTED                  202     /**< The request has been accepted and processing is continuing */
#define HTTP_CODE_NOT_AUTHORITATIVE         203     /**< The request has completed but content may be from another source */
#define HTTP_CODE_NO_CONTENT                204     /**< The request has completed and there is no response to send */
#define HTTP_CODE_RESET                     205     /**< The request has completed with no content. Client must reset view */
#define HTTP_CODE_PARTIAL                   206     /**< The request has completed and is returning partial content */
#define HTTP_CODE_MOVED_PERMANENTLY         301     /**< The requested URI has moved permanently to a new location */
#define HTTP_CODE_MOVED_TEMPORARILY         302     /**< The URI has moved temporarily to a new location */
#define HTTP_CODE_SEE_OTHER                 303     /**< The requested URI can be found at another URI location */
#define HTTP_CODE_NOT_MODIFIED              304     /**< The requested resource has changed since the last request */
#define HTTP_CODE_USE_PROXY                 305     /**< The requested resource must be accessed via the location proxy */
#define HTTP_CODE_TEMPORARY_REDIRECT        307     /**< The request should be repeated at another URI location */
#define HTTP_CODE_BAD_REQUEST               400     /**< The request is malformed */
#define HTTP_CODE_UNAUTHORIZED              401     /**< Authentication for the request has failed */
#define HTTP_CODE_PAYMENT_REQUIRED          402     /**< Reserved for future use */
#define HTTP_CODE_FORBIDDEN                 403     /**< The request was legal, but the server refuses to process */
#define HTTP_CODE_NOT_FOUND                 404     /**< The requested resource was not found */
#define HTTP_CODE_BAD_METHOD                405     /**< The request HTTP method was not supported by the resource */
#define HTTP_CODE_NOT_ACCEPTABLE            406     /**< The requested resource cannot generate the required content */
#define HTTP_CODE_REQUEST_TIMEOUT           408     /**< The server timed out waiting for the request to complete */
#define HTTP_CODE_CONFLICT                  409     /**< The request had a conflict in the request headers and URI */
#define HTTP_CODE_GONE                      410     /**< The requested resource is no longer available*/
#define HTTP_CODE_LENGTH_REQUIRED           411     /**< The request did not specify a required content length*/
#define HTTP_CODE_PRECOND_FAILED            412     /**< The server cannot satisfy one of the request preconditions */
#define HTTP_CODE_REQUEST_TOO_LARGE         413     /**< The request is too large for the server to process */
#define HTTP_CODE_REQUEST_URL_TOO_LARGE     414     /**< The request URI is too long for the server to process */
#define HTTP_CODE_UNSUPPORTED_MEDIA_TYPE    415     /**< The request media type is not supported by the server or resource */
#define HTTP_CODE_RANGE_NOT_SATISFIABLE     416     /**< The request content range does not exist for the resource */
#define HTTP_CODE_EXPECTATION_FAILED        417     /**< The server cannot satisfy the Expect header requirements */
#define HTTP_CODE_NO_RESPONSE               444     /**< The connection was closed with no response to the client */
#define HTTP_CODE_INTERNAL_SERVER_ERROR     500     /**< Server processing or configuration error. No response generated */
#define HTTP_CODE_NOT_IMPLEMENTED           501     /**< The server does not recognize the request or method */
#define HTTP_CODE_BAD_GATEWAY               502     /**< The server cannot act as a gateway for the given request */
#define HTTP_CODE_SERVICE_UNAVAILABLE       503     /**< The server is currently unavailable or overloaded */
#define HTTP_CODE_GATEWAY_TIMEOUT           504     /**< The server gateway timed out waiting for the upstream server */
#define HTTP_CODE_BAD_VERSION               505     /**< The server does not support the HTTP protocol version */
#define HTTP_CODE_INSUFFICIENT_STORAGE      507     /**< The server has insufficient storage to complete the request */

/*
    Proprietary HTTP status codes
 */
#define HTTP_CODE_START_LOCAL_ERRORS        550
#define HTTP_CODE_COMMS_ERROR               550     /**< The server had a communicationss error responding to the client */

/************************************* Value **********************************/
/*
    These values are not prefixed so as to aid code readability
 */
typedef enum {
    undefined   = 0,
    byteint     = 1,
    shortint    = 2,
    integer     = 3,
    hex         = 4,
    percent     = 5,
    octal       = 6,
    big         = 7,
    flag        = 8,
    floating    = 9,
    string      = 10,
    bytes       = 11,
    symbol      = 12,
    errmsg      = 13
} vtype_t;

typedef struct {
    union {
        char    flag;
        char    byteint;
        short   shortint;
        char    percent;
        long    integer;
        long    hex;
        long    octal;
        long    big[2];
#if BIT_FLOAT
        double  floating;
#endif
        char_t  *string;
        char    *bytes;
        char_t  *errmsg;
        void    *symbol;
    } value;
    vtype_t     type;
    uint        valid       : 8;
    uint        allocated   : 8;        /* String was allocated */
} value_t;

#define value_numeric(t)    (t >= byteint && t <= big)
#define value_str(t)        (t >= string && t <= bytes)
#define value_ok(t)         (t > undefined && t <= symbol)

#define VALUE_ALLOCATE      0x1
#define VALUE_VALID         { {0}, integer, 1 }
#define VALUE_INVALID       { {0}, undefined, 0 }

extern value_t valueInteger(long value);
extern value_t valueString(char_t *value, int flags);
extern value_t valueSymbol(void *value);
extern value_t valueErrmsg(char_t *value);
extern void valueFree(value_t *v);

/************************************* Ringq **********************************/
/*
    A ring queue allows maximum utilization of memory for data storage and is
    ideal for input/output buffering. This module provides a highly effecient
    implementation and a vehicle for dynamic strings.
  
    WARNING:  This is a public implementation and callers have full access to
    the queue structure and pointers.  Change this module very carefully.
  
    This module follows the open/close model.
  
    Operation of a ringq where rq is a pointer to a ringq :
  
        rq->buflen contains the size of the buffer.
        rq->buf will point to the start of the buffer.
        rq->servp will point to the first (un-consumed) data byte.
        rq->endp will point to the next free location to which new data is added
        rq->endbuf will point to one past the end of the buffer.
  
    Eg. If the ringq contains the data "abcdef", it might look like :
  
    +-------------------------------------------------------------------+
    |   |   |   |   |   |   |   | a | b | c | d | e | f |   |   |   |   |
    +-------------------------------------------------------------------+
      ^                           ^                       ^               ^
      |                           |                       |               |
    rq->buf                    rq->servp               rq->endp      rq->enduf
       
    The queue is empty when servp == endp.  This means that the queue will hold
    at most rq->buflen -1 bytes.  It is the fillers responsibility to ensure
    the ringq is never filled such that servp == endp.
  
    It is the fillers responsibility to "wrap" the endp back to point to
    rq->buf when the pointer steps past the end. Correspondingly it is the
    consumers responsibility to "wrap" the servp when it steps to rq->endbuf.
    The ringqPutc and ringqGetc routines will do this automatically.
 */

typedef struct {
    char    *buf;               /* Holding buffer for data */
    char    *servp;             /* Pointer to start of data */
    char    *endp;              /* Pointer to end of data */
    char    *endbuf;            /* Pointer to end of buffer */
    ssize   buflen;             /* Length of ring queue */
    ssize   maxsize;            /* Maximum size */
    int     increment;          /* Growth increment */
} ringq_t;

extern int ringqOpen(ringq_t *rq, int increment, int maxsize);
extern void ringqClose(ringq_t *rq);
extern ssize ringqLen(ringq_t *rq);
extern int ringqPutc(ringq_t *rq, char_t c);
extern int ringqInsertc(ringq_t *rq, char_t c);
extern ssize ringqPutStr(ringq_t *rq, char_t *str);
extern int ringqGetc(ringq_t *rq);
extern int ringqGrow(ringq_t *rq);

#if UNICODE || DOXYGEN
    extern int ringqPutcA(ringq_t *rq, char c);
    extern int ringqInsertcA(ringq_t *rq, char c);
    extern int ringqPutStrA(ringq_t *rq, char *str);
    extern int ringqGetcA(ringq_t *rq);
#else
    #define ringqPutcA ringqPutc
    #define ringqInsertcA ringqInsertc
    #define ringqPutStrA ringqPutStr
    #define ringqGetcA ringqGetc
#endif /* UNICODE */

extern ssize ringqPutBlk(ringq_t *rq, char *buf, ssize len);
extern ssize ringqPutBlkMax(ringq_t *rq);
extern void ringqPutBlkAdj(ringq_t *rq, ssize size);
extern ssize ringqGetBlk(ringq_t *rq, char *buf, ssize len);
extern ssize ringqGetBlkMax(ringq_t *rq);
extern void ringqGetBlkAdj(ringq_t *rq, ssize size);
extern void ringqFlush(ringq_t *rq);
extern void ringqCompact(ringq_t *rq);
extern void ringqAddNull(ringq_t *rq);

/******************************* Malloc Replacement ***************************/
/*
    Block classes are: 16, 32, 64, 128, 256, 512, 1024, 2048, 4096, 8192, 16384, 32768, 65536 
 */
typedef struct WebsBlock {
    union {
        void    *next;                          /* Pointer to next in q */
        int     size;                           /* Actual requested size */
    } u;
    int         flags;                          /* Per block allocation flags */
} WebsBlock;

#define WEBS_SHIFT         4                   /* Convert size to class */
#define WEBS_ROUND         ((1 << (B_SHIFT)) - 1)
#define WEBS_MAX_CLASS     13                  /* Maximum class number + 1 */
#define WEBS_MALLOCED      0x80000000          /* Block was malloced */
#define WEBS_DEFAULT_MEM   (64 * 1024)         /* Default memory allocation */
#define WEBS_MAX_FILES     (512)               /* Maximum number of files */
#define WEBS_FILL_CHAR     (0x77)              /* Fill byte for buffers */
#define WEBS_FILL_WORD     (0x77777777)        /* Fill word for buffers */
#define WEBS_MAX_BLOCKS    (64 * 1024)         /* Maximum allocated blocks */

/*
    Flags. The integrity value is used as an arbitrary value to fill the flags.
 */
#define WEBS_INTEGRITY         0x8124000       /* Integrity value */
#define WEBS_INTEGRITY_MASK    0xFFFF000       /* Integrity mask */
#define WEBS_USE_MALLOC        0x1             /* Okay to use malloc if required */
#define WEBS_USER_BUF          0x2             /* User supplied buffer for mem */

extern void gcloseAlloc();
extern int  gopenAlloc(void *buf, int bufsize, int flags);

#if !BIT_REPLACE_MALLOC
    extern char_t *gstrdupNoAlloc(char_t *s);
    extern char *gstrdupANoAlloc(char *s);
    #define galloc(num) malloc(num)
    #define gfree(p) if (p) { free(p); } else
    #define grealloc(p, num) realloc(p, num)
    #define gstrdup(s) gstrdupNoAlloc(s)
    #define gstrdupA(s) gstrdupANoAlloc(s)
    #define gstrdup(s) gstrdupNoAlloc(s)

#else /* BIT_REPLACE_MALLOC */
    #if UNICODE
        extern char *gstrdupA(char *s);
        #define gstrdupA(p) gstrdupA(p)
    #else
        #define gstrdupA gstrdup
    #endif
    extern void *galloc(ssize size);
    extern void gfree(void *mp);
    extern void *grealloc(void *buf, ssize newsize);
    extern char_t *gstrdup(char_t *s);
#endif /* BIT_REPLACE_MALLOC */

extern char_t *gallocAscToUni(char  *cp, ssize alen);
extern char *gallocUniToAsc(char_t *unip, ssize ulen);

/******************************* Symbol Table *********************************/
/*
    The symbol table record for each symbol entry
 */
typedef struct WebsKey {
    struct WebsKey  *forw;                  /* Pointer to next hash list */
    value_t         name;                   /* Name of symbol */
    value_t         content;                /* Value of symbol */
    int             arg;                    /* Parameter value */
    int             bucket;                 /* Bucket index */
} WebsKey;

typedef int WebsHash;                       /* Returned by symOpen */

extern WebsHash symOpen(int hash_size);
extern void     symClose(WebsHash sd);
extern WebsKey  *symLookup(WebsHash sd, char_t *name);
extern WebsKey  *symEnter(WebsHash sd, char_t *name, value_t v, int arg);
extern int      symDelete(WebsHash sd, char_t *name);
extern void     symWalk(WebsHash sd, void (*fn)(WebsKey *symp));
extern WebsKey  *symFirst(WebsHash sd);
extern WebsKey  *symNext(WebsHash sd, WebsKey *last);

/************************************ Socket **********************************/
/*
    Socket flags 
 */
#define SOCKET_EOF              0x1     /* Seen end of file */
#define SOCKET_CONNECTING       0x2     /* Connect in progress */
#define SOCKET_PENDING          0x4     /* Message pending on this socket */
#define SOCKET_RESERVICE        0x8     /* Socket needs re-servicing */
#define SOCKET_ASYNC            0x10    /* Use async connect */
#define SOCKET_BLOCK            0x20    /* Use blocking I/O */
#define SOCKET_LISTENING        0x40    /* Socket is server listener */
#define SOCKET_CLOSING          0x80    /* Socket is closing */
#define SOCKET_CONNRESET        0x100   /* Socket connection was reset */
#define SOCKET_TRACED           0x200   /* Trace TLS connections */

#define SOCKET_PORT_MAX         0xffff  /* Max Port size */

/*
    Socket error values
 */
#define SOCKET_WOULDBLOCK       1       /* Socket would block on I/O */
#define SOCKET_RESET            2       /* Socket has been reset */
#define SOCKET_NETDOWN          3       /* Network is down */
#define SOCKET_AGAIN            4       /* Issue the request again */
#define SOCKET_INTR             5       /* Call was interrupted */
#define SOCKET_INVAL            6       /* Invalid */

/*
    Handler event masks
 */
#define SOCKET_READABLE         0x2     /* Make socket readable */ 
#define SOCKET_WRITABLE         0x4     /* Make socket writable */
#define SOCKET_EXCEPTION        0x8     /* Interested in exceptions */

typedef void    (*socketHandler_t)(int sid, int mask, void* data);
typedef int     (*socketAccept_t)(int sid, char *ipaddr, int port, int listenSid);

typedef struct {
    ringq_t         lineBuf;                /* Line ring queue */
    socketAccept_t  accept;                 /* Accept handler */
    socketHandler_t handler;                /* User I/O handler */
    char            *ip;                    /* Server listen address or remote client address */
    void            *handler_data;          /* User handler data */
    int             handlerMask;            /* Handler events of interest */
    int             sid;                    /* Index into socket[] */
    int             port;                   /* Port to listen on */
    int             flags;                  /* Current state flags */
    int             sock;                   /* Actual socket handle */
    int             fileHandle;             /* ID of the file handler */
    int             interestEvents;         /* Mask of events to watch for */
    int             currentEvents;          /* Mask of ready events (FD_xx) */
    int             selectEvents;           /* Events being selected */
    int             saveMask;               /* saved Mask for socketFlush */
    int             error;                  /* Last error */
    int             secure;                 /* Socket is using SSL */
} socket_t;

extern socket_t     **socketList;           /* List of open sockets */

extern int      socketAddress(struct sockaddr *addr, int addrlen, char *ip, int ipLen, int *port);
extern bool     socketAddressIsV6(char_t *ip);
extern void     socketClose();
extern void     socketCloseConnection(int sid);
extern int      socketConnect(char *host, int port, int flags);
extern void     socketCreateHandler(int sid, int mask, socketHandler_t handler, void *arg);
extern void     socketDeleteHandler(int sid);
extern void     socketReservice(int sid);
extern int      socketEof(int sid);
extern int      socketGetPort(int sid);
extern int      socketInfo(char_t *ip, int port, int *family, int *protocol, struct sockaddr_storage *addr, 
                    WebsSockLenArg *addrlen);
extern bool     socketIsV6(int sid);
extern int      socketOpen();
extern int      socketListen(char *host, int port, socketAccept_t accept, int flags);
extern int      socketParseAddress(char_t *ipAddrPort, char_t **pip, int *pport, int *secure, int defaultPort);
extern void     socketProcess();
extern ssize    socketRead(int sid, void *buf, ssize len);
extern ssize    socketWrite(int sid, void *buf, ssize len);
extern ssize    socketWriteString(int sid, char_t *buf);
extern int      socketSelect(int hid, int timeout);
extern int      socketGetHandle(int sid);
extern int      socketSetBlock(int sid, int flags);
extern int      socketGetBlock(int sid);
extern int      socketAlloc(char *host, int port, socketAccept_t accept, int flags);
extern void     socketFree(int sid);
extern int      socketGetError();
extern socket_t *socketPtr(int sid);
extern int      socketWaitForEvent(socket_t *sp, int events, int *errCode);
extern void     socketRegisterInterest(socket_t *sp, int handlerMask);
extern ssize    socketGetInput(int sid, char *buf, ssize toRead, int *errCode);

/*********************************** Runtime **********************************/

/*
    String trim flags
 */
#define WEBS_TRIM_START  0x1             /**< Flag for #strim to trim from the start of the string */
#define WEBS_TRIM_END    0x2             /**< Flag for #strim to trim from the end of the string */
#define WEBS_TRIM_BOTH   0x3             /**< Flag for #strim to trim from both the start and the end of the string */

extern char *gtrim(char *str, cchar *set, int where);

extern int gallocHandle(void ***map);
extern int gallocEntry(void ***list, int *max, int size);
extern int gfreeHandle(void ***map, int handle);
extern int gcaselesscmp(char_t *s1, char_t *s2);
extern bool gcaselessmatch(char_t *s1, char_t *s2);
extern int gcmp(char_t *s1, char_t *s2);
extern ssize gfmtAlloc(char_t **s, ssize n, char_t *fmt, ...);
extern ssize gfmtStatic(char_t *s, ssize n, char_t *fmt, ...);
extern ssize gfmtValloc(char_t **s, ssize n, char_t *fmt, va_list arg);
extern uint ghextoi(char_t *hexstring);
extern ssize glen(char_t *s1);
extern ssize gcopy(char *dest, ssize destMax, char *src);
extern ssize gncopy(char *dest, ssize destMax, char *src, ssize count);
extern bool gmatch(char_t *s1, char_t *s2);
extern int gopen(char_t *path, int oflag, int mode);
extern int gncaselesscmp(char_t *s1, char_t *s2, ssize n);
extern int gncmp(char_t *s1, char_t *s2, ssize n);
extern char_t *gstrlower(char_t *string);
extern ssize gstrnlen(char_t *s, ssize n);
extern char_t *gstrupper(char_t *string);
extern char_t *gstritoa(int n, char_t *string, int width);
extern uint gstrtoi(char_t *s);
extern char_t *gtok(char_t *str, char_t *delim, char_t **last);

typedef void (WebsCallback)(void *data, int id);
extern int gschedCallback(int delay, WebsCallback *proc, void *arg);
extern void gunschedCallback(int id);
extern void greschedCallback(int id, int delay);
extern void grunCallbacks();

/* Forward declare */
struct WebsRoute;
struct WebsUser;
struct WebsSession;
struct Webs;

/********************************** Upload ************************************/
#if BIT_UPLOAD

typedef struct WebsUploadFile {
    char    *filename;              /**< Local (temp) name of the file */
    char    *clientFilename;        /**< Client side name of the file */
    char    *contentType;           /**< Content type */
    ssize   size;                   /**< Uploaded file size */
} WebsUploadFile;

extern void websUploadOpen();
extern WebsHash websGetUpload(struct Webs *wp);
extern WebsUploadFile *websLookupUpload(struct Webs *wp, char *key);
#endif
/********************************** Defines ***********************************/

#define WEBS_MAX_PORT_LEN       10          /* Max digits in port number */
#define WEBS_SYM_INIT           64          /* Hash size for form table */
#define WEBS_SESSION_HASH       31          /* Hash size for session stores */
#define WEBS_SESSION_PRUNE      (60*1000)   /* Prune sessions every minute */

/* 
    Request flags (MOB - reorder)
 */
//  MOB - is this used
#define WEBS_LOCAL_PAGE         0x1         /* Request for local webs page */ 
#define WEBS_KEEP_ALIVE         0x2         /* HTTP/1.1 keep alive */
#define WEBS_COOKIE             0x8         /* Cookie supplied in request */
#define WEBS_IF_MODIFIED        0x10        /* If-modified-since in request */

#define WEBS_POST               0x20        /* Post request operation */
//  MOB - is this used?
#define WEBS_LOCAL              0x40        /* Request from this system */
#define WEBS_HOME_PAGE          0x80        /* Request for the home page */ 
#define WEBS_JS                 0x100       /* Javscript request */ 
#define WEBS_HEAD               0x200       /* Head request */
#define WEBS_FORM               0x800       /* Request is a form (url encoded data) */
#define WEBS_DELETE             0x1000      /* Delete method */
#define WEBS_PUT                0x2000      /* Put method */
#define WEBS_CGI                0x4000      /* cgi-bin request */
#define WEBS_SECURE             0x8000      /* connection uses SSL */
#define WEBS_HEADER_DONE        0x40000     /* Already output the HTTP header */
#define WEBS_HTTP11             0x80000     /* Request is using HTTP/1.1 */
#define WEBS_RESPONSE_TRACED    0x100000    /* Started tracing the response */
#define WEBS_GET                0x200000    /* Get Request */
#define WEBS_UPLOAD             0x400000    /* Multipart-mime file upload */
#define WEBS_ACCEPTED           0x800000    /* TLS connection accepted */

/*
    URL handler flags
 */
#define WEBS_HANDLER_FIRST  0x1         /* Process this handler first */
#define WEBS_HANDLER_LAST   0x2         /* Process this handler last */

/* 
    Read handler flags and state
 */
#define WEBS_BEGIN          0x1         /* Beginning state */
#define WEBS_CONTENT        0x2         /* Ready for body data */
#define WEBS_RUNNING        0x4         /* Processing request */

#define WEBS_KEEP_TIMEOUT   15000       /* Keep-alive timeout (15 secs) */
#define WEBS_TIMEOUT        60000       /* General request timeout (60) */

/*
    Session names
 */
#define WEBS_SESSION            "-goahead-session-"
#define WEBS_SESSION_USERNAME   "_:USERNAME:_"      /**< Username variable */

/*
    Flags for httpSetCookie
 */
#define WEBS_COOKIE_SECURE   0x1         /**< Flag for websSetCookie for secure cookies (https only) */
#define WEBS_COOKIE_HTTP     0x2         /**< Flag for websSetCookie for http cookies (http only) */

/*
    WebsDone flags
 */
#define WEBS_CLOSE          0x20000

/* 
    Per socket connection webs structure
 */
typedef struct Webs {
    ringq_t         input;              /* Request input buffer */
    ringq_t         output;             /* Output buffer */
    time_t          since;              /* Parsed if-modified-since time */
    WebsHash        vars;               /* CGI standard variables */
    time_t          timestamp;          /* Last transaction with browser */
    int             timeout;            /* Timeout handle */
    char_t          ipaddr[64];         /* Connecting ipaddress */
    char_t          ifaddr[64];         /* Local interface ipaddress */

    //  MOB OPT - which of these should be allocated strings and which should be static

    char_t          *authDetails;       /* Http header auth details */
    char_t          *authResponse;      /* Outgoing auth header */
    char_t          *authType;          /* Authorization type (Basic/DAA) */
    char_t          *contentType;       /* Body content type */
    char_t          *cookie;            /* Request cookie string */
    char_t          *decodedQuery;      /* Decoded request query */
    char_t          *digest;            /* Password digest */
    char_t          *dir;               /* Directory containing the page */
    char_t          *ext;               /* Path extension */
    char_t          *filename;          /* Document path name */
    char_t          *host;              /* Requested host */
    char_t          *inputFile;         /* File name to write input body data */
    char_t          *method;            /* HTTP request method */
    char_t          *password;          /* Authorization password */
    char_t          *path;              /* Path name without query */
    char_t          *protoVersion;      /* Protocol version */
    char_t          *protocol;          /* Protocol (normally HTTP) */
    char_t          *query;             /* Request query */
    char_t          *realm;             /* Realm field supplied in auth header */
    char_t          *responseCookie;    /* Outgoing cookie */
    char_t          *url;               /* Full request url */
    char_t          *userAgent;         /* User agent (browser) */
    char_t          *username;          /* Authorization username */

    int             sid;                /* Socket id (handler) */
    int             listenSid;          /* Listen Socket id */
    int             port;               /* Request port number */
    int             state;              /* Current state */
    int             flags;              /* Current flags -- see above */
    int             code;               /* Response status code */
    ssize           clen;               /* Content length */
    ssize           remainingContent;   /* Remaining content length to read */
    ssize           buffered;           /* Content buffered in input */
    int             wid;                /* Index into webs */
#if BIT_CGI
    char_t          *cgiStdin;          /* Filename for CGI program input */
    int             cgifd;              /* File handle for CGI program input */
#endif
    int             putfd;              /* File handle to write PUT data */
    int             docfd;              /* File descriptor for document being served */
    ssize           numbytes;           /* Bytes to transfer to browser */
    ssize           written;            /* Bytes actually transferred */
    void            (*writable)(struct Webs *wp);

    struct WebsSession *session;        /* Session record */
    struct WebsRoute *route;            /* Request route */
    struct WebsUser *user;              /* User auth record */
    int             encoded;            /* True if the password is MD5(username:realm:password) */
#if BIT_DIGEST
    char_t          *cnonce;            /* check nonce */
    char_t          *digestUri;         /* URI found in digest header */
    char_t          *nonce;             /* opaque-to-client string sent by server */
    char_t          *nc;                /* nonce count */
    char_t          *opaque;            /* opaque value passed from server */
    char_t          *qop;               /* quality operator */
#endif
#if BIT_UPLOAD
    int             upfd;               /* Upload file handle */
    WebsHash        files;              /* Uploaded files */
    char            *boundary;          /* Mime boundary (static) */
    ssize           boundaryLen;        /* Boundary length */
    int             uploadState;        /* Current file upload state */
    WebsUploadFile  *currentFile;       /* Current file context */
    char            *clientFilename;    /* Current file filename */
    char            *uploadTmp;         /* Current temp filename for upload data */
    char            *uploadVar;         /* Current upload form variable name */
#endif
#if BIT_PACK_OPENSSL
    SSL             *ssl;               /* SSL state */
    BIO             *bio;               /* Buffer for I/O - not used in actual I/O */
#elif BIT_PACK_MATRIXSSL
    void            *ms;                /* MatrixSSL state */
#endif
} Webs;


typedef int (*WebsHandlerProc)(Webs *wp, char_t *prefix, char_t *dir, int arg);
typedef int (*WebsProc)(Webs *wp, char_t *path, char_t *query);

/*
    URL handler structure. Stores the leading URL path and the handler function to call when the URL path is seen.
 */ 
typedef struct WebsHandler {
    WebsHandlerProc handler;
    char_t          *dir;                   /**< Web directory if required */
    char_t          *prefix;                /**< URL leading prefix */
    ssize           len;                    /**< Length of prefix for speed */
    int             arg;                    /**< Argument to provide to handler */
    int             flags;                  /**< Flags */
} WebsHandler;

/* 
    Error code list
 */
typedef struct WebsError {
    int     code;                           /* HTTP error code */
    char_t  *msg;                           /* HTTP error message */
} WebsError;

/* 
    Mime type list
 */
typedef struct WebsMime {
    char_t  *type;                          /* Mime type */
    char_t  *ext;                           /* File extension */
} WebsMime;

/*
    File information structure.
 */
typedef struct WebsFileInfo {
    ulong           size;                   /* File length */
    int             isDir;                  /* Set if directory */
    time_t          mtime;                  /* Modified time */
} WebsFileInfo;

/*
    Compiled Rom Page Index
 */
typedef struct WebsRomIndex {
    char_t          *path;                  /* Web page URL path */
    uchar           *page;                  /* Web page data */
    int             size;                   /* Size of web page in bytes */
    WebsFilePos     pos;                    /* Current read position */
} WebsRomIndex;

/*
    Globals
 */
#if BIT_ROM
    extern WebsRomIndex websRomPageIndex[];
#endif

/**
    Decode base 64 blocks up to a NULL or equals
 */
#define WEBS_DECODE_TOKEQ 1

extern int websAccept(int sid, char *ipaddr, int port, int listenSid);
extern int websAlloc(int sid);
extern char_t *websCalcNonce(Webs *wp);
extern char_t *websCalcOpaque(Webs *wp);
extern char_t *websCalcDigest(Webs *wp);
extern char_t *websCalcUrlDigest(Webs *wp);
extern int websCgiHandler(Webs *wp, char_t *prefix, char_t *dir, int arg);
extern void websCgiCleanup();
extern int websCheckCgiProc(int handle);
extern void websClose();
extern void websCloseListen(int sock);
extern char_t *websDecode64(char_t *string);
extern char_t *websDecode64Block(char_t *s, ssize *len, int flags);
extern void websDecodeUrl(char_t *token, char_t *decoded, ssize len);
extern void websFileOpen();
extern void websFileClose();
extern int websFileHandler(Webs *wp, char_t *prefix, char_t *dir, int arg);
extern int websHomePageHandler(Webs *wp, char_t *prefix, char_t *dir, int arg);
extern void websDone(Webs *wp, int code);
extern char_t *websEncode64(char_t *string);
extern char_t *websEncode64Block(char_t *s, ssize len);
extern char *websEscapeHtml(cchar *html);
extern void websError(Webs *wp, int code, char_t *msg, ...);
extern char_t *websErrorMsg(int code);
extern int websEval(char_t *cmd, char_t **rslt, void *chan);
extern void websProcClose();
extern int websProcDefine(char_t *name, void *proc);
extern int websProcHandler(Webs *wp, char_t *prefix, char_t *dir, int arg);
extern void websProcOpen();
extern void websFree(Webs *wp);
extern char_t *websGetCgiCommName();
extern char_t *websGetDateString(WebsFileInfo *sbuf);
extern char_t *websGetDocuments();
extern char_t *websGetIndex();
extern void websSetDocuments(char_t *dir);
extern void websSetIndex(char_t *page);
extern char_t *websGetHostUrl();
extern char_t *websGetIpAddrUrl();
extern char_t *websGetPassword();
extern char_t *websGetPublishDir(char_t *path, char_t **prefix);
extern char_t *websGetRealm();
extern ssize websGetRequestBytes(Webs *wp);
extern char_t *websGetRequestDir(Webs *wp);
extern int websGetRequestFlags(Webs *wp);
extern char_t *websGetRequestIpAddr(Webs *wp);
extern char_t *websGetRequestFilename(Webs *wp);
extern char_t *websGetRequestPath(Webs *wp);
extern char_t *websGetRequestPassword(Webs *wp);
extern ssize websGetRequestWritten(Webs *wp);
extern char_t *websGetVar(Webs *wp, char_t *var, char_t *def);
extern int websCompareVar(Webs *wp, char_t *var, char_t *value);
extern int websLaunchCgiProc(char_t *cgiPath, char_t **argp, char_t **envp, char_t *stdIn, char_t *stdOut);
extern char *websMD5(char_t *s);
extern char *websMD5binary(char_t *buf, ssize length, char_t *prefix);
extern char_t *websNormalizeUriPath(char_t *path);
extern int websOpen(char_t *documents, char_t *authPath);
extern int websListen(char *endpoint);
extern void websPageClose(Webs *wp);
extern int websPageIsDirectory(char_t *filename);
extern int websPageOpen(Webs *wp, char_t *filename, char_t *path, int mode, int perm);
extern ssize websPageReadData(Webs *wp, char *buf, ssize nBytes);
extern void websPageSeek(Webs *wp, WebsFilePos offset);
extern int websPageStat(Webs *wp, char_t *filename, char_t *path, WebsFileInfo *sbuf);
extern int websPublish(char_t *prefix, char_t *path);
extern void websRedirect(Webs *wp, char_t *url);
extern void websResponse(Webs *wp, int code, char_t *msg, char_t *redirect);
extern void websRewriteRequest(Webs *wp, char_t *url);
extern int websRomOpen();
extern void websRomClose();
extern int websRomPageOpen(Webs *wp, char_t *path, int mode, int perm);
extern void websRomPageClose(int fd);
extern ssize websRomPageReadData(Webs *wp, char *buf, ssize len);
extern int websRomPageStat(char_t *path, WebsFileInfo *sbuf);
extern long websRomPageSeek(Webs *wp, WebsFilePos offset, int origin);
extern void websSetEnv(Webs *wp);
extern void websSetHost(char_t *host);
extern void websSetIpAddr(char_t *ipaddr);
extern void websSetRequestFilename(Webs *wp, char_t *filename);
extern void websSetRequestPath(Webs *wp, char_t *dir, char_t *path);
//  MOB - do all these APIs exist?
extern char_t *websGetRequestUserName(Webs *wp);
extern void websServiceEvents(int *finished);
extern void websSetCookie(Webs *wp, char_t *name, char_t *value, char_t *path, char_t *domain, time_t lifespan, int flags);
extern void websSetRequestWritten(Webs *wp, ssize written);
extern void websSetTimeMark(Webs *wp);
extern void websSetVar(Webs *wp, char_t *var, char_t *value);
extern int websTestVar(Webs *wp, char_t *var);
extern void websTimeout(void *arg, int id);
extern void websTimeoutCancel(Webs *wp);
extern int websUrlHandlerDefine(char_t *prefix, char_t *dir, int arg, WebsHandlerProc handler, int flags);
extern void websUrlHandlerClose();
extern int websUrlHandlerDelete(WebsHandlerProc handler);
extern int websUrlHandlerOpen();
extern void websHandleRequest(Webs *wp);
extern int websUrlParse(char_t *url, char_t **buf, char_t **host, char_t **path, char_t **port, char_t **query, char_t **proto, char_t **tag, char_t **ext);
extern void websWriteHeaders(Webs *wp, int code, ssize contentLength, char_t *redirect);
extern ssize websWriteHeader(Webs *wp, char_t *fmt, ...);
extern ssize websWrite(Webs *wp, char_t *fmt, ...);
extern ssize websWriteBlock(Webs *wp, char_t *buf, ssize nChars);
extern ssize websWriteDataNonBlock(Webs *wp, char *buf, ssize nChars);
extern bool websValid(Webs *wp);
extern bool websComplete(Webs *wp);
extern int websGetBackground();
extern void websSetBackground(int on);
extern int websGetDebug();
extern void websSetDebug(int on);
extern void websReadEvent(Webs *wp);

#if BIT_UPLOAD
extern int websProcessUploadData(Webs *wp);
extern void websFreeUpload(Webs *wp);
#endif
#if BIT_CGI
extern int websProcessCgiData(Webs *wp);
#endif
extern int websProcessPutData(Webs *wp);

#if BIT_JAVASCRIPT
extern void websJsClose();
extern int websJsDefine(char_t *name, int (*fn)(int ejid, Webs *wp, int argc, char_t **argv));
extern int websJsOpen();
extern int websJsRequest(Webs *wp, char_t *filename);
extern int websJsWrite(int ejid, Webs *wp, int argc, char_t **argv);
extern int websJsHandler(Webs *wp, char_t *prefix, char_t *dir, int arg);
#endif

/*************************************** SSL ***********************************/

#if BIT_PACK_SSL
extern int sslOpen();
extern void sslClose();
extern int sslAccept(Webs *wp);
extern void sslFree(Webs *wp);
extern int sslUpgrade(Webs *wp);
extern ssize sslRead(Webs *wp, void *buf, ssize len);
extern ssize sslWrite(Webs *wp, void *buf, ssize len);
extern void sslWriteClosureAlert(Webs *wp);
extern ssize sslFlush(Webs *wp);
#endif /* BIT_PACK_SSL */

/*************************************** Route *********************************/

typedef void (*WebsAskLogin)(Webs *wp);
typedef bool (*WebsVerify)(Webs *wp);
typedef bool (*WebsParseAuth)(Webs *wp);

typedef struct WebsRoute {
    char           *prefix;
    ssize          prefixLen;
    WebsAskLogin   askLogin;
    WebsParseAuth  parseAuth;              /* Basic or Digest */
    WebsVerify     verify;                 /* Pam or internal */
    WebsHash       abilities;
    char_t         *loginPage;
    char_t         *loggedInPage;
    char_t         *authType;
    int            flags;
} WebsRoute;

extern void websCloseRoute();
extern int websOpenRoute(char_t *path);
extern WebsRoute *websAddRoute(char_t *type, char_t *name, char_t *abilities, char_t *redirect, 
        WebsAskLogin login, WebsParseAuth parseAuth, WebsVerify verify);
extern int websRemoveRoute(char_t *uri);
extern bool websRouteRequest(Webs *wp);

/*************************************** Auth **********************************/
#define WEBS_USIZE          128              /* Size of realm:username */

typedef struct WebsUser {
    char_t  *name;
    char_t  *password;
    char_t  *roles;
    WebsHash  abilities;
} WebsUser;

typedef struct WebsRole {
    WebsHash  abilities;
} WebsRole;

extern WebsUser *websAddUser(char_t *username, char_t *password, char_t *roles);
extern int websRemoveUser(char_t *name);
extern int websSetUserRoles(char_t *username, char_t *roles);
extern WebsUser *websLookupUser(char *username);
extern bool websCan(Webs *wp, WebsHash ability);
extern bool websCanString(Webs *wp, char *ability);
extern int websAddRole(char_t *role, char_t *abilities);
extern int websRemoveRole(char_t *role);

extern bool websLoginUser(Webs *wp, char_t *username, char_t *password);
extern bool websAuthenticate(Webs *wp);

extern void websCloseAuth();
extern int websOpenAuth();
extern void websComputeAllUserAbilities();

extern void websBasicLogin(Webs *wp);
extern bool websParseBasicDetails(Webs *wp);
extern void websFormLogin(Webs *wp);
extern bool websVerifyUser(Webs *wp);

#if BIT_HAS_PAM && BIT_PAM
extern bool websVerifyPamUser(Webs *wp);
#endif

#if BIT_DIGEST
extern void websDigestLogin(Webs *wp);
extern bool websParseDigestDetails(Webs *wp);
#endif

/************************************** Sessions *******************************/

typedef struct WebsSession {
    char            *id;                    /**< Session ID key */
    time_t          lifespan;               /**< Session inactivity timeout (msecs) */
    time_t          expires;                /**< When the session expires */
    WebsHash        cache;                  /**< Cache of session variables */
} WebsSession;

extern WebsSession *websAllocSession(Webs *wp, char_t *id, time_t lifespan);
extern WebsSession *websGetSession(Webs *wp, int create);
extern char_t *websGetSessionVar(Webs *wp, char_t *name, char_t *defaultValue);
extern void websRemoveSessionVar(Webs *wp, char_t *name);
extern int websSetSessionVar(Webs *wp, char_t *name, char_t *value);
extern char *websGetSessionID(Webs *wp);

/************************************ Legacy **********************************/

#if BIT_LEGACY
//  MOB ORDER
    typedef wchar char_t;
    typedef unsigned wchar uchar_t;

    #define a_assert gassert
    typedef WebsStat gstat_t;
    #define emfSchedProc WebsCallback
    #define emfSchedCallback gschedCallback
    #define emfUnschedCallback gunschedCallback
    #define emfReschedCallback greschedCallback
    #define emfSchedProcess grunCallbacks

    #define hAlloc gAlloc
    #define hAllocEntry gAllocEntry
    #define hFree gFree

    #define ascToUni guni
    #define uniToAsc gasc

    #define WEBS_NAME "Server: GoAhead/" BIT_VERSION
    #define B_L 0

    #define bopen gopenAlloc
    #define bclose gcloseAlloc
    #define bstrdupNoBalloc gstrdupNoAlloc
    #define bstrdupANoBalloc gstrdupANoAlloc
    #define balloc galloc
    #define bfree(loc, p) gfree(p)
    #define bfreeSafe(loc, p) gfree(p)
    #define brealloc grealloc
    #define bstrdup gstrdup
    #define bstrdupA gstrdupA

    #define strlower gstrlower
    #define strupper gstrupper
    #define stritoa gstritoa
    #define WEBS_ASP WEBS_JS

    #define fmtValloc gfmtValloc
    #define fmtAlloc gfmtAlloc
    #define fmtStatic gfmtStatic

    #define websAspClose websJsClose
    #define websAspDefine websJsDefine
    #define websAspOpen websJsOpen
    #define websAspRequest websJsRequest

    #define websGetDefaultDir websGetDocuments
    #define websGetDefaultPage websGetIndex
    #define websSetDefaultDir websSetDocuments
    #define websSetDefaultPage websGetIndex
    #define websSetRequestLpath websSetRequestFilename
    #define websGetRequestLpath websGetRequestFilename
    #define websFormDefine websProcDefine

    typedef Webs WebsRec;
    typedef Webs websType;
    typedef Webs *webs_t;
    typedef WebsHash sym_fd_t;
    typedef WebsKey WebsKey;
    typedef WebsFormProc WebsProc;

    typedef WebsHandler websUrlHandlerType;
    typedef WebsError websErrorType;
    typedef WebsMime websMimeType;
    typedef WebsFileInfo websStatType;
#if BIT_ROM
    typedef WebsRomIndex websRomPageIndexType;
#endif
    extern void websHeader(Webs *wp);
    extern void websFooter(Webs *wp);
#endif

#ifdef __cplusplus
}
#endif
#endif /* _h_GOAHEAD */

/*
    @copy   default

    Copyright (c) Embedthis Software LLC, 2003-2012. All Rights Reserved.

    This software is distributed under commercial and open source licenses.
    You may use the Embedthis GoAhead open source license or you may acquire 
    a commercial license from Embedthis Software. You agree to be fully bound
    by the terms of either license. Consult the LICENSE.md distributed with
    this software for full details and other copyrights.

    Local variables:
    tab-width: 4
    c-basic-offset: 4
    End:
    vim: sw=4 ts=4 expandtab

    @end
 */
