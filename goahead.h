/*
    goahead.h -- GoAhead Web Server Header
  
    Copyright (c) All Rights Reserved. See details at the end of the file.
 */

/**
    @file goahead.h
    GoAhead is a tiny, simple web server. Yes it supports HTTP/1.1 and a simple
    server-side JavaScript expression language.
 */

#ifndef _h_GOAHEAD
#define _h_GOAHEAD 1

/************************************ Defaults ********************************/

#include    "bit.h"

#ifndef BIT_DEBUG
    #define BIT_DEBUG 0                 /**< Enable a debug build */
#endif
#ifndef BIT_ASSERT
    #if BIT_DEBUG
        #define BIT_ASSERT 1            /**< Turn debug assertions on */
    #else
        #define BIT_ASSERT 0
    #endif
#endif
#ifndef BIT_FLOAT
    #define BIT_FLOAT 1                 /**< Build with floating point support */
#endif
#ifndef BIT_ROM
    #define BIT_ROM 0                   /**< Build for execute from ROM */
#endif

/********************************* CPU Families *******************************/
/*
    CPU Architectures
 */
#define BIT_CPU_UNKNOWN     0
#define BIT_CPU_ARM         1           /**< Arm */
#define BIT_CPU_ITANIUM     2           /**< Intel Itanium */
#define BIT_CPU_X86         3           /**< X86 */
#define BIT_CPU_X64         4           /**< AMD64 or EMT64 */
#define BIT_CPU_MIPS        5           /**< Mips */
#define BIT_CPU_PPC         6           /**< Power PC */
#define BIT_CPU_SPARC       7           /**< Sparc */

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
    Unicode 
 */
#ifndef BIT_CHAR_LEN
    #define BIT_CHAR_LEN 1
#endif
#if BIT_CHAR_LEN == 4
    typedef int wchar;
    #define TT(s) L ## s
    #define UNICODE 1
#elif BIT_CHAR_LEN == 2
    typedef short wchar;
    #define TT(s) L ## s
    #define UNICODE 1
#else
    typedef char wchar;
    #define TT(s) s
#endif
    #define TSZ(b) (sizeof(b) / sizeof(wchar))
    #define T(s) s

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
    error("Windows CE support is not yet complete for GoAhead 3.x")
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
    #include    <libgen.h>
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
    #include    <libgen.h>
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
    #define access      _access
    #define chdir       _chdir
    #define chmod       _chmod
    #define close       _close
    #define fileno      _fileno
    #define fstat       _fstat
    #define getch       _getch
    #define getcwd      _getcwd
    #define getpid      _getpid
    #define gettimezone _gettimezone
    #define lseek       _lseek
    #define mkdir(a,b)  _mkdir(a)
    #define open        _open
    #define putenv      _putenv
    #define read        _read
    #define rmdir(a)    _rmdir(a)
    #define stat        _stat
    #define strdup      _strdup
    #define tempnam     _tempnam
    #define umask       _umask
    #define unlink      _unlink
    #define write       _write
    extern void sleep(int secs);
    extern int _getpid();
    extern int _getch();
#endif

/**
    Signed file offset data type. Supports large files greater than 4GB in size on all systems.
 */
typedef int64 WebsFilePos;

/**
    Date and time storage with millisecond resolution.
  */
typedef int64 WebsDateTime;

#if VXWORKS
    typedef int WebsSockLenArg;
#else
    typedef socklen_t WebsSockLenArg;
#endif

#if WINDOWS || DOXYGEN
    typedef int socklen_t;
#endif

#if VXWORKS
    #define fcntl(a, b, c)
    #define chdir vxchdir
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


#if !LINUX
    extern char *basename(char *name);
#endif

#if VXWORKS
    extern int vxchdir(char *dirname);
    extern char *tempnam(char *dir, char *pfx);
#endif

/**
    File status structure
 */
typedef struct stat WebsStat;

/*
    Copyright. The software license requires that this not be modified or removed.
 */
#define EMBEDTHIS_GOAHEAD_COPYRIGHT \
    "Copyright (c) Embedthis Software Inc., 1993-2012. All Rights Reserved." \
    "Copyright (c) GoAhead Software Inc., 2003. All Rights Reserved."

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
#elif BIT_WIN_LIKE
    #define MAIN(name, _argc, _argv, _envp)  \
        APIENTRY WinMain(HINSTANCE inst, HINSTANCE junk, char *command, int junk2) { \
            extern int main(); \
            char *largv[BIT_MAX_ARGC]; \
            int largc; \
            largc = websParseArgs(command, &largv[1], BIT_MAX_ARGC - 1); \
            largv[0] = #name; \
            main(largc, largv, NULL); \
        } \
        int main(_argc, _argv, _envp)
#else
    #define MAIN(name, _argc, _argv, _envp) int main(_argc, _argv, _envp)
#endif

extern int websParseArgs(char *args, char **argv, int maxArgc);

#if WINDOWS
    extern void websSetInst(HINSTANCE inst);
    extern HINSTANCE websGetInst();
#endif

/************************************ Tunables ********************************/

#define WEBS_MAX_LISTEN     8           /**< Maximum number of listen endpoints */
#define WEBS_SMALL_HASH     31          /**< General small hash size */

/************************************* Error **********************************/

#define WEBS_L                 __FILE__, __LINE__
#define WEBS_ARGS_DEC          char *file, int line
#define WEBS_ARGS              file, line

/*
    Log level flags
 */
#define WEBS_LOG_RAW        0x1000
#define WEBS_LOG_NEWLINE    0x2000
#define WEBS_LOG_MASK       0xF

#if BIT_DEBUG
    #define gassert(C)     if (C) ; else gassertError(WEBS_L, "%s", #C)
    extern void gassertError(WEBS_ARGS_DEC, char *fmt, ...);
#else
    #define gassert(C)     if (1) ; else
#endif

/*
    Optimized logging calling sequence. This compiles out for release mode.
 */
#if BIT_DEBUG
    #define LOG trace
#else
    #define LOG if (0) trace
#endif

/**
    Open the trace logging module
    @return Zero if successful
    @internal
 */
extern int traceOpen();

/**
    Close the trace logging module
    @internal
 */
extern void traceClose();

/**
    Callback for emitting trace log output
    @param level Integer between 0 and 9. Zero is the lowest trace level used for the most important messages.
    @param msg Message to log
    @return Zero if successful
    @internal
 */
typedef void (*WebsTraceHandler)(int level, char *msg);

/**
    Set a trace callback
    @param handler Callback handler function of type WebsTraceHandler
    @return The previous callback function
 */
extern WebsTraceHandler traceSetHandler(WebsTraceHandler handler);

/**
    Set the filename to save logging output
    @param path Filename path to use
 */
extern void traceSetPath(char *path);

/**
    Open the trace logging module
    @return Zero if successful
    @internal
*/
extern void error(char *fmt, ...);

/**
    Emit trace a
    @description This emits a message at the specified level. GoAhead filters logging messages by defining a verbosity
    level at startup. Level 0 is the least verbose where only the most important messages will be output. Level 9 is the
    most verbose. Level 2-4 are the most useful for debugging.
    @param level Integer verbosity level (0-9).
    @param fmt Printf style format string
    @param ... Arguments for the format string
 */
extern void trace(int level, char *fmt, ...);

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

/************************************* WebsValue ******************************/
/**
    Value types.
 */
typedef enum WebsType {
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
} WebsType;

/**
    System native time type
 */
typedef time_t WebsTime;

/**
    Value union to store primitive value types
 */
typedef struct WebsValue {
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
        char    *string;
        char    *bytes;
        char    *errmsg;
        void    *symbol;
    } value;
    WebsType    type;
    uint        valid       : 8;
    uint        allocated   : 8;        /* String was allocated */
} WebsValue;

/**
    The value is a numeric type
 */
#define value_numeric(t)    (t >= byteint && t <= big)

/**
    The value is a string type
 */
#define value_str(t)        (t >= string && t <= bytes)

/**
    The value is valid supported type
 */
#define value_ok(t)         (t > undefined && t <= symbol)

/**
    Allocate strings using malloc
 */
#define VALUE_ALLOCATE      0x1

#if UNUSED && KEEP
/**
    Static definition of a valid value (Uses an integer of value 1)
 */
#define VALUE_VALID         { {0}, integer, 1 }

/**
    Static definition of an invalid value
 */
#define VALUE_INVALID       { {0}, undefined, 0 }
#endif

/**
    Create an integer value
    @param value Integer long value
    @return Value object containing the integer
 */
extern WebsValue valueInteger(long value);

/**
    Create an string value
    @param value String long value
    @param flags Set to VALUE_ALLOCATE to store a copy of the string reference
    @return Value object containing the string
 */
extern WebsValue valueString(char *value, int flags);

/**
    Create an symbol value containing an object reference
    @param value Value reference
    @return Value object containing the symbol reference
 */
extern WebsValue valueSymbol(void *value);

#if UNUSED
/**
    Create an  value
    @param value Integer long value
    @return Value object containing the integer
 */
extern WebsValue valueErrmsg(char *value);
#endif

/**
    Free any allocated string in a value
    @param value Value object
 */
extern void valueFree(WebsValue *value);

/************************************* Ringq **********************************/
/**
    A WebsBuf (ring queue) allows maximum utilization of memory for data storage and is
    ideal for input/output buffering. This module provides a highly effecient
    implementation and a vehicle for dynamic strings.
    \n\n
    WARNING:  This is a public implementation and callers have full access to
    the queue structure and pointers.  Change this module very carefully.
    \n\n
    This module follows the open/close model.
    \n\n
    Operation of a WebsBuf where bp is a pointer to a WebsBuf :
  
        bp->buflen contains the size of the buffer.
        bp->buf will point to the start of the buffer.
        bp->servp will point to the first (un-consumed) data byte.
        bp->endp will point to the next free location to which new data is added
        bp->endbuf will point to one past the end of the buffer.
    \n\n
    Eg. If the WebsBuf contains the data "abcdef", it might look like :
    \n\n
    +-------------------------------------------------------------------+
    |   |   |   |   |   |   |   | a | b | c | d | e | f |   |   |   |   |
    +-------------------------------------------------------------------+
      ^                           ^                       ^               ^
      |                           |                       |               |
    bp->buf                    bp->servp               bp->endp      bp->enduf
    \n\n
    The queue is empty when servp == endp.  This means that the queue will hold
    at most bp->buflen -1 bytes.  It is the fillers responsibility to ensure
    the WebsBuf is never filled such that servp == endp.
    \n\n
    It is the fillers responsibility to "wrap" the endp back to point to
    bp->buf when the pointer steps past the end. Correspondingly it is the
    consumers responsibility to "wrap" the servp when it steps to bp->endbuf.
    The bufPutc and bufGetc routines will do this automatically.
    @defgroup WebsBuf WebsBuf
 */
typedef struct WebsBuf {
    char    *buf;               /**< Holding buffer for data */
    char    *servp;             /**< Pointer to start of data */
    char    *endp;              /**< Pointer to end of data */
    char    *endbuf;            /**< Pointer to end of buffer */
    ssize   buflen;             /**< Length of ring queue */
    ssize   maxsize;            /**< Maximum size */
    int     increment;          /**< Growth increment */
} WebsBuf;

/**
    Create a buffer
    @param bp Buffer reference
    @param increment Incremental size to grow the buffer. This will be increased by a power of two each time
        the buffer grows.
    @param maxsize Maximum size of the buffer
    @return Zero if successful
    @ingroup WebsBuf
 */
extern int bufCreate(WebsBuf *bp, int increment, int maxsize);

/**
    Free allocated storage for the buffer
    @param bp Buffer reference
    @return Zero if successful
    @ingroup WebsBuf
 */
extern void bufFree(WebsBuf *bp);

/**
    Get the length of available data in the buffer
    @param bp Buffer reference
    @return Size of available data in bytes
    @ingroup WebsBuf
 */
extern ssize bufLen(WebsBuf *bp);

/**
    Append a character to the buffer at the endp position and increment the endp
    @param bp Buffer reference
    @param c Character to append
    @return Zero if successful
    @ingroup WebsBuf
 */
extern int bufPutc(WebsBuf *bp, char c);

/**
    Insert a character to the buffer before the servp position and decrement the servp
    @param bp Buffer reference
    @param c Character to insert
    @return Zero if successful
    @ingroup WebsBuf
 */
extern int bufInsertc(WebsBuf *bp, char c);

