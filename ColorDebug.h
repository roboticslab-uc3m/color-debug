// -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*-

/**
 * ColorDebug
 * Version: 0.17 - Allow downstreams to disable colors, rename color tags.
 * Version: 0.16 - Add support for Windows 10 console VT sequences.
 * Version: 0.15 - Deprecate CD_PERROR, use strerror from <string.h> instead.
 * Version: 0.14 - Fix semicolon bug, add helper printf macros.
 * Version: 0.13 - Call fflush() to avoid issues on Windows.
 * Version: 0.12 - Compatibility with C, no colors on Windows for now.
 * Version: 0.11 - Removed unnecessary namespace.
 * Version: 0.10 - Add CD_FULL_FILE define. Revive CD_PERROR.
 * Version: 0.9 - Add CD_HIDE_**** defines.
 * Version: 0.8 - stderr only on warning and error.
 * Version: 0.7 - fix CD_INFO_NO_HEADER to not print header (thank you, tests).
 * Version: 0.6 - Show file name instead of full path - fix for windows.
 * Version: 0.5 - Drop CD_PERROR (recommend use of CD_ERROR_NO_HEADER instead).
 * Version: 0.4 - __func__ as __FUNCTION__ for VS2008.
 * Version: 0.3 - Added CD_*****_NO_HEADER. Added scopes for each CD_printf macro.
 * Version: 0.2 - Added CD_PERROR.
 * Version: 0.1 - Initial version.
 *
 * Copyright: UC3M 2018 (C)
 * Author:
 * <a href="http://roboticslab.uc3m.es/roboticslab/people/jg-victores">Juan G. Victores</a>
 *
 * CopyPolicy: Released under the terms of the LGPLv2.1 or later, look for LICENSE
 */

#ifndef __COLOR_DEBUG_H__
#define __COLOR_DEBUG_H__

#include <stdio.h>

//-- Fix for old Windows versions.
//-- Thanks: tomlogic @ http://stackoverflow.com/questions/2281970/cross-platform-defining-define-for-macros-function-and-func
#if defined ( WIN32 ) && !defined ( __func__ )
  #define __func__ __FUNCTION__
#endif

//-- Macros for size_t and similar across platforms.
//-- Thanks: dalle @ http://stackoverflow.com/questions/1546789/clean-code-to-printf-size-t-in-c-or-nearest-equivalent-of-c99s-z-in-c
#if defined(_MSC_VER)
  #define CD_SIZE_T    "%Iu"
  #define CD_SSIZE_T   "%Id"
  #define CD_PTRDIFF_T "%Id"
#elif defined(__GNUC__)
  #define CD_SIZE_T    "%zu"
  #define CD_SSIZE_T   "%zd"
  #define CD_PTRDIFF_T "%zd"
#else
  // TODO figure out which to use.
  #if NUMBITS == 32
    #define CD_SIZE_T_SPECIFIER    something_unsigned
    #define CD_SSIZE_T_SPECIFIER   something_signed
    #define CD_PTRDIFF_T_SPECIFIER something_signed
  #else
    #define CD_SIZE_T_SPECIFIER    something_bigger_unsigned
    #define CD_SSIZE_T_SPECIFIER   something_bigger_signed
    #define CD_PTRDIFF_T_SPECIFIER something-bigger_signed
  #endif
#endif

#if defined ( CD_FULL_FILE )
  #define CD_FILE __FILE__
#else
  #include <string.h>  // strrchr

  //-- Show file name instead of full path.
  //-- Thanks: red1ynx @ http://stackoverflow.com/questions/8487986/file-macro-shows-full-path
  #if defined ( WIN32 )  //-- For Windows use '\\' instead of '/'.
    #define CD_FILE (strrchr(__FILE__, '\\') ? strrchr(__FILE__, '\\') + 1 : __FILE__)
  #else
    #define CD_FILE (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)
  #endif
#endif

//-- Color defines.
//-- Thanks: http://stackoverflow.com/questions/1961209/making-some-text-in-printf-appear-in-green-and-red
#define CD_RESET   "\033[0m"
#define CD_BLACK   "\033[30m"      /* Black */
#define CD_RED     "\033[31m"      /* Red */
#define CD_GREEN   "\033[32m"      /* Green */
#define CD_YELLOW  "\033[33m"      /* Yellow */
#define CD_BLUE    "\033[34m"      /* Blue */
#define CD_MAGENTA "\033[35m"      /* Magenta */
#define CD_CYAN    "\033[36m"      /* Cyan */
#define CD_WHITE   "\033[37m"      /* White */
#define CD_BOLDBLACK   "\033[1m\033[30m"      /* Bold Black */
#define CD_BOLDRED     "\033[1m\033[31m"      /* Bold Red */
#define CD_BOLDGREEN   "\033[1m\033[32m"      /* Bold Green */
#define CD_BOLDYELLOW  "\033[1m\033[33m"      /* Bold Yellow */
#define CD_BOLDBLUE    "\033[1m\033[34m"      /* Bold Blue */
#define CD_BOLDMAGENTA "\033[1m\033[35m"      /* Bold Magenta */
#define CD_BOLDCYAN    "\033[1m\033[36m"      /* Bold Cyan */
#define CD_BOLDWHITE   "\033[1m\033[37m"      /* Bold White */

