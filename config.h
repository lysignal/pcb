/* config.h.  Generated from config.h.in by configure.  */
/* config.h.in.  Generated from configure.ac by autoheader.  */

/* Relative path from bindir to exec_prefix */
#define BINDIR_TO_EXECPREFIX ".."

/* Relative path from bindir to pcblibdir */
#define BINDIR_TO_PCBLIBDIR "../share/pcb"

/* Relative path from bindir to pcbtreedir */
#define BINDIR_TO_PCBTREEDIR "../share/pcb/newlib"

/* Maximum value of coordinate type */
#define COORD_MAX LONG_MAX

/* C type for Coordinates */
#define COORD_TYPE long

/* Define to one of `_getb67', `GETB67', `getb67' for Cray-2 and Cray-YMP
   systems. This function is required for `alloca.c' support on those systems.
   */
/* #undef CRAY_STACKSEG_END */

/* Define to 1 if using `alloca.c'. */
/* #undef C_ALLOCA */

/* Define to 1 if GL support is to be compiled in */
/* #undef ENABLE_GL */
#define ENABLE_GL 1
//#define ENABLE_GL_TRACKBALL 1

/* Define to 1 if translation of program messages to the user's native
   language is requested. */
/* #undef ENABLE_NLS */

/* File for default font */
#define FONTFILENAME "default_font"

/* Name of this program's gettext domain */
#define GETTEXT_PACKAGE "pcb"

/* m4 program used by pcb */
#define GNUM4 "/usr/bin/m4"

/* Define to 1 if you have `alloca', as a function or macro. */
#define HAVE_ALLOCA 1

/* Define to 1 if you have <alloca.h> and it should be used (not on Ultrix).
   */
#define HAVE_ALLOCA_H 1

/* Define to 1 if you have the `argz_count' function. */
#define HAVE_ARGZ_COUNT 1

/* Define to 1 if you have the <argz.h> header file. */
#define HAVE_ARGZ_H 1

/* Define to 1 if you have the `argz_next' function. */
#define HAVE_ARGZ_NEXT 1

/* Define to 1 if you have the `argz_stringify' function. */
#define HAVE_ARGZ_STRINGIFY 1

/* Define to 1 if you have the `asprintf' function. */
#define HAVE_ASPRINTF 1

/* Define to 1 if the compiler understands __builtin_expect. */
#define HAVE_BUILTIN_EXPECT 1

/* Define to 1 if you have the `canonicalize_file_name' function. */
#define HAVE_CANONICALIZE_FILE_NAME 1

/* Define to 1 if you have the Mac OS X function CFLocaleCopyCurrent in the
   CoreFoundation framework. */
/* #undef HAVE_CFLOCALECOPYCURRENT */

/* Define to 1 if you have the Mac OS X function CFPreferencesCopyAppValue in
   the CoreFoundation framework. */
/* #undef HAVE_CFPREFERENCESCOPYAPPVALUE */

/* Define to 1 if DBUS IPC is to be compiled in */
/* #undef HAVE_DBUS */

/* Define to 1 if you have the `dbus_watch_get_unix_fd' function. */
/* #undef HAVE_DBUS_WATCH_GET_UNIX_FD */

/* Define if the GNU dcgettext() function is already present or preinstalled.
   */
/* #undef HAVE_DCGETTEXT */

/* Define to 1 if you have the declaration of `feof_unlocked', and to 0 if you
   don't. */
#define HAVE_DECL_FEOF_UNLOCKED 1

/* Define to 1 if you have the declaration of `fgets_unlocked', and to 0 if
   you don't. */
#define HAVE_DECL_FGETS_UNLOCKED 1

/* Define to 1 if you have the declaration of `getc_unlocked', and to 0 if you
   don't. */
#define HAVE_DECL_GETC_UNLOCKED 1

/* Define to 1 if you have the declaration of `_snprintf', and to 0 if you
   don't. */
#define HAVE_DECL__SNPRINTF 0

/* Define to 1 if you have the declaration of `_snwprintf', and to 0 if you
   don't. */
#define HAVE_DECL__SNWPRINTF 0

/* Define to 1 if you have the <dlfcn.h> header file. */
#define HAVE_DLFCN_H 1

/* Define to 1 if you have the `expf' function. */
#define HAVE_EXPF 1