/**
    Append a string to the buffer at the endp position and increment the endp
    @param bp Buffer reference
    @param str String to append
    @return Count of characters appended. Returns negative if there is an allocation error.
    @ingroup WebsBuf
 */
extern ssize bufPutStr(WebsBuf *bp, char *str);

/**
    Get a character from the buffer and increment the servp
    @param bp Buffer reference
    @return The next character or -1 if the buffer is empty
    @ingroup WebsBuf
 */
extern int bufGetc(WebsBuf *bp);

/**
    Grow the buffer by at least the required amount of room
    @param bp Buffer reference
    @param room Available size required after growing the buffer 
    @return True if the buffer can be grown to have the required amount of room.
    @ingroup WebsBuf
 */
extern bool bufGrow(WebsBuf *bp, ssize room);

/**
    Put a block to the buffer.
    @param bp Buffer reference
    @param blk Block to append to the buffer
    @param len Size of the block
    @return Length of data appended. Should equal len.
    @ingroup WebsBuf
 */
extern ssize bufPutBlk(WebsBuf *bp, char *blk, ssize len);

/**
    Determine the room available in the buffer. 
    @description This returns the maximum number of bytes the buffer can absorb in a single block copy.
    @param bp Buffer reference
    @return Number of bytes of availble space. 
    @ingroup WebsBuf
 */
extern ssize bufRoom(WebsBuf *bp);

/**
    Adjust the endp pointer by the specified size.
    @description This is useful after manually copying data into the buffer and needing to adjust the end pointer.
    @param bp Buffer reference
    @param size Size of adjustment. May be positive or negative value.
    @ingroup WebsBuf
 */
extern void bufAdjustEnd(WebsBuf *bp, ssize size);

/**
    Copy a block of from the buffer and adjust the servp.
    @param bp Buffer reference
    @param blk Block into which to place the data
    @param len Length of the block
    @return Number of bytes copied. 
    @ingroup WebsBuf
 */
extern ssize bufGetBlk(WebsBuf *bp, char *blk, ssize len);

/**
    Return the maximum number of bytes the buffer can provide via a single block copy. 
    @description Useful if the user is doing their own data retrieval. 
    @param bp Buffer reference
    @return Number of bytes available for copying.
    @ingroup WebsBuf
 */
extern ssize bufGetBlkMax(WebsBuf *bp);

/**
    Adjust the start (servp) reference
    @param bp Buffer reference
    @param count Number of bytes to adjust
    @ingroup WebsBuf
 */
extern void bufAdjustStart(WebsBuf *bp, ssize count);

/**
    Flush all data in the buffer and reset the pointers.
    @param bp Buffer reference
    @ingroup WebsBuf
 */
extern void bufFlush(WebsBuf *bp);

/**
    Compact the data in the buffer and move to the start of the buffer
    @param bp Buffer reference
    @ingroup WebsBuf
 */
extern void bufCompact(WebsBuf *bp);

/**
    Reset the buffer pointers to the start of the buffer if empty
    @param bp Buffer reference
    @ingroup WebsBuf
 */
extern void bufReset(WebsBuf *bp);

/**
    Add a trailing null to the buffer. The end pointer is not changed.
    @param bp Buffer reference
    @ingroup WebsBuf
 */
extern void bufAddNull(WebsBuf *bp);

/******************************* Malloc Replacement ***************************/
#if BIT_REPLACE_MALLOC
/**
    GoAhead allocator memory block 
    Memory block classes are: 16, 32, 64, 128, 256, 512, 1024, 2048, 4096, 8192, 16384, 32768, 65536.
    @defgroup WebsAlloc WebsAlloc
 */
typedef struct WebsAlloc {
    union {
        void    *next;                          /**< Pointer to next in q */
        int     size;                           /**< Actual requested size */
    } u;
    int         flags;                          /**< Per block allocation flags */
} WebsAlloc;

#define WEBS_DEFAULT_MEM   (64 * 1024)         /**< Default memory allocation */
#define WEBS_MAX_CLASS     13                  /**< Maximum class number + 1 */
#define WEBS_SHIFT         4                   /**< Convert size to class */
#define WEBS_ROUND         ((1 << (B_SHIFT)) - 1)
#define WEBS_MALLOCED      0x80000000          /* Block was malloced */
#define WEBS_FILL_CHAR     (0x77)              /* Fill byte for buffers */
#define WEBS_FILL_WORD     (0x77777777)        /* Fill word for buffers */

/*
    Flags. The integrity value is used as an arbitrary value to fill the flags.
 */
#define WEBS_USE_MALLOC        0x1             /**< Okay to use malloc if required */
#define WEBS_USER_BUF          0x2             /* User supplied buffer for mem */
#define WEBS_INTEGRITY         0x8124000       /* Integrity value */
#define WEBS_INTEGRITY_MASK    0xFFFF000       /* Integrity mask */

/**
    Close the GoAhead memory allocator
    @ingroup WebsAlloc
 */
extern void gcloseAlloc();

/**
    Initialize the galloc module. 
    @description The gopenAlloc function should be called the very first thing after the application starts and gclose
    should be called the last thing before exiting. If gopenAlloc is not called, it will be called on the first allocation
    with default values. "buf" points to memory to use of size "bufsize". If buf is NULL, memory is allocated using malloc.
    flags may be set to WEBS_USE_MALLOC if using malloc is okay. This routine will allocate *  an initial buffer of size
    bufsize for use by the application. 
    @param buf Optional user supplied block of memory to use for allocations
    @param bufsize Size of buf
    @param flags Allocation flags. Set to WEBS_USE_MALLOC to permit the use of malloc() to grow memory.
    @return Zero if successful, otherwise -1.
    @ingroup WebsAlloc
 */
extern int gopenAlloc(void *buf, int bufsize, int flags);

/**
    Allocate a block of the requested size
    @param size Memory size required
    @return A reference to the allocated block 
    @ingroup WebsAlloc
 */
extern void *galloc(ssize size);

/**
    Free an allocated block of memory
    @param blk Reference to the memory block to free.
    @ingroup WebsAlloc
 */
extern void gfree(void *blk);

/**
    Reallocate a block of memory and grow its size
    @description If the new size is larger than the existing block, a new block will be allocated and the old data
        will be copied to the new block.
    @param blk Original block reference
    @param newsize Size of the new block. 
    @return Reference to the new memory block
    @ingroup WebsAlloc
 */
extern void *grealloc(void *blk, ssize newsize);

#else /* !BIT_REPLACE_MALLOC */

    #define WEBS_SHIFT 4
    #define galloc(num) malloc(num)
    #define gfree(p) if (p) { free(p); } else
    #define grealloc(p, num) realloc(p, num)
#endif /* BIT_REPLACE_MALLOC */

//  FUTURE DOC
extern ssize mtow(wchar *dest, ssize count, char *src, ssize len);
extern ssize wtom(char *dest, ssize count, wchar *src, ssize len);
extern wchar *amtow(char *src, ssize *len);
extern char  *awtom(wchar *src, ssize *len);

/******************************* Hash Table *********************************/
/**
    Hash table entry structure.
    @description The hash structure supports growable hash tables with high performance, collision resistant hashes.
    Each hash entry has a descriptor entry. This is used to manage the hash table link chains.
    @see hashCreate hashFree hashLookup hashEnter hashDelete hashWalk hashFirst hashNext
    @defgroup WebsHash WebsHash
 */
typedef struct WebsKey {
    struct WebsKey  *forw;                  /* Pointer to next hash list */
    WebsValue       name;                   /* Name of symbol */
    WebsValue       content;                /* Value of symbol */
    int             arg;                    /* Parameter value */
    int             bucket;                 /* Bucket index */
} WebsKey;

/**
    Hash table ID returned by hashCreate
 */
typedef int WebsHash;                       /* Returned by symCreate */

/**
    Create a hash table
    @param size Minimum size of the hash index
    @return Hash table ID
    @ingroup WebsHash
 */
extern WebsHash hashCreate(int size);

/**
    Free a hash table
    @param id Hash table id returned by hashCreate
    @ingroup WebsHash
 */
extern void hashFree(WebsHash id);

/**
    Lookup a name in the hash table
    @param id Hash table id returned by hashCreate
    @param name Key name to search for 
    @return Reference to the WebKey object storing the key and value
    @ingroup WebsHash
 */
extern WebsKey *hashLookup(WebsHash id, char *name);

/**
    Enter a new key and value into the hash table
    @param id Hash table id returned by hashCreate
    @param name Key name to create
    @param value Key value to enter
    @param arg Optional extra argument to store with the value
    @return Reference to the WebKey object storing the key and value
    @ingroup WebsHash
 */
extern WebsKey *hashEnter(WebsHash id, char *name, WebsValue value, int arg);

/**
    Delete a key by name
    @param id Hash table id returned by hashCreate
    @param name Key name to delete
    @return Zero if the delete was successful. Otherwise -1 if the key was not found.
    @ingroup WebsHash
 */
extern int hashDelete(WebsHash id, char *name);

/**
    Start walking the hash keys by returning the first key entry in the hash
    @param id Hash table id returned by hashCreate
    @return Reference to the first WebKey object. Return null if there are no keys in the hash.
    @ingroup WebsHash
 */
extern WebsKey *hashFirst(WebsHash id);

/**
    Continue walking the hash keys by returning the next key entry in the hash
    @param id Hash table id returned by hashCreate
    @param last Reference to a WebsKey to hold the current traversal key state.
    @return Reference to the next WebKey object. Returns null if no more keys exist to be traversed.
    @ingroup WebsHash
 */
extern WebsKey *hashNext(WebsHash id, WebsKey *last);

/************************************ Socket **********************************/
/*
    Socket flags 
 */
#define SOCKET_EOF              0x1     /**< Seen end of file */
#define SOCKET_CONNECTING       0x2     /**< Connect in progress */
#define SOCKET_PENDING          0x4     /**< Message pending on this socket */
#define SOCKET_RESERVICE        0x8     /**< Socket needs re-servicing */
#define SOCKET_ASYNC            0x10    /**< Use async connect */
#define SOCKET_BLOCK            0x20    /**< Use blocking I/O */
#define SOCKET_LISTENING        0x40    /**< Socket is server listener */
#define SOCKET_CLOSING          0x80    /**< Socket is closing */
#define SOCKET_CONNRESET        0x100   /**< Socket connection was reset */
#define SOCKET_TRACED           0x200   /**< Trace TLS connections */

#define SOCKET_PORT_MAX         0xffff  /* Max Port size */

/*
    Socket error values
 */
#define SOCKET_WOULDBLOCK       1       /**< Socket would block on I/O */
#define SOCKET_RESET            2       /**< Socket has been reset */
#define SOCKET_NETDOWN          3       /**< Network is down */
#define SOCKET_AGAIN            4       /**< Issue the request again */
#define SOCKET_INTR             5       /**< Call was interrupted */
#define SOCKET_INVAL            6       /**< Invalid */

/*
    Handler event masks
 */
#define SOCKET_READABLE         0x2     /**< Make socket readable */ 
#define SOCKET_WRITABLE         0x4     /**< Make socket writable */
#define SOCKET_EXCEPTION        0x8     /**< Interested in exceptions */

/**
    Socket I/O callback
    @param sid Socket ID handle returned from socketConnect or when a new socket is passed to a SocketAccept
        callback..
    @param mask Mask of events of interest. Set to SOCKET_READABLE | SOCKET_WRITABLE | SOCKET_EXCEPTION.
    @param data Data argument to pass to the callback function.
    @ingroup WebsSocket
 */
typedef void (*SocketHandler)(int sid, int mask, void *data);

/**
    Socket accept callback
    @param sid Socket ID handle for the newly accepted socket
    @param ipaddr IP address of the connecting client. 
    @param port Port of the connecting client.
    @param listenSid Socket ID for the listening socket
    @ingroup WebsSocket
 */
typedef int (*SocketAccept)(int sid, char *ipaddr, int port, int listenSid);

/*
    Socket control structure
    @see socketAddress socketAddressIsV6 socketClose socketCloseConnection socketCreateHandler
    socketDeletehandler socketReservice socketEof socketGetPort socketInfo socketIsV6
    socketOpen socketListen socketParseAddress socketProcess socketRead socketWrite socketWriteString
    socketSelect socketGetHandle socketSetBlock socketGetBlock socketAlloc socketFree socketGetError
    socketPtr socketWaitForEvent socketRegisterInterest
    @defgroup WebsSocket WebsSocket
 */
