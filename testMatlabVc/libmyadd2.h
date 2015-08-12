//
// MATLAB Compiler: 4.16 (R2011b)
// Date: Sat Jun 20 23:37:39 2015
// Arguments: "-B" "macro_default" "-W" "cpplib:libmyadd2" "-T" "link:lib"
// "myadd2.m" 
//

#ifndef __libmyadd2_h
#define __libmyadd2_h 1

#if defined(__cplusplus) && !defined(mclmcrrt_h) && defined(__linux__)
#  pragma implementation "mclmcrrt.h"
#endif
#include "mclmcrrt.h"
#include "mclcppclass.h"
#ifdef __cplusplus
extern "C" {
#endif

#if defined(__SUNPRO_CC)
/* Solaris shared libraries use __global, rather than mapfiles
 * to define the API exported from a shared library. __global is
 * only necessary when building the library -- files including
 * this header file to use the library do not need the __global
 * declaration; hence the EXPORTING_<library> logic.
 */

#ifdef EXPORTING_libmyadd2
#define PUBLIC_libmyadd2_C_API __global
#else
#define PUBLIC_libmyadd2_C_API /* No import statement needed. */
#endif

#define LIB_libmyadd2_C_API PUBLIC_libmyadd2_C_API

#elif defined(_HPUX_SOURCE)

#ifdef EXPORTING_libmyadd2
#define PUBLIC_libmyadd2_C_API __declspec(dllexport)
#else
#define PUBLIC_libmyadd2_C_API __declspec(dllimport)
#endif

#define LIB_libmyadd2_C_API PUBLIC_libmyadd2_C_API


#else

#define LIB_libmyadd2_C_API

#endif

/* This symbol is defined in shared libraries. Define it here
 * (to nothing) in case this isn't a shared library. 
 */
#ifndef LIB_libmyadd2_C_API 
#define LIB_libmyadd2_C_API /* No special import/export declaration */
#endif

extern LIB_libmyadd2_C_API 
bool MW_CALL_CONV libmyadd2InitializeWithHandlers(
       mclOutputHandlerFcn error_handler, 
       mclOutputHandlerFcn print_handler);

extern LIB_libmyadd2_C_API 
bool MW_CALL_CONV libmyadd2Initialize(void);

extern LIB_libmyadd2_C_API 
void MW_CALL_CONV libmyadd2Terminate(void);



extern LIB_libmyadd2_C_API 
void MW_CALL_CONV libmyadd2PrintStackTrace(void);

extern LIB_libmyadd2_C_API 
bool MW_CALL_CONV mlxMyadd2(int nlhs, mxArray *plhs[], int nrhs, mxArray *prhs[]);

extern LIB_libmyadd2_C_API 
long MW_CALL_CONV libmyadd2GetMcrID();


#ifdef __cplusplus
}
#endif

#ifdef __cplusplus

/* On Windows, use __declspec to control the exported API */
#if defined(_MSC_VER) || defined(__BORLANDC__)

#ifdef EXPORTING_libmyadd2
#define PUBLIC_libmyadd2_CPP_API __declspec(dllexport)
#else
#define PUBLIC_libmyadd2_CPP_API __declspec(dllimport)
#endif

#define LIB_libmyadd2_CPP_API PUBLIC_libmyadd2_CPP_API

#else

#if !defined(LIB_libmyadd2_CPP_API)
#if defined(LIB_libmyadd2_C_API)
#define LIB_libmyadd2_CPP_API LIB_libmyadd2_C_API
#else
#define LIB_libmyadd2_CPP_API /* empty! */ 
#endif
#endif

#endif

extern LIB_libmyadd2_CPP_API void MW_CALL_CONV myadd2(int nargout, mwArray& y, mwArray& z, const mwArray& a, const mwArray& b);

#endif
#endif
