/*
 * 版权属于：yitter(yitter@126.com)
 * 开源地址：https://gitee.com/yitter/idgenerator
 */
#pragma once

#include <stdint.h>
#include "common.h"
#include "IdGenerator.h"

//TAP_DLLEXPORT
//extern void TAP_STDCALL SetIdGenerator(IdGeneratorOptions options);
extern void SetIdGenerator(IdGeneratorOptions options);
//TAP_DLLEXPORT
//extern void TAP_STDCALL SetWorkerId(uint32_t workerId);
extern void SetWorkerId(uint32_t workerId);
//TAP_DLLEXPORT
//extern int64_t TAP_STDCALL NextId();
extern uint64_t NextId();