typedef struct WebsSocket {
    WebsBuf         lineBuf;            /* Line ring queue */
    SocketAccept    accept;             /* Accept handler */
    SocketHandler   handler;            /* User I/O handler */
    char            *ip;                /* Server listen address or remote client address */
    void            *handler_data;      /* User handler data */
    int             handlerMask;        /* Handler events of interest */
    int             sid;                /* Index into socket[] */
    int             port;               /* Port to listen on */
    int             flags;              /* Current state flags */
    int             sock;               /* Actual socket handle */
    int             fileHandle;         /* ID of the file handler */
    int             interestEvents;     /* Mask of events to watch for */
    int             currentEvents;      /* Mask of ready events (FD_xx) */
    int             selectEvents;       /* Events being selected */
    int             saveMask;           /* saved Mask for socketFlush */
    int             error;              /* Last error */
    int             secure;             /* Socket is using SSL */
} WebsSocket;


/**
    List of open sockets
    @ingroup WebsSocket
 */
extern WebsSocket **socketList;         /* List of open sockets */

/**
    Extract the numerical IP address and port for the given socket info
    @param addr Reference to the socket address.
    @param addrlen Length of the socket address
    @param ipbuf Buffer to contain the parsed IP address
    @param ipLen Size of ipbuf
    @param port Reference to an integer to hold the parsed port.
    @return Zero if successful. Otherwise -1 for parse errors.
    @ingroup WebsSocket
 */
extern int socketAddress(struct sockaddr *addr, int addrlen, char *ipbuf, int ipLen, int *port);

/**
    Determine if an IP address is an IPv6 address.
    @param ip String IP address.
    @return True if the address is an IPv6 address.
    @ingroup WebsSocket
 */
extern bool socketAddressIsV6(char *ip);

/**
    Allocate a socket object
    @param host String host IP address.
    @param port Socket port
    @param accept Optional SocketAccept accept callback function
    @param flags Control flags
    @return Socket ID handle to use with other APIs.
    @ingroup WebsSocket
 */
extern int socketAlloc(char *host, int port, SocketAccept accept, int flags);

/**
    Close the socket module
    @ingroup WebsSocket
 */
extern void socketClose();

/**
    Close a socket connection
    @param sid Socket ID handle returned from socketConnect or socketAccept.
    @ingroup WebsSocket
 */
extern void socketCloseConnection(int sid);

/**
    Connect to a server and create a new socket
    @param host Host IP address.
    @param port Port number to connect to
    @param flags Set to SOCKET_BLOCK for blocking I/O. Otherwise non-blocking I/O is used.
    @return True if the address is an IPv6 address.
    @ingroup WebsSocket
    @internal
 */
extern int socketConnect(char *host, int port, int flags);

/**
    Create a socket handler that will be invoked when I/O events occur.
    @param sid Socket ID handle returned from socketConnect or socketAccept.
    @param mask Mask of events of interest. Set to SOCKET_READABLE | SOCKET_WRITABLE | SOCKET_EXCEPTION.
    @param handler Socket handler function.
    @param arg Arbitrary object reference to pass to the SocketHandler callback function.
    @return True if the address is an IPv6 address.
    @ingroup WebsSocket
 */
extern void socketCreateHandler(int sid, int mask, SocketHandler handler, void *arg);

/**
    Delete a socket handler created via socketCreateHandler
    @param sid Socket ID handle returned from socketConnect or socketAccept.
    @ingroup WebsSocket
 */
extern void socketDeleteHandler(int sid);

/**
    Determine if the socket is at end-of-file for input.
    @param sid Socket ID handle returned from socketConnect or socketAccept.
    @return True if the address is at EOF
    @ingroup WebsSocket
 */
extern bool socketEof(int sid);

/**
    Free (and close) the socket
    @param sid Socket ID handle returned from socketConnect or socketAccept.
    @ingroup WebsSocket
 */
extern void socketFree(int sid);

/**
    Get the current blocking mode
    @param sid Socket ID handle returned from socketConnect or socketAccept.
    @return True if the socket is in blocking mode.
    @ingroup WebsSocket
 */
extern int socketGetBlock(int sid);

/**
    Get the error code for the last socket operation on this thread.
    @return Integer error code. See errno or GetLastError() on windows.
    @ingroup WebsSocket
 */
extern int socketGetError();

/**
    Get the underlying socket operating system socket/file handle
    @param sid Socket ID handle returned from socketConnect or socketAccept.
    @return The integer socket handle
    @ingroup WebsSocket
 */
extern int socketGetHandle(int sid);

/**
    Get the IP port associated with this socket.
    @param sid Socket ID handle returned from socketConnect or socketAccept.
    @return The TCP/IP port for this socket
    @ingroup WebsSocket
 */
extern int socketGetPort(int sid);

/**
    Get a socket address structure for the specified IP:Port
    @description This returns address details in *family, *protocol, *addr, and *addrlen.
    @param ip IP address to parse
    @param port TCP/IP port number
    @param family Reference to an integer to hold the address family
    @param protocol Reference to an integer to hold the address protocol
    @param addr Reference to an integer to hold the address structure
    @param addrlen Reference to an integer to hold the address structure length
    @return Zero if successful, otherwise -1.
    @ingroup WebsSocket
 */
extern int socketInfo(char *ip, int port, int *family, int *protocol, struct sockaddr_storage *addr, 
    WebsSockLenArg *addrlen);

/**
    Determine if a socket is bound to an IPv6 address.
    @param sid Socket ID handle returned from socketConnect or socketAccept.
    @return True if the socket is using IPv6.
    @ingroup WebsSocket
 */
extern bool socketIsV6(int sid);

/**
    Open a listening socket
    @param host Host IP address on which to listen. Set to NULL to listen on all interfaces.
    @param port TCP/IP port on which to listen
    @param accept SocketAccept callback function to invoke to receive incoming connections.
    @param flags Reserved
    @return Zero if successful, otherwise -1.
    @ingroup WebsSocket
 */
extern int socketListen(char *host, int port, SocketAccept accept, int flags);

/**
    Open the socket module
    @return Zerof if successful, otherwise -1.
    @ingroup WebsSocket
 */
extern int socketOpen();

/**
    Parse an IP address into its constituent parts.
    @description Parse the IP address and return the IP address and port components. Handles ipv4 and ipv6 addresses.
    If the IP portion is absent, *pip is set to null. If the port portion is absent, port is set to the defaultPort.
    If a ":*" port specifier is used, *pport is set to -1;
    When an address contains an ipv6 port it should be written as
        aaaa:bbbb:cccc:dddd:eeee:ffff:gggg:hhhh:iiii
    or
        [aaaa:bbbb:cccc:dddd:eeee:ffff:gggg:hhhh:iiii]:port
    If supplied an IPv6 address, the backets are stripped in the returned IP address.
    @param ipAddrPort IP address which may contain an optional ":port" component. 
    @param pip Returns a reference to an allocated string containing the IP address portion. Caller must free.
    @param pport Reference to an integer to hold the port component.
    @param secure Reference to an integer to be set to true if the address is using SSL/TLS.
    @param defaultPort Default port number to use if no port specifier is included in ipAddrPort.
    @return Zero if successful, otherwise -1.
    @ingroup WebsSocket
 */
extern int socketParseAddress(char *ipAddrPort, char **pip, int *pport, int *secure, int defaultPort);

/**
    Process pending socket I/O events.
    @ingroup WebsSocket
    @internal
 */
extern void socketProcess();

/**
    Read data from a socket
    @param sid Socket ID handle returned from socketConnect or socketAccept.
    @param buf Buffer to hold read data
    @param len Size of the buffer
    @return Count of bytes actually read. Returns -1 for errors and EOF. Distinguish between errors and EOF
        via socketEof().
    @ingroup WebsSocket
 */
extern ssize socketRead(int sid, void *buf, ssize len);

/**
    Register interest in socket I/OEvents
    @param sp Socket object reference. Use socketPtr to obtain from a socket ID.
    @param mask Mask of events of interest. Set to SOCKET_READABLE | SOCKET_WRITABLE | SOCKET_EXCEPTION.
    @ingroup WebsSocket
 */
extern void socketRegisterInterest(WebsSocket *sp, int mask);

/**
    Request that the socket be reserviced.
    @description This routine is useful when upper layers have unprocessed, buffered data for the socket.
        This routine will cause the socket I/O callback handler to be invoked soon in the future.
    @param sid Socket ID handle returned from socketConnect or socketAccept.
    @ingroup WebsSocket
 */
extern void socketReservice(int sid);

/**
    Wait for I/O on a socket
    @description This call uses the mask of events of interest defined by socketRegisterInterest. It blocks the caller
        until a suitable I/O event or timeout occurs.
    @param sid Socket ID handle returned from socketConnect or socketAccept.
    @param timeout Timeout in milliseconds.
    @return Number of I/O events.
    @ingroup WebsSocket
 */
extern int socketSelect(int sid, int timeout);

/**
    Set the socket blocking mode
    @param sid Socket ID handle returned from socketConnect or socketAccept.
    @param on Set to 1 to enable blocking 
    @return The previous blocking mode
    @ingroup WebsSocket
 */
extern int socketSetBlock(int sid, int on);

/**
    Wait for a socket I/O event
    @param sp Socket object
    @param mask Mask of events of interest. Set to SOCKET_READABLE | SOCKET_WRITABLE | SOCKET_EXCEPTION.
    @return Zero if successful in waiting for the desired event, othewise return -1.
    @ingroup WebsSocket
 */
extern int socketWaitForEvent(WebsSocket *sp, int mask);

/**
    Write data to the socket
    @param sid Socket ID handle returned from socketConnect or socketAccept.
    @param buf Buffer containing data to write
    @param len Size of buf
    @return Count of bytes written. May be less than len if the socket is in non-blocking mode.
        Returns -1 for errors.
    @ingroup WebsSocket
 */
extern ssize socketWrite(int sid, void *buf, ssize len);

/**
    Return the socket object for the socket ID.
    @param sid Socket ID handle returned from socketConnect or socketAccept.
    @return Corresponding socket object.
    @ingroup WebsSocket
 */
extern WebsSocket *socketPtr(int sid);

/*********************************** Runtime **********************************/
/**
    GoAhead Web Server Runtime
    @description GoAhead provides a secure runtime environment for safe string manipulation and to 
    help prevent buffer overflows and other potential security traps.
    @defgroup WebsRuntime WebsRuntime
    @see fmt gallocHandle gallocObject gfreehandle hextoi itosbuf scaselesscmp scaselessmatch
    sclone scmp scopy sfmt sfmtv slen slower smatch sncaselesscmp sncmp sncopy stok strim supper
 */

/**
    Format a string into a static buffer.
    @description This call format a string using printf style formatting arguments. A trailing null will 
        always be appended. The call returns the size of the allocated string excluding the null.
    @param buf Pointer to the buffer.
    @param maxSize Size of the buffer.
    @param format Printf style format string
    @param ... Variable arguments to format
    @return Returns the buffer.
    @ingroup WebsRuntime
 */
extern char *fmt(char *buf, ssize maxSize, char *format, ...);

/**
    Allocate a handle from a map
    @param map Reference to a location holding the map reference. On the first call, the map is allocated.
    @return Integer handle index. Otherwise return -1 on allocation errors.
    @ingroup WebsRuntime
 */
extern int gallocHandle(void *map);

/**
    Allocate an object in a halloc map
    @param map Reference to a location holding the map reference. On the first call, the map is allocated.
    @param max Reference to an integer that holds the maximum handle in the map.
    @param size Size of the object to allocate.
    @return Integer handle index. Otherwise return -1 on allocation errors.
    @ingroup WebsRuntime
 */
extern int gallocObject(void *map, int *max, int size);

/**
    Free a handle in the map
    @param map Reference to a location to hold the map reference.
    @param handle Handle to free in the map.
    @return Integer handle index. Otherwise return -1 on allocation errors.
    @ingroup WebsRuntime
 */
extern int gfreeHandle(void *map, int handle);

/**
    Convert a hex string to an integer 
    @description This call converts the supplied string to an integer using base 16.
    @param str Pointer to the string to parse.
    @return Returns the integer equivalent value of the string. 
    @ingroup WebsRuntime
 */
extern uint hextoi(char *str);

