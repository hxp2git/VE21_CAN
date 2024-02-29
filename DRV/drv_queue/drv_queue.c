/******************************************************************************
 * @brief    通用队列管理
 *
 * Copyright (c) 2017~2020, <morro_luo@163.com>
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2017-03-19     Morro        Initial version.
 ******************************************************************************/
#include "drv_queue.h"
#include <stddef.h>
#include <string.h>

/* @brief      创建一个队列
 * @param[in]  q    - 队列管理器
 * @param[in]  base - 队列容器基地址
 * @param[in]  size - 队列容器可容纳元素个数
 * @param[in]  element_size - 队列元素大小(sizeof(type))
 * @return     true - 创建成功, false - 创建失败
 */
static bool queue_create(DrvQueueDataStruct *q, void *base, int size, int element_size)
{
    if (q == NULL || base == NULL || size == 0 || element_size == 0)
        return false;
    q->base = base;
    q->size = size;
    q->element_size = element_size;
    q->front = q->rear = 0;
    return true;
}

/* @brief      判断队列是否为空
 * @return    true - 队列为空, false - 队列非空
 */
static bool queue_is_empty(DrvQueueDataStruct *q)
{
    return q->front == q->rear;
}

/* @brief      判断队列是否满
 * @return     true - 队列非满, false - 队列未满
 */
static bool queue_is_full(DrvQueueDataStruct *q)
{
    return (q->rear + 1) % q->size == q->front;
}

/* @brief      入队(添加元素至队尾)
 * @param[in]  element  - 队列元素
 * @return     true - 成功入队, false - 队列满
 */
static bool queue_put(DrvQueueDataStruct *q, void *element)
{
    if (queue_is_full(q))
        return false;
    memcpy((unsigned char *)q->base + q->rear * q->element_size, element,
           q->element_size);
    q->rear = (q->rear + 1) % q->size;
    return true;
}

/* @brief      出队(移除队首元素)
 * @param[in]  element  - 指向队首元素的地址
 * @return     true - 成功出队, false - 队列为空
 */
static bool queue_get(DrvQueueDataStruct *q, void *element)
{
    if (queue_is_empty(q))
        return false;
    memcpy(element, (unsigned char *)q->base + q->front * q->element_size,
           q->element_size);
    q->front = (q->front + 1) % q->size;
    return true;
}

/* @brief      获取队首元素地址(预读取)
 * @param[in]  element  - 指向队首元素的地址
 * @return     true - 获取成功, false - 获取失败队列为空
 */
static bool queue_peek(DrvQueueDataStruct *q, void **element)
{
    if (queue_is_empty(q))
        return false;
    *element = (void *)((unsigned char *)q->base + q->front *
                                                       q->element_size);
    return true;
}

/* @brief      删除队尾元素
 * @return     true - 成功移除, false -  队列为空,
 */
static bool queue_del(DrvQueueDataStruct *q)
{
    if (queue_is_empty(q))
        return false;
    q->front = (q->front + 1) % q->size;
    return true;
}

/* @brief      获取队列元素个数
 * @return    队列元素个数
 */
static int queue_size(DrvQueueDataStruct *q)
{
    return (q->rear + q->size - q->front) % q->size;
}

/* @brief      清空队列
 * @return    none
 */
static void queue_clr(DrvQueueDataStruct *q)
{
    q->front = q->rear = 0;
}
const DrvQueueInterfaceStruct g_drv_queue_interface = {
    .queue_create = queue_create,
    .queue_peek = queue_peek,
    .queue_put = queue_put,
    .queue_get = queue_get,
    .queue_del = queue_del,
    .queue_clr = queue_clr,
    .queue_len = queue_size};