/* Define to 1 if you have the <features.h> header file. */
#define HAVE_FEATURES_H 1

/* Define to 1 if you have the `fwprintf' function. */
#define HAVE_FWPRINTF 1

/* Define to 1 if you have the `gdImageGif' function. */
/* #undef HAVE_GDIMAGEGIF */

/* Define to 1 if you have the `gdImageJpeg' function. */
/* #undef HAVE_GDIMAGEJPEG */

/* Define to 1 if you have the `gdImagePng' function. */
/* #undef HAVE_GDIMAGEPNG */

/* Define to 1 if you have the `getcwd' function. */
#define HAVE_GETCWD 1

/* Define to 1 if you have the `getegid' function. */
#define HAVE_GETEGID 1

/* Define to 1 if you have the `geteuid' function. */
#define HAVE_GETEUID 1

/* Define to 1 if you have the `getgid' function. */
#define HAVE_GETGID 1

/* Define to 1 if you have the `getline' function. */
#define HAVE_GETLINE 1

/* Define to 1 if you have the `getpagesize' function. */
#define HAVE_GETPAGESIZE 1

/* Define to 1 if you have the `getpwuid' function. */
#define HAVE_GETPWUID 1

/* Define if the GNU gettext() function is already present or preinstalled. */
/* #undef HAVE_GETTEXT */

/* Define to 1 if you have the `getuid' function. */
#define HAVE_GETUID 1

/* Define to 1 if you have the <GL/glu.h> header file. */
/* #undef HAVE_GL_GLU_H */
#define HAVE_GL_GLU_H 1

/* Define to 1 if you have the <GL/gl.h> header file. */
/* #undef HAVE_GL_GL_H */
#define HAVE_GL_GL_H 1

/* Define if you have the iconv() function and it works. */
#define HAVE_ICONV 1

/* Define if you have the 'intmax_t' type in <stdint.h> or <inttypes.h>. */
#define HAVE_INTMAX_T 1

/* Define to 1 if you have the <inttypes.h> header file. */
#define HAVE_INTTYPES_H 1

/* Define if <inttypes.h> exists, doesn't clash with <sys/types.h>, and
   declares uintmax_t. */
#define HAVE_INTTYPES_H_WITH_UINTMAX 1

/* Define if you have <langinfo.h> and nl_langinfo(CODESET). */
#define HAVE_LANGINFO_CODESET 1

/* Define if your <locale.h> file defines LC_MESSAGES. */
#define HAVE_LC_MESSAGES 1

/* Define to 1 if you have the `dl' library (-ldl). */
#define HAVE_LIBDL 1

/* Define to 1 if you have the `dmalloc' library (-ldmalloc). */
/* #undef HAVE_LIBDMALLOC */

/* Define to 1 if you have the `efence' library (-lefence). */
/* #undef HAVE_LIBEFENCE */

/* Define to 1 if you have the `fl' library (-lfl). */
#define HAVE_LIBFL 1

/* Define to 1 if you have the `ICE' library (-lICE). */
/* #undef HAVE_LIBICE */

/* Define to 1 if you have the `m' library (-lm). */
#define HAVE_LIBM 1

/* Define to 1 if you have the `SM' library (-lSM). */
/* #undef HAVE_LIBSM */

/* Define to 1 if you have the `X11' library (-lX11). */
/* #undef HAVE_LIBX11 */

/* Define to 1 if you have the `Xext' library (-lXext). */
/* #undef HAVE_LIBXEXT */

/* Define to 1 if you have the `Xm' library (-lXm). */
/* #undef HAVE_LIBXM */

/* Define to 1 if you have the `Xmu' library (-lXmu). */
/* #undef HAVE_LIBXMU */

/* Define to 1 if you have the `xnet' library (-lxnet). */
/* #undef HAVE_LIBXNET */

/* Define to 1 if you have the `Xpm' library (-lXpm). */
/* #undef HAVE_LIBXPM */

/* Define to 1 if you have the `Xt' library (-lXt). */
/* #undef HAVE_LIBXT */

/* Define to 1 if you have the <limits.h> header file. */
#define HAVE_LIMITS_H 1

/* Define to 1 if you have the <locale.h> header file. */
#define HAVE_LOCALE_H 1

/* Define to 1 if you have the `logf' function. */
#define HAVE_LOGF 1

