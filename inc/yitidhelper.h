/*
 * 版权属于：yitter(yitter@126.com)
 * 开源地址：https://gitee.com/yitter/idgenerator
 */
#ifndef __YITIDHELPER_H__
#define __YITIDHELPER_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include "common.h"
#include "idgenerator.h"

// TAP_DLLEXPORT
extern void SetIdGenerator(IdGeneratorOptions options);

// TAP_DLLEXPORT
extern void SetWorkerId(uint32_t workerId);

// TAP_DLLEXPORT
extern uint64_t NextId(void);

#ifdef __cplusplus
}
#endif

#endif // !__YITIDHELPER_H__
