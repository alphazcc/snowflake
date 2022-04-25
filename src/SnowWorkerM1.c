/*
 * 版权属于：yitter(yitter@126.com)
 * 代码翻译：amuluowin
 * 代码修订：yitter
 * 开源地址：https://github.com/yitter/idgenerator
 */

#include "SnowWorkerM1.h"
#include "snowflake_port.h"

static void EndOverCostAction(int64_t useTimeTick, SnowFlakeWorker *worker);

static int64_t NextOverCostId(SnowFlakeWorker *worker);

static int64_t NextNormalId(SnowFlakeWorker *worker);

static int64_t CalcId(SnowFlakeWorker *worker);

static int64_t CalcTurnBackId(SnowFlakeWorker *worker);


static inline void EndOverCostAction(int64_t useTimeTick, SnowFlakeWorker *worker) {
    // if (worker->_TermIndex > 10000) {
    //     worker->_TermIndex = 0;
    // }
}

static inline int64_t NextOverCostId(SnowFlakeWorker *worker) {
    uint64_t currentTimeTick = GetCurrentTimeTick(worker);
    if (currentTimeTick > worker->_LastTimeTick) {
        EndOverCostAction(currentTimeTick, worker);
        worker->_LastTimeTick = currentTimeTick;
        worker->_CurrentSeqNumber = worker->MinSeqNumber;
        worker->_IsOverCost = false;
        worker->_OverCostCountInOneTerm = 0;
        worker->_GenCountInOneTerm = 0;
        return CalcId(worker);
    }
    if (worker->_OverCostCountInOneTerm > worker->TopOverCostCount) {
        EndOverCostAction(currentTimeTick, worker);
        worker->_LastTimeTick = GetNextTimeTick(worker);
        worker->_CurrentSeqNumber = worker->MinSeqNumber;
        worker->_IsOverCost = false;
        worker->_OverCostCountInOneTerm = 0;
        worker->_GenCountInOneTerm = 0;
        return CalcId(worker);
    }
    if (worker->_CurrentSeqNumber > worker->MaxSeqNumber) {
        worker->_LastTimeTick++;
        worker->_CurrentSeqNumber = worker->MinSeqNumber;
        worker->_IsOverCost = true;
        worker->_OverCostCountInOneTerm++;
        worker->_GenCountInOneTerm++;
        return CalcId(worker);
    }

    worker->_GenCountInOneTerm++;
    return CalcId(worker);
}

static inline int64_t NextNormalId(SnowFlakeWorker *worker) {
    uint64_t currentTimeTick = GetCurrentTimeTick(worker);
    if (currentTimeTick < worker->_LastTimeTick) {
        if (worker->_TurnBackTimeTick < 1) {
            worker->_TurnBackTimeTick = worker->_LastTimeTick - 1;
            worker->_TurnBackIndex++;
            // 每毫秒序列数的前 5 位是预留位，0 用于手工新值，1-4 是时间回拨次序
            // 支持 4 次回拨次序（避免回拨重叠导致 ID 重复），可无限次回拨（次序循环使用）。
            if (worker->_TurnBackIndex > 4) {
                worker->_TurnBackIndex = 1;
            }
        }

        // usleep(1000); // 暂停1ms
        return CalcTurnBackId(worker);
    }

    if (worker->_TurnBackTimeTick > 0) {
        worker->_TurnBackTimeTick = 0;
    }

    if (currentTimeTick > worker->_LastTimeTick) {
        worker->_LastTimeTick = currentTimeTick;
        worker->_CurrentSeqNumber = worker->MinSeqNumber;
        return CalcId(worker);
    }

    if (worker->_CurrentSeqNumber > worker->MaxSeqNumber) {
        worker->_TermIndex++;
        worker->_LastTimeTick++;
        worker->_CurrentSeqNumber = worker->MinSeqNumber;
        worker->_IsOverCost = true;
        worker->_OverCostCountInOneTerm = 1;
        worker->_GenCountInOneTerm = 1;
        return CalcId(worker);
    }

    return CalcId(worker);
}

static inline int64_t CalcId(SnowFlakeWorker *worker) {
    uint64_t result = (worker->_LastTimeTick << worker->_TimestampShift) | (worker->WorkerId << worker->SeqBitLength) |
                      (worker->_CurrentSeqNumber);
    worker->_CurrentSeqNumber++;
    return result;
}

static inline int64_t CalcTurnBackId(SnowFlakeWorker *worker) {
    uint64_t result = (worker->_LastTimeTick << worker->_TimestampShift) | (worker->WorkerId << worker->SeqBitLength) |
                      (worker->_TurnBackTimeTick);
    worker->_TurnBackTimeTick--;
    return result;
}


extern SnowFlakeWorker *NewSnowFlakeWorker() {
    SnowFlakeWorker *worker = (SnowFlakeWorker *)SNOWFLAKE_MALLOC(sizeof(SnowFlakeWorker));
    worker->_IsOverCost = false;
    worker->_LastTimeTick = 0;
    worker->_TurnBackTimeTick = 0;
    worker->_TurnBackIndex = 0;
    worker->_OverCostCountInOneTerm = 0;
    worker->_GenCountInOneTerm = 0;
    worker->_TermIndex = 0;

    return worker;
}

extern uint64_t WorkerM1NextId(SnowFlakeWorker *worker) {
    SNOWFLAKE_LOCK;
    int64_t id = worker->_IsOverCost ? NextOverCostId(worker) : NextNormalId(worker);
    SNOWFLAKE_UNLOCK;
    return id;
}

extern uint64_t GetCurrentTimeTick(SnowFlakeWorker *worker) {
    return (GetCurrentTime() - worker->BaseTime);
}

extern uint64_t GetCurrentTime() {
    return (GetCurrentMicroTime() / 1000);
}

extern uint64_t GetCurrentMicroTime() {
    return GetSystemCurrentMicroTime();
}

extern uint64_t GetNextTimeTick(SnowFlakeWorker *worker) {
    uint64_t tempTimeTicker = GetCurrentTimeTick(worker);
    while (tempTimeTicker <= worker->_LastTimeTick) {
        //usleep(1000);  // 暂停1ms
        tempTimeTicker = GetCurrentTimeTick(worker);
    }
    return tempTimeTicker;
}