/* Define to 1 if the system has the type 'long long int'. */
#define HAVE_LONG_LONG_INT 1

/* Define to 1 if you have the `mbrtowc' function. */
#define HAVE_MBRTOWC 1

/* Define to 1 if you have the <memory.h> header file. */
#define HAVE_MEMORY_H 1

/* Define to 1 if you have the `mempcpy' function. */
#define HAVE_MEMPCPY 1

/* Define to 1 if you have the `mkdir' function. */
#define HAVE_MKDIR 1

/* Define to 1 if you have the `mkdtemp' function. */
#define HAVE_MKDTEMP 1

/* Define to 1 if you have a working `mmap' system call. */
#define HAVE_MMAP 1

/* Define to 1 if you have the `munmap' function. */
#define HAVE_MUNMAP 1

/* Define to 1 if you have the <netdb.h> header file. */
#define HAVE_NETDB_H 1

/* Define to 1 if you have the <netinet/in.h> header file. */
#define HAVE_NETINET_IN_H 1

/* Define to 1 if you have the `newlocale' function. */
#define HAVE_NEWLOCALE 1

/* Define to 1 if you have the <OpenGL/glu.h> header file. */
/* #undef HAVE_OPENGL_GLU_H */

/* Define to 1 if you have the <OpenGL/gl.h> header file. */
/* #undef HAVE_OPENGL_GL_H */

/* Define to 1 if you have the `popen' function. */
#define HAVE_POPEN 1

/* Define if your printf() function supports format strings with positions. */
#define HAVE_POSIX_PRINTF 1

/* Define if you have POSIX threads libraries and header files. */
/* #undef HAVE_PTHREAD */

/* Define if the <pthread.h> defines PTHREAD_MUTEX_RECURSIVE. */
/* #undef HAVE_PTHREAD_MUTEX_RECURSIVE */

/* Define if the POSIX multithreading library has read/write locks. */
/* #undef HAVE_PTHREAD_RWLOCK */

/* Define to 1 if you have the `putenv' function. */
#define HAVE_PUTENV 1

/* Define to 1 if you have the <pwd.h> header file. */
#define HAVE_PWD_H 1

/* Define to 1 if you have the `rand' function. */
#define HAVE_RAND 1

/* Define to 1 if you have the `random' function. */
#define HAVE_RANDOM 1

/* Define to 1 if you have the `realpath' function. */
#define HAVE_REALPATH 1

/* Define to 1 if you have the `regcomp' function. */
#define HAVE_REGCOMP 1

/* Define to 1 if you have the <regex.h> header file. */
#define HAVE_REGEX_H 1

/* Define to 1 if you have the `re_comp' function. */
#define HAVE_RE_COMP 1

/* Define to 1 if you have the `rint' function. */
#define HAVE_RINT 1

/* Define to 1 if you have the `setenv' function. */
#define HAVE_SETENV 1

/* Define to 1 if you have the `setlocale' function. */
#define HAVE_SETLOCALE 1

/* Define to 1 if you have the `snprintf' function. */
#define HAVE_SNPRINTF 1

/* Define to 1 if you have the `stat' function. */
#define HAVE_STAT 1

/* Define to 1 if you have the <stddef.h> header file. */
#define HAVE_STDDEF_H 1

/* Define to 1 if you have the <stdint.h> header file. */
#define HAVE_STDINT_H 1

/* Define if <stdint.h> exists, doesn't clash with <sys/types.h>, and declares
   uintmax_t. */
#define HAVE_STDINT_H_WITH_UINTMAX 1

/* Define to 1 if you have the <stdlib.h> header file. */
#define HAVE_STDLIB_H 1

/* Define to 1 if you have the `stpcpy' function. */
#define HAVE_STPCPY 1

/* Define to 1 if you have the `strcasecmp' function. */
#define HAVE_STRCASECMP 1

/* Define to 1 if you have the `strcasestr' function. */
#define HAVE_STRCASESTR 1

/* Define to 1 if you have the `strdup' function. */
#define HAVE_STRDUP 1

/* Define to 1 if you have the `strerror' function. */
#define HAVE_STRERROR 1

/* Define to 1 if you have the <strings.h> header file. */
#define HAVE_STRINGS_H 1

