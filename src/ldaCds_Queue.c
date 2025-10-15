#include <ldaCds_Queue.h>

ldaCds_Queue *ldaCds_CreateQueue(void *_queuestate)
{
    ldaCds_Queue *newqueue = malloc(sizeof(ldaCds_Queue));
    if(newqueue == NULL) return NULL;
    newqueue->firstelement = NULL;
    newqueue->lastelement = NULL;
    newqueue->queuestate = _queuestate;
    newqueue->queuestatus = ldaCds_StatusNoErrorDetected;
    return newqueue;
}
ldaCds_QueueNode *ldaCds_CreateQueueNode(void *_nodedata, void *_nodestate)
{
    ldaCds_QueueNode *newnode = malloc(sizeof(ldaCds_QueueNode));
    if(newnode == NULL) return NULL;
    newnode->nextnode = NULL;
    newnode->nodedata = _nodedata;
    newnode->nodestate = _nodestate;
    return newnode;
}
bool ldaCds_QueueHasState(ldaCds_Queue *_queue)
{
    if(_queue == NULL) return false;
    return _queue->queuestate != NULL;
}
bool ldaCds_QueueNodeHasState(ldaCds_QueueNode *_queuenode)
{
    if(_queuenode== NULL) return false;
    return _queuenode->nodestate != NULL;
}
bool ldaCds_QueueIsEmpty(ldaCds_Queue *_queue)
{
    if(_queue == NULL) return false;
    return _queue->firstelement == NULL && _queue->lastelement == NULL;
}

ldaCds_QueueNode *ldaCds_QueuePeek(ldaCds_Queue *_queue)
{
    if(_queue == NULL) return NULL;
    return _queue->firstelement;
}
ldaCds_QueueNode *ldaCds_QueueEnqueue(ldaCds_Queue *_queue, ldaCds_QueueNode *_queuenode, LDACDS_CBF(Q,Queue,q), LDACDS_CBF(QN,QueueNode,qn))
{
    if(_queue == NULL) return NULL;
    if(_queuenode == NULL)
    {
        _queue->queuestatus = ldaCds_StatusNodeParameterIsNUll;
        return NULL;
    }
    if(ldaCds_QueueIsEmpty(_queue))
    {
        _queue->firstelement = _queuenode;
        _queue->lastelement = _queuenode;
    }else
    {
        _queue->lastelement->nextnode = _queuenode;
        _queue->lastelement = _queuenode;
    }
    if(_callbackQN != NULL)
    {
        _callbackQN(_queuenode);
    }
    if(_callbackQ != NULL)
    {
        _callbackQ(_queue);
    }
    _queue->queuestatus = ldaCds_StatusNoErrorDetected;
    return _queuenode;
}
ldaCds_QueueNode *ldaCds_QueueDequeue(ldaCds_Queue *_queue, LDACDS_CBF(Q,Queue,q), LDACDS_CBF(QN,QueueNode,qn))
{
    if(_queue == NULL) return NULL;
    if(ldaCds_QueueIsEmpty(_queue))
    {
        _queue->queuestatus = ldaCds_StatusStructureIsAlreadyEmpty;
        return NULL;
    }
    ldaCds_QueueNode *node = _queue->firstelement;
    if(node == _queue->lastelement)
    {
        _queue->firstelement = NULL;
        _queue->lastelement = NULL;
    }else
    {
        _queue->firstelement = node->nextnode;
        node->nextnode = NULL;
    }
    if(_callbackQN != NULL)
    {
        _callbackQN(node);
    }
    if(_callbackQ != NULL)
    {
        _callbackQ(_queue);
    }
    _queue->queuestatus = ldaCds_StatusNoErrorDetected;
    return node;
}
bool ldaCds_QueueDequeueDelete(ldaCds_Queue *_queue, LDACDS_CBF(Q,Queue,q), LDACDS_CBF(QN,QueueNode,qn))
{
    if(_queue == NULL) return false;
    if(ldaCds_QueueIsEmpty(_queue))
    {
        _queue->queuestatus = ldaCds_StatusStructureIsAlreadyEmpty;
        return false;
    }
    ldaCds_QueueNode *node = _queue->firstelement;
    if(node == _queue->lastelement)
    {
        _queue->firstelement = NULL;
        _queue->lastelement = NULL;
    }else
    {
        _queue->firstelement = node->nextnode;
        node->nextnode = NULL;
    }
    if(_callbackQN != NULL)
    {
        _callbackQN(node);
    }
    if(_callbackQ != NULL)
    {
        _callbackQ(_queue);
    }
    _queue->queuestatus = ldaCds_StatusNoErrorDetected;
    free(node);
    return true;
}
bool ldaCds_QueueClear(ldaCds_Queue *_queue, LDACDS_CBF(Q,Queue,q), LDACDS_CBF(QN,QueueNode,qn))
{
    if(_queue == NULL) return false;
    while(ldaCds_QueueDequeueDelete(_queue,NULL,_callbackQN));
    if(_callbackQ != NULL)
    {
        _callbackQ(_queue);
    }
    _queue->queuestatus = ldaCds_StatusNoErrorDetected;
    return true;
}
bool ldaCds_QueueDelete(ldaCds_Queue *_queue, LDACDS_CBF(Q,Queue,q), LDACDS_CBF(QN,QueueNode,qn))
{
    if(_queue == NULL) return false;
    if(!ldaCds_QueueClear(_queue,NULL,_callbackQN))
    {
        _queue->queuestatus = ldaCds_StatusStructureCantBeCleared;
        return false;
    }
    if(_callbackQ != NULL)
    {
        _callbackQ(_queue);
    }
    free(_queue);
    return true;
}