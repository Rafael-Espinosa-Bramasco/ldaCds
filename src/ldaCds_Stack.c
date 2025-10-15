#include <ldaCds_Stack.h>

ldaCds_Stack *ldaCds_CreateStack(void *_stackstate)
{
    ldaCds_Stack *newstack = malloc(sizeof(ldaCds_Stack));
    if(newstack == NULL) return NULL;
    newstack->stackstate = _stackstate;
    newstack->stackstatus = ldaCds_StatusNoErrorDetected;
    newstack->stacktop = NULL;
    return newstack;
}
ldaCds_StackNode *ldaCds_CreateStackNode(void *_nodedata, void *_nodestate)
{
    ldaCds_StackNode *newnode = malloc(sizeof(ldaCds_StackNode));
    if(newnode == NULL) return NULL;
    newnode->nodebelow = NULL;
    newnode->nodedata = _nodedata;
    newnode->nodestate = _nodestate;
    return newnode;
}
bool ldaCds_StackHasState(ldaCds_Stack *_stack)
{
    if(_stack == NULL) return false;
    return _stack->stackstate != NULL;
}
bool ldaCds_StackNodeHasState(ldaCds_StackNode *_stacknode)
{
    if(_stacknode == NULL) return false;
    return _stacknode->nodestate != NULL;
}
bool ldaCds_StackIsEmpty(ldaCds_Stack *_stack)
{
    if(_stack == NULL) return false;
    return _stack->stacktop == NULL;
}

ldaCds_StackNode *ldaCds_StackPeek(ldaCds_Stack *_stack)
{
    if(_stack == NULL) return NULL;
    return _stack->stacktop;
}
ldaCds_StackNode *ldaCds_StackPush(ldaCds_Stack *_stack, ldaCds_StackNode *_stacknode, LDACDS_CBF(S,Stack,s), LDACDS_CBF(SN,StackNode,sn))
{
    if(_stack == NULL) return NULL;
    if(_stacknode == NULL)
    {
        _stack->stackstatus = ldaCds_StatusNodeParameterIsNUll;
        return NULL;
    }
    _stacknode->nodebelow = _stack->stacktop;
    _stack->stacktop = _stacknode;
    if(_callbackSN != NULL)
    {
        callbackSN(_stacknode);
    }
    if(_callbackS != NULL)
    {
        callbackS(_stack);
    }
    _stack->stackstatus = ldaCds_StatusNoErrorDetected;
    return _stacknode;
}
ldaCds_StackNode *ldaCds_StackPop(ldaCds_Stack *_stack, LDACDS_CBF(S,Stack,s), LDACDS_CBF(SN,StackNode,sn))
{
    if(_stack == NULL) return NULL;
    ldaCds_StackNode *node = _stack->stacktop;
    if(ldaCds_StackIsEmpty(_stack))
    {
        _stack->stackstatus = ldaCds_StatusStructureIsAlreadyEmpty;
        return NULL;
    }else
    {
        _stack->stacktop = node->nodebelow;
        node->nodebelow = NULL;
    }
    if(_callbackSN != NULL)
    {
        callbackSN(node);
    }
    if(_callbackS != NULL)
    {
        callbackS(_stack);
    }
    _stack->stackstatus = ldaCds_StatusNoErrorDetected;
    return node;
}
bool ldaCds_StackPopDelete(ldaCds_Stack *_stack, LDACDS_CBF(S,Stack,s), LDACDS_CBF(SN,StackNode,sn))
{
    if(_stack == NULL) return false;
    ldaCds_StackNode *node = _stack->stacktop;
    if(ldaCds_StackIsEmpty(_stack))
    {
        _stack->stackstatus = ldaCds_StatusStructureIsAlreadyEmpty;
        return false;
    }else
    {
        _stack->stacktop = node->nodebelow;
        node->nodebelow = NULL;
    }
    if(_callbackSN != NULL)
    {
        callbackSN(node);
    }
    if(_callbackS != NULL)
    {
        callbackS(_stack);
    }
    free(node);
    _stack->stackstatus = ldaCds_StatusNoErrorDetected;
    return true;
}
bool ldaCds_StackClear(ldaCds_Stack *_stack, LDACDS_CBF(S,Stack,s), LDACDS_CBF(SN,StackNode,sn))
{
    if(_stack == NULL) return false;
    while(ldaCds_StackPopDelete(_stack,NULL,_callbackSN));
    if(_callbackS != NULL)
    {
        _callbackS(_stack);
    }
    _stack->stackstatus = ldaCds_StatusNoErrorDetected;
    return true;
}
bool ldaCds_StackDelete(ldaCds_Stack *_stack, LDACDS_CBF(S,Stack,s), LDACDS_CBF(SN,StackNode,sn))
{
    if(_stack == NULL) return false;
    if(!ldaCds_StackClear(_stack,NULL,_callbackSN))
    {
        _stack->stackstatus = ldaCds_StatusStructureCantBeCleared;
        return false;
    }
    if(_callbackS != NULL)
    {
        _callbackS(_stack);
    }
    free(_stack);
    return true;
}