/* Define to 1 if you have the <string.h> header file. */
#define HAVE_STRING_H 1

/* Define to 1 if you have the `strnlen' function. */
#define HAVE_STRNLEN 1

/* Define to 1 if you have the `strtoul' function. */
#define HAVE_STRTOUL 1

/* Define to 1 if you have the `symlink' function. */
#define HAVE_SYMLINK 1

/* Define to 1 if you have the <sys/param.h> header file. */
#define HAVE_SYS_PARAM_H 1

/* Define to 1 if you have the <sys/socket.h> header file. */
#define HAVE_SYS_SOCKET_H 1

/* Define to 1 if you have the <sys/stat.h> header file. */
#define HAVE_SYS_STAT_H 1

/* Define to 1 if you have the <sys/times.h> header file. */
#define HAVE_SYS_TIMES_H 1

/* Define to 1 if you have the <sys/types.h> header file. */
#define HAVE_SYS_TYPES_H 1

/* Define to 1 if you have the <sys/wait.h> header file. */
#define HAVE_SYS_WAIT_H 1

/* Define to 1 if you have the `tsearch' function. */
#define HAVE_TSEARCH 1

/* Define if you have the 'uintmax_t' type in <stdint.h> or <inttypes.h>. */
#define HAVE_UINTMAX_T 1

/* Define to 1 if you have the <unistd.h> header file. */
#define HAVE_UNISTD_H 1

/* Define to 1 if the system has the type 'unsigned long long int'. */
#define HAVE_UNSIGNED_LONG_LONG_INT 1

/* Define to 1 if you have the `uselocale' function. */
#define HAVE_USELOCALE 1

/* Use nonstandard varargs form for the GLU tesselator callback */
/* #undef HAVE_VARARGS_GLU_TESSCB */

/* Define to 1 or 0, depending whether the compiler supports simple visibility
   declarations. */
#define HAVE_VISIBILITY 1

/* Define to 1 if you have the `vsnprintf' function. */
#define HAVE_VSNPRINTF 1

/* Define if you have the 'wchar_t' type. */
#define HAVE_WCHAR_T 1

/* Define to 1 if you have the `wcrtomb' function. */
#define HAVE_WCRTOMB 1

/* Define to 1 if you have the `wcslen' function. */
#define HAVE_WCSLEN 1

/* Define to 1 if you have the `wcsnlen' function. */
#define HAVE_WCSNLEN 1

/* Define to 1 if you have the <windows.h> header file. */
/* #undef HAVE_WINDOWS_H */

/* Define if you have the 'wint_t' type. */
#define HAVE_WINT_T 1

/* Define to 1 if O_NOATIME works. */
#define HAVE_WORKING_O_NOATIME 1

/* Define to 1 if O_NOFOLLOW works. */
#define HAVE_WORKING_O_NOFOLLOW 1

/* Define to 1 if Xinerama is available */
/* #undef HAVE_XINERAMA */

/* Define to 1 if you have the <Xm/Xm.h> header file. */
/* #undef HAVE_XM_XM_H */

/* Define to 1 if Xrender is available */
/* #undef HAVE_XRENDER */

/* Define to 1 if you have the `_mkdir' function. */
/* #undef HAVE__MKDIR */

/* Define to 1 if you have the `_spawnvp' function. */
/* #undef HAVE__SPAWNVP */

/* Define to 1 if you have the `__fsetlocking' function. */
#define HAVE___FSETLOCKING 1

/* Define as const if the declaration of iconv() needs const. */
#define ICONV_CONST 

/* Define if integer division by zero raises signal SIGFPE. */
#define INTDIV0_RAISES_SIGFPE 1

/* library file name */
#define LIBRARYFILENAME "pcblib"

/* m4 executible */
#define M4 /usr/bin/m4

/* Define if mkdir takes only one argument. */
/* #undef MKDIR_TAKES_ONE_ARG */

/* Define if canonicalize_file_name is not declared in system header files. */
/* #undef NEED_DECLARATION_CANONICALIZE_FILE_NAME */

/* Name of package */
#define PACKAGE "pcb"

/* Define to the address where bug reports for this package should be sent. */
#define PACKAGE_BUGREPORT ""

/* Define to the full name of this package. */
#define PACKAGE_NAME "pcb"

