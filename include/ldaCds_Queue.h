#ifndef LDACDS_QUEUE_H
#define LDACDS_QUEUE_H

#include <stdlib.h>
#include <stddef.h>
#include <stdbool.h>

#include <ldaCds.h>

typedef struct __ldacds_queuenode__
{
    void *nodedata;
    void *nodestate;
    struct __ldacds_queuenode__ *nextnode;
}ldaCds_QueueNode;
typedef struct
{
    void *queuestate;
    ldaCds_StatusCode queuestatus;
    ldaCds_QueueNode *firstelement;
    ldaCds_QueueNode *lastelement;
}ldaCds_Queue;

ldaCds_Queue *ldaCds_CreateQueue(void *_queuestate);
ldaCds_Queue *ldaCds_CreateQueueNode(void *_nodedata, void *_nodestate);
bool ldaCds_QueueHasState(ldaCds_Queue *_queue);
bool ldaCds_QueueNodeHasState(ldaCds_QueueNode *_queuenode);
bool ldaCds_QueueIsEmpty(ldaCds_Queue *_queue);

ldaCds_QueueNode *ldaCds_QueuePeek(ldaCds_Queue *_queue);
ldaCds_QueueNode *ldaCds_QueueEnqueue(ldaCds_Queue *_queue, ldaCds_QueueNode *_queuenode, LDACDS_CBF(Q,Queue,q), LDACDS_CBF(QN,QueueNode,qn));
ldaCds_QueueNode *ldaCds_QueueDequeue(ldaCds_Queue *_queue, LDACDS_CBF(Q,Queue,q), LDACDS_CBF(QN,QueueNode,qn));
bool ldaCds_QueueDequeueDelete(ldaCds_Queue *_queue, LDACDS_CBF(Q,Queue,q), LDACDS_CBF(QN,QueueNode,qn));
bool ldaCds_QueueClear(ldaCds_Queue *_queue, LDACDS_CBF(Q,Queue,q), LDACDS_CBF(QN,QueueNode,qn));
bool ldaCds_QueueDelete(ldaCds_Queue *_queue, LDACDS_CBF(Q,Queue,q), LDACDS_CBF(QN,QueueNode,qn));

#endif /* LDACDS_QUEUE_H */
