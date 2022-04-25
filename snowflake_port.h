/*
 * @file    snowflake_port.h
 * @brief   SnowFlack 软件包 Port 头文件
 * @author  2022alpha
 * @version v0.1.0 
 * @date    2022-03-18
*/
#ifndef __SMOWFLAKE_PORT_H__
#define __SMOWFLAKE_PORT_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <rtthread.h>
#include <stdint.h>
#include "snowflake.h"

#ifdef USING_MULTITHREAD
#define SNOWFLAKE_LOCK		snowflake_lock()
#define SNOWFLAKE_UNLOCK	snowflake_unlock()
#else
#define SNOWFLAKE_LOCK
#define SNOWFLAKE_UNLOCK
#endif

#define SNOWFLAKE_MALLOC	rt_malloc
#define SNOWFLAKE_FREE		rt_free

void snowflake_lock(void);
void snowflake_unlock(void);
extern int64_t GetSystemCurrentMicroTime(void);

#ifdef __cplusplus
}
#endif

#endif