/* Define to the full name and version of this package. */
#define PACKAGE_STRING "pcb 4.3.0"

/* Define to the one symbol short name of this package. */
#define PACKAGE_TARNAME "pcb"

/* Define to the home page for this package. */
#define PACKAGE_URL ""

/* Define to the version of this package. */
#define PACKAGE_VERSION "4.3.0"

/* Directory separator char */
#define PCB_DIR_SEPARATOR_C '/'

/* Directory separator string */
#define PCB_DIR_SEPARATOR_S "/"

/* Search path separator string */
#define PCB_PATH_DELIMETER ":"

/* Define if <inttypes.h> exists and defines unusable PRI* macros. */
/* #undef PRI_MACROS_BROKEN */

/* Define to necessary symbol if this constant uses a non-standard name on
   your system. */
/* #undef PTHREAD_CREATE_JOINABLE */

/* Define if the pthread_in_use() detection is hard. */
/* #undef PTHREAD_IN_USE_DETECTION_HARD */

/* Define as the maximum value of type 'size_t', if the system doesn't define
   it. */
#ifndef SIZE_MAX
/* # undef SIZE_MAX */
#endif

/* If using the C implementation of alloca, define if you know the
   direction of stack growth for your system; otherwise it will be
   automatically deduced at runtime.
	STACK_DIRECTION > 0 => grows toward higher addresses
	STACK_DIRECTION < 0 => grows toward lower addresses
	STACK_DIRECTION = 0 => direction of growth unknown */
/* #undef STACK_DIRECTION */

/* Define to 1 if you have the ANSI C header files. */
#define STDC_HEADERS 1

/* Define to 1 to enable toporouter graphical output */
#define TOPO_OUTPUT_ENABLED 0

/* Define if the POSIX multithreading library can be used. */
/* #undef USE_POSIX_THREADS */

/* Define if references to the POSIX multithreading library should be made
   weak. */
/* #undef USE_POSIX_THREADS_WEAK */

/* Define if the GNU Pth multithreading library can be used. */
/* #undef USE_PTH_THREADS */

/* Define if references to the GNU Pth multithreading library should be made
   weak. */
/* #undef USE_PTH_THREADS_WEAK */

/* Define if the old Solaris multithreading library can be used. */
/* #undef USE_SOLARIS_THREADS */

/* Define if references to the old Solaris multithreading library should be
   made weak. */
/* #undef USE_SOLARIS_THREADS_WEAK */

/* Enable extensions on AIX 3, Interix.  */
#ifndef _ALL_SOURCE
# define _ALL_SOURCE 1
#endif
/* Enable GNU extensions on systems that have them.  */
#ifndef _GNU_SOURCE
# define _GNU_SOURCE 1
#endif
/* Enable threading extensions on Solaris.  */
#ifndef _POSIX_PTHREAD_SEMANTICS
# define _POSIX_PTHREAD_SEMANTICS 1
#endif
/* Enable extensions on HP NonStop.  */
#ifndef _TANDEM_SOURCE
# define _TANDEM_SOURCE 1
#endif
/* Enable general extensions on Solaris.  */
#ifndef __EXTENSIONS__
# define __EXTENSIONS__ 1
#endif


/* Define if the native Windows multithreading API can be used. */
/* #undef USE_WINDOWS_THREADS */

/* Version number of package */
#define VERSION "4.3.0"

/* Define to 1 if the X Window System is missing or not being used. */
/* #undef X_DISPLAY_MISSING */

/* Define to 1 if `lex' declares `yytext' as a `char *' by default, not a
   `char[]'. */
#define YYTEXT_POINTER 1

/* Define to 1 if on MINIX. */
/* #undef _MINIX */

/* Define to 2 if the system does not provide POSIX.1 features except with
   this defined. */
/* #undef _POSIX_1_SOURCE */

/* Define to 1 if you need to in order for `stat' and other things to work. */
/* #undef _POSIX_SOURCE */

