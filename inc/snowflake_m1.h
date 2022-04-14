/*
 * 版权属于：yitter(yitter@126.com)
 * 代码翻译：amuluowin
 * 代码修订：yitter
 * 开源地址：https://gitee.com/yitter/idgenerator
 */
#ifndef __SNOWFLAKE_M1_H__
#define __SNOWFLAKE_M1_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdbool.h>
#include "snowflake_port.h"

typedef struct SnowFlakeWorker
{
    uint8_t Method;
    uint64_t BaseTime;
    uint32_t WorkerId;
    uint8_t WorkerIdBitLength;
    uint8_t SeqBitLength;
    uint32_t MaxSeqNumber;
    uint32_t MinSeqNumber;
    uint32_t TopOverCostCount;

    uint8_t _TimestampShift;
    uint32_t _CurrentSeqNumber;
    uint64_t _LastTimeTick;
    uint64_t _TurnBackTimeTick;
    uint8_t _TurnBackIndex;
    bool _IsOverCost;
    uint32_t _OverCostCountInOneTerm;
    uint32_t _GenCountInOneTerm;
    uint32_t _TermIndex;

} SnowFlakeWorker;

extern SnowFlakeWorker* NewSnowFlakeWorker();

extern uint64_t WorkerM1NextId(SnowFlakeWorker* worker);

extern uint64_t uGetCurrentTimeTick(SnowFlakeWorker* worker);

extern uint64_t uGetNextTimeTick(SnowFlakeWorker* worker);

extern uint64_t uGetCurrentTime();

extern uint64_t uGetCurrentMicroTime();

#ifdef __cplusplus
}
#endif

#endif // !__SNOWFLAKE_M1_H__
