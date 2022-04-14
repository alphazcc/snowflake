/*
 * 版权属于：yitter(yitter@126.com)
 * 开源地址：https://gitee.com/yitter/idgenerator
 */
#ifndef __IDGENERATOR_H__
#define __IDGENERATOR_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include "idgenoptions.h"
#include "snowflake_m1.h"
#include "snowflake_m2.h"
#include "snowflake_port.h"
#include "yitidhelper.h"

typedef struct IdGenerator
{
    SnowFlakeWorker* Worker;

    uint64_t(*NextId)();

} IdGenerator;

static IdGenerator* _idGenerator = NULL;

extern IdGenerator* GetIdGenInstance(void);

extern void SetOptions(IdGeneratorOptions options);

#ifdef __cplusplus
}
#endif

#endif // !__IDGENERATOR_H__
