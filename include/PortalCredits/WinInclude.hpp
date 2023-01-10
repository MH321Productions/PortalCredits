//An include helper for Windows.h to not use every feature (smaller build time)
#if !defined(PC_WININCLUDE_HPP) && defined(PC_WINDOWS)
#define PC_WININCLUDE_HPP

#if _WIN32_WINNT < 0x0601
    #undef _WIN32_WINNT
    #define _WIN32_WINNT 0x0601
#endif

#include <sdkddkver.h>

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#ifndef NOGDICAPMASKS
#define NOGDICAPMASKS
#endif

/*#ifndef NOSYSMETRICS
//#define NOSYSMETRICS
#endif*/

#ifndef NOMENUS
#define NOMENUS
#endif

#ifndef NOICONS
#define NOICONS
#endif

#ifndef NOSYSCOMMANDS
#define NOSYSCOMMANDS
#endif

#ifndef NORASTEROPS
#define NORASTEROPS
#endif

#ifndef OEMRESOURCE
#define OEMRESOURCE
#endif

#ifndef NOATOM
#define NOATOM
#endif

#ifndef NOCLIPBOARD
#define NOCLIPBOARD
#endif

#ifndef NOCOLOR
#define NOCOLOR
#endif

#ifndef NOCTLMGR
#define NOCTLMGR
#endif

#ifndef NODRAWTEXT
#define NODRAWTEXT
#endif

#ifndef NOKERNEL
#define NOKERNEL
#endif

#ifndef NONLS
#define NONLS
#endif

#ifndef NOMEMMGR
#define NOMEMMGR
#endif

#ifndef NOMETAFILE
#define NOMETAFILE
#endif

#ifndef NOOPENFILE
#define NOOPENFILE
#endif

#ifndef NOSCROLL
#define NOSCROLL
#endif

#ifndef NOSERVICE
#define NOSERVICE
#endif

#ifndef NOSOUND
#define NOSOUND
#endif

#ifndef NOTEXTMETRIC
#define NOTEXTMETRIC
#endif

#ifndef NOWH
#define NOWH
#endif

#ifndef NOCOMM
#define NOCOMM
#endif

#ifndef NOKANJI
#define NOKANJI
#endif

#ifndef NOHELP
#define NOHELP
#endif

#ifndef NOPROFILER
#define NOPROFILER
#endif

#ifndef NODEFERWINDOWPOS
#define NODEFERWINDOWPOS
#endif

#ifndef NOMCX
#define NOMCX
#endif

#ifndef NORPC
#define NORPC
#endif

#ifndef NOPROXYSTUB
#define NOPROXYSTUB
#endif

#ifndef NOIMAGE
#define NOIMAGE
#endif

#ifndef NOTAPE
#define NOTAPE
#endif

#ifndef NOMINMAX
#define NOMINMAX
#endif

#ifndef STRICT
#define STRICT
#endif


#include <Windows.h>

#endif //PC_WININCLUDE_HPP