#if defined ( CD_SUPPORTS_VT )
    #ifdef __cplusplus
    extern "C" {
    #endif
        void cd_enable_vt_colors(void);
    #ifdef __cplusplus
    }
    #endif
    #define CD_IF_SUPPORTS_VT(...) __VA_ARGS__
#else
    #define CD_IF_SUPPORTS_VT(...)
#endif

#if !defined ( CD_NO_COLOR ) && ( !defined ( WIN32 ) || defined ( CD_SUPPORTS_VT ) )
    #define CD_FPRINTF(file, fmt, header, ...) do { \
            CD_IF_SUPPORTS_VT(cd_enable_vt_colors()); \
            fprintf(file, fmt); \
            fprintf(file, "[%s] %s:%d %s(): ", header, CD_FILE, __LINE__, __func__); \
            fprintf(file, __VA_ARGS__); \
            fprintf(file, CD_RESET); \
            fflush(file); \
        } while (0)

    #define CD_FPRINTF_NO_HEADER(file, fmt, ...) do { \
            CD_IF_SUPPORTS_VT(cd_enable_vt_colors()); \
            fprintf(file, fmt); \
            fprintf(file, __VA_ARGS__); \
            fprintf(file, CD_RESET); \
            fflush(file); \
        } while (0)
#else
    #define CD_FPRINTF(file, fmt, header, ...) do { \
            fprintf(file, "[%s] %s:%d %s(): ", header, CD_FILE, __LINE__, __func__); \
            fprintf(file, __VA_ARGS__); \
            fflush(file); \
        } while (0)

    #define CD_FPRINTF_NO_HEADER(file, fmt, ...) do { \
            fprintf(file, __VA_ARGS__); \
            fflush(file); \
        } while (0)
#endif

//-- ------------------------ \begin Real macros ------------------------ --//

//-- CD_**** and their corresponding CD_****_NO_HEADER defines.
//-- Thanks: http://en.wikipedia.org/wiki/Variadic_macro
//-- Thanks: http://stackoverflow.com/questions/15549893/modify-printfs-via-macro-to-include-file-and-line-number-information

#if defined ( CD_HIDE_ERROR )
    #define CD_ERROR(...)
    #define CD_ERROR_NO_HEADER(...)
#else
    #define CD_ERROR(...) CD_FPRINTF(stderr, CD_RED, "error", __VA_ARGS__)
    #define CD_ERROR_NO_HEADER(...) CD_FPRINTF_NO_HEADER(stderr, CD_RED, __VA_ARGS__)
#endif

#if defined ( CD_HIDE_WARNING )
    #define CD_WARNING(...)
    #define CD_WARNING_NO_HEADER(...)
#else
    #define CD_WARNING(...) CD_FPRINTF(stderr, CD_YELLOW, "warning", __VA_ARGS__)
    #define CD_WARNING_NO_HEADER(...) CD_FPRINTF_NO_HEADER(stderr, CD_YELLOW, __VA_ARGS__)
#endif

#if defined ( CD_HIDE_SUCCESS )
    #define CD_SUCCESS(...)
    #define CD_SUCCESS_NO_HEADER(...)
#else
    #define CD_SUCCESS(...) CD_FPRINTF(stdout, CD_GREEN, "success", __VA_ARGS__)
    #define CD_SUCCESS_NO_HEADER(...) CD_FPRINTF_NO_HEADER(stdout, CD_GREEN, __VA_ARGS__)
#endif

#if defined ( CD_HIDE_INFO )
    #define CD_INFO(...)
    #define CD_INFO_NO_HEADER(...)
#else
    #define CD_INFO(...) CD_FPRINTF(stdout, CD_WHITE, "info", __VA_ARGS__)
    #define CD_INFO_NO_HEADER(...) CD_FPRINTF_NO_HEADER(stdout, CD_WHITE, __VA_ARGS__)
#endif

#if defined ( CD_HIDE_DEBUG )
    #define CD_DEBUG(...)
    #define CD_DEBUG_NO_HEADER(...)
#else
    #define CD_DEBUG(...) CD_FPRINTF(stdout, CD_BLUE, "debug", __VA_ARGS__)
    #define CD_DEBUG_NO_HEADER(...) CD_FPRINTF_NO_HEADER(stdout, CD_BLUE, __VA_ARGS__)
#endif

//-- Deprecated since v0.15.
#define CD_PERROR(...) CD_ERROR(__VA_ARGS__)

//-- Deprecated since v0.17.
#define RESET   CD_RESET
#define BLACK   CD_BLACK
#define RED     CD_RED
#define GREEN   CD_GREEN
#define YELLOW  CD_YELLOW
#define BLUE    CD_BLUE
#define MAGENTA CD_MAGENTA
#define CYAN    CD_CYAN
#define WHITE   CD_WHITE
#define BOLDBLACK   CD_BOLDBLACK
#define BOLDRED     CD_BOLDRED
#define BOLDGREEN   CD_BOLDGREEN
#define BOLDYELLOW  CD_BOLDYELLOW
#define BOLDBLUE    CD_BOLDBLUE
#define BOLDMAGENTA CD_BOLDMAGENTA
#define BOLDCYAN    CD_BOLDCYAN
#define BOLDWHITE   CD_BOLDWHITE

//-- ------------------------ \end Real macros ------------------------ --//

#endif  // __COLOR_DEBUG_H__
