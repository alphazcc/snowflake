/*
 * @file    snowflake.h
 * @brief   SnowFlack 软件包 API 文件
 * @author  2022alpha
 * @version v0.1.0
 * @date    2022-03-18
*/
#ifndef __SNOWFLAKE_H__
#define __SNOWFLAKE_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

#define USING_MULTITHREAD

void snowflake_init(uint32_t workerId, uint8_t method, uint8_t wkIdLen,
                    uint8_t seqLen, uint32_t drifts);
uint64_t snowflake_get_id(void);

#ifdef __cplusplus
}
#endif

#endif
