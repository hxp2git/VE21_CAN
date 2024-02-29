/******************************************************************************
 * @brief    通用队列管理
 ******************************************************************************/
#ifndef _QUEUE_H_
#define _QUEUE_H_

#include <stdbool.h>

#ifdef __cplusplus
extern "C"
{
#endif

    typedef struct
    {
        void *base;                  /*队列容器基地址*/
        unsigned short element_size; /*队列元素大小*/
        unsigned short size;         /*队列容器可容纳元素个数*/
        unsigned short front;        /*队首*/
        unsigned short rear;         /*队尾*/
    } DrvQueueDataStruct;

    typedef struct
    {
        bool (*queue_create)(DrvQueueDataStruct *q, void *container, int size, int element_size);
        bool (*queue_peek)(DrvQueueDataStruct *q, void **element);
        bool (*queue_put)(DrvQueueDataStruct *q, void *element);
        bool (*queue_get)(DrvQueueDataStruct *q, void *element);
        bool (*queue_del)(DrvQueueDataStruct *q);
        void (*queue_clr)(DrvQueueDataStruct *q);
        int (*queue_len)(DrvQueueDataStruct *q);
    } DrvQueueInterfaceStruct;
    extern const DrvQueueInterfaceStruct g_drv_queue_interface;
#ifdef __cplusplus
}
#endif

#endif
