//
// Created by zhouzj on 2021/3/28.
//
#pragma once

#ifdef _WIN32
#define TAP_CDECL  __cdecl
#define TAP_STDCALL __stdcall
#define TAP_DLLEXPORT __declspec(dllexport)
#else
#define TAP_CDECL
#define TAP_STDCALL
#define TAP_DLLEXPORT
#endif