/* Please see the Gnulib manual for how to use these macros.

   Suppress extern inline with HP-UX cc, as it appears to be broken; see
   <http://lists.gnu.org/archive/html/bug-texinfo/2013-02/msg00030.html>.

   Suppress extern inline with Sun C in standards-conformance mode, as it
   mishandles inline functions that call each other.  E.g., for 'inline void f
   (void) { } inline void g (void) { f (); }', c99 incorrectly complains
   'reference to static identifier "f" in extern inline function'.
   This bug was observed with Sun C 5.12 SunOS_i386 2011/11/16.

   Suppress extern inline (with or without __attribute__ ((__gnu_inline__)))
   on configurations that mistakenly use 'static inline' to implement
   functions or macros in standard C headers like <ctype.h>.  For example,
   if isdigit is mistakenly implemented via a static inline function,
   a program containing an extern inline function that calls isdigit
   may not work since the C standard prohibits extern inline functions
   from calling static functions.  This bug is known to occur on:

     OS X 10.8 and earlier; see:
     http://lists.gnu.org/archive/html/bug-gnulib/2012-12/msg00023.html

     DragonFly; see
     http://muscles.dragonflybsd.org/bulk/bleeding-edge-potential/latest-per-pkg/ah-tty-0.3.12.log

     FreeBSD; see:
     http://lists.gnu.org/archive/html/bug-gnulib/2014-07/msg00104.html

   OS X 10.9 has a macro __header_inline indicating the bug is fixed for C and
   for clang but remains for g++; see <http://trac.macports.org/ticket/41033>.
   Assume DragonFly and FreeBSD will be similar.  */
#if (((defined __APPLE__ && defined __MACH__) \
      || defined __DragonFly__ || defined __FreeBSD__) \
     && (defined __header_inline \
         ? (defined __cplusplus && defined __GNUC_STDC_INLINE__ \
            && ! defined __clang__) \
         : ((! defined _DONT_USE_CTYPE_INLINE_ \
             && (defined __GNUC__ || defined __cplusplus)) \
            || (defined _FORTIFY_SOURCE && 0 < _FORTIFY_SOURCE \
                && defined __GNUC__ && ! defined __cplusplus))))
# define _GL_EXTERN_INLINE_STDHEADER_BUG
#endif
#if ((__GNUC__ \
      ? defined __GNUC_STDC_INLINE__ && __GNUC_STDC_INLINE__ \
      : (199901L <= __STDC_VERSION__ \
         && !defined __HP_cc \
         && !(defined __SUNPRO_C && __STDC__))) \
     && !defined _GL_EXTERN_INLINE_STDHEADER_BUG)
# define _GL_INLINE inline
# define _GL_EXTERN_INLINE extern inline
# define _GL_EXTERN_INLINE_IN_USE
#elif (2 < __GNUC__ + (7 <= __GNUC_MINOR__) && !defined __STRICT_ANSI__ \
       && !defined _GL_EXTERN_INLINE_STDHEADER_BUG)
# if defined __GNUC_GNU_INLINE__ && __GNUC_GNU_INLINE__
   /* __gnu_inline__ suppresses a GCC 4.2 diagnostic.  */
#  define _GL_INLINE extern inline __attribute__ ((__gnu_inline__))
# else
#  define _GL_INLINE extern inline
# endif
# define _GL_EXTERN_INLINE extern
# define _GL_EXTERN_INLINE_IN_USE
#else
# define _GL_INLINE static _GL_UNUSED
# define _GL_EXTERN_INLINE static _GL_UNUSED
#endif

#if 4 < __GNUC__ + (6 <= __GNUC_MINOR__)
# if defined __GNUC_STDC_INLINE__ && __GNUC_STDC_INLINE__
#  define _GL_INLINE_HEADER_CONST_PRAGMA
# else
#  define _GL_INLINE_HEADER_CONST_PRAGMA \
     _Pragma ("GCC diagnostic ignored \"-Wsuggest-attribute=const\"")
# endif
  /* Suppress GCC's bogus "no previous prototype for 'FOO'"
     and "no previous declaration for 'FOO'"  diagnostics,
     when FOO is an inline function in the header; see
     <http://gcc.gnu.org/bugzilla/show_bug.cgi?id=54113>.  */
# define _GL_INLINE_HEADER_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wmissing-prototypes\"") \
    _Pragma ("GCC diagnostic ignored \"-Wmissing-declarations\"") \
    _GL_INLINE_HEADER_CONST_PRAGMA
# define _GL_INLINE_HEADER_END \
    _Pragma ("GCC diagnostic pop")
#else
# define _GL_INLINE_HEADER_BEGIN
# define _GL_INLINE_HEADER_END
#endif

