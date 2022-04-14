/*
 * @file    snowflake.h
 * @brief   SnowFlack 软件包 API 文件
 * @author  2022alpha
 * @version v0.1.0
 * @date    2022-03-18
*/
#ifndef __SNOWFLAKE_H__
#define __SNOWFLAKE_H__

#include <stdint.h>

void snowflake_init(uint32_t workerid, uint8_t method, uint8_t worker_id_bit_length, uint8_t Seq_bit_length);
uint64_t snowflake_get_id(void);

#endif // !__SNOWFLAKE_H__
