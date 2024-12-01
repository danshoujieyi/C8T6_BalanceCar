//
// Created by 刘嘉俊 on 24-9-14.
//  日志打印网：https://blog.csdn.net/Mculover666/article/details/105141286
// 日志打印网：https://zhuanlan.zhihu.com/p/701541171?utm_psn=1798699051195179008

#ifndef LOGGER_H
#define LOGGER_H

#ifdef __cplusplus
extern "C" {
#endif

#include "stm32f1xx_hal.h"
#include "stdio.h"
#include <string.h>

#ifndef  USE_LOG
#define  USE_LOG						1
#endif

#ifndef  USE_DUMP
#define  USE_DUMP						1
#endif

#ifndef  USE_BLOCK
#define  USE_BLOCK						1
#endif

#define ONLY_FILENAME(x) (strrchr(x, '\\') ? strrchr(x, '\\')+1 : x)

#if USE_BLOCK > 0
#define BLOCK(s,...)				        \
	do{									        \
			printf("\r\n[BLOCK %s:%d] ",	    \
			ONLY_FILENAME(__FILE__),__LINE__);	\
			printf(s,##__VA_ARGS__);	        \
			printf(",按任意键继续");	            \
			block_flag = 0;				        \
			while(block_flag==0);		        \
			printf("\r\n");				        \
	} while(0)

#else
#define BLOCK(x)
#endif

#if USE_LOG > 0
#define LOG_DEBUG(s,...)	\
			do{	\
				printf("\033[1;36m\r\n[DEBUG %s:%d] ",	\
					ONLY_FILENAME(__FILE__),__LINE__);			\
				printf(s,##__VA_ARGS__);	\
				printf("\33[0m\r\n");		\
			}while(0)
#define LOG_INFO(s,...)	\
			do{                   \
				printf("\033[0;32m\r\n[INFO] ");	\
				printf(s,##__VA_ARGS__);	\
				printf("\33[0m\r\n");		\
			}while(0)
#define LOG_ERROR(s,...)	\
			do{	\
                printf("\033[0;31m\r\n[ERROR %s:%d] ",	\
					ONLY_FILENAME(__FILE__),__LINE__);			\
				printf(s,##__VA_ARGS__);	\
				printf("\33[0m\r\n");				\
			}while(0)
#define LOG_ASSERT(cond)	\
			do { \
                if (!(cond)) { \
                    printf("\r\n[ASSERT] File=[%s],Line=[%ld] Failed to vertify thc condition [\"%s\"]\r\n",__FILE__,__LINE__,#cond); \
                    while(1); \
                } \
			}while(0)
#else
#define LOG_DEBUG(s,...)
	#define LOG_INFO(s,...)
	#define LOG_ERROR(s,...)
	#define LOG_ERROR2()
	#define LOG_ERROR3(cond)
	#define LOG_ERROR4(s,...)
	#define LOG_ASSERT(cond)
#endif


#if USE_DUMP > 0
#define LOG_DUMP(info, data, len,...) \
    do {                              \
        printf("\033[1;36m\r\n[DUMP] ");        \
        printf(info,##__VA_ARGS__);   \
	    printf("\r\n\r\n");               \
        log_dump(data, len);          \
        printf("\33[0m\r\n");                              \
    } while(0)

void log_dump(const uint8_t *data, uint16_t len);
#else
#define LOG_DUMP(info, data, len)
#endif

#ifdef __cplusplus
}
#endif

#endif /* LOGGER_H */
