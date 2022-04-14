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

#include <stdint.h>

uint32_t* snowflake_malloc(uint32_t size);
void snowflake_lock(void);
void snowflake_unlock(void);
void snowflake_init(uint32_t workerid, uint8_t method, uint8_t worker_id_bit_length, uint8_t Seq_bit_length);
uint64_t snowflake_get_id(void);
uint64_t GetSystemCurrentMicroTime(void);

#ifdef __cplusplus
}
#endif

#endif // !__SMOWFLAKE_PORT_H__

