
#ifndef BLACK_EXPORTED_H
#define BLACK_EXPORTED_H

#ifdef BLACKENGINE_STATIC_DEFINE
#  define BLACK_EXPORTED
#  define BLACKENGINE_NO_EXPORT
#else
#  ifndef BLACK_EXPORTED
#    ifdef BlackEngine_EXPORTS
        /* We are building this library */
#      define BLACK_EXPORTED __declspec(dllexport)
#    else
        /* We are using this library */
#      define BLACK_EXPORTED __declspec(dllimport)
#    endif
#  endif

#  ifndef BLACKENGINE_NO_EXPORT
#    define BLACKENGINE_NO_EXPORT 
#  endif
#endif

#ifndef BLACKENGINE_DEPRECATED
#  define BLACKENGINE_DEPRECATED __attribute__ ((__deprecated__))
#endif

#ifndef BLACKENGINE_DEPRECATED_EXPORT
#  define BLACKENGINE_DEPRECATED_EXPORT BLACK_EXPORTED BLACKENGINE_DEPRECATED
#endif

#ifndef BLACKENGINE_DEPRECATED_NO_EXPORT
#  define BLACKENGINE_DEPRECATED_NO_EXPORT BLACKENGINE_NO_EXPORT BLACKENGINE_DEPRECATED
#endif

#if 0 /* DEFINE_NO_DEPRECATED */
#  ifndef BLACKENGINE_NO_DEPRECATED
#    define BLACKENGINE_NO_DEPRECATED
#  endif
#endif

#endif /* BLACK_EXPORTED_H */