/**
    Convert an integer to a string buffer.
    @description This call converts the supplied 64 bit integer into a string formatted into the supplied buffer according
        to the specified radix.
    @param buf Pointer to the buffer that will hold the string.
    @param size Size of the buffer.
    @param value Integer value to convert
    @param radix The base radix to use when encoding the number
    @return Returns a reference to the string.
    @ingroup WebsRuntime
 */
extern char *itosbuf(char *buf, ssize size, int64 value, int radix);

/**
    Compare strings ignoring case. This is a safe replacement for strcasecmp. It can handle NULL args.
    @description Compare two strings ignoring case differences. This call operates similarly to strcmp.
    @param s1 First string to compare.
    @param s2 Second string to compare. 
    @return Returns zero if the strings are equivalent, < 0 if s1 sorts lower than s2 in the collating sequence 
        or > 0 if it sorts higher.
    @ingroup WebsRuntime
 */
extern int scaselesscmp(char *s1, char *s2);

/**
    Compare strings ignoring case. This is similar to scaselesscmp but it returns a boolean.
    @description Compare two strings ignoring case differences.
    @param s1 First string to compare.
    @param s2 Second string to compare. 
    @return Returns true if the strings are equivalent, otherwise false.
    @ingroup WebsRuntime
 */
extern bool scaselessmatch(char *s1, char *s2);

/**
    Clone a string
    @description Copy a string into a newly allocated block.
    @param str Pointer to the block to duplicate.
    @return Returns a newly allocated string.
    @ingroup WebsRuntime
 */
extern char *sclone(char *str);

/**
    Compare strings.
    @description Compare two strings. This is a safe replacement for strcmp. It can handle null args.
    @param s1 First string to compare.
    @param s2 Second string to compare.
    @return Returns zero if the strings are identical. Return -1 if the first string is less than the second. Return 1
        if the first string is greater than the second.
    @ingroup WebsRuntime
 */
extern int scmp(char *s1, char *s2);

/**
    Copy a string.
    @description Safe replacement for strcpy. Copy a string and ensure the destination buffer is not overflowed. 
        The call returns the length of the resultant string or an error code if it will not fit into the target
        string. This is similar to strcpy, but it will enforce a maximum size for the copied string and will 
        ensure it is always terminated with a null.
    @param dest Pointer to a pointer that will hold the address of the allocated block.
    @param destMax Maximum size of the target string in characters.
    @param src String to copy
    @return Returns the number of characters in the target string.
    @ingroup WebsRuntime
 */
extern ssize scopy(char *dest, ssize destMax, char *src);

/*
    String trim flags
 */
#define WEBS_TRIM_START  0x1             /**< Flag for #strim to trim from the start of the string */
#define WEBS_TRIM_END    0x2             /**< Flag for #strim to trim from the end of the string */
#define WEBS_TRIM_BOTH   0x3             /**< Flag for #strim to trim from both the start and the end of the string */

/**
    Format a string. This is a secure verion of printf that can handle null args.
    @description Format the given arguments according to the printf style format. See fmt() for a full list of the
        format specifies. This is a secure replacement for sprintf, it can handle null arguments without crashes.
    @param format Printf style format string
    @param ... Variable arguments for the format string
    @return Returns a newly allocated string
    @ingroup WebsRuntime
 */
extern char *sfmt(char *format, ...);

/**
    Format a string with varargs. This is a secure verion of printf that can handle null args.
    @description Format the given arguments according to the printf style format. See fmt() for a full list of the
        format specifies. This is a secure replacement for sprintf, it can handle null arguments without crashes.
    @param format Printf style format string
    @param args Varargs argument obtained from va_start.
    @return Returns a newly allocated string
    @ingroup WebsRuntime
 */
extern char *sfmtv(char *format, va_list args);

/**
    Return the length of a string.
    @description Safe replacement for strlen. This call returns the length of a string and tests if the length is 
        less than a given maximum. It will return zero for NULL args.
    @param str String to measure.
    @return Returns the length of the string
    @ingroup WebsRuntime
 */
extern ssize slen(char *str);

/**
    Convert a string to lower case. 
    @description Convert a string to its lower case equivalent.
    @param str String to convert. This string is modified.
    @return Reference to the supplied str.
    @ingroup WebsRuntime
 */
extern char *slower(char *str);

/**
    Compare strings
    @description Compare two strings. This is similar to #scmp but it returns a boolean.
    @param s1 First string to compare.
    @param s2 Second string to compare.
    @return Returns true if the strings are equivalent, otherwise false.
    @ingroup WebsRuntime
 */
extern bool smatch(char *s1, char *s2);

/**
    Compare strings ignoring case.
    @description Compare two strings ignoring case differences for a given string length. This call operates 
        similarly to strncasecmp.
    @param s1 First string to compare.
    @param s2 Second string to compare.
    @param len Length of characters to compare.
    @return Returns zero if the strings are equivalent, < 0 if s1 sorts lower than s2 in the collating sequence 
        or > 0 if it sorts higher.
    @ingroup WebsRuntime
 */
extern int sncaselesscmp(char *s1, char *s2, ssize len);

/**
    Compare strings.
    @description Compare two strings for a given string length. This call operates similarly to strncmp.
    @param s1 First string to compare.
    @param s2 Second string to compare.
    @param len Length of characters to compare.
    @return Returns zero if the strings are equivalent, < 0 if s1 sorts lower than s2 in the collating sequence 
        or > 0 if it sorts higher.
    @ingroup WebsRuntime
 */
extern int sncmp(char *s1, char *s2, ssize len);

/**
    Copy characters from a string.
    @description Safe replacement for strncpy. Copy bytes from a string and ensure the target string is not overflowed. 
        The call returns the length of the resultant string or an error code if it will not fit into the target
        string. This is similar to strcpy, but it will enforce a maximum size for the copied string and will 
        ensure it is terminated with a null.
    @param dest Pointer to a pointer that will hold the address of the allocated block.
    @param destMax Maximum size of the target string in characters.
    @param src String to copy
    @param count Maximum count of characters to copy
    @return Returns a reference to the destination if successful or NULL if the string won't fit.
    @ingroup WebsRuntime
 */
extern ssize sncopy(char *dest, ssize destMax, char *src, ssize count);

/**
    Tokenize a string
    @description Split a string into tokens.
    @param str String to tokenize.
    @param delim String of characters to use as token separators.
    @param last Last token pointer.
    @return Returns a pointer to the next token.
    @ingroup WebsRuntime
 */
extern char *stok(char *str, char *delim, char **last);

/**
    Trim a string.
    @description Trim leading and trailing characters off a string.
    @param str String to trim.
    @param set String of characters to remove.
    @param where Flags to indicate trim from the start, end or both. Use WEBS_TRIM_START, WEBS_TRIM_END, WEBS_TRIM_BOTH.
    @return Returns a pointer to the trimmed string. May not equal \a str.
 */
extern char *strim(char *str, char *set, int where);

/**
    Convert a string to upper case.
    @description Convert a string to its upper case equivalent.
    @param str String to convert. This string is modified.
    @return Returns a pointer to the converted string. Will always equal str.
    @ingroup WebsRuntime
 */
extern char *supper(char *str);

/**
    Callback function for events
    @param data Opaque data argument
    @param id Event ID
    @ingroup WebsRuntime
 */
typedef void (*WebsEventProc)(void *data, int id);

/**
    Start a callback event
    @description This schedules an event to run once. The event can be rescheduled in the callback by invoking
    websRestartEvent.
    @param delay Delay in milliseconds in which to run the callback
    @param proc Callback procedure function. Signature is: void (*fn)(void *data, int id)
    @param data Data reference to pass to the callback
    @return A positive integer event ID
    @ingroup WebsRuntime
 */
extern int websStartEvent(int delay, WebsEventProc proc, void *data);

/**
    Stop an event
    @param id Event id allocated by websStartEvent
    @return Integer handle index. Otherwise return -1 on allocation errors.
    @ingroup WebsRuntime
 */
extern void websStopEvent(int id);

/**
    Restart an event
    @param id Event id allocated by websStartEvent
    @param delay Delay in milliseconds till the event next runs
    @ingroup WebsRuntime
 */
extern void websRestartEvent(int id, int delay);

/**
    Run due events
    @ingroup WebsRuntime
    @internal
 */
extern void websRunEvents();

/* Forward declare */
struct WebsRoute;
struct WebsUser;
struct WebsSession;
struct Webs;

/********************************** Upload ************************************/
#if BIT_UPLOAD

/**
    File upload structure
    @see websUploadOpen websLookupUpload websGetUpload
    @defgroup WebsUpload WebsUpload
 */
typedef struct WebsUpload {
    char    *filename;              /**< Local (temp) name of the file */
    char    *clientFilename;        /**< Client side name of the file */
    char    *contentType;           /**< Content type */
    ssize   size;                   /**< Uploaded file size */
} WebsUpload;

/**
    Open the file upload filter
    @ingroup WebsUpload
 */
extern void websUploadOpen();

/**
    Get the hash of uploaded files for the request
    @param wp Webs request object
    @return Hash table of uploaded files
    @ingroup WebsUpload
 */
extern WebsHash websGetUpload(struct Webs *wp);

/**
    Open the file upload filter
    @param wp Webs request object
    @param key Form upload name
    @return Upload object for the uploaded file
    @ingroup WebsUpload
 */
extern WebsUpload *websLookupUpload(struct Webs *wp, char *key);
#endif
/********************************** Defines ***********************************/

#define WEBS_MAX_PORT_LEN       10          /* Max digits in port number */
#define WEBS_HASH_INIT          64          /* Hash size for form table */
#define WEBS_SESSION_HASH       31          /* Hash size for session stores */
#define WEBS_SESSION_PRUNE      (60*1000)   /* Prune sessions every minute */

/* 
    Request flags
 */
#define WEBS_ACCEPTED           0x1         /**< TLS connection accepted */
#define WEBS_COOKIE             0x2         /**< Cookie supplied in request */
#define WEBS_FORM               0x4         /**< Request is a form (url encoded data) */
#define WEBS_HEADERS_DONE       0x8         /**< Already output the HTTP header */
#define WEBS_HTTP11             0x10        /**< Request is using HTTP/1.1 */
#define WEBS_KEEP_ALIVE         0x20        /**< HTTP/1.1 keep alive */
#define WEBS_RESPONSE_TRACED    0x40        /**< Started tracing the response */
#define WEBS_SECURE             0x80        /**< Connection uses SSL */
#define WEBS_UPLOAD             0x100       /**< Multipart-mime file upload */
#define WEBS_REROUTE            0x200       /**< Restart route matching */
#define WEBS_FINALIZED          0x400       /**< Output is finalized */
#if BIT_LEGACY
#define WEBS_LOCAL              0x10000     /**< Request from local system */
#endif

/*
    Incoming chunk encoding states. Used for tx and rx chunking.
 */
#define WEBS_CHUNK_UNCHUNKED  0             /**< Data is not transfer-chunk encoded */
#define WEBS_CHUNK_START      1             /**< Start of a new chunk */
#define WEBS_CHUNK_HEADER     2             /**< Preparing tx chunk header */
#define WEBS_CHUNK_DATA       3             /**< Start of chunk data */

/* 
    Read handler flags and state
 */
#define WEBS_BEGIN          0x1             /**< Beginning state */
#define WEBS_CONTENT        0x2             /**< Ready for body data */
#define WEBS_RUNNING        0x4             /**< Processing request */

/*
    Session names
 */
#define WEBS_SESSION            "-goahead-session-"
#define WEBS_SESSION_USERNAME   "_:USERNAME:_"  /* Username variable */

/*
    WebsDone flags
 */
#define WEBS_CLOSE          0x20000     /**< Close connection */

/**
    GoAhead request structure. This is a per-socket connection structure.
    @defgroup Webs Webs
 */
