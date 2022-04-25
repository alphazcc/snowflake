/*
 * @file    snowflake_port.c
 * @brief   SnowFlack 软件包 Port 源文件
 * @author  2022alpha
 * @version v0.1.0 
 * @date    2022-03-18
*/
#include <rtthread.h>
#include <sys/time.h>
#include "IdGenerator.h"
#include "snowflake_port.h"

#ifdef USING_MULTITHREAD
    rt_mutex_t snowflake_mux = RT_NULL;
#endif

/**
 * @brief   雪花算法初始化
 * @param   workerId    机器码，必须由外部设定
 * @param   method      雪花计算方式（1 - 漂移算法 | 2 - 传统算法），默认1 
 * @param   wkIdLen     机器码位长，默认值6，取值范围 [1, 15]
 * @param   seqLen      序列数位长，默认值6，取值范围 [3, 21]
 * @param   drifts      最大漂移次数（含），推荐范围 500-20000（与计算能力有关） 
 *                      （变量取默认值可设为 0 ）
 */
void snowflake_init(uint32_t workerId, uint8_t method, uint8_t wkIdLen,
                        uint8_t seqLen, uint32_t drifts)
{
    IdGeneratorOptions options = BuildIdGenOptions(workerId);

    if (method == 1 || method == 2)
    {
        options.Method = method;
    }

    if (wkIdLen >= 1 && wkIdLen <= 15)
    {
        options.WorkerIdBitLength = wkIdLen;
    }

    if (seqLen >= 3 && seqLen <= 21)
    {
        options.SeqBitLength = seqLen;
    }

    //options.TopOverCostCount = drifts;

    SetIdGenerator(options);

#ifdef USING_MULTITHREAD
    snowflake_mux = rt_mutex_create("snowflake_mux", RT_IPC_FLAG_PRIO);
#endif
}

uint64_t snowflake_get_id(void)
{
    return NextId();
}

#ifdef USING_MULTITHREAD
void snowflake_lock(void)
{
    rt_mutex_take(snowflake_mux, RT_WAITING_FOREVER);
}

void snowflake_unlock(void)
{
    rt_mutex_release(snowflake_mux);
}
#endif

extern int64_t GetSystemCurrentMicroTime(void)
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return ((int64_t)tv.tv_sec * 1000000 + tv.tv_usec);
 }
