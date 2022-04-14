/*
 * 版权属于：yitter(yitter@126.com)
 * 代码翻译：amuluowin
 * 代码修订：yitter
 * 开源地址：https://github.com/yitter/idgenerator
 */
#include "snowflake_m2.h"

 /**
  * @brief   计算方式 2 传统雪花算法
  * @param   worker 参数
  * @return  ID
  */
extern uint64_t WorkerM2NextId(SnowFlakeWorker *worker) 
{
    snowflake_lock();
    uint64_t currentTimeTick = uGetCurrentTimeTick(worker);
    if (worker->_LastTimeTick == currentTimeTick) 
    {
        worker->_CurrentSeqNumber = (++worker->_CurrentSeqNumber) & worker->MaxSeqNumber;
        if (worker->_CurrentSeqNumber == 0) 
        {
            currentTimeTick = uGetNextTimeTick(worker);
        }
    } 
    else 
    {
        worker->_CurrentSeqNumber = worker->MinSeqNumber;
    }
    worker->_LastTimeTick = currentTimeTick;
    uint64_t id = (uint64_t) ((currentTimeTick << worker->_TimestampShift) |
                              (worker->WorkerId << worker->SeqBitLength) | worker->_CurrentSeqNumber);
    snowflake_unlock();
    return id;
}