typedef struct Webs {
    WebsBuf         rxbuf;              /**< Raw receive buffer */
    WebsBuf         input;              /**< Receive buffer after de-chunking */
    WebsBuf         output;             /**< Transmit data buffer */
    WebsTime        since;              /**< Parsed if-modified-since time */
    WebsHash        vars;               /**< CGI standard variables */
    WebsTime        timestamp;          /**< Last transaction with browser */
    int             timeout;            /**< Timeout handle */
    char            ipaddr[64];         /**< Connecting ipaddress */
    char            ifaddr[64];         /**< Local interface ipaddress */

    int             rxChunkState;       /**< Rx chunk encoding state */
    ssize           rxChunkSize;        /**< Rx chunk size */
    char            *rxEndp;            /**< Pointer to end of raw data in input beyond endp */
    ssize           lastRead;           /**< Number of bytes last read from the socket */
    bool            eof;                /**< If at the end of the request content */

    char            txChunkPrefix[16];  /**< Transmit chunk prefix */
    char            *txChunkPrefixNext; /**< Current I/O pos in txChunkPrefix */
    ssize           txChunkPrefixLen;   /**< Length of prefix */
    ssize           txChunkLen;         /**< Length of the chunk */
    int             txChunkState;       /**< Transmit chunk state */

    //  MOB OPT - which of these should be allocated strings and which should be static

    char            *authDetails;       /**< Http header auth details */
    char            *authResponse;      /**< Outgoing auth header */
    char            *authType;          /**< Authorization type (Basic/DAA) */
    char            *contentType;       /**< Body content type */
    char            *cookie;            /**< Request cookie string */
    char            *decodedQuery;      /**< Decoded request query */
    char            *digest;            /**< Password digest */
    char            *ext;               /**< Path extension */
    char            *filename;          /**< Document path name */
    char            *host;              /**< Requested host */
    char            *inputFile;         /**< File name to write input body data */
    char            *method;            /**< HTTP request method */
    char            *password;          /**< Authorization password */
    char            *path;              /**< Path name without query. This is decoded. */
    char            *protoVersion;      /**< Protocol version (HTTP/1.1)*/
    char            *protocol;          /**< Protocol scheme (normally http|https) */
    char            *query;             /**< Request query. This is decoded. */
    char            *realm;             /**< Realm field supplied in auth header */
    char            *referrer;          /**< The referring page */
    char            *responseCookie;    /**< Outgoing cookie */
    char            *url;               /**< Full request url. This is not decoded. */
    char            *userAgent;         /**< User agent (browser) */
    char            *username;          /**< Authorization username */

    int             sid;                /**< Socket id (handler) */
    int             listenSid;          /**< Listen Socket id */
    int             port;               /**< Request port number */
    int             state;              /**< Current state */
    int             flags;              /**< Current flags -- see above */
    int             code;               /**< Response status code */
    ssize           rxLen;              /**< Rx content length */
    ssize           rxRemaining;        /**< Remaining content to read from client */
    ssize           txLen;              /**< Tx content length header value */
    int             wid;                /**< Index into webs */
#if BIT_CGI
    char            *cgiStdin;          /**< Filename for CGI program input */
    int             cgifd;              /**< File handle for CGI program input */
#endif
    int             putfd;              /**< File handle to write PUT data */
    int             docfd;              /**< File descriptor for document being served */
    ssize           written;            /**< Bytes actually transferred */
    void            (*writable)(struct Webs *wp);

    struct WebsSession *session;        /**< Session record */
    struct WebsRoute *route;            /**< Request route */
    struct WebsUser *user;              /**< User auth record */
    int             encoded;            /**< True if the password is MD5(username:realm:password) */
#if BIT_DIGEST
    char            *cnonce;            /**< check nonce */
    char            *digestUri;         /**< URI found in digest header */
    char            *nonce;             /**< opaque-to-client string sent by server */
    char            *nc;                /**< nonce count */
    char            *opaque;            /**< opaque value passed from server */
    char            *qop;               /**< quality operator */
#endif
#if BIT_UPLOAD
    int             upfd;               /**< Upload file handle */
    WebsHash        files;              /**< Uploaded files */
    char            *boundary;          /**< Mime boundary (static) */
    ssize           boundaryLen;        /**< Boundary length */
    int             uploadState;        /**< Current file upload state */
    WebsUpload      *currentFile;       /**< Current file context */
    char            *clientFilename;    /**< Current file filename */
    char            *uploadTmp;         /**< Current temp filename for upload data */
    char            *uploadVar;         /**< Current upload form variable name */
#endif
#if BIT_PACK_OPENSSL
    SSL             *ssl;               /**< SSL state */
    BIO             *bio;               /**< Buffer for I/O - not used in actual I/O */
#elif BIT_PACK_MATRIXSSL
    void            *ms;                /**< MatrixSSL state */
#endif
} Webs;

#if BIT_LEGACY
    #define WEBS_LEGACY_HANDLER 0x1     /* Using legacy calling sequence */
#endif


/**
    GoAhead handler service callback
    @param wp Webs request object
    @return True if the handler serviced the request
    @ingroup Webs
 */
typedef bool (*WebsHandlerProc)(Webs *wp);

/**
    GoAhead handler close to release memory prior to shutdown.
    @description This callback is invoked when GoAhead is shutting down.
    @ingroup Webs
 */
typedef void (*WebsHandlerClose)();

/**
    GoAhead handler object
    @ingroup Webs
 */
typedef struct WebsHandler {
    char                *name;              /**< Handler name */
    WebsHandlerProc     service;            /**< Handler service callback */
    WebsHandlerClose    close;              /**< Handler close callback  */
    int                 flags;              /**< Handler control flags */
} WebsHandler;

#if BIT_LEGACY
    typedef void (*WebsProc)(Webs *wp, char *path, char *query);
#else
    /**
        Proc handler callback
        @param wp Webs request object
        @ingroup Webs
     */
    typedef void (*WebsProc)(Webs *wp);
#endif

/**
    Error code list
    @ingroup Webs
 */
typedef struct WebsError {
    int     code;                           /**< HTTP error code */
    char    *msg;                           /**< HTTP error message */
} WebsError;

/** 
    Mime type list
    @ingroup Webs
 */
typedef struct WebsMime {
    char    *type;                          /**< Mime type */
    char    *ext;                           /**< File extension */
} WebsMime;

/**
    File information structure.
    @ingroup Webs
 */
typedef struct WebsFileInfo {
    ulong           size;                   /**< File length */
    int             isDir;                  /**< Set if directory */
    WebsTime        mtime;                  /**< Modified time */
} WebsFileInfo;

/**
    Compiled Rom Page Index
    @ingroup Webs
 */
typedef struct WebsRomIndex {
    char            *path;                  /**< Web page URL path */
    uchar           *page;                  /**< Web page data */
    int             size;                   /**< Size of web page in bytes */
    WebsFilePos     pos;                    /**< Current read position */
} WebsRomIndex;

#if BIT_ROM
    /**
        List of documents to service when built with ROM support
        @ingroup Webs
     */
    extern WebsRomIndex websRomPageIndex[];
#endif

#define WEBS_DECODE_TOKEQ 1                 /**< Decode base 64 blocks up to a NULL or equals */

/**
    Accept a new connection 
    @param sid Socket ID handle for the newly accepted socket
    @param ipaddr IP address originating the connection.
    @param port Port number originating the connection.
    @param listenSid Socket ID of the listening socket
    @return Zero if successful, otherwise -1
    @ingroup Webs
 */
extern int websAccept(int sid, char *ipaddr, int port, int listenSid);

/**
    Allocate a new Webs object
    @param sid Socket ID handle for the newly accepted socket
    @return The webs[] handle index for the allocated Webs object
    @ingroup Webs
 */
extern int websAlloc(int sid);

#if BIT_CGI
/**
    Open the CGI handler
    @return Zero if successful, otherwise -1
    @ingroup Webs
 */
extern int websCgiOpen();

/**
    CGI handler service callback
    @param wp Webs object
    @return Returns 1 if the request was handled. 
    @ingroup Webs
 */
extern int websCgiHandler(Webs *wp);

/**
    Cleanup completed CGI processes and output.
    @ingroup Webs
 */
extern void websCgiCleanup();

#if UNUSED
/**
    Check if a CGI process has completed
    @param handle CGI process handle
    @ingroup Webs
 */
extern int websCheckCgiProc(int handle);
#endif
#endif /* BIT_CGI */

/**
    Close the core GoAhead web server module
    @description Invoked when GoAhead is shutting down.
    @ingroup Webs
 */
extern void websClose();

/**
    Compare a request variable
    @param wp Webs request object
    @param var Variable name
    @param value Value to compare with
    @return True if the value matches. Otherwise return 0
    @ingroup Webs
 */
extern int websCompareVar(Webs *wp, char *var, char *value);

/**
    Consume input from the request input buffer.
    @description This is called by handlers when consuming data from the request input buffer.
        This call updates the input service pointers and compacts the input buffer if required.
    @param wp Webs request object
    @param nbytes Number of bytes the handler has consumed from the input buffer.
    @ingroup Webs
 */
extern void websConsumeInput(Webs *wp, ssize nbytes);

/**
    Decode the string using base-64 encoding
    @description This modifies the original string
    @param str String to decode
    @return The original string.
    @ingroup Webs
 */
extern char *websDecode64(char *str);

/**
    Decode a block using base-46 encoding
    @param str String to decode. The string must be null terminated.
    @param len Reference to an integer holding the length of the decoded string.
    @param flags Reserved.
    @return The original string.
    @ingroup Webs
 */
extern char *websDecode64Block(char *str, ssize *len, int flags);

/**
    Decode a URL expanding %NN encoding
    @description Supports insitu decoding. i.e. url may equal decoded.
    @param url URL to decode
    @param decoded Buffer to hold the decoded URL
    @param len Length of the decoded buffer.
    @ingroup Webs
 */
extern void websDecodeUrl(char *url, char *decoded, ssize len);

/**
    Define a request handler
    @param name Name of the handler
    @param service Handler callback service procedure. Invoked to service each relevant request.
    @param close Handler callback close procedure. Called when GoAhead is shutting down.
    @param flags Set to WEBS_LEGACY_HANDLER to support the legacy handler API calling sequence.
    @return Zero if successful, otherwise -1.
    @ingroup Webs
 */
extern int websDefineHandler(char *name, WebsHandlerProc service, WebsHandlerClose close, int flags);

/**
    Complete a request.
    @description A handler should call websDone() to complete the request.
    @param wp Webs request object
    @param code HTTP status code
    @ingroup Webs
 */
extern void websDone(Webs *wp, int code);

/**
    Encode a string using base-64 encoding
    @description The string is encoded insitu.
    @param str String to encode
    @return The original string.
    @ingroup Webs
 */
extern char *websEncode64(char *str);

/**
    Encode a block using base-64 encoding
    @description The string is encoded insitu.
    @param str String to encode.
    @param len Length of string to encode
    @return The original string.
    @ingroup Webs
 */
extern char *websEncode64Block(char *str, ssize len);

/**
    Escape unsafe characters in a string
    @param str String to escape
    @return An allocated block containing the escaped string. Caller must free.
    @ingroup Webs
 */
extern char *websEscapeHtml(char *str);

/**
    Complete a request with an error response
    @param wp Webs request object
    @param code HTTP status code
    @param fmt Message printf style format
    @param ... Format args
    @ingroup Webs
 */
extern void websError(Webs *wp, int code, char *fmt, ...);

/**
    Get a message for a HTTP status code
    @param code HTTP status code
    @return Http status message
    @ingroup Webs
 */
extern char *websErrorMsg(int code);

/**
    Open and initialize the file handler
    @ingroup Webs
 */
extern void websFileOpen();

/**
    Finalize the response 
    @description Flush transmit data and write a chunk trailer if required. After finalization, 
        the client should have the full response. WARNING: this call may block.
    @param wp Webs request object
    @ingroup Webs
 */
extern ssize websFinalize(Webs *wp);

/**
    Flush buffered transmit data and compact the transmit buffer to make room for more data
    @param wp Webs request object
    @return Number of bytes written
    @ingroup Webs
 */
extern ssize websFlush(Webs *wp);

/**
    Free the webs request object. 
    @description Callers should call websDone to complete requests prior to invoking websFree.
    @param wp Webs request object
    @ingroup Webs
 */
extern void websFree(Webs *wp);

/**
    Get the background execution flag
    @description If goahead is invoked with --background, it will run as a daemon in the background.
    @return True if GoAhead is running in the background.
    @ingroup Webs
 */
extern int websGetBackground();

#if BIT_CGI
/**
    Get a unique temporary filename for CGI communications
    @return Filename string
    @ingroup Webs
 */
extern char *websGetCgiCommName();
#endif /* BIT_CGI */

/**
    Get the request cookie if supplied
    @param wp Webs request object
    @return Cookie string if defined, otherwise null.
    @ingroup Webs
 */
extern char *websGetCookie(Webs *wp);

