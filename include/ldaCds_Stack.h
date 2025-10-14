#ifndef LDACDS_STACK_H
#define LDACDS_STACK_H

#include <stdlib.h>
#include <stddef.h>
#include <stdbool.h>

#include <ldaCds.h>

typedef struct __ldacds_stacknode__
{
    void *nodedata;
    void *nodestate;
    struct __ldacds_stacknode__ *nodebelow;
}ldaCds_StackNode;
typedef struct
{
    void *stackstate;
    ldaCds_StatusCode stackstatus;
    ldaCds_StackNode *stacktop;
}ldaCds_Stack;

ldaCds_Stack *ldaCds_CreateStack(void *_stackstate);
ldaCds_StackNode *ldaCds_CreateStackNode(void *_nodedata, void *_nodestate);
bool ldaCds_StackHasState(ldaCds_Stack *_stack);
bool ldaCds_StackNodeHasState(ldaCds_StackNode *_stacknode);
bool ldaCds_StackIsEmpty(ldaCds_Stack *_stack);

ldaCds_StackNode *ldaCds_StackPeek(ldaCds_Stack *_stack);
ldaCds_StackNode *ldaCds_StackPush(ldaCds_Stack *_stack, ldaCds_StackNode *_stacknode, LDACDS_CBF(S,Stack,s), LDACDS_CBF(SN,StackNode,sn));
ldaCds_StackNode *ldaCds_StackPop(ldaCds_Stack *_stack, LDACDS_CBF(S,Stack,s), LDACDS_CBF(SN,StackNode,sn));
bool ldaCds_StackPopDelete(ldaCds_Stack *_stack, LDACDS_CBF(S,Stack,s), LDACDS_CBF(SN,StackNode,sn));
bool ldaCds_StackClear(ldaCds_Stack *_stack, LDACDS_CBF(S,Stack,s), LDACDS_CBF(SN,StackNode,sn));
bool ldaCds_StackDelete(ldaCds_Stack *_stack, LDACDS_CBF(S,Stack,s), LDACDS_CBF(SN,StackNode,sn));

#endif /* LDACDS_STACK_H */
