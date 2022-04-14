//
// Created by zhouzj on 2021/3/28.
//

#ifndef __COMMON_H__
#define __COMMON_H__

#ifdef _WIN32
#define TAP_CDECL  __cdecl
#define TAP_STDCALL __stdcall
#define TAP_DLLEXPORT __declspec(dllexport)
#else
#define TAP_CDECL
#define TAP_STDCALL
#define TAP_DLLEXPORT
#endif

#endif // !__COMMON_H__