/**
    Get a date as a string
    @description If sbuf is supplied, it is used to calculate the date. Otherwise, the current time is used.
    @param sbuf File info object
    @return An allocated date string. Caller should free.
    @ingroup Webs
 */
extern char *websGetDateString(WebsFileInfo *sbuf);

/**
    Get the debug flag
    @description If GoAhead is invoked with --debugger, the debug flag will be set to true
    @return True if GoAhead is running in debug mode.
    @ingroup Webs
 */
extern int websGetDebug();

/**
    Get the base file directory for a request
    @description Returns the request route directory if defined, otherwise returns the documents directory.
    @param wp Webs request object
    @return Path name string. Caller should not free.
    @ingroup Webs
 */
extern char *websGetDir(Webs *wp);

/**
    Get the GoAhead base documents directory 
    @description The documents directory is defined at build time and may be overridden by the GoAhead command line.
    @return Path string for the documents directory.
    @ingroup Webs
 */
extern char *websGetDocuments();

/**
    Get the request EOF status
    @description The request EOF status is set to true when all the request body (POST|PUT) data has been received.
    @param wp Webs request object
    @return True if all the request body data has been received.
    @ingroup Webs
 */
extern int websGetEof(Webs *wp);

/**
    Get the request URI extension
    @param wp Webs request object
    @return The URI filename extension component. Caller should not free.
    @ingroup Webs
 */
extern char *websGetExt(Webs *wp);

/**
    Get the request filename
    @description The URI is mapped to a filename by decoding and prepending with the request directory.
    @param wp Webs request object
    @return Filename string. Caller should not free.
    @ingroup Webs
 */
extern char *websGetFilename(Webs *wp);

/**
    Get the request host
    @description The request host is set to the Host HTTP header value if it is present. Otherwise it is set to the request URI hostname.
    @param wp Webs request object
    @return Host string. Caller should not free.
    @ingroup Webs
 */
extern char *websGetHost(Webs *wp);

/**
    Get the request interface address
    @param wp Webs request object
    @return Network interface string. Caller should not free.
    @ingroup Webs
 */
extern char *websGetIfaddr(Webs *wp);

/**
    Get the default index document name
    @description The default index is "index.html" and can be updated via websSetIndex.
    @return Index name string. Caller should not free.
    @ingroup Webs
 */
extern char *websGetIndex();

/**
    Get the request method
    @param wp Webs request object
    @return HTTP method string. Caller should not free.
    @ingroup Webs
 */
extern char *websGetMethod(Webs *wp);

/**
    Get the request password
    @description The request password may be encoded depending on the authentication scheme. 
        See wp->encoded to test if it is encoded.
    @param wp Webs request object
    @return Password string. Caller should not free.
    @ingroup Webs
 */
extern char *websGetPassword(Webs *wp);

/**
    Get the request path
    @description The URI path component excludes the http protocol, hostname, port, reference and query components.
    It always beings with "/".
    @param wp Webs request object
    @return Request path string. Caller should not free.
    @ingroup Webs
 */
extern char *websGetPath(Webs *wp);

/**
    Get the request TCP/IP port
    @param wp Webs request object
    @return TCP/IP Port integer
    @ingroup Webs
 */
extern int websGetPort(Webs *wp);

/**
    Get the request HTTP protocol
    @description This will be set to either "http" or "https"
    @param wp Webs request object
    @return Protocol string. Caller should not free.
    @ingroup Webs
 */
extern char *websGetProtocol(Webs *wp);

/**
    Get the request query component
    @param wp Webs request object
    @return Request query string. Caller should not free.
    @ingroup Webs
 */
extern char *websGetQuery(Webs *wp);

/**
    Get the server host name
    @return Host name string. Caller should not free.
    @ingroup Webs
 */
extern char *websGetServer();

/**
    Get the server host name with port number.
    @return Host name string with port number. Caller should not free.
    @ingroup Webs
 */
extern char *websGetServerUrl();

/**
    Get the server IP address
    @return Server IP address string. Caller should not free.
    @ingroup Webs
 */
extern char *websGetServerAddress();

/**
    Get the server IP address with port number
    @return Server IP:PORT address string. Caller should not free.
    @ingroup Webs
 */
extern char *websGetServerAddressUrl();

/**
    Get the request URI
    @description This returns the request URI. This may be modified if the request is rewritten via websRewrite
    @param wp Webs request object
    @return URI string. Caller should not free.
    @ingroup Webs
 */
extern char *websGetUrl(Webs *wp);

/**
    Get the client User-Agent HTTP header
    @param wp Webs request object
    @return User-Agent string. Caller should not free.
    @ingroup Webs
 */
extern char *websGetUserAgent(Webs *wp);

/**
    Get the request username
    @description If the request is authenticated, this call returns the username supplied during authentication.
    @param wp Webs request object
    @return Username string if defined, otherwise null. Caller should not free.
    @ingroup Webs
 */
extern char *websGetUsername(Webs *wp);

/**
    Get a request variable
    @description Request variables are defined for HTTP headers of the form HTTP_*. 
        Some request handlers also define their own variables. For example: CGI environment variables.
    @param wp Webs request object
    @param name Variable name
    @param defaultValue Default value to return if the variable is not defined
    @return Variable value string. Caller should not free.
    @ingroup Webs
 */
extern char *websGetVar(Webs *wp, char *name, char *defaultValue);

/**
    Listen on a TCP/IP address endpoint
    @description The URI is mapped to a filename by decoding and prepending with the request directory.
        For IPv6 addresses, use the format: [aaaa:bbbb:cccc:dddd:eeee:ffff:gggg:hhhh:iiii]:port.
    @param endpoint IPv4 or IPv6 address on which to listen.
    @return Positive integer holding a Socket ID handle if successful, otherwise -1.
    @ingroup Webs
 */
extern int websListen(char *endpoint);

/**
    Get an MD5 digest of a string
    @param str String to analyze.
    @return Allocated MD5 checksum. Caller should free.
    @ingroup Webs
 */
extern char *websMD5(char *str);

/**
    Get an MD5 digest of a block and optionally prepend a prefix.
    @param buf Block to analyze
    @param length Length of block
    @param prefix Optional prefix to prepend to the MD5 sum.
    @return Allocated MD5 checksum. Caller should free.
    @ingroup Webs
 */
extern char *websMD5Block(char *buf, ssize length, char *prefix);

/**
    Normalize a URI path
    @description This removes "./", "../" and redundant separators.
    @param path URI path to normalize
    @return A normalized URI path. Caller should not free.
    @ingroup Webs
 */
extern char *websNormalizeUriPath(char *path);

/**
    Open the web server
    @description This initializes the web server and defines the documents directory.
    @param documents Optional web documents directory. If set to null, the build time BIT_DOCUMENTS value 
        is used for the documents directory.
    @param routes Optional filename for a route configuration file to load. Additional route or 
        authentication configuration files can be loaded via websLoad.
    @param routes Webs request object
    @return Zero if successful, otherwise -1.
    @ingroup Webs
 */
extern int websOpen(char *documents, char *routes);

/**
    Open the options handler
    @return Zero if successful, otherwise -1.
    @ingroup Webs
 */
extern int websOptionsOpen();

/**
    Close the document page
    @description This provides an interface above the file system or ROM based file system.
    @param wp Webs request object
    @ingroup Webs
 */
extern void websPageClose(Webs *wp);

/**
    Test if the document page for the request corresponds to a directory 
    @description This provides an interface above the file system or ROM based file system.
    @param wp Webs request object
    @return True if the filename is a directory
    @ingroup Webs
 */
extern int websPageIsDirectory(Webs *wp);

/**
    Open a web page document for a request
    @description This provides an interface above the file system or ROM based file system.
    @param wp Webs request object
    @param mode File open mode. Select from O_RDONLY and O_BINARY. Rom files systems ignore this argument.
    @param perms Ignored
    @return File handle if successful, otherwise -1.
    @ingroup Webs
 */
extern int websPageOpen(Webs *wp, int mode, int perms);

/**
    Read data from the request page document
    @param wp Webs request object
    @param buf Buffer for the read data
    @param size Size of buf
    @return Count of bytes read if successful, otherwise -1.
    @ingroup Webs
 */
extern ssize websPageReadData(Webs *wp, char *buf, ssize size);

/**
    Seek to a position in the request page document
    @param wp Webs request object
    @param offset Offset of location in the file to seek to. This is relative to the specified origin.
    @param origin Set to SEEK_CUR, SEEK_SET or SEEK_END to position relative to the current position, 
        beginning or end of the document.
    @ingroup Webs
 */
extern void websPageSeek(Webs *wp, WebsFilePos offset, int origin);

/**
    Get file status for the current request document
    @description This provides an interface above the file system or ROM based file system.
    @param wp Webs request object
    @param sbuf File information structure to modify with file status
    @return Zero if successful, otherwise -1.
    @ingroup Webs
 */
extern int websPageStat(Webs *wp, WebsFileInfo *sbuf);

/**
    Process request PUT body data
    @description This routine is called by the core HTTP engine to process request PUT data.
    @param wp Webs request object
    @return Zero if successful, otherwise -1.
    @ingroup Webs
 */
extern int websProcessPutData(Webs *wp);

/**
    Define a procedure callback for use with the proc handler.
    @description The proc handler binds function procedure calls to URIs.
    @param name URI path suffix. This suffix is added to "/proc" to form the bound URI path.
    @param proc Callback function procedure. The signature is void (*WebsProc)(Webs *wp);
    @return Zero if successful, otherwise -1.
    @ingroup Webs
 */
extern int websProcDefine(char *name, void *proc);

/**
    Open the proc handler
    @ingroup Webs
 */
extern void websProcOpen();

/**
    Redirect the client to a new URL.
    @description This creates a response to the client with a Location header directing the client to a new location.
        The response uses a 302 HTTP status code.
    @param wp Webs request object
    @param url URL to direct the client to. 
    @ingroup Webs
 */
extern void websRedirect(Webs *wp, char *url);

/**
    Redirect the client to a new URI
    @description The routing configuration file can define redirection routes for various HTTP status codes.
        This routine will utilize the appropriate route redirection based on the request route and specified status code.
    @param wp Webs request object
    @param status HTTP status code to use in selecting the route redirection.
    @return Zero if successful, otherwise -1.
    @ingroup Webs
 */
extern int websRedirectByStatus(Webs *wp, int status);

/**
    Create and send a request response
    @description This creates a response for the current request using the specified HTTP status code and 
        the supplied message.
    @param wp Webs request object
    @param status HTTP status code.
    @param msg Response message body
    @return Zero if successful, otherwise -1.
    @ingroup Webs
 */
extern void websResponse(Webs *wp, int status, char *msg);

/**
    Rewrite a request
    @description Handlers may choose to not process a request but rather rewrite requests and then reroute. 
    @param wp Webs request object
    @param url New request URL.
    @return Zero if successful, otherwise -1.
    @ingroup Webs
 */
extern int websRewriteRequest(Webs *wp, char *url);

#if BIT_ROM
/**
    Open the ROM file system
    @return Zero if successful, otherwise -1.
    @ingroup Webs
 */
extern int websRomOpen();

/**
    Close the ROM file system
    @ingroup Webs
 */
extern void websRomClose();

/**
    Open the web page document for the current request
    @param wp Webs request object
    @return Zero if successful, otherwise -1.
    @ingroup Webs
 */
extern int websRomPageOpen(Webs *wp);

/**
    Close the web page document for the current request
    @param wp Webs request object
    @ingroup Webs
 */
extern void websRomPageClose(Webs *wp);

/**
    Read data from ROM for the current request document
    @param wp Webs request object
    @param buf Buffer for the read data
    @param size Size of buf
    @return Count of bytes read if successful, otherwise -1.
    @ingroup Webs
 */
extern ssize websRomPageReadData(Webs *wp, char *buf, ssize size);

/**
    Get ROM file status for the current request document
    @description This provides an interface above the file system or ROM based file system.
    @param wp Webs request object
    @param sbuf File information structure to modify with file status
    @return Zero if successful, otherwise -1.
    @ingroup Webs
 */
extern int websRomPageStat(Webs *wp, WebsFileInfo *sbuf);

/**
    Seek to a position in the current request page document
    @param wp Webs request object
    @param offset Location in the file to seek to.
    @param origin Set to SEEK_CUR, SEEK_SET or SEEK_END to position relative to the current position, 
        beginning or end of the document.
    @ingroup Webs
 */
extern long websRomPageSeek(Webs *wp, WebsFilePos offset, int origin);
#endif