/* Define as a marker that can be attached to declarations that might not
    be used.  This helps to reduce warnings, such as from
    GCC -Wunused-parameter.  */
#ifndef _GL_UNUSED
# if __GNUC__ >= 3 || (__GNUC__ == 2 && __GNUC_MINOR__ >= 7)
#  define _GL_UNUSED __attribute__ ((__unused__))
# else
#  define _GL_UNUSED
# endif
#endif

/* The __pure__ attribute was added in gcc 2.96.  */
#ifndef _GL_ATTRIBUTE_PURE
# if __GNUC__ > 2 || (__GNUC__ == 2 && __GNUC_MINOR__ >= 96)
#  define _GL_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define _GL_ATTRIBUTE_PURE /* empty */
# endif
#endif


/* Define to `__inline__' or `__inline' if that's what the C compiler
   calls it, or to nothing if 'inline' is not supported under any name.  */
#ifndef __cplusplus
/* #undef inline */
#endif

/* Define as the type of the result of subtracting two pointers, if the system
   doesn't define it. */
/* #undef ptrdiff_t */

/* Define to `unsigned int' if <sys/types.h> does not define. */
/* #undef size_t */

/* Define to unsigned long or unsigned long long if <stdint.h> and
   <inttypes.h> don't define. */
/* #undef uintmax_t */


#define __libc_lock_t                   gl_lock_t
#define __libc_lock_define              gl_lock_define
#define __libc_lock_define_initialized  gl_lock_define_initialized
#define __libc_lock_init                gl_lock_init
#define __libc_lock_lock                gl_lock_lock
#define __libc_lock_unlock              gl_lock_unlock
#define __libc_lock_recursive_t                   gl_recursive_lock_t
#define __libc_lock_define_recursive              gl_recursive_lock_define
#define __libc_lock_define_initialized_recursive  gl_recursive_lock_define_initialized
#define __libc_lock_init_recursive                gl_recursive_lock_init
#define __libc_lock_lock_recursive                gl_recursive_lock_lock
#define __libc_lock_unlock_recursive              gl_recursive_lock_unlock
#define glthread_in_use  libintl_thread_in_use
#define glthread_lock_init_func     libintl_lock_init_func
#define glthread_lock_lock_func     libintl_lock_lock_func
#define glthread_lock_unlock_func   libintl_lock_unlock_func
#define glthread_lock_destroy_func  libintl_lock_destroy_func
#define glthread_rwlock_init_multithreaded     libintl_rwlock_init_multithreaded
#define glthread_rwlock_init_func              libintl_rwlock_init_func
#define glthread_rwlock_rdlock_multithreaded   libintl_rwlock_rdlock_multithreaded
#define glthread_rwlock_rdlock_func            libintl_rwlock_rdlock_func
#define glthread_rwlock_wrlock_multithreaded   libintl_rwlock_wrlock_multithreaded
#define glthread_rwlock_wrlock_func            libintl_rwlock_wrlock_func
#define glthread_rwlock_unlock_multithreaded   libintl_rwlock_unlock_multithreaded
#define glthread_rwlock_unlock_func            libintl_rwlock_unlock_func
#define glthread_rwlock_destroy_multithreaded  libintl_rwlock_destroy_multithreaded
#define glthread_rwlock_destroy_func           libintl_rwlock_destroy_func
#define glthread_recursive_lock_init_multithreaded     libintl_recursive_lock_init_multithreaded
#define glthread_recursive_lock_init_func              libintl_recursive_lock_init_func
#define glthread_recursive_lock_lock_multithreaded     libintl_recursive_lock_lock_multithreaded
#define glthread_recursive_lock_lock_func              libintl_recursive_lock_lock_func
#define glthread_recursive_lock_unlock_multithreaded   libintl_recursive_lock_unlock_multithreaded
#define glthread_recursive_lock_unlock_func            libintl_recursive_lock_unlock_func
#define glthread_recursive_lock_destroy_multithreaded  libintl_recursive_lock_destroy_multithreaded
#define glthread_recursive_lock_destroy_func           libintl_recursive_lock_destroy_func
#define glthread_once_func            libintl_once_func
#define glthread_once_singlethreaded  libintl_once_singlethreaded
#define glthread_once_multithreaded   libintl_once_multithreaded

