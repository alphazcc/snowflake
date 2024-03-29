/*
 * @file    snowflake_port.c
 * @brief   SnowFlack 软件包示例文件
 * @author  2022alpha
 * @version v0.1.0 
 * @date    2022-03-18
*/

/*
 * 版权属于：yitter(yitter@126.com)
 * 代码翻译：amuluowin
 * 代码修订：yitter
 */

#include <stdio.h>
#include "rtthread.h"
#include "snowflake.h"

#ifdef USING_MULTITHREAD

#define THREAD_NUM    2
rt_thread_t snowflake_thread1 = RT_NULL;
rt_thread_t snowflake_thread2 = RT_NULL;

void snowflake_thread1_entry(void* parameter)
{
    int GenIdCount = (int*)parameter;
    uint64_t id = 0;
    for (int i = 0; i < GenIdCount; i++)
    {
        id = snowflake_get_id();
        printf("snowflake-thread-1 count: %d\t    ID: %lld\n", i, id);
        rt_thread_mdelay(1);
    }
}

void snowflake_thread2_entry(void* parameter)
{
    int GenIdCount = (int*)parameter;
    uint64_t id = 0;
    for (int i = 0; i < GenIdCount; i++)
    {
        id = snowflake_get_id();
        printf("snowflake-thread-2 count: %d\t    ID: %lld\n", i, id);
        rt_thread_mdelay(1);
    }
}

int GetIdRunThread(const int IdCount)
{
    int parameter = IdCount / THREAD_NUM;

    snowflake_thread1 = rt_thread_create("snowflake_thread1", 
                                            snowflake_thread1_entry,
                                            (void* )parameter, 64, 10, 2);
    if (snowflake_thread1 != RT_NULL)
        rt_thread_startup(snowflake_thread1);

    snowflake_thread2 = rt_thread_create("snowflake_thread2", 
                                            snowflake_thread2_entry,
                                            (void* )parameter, 64, 10, 2);
    if (snowflake_thread2 != RT_NULL)
        rt_thread_startup(snowflake_thread2);

    return 0;
}
#else
void GetIdRunSingle(const int GenIdCount)
{
    uint64_t id = 0;
    for (int i = 0; i < GenIdCount; i++)
    {
        id = snowflake_get_id();
        printf("count: %d\t    ID: %lld\n", i, id);
    }
}
#endif

int snowflake_sample(int argc, char* argv[])
{
    const int GenIdCount = 5000;
    const int method = 1;
    const int workerid = 1;

    snowflake_init(workerid, method,0,0,0);

#ifdef USING_MULTITHREAD
    GetIdRunThread(GenIdCount);
#else
    GetIdRunSingle(GenIdCount);
#endif
    
    return 0;
}

#ifdef RT_USING_FINSH
#include <finsh.h>
MSH_CMD_EXPORT(snowflake_sample, snowflake_sample test);
#endif