/**
    Service I/O events until finished
    @description This will wait for socket events and service those until *finished is set to true
    @param finished Integer location to test. If set to true, then exit. Note: setting finished will not 
        automatically wake up the service routine. 
    @ingroup Webs
 */
extern void websServiceEvents(int *finished);

/**
    Set the background processing flag
    @param on Value to set the background flag to.
    @ingroup Webs
    @internal
 */
extern void websSetBackground(int on);

/**
    Set the debug processing flag
    @param on Value to set the debug flag to.
    @ingroup Webs
    @internal
 */
extern void websSetDebug(int on);

/**
    Create the CGI environment variables for the current request.
    @param wp Webs request object
    @ingroup Webs
 */
extern void websSetEnv(Webs *wp);

/**
    Create request variables for query and POST body data
    @description This creates request variables if the request is a POST form (has a Content-Type of 
        application/x-www-form-urlencoded). The POST body data is consumed from the input buffer.
    @param wp Webs request object
    @ingroup Webs
 */
extern void websSetFormVars(Webs *wp);

/**
    Define the host name for the server
    @param host String host name
    @ingroup Webs
 */
extern void websSetHost(char *host);

/**
    Define the host IP address
    @param ipaddr Host IP address
    @ingroup Webs
 */
extern void websSetIpAddr(char *ipaddr);

/**
    Set the web documents directory
    @description The web documents directory is used when resolving request URIs into filenames.
    @param dir Directory path to use
    @ingroup Webs
 */
extern void websSetDocuments(char *dir);

/*
    Flags for websSetCookie
 */
#define WEBS_COOKIE_SECURE   0x1         /**< Flag for websSetCookie for secure cookies (https only) */
#define WEBS_COOKIE_HTTP     0x2         /**< Flag for websSetCookie for http cookies (http only) */

/**
    Define a cookie to include in the response
    @param wp Webs request object
    @param name Cookie name
    @param value Cookie value
    @param path URI path prefix applicable for this cookie 
    @param domain Domain applicable for this cookie
    @param lifespan Cookie lifespan in secons
    @param flags Set to WEBS_COOKIE_SECURE for https only. Set to WEBS_COOKIE_HTTP for http only. 
        Otherwise the cookie applies to both http and https requests.
    @return Zero if successful, otherwise -1.
    @ingroup Webs
 */
extern void websSetCookie(Webs *wp, char *name, char *value, char *path, char *domain, WebsTime lifespan, int flags);

/**
    Create and send a request response
    @description This creates a response for the current request using the specified HTTP status code and 
        the supplied message.
    @param filename Web document name to use as the index. This should not contain any directory components.
    @ingroup Webs
 */
extern void websSetIndex(char *filename);

/**
    Take not of the request activity and mark the time.
    @description This is used to defer the request timeout whenever there is request I/O activity.
    @param wp Webs request object
    @ingroup Webs
 */
extern void websNoteRequestActivity(Webs *wp);

/**
    Set the response body content length
    @param wp Webs request object
    @param length Length value to use
    @ingroup Webs
 */
extern void websSetTxLength(Webs *wp, ssize length);

/**
    Set a request variable
    @description Request variables are defined for HTTP headers of the form HTTP_*. 
        Some request handlers also define their own variables. For example: CGI environment variables.
    @param wp Webs request object
    @param name Variable name to set
    @param value Value to set
    @ingroup Webs
 */
extern void websSetVar(Webs *wp, char *name, char *value);

/**
    Test if  a request variable is defined
    @param wp Webs request object
    @param name Variable name
    @return True if the variable is defined
    @ingroup Webs
 */
extern bool websTestVar(Webs *wp, char *name);

/**
    Cancel the request timeout.
    @description Handlers may choose to manually manage the request timeout. This routine will disable the
        centralized management of the timeout for this request.
    @param wp Webs request object
    @ingroup Webs
 */
extern void websTimeoutCancel(Webs *wp);


/**
    Parse a URL into its components
    @param url URL to parse
    @param buf Buffer to hold storage for various parsed components. Caller must free. NOTE: the parsed components may
        point to locations in this buffer.
    @param protocol Parsed URL protocol component
    @param host Parsed hostname
    @param port Parsed URL port
    @param path Parsed URL path component
    @param ext Parsed URL extension
    @param reference Parsed URL reference portion (\#reference)
    @param query Parsed URL query component
    @return Zero if successful, otherwise -1.
    @ingroup Webs
 */
extern int websUrlParse(char *url, char **buf, char **protocol, char **host, char **port, char **path, char **ext, 
    char **reference, char **query);

/**
    Test if a webs object is valid
    @description After calling websDone, the websFree routine will have been called and the memory for the webs object
        will be released. Call websValid to test an object hand for validity.
    @param wp Webs request object
    @return True if the webs object is still valid and the request has not been completed.
    @ingroup Webs
 */
extern bool websValid(Webs *wp);

/**
    Write a set of standard response headers
    @param wp Webs request object
    @param status HTTP status code
    @param contentLength Value for the Content-Length header which describes the length of the response body
    @param redirect Value for the Location header which redirects the client to a new URL.
    @ingroup Webs
 */
extern void websWriteHeaders(Webs *wp, int status, ssize contentLength, char *redirect);

/**
    Signify the end of the response headers
    @description This call concludes the response headers and writes a blank line to the response.
    @param wp Webs request object
    @ingroup Webs
 */
extern void websWriteEndHeaders(Webs *wp);

/**
    Write a response header
    @description This routine writes a response header. It should be invoked after calling websWriteHeaders
        to write the standard headers and before websWriteEndHeaders.
        This routine differs from websWrite in that it traces header values to the log.
    @param wp Webs request object
    @param fmt Header key and value. Should be of the form: "Name: Value"
    @param ... Arguments to the format string.
    @return Count of bytes written
    @ingroup Webs
 */
extern ssize websWriteHeader(Webs *wp, char *fmt, ...);

/**
    Write data to the response
    @description The data is buffered and will be sent to the client when the buffer is full or websFlush is
        called.
    @param wp Webs request object
    @param fmt Printf style format string.
    @param ... Arguments to the format string.
    @return Count of bytes written
    @ingroup Webs
 */
extern ssize websWrite(Webs *wp, char *fmt, ...);

/**
    Write a block of data to the response
    @description The data is buffered and will be sent to the client when the buffer is full or websFlush is
        called.
    @param wp Webs request object
    @param buf Buffer of data to write
    @param size Length of buf
    @return Count of bytes written
    @ingroup Webs
 */
extern ssize websWriteBlock(Webs *wp, char *buf, ssize size);

/**
    Write a block of data to the response and bypass output buffering.
    @description This routine will first invoke websFlush if there is prior data in the output buffer, before writing
        the raw data.
    @param wp Webs request object
    @param buf Buffer of data to write
    @param size Length of buf
    @return Count of bytes written
    @ingroup Webs
 */
extern ssize websWriteRaw(Webs *wp, char *buf, ssize size);

#if BIT_UPLOAD
/**
    Process upload data for form, multipart mime file upload.
    @param wp Webs request object
    @return Zero if successful, otherwise -1.
    @ingroup Webs
 */
extern int websProcessUploadData(Webs *wp);

/**
    Free file upload data structures.
    @param wp Webs request object
    @ingroup Webs
 */
extern void websFreeUpload(Webs *wp);
#endif

#if BIT_CGI
/**
    Process CGI request body data.
    @param wp Webs request object
    @return Zero if successful, otherwise -1.
    @ingroup Webs
 */
extern int websProcessCgiData(Webs *wp);
#endif

#if BIT_JAVASCRIPT
/**
    Javascript native function 
    @param jid JavaScript engine ID
    @param wp Webs request object
    @param argc Count of function arguments
    @param argv Array of function arguments
    @param defaultValue Default value to return if the variable is not defined
    @return Return zero if successful, otherwise -1.
    @ingroup Webs
 */
typedef int (*WebsJsProc)(int jid, Webs *wp, int argc, char **argv);

/**
    Define a Javscript native function.
    @description This routine binds a C function to a Javascript function. When the Javascript function is called,
        the C function is invoked.
    @param name Javascript function name
    @param fn C function to invoke
    @return Zero if successful, otherwise -1.
    @ingroup Webs
 */
extern int websJsDefine(char *name, WebsJsProc fn);

/**
    Open the Javascript module.
    @return Zero if successful, otherwise -1.
    @ingroup Webs
 */
extern int websJsOpen();

/**
    Write data to the response
    @param jid Javascript ID handle
    @param wp Webs request object 
    @param argc Count of arguments
    @param argv Array arguments
    @return Zero if successful, otherwise -1.
    @ingroup Webs
 */
extern int websJsWrite(int jid, Webs *wp, int argc, char **argv);
#endif

/*************************************** SSL ***********************************/

#if BIT_PACK_SSL
/**
    Open the ssl module
    @return Zero if successful, otherwise -1.
    @ingroup Webs
 */
extern int sslOpen();

/**
    Close the ssl module
    @ingroup Webs
 */
extern void sslClose();

/**
    Free a ssl connection associated with a request
    @param wp Webs request object
    @ingroup Webs
 */
extern void sslFree(Webs *wp);

/**
    Upgrade a request connection to utilize SSL
    @description This routine is invoked on a connection received on a secure listening socket
    @param wp Webs request object
    @return Zero if successful, otherwise -1.
    @ingroup Webs
 */
extern int sslUpgrade(Webs *wp);

/**
    Read data from a secure socket
    @param wp Webs request object
    @param buf Buffer into which to read data
    @param len Size of buf
    @return Count of bytes read if successful, otherwise -1. 
    @ingroup Webs
 */
extern ssize sslRead(Webs *wp, void *buf, ssize len);

/**
    WRite data to a secure socket
    @param wp Webs request object
    @param buf Buffer from which to write data
    @param len Size of buf
    @return Count of bytes written if successful, otherwise -1. 
    @ingroup Webs
 */
extern ssize sslWrite(Webs *wp, void *buf, ssize len);
#endif /* BIT_PACK_SSL */

/*************************************** Route *********************************/
/**
    Callback to prompt the user for their password
    @param wp Webs request object
    @ingroup Webs
 */
typedef void (*WebsAskLogin)(Webs *wp);

/**
    Callback to verify the username and password
    @param wp Webs request object
    @return True if the password is verified
    @ingroup Webs
 */
typedef bool (*WebsVerify)(Webs *wp);

/**
    Callback to parse authentication details submitted with the web request
    @param wp Webs request object
    @return True if the details can be parsed
    @ingroup Webs
 */
typedef bool (*WebsParseAuth)(Webs *wp);

/**
    Request route structure
    @defgroup WebsRoute WebsRoute
 */
typedef struct WebsRoute {
    char            *prefix;                /**< Route path prefix */
    ssize           prefixLen;              /**< Prefix length */
    char            *dir;                   /**< Filesystem base directory for route documents */
    char            *protocol;              /**< HTTP protocol to use for this route */
    char            *authType;              /**< Authentication type */
    WebsHandler     *handler;               /**< Request handler to service requests */
    WebsHash        abilities;              /**< Required user abilities */
    WebsHash        extensions;             /**< Permissible URI extensions */
    WebsHash        redirects;              /**< Response redirections */
    WebsHash        methods;                /**< Supported HTTP methods */
    WebsAskLogin    askLogin;               /**< Route path prefix */
    WebsParseAuth   parseAuth;              /**< Parse authentication details callback*/
    WebsVerify      verify;                 /**< Verify password callback */
    int             flags;                  /**< Route control flags */
} WebsRoute;

/**
    Add a route to the routing tables
    @param uri Matching URI prefix
    @param handler Request handler to service routed requests
    @param pos Position in the list of routes. Zero inserts at the front of the list. A value of -1 will append to the
        end of the list.
    @return A route object
    @ingroup WebsRoute
 */
extern WebsRoute *websAddRoute(char *uri, char *handler, int pos);

/**
    Close the route module
    @ingroup WebsRoute
 */
extern void websCloseRoute();

/**
    Load routing tables from the specified filename
    @param path Route configuration filename
    @return Zero if successful, otherwise -1.
    @ingroup WebsRoute
 */
extern int websLoad(char *path);

/**
    Open the routing module
    @ingroup WebsRoute
 */
extern int websOpenRoute();

/**
    Remove a route from the routing tables
    @param uri Matching URI prefix
    @return Zero if successful, otherwise -1.
    @ingroup WebsRoute
 */
