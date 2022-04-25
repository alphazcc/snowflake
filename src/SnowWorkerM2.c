/*
 * 版权属于：yitter(yitter@126.com)
 * 代码翻译：amuluowin
 * 代码修订：yitter
 * 开源地址：https://github.com/yitter/idgenerator
 */
#include "SnowWorkerM2.h"
#include "snowflake_port.h"

extern uint64_t WorkerM2NextId(SnowFlakeWorker *worker) {
    SNOWFLAKE_LOCK;
    uint64_t currentTimeTick = GetCurrentTimeTick(worker);
    if (worker->_LastTimeTick == currentTimeTick) {
        worker->_CurrentSeqNumber = (++worker->_CurrentSeqNumber) & worker->MaxSeqNumber;
        if (worker->_CurrentSeqNumber == 0) {
            currentTimeTick = GetNextTimeTick(worker);
        }
    } else {
        worker->_CurrentSeqNumber = worker->MinSeqNumber;
    }
    worker->_LastTimeTick = currentTimeTick;
    uint64_t id = (uint64_t) ((currentTimeTick << worker->_TimestampShift) |
                              (worker->WorkerId << worker->SeqBitLength) |
                              worker->_CurrentSeqNumber);
    SNOWFLAKE_UNLOCK;
    return id;
}
