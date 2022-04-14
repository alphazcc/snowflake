/*
 * 版权属于：yitter(yitter@126.com)
 * 代码翻译：amuluowin
 * 代码修订：yitter
 * 开源地址：https://gitee.com/yitter/idgenerator
 */
#ifndef __SNOWFLAKE_M2_H__
#define __SNOWFLAKE_M2_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <stdlib.h>
#include "snowflake_m1.h"

extern uint64_t WorkerM2NextId(SnowFlakeWorker* worker);

#ifdef __cplusplus
}
#endif

#endif // !__SNOWFLAKE_M2_H__