extern int websRemoveRoute(char *uri);

/**
    Route a request
    @description This routine will select a matching route and will invoke the selected route handler to service
        the request. In the process, authentication and request rewriting may take place.
    @param wp Webs request object
    @ingroup WebsRoute
 */
extern void websRouteRequest(Webs *wp);

/**
    Configure a route by adding matching criteria
    @param route Route to modify
    @param dir Set the route documents directory filename
    @param protocol Set the matching HTTP protocol (http or https)
    @param methods Hash of permissible HTTP methods. (GET, HEAD, POST, PUT)
    @param extensions Hash of permissible URI filename extensions.
    @param abilities Required user abilities. The user must be authenticated.
    @param abilities Required user abilities. If abilities are required, the user must be authenticated.
    @param redirects Set of applicable response redirections when completing the request.
    @return Zero if successful, otherwise -1.
    @ingroup WebsRoute
 */
extern int websSetRouteMatch(WebsRoute *route, char *dir, char *protocol, WebsHash methods, WebsHash extensions, 
        WebsHash abilities, WebsHash redirects);

/**
    Set route authentication scheme
    @param route Route to modify
    @param authType Set to "basic", "digest" or "form".
    @return Zero if successful, otherwise -1.
    @ingroup WebsRoute
 */
extern int websSetRouteAuth(WebsRoute *route, char *authType);

/*************************************** Auth **********************************/
#define WEBS_USIZE          128              /* Size of realm:username */

/**
    GoAhead Authentication
    @defgroup WebsAuth WebsAuth
 */
/**
    User definition structure
    @ingroup WebsAuth
 */
typedef struct WebsUser {
    char    *name;                          /**< User name */
    char    *password;                      /**< User password (encrypted) */
    char    *roles;                         /**< User roles */
    WebsHash abilities;                     /**< Resolved user abilities */
} WebsUser;

/**
    Role definition structure
    @ingroup WebsAuth
 */
typedef struct WebsRole {
    WebsHash  abilities;                    /**< Resolved role abilities */
} WebsRole;

/**
    Add a role
    @description The role is added to the list of roles
    @param role Role name
    @param abilities Hash of abilities for the role
    @return The allocated role.
    @ingroup WebsAuth
 */
extern WebsRole *websAddRole(char *role, WebsHash abilities);

/**
    Add a user
    @description The user is added to the list of users
    @param username User name
    @param password User password (encrypted)
    @param roles Space separated list of roles. This may also contain abilities.
    @return User object.
    @ingroup WebsAuth
 */
extern WebsUser *websAddUser(char *username, char *password, char *roles);

/**
    Authenticate a user
    @description The user is authenticated if required by the selected request route.
    @return True if the route does not require authentication or the user is authenticated successfully.
    @ingroup WebsAuth
 */
extern bool websAuthenticate(Webs *wp);

/**
    Test if a user possesses the required ability
    @param wp Webs request object
    @param ability Set of required abilities.
    @return True if the user has the required ability.
    @ingroup WebsAuth
 */
extern bool websCan(Webs *wp, WebsHash ability);

/**
    Close the authentication module
    @ingroup WebsAuth
 */
extern void websCloseAuth();

/**
    Compute the abilities for all users by resolving roles into abilities
    @ingroup WebsAuth
 */
extern void websComputeAllUserAbilities();

#if UNUSED
extern WebsHash websGetUsers();
extern WebsHash websGetRoles();
#endif

/**
    Login a user by verifying the login credentials.
    @description This may be called by handlers to manually authenticate a user.
    @param wp Webs request object
    @param username User name
    @param password User password (encrypted)
    @return True if the user can be authenticated. 
    @ingroup WebsAuth
 */
extern bool websLoginUser(Webs *wp, char *username, char *password);

/**
    Lookup if a user exists
    @param username User name to search for
    @return User object or null if the user cannot be found
    @ingroup WebsAuth
 */
extern WebsUser *websLookupUser(char *username);

/**
    Remove a role from the system
    @param role Role name
    @return Zero if successful, otherwise -1
    @ingroup WebsAuth
 */
extern int websRemoveRole(char *role);

/**
    Remove a user from the system
    @param name User name
    @return Zero if successful, otherwise -1
    @ingroup WebsAuth
 */
extern int websRemoveUser(char *name);

/**
    Open the authentication module
    @param minimal Reserved. Set to zero.
    @return True if the user has the required ability.
    @ingroup WebsAuth
 */
extern int websOpenAuth(int minimal);

/**
    Define the set of roles for a user
    @param username User name
    @param roles Space separated list of roles or abilities
    @return Zero if successful, otherwise -1.
    @ingroup WebsAuth
 */
extern int websSetUserRoles(char *username, char *roles);

/**
    Save the authentication file
    @param path Filename to save to
    @return Zero if successful, otherwise -1.
    @ingroup WebsAuth
 */
extern int websWriteAuthFile(char *path);

/**
    Standard user password verification routine.
    @param wp Webs request object
    @return True if the user password verifies.
    @ingroup WebsAuth
 */
extern bool websVerifyPassword(Webs *wp);

#if BIT_HAS_PAM && BIT_PAM
/**
    Verify a password using the system PAM password database.
    @param wp Webs request object
    @return True if the user password verifies.
    @ingroup WebsAuth
 */
extern bool websVerifyPampassword(Webs *wp);
#endif

/************************************** Sessions *******************************/
/**
    Session state storage
    @defgroup WebsSession WebsSession
 */
typedef struct WebsSession {
    char            *id;                    /**< Session ID key */
    WebsTime        lifespan;               /**< Session inactivity timeout (msecs) */
    WebsTime        expires;                /**< When the session expires */
    WebsHash        cache;                  /**< Cache of session variables */
} WebsSession;

/**
    Test if a user possesses the required ability
    @param wp Webs request object
    @param id Session ID to use. Set to null to allocate a new session ID.
    @param lifespan Lifespan of the session in seconds.
    @return Allocated session object
    @ingroup WebsSession
 */
extern WebsSession *websAllocSession(Webs *wp, char *id, WebsTime lifespan);

/**
    Get the session ID
    @param wp Webs request object
    @return The session ID if session state storage is defined for this request.
    @ingroup WebsSession
 */
extern char *websGetSessionID(Webs *wp);

/**
    Get the session state object for the current request
    @param wp Webs request object
    @param create Set to true to create a new session if one does not already exist.
    @return Session object
    @ingroup WebsSession
 */
extern WebsSession *websGetSession(Webs *wp, int create);

/**
    Get a session variable
    @param wp Webs request object
    @param name Session variable name
    @param defaultValue Default value to return if the variable does not exist
    @return Session variable value or default value if it does not exist
    @ingroup WebsSession
 */
extern char *websGetSessionVar(Webs *wp, char *name, char *defaultValue);

/**
    Remove a session variable
    @param wp Webs request object
    @param name Session variable name
    @ingroup WebsSession
 */
extern void websRemoveSessionVar(Webs *wp, char *name);

/**
    Set a session variable name value
    @param wp Webs request object
    @param name Session variable name
    @param value Value to set the variable to
    @return Zero if successful, otherwise -1
    @ingroup WebsSession
 */
extern int websSetSessionVar(Webs *wp, char *name, char *value);

/************************************ Legacy **********************************/
/*
    Legacy mappings for pre GoAhead 3.X applications
    This is a list of the name changes from GoAhead 2.X to GoAhead 3.x
    To maximize forward compatibility, It is best to not use BIT_LEGACY except as 
    a transitional compilation aid.
 */
#if BIT_LEGACY
    #define B_L 0
    #define WEBS_ASP WEBS_JS
    #define WEBS_NAME "Server: GoAhead/" BIT_VERSION
    #define a_assert gassert
    #define balloc galloc
    #define bclose gcloseAlloc
    #define bfree(loc, p) gfree(p)
    #define bfreeSafe(loc, p) gfree(p)
    #define bopen gopenAlloc
    #define brealloc grealloc
    #define bstrdup strdup
    #define emfReschedCallback websRestartEvent
    #define emfSchedCallback websStartEVent
    #define emfSchedProc WebsEventProc
    #define emfSchedProcess websRunEvents
    #define emfUnschedCallback websStopEvent
    #define fmtStatic fmt
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
    #define gstritoa    stritoa
    #define gstrlen     strlen
    #define gstrlower   strlower
    #define gstrncat    strncat
    #define gstrncmp    strncmp
    #define gstrncpy    strncpy
    #define gstrnlen    strnlen
    #define gstrnset    strnset
    #define gstrrchr    strrchr
    #define gstrspn     strspn
    #define gstrstr     strstr
    #define gstrtok     strtok
    #define gstrtol     strtol
    #define gstrupper   strupper
    #define gtempnam    tempnam
    #define gtolower    tolower
    #define gtoupper    toupper
    #define gunlink     unlink
    #define gvsprintf   vsprintf
    #define gwrite      write
    #define hAlloc galloc
    #define hAllocEntry gallocObject
    #define hFree gFree
    #define stritoa gstritoa
    #define strlower gstrlower
    #define strupper gstrupper
    #define websAspDefine websJsDefine
    #define websAspOpen websJsOpen
    #define websAspRequest websJsRequest
    #define websFormDefine websProcDefine
    #define websGetDefaultDir websGetDocuments
    #define websGetDefaultPage websGetIndex

    #define websGetRequestDir(wp) wp->dir
    #define websGetRequestIpAddr(wp) wp->ipaddr
    #define websGetRequestFilename(wp) wp->filename
    #define websGetRequestFlags(wp) wp->flags
    #define websGetRequestLpath(wp) wp->filename
    #define websGetRequestPath(wp) wp->path
    #define websGetRequestPassword(wp) wp->password
    #define websGetRequestUserName(wp) wp->username
    #define websGetRequestWritten(wp) wp->written

    #define websSetDefaultDir websSetDocuments
    #define websSetDefaultPage websGetIndex
    #define websSetRequestLpath websSetRequestFilename
    #define websSetRequestWritten(wp, nbytes)  if (1) { wp->written = nbytes; } else
    #define websWriteDataNonBlock websWriteRaw

    #define ringqOpen bufCreate
    #define ringqClose bufFree
    #define ringqLen bufLen
    #define ringqPutc bufPutc
    #define ringqInsertc bufInsertc
    #define ringqPutStr bufPutStr
    #define ringqGetc bufGetc
    #define ringqGrow bufGrow
    #define ringqPutBlk bufPutBlk
    #define ringqPutBlkMax bufRoom
    #define ringqPutBlkAdj bufAdjustEnd
    #define ringqGetBlk bufGetBlk
    #define ringqGetBlkMax bufGetBlkMax
    #define ringqGetBlkAdj bufAdjustSTart
    #define ringqFlush bufFlush
    #define ringqCompact bufCompact
    #define ringqReset bufReset
    #define ringqAddNull bufAddNull

    #define symCreate hashCreate
    #define symClose hashFree
    #define symLookup hashLookup
    #define symEnter hashEnter
    #define symDelete hashDelete
    #define symWalk hashWalk
    #define symFirst hashFirst
    #define symNext hashNext

    typedef Webs *webs_t;
    typedef Webs WebsRec;
    typedef Webs websType;
    typedef WebsBuf ringq_t;
    typedef WebsError websErrorType;
    typedef WebsFileInfo websStatType;
    typedef WebsProc WebsFormProc;
    typedef int (*WebsLegacyHandlerProc)(Webs *wp, char *prefix, char *dir, int flags);
    typedef SocketHandler socketHandler_t;
    typedef SocketAccept socketAccept_t;
    typedef WebsType vtype_t;
    
    typedef WebsHash sym_fd_t;
    typedef WebsKey sym_t;
    typedef WebsMime websMimeType;
    typedef WebsSocket socket_t;
    typedef WebsStat gstat_t;
    typedef WebsValue value_t;

    extern int fmtValloc(char **s, int n, char *fmt, va_list arg);
    extern int fmtAlloc(char **s, int n, char *fmt, ...);
    extern void websFooter(Webs *wp);
    extern void websHeader(Webs *wp);
    extern int websPublish(char *prefix, char *path);
    extern void websSetRequestFilename(Webs *wp, char *filename);
    extern int websUrlHandlerDefine(char *prefix, char *dir, int arg, WebsLegacyHandlerProc handler, int flags);

#if BIT_ROM
    typedef WebsRomIndex websRomPageIndexType;
#endif